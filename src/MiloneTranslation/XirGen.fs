module rec MiloneTranslation.XirGen

open MiloneShared.SharedTypes
open MiloneShared.TypeFloat
open MiloneShared.TypeIntegers
open MiloneShared.Util
open MiloneTranslation.Hir
open MiloneTranslation.Xir

module S = MiloneStd.StdString
module TMap = MiloneStd.StdMap
module TSet = MiloneStd.StdSet

type private TraceFun = string -> string list -> unit

let private expect (context: _) (opt: 'T option) : 'T =
  match opt with
  | Some it -> it
  | None -> unreachable context

// -----------------------------------------------
// HIR helpers
// -----------------------------------------------

[<RequireQualifiedAccess>]
type private PrimTyInfo =
  | None
  | ScalarAdd
  | StrAdd
  | Option of optionItemTy: Ty

let private primTyInfo (prim: HPrim) (args: HExpr list) (targetTy: Ty) : PrimTyInfo =
  match prim, args, targetTy with
  | HPrim.Add, l :: _, _ ->
    let (Ty (tk, _)) = exprToTy l

    match tk with
    | IntTk _
    | FloatTk _
    | CharTk -> PrimTyInfo.ScalarAdd

    | StrTk -> PrimTyInfo.StrAdd
    | _ -> unreachable ()

  | HPrim.OptionSome, arg :: _, _ -> PrimTyInfo.Option(exprToTy arg)
  | HPrim.OptionSome, _, _ -> unreachable ()
  | HPrim.OptionNone, [], Ty (OptionTk, [ itemTy ]) -> PrimTyInfo.Option(itemTy)
  | HPrim.OptionNone, _, _ -> unreachable ()

  | _ -> PrimTyInfo.None

// -----------------------------------------------
// XIR helpers
// -----------------------------------------------

/// Target represents a context of evaluating an expr.
///
/// After the expr is evaluated, the value is set to the local
/// and code jumps to the block.
type private XTarget = XLocalId * XBlockId

let private unreachableBlockDef : XBlockDef =
  { Stmts = []
    Terminator = XUnreachableTk }

let private emptyLocals : AssocMap<XLocalId, XLocalDef> = TMap.empty compare
let private emptyBlocks : AssocMap<XBlockId, XBlockDef> = TMap.empty compare

let private xLocalPlace (local: XLocalId) : XPlace = { Local = local; Path = [] }

let private xArgOfRval (rval: XRval) : XArg option =
  match rval with
  | XLitRval (lit, loc) -> XLitArg(lit, loc) |> Some
  | XUnitRval loc -> XUnitArg loc |> Some
  | XLocalRval (localId, loc) -> XLocalArg(localId, loc) |> Some
  | _ -> None

let private xRvalOfArg (arg: XArg) : XRval =
  match arg with
  | XLitArg (lit, loc) -> XLitRval(lit, loc)
  | XUnitArg loc -> XUnitRval loc
  | XLocalArg (localId, loc) -> XLocalRval(localId, loc)

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private Ctx =
  { Serial: Serial
    Vars: AssocMap<VarSerial, VarDef>
    Funs: AssocMap<FunSerial, FunDef>
    // Variants: AssocMap<VariantSerial, VariantDef>
    Tys: AssocMap<TySerial, TyDef>

    MainFunOpt: FunSerial option

    TyMangleMemo: AssocMap<Ty, string>
    OptionTyMap: AssocMap<Ty, XUnionTyId>
    ListTyMap: AssocMap<Ty, XUnionTyId>
    XRecords: AssocMap<XRecordTyId, XRecordDef>
    XVariants: AssocMap<XVariantId, XVariantDef>
    XUnions: AssocMap<XUnionTyId, XUnionDef>

    // Done bodies.
    Bodies: XBodyDef list
    MainBodyIdOpt: XBodyId option

    // Current block:
    CurrentBlockOpt: XBlockId option
    Stmts: XStmt list
    TerminatorOpt: XTerminator option

    // Current body:
    CurrentBodyOpt: XBodyDef option
    Locals: AssocMap<XLocalId, XLocalDef>
    Blocks: AssocMap<XBlockId, XBlockDef>

    Trace: TraceFun }

let private ofTyCtx (trace: TraceFun) (tyCtx: TyCtx) : Ctx =
  { Serial = tyCtx.Serial
    Vars = tyCtx.Vars
    Funs = tyCtx.Funs
    // Variants = tyCtx.Variants
    MainFunOpt = tyCtx.MainFunOpt
    Tys = tyCtx.Tys
    TyMangleMemo = TMap.empty tyCompare
    OptionTyMap = TMap.empty tyCompare
    ListTyMap = TMap.empty tyCompare
    XRecords = TMap.empty compare
    XVariants = TMap.empty compare
    XUnions = TMap.empty compare

    Bodies = []
    MainBodyIdOpt = None
    CurrentBlockOpt = None
    Stmts = []
    TerminatorOpt = None
    CurrentBodyOpt = None
    Locals = emptyLocals
    Blocks = emptyBlocks

    Trace = trace }

let private toProgram (ctx: Ctx) : XProgram =
  // instead of generating XProgram, print debug info...
  ctx.Trace "toProgram:" []

  List.fold
    (fun () (body: XBodyDef) ->
      ctx.Trace "\nbody \"{}\" {}" [ body.Name; locToString body.Loc ]

      ctx.Trace
        "  locals({})"
        [ body.Locals
          |> TMap.toList
          |> List.length
          |> string ]

      TMap.fold
        (fun () (localId: XLocalId) (local: XLocalDef) ->
          ctx.Trace
            "    {}#{}"
            [ Option.defaultValue "" local.Name
              string localId ])
        ()
        body.Locals

      ctx.Trace
        "  blocks ({})"
        [ body.Blocks
          |> TMap.toList
          |> List.length
          |> string ]

      TMap.fold
        (fun () (blockId: XBlockId) (block: XBlockDef) ->
          ctx.Trace "    #{}" [ string blockId ]

          List.fold (fun () stmt -> ctx.Trace "  ;{}" [ objToString stmt ]) () block.Stmts
          ctx.Trace "    !{}" [ objToString block.Terminator ])
        ()
        body.Blocks)
    ()
    ctx.Bodies

  exit 1

let private freshSerial (ctx: Ctx) =
  ctx.Serial + 1, { ctx with Serial = ctx.Serial + 1 }

let private freshSerialBy (n: int) (ctx: Ctx) =
  assert (n >= 1)
  ctx.Serial + n, { ctx with Serial = ctx.Serial + n }

let private enterBlock blockId (ctx: Ctx) =
  let parent =
    ctx.CurrentBlockOpt, ctx.Stmts, ctx.TerminatorOpt

  let ctx =
    { ctx with
        CurrentBlockOpt = Some blockId
        Stmts = []
        TerminatorOpt = None }

  parent, ctx

let private leaveBlock parent (ctx: Ctx) =
  let exitBlockId = ctx.CurrentBlockOpt |> expect ()
  let stmts = ctx.Stmts |> List.rev
  let terminator = ctx.TerminatorOpt |> expect ()

  let ctx =
    let blockIdOpt, stmts, terminatorOpt = parent

    { ctx with
        CurrentBlockOpt = blockIdOpt
        Stmts = stmts
        TerminatorOpt = terminatorOpt }

  let ctx =
    let blockDef : XBlockDef =
      { Stmts = stmts
        Terminator = terminator }

    { ctx with
        Blocks = ctx.Blocks |> TMap.add exitBlockId blockDef }

  ctx

let private addStmt stmt (ctx: Ctx) =
  if ctx.TerminatorOpt |> Option.isSome then
    ctx
  else
    { ctx with Stmts = stmt :: ctx.Stmts }

let private setTerminator terminator (ctx: Ctx) =
  if ctx.TerminatorOpt |> Option.isSome then
    ctx
  else
    { ctx with
        TerminatorOpt = Some terminator }

/// Allocates a fresh local.
let private addLocal (name: string) (ty: XTy) (loc: Loc) (ctx: Ctx) : XLocalId * Ctx =
  let localId, ctx = freshSerial ctx

  let localDef : XLocalDef =
    { Name = Some name
      Id = localId
      Ty = ty
      Loc = loc }

  let ctx =
    { ctx with
        Locals = ctx.Locals |> TMap.add localId localDef }

  localId, ctx

/// Converts Ty -> XTy and adds an local of the type.
let private addTempLocal (name: string) (ty: Ty) (loc: Loc) (ctx: Ctx) =
  let ty, ctx = xgTy ty ctx
  addLocal name ty loc ctx

let private freshBlock (ctx: Ctx) =
  let blockId, ctx = freshSerial ctx

  let ctx =
    { ctx with
        Blocks = ctx.Blocks |> TMap.add blockId unreachableBlockDef }

  blockId, ctx

let private finishBranching terminator targetBlock (ctx: Ctx) =
  let blockId = ctx.CurrentBlockOpt |> expect ()
  let stmts = ctx.Stmts |> List.rev
  let terminatorOpt = ctx.TerminatorOpt

  let ctx =
    let blockDef = ctx.Blocks |> mapFind blockId
    assert (blockDef.Stmts |> List.isEmpty)

    let blockDef =
      { blockDef with
          Stmts = stmts
          Terminator = Option.defaultValue terminator terminatorOpt }

    { ctx with
        Blocks = ctx.Blocks |> TMap.add blockId blockDef }

  { ctx with
      CurrentBlockOpt = Some targetBlock
      Stmts = []
      TerminatorOpt = None }

// -----------------------------------------------
// symbols
// -----------------------------------------------

let private xgVar varSerial (ctx: Ctx) : XLocalId * Ctx =
  let varDef = mapFind varSerial ctx.Vars

  match varDef.IsStatic with
  | IsStatic -> todo ()

  | NotStatic ->
    let localId : XLocalId = varSerial |> varSerialToInt

    if ctx.Locals |> TMap.containsKey localId then
      localId, ctx
    else
      let ty, (ctx: Ctx) = xgTy varDef.Ty ctx

      let localDef : XLocalDef =
        { Name = Some varDef.Name
          Id = localId
          Ty = ty
          Loc = varDef.Loc }

      let ctx =
        { ctx with
            Locals = ctx.Locals |> TMap.add localId localDef }

      localId, ctx

// -----------------------------------------------
// tys
// -----------------------------------------------

// Type conversion doesn't recurse thanks to auto-boxing.

let private ctxTyMangle (ty: Ty) (ctx: Ctx) =
  let name, memo = tyMangle (ty, ctx.TyMangleMemo)
  name, { ctx with TyMangleMemo = memo }

let private xgOptionTy (itemTy: Ty) (ctx: Ctx) : XUnionTyId * Ctx =
  match ctx.OptionTyMap |> TMap.tryFind itemTy with
  | Some it -> it, ctx

  | None ->
    let n, ctx = freshSerialBy 3 ctx
    let unionTyId = n
    let noneVariantId = n + 1
    let someVariantId = n + 2

    let optionTy = tyOption itemTy
    let name, ctx = ctxTyMangle optionTy ctx
    let someTy, ctx = xgTy itemTy ctx

    let noneVariant : XVariantDef =
      { Name = "None"
        HasPayload = false
        PayloadTy = XUnitTy
        IsNewtype = false }

    let someVariant : XVariantDef =
      { Name = "Some"
        HasPayload = true
        PayloadTy = someTy
        IsNewtype = false }

    let unionDef : XUnionDef =
      { Name = name
        Variants = [ noneVariantId; someVariantId ] }

    let ctx =
      { ctx with
          OptionTyMap = ctx.OptionTyMap |> TMap.add itemTy unionTyId
          XVariants =
            ctx.XVariants
            |> TMap.add noneVariantId noneVariant
            |> TMap.add someVariantId someVariant
          XUnions = ctx.XUnions |> TMap.add unionTyId unionDef }

    unionTyId, ctx

let private xgTy (ty: Ty) (ctx: Ctx) : XTy * Ctx =
  let (Ty (tk, tyArgs)) = ty

  match tk, tyArgs with
  | IntTk flavor, _ -> XIntTy flavor, ctx
  | StrTk, _ -> XStrTy, ctx
  | BoolTk, _ -> XBoolTy, ctx
  | TupleTk, [] -> XUnitTy, ctx

  | OptionTk, [ itemTy ] ->
    let unionTyId, ctx = xgOptionTy itemTy ctx
    XUnionTy unionTyId, ctx
  | OptionTk, _ -> unreachable ()

  | _ -> todo ty

// -----------------------------------------------
// pats
// -----------------------------------------------

let private xgPatAsIrrefutable (pat: HPat) (cond: XArg) (ctx: Ctx) : Ctx =
  match pat with
  | HDiscardPat _
  | HNodePat (HTuplePN, [], _, _) -> ctx

  | HVarPat (_, varSerial, _, loc) ->
    let local, ctx = xgVar varSerial ctx

    ctx
    |> addStmt (XAssignStmt(xLocalPlace local, xRvalOfArg cond, loc))

  | HAsPat (innerPat, varSerial, loc) ->
    let local, ctx = xgVar varSerial ctx

    let ctx =
      ctx
      |> addStmt (XAssignStmt(xLocalPlace local, xRvalOfArg cond, loc))

    xgPatAsIrrefutable innerPat cond ctx

  | _ -> todo ()

// -----------------------------------------------
// pattern matching
// -----------------------------------------------

/// Tries to *sugar* a match expression to if expression
/// when `match p with true -> body | false -> alt`.
let private mcToIf (cond: XArg) (condTy: Ty) arms target loc (ctx: Ctx) : Ctx option =
  match condTy, arms with
  | Ty (BoolTk, []),
    [ HLitPat (BoolLit true, _), HLitExpr (BoolLit true, _), body;
      HLitPat (BoolLit false, _), HLitExpr (BoolLit true, _), alt ] ->

    let bodyBlock, ctx = xgExprAsBranch body target loc ctx
    let altBlock, ctx = xgExprAsBranch alt target loc ctx

    ctx
    |> finishBranching (XIfTk(cond, bodyBlock, altBlock, loc)) (snd target)
    |> Some

  | _ -> None

// -----------------------------------------------
// expr: prim and node
// -----------------------------------------------

let private xgPrimExpr (prim: HPrim) (tyInfo: PrimTyInfo) loc ctx : XRval * Ctx =
  match prim, tyInfo with
  | HPrim.OptionNone, PrimTyInfo.Option itemTy ->
    let unionId, ctx = xgOptionTy itemTy ctx
    XAggregateRval(XUnionAk unionId, [], loc), ctx

  | HPrim.Nil, _ -> todo ()

  | _ -> unreachable () // Must be called.

let private xgCallPrim (prim: HPrim) (tyInfo: PrimTyInfo) (args: XArg list) loc ctx : XRval * Ctx =
  let regularAction stmt ctx =
    let ctx = ctx |> addStmt stmt
    XUnitRval loc, ctx

  match prim, args, tyInfo with
  // operator:
  | HPrim.Not, [ arg ], _ -> XUnaryRval(XNotUnary, arg, loc), ctx
  | HPrim.Not, _, _ -> unreachable ()

  | HPrim.Add, [ l; r ], PrimTyInfo.ScalarAdd -> XBinaryRval(XAddBinary, l, r, loc), ctx
  | HPrim.Add, [ l; r ], PrimTyInfo.StrAdd -> XBinaryRval(XStrAddBinary, l, r, loc), ctx
  | HPrim.Add, _, _ -> unreachable ()

  // constructor:
  | HPrim.OptionSome, [ arg ], PrimTyInfo.Option itemTy ->
    let ty, ctx = xgOptionTy itemTy ctx
    XAggregateRval(XUnionAk ty, [ arg ], loc), ctx

  // effects:
  | HPrim.Exit, [ arg ], _ -> XUnitRval loc, setTerminator (XExitTk(arg, loc)) ctx
  | HPrim.Exit, _, _ -> unreachable ()

  | HPrim.Printfn, _, _ -> regularAction (XPrintfnStmt(args, loc)) ctx

  | HPrim.PtrWrite, [ l; r ], _ -> regularAction (XPtrWriteStmt(l, r, loc)) ctx
  | HPrim.PtrWrite, _, _ -> unreachable ()

  | HPrim.Nil, _, _
  | HPrim.OptionNone, _, _ -> unreachable () // Can't be called.

  | _ -> todo ()

let private xgNodeExpr (expr: HExpr) (ctx: Ctx) : XRval * Ctx =
  let kind, args, targetTy, loc =
    match expr with
    | HNodeExpr (kind, args, ty, loc) -> kind, args, ty, loc
    | _ -> unreachable ()

  match kind, args with
  | HMinusEN, [ arg ] ->
    let arg, ctx = xgExprToArg (arg, ctx)
    XUnaryRval(XMinusUnary, arg, loc), ctx

  | HCallProcEN, HFunExpr (funSerial, _, _) :: args ->
    let args, ctx = (args, ctx) |> stMap xgExprToArg
    ctx.Trace "unimplemented call-fun expr {} ({})" [ objToString kind; locToString loc ]
    // let ctx = ctx |> addStmt (XPrintfnStmt(args, loc))
    XUnitRval loc, ctx

  | HCallProcEN, HPrimExpr (prim, _, _) :: args ->
    let tyInfo = primTyInfo prim args targetTy
    let args, ctx = (args, ctx) |> stMap xgExprToArg
    xgCallPrim prim tyInfo args loc ctx

  | _ ->
    ctx.Trace "unimplemented node expr {} ({})" [ objToString kind; locToString loc ]
    let args, ctx = (args, ctx) |> stMap xgExprToArg
    // todo
    XUnitRval loc, ctx

// -----------------------------------------------
// expr: pattern matching
// -----------------------------------------------

let private xgMatchExpr (expr: HExpr) (ctx: Ctx) : XArg * Ctx =
  let cond, arms, targetTy, loc =
    match expr with
    | HMatchExpr (cond, arms, ty, loc) -> cond, arms, ty, loc
    | _ -> unreachable ()

  let condTy = exprToTy cond
  let cond, ctx = xgExprToArg (cond, ctx)

  let targetLocal, ctx = addTempLocal "match" targetTy loc ctx
  let targetBlock, ctx = freshBlock ctx
  let target : XTarget = targetLocal, targetBlock

  match mcToIf cond condTy arms target loc ctx with
  | Some ctx ->
    assert (ctx.CurrentBlockOpt |> expect () = targetBlock)
    XLocalArg(targetLocal, loc), ctx

  | None ->
    ctx.Trace "unimplemented full-match" []
    XLocalArg(targetLocal, loc), ctx

let private xgLetValExpr (expr: HExpr) (ctx: Ctx) : Ctx =
  let pat, init =
    match expr with
    | HLetValExpr (pat, init, _, _, _) -> pat, init
    | _ -> unreachable ()

  let init, ctx = xgExprToArg (init, ctx)
  xgPatAsIrrefutable pat init ctx

// -----------------------------------------------
// expr: exprToXxx flavors
// -----------------------------------------------

let private xgExprToArg (expr: HExpr, ctx: Ctx) : XArg * Ctx =
  let rval, ctx = xgExprToRval expr ctx

  match xArgOfRval rval with
  | Some it -> it, ctx

  | None ->
    let ty, loc = exprExtract expr
    let localId, ctx = addTempLocal "rval" ty loc ctx

    let ctx =
      ctx
      |> addStmt (XAssignStmt(xLocalPlace localId, rval, loc))

    XLocalArg(localId, loc), ctx

let private xgExprToRval (expr: HExpr) (ctx: Ctx) : XRval * Ctx =
  match expr with
  | HLitExpr (lit, loc) -> XLitRval(lit, loc), ctx

  | HVarExpr (varSerial, _, loc) ->
    let localId, ctx = xgVar varSerial ctx
    XLocalRval(localId, loc), ctx

  | HFunExpr _ -> failwith "fun expr must occur as callee or arg of closure"

  | HVariantExpr (serial, ty, loc) -> todo ()

  | HPrimExpr (prim, targetTy, loc) ->
    let tyInfo = primTyInfo prim [] targetTy
    xgPrimExpr prim tyInfo loc ctx

  | HMatchExpr _ ->
    let arg, ctx = xgMatchExpr expr ctx
    xRvalOfArg arg, ctx

  | HNodeExpr _ -> xgNodeExpr expr ctx

  | HBlockExpr (stmts, last) ->
    let ctx = xgStmts stmts ctx
    xgExprToRval last ctx

  | HLetValExpr _ ->
    let ctx = xgLetValExpr expr ctx
    XUnitRval(exprToLoc expr), ctx

  | HLetFunExpr _ // Nested HLetFunExpr is resolved in Hoist.
  | HNavExpr _ // HNavExpr is resolved in RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

let private xgExprAsStmt (expr: HExpr) (ctx: Ctx) : Ctx =
  match expr with
  | HLitExpr _
  | HVarExpr _
  | HFunExpr _
  | HVariantExpr _ -> ctx

  | _ when ctx.TerminatorOpt |> Option.isSome ->
    ctx.Trace
      "unreachable expr deleted {} {}"
      [ locToString (exprToLoc expr)
        objToString expr ]

    ctx

  | HBlockExpr (stmts, last) ->
    let ctx = xgStmts stmts ctx
    xgExprAsStmt last ctx

  | HLetValExpr _ -> xgLetValExpr expr ctx

  | _ ->
    let _, ctx = xgExprToArg (expr, ctx)
    ctx

let private xgStmts (stmts: HExpr list) (ctx: Ctx) : Ctx =
  List.fold (fun ctx expr -> xgExprAsStmt expr ctx) ctx stmts

let private xgExprAsBranch (expr: HExpr) (target: XTarget) (loc: Loc) (ctx: Ctx) : XBlockId * Ctx =
  let entryBlockId, ctx = freshBlock ctx

  let parent, ctx = enterBlock entryBlockId ctx
  let rval, (ctx: Ctx) = xgExprToRval expr ctx

  let ctx =
    let targetLocal, targetBlockId = target

    ctx
    |> addStmt (XAssignStmt(xLocalPlace targetLocal, rval, loc))
    |> setTerminator (XJumpTk targetBlockId)

  let ctx = leaveBlock parent ctx

  entryBlockId, ctx

// -----------------------------------------------
// decls
// -----------------------------------------------

let private xgLetFunDeclContents (decl: HExpr, ctx: Ctx) =
  assert (ctx.CurrentBlockOpt |> Option.isNone)
  assert (ctx.Stmts |> List.isEmpty)
  assert (ctx.TerminatorOpt |> Option.isNone)
  assert (ctx.CurrentBodyOpt |> Option.isNone)
  assert (ctx.Locals |> TMap.isEmpty)
  assert (ctx.Blocks |> TMap.isEmpty)

  let funSerial, argPats, bodyExpr, loc =
    match decl with
    | HLetFunExpr (funSerial, _, _, argPats, body, _, _, loc) -> funSerial, argPats, body, loc
    | _ -> unreachable ()

  let funDef = ctx.Funs |> mapFind funSerial

  let bodyId, ctx = freshSerial ctx

  let bodyDef : XBodyDef =
    { Name = funDef.Name
      Loc = funDef.Loc

      ArgTys = []
      ResultTy = XUnitTy
      Locals = emptyLocals
      Blocks = emptyBlocks
      EntryBlockId = -1 }

  let ctx =
    let mainBodyIdOpt =
      match ctx.MainFunOpt with
      | Some mainFun when mainFun = funSerial -> Some bodyId
      | _ -> ctx.MainBodyIdOpt

    { ctx with
        MainBodyIdOpt = mainBodyIdOpt
        CurrentBodyOpt = Some bodyDef }

  // Compute signature.

  // Generate blocks.
  let entryBlockId, ctx = freshBlock ctx
  let noBlock, ctx = enterBlock entryBlockId ctx
  // process arg pats
  let resultArg, ctx = xgExprToArg (bodyExpr, ctx)

  let ctx =
    { ctx with
        TerminatorOpt = Some(Option.defaultValue (XReturnTk resultArg) ctx.TerminatorOpt) }

  let ctx = leaveBlock noBlock ctx

  let bodyDef =
    { bodyDef with
        Locals = ctx.Locals
        Blocks = ctx.Blocks
        EntryBlockId = entryBlockId }

  { ctx with
      Bodies = bodyDef :: ctx.Bodies
      CurrentBodyOpt = None
      Locals = emptyLocals
      Blocks = emptyBlocks }

let private xgDecl (decl: HExpr, ctx: Ctx) =
  match decl with
  | HBlockExpr (stmts, last) ->
    if stmts |> List.forall hxIsUnitLit |> not then
      ctx.Trace "// top-level block: {}" [ objToString stmts ]

    xgDecl (last, ctx)

  | HLetValExpr (pat, _, next, _, loc) ->
    ctx.Trace "// top-level let-val: {} ({})" [ objToString pat; locToString loc ]
    xgDecl (next, ctx)

  | HLetFunExpr (_, _, _, _, _, next, _, _) ->
    ctx.Trace
      "// top-level fun: {} {}"
      [ exprToLoc decl |> locToString
        objToString decl ]

    let ctx = xgLetFunDeclContents (decl, ctx)
    xgDecl (next, ctx)

  | _ ->
    if hxIsUnitLit decl |> not then
      ctx.Trace
        "// top-level non-fun: {} {}"
        [ exprToLoc decl |> locToString
          objToString decl ]

    ctx

let xirGen (trace: TraceFun) (decls: HExpr list, tyCtx: TyCtx) : XProgram =
  let ctx = ofTyCtx trace tyCtx

  let ctx =
    List.fold (fun ctx decl -> xgDecl (decl, ctx)) ctx decls

  ctx |> toProgram
