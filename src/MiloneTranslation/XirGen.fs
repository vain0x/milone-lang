module rec MiloneTranslation.XirGen

open MiloneShared.SharedTypes
open MiloneShared.TypeFloat
open MiloneShared.TypeIntegers
open MiloneShared.Util
open MiloneTranslation.Hir
open MiloneTranslation.Xir
open MiloneTranslation.PatCompile

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
  | NoInfo
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

  | _ -> PrimTyInfo.NoInfo

// -----------------------------------------------
// XIR helpers
// -----------------------------------------------

/// Target represents a context of evaluating an expr.
///
/// After the expr is evaluated, the value is set to the local
/// and code jumps to the block.
type private XTarget = XLocalId * XBlockId

let private xtInt = XIntTy(IntFlavor(Signed, I32))

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
  | XDiscriminantRval (variantId, loc) -> XDiscriminantArg(variantId, loc) |> Some
  | XLocalRval (localId, loc) -> XLocalArg(localId, loc) |> Some
  | _ -> None

let private xRvalOfArg (arg: XArg) : XRval =
  match arg with
  | XLitArg (lit, loc) -> XLitRval(lit, loc)
  | XUnitArg loc -> XUnitRval loc
  | XDiscriminantArg (variantId, loc) -> XDiscriminantRval(variantId, loc)
  | XLocalArg (localId, loc) -> XLocalRval(localId, loc)

let private xAssignStmtToLocalFromRval local rval loc =
  XAssignStmt(xLocalPlace local, rval, loc)

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
  ctx.Serial + 1, { ctx with Serial = ctx.Serial + n }

let private funSerialToBodyId (funSerial: FunSerial) : XBodyId = funSerialToInt funSerial

// -----------------------------------------------
// Context: places and values
// -----------------------------------------------

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

/// Converts an rval to a local (fresh temporary).
let private rvalToLocal (rval: XRval) (ty: XTy) (loc: Loc) (ctx: Ctx) : XLocalId * Ctx =
  let localOpt =
    match rval with
    | XLocalRval (local, _) -> Some local
    | XPlaceRval (place, _) when List.isEmpty place.Path -> Some place.Local
    | _ -> None

  match localOpt with
  | Some it -> it, ctx

  | None ->
    let localId, ctx = addLocal "rval" ty loc ctx

    let ctx =
      ctx
      |> addStmt (xAssignStmtToLocalFromRval localId rval loc)

    localId, ctx

/// Converts an rval to an arg (fresh temporary).
let private rvalToArg (rval: XRval) (ty: XTy) (loc: Loc) (ctx: Ctx) : XArg * Ctx =
  match xArgOfRval rval with
  | Some arg -> arg, ctx

  | None ->
    let local, ctx = rvalToLocal rval ty loc ctx
    XLocalArg(local, loc), ctx

// -----------------------------------------------
// Context: statements, terminators and blocks
// -----------------------------------------------

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

let private freshBlock (ctx: Ctx) =
  let blockId, ctx = freshSerial ctx

  let ctx =
    { ctx with
        Blocks = ctx.Blocks |> TMap.add blockId unreachableBlockDef }

  blockId, ctx

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

/// Emits after all branches in the current conditional branching
/// (those branches should jump to the target if converging).
///
/// Emits a terminator in the case it's converging.
/// Current block switches to the target.
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

let private jumpToTarget rval (target: XTarget) loc (ctx: Ctx) =
  let local, block = target

  ctx
  |> addStmt (xAssignStmtToLocalFromRval local rval loc)
  |> setTerminator (XJumpTk block)

/// Emits a (chain of) basic block as a branch of conditional branching.
///
/// That block jumps to the specified target if converging.
///
/// `f` is a function to emit code for that block
/// and return a value to be passed to the target.
let private emitInBranch (f: Ctx -> XRval * Ctx) blockId target loc ctx : Ctx =
  let parent, ctx = enterBlock blockId ctx
  let rval, (ctx: Ctx) = f ctx
  let ctx = jumpToTarget rval target loc ctx
  leaveBlock parent ctx

/// Emits a (chain of) fresh basic block as a branch.
let private emitInFreshBranch (f: Ctx -> XRval * Ctx) target loc ctx : XBlockId * Ctx =
  let entryBlockId, ctx = freshBlock ctx

  let ctx =
    emitInBranch f entryBlockId target loc ctx

  entryBlockId, ctx

/// Emits an if-like control structure.
/// Always terminates and jumps to target if converging.
let private emitIf (cond: XArg) (body: Ctx -> XRval * Ctx) (alt: Ctx -> XRval * Ctx) (target: XTarget) loc ctx : Ctx =
  let bodyBlock, ctx = emitInFreshBranch body target loc ctx
  let altBlock, ctx = emitInFreshBranch alt target loc ctx

  ctx
  |> finishBranching (XIfTk(cond, bodyBlock, altBlock, loc)) (snd target)

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

/// Converts a var to place, assigned an initial value.
let private xgVarWithRval varSerial (init: XRval) loc ctx =
  let local, ctx = xgVar varSerial ctx

  let ctx =
    ctx
    |> addStmt (xAssignStmtToLocalFromRval local init loc)

  XPlaceRval(xLocalPlace local, loc), ctx

// -----------------------------------------------
// tys
// -----------------------------------------------

// Type conversion doesn't recurse thanks to auto-boxing.

let private ctxTyMangle (ty: Ty) (ctx: Ctx) =
  let name, memo = tyMangle (ty, ctx.TyMangleMemo)
  name, { ctx with TyMangleMemo = memo }

let private computeNoneVariantId (unionTyId: XUnionTyId) : XVariantId = unionTyId + 1

let private computeSomeVariantId (unionTyId: XUnionTyId) : XVariantId = unionTyId + 2

let private xgOptionTy (itemTy: Ty) (ctx: Ctx) : XUnionTyId * Ctx =
  match ctx.OptionTyMap |> TMap.tryFind itemTy with
  | Some it -> it, ctx

  | None ->
    let n, ctx = freshSerialBy 3 ctx
    let unionTyId = n
    let noneVariantId = n + 1
    let someVariantId = n + 2
    assert (computeNoneVariantId unionTyId = noneVariantId)
    assert (computeSomeVariantId unionTyId = someVariantId)

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

type private PatTermHost =
  { Guard: int -> Ctx -> XArg * Ctx
    Body: int -> Ctx -> Ctx
    Fallback: int -> Ctx -> Ctx }

let private optionTyToItemTy (ty: XTy) (ctx: Ctx) =
  match ty with
  | XUnionTy unionTyId ->
    let variantId = computeSomeVariantId unionTyId
    let variantDef = ctx.XVariants |> mapFind variantId
    assert (variantDef.Name = "Some")
    unionTyId, variantDef.PayloadTy

  | _ -> unreachable () // not an option type

let private isNoneRval (arg: XRval) argTy loc ctx =
  let unionTyId, _itemTy = optionTyToItemTy argTy ctx

  let argLocal, ctx = rvalToLocal arg argTy loc ctx

  let place : XPlace =
    { Local = argLocal
      Path = [ XPart.Discriminant ] }

  let l, ctx =
    rvalToArg (XPlaceRval(place, loc)) xtInt loc ctx

  let r =
    XDiscriminantArg(computeNoneVariantId unionTyId, loc)

  XBinaryRval(XScalarEqualBinary, l, r, loc), ctx

let private xgPatTerm (host: PatTermHost) (term: PTerm) (cond: XRval) condTy loc ctx : Ctx =
  match term with
  | PAbortTerm -> setTerminator (XExitTk(XLitArg(IntLit "1", loc))) ctx

  | PSelectTerm (part, term) ->
    match part with
    | PSomeContentPart ->
      let local, ctx = rvalToLocal cond condTy loc ctx
      let unionTyId, condTy = optionTyToItemTy condTy ctx

      let cond =
        let place : XPlace =
          { Local = local
            Path = [ XPart.Payload(computeSomeVariantId unionTyId) ] }

        XPlaceRval(place, loc)

      xgPatTerm host term cond condTy loc ctx

    | _ -> todo ()

  | PGuardTerm (clauseIndex, body, alt) ->
    let guard, ctx = host.Guard clauseIndex ctx

    let bodyBlock, ctx =
      xgPatTermAsFreshBranch host body cond condTy loc ctx

    let altBlock, ctx =
      xgPatTermAsFreshBranch host alt cond condTy loc ctx

    ctx
    |> setTerminator (XIfTk(guard, bodyBlock, altBlock, loc))

  | PBodyTerm i ->
    let ctx = host.Body i ctx
    assert (ctx.TerminatorOpt |> Option.isSome)
    ctx

  | PFallbackTerm i ->
    let ctx = host.Fallback i ctx
    assert (ctx.TerminatorOpt |> Option.isSome)
    ctx

  | PLetTerm (varSerial, _, term) ->
    let cond, ctx = xgVarWithRval varSerial cond loc ctx
    xgPatTerm host term cond condTy loc ctx

  | PMatchOptionTerm (_, termOnNone, termOnSome) ->
    let isNoneArg, ctx =
      let rval, ctx = isNoneRval cond condTy loc ctx
      rvalToArg rval XBoolTy loc ctx

    let bodyBlock, ctx =
      xgPatTermAsFreshBranch host termOnNone cond condTy loc ctx

    let altBlock, ctx =
      xgPatTermAsFreshBranch host termOnSome cond condTy loc ctx

    ctx
    |> setTerminator (XIfTk(isNoneArg, bodyBlock, altBlock, loc))

  | _ -> todo ()

let private xgPatTermInBranch (host: PatTermHost) blockId (term: PTerm) (cond: XRval) condTy loc ctx =
  let parent, ctx = enterBlock blockId ctx
  let ctx = xgPatTerm host term cond condTy loc ctx
  leaveBlock parent ctx

let private xgPatTermAsFreshBranch (host: PatTermHost) (term: PTerm) (cond: XRval) condTy loc ctx =
  let entryBlockId, ctx = freshBlock ctx

  let ctx =
    xgPatTermInBranch host entryBlockId term cond condTy loc ctx

  entryBlockId, ctx

let private xgPatAsIrrefutable (pat: HPat) (cond: XRval) (ctx: Ctx) : Ctx =
  match pat with
  | HDiscardPat _
  | HNodePat (HTuplePN, [], _, _) -> ctx

  | HVarPat (_, varSerial, _, loc) ->
    let _, ctx = xgVarWithRval varSerial cond loc ctx
    ctx

  | HAsPat (innerPat, varSerial, loc) ->
    let cond, ctx = xgVarWithRval varSerial cond loc ctx
    xgPatAsIrrefutable innerPat cond ctx

  | _ -> todo ()

// -----------------------------------------------
// pattern matching
// -----------------------------------------------

/// Tries to *sugar* a match expression to if expression
/// when `match p with true -> body | false -> alt`.
let private mcToIf (cond: XArg) (condTy: Ty) arms target loc (ctx: Ctx) : Ctx option =
  match condTy, arms with
  // | true -> ... | false -> ...
  | Ty (BoolTk, []),
    [ HLitPat (BoolLit true, _), HLitExpr (BoolLit true, _), body;
      HLitPat (BoolLit false, _), HLitExpr (BoolLit true, _), alt ] ->

    ctx
    |> emitIf cond (fun ctx -> xgExprToRval body ctx) (fun ctx -> xgExprToRval alt ctx) target loc
    |> Some

  // | None -> ... | _ -> ...
  | Ty (OptionTk, [ itemTy ]),
    [ HNodePat (HNonePN, _, _, _), HLitExpr (BoolLit true, _), noneCl; HDiscardPat _, HLitExpr (BoolLit true, _), someCl ] ->

    let cond, ctx =
      let unionTyId, ctx = xgOptionTy itemTy ctx

      let condLocal, ctx =
        let condTy, ctx = xgTy condTy ctx
        rvalToLocal (xRvalOfArg cond) condTy loc ctx

      let l, ctx =
        let place : XPlace =
          { Local = condLocal
            Path = [ XPart.Discriminant ] }

        rvalToArg (XPlaceRval(place, loc)) xtInt loc ctx

      let r =
        XDiscriminantArg(computeNoneVariantId unionTyId, loc)

      rvalToArg (XBinaryRval(XScalarEqualBinary, l, r, loc)) XBoolTy loc ctx

    ctx
    |> emitIf cond (fun ctx -> xgExprToRval noneCl ctx) (fun ctx -> xgExprToRval someCl ctx) target loc
    |> Some

  | _ -> None

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
    let condTy, ctx = xgTy condTy ctx
    let cond = xRvalOfArg cond

    let n = List.length arms

    let terms =
      patCompileForMatchExprToBlocks (List.map (fun (pat, _, _) -> pat) arms)

    let serial, ctx = freshSerialBy (n * 4) ctx
    let nthArmId (i: int) : XBlockId = serial + i * 4
    let nthBodyId (i: int) : XBlockId = serial + i * 4 + 1

    let host : PatTermHost =
      { Guard =
          fun i ctx ->
            let guard =
              match List.tryItem i arms with
              | Some (_, guard, _) -> guard
              | _ -> unreachable ()

            xgExprToArg (guard, ctx)

        Body = fun i ctx -> ctx |> setTerminator (XJumpTk(nthBodyId i))
        Fallback = fun i ctx -> ctx |> setTerminator (XJumpTk(nthArmId i)) }

    let ctx =
      let zipped =
        match listTryZip arms terms with
        | it, [], [] -> it
        | _ -> unreachable ()

      zipped
      |> List.mapi (fun i ((_, guard, body), term) -> i, guard, body, term)
      |> List.fold
           (fun (ctx: Ctx) (i, _guard, body, term) ->
             // arm:
             let ctx =
               let entryBlockId = nthArmId i
               let parent, ctx = enterBlock entryBlockId ctx
               let ctx = xgPatTerm host term cond condTy loc ctx
               leaveBlock parent ctx

             // body:
             let ctx =
               let entryBlockId = nthBodyId i
               let parent, ctx = enterBlock entryBlockId ctx
               let rval, ctx = xgExprToRval body ctx
               let ctx = jumpToTarget rval target loc ctx
               leaveBlock parent ctx

             ctx)
           ctx

    let ctx =
      ctx
      |> finishBranching (XJumpTk(nthArmId 0)) targetBlock

    XLocalArg(targetLocal, loc), ctx

let private xgLetValExpr (expr: HExpr) (ctx: Ctx) : Ctx =
  let pat, init =
    match expr with
    | HLetValExpr (pat, init, _, _, _) -> pat, init
    | _ -> unreachable ()

  let init, ctx = xgExprToRval init ctx
  xgPatAsIrrefutable pat init ctx

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
  | HPrim.Exit, [ arg ], _ -> XUnitRval loc, setTerminator (XExitTk arg) ctx
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
    let bodyId = funSerialToBodyId funSerial
    let args, ctx = (args, ctx) |> stMap xgExprToArg

    let resultLocal, ctx =
      let name =
        (ctx.Funs |> mapFind funSerial).Name + "_result"

      addTempLocal name targetTy loc ctx

    let ctx =
      ctx
      |> addStmt (XCallStmt(bodyId, args, xLocalPlace resultLocal, loc))

    XLocalRval(resultLocal, loc), ctx

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
// expr: exprToXxx flavors
// -----------------------------------------------

let private xgExprToArg (expr: HExpr, ctx: Ctx) : XArg * Ctx =
  let rval, ctx = xgExprToRval expr ctx

  match xArgOfRval rval with
  | Some it -> it, ctx

  | None ->
    let ty, loc = exprExtract expr
    let ty, ctx = xgTy ty ctx
    rvalToArg rval ty loc ctx

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

  let bodyId = funSerialToInt funSerial

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
      | Some mainFun when funSerialToInt mainFun = funSerialToInt funSerial -> Some bodyId
      | _ -> ctx.MainBodyIdOpt

    { ctx with
        MainBodyIdOpt = mainBodyIdOpt
        CurrentBodyOpt = Some bodyDef }

  // Compute signature.

  // Generate blocks.
  let entryBlockId, ctx = freshBlock ctx

  let ctx =
    let noBlock, ctx = enterBlock entryBlockId ctx
    // process arg pats
    let resultArg, ctx = xgExprToArg (bodyExpr, ctx)

    let ctx =
      { ctx with
          TerminatorOpt = Some(Option.defaultValue (XReturnTk resultArg) ctx.TerminatorOpt) }

    leaveBlock noBlock ctx

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
    ctx.Trace "// top-level fun: {}" [ exprToLoc decl |> locToString ]

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
