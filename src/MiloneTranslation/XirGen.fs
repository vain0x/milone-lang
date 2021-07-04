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

/// Target represents a context of evaluating an expr.
///
/// After the expr is evaluated, the value is set to the reg
/// and code jumps to the block.
type private XTarget = XRegId * XBlockId

let private unreachableBlockDef : XBlockDef =
  { Stmts = []
    Terminator = XUnreachableTk }

let private emptyRegs : AssocMap<XRegId, XRegDef> = TMap.empty compare
let private emptyBlocks : AssocMap<XBlockId, XBlockDef> = TMap.empty compare

let private expect (context: _) (opt: 'T option) : 'T =
  match opt with
  | Some it -> it
  | None -> unreachable context

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

    // Done bodies.
    Bodies: XBodyDef list
    MainBodyIdOpt: XBodyId option

    // Current block:
    CurrentBlockOpt: XBlockId option
    Stmts: XStmt list
    TerminatorOpt: XTerminator option

    // Current body:
    CurrentBodyOpt: XBodyDef option
    Regs: AssocMap<XRegId, XRegDef>
    Blocks: AssocMap<XBlockId, XBlockDef>

    Trace: TraceFun }

let private ofTyCtx (trace: TraceFun) (tyCtx: TyCtx) : Ctx =
  { Serial = tyCtx.Serial
    Vars = tyCtx.Vars
    Funs = tyCtx.Funs
    // Variants = tyCtx.Variants
    MainFunOpt = tyCtx.MainFunOpt
    Tys = tyCtx.Tys

    Bodies = []
    MainBodyIdOpt = None
    CurrentBlockOpt = None
    Stmts = []
    TerminatorOpt = None
    CurrentBodyOpt = None
    Regs = emptyRegs
    Blocks = emptyBlocks

    Trace = trace }

let private toProgram (ctx: Ctx) : XProgram =
  // instead of generating XProgram, print debug info...
  ctx.Trace "toProgram:" []

  List.fold
    (fun () (body: XBodyDef) ->
      ctx.Trace "\nbody \"{}\" {}" [ body.Name; locToString body.Loc ]

      ctx.Trace "  regs({})" [ body.Regs |> TMap.toList |> List.length |> string ]

      TMap.fold
        (fun () (regId: XRegId) (reg: XRegDef) ->
          ctx.Trace
            "    {}#{}"
            [ Option.defaultValue "" reg.Name
              string regId ])
        ()
        body.Regs

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

/// Allocates a fresh reg.
let private addReg (name: string) (ty: XTy) (loc: Loc) (ctx: Ctx) : XRegId * Ctx =
  let regId, ctx = freshSerial ctx

  let regDef : XRegDef =
    { Name = Some name
      Id = regId
      Ty = ty
      Loc = loc }

  let ctx =
    { ctx with
        Regs = ctx.Regs |> TMap.add regId regDef }

  regId, ctx

/// Converts Ty -> XTy and adds an reg of the type.
let private addTempReg (name: string) (ty: Ty) (loc: Loc) (ctx: Ctx) =
  let ty, ctx = xgTy (ty, ctx)
  addReg name ty loc ctx

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

let private xgVar varSerial (ctx: Ctx) : XRegId * Ctx =
  let varDef = mapFind varSerial ctx.Vars

  match varDef.IsStatic with
  | IsStatic -> todo ()

  | NotStatic ->
    let regId : XRegId = varSerial |> varSerialToInt

    if ctx.Regs |> TMap.containsKey regId then
      regId, ctx

    else
      let ty, (ctx: Ctx) = xgTy (varDef.Ty, ctx)

      let regDef : XRegDef =
        { Name = Some varDef.Name
          Id = regId
          Ty = ty
          Loc = varDef.Loc }

      let ctx =
        { ctx with
            Regs = ctx.Regs |> TMap.add regId regDef }

      regId, ctx

// -----------------------------------------------
// tys
// -----------------------------------------------

let private xgTy (ty: Ty, ctx: Ctx) : XTy * Ctx =
  let (Ty (tk, tyArgs)) = ty

  match tk, tyArgs with
  | IntTk flavor, _ -> XIntTy flavor, ctx
  | StrTk, _ -> XStrTy, ctx
  | BoolTk, _ -> XBoolTy, ctx
  | TupleTk, [] -> XUnitTy, ctx
  | _ -> todo ty

// -----------------------------------------------
// pats
// -----------------------------------------------

let private xgPatAsIrrefutable (pat: HPat) (cond: XArg) (ctx: Ctx) : Ctx =
  match pat with
  | HDiscardPat _
  | HNodePat (HTuplePN, [], _, _) -> ctx

  | HVarPat (_, varSerial, _, loc) ->
    let reg, ctx = xgVar varSerial ctx
    ctx |> addStmt (XAssignStmt(reg, cond, loc))

  | HAsPat (innerPat, varSerial, loc) ->
    let reg, ctx = xgVar varSerial ctx

    let ctx =
      ctx |> addStmt (XAssignStmt(reg, cond, loc))

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
// exprs
// -----------------------------------------------

let private xgMatchExpr (expr: HExpr) (ctx: Ctx) =
  let cond, arms, targetTy, loc =
    match expr with
    | HMatchExpr (cond, arms, ty, loc) -> cond, arms, ty, loc
    | _ -> unreachable ()

  let condTy = exprToTy cond
  let cond, ctx = xgExprToArg (cond, ctx)

  let targetReg, ctx = addTempReg "match" targetTy loc ctx
  let targetBlock, ctx = freshBlock ctx
  let target : XTarget = targetReg, targetBlock

  match mcToIf cond condTy arms target loc ctx with
  | Some ctx ->
    assert (ctx.CurrentBlockOpt |> expect () = targetBlock)
    XRegArg(targetReg, loc), ctx

  | None ->
    ctx.Trace "unimplemented full-match" []
    XRegArg(targetReg, loc), ctx

let private xgNodeExprToArg (expr: HExpr) (ctx: Ctx) =
  let kind, args, loc =
    match expr with
    | HNodeExpr (kind, args, _, loc) -> kind, args, loc
    | _ -> unreachable ()

  match kind, args with
  | HCallProcEN, HFunExpr (funSerial, _, _) :: args ->
    let args, ctx = (args, ctx) |> stMap xgExprToArg
    ctx.Trace "unimplemented call-fun expr {} ({})" [ objToString kind; locToString loc ]
    // let ctx = ctx |> addStmt (XPrintfnStmt(args, loc))
    XUnitArg loc, ctx

  | HCallProcEN, HPrimExpr (HPrim.Printfn, _, _) :: args ->
    let args, ctx = (args, ctx) |> stMap xgExprToArg
    let ctx = ctx |> addStmt (XPrintfnStmt(args, loc))
    XUnitArg loc, ctx

  | _ ->
    ctx.Trace "unimplemented node expr {} ({})" [ objToString kind; locToString loc ]
    let args, ctx = (args, ctx) |> stMap xgExprToArg
    // todo
    XUnitArg loc, ctx

let private xgLetValExpr (expr: HExpr) (ctx: Ctx) : Ctx =
  let pat, init =
    match expr with
    | HLetValExpr (pat, init, _, _, _) -> pat, init
    | _ -> unreachable ()

  let init, ctx = xgExprToArg (init, ctx)
  xgPatAsIrrefutable pat init ctx

let private xgExprToArg (expr: HExpr, ctx: Ctx) : XArg * Ctx =
  match expr with
  | HLitExpr (lit, loc) -> XLitArg(lit, loc), ctx

  | HVarExpr (varSerial, _, loc) ->
    let regId, ctx = xgVar varSerial ctx
    XRegArg(regId, loc), ctx

  | HFunExpr _ -> failwith "fun expr must occur as callee or arg of closure"

  | HVariantExpr (serial, ty, loc) -> todo ()

  | HPrimExpr (prim, ty, loc) ->
    ctx.Trace "prim {}" [ objToString prim ]
    XRegArg(0, loc), ctx

  | HMatchExpr _ -> xgMatchExpr expr ctx

  | HNodeExpr _ -> xgNodeExprToArg expr ctx

  | HBlockExpr (stmts, last) ->
    let ctx = xgStmts stmts ctx
    xgExprToArg (last, ctx)

  | HLetValExpr _ ->
    let ctx = xgLetValExpr expr ctx
    XUnitArg(exprToLoc expr), ctx

  | HLetFunExpr _ // Nested HLetFunExpr is resolved in Hoist.
  | HNavExpr _ // HNavExpr is resolved in RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

let private xgExprAsStmt (expr: HExpr) (ctx: Ctx) : Ctx =
  match expr with
  | _ when ctx.TerminatorOpt |> Option.isSome ->
    ctx.Trace
      "unreachable expr deleted {} {}"
      [ locToString (exprToLoc expr)
        objToString expr ]

    ctx

  | HLitExpr _
  | HVarExpr _
  | HFunExpr _
  | HVariantExpr _ -> ctx

  | HPrimExpr (prim, ty, loc) ->
    invoke
      (fun () ->
        ctx.Trace "prim at {} {}" [ locToString loc ]
        ctx)

  | HMatchExpr _ ->
    let _, ctx = xgMatchExpr expr ctx
    ctx

  | HNodeExpr _ ->
    let _, ctx = xgNodeExprToArg expr ctx
    ctx

  | HBlockExpr (stmts, last) ->
    let ctx = xgStmts stmts ctx
    xgExprAsStmt last ctx

  | HLetValExpr _ -> xgLetValExpr expr ctx

  | HLetFunExpr _ // Nested HLetFunExpr is resolved in Hoist.
  | HNavExpr _ // HNavExpr is resolved in RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

let private xgExprAsBranch (expr: HExpr) (target: XTarget) (loc: Loc) (ctx: Ctx) : XBlockId * Ctx =
  let entryBlockId, ctx = freshBlock ctx

  let parent, ctx = enterBlock entryBlockId ctx
  let arg, (ctx: Ctx) = xgExprToArg (expr, ctx)

  let ctx =
    let targetReg, targetBlockId = target

    ctx
    |> addStmt (XAssignStmt(targetReg, arg, loc))
    |> setTerminator (XJumpTk targetBlockId)

  let ctx = leaveBlock parent ctx

  entryBlockId, ctx

let private xgStmts (stmts: HExpr list) (ctx: Ctx) : Ctx =
  List.fold (fun ctx expr -> xgExprAsStmt expr ctx) ctx stmts

// -----------------------------------------------
// decls
// -----------------------------------------------

let private xgLetFunDeclContents (decl: HExpr, ctx: Ctx) =
  assert (ctx.CurrentBlockOpt |> Option.isNone)
  assert (ctx.Stmts |> List.isEmpty)
  assert (ctx.TerminatorOpt |> Option.isNone)
  assert (ctx.CurrentBodyOpt |> Option.isNone)
  assert (ctx.Regs |> TMap.isEmpty)
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
      Regs = emptyRegs
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
        Regs = ctx.Regs
        Blocks = ctx.Blocks
        EntryBlockId = entryBlockId }

  { ctx with
      Bodies = bodyDef :: ctx.Bodies
      CurrentBodyOpt = None
      Regs = emptyRegs
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
