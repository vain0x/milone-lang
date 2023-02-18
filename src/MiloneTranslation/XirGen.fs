module rec MiloneTranslation.XirGen

open MiloneShared.SharedTypes
open MiloneShared.TypeIntegers
open MiloneShared.Util
open MiloneTranslation.Hir
open MiloneTranslation.HirTypes
open MiloneTranslation.Xir
open MiloneTranslation.PatCompile
open Std.StdError
open Std.StdList
open Std.StdMap
open Std.StdPair

module S = Std.StdString

type private TraceFun = string -> string list -> unit

let private expect (context: _) (opt: 'T option) : 'T =
  match opt with
  | Some it -> it
  | None -> unreachable context

module IsMut =
  let toOrdinary isMut =
    match isMut with
    | IsMut -> 1
    | IsConst -> 0

  let compare l r = toOrdinary l - toOrdinary r

// -----------------------------------------------
// HIR helpers
// -----------------------------------------------

[<RequireQualifiedAccess>]
type private PrimTyInfo =
  | NoInfo
  | ScalarOperation
  | StrOperation

let private primTyInfo (prim: HPrim) (args: HExpr list) (targetTy: Ty) : PrimTyInfo =
  let onScalarOrStr expr =
    let (Ty(tk, _)) = exprToTy expr

    match tk with
    | IntTk _
    | FloatTk _
    | BoolTk
    | CharTk -> PrimTyInfo.ScalarOperation

    | StringTk -> PrimTyInfo.StrOperation
    | _ -> unreachable ()

  match prim, args, targetTy with
  | HPrim.Add, l :: _, _ -> onScalarOrStr l

  | HPrim.Equal, l :: _, _ -> onScalarOrStr l
  | HPrim.Less, l :: _, _ -> onScalarOrStr l
  | HPrim.Compare, l :: _, _ -> onScalarOrStr l

  | _ -> PrimTyInfo.NoInfo

// -----------------------------------------------
// XIR helpers
// -----------------------------------------------

/// Target represents a context of evaluating an expr.
///
/// After the expr is evaluated, the value is set to the local
/// and code jumps to the block.
type private XTarget = XLocalId * XBlockId

let private xtInt = XIntTy I32

let private unreachableBlockDef: XBlockDef =
  { Stmts = []
    Terminator = XUnreachableTk }

let private emptyLocals: TreeMap<XLocalId, XLocalDef> = TMap.empty compare
let private emptyBlocks: TreeMap<XBlockId, XBlockDef> = TMap.empty compare

let private xLocalPlace (local: XLocalId) : XPlace = { Local = local; Path = [] }

let private xArgOfRval (rval: XRval) : XArg option =
  match rval with
  | XLitRval(lit, loc) -> XLitArg(lit, loc) |> Some
  | XUnitRval loc -> XUnitArg loc |> Some
  | XDiscriminantRval(variantId, loc) -> XDiscriminantArg(variantId, loc) |> Some
  | XLocalRval(localId, loc) -> XLocalArg(localId, loc) |> Some
  | _ -> None

let private xRvalOfArg (arg: XArg) : XRval =
  match arg with
  | XLitArg(lit, loc) -> XLitRval(lit, loc)
  | XUnitArg loc -> XUnitRval loc
  | XDiscriminantArg(variantId, loc) -> XDiscriminantRval(variantId, loc)
  | XLocalArg(localId, loc) -> XLocalRval(localId, loc)

let private xAssignStmtToLocalFromRval local rval loc =
  XAssignStmt(xLocalPlace local, rval, loc)

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private Ctx =
  { Serial: Serial
    Vars: TreeMap<VarSerial, VarDef>
    Funs: TreeMap<FunSerial, FunDef>
    Variants: TreeMap<VariantSerial, VariantDef>
    Tys: TreeMap<TySerial, TyDef>

    MainFunOpt: FunSerial option

    TyMangleMemo: TreeMap<Ty, string>
    FunTyMap: TreeMap<XTy * XTy, XTy>
    ListTyMap: TreeMap<XTy, XTy>
    NativePtrTyMap: TreeMap<RefMode * XTy, XTy>
    NativeFunTyMap: TreeMap<XTy list * XTy, XTy>
    NativeEmbedTyMap: TreeMap<string, XTy>
    XRecords: TreeMap<XRecordTyId, XRecordDef>
    XVariants: TreeMap<XVariantId, XVariantDef>
    XUnions: TreeMap<XUnionTyId, XUnionDef>

    // Done bodies.
    Bodies: TreeMap<XBodyId, XBodyDef>
    MainBodyIdOpt: XBodyId option

    // Current block:
    CurrentBlockOpt: XBlockId option
    Stmts: XStmt list
    TerminatorOpt: XTerminator option

    // Current body:
    CurrentBodyOpt: XBodyDef option
    ArgLocals: XLocalId list
    ResultLocalOpt: XLocalId option
    Locals: TreeMap<XLocalId, XLocalDef>
    Blocks: TreeMap<XBlockId, XBlockDef>

    Trace: TraceFun }

let private ofTyCtx (trace: TraceFun) (hirCtx: HirCtx) : Ctx =
  { Serial = hirCtx.Serial
    Vars = hirCtx.StaticVars
    Funs = hirCtx.Funs
    Variants = hirCtx.Variants
    MainFunOpt = hirCtx.MainFunOpt
    Tys = hirCtx.Tys

    TyMangleMemo = TMap.empty tyCompare
    FunTyMap = TMap.empty (Pair.compare XTy.compare XTy.compare)
    ListTyMap = TMap.empty XTy.compare
    NativePtrTyMap = TMap.empty (Pair.compare RefMode.compare XTy.compare)
    NativeFunTyMap = TMap.empty (Pair.compare (List.compare XTy.compare) XTy.compare)
    NativeEmbedTyMap = TMap.empty compare

    XRecords = TMap.empty compare
    XVariants = TMap.empty compare
    XUnions = TMap.empty compare

    Bodies = TMap.empty compare
    MainBodyIdOpt = hirCtx.MainFunOpt |> Option.map funSerialToBodyId
    CurrentBlockOpt = None
    Stmts = []
    TerminatorOpt = None
    CurrentBodyOpt = None
    ArgLocals = []
    ResultLocalOpt = None
    Locals = emptyLocals
    Blocks = emptyBlocks

    Trace = trace }

let private initializeCtx (hirCtx: HirCtx) (ctx: Ctx) : Ctx =
  let xVariants, ctx =
    hirCtx.Variants
    |> TMap.fold
      (fun (variants, ctx) variantSerial (variantDef: VariantDef) ->
        let variantId: XVariantId = variantSerial |> variantSerialToInt
        let payloadTy, ctx = xgTy variantDef.PayloadTy ctx

        let xVariantDef: XVariantDef =
          { Name = variantDef.Name
            IsNewtype = variantDef.IsNewtype
            HasPayload = variantDef.HasPayload
            PayloadTy = payloadTy }

        variants |> TMap.add variantId xVariantDef, ctx)
      (TMap.empty compare, ctx)

  let xUnions, xRecords, ctx =
    hirCtx.Tys
    |> TMap.fold
      (fun (unions, records, ctx) tySerial (tyDef: TyDef) ->
        match tyDef with
        | UnionTyDef(ident, _, variants, _) ->
          let xUnionDef: XUnionDef =
            { Name = ident
              Variants = variants |> List.map variantSerialToInt }

          unions |> TMap.add tySerial xUnionDef, records, ctx

        | RecordTyDef(ident, _, fields, _, _) ->
          let fields, ctx =
            fields
            |> List.mapFold
              (fun ctx (ident, ty, _) ->
                let ty, ctx = xgTy ty ctx
                (ident, ty), ctx)
              ctx

          let xRecordDef: XRecordDef = { Name = ident; Fields = fields }
          unions, records |> TMap.add tySerial xRecordDef, ctx

        | OpaqueTyDef _ -> todo ())
      (TMap.empty compare, TMap.empty compare, ctx)

  { ctx with
      XVariants = xVariants
      XUnions = xUnions
      XRecords = xRecords }

let private toProgram (ctx: Ctx) : XProgram =
  // instead of generating XProgram, print debug info...
  ctx.Trace "toProgram:" []

  TMap.fold
    (fun () _ (body: XBodyDef) ->
      ctx.Trace "\nbody \"{0}\" {1}" [ body.Name; Loc.toString body.Loc ]

      ctx.Trace "  locals({0})" [ body.Locals |> TMap.toList |> List.length |> string ]

      TMap.fold
        (fun () (localId: XLocalId) (local: XLocalDef) ->
          ctx.Trace "    {0}#{1}" [ Option.defaultValue "" local.Name; string localId ])
        ()
        body.Locals

      ctx.Trace "  blocks ({0})" [ body.Blocks |> TMap.toList |> List.length |> string ]

      TMap.fold
        (fun () (blockId: XBlockId) (block: XBlockDef) ->
          ctx.Trace "    #{0}" [ string blockId ]

          List.fold (fun () stmt -> ctx.Trace "  ;{0}" [ __dump stmt ]) () block.Stmts
          ctx.Trace "    !{0}" [ __dump block.Terminator ])
        ()
        body.Blocks)
    ()
    ctx.Bodies

  { Bodies = ctx.Bodies
    MainId = ctx.MainBodyIdOpt |> expect () }

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

  let localDef: XLocalDef =
    { Name = Some name
      Arg = false
      Id = localId
      Ty = ty
      Loc = loc }

  let ctx =
    { ctx with
        Locals = ctx.Locals |> TMap.add localId localDef }

  localId, ctx

/// Converts Ty -> XTy and adds an local of the type.
let private addTempLocal (name: string) (ty: Ty) (loc: Loc) (ctx: Ctx) : XLocalId * Ctx =
  let ty, ctx = xgTy ty ctx
  addLocal name ty loc ctx

let private argToLocal (arg: XArg) (ty: XTy) (loc: Loc) (ctx: Ctx) : XLocalId * Ctx =
  rvalToLocal (xRvalOfArg arg) ty loc ctx

/// Converts an rval to a local (fresh temporary).
let private rvalToLocal (rval: XRval) (ty: XTy) (loc: Loc) (ctx: Ctx) : XLocalId * Ctx =
  let localOpt =
    match rval with
    | XLocalRval(local, _) -> Some local
    | XPlaceRval(place, _) when List.isEmpty place.Path -> Some place.Local
    | _ -> None

  match localOpt with
  | Some it -> it, ctx

  | None ->
    let localId, ctx = addLocal "rval" ty loc ctx

    let ctx = ctx |> addStmt (xAssignStmtToLocalFromRval localId rval loc)

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
  let parent = ctx.CurrentBlockOpt, ctx.Stmts, ctx.TerminatorOpt

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
    let blockDef: XBlockDef =
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

  let ctx = emitInBranch f entryBlockId target loc ctx

  entryBlockId, ctx

/// Emits an if-like control structure.
/// Always terminates and jumps to target if converging.
let private emitIf (cond: XArg) (body: Ctx -> XRval * Ctx) (alt: Ctx -> XRval * Ctx) (target: XTarget) loc ctx : Ctx =
  let bodyBlock, ctx = emitInFreshBranch body target loc ctx
  let altBlock, ctx = emitInFreshBranch alt target loc ctx

  ctx |> finishBranching (XIfTk(cond, bodyBlock, altBlock, loc)) (snd target)

// -----------------------------------------------
// symbols
// -----------------------------------------------

let private xgVar varSerial ty (ctx: Ctx) : XLocalId * Ctx =
  let isStatic = false

  if isStatic then
    // FIXME: static var
    todo ()
  else
    let localId: XLocalId = varSerial |> varSerialToInt

    if ctx.Locals |> TMap.containsKey localId then
      localId, ctx
    else
      let localDef: XLocalDef =
        { Name = None
          Id = localId
          Arg = false
          Ty = ty
          Loc = noLoc }

      let ctx =
        { ctx with
            Locals = ctx.Locals |> TMap.add localId localDef }

      localId, ctx

/// Converts a var to place, assigned an initial value.
let private xgVarWithRval varSerial (init: XRval) ty loc ctx =
  let local, ctx = xgVar varSerial ty ctx

  let ctx = ctx |> addStmt (xAssignStmtToLocalFromRval local init loc)

  XPlaceRval(xLocalPlace local, loc), ctx

let private xgVariantExpr expr ctx =
  let variantSerial, ty, loc =
    match expr with
    | HVariantExpr(variantSerial, ty, loc) -> variantSerial, ty, loc
    | _ -> unreachable ()

  let ty, ctx = xgTy ty ctx

  let xUnionId =
    match ty with
    | XUnionTy it -> it
    | _ -> unreachable () // Variant must be a union. (Resolved in )

  assert (ctx.XUnions |> TMap.containsKey xUnionId)

  let xVariantId = variantSerialToInt variantSerial
  assert (ctx.XVariants |> TMap.containsKey xVariantId)

  XAggregateRval(XVariantAk xVariantId, [], loc), ctx

// -----------------------------------------------
// tys
// -----------------------------------------------

// Type conversion doesn't recurse thanks to auto-boxing.

let private ctxTyMangle (ty: Ty) (ctx: Ctx) =
  let name, memo = tyMangle (ty, ctx.TyMangleMemo)
  name, { ctx with TyMangleMemo = memo }

let private xgFunTy sTy tTy (ctx: Ctx) : XTy * Ctx =
  match ctx.FunTyMap |> TMap.tryFind (sTy, tTy) with
  | Some it -> it, ctx
  | None ->
    let funTyId, ctx = freshSerial ctx
    let ty = XFunTy funTyId

    let ctx =
      { ctx with
          FunTyMap = ctx.FunTyMap |> TMap.add (sTy, tTy) ty }

    ty, ctx

let private xgListTy itemTy (ctx: Ctx) : XTy * Ctx =
  match ctx.ListTyMap |> TMap.tryFind itemTy with
  | Some it -> it, ctx
  | None ->
    let listTyId, ctx = freshSerial ctx
    let ty = XListTy listTyId

    let ctx =
      { ctx with
          ListTyMap = ctx.ListTyMap |> TMap.add itemTy ty }

    ty, ctx

let private xgNativePtrTy mode targetTy (ctx: Ctx) : XTy * Ctx =
  match ctx.NativePtrTyMap |> TMap.tryFind (mode, targetTy) with
  | Some it -> it, ctx
  | None ->
    let nativePtrTyId, ctx = freshSerial ctx
    let ty = XNativePtrTy(mode, nativePtrTyId)

    let ctx =
      { ctx with
          NativePtrTyMap = ctx.NativePtrTyMap |> TMap.add (mode, targetTy) ty }

    ty, ctx

let private xgNativeFunTy tyArgs (ctx: Ctx) : XTy * Ctx =
  let argTys, resultTy =
    match splitLast tyArgs with
    | Some it -> it
    | None -> unreachable ()

  match ctx.NativeFunTyMap |> TMap.tryFind (argTys, resultTy) with
  | Some it -> it, ctx
  | None ->
    let nativeFunTyId, ctx = freshSerial ctx
    let ty = XNativeFunTy nativeFunTyId

    let ctx =
      { ctx with
          NativeFunTyMap = ctx.NativeFunTyMap |> TMap.add (argTys, resultTy) ty }

    ty, ctx

let private xgNativeEmbedTy embed (ctx: Ctx) : XTy * Ctx =
  match ctx.NativeEmbedTyMap |> TMap.tryFind embed with
  | Some it -> it, ctx
  | None ->
    let nativeEmbedTyId, ctx = freshSerial ctx
    let ty = XNativeEmbedTy nativeEmbedTyId

    let ctx =
      { ctx with
          NativeEmbedTyMap = ctx.NativeEmbedTyMap |> TMap.add embed ty }

    ty, ctx

let private xgTy (ty: Ty) (ctx: Ctx) : XTy * Ctx =
  let (Ty(tk, tyArgs)) = ty

  let tyArgs, ctx = tyArgs |> List.mapFold (fun ctx ty -> xgTy ty ctx) ctx

  match tk, tyArgs with
  | IntTk flavor, _ -> XIntTy flavor, ctx
  | FloatTk flavor, _ -> XFloatTy flavor, ctx
  | BoolTk, _ -> XBoolTy, ctx
  | CharTk, _ -> XCharTy, ctx
  | StringTk, _ -> XStrTy, ctx
  | ObjTk, _ -> XVoidPtrTy IsConst, ctx

  | TupleTk, [] -> XUnitTy, ctx
  | TupleTk, _ -> unreachable () // Resolved in MonoTy.

  | FunTk, [ sTy; tTy ] -> xgFunTy sTy tTy ctx
  | FunTk, _ -> unreachable ()

  | ListTk, [ itemTy ] -> xgListTy itemTy ctx
  | ListTk, _ -> unreachable ()

  | UnionTk(tySerial, _), _ -> XUnionTy tySerial, ctx
  | RecordTk(tySerial, _), _ -> XRecordTy tySerial, ctx

  | VoidPtrTk isMut, _ -> XVoidPtrTy isMut, ctx
  | NativePtrTk mode, [ targetTy ] -> xgNativePtrTy mode targetTy ctx
  | NativePtrTk _, _ -> unreachable ()
  | FunPtrTk, _ -> xgNativeFunTy tyArgs ctx
  | NativeTypeTk embed, _ -> xgNativeEmbedTy embed ctx

  | OpaqueTk _, _
  | NeverTk, _ -> todo ()

  | MetaTk _, _ -> unreachable () // Resolved in Typing, Monomorphizing and MonoTy.

// -----------------------------------------------
// pats
// -----------------------------------------------

type private PatTermHost =
  { Guard: int -> Ctx -> XArg * Ctx
    Body: int -> Ctx -> Ctx
    Fallback: int -> Ctx -> Ctx }

// let private optionTyToItemTy (ty: XTy) (ctx: Ctx) =
//   match ty with
//   | XUnionTy unionTyId ->
//     let variantId = computeSomeVariantId unionTyId
//     let variantDef = ctx.XVariants |> mapFind variantId
//     assert (variantDef.Name = "Some")
//     unionTyId, variantDef.PayloadTy

//   | _ -> unreachable () // not an option type

// let private isNoneRval (arg: XRval) argTy loc ctx =
//   let unionTyId, _itemTy = optionTyToItemTy argTy ctx

//   let argLocal, ctx = rvalToLocal arg argTy loc ctx

//   let place: XPlace =
//     { Local = argLocal
//       Path = [ XPart.Discriminant ] }

//   let l, ctx =
//     rvalToArg (XPlaceRval(place, loc)) xtInt loc ctx

//   let r =
//     XDiscriminantArg(computeNoneVariantId unionTyId, loc)

//   XBinaryRval(XScalarEqualBinary, l, r, loc), ctx

let private xgPatTerm (host: PatTermHost) (term: PTerm) (cond: XRval) condTy loc ctx : Ctx =
  match term with
  | PAbortTerm -> setTerminator (XExitTk(XLitArg(IntLit "1", loc))) ctx

  | PSelectTerm(part, term) ->
    match part with
    // | PSomeContentPart ->
    //   let local, ctx = rvalToLocal cond condTy loc ctx
    //   let unionTyId, condTy = optionTyToItemTy condTy ctx

    //   let cond =
    //     let place: XPlace =
    //       { Local = local
    //         Path = [ XPart.Payload(computeSomeVariantId unionTyId) ] }

    //     XPlaceRval(place, loc)

    //   xgPatTerm host term cond condTy loc ctx

    | _ -> todo ()

  | PGuardTerm(clauseIndex, body, alt) ->
    let guard, ctx = host.Guard clauseIndex ctx

    let bodyBlock, ctx = xgPatTermAsFreshBranch host body cond condTy loc ctx

    let altBlock, ctx = xgPatTermAsFreshBranch host alt cond condTy loc ctx

    ctx |> setTerminator (XIfTk(guard, bodyBlock, altBlock, loc))

  | PBodyTerm i ->
    let ctx = host.Body i ctx
    assert (ctx.TerminatorOpt |> Option.isSome)
    ctx

  | PFallbackTerm i ->
    let ctx = host.Fallback i ctx
    assert (ctx.TerminatorOpt |> Option.isSome)
    ctx

  | PLetTerm(varSerial, _, term) ->
    let cond, ctx = xgVarWithRval varSerial cond condTy loc ctx

    xgPatTerm host term cond condTy loc ctx

  // | PMatchOptionTerm (_, termOnNone, termOnSome) ->
  //   let isNoneArg, ctx =
  //     let rval, ctx = isNoneRval cond condTy loc ctx
  //     rvalToArg rval XBoolTy loc ctx

  //   let bodyBlock, ctx =
  //     xgPatTermAsFreshBranch host termOnNone cond condTy loc ctx

  //   let altBlock, ctx =
  //     xgPatTermAsFreshBranch host termOnSome cond condTy loc ctx

  //   ctx
  //   |> setTerminator (XIfTk(isNoneArg, bodyBlock, altBlock, loc))

  | _ -> todo ()

let private xgPatTermInBranch (host: PatTermHost) blockId (term: PTerm) (cond: XRval) condTy loc ctx =
  let parent, ctx = enterBlock blockId ctx
  let ctx = xgPatTerm host term cond condTy loc ctx
  leaveBlock parent ctx

let private xgPatTermAsFreshBranch (host: PatTermHost) (term: PTerm) (cond: XRval) condTy loc ctx =
  let entryBlockId, ctx = freshBlock ctx

  let ctx = xgPatTermInBranch host entryBlockId term cond condTy loc ctx

  entryBlockId, ctx

let private xgPatAsIrrefutable (pat: HPat) (cond: XRval) condTy (ctx: Ctx) : Ctx =
  match pat with
  | HDiscardPat _
  | HNodePat(HTuplePN, [], _, _) -> ctx

  | HVarPat(varSerial, _, loc) ->
    let _, ctx = xgVarWithRval varSerial cond condTy loc ctx

    ctx

  | HAsPat(innerPat, varSerial, loc) ->
    let cond, ctx = xgVarWithRval varSerial cond condTy loc ctx

    xgPatAsIrrefutable innerPat cond condTy ctx

  | _ -> todo ()

/// Processes an arg-site pattern to local.
let private xgArgPat funName (i: int) pat ctx : XLocalId * Ctx =
  match pat with
  | HVarPat(varSerial, ty, _) ->
    let ty, ctx = xgTy ty ctx
    xgVar varSerial ty ctx

  | _ ->
    let ty, loc = patExtract pat

    let local, ctx = addTempLocal (funName + "_arg_" + string i) ty loc ctx

    let ctx =
      let ty, ctx = xgTy ty ctx
      xgPatAsIrrefutable pat (XLocalRval(local, loc)) ty ctx

    local, ctx

let private xgArgPats funName argPats ctx : XLocalId list * Ctx =
  let locals, (_, ctx) =
    argPats
    |> List.mapFold
      (fun (i: int, ctx) pat ->
        let local, ctx = xgArgPat funName i pat ctx
        local, (i + 1, ctx))
      (0, ctx)

  locals, ctx

// -----------------------------------------------
// pattern matching
// -----------------------------------------------

/// Tries to *sugar* a match expression to if expression
/// when `match p with true -> body | false -> alt`.
let private mcToIf (cond: XArg) (condTy: Ty) arms target loc (ctx: Ctx) : Ctx option =
  match condTy, arms with
  // | true -> ... | false -> ...
  | Ty(BoolTk, []),
    [ HLitPat(BoolLit true, _), HLitExpr(BoolLit true, _), body
      HLitPat(BoolLit false, _), HLitExpr(BoolLit true, _), alt ] ->

    ctx
    |> emitIf cond (fun ctx -> xgExprToRval body ctx) (fun ctx -> xgExprToRval alt ctx) target loc
    |> Some

  // | None -> ... | _ -> ...
  // | Ty (OptionTk, [ itemTy ]),
  //   [ HNodePat (HNonePN, _, _, _), HLitExpr (BoolLit true, _), noneCl; HDiscardPat _, HLitExpr (BoolLit true, _), someCl ] ->

  //   let cond, ctx =
  //     let unionTyId, ctx = xgOptionTy itemTy ctx

  //     let condLocal, ctx =
  //       let condTy, ctx = xgTy condTy ctx
  //       rvalToLocal (xRvalOfArg cond) condTy loc ctx

  //     let l, ctx =
  //       let place: XPlace =
  //         { Local = condLocal
  //           Path = [ XPart.Discriminant ] }

  //       rvalToArg (XPlaceRval(place, loc)) xtInt loc ctx

  //     let r =
  //       XDiscriminantArg(computeNoneVariantId unionTyId, loc)

  //     rvalToArg (XBinaryRval(XScalarEqualBinary, l, r, loc)) XBoolTy loc ctx

  //   ctx
  //   |> emitIf cond (fun ctx -> xgExprToRval noneCl ctx) (fun ctx -> xgExprToRval someCl ctx) target loc
  //   |> Some

  | _ -> None

// -----------------------------------------------
// expr: pattern matching
// -----------------------------------------------

let private xgMatchExpr (expr: HExpr) (ctx: Ctx) : XArg * Ctx =
  let cond, arms, targetTy, loc =
    match expr with
    | HMatchExpr(cond, arms, ty, loc) -> cond, arms, ty, loc
    | _ -> unreachable ()

  let condTy = exprToTy cond
  let cond, ctx = xgExprToArg (cond, ctx)

  let targetLocal, ctx = addTempLocal "match" targetTy loc ctx
  let targetBlock, ctx = freshBlock ctx
  let target: XTarget = targetLocal, targetBlock

  match mcToIf cond condTy arms target loc ctx with
  | Some ctx ->
    assert (ctx.CurrentBlockOpt |> expect () = targetBlock)
    XLocalArg(targetLocal, loc), ctx

  | None ->
    let condTy, ctx = xgTy condTy ctx
    let cond = xRvalOfArg cond

    let n = List.length arms

    let terms = patCompileForMatchExprToBlocks (List.map (fun (pat, _, _) -> pat) arms)

    let serial, ctx = freshSerialBy (n * 4) ctx
    let nthArmId (i: int) : XBlockId = serial + i * 4
    let nthBodyId (i: int) : XBlockId = serial + i * 4 + 1

    let host: PatTermHost =
      { Guard =
          fun i ctx ->
            let guard =
              match List.tryItem i arms with
              | Some(_, guard, _) -> guard
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

    let ctx = ctx |> finishBranching (XJumpTk(nthArmId 0)) targetBlock

    XLocalArg(targetLocal, loc), ctx

let private xgLetValStmt (letValStmt: HStmt) (ctx: Ctx) : Ctx =
  let pat, init =
    match letValStmt with
    | HLetValStmt(pat, init, _) -> pat, init
    | _ -> unreachable ()

  let initTy, ctx = xgTy (exprToTy init) ctx
  let init, ctx = xgExprToRval init ctx
  xgPatAsIrrefutable pat init initTy ctx

// -----------------------------------------------
// expr: objects
// -----------------------------------------------

let private xgRecordExpr args ty loc (ctx: Ctx) =
  let ty, ctx = xgTy ty ctx

  let recordId =
    match ty with
    | XRecordTy it -> it
    | _ -> unreachable ()

  let fields, ctx = (args, ctx) |> xgExprListToArg

  XAggregateRval(XRecordAk recordId, fields, loc), ctx

let private xgRecordItemExpr index record ty loc (ctx: Ctx) =
  let recordTy, ctx = xgTy (record |> exprToTy) ctx
  let record, ctx = (record, ctx) |> xgExprToLocal
  let _, ctx = xgTy ty ctx

  let recordId =
    match recordTy with
    | XRecordTy it -> it
    | _ -> unreachable ()

  assert (ctx.XRecords |> TMap.containsKey recordId)

  let place: XPlace =
    { Local = record
      Path = [ XPart.Field index ] }

  XPlaceRval(place, loc), ctx

// -----------------------------------------------
// expr: prim and node
// -----------------------------------------------

let private xgPrimExpr (prim: HPrim) (tyInfo: PrimTyInfo) loc ctx : XRval * Ctx =
  match prim, tyInfo with
  // | HPrim.OptionNone, PrimTyInfo.Option itemTy ->
  //   let unionId, ctx = xgOptionTy itemTy ctx
  //   XAggregateRval(XUnionAk unionId, [], loc), ctx

  | HPrim.Nil, _ -> todo ()

  | _ -> unreachable () // Must be called.

let private xgCallPrim (prim: HPrim) (tyInfo: PrimTyInfo) (args: XArg list) loc ctx : XRval * Ctx =
  let regularAction stmt ctx =
    let ctx = ctx |> addStmt stmt
    XUnitRval loc, ctx

  let toBinary binary ctx =
    match args with
    | [ l; r ] -> XBinaryRval(binary, l, r, loc), ctx
    | _ -> unreachable ()

  match prim, args, tyInfo with
  // operator:
  | HPrim.Not, [ arg ], _ -> XUnaryRval(XNotUnary, arg, loc), ctx
  | HPrim.Not, _, _ -> unreachable ()

  | HPrim.Add, [ l; r ], PrimTyInfo.ScalarOperation -> XBinaryRval(XScalarAddBinary, l, r, loc), ctx
  | HPrim.Add, [ l; r ], PrimTyInfo.StrOperation -> XBinaryRval(XStrAddBinary, l, r, loc), ctx
  | HPrim.Add, _, _ -> unreachable ()

  | HPrim.Subtract, _, _ -> toBinary XScalarSubBinary ctx
  | HPrim.Multiply, _, _ -> toBinary XScalarMulBinary ctx
  | HPrim.Divide, _, _ -> toBinary XScalarDivBinary ctx
  | HPrim.Modulo, _, _ -> toBinary XScalarModuloBinary ctx

  | HPrim.Equal, [ l; r ], PrimTyInfo.ScalarOperation -> XBinaryRval(XScalarEqualBinary, l, r, loc), ctx
  | HPrim.Equal, [ l; r ], PrimTyInfo.StrOperation -> XBinaryRval(XStrEqualBinary, l, r, loc), ctx
  | HPrim.Less, [ l; r ], PrimTyInfo.ScalarOperation -> XBinaryRval(XScalarLessBinary, l, r, loc), ctx
  | HPrim.Less, [ l; r ], PrimTyInfo.StrOperation -> XBinaryRval(XStrLessBinary, l, r, loc), ctx
  | HPrim.Compare, [ l; r ], PrimTyInfo.ScalarOperation -> XBinaryRval(XScalarCompareBinary, l, r, loc), ctx
  | HPrim.Compare, [ l; r ], PrimTyInfo.StrOperation -> XBinaryRval(XStrCompareBinary, l, r, loc), ctx

  // string
  | HPrim.StringLength, [ s ], _ -> XUnaryRval(XStrLengthUnary, s, loc), ctx

  // constructor:
  // | HPrim.OptionSome, [ arg ], PrimTyInfo.Option itemTy ->
  //   let ty, ctx = xgOptionTy itemTy ctx
  //   XAggregateRval(XUnionAk ty, [ arg ], loc), ctx

  // effects:
  | HPrim.Assert, [ arg ], _ -> regularAction (XAssertStmt(arg, loc)) ctx
  | HPrim.Assert, _, _ -> unreachable ()
  | HPrim.Printfn, _, _ -> regularAction (XPrintfnStmt(args, loc)) ctx

  | HPrim.NativeCast, [ arg ], _ -> xRvalOfArg arg, ctx // FIXME: insert cast

  // FIXME: replace with HPtrReadEn etc.
  // | HPrim.PtrRead, [ p; i ], _ ->
  //   let q, ctx =
  //     let q = XBinaryRval(XPtrAddBinary, p, i, loc)
  //     rvalToLocal q XUnitTy loc ctx // FIXME: ty info

  //   let place: XPlace = { Local = q; Path = [ XPart.Deref ] }
  //   XPlaceRval(place, loc), ctx

  // | HPrim.PtrWrite, [ p; i; arg ], _ ->
  //   let q, ctx =
  //     let q = XBinaryRval(XPtrAddBinary, p, i, loc)
  //     rvalToLocal q XUnitTy loc ctx // FIXME: ty info

  //   let place: XPlace = { Local = q; Path = [ XPart.Deref ] }
  //   regularAction (XAssignStmt(place, xRvalOfArg arg, loc)) ctx

  // | HPrim.PtrWrite, _, _ -> unreachable ()

  | HPrim.Nil, _, _ // Can't be called.

  | _ -> todo ()

let private xgNodeExpr (expr: HExpr) (ctx: Ctx) : XRval * Ctx =
  let kind, args, targetTy, loc =
    match expr with
    | HNodeExpr(kind, args, ty, loc) -> kind, args, ty, loc
    | _ -> unreachable ()

  let toUnary (kind: XUnary) arg ctx =
    let arg, ctx = xgExprToArg (arg, ctx)
    XUnaryRval(kind, arg, loc), ctx

  let toBinary (kind: XBinary) arg1 arg2 ctx =
    let arg1, ctx = xgExprToArg (arg1, ctx)
    let arg2, ctx = xgExprToArg (arg2, ctx)
    XBinaryRval(kind, arg1, arg2, loc), ctx

  let toNode (kind: XRvalKind) args ctx =
    let args, ctx = (args, ctx) |> xgExprListToArg
    XNodeRval(kind, args, loc), ctx

  match kind, args with
  | HMinusEN, [ arg ] ->
    let arg, ctx = xgExprToArg (arg, ctx)
    XUnaryRval(XMinusUnary, arg, loc), ctx

  | HTupleEN, [] -> XUnitRval loc, ctx
  | HTupleEN, _ -> unreachable () // Non-unit HTupleEN is resolved in MonoTy.

  | HRecordEN, _ -> xgRecordExpr args targetTy loc ctx
  | HRecordItemEN index, [ record ] -> xgRecordItemExpr index record targetTy loc ctx
  | HRecordItemEN _, _ -> unreachable ()

  | HIndexEN, [ l; r ] -> toBinary XStrIndexBinary l r ctx
  | HIndexEN, _ -> unreachable ()
  | HSliceEN, _ -> toNode XRvalKind.StrSlice args ctx

  | HDiscriminantEN variantSerial, _ ->
    let variantId = variantSerialToInt variantSerial
    XDiscriminantRval(variantId, loc), ctx

  | HCallProcEN, HFunExpr(funSerial, _, _, _) :: args ->
    let bodyId = funSerialToBodyId funSerial
    let args, ctx = (args, ctx) |> xgExprListToArg

    let resultLocal, ctx =
      let name = (ctx.Funs |> mapFind funSerial).Name + "_result"

      addTempLocal name targetTy loc ctx

    let ctx = ctx |> addStmt (XCallStmt(bodyId, args, xLocalPlace resultLocal, loc))

    XLocalRval(resultLocal, loc), ctx

  | HCallProcEN, [ HVariantExpr(variantSerial, _, _); payload ] ->
    let payload, ctx = xgExprToArg (payload, ctx)
    let variantId = variantSerialToInt variantSerial
    XAggregateRval(XVariantAk variantId, [ payload ], loc), ctx

  | HCallProcEN, HPrimExpr(prim, _, _) :: args ->
    let tyInfo = primTyInfo prim args targetTy
    let args, ctx = (args, ctx) |> xgExprListToArg
    xgCallPrim prim tyInfo args loc ctx

  // | HCallProcEN, HNodeExpr (HNativeFunEN funSerial, _, _, _) :: args ->
  //   let args, ctx = args |> List.mapFold (fun ctx arg -> xgExprToArg (arg, ctx)) ctx
  //   let result, ctx = addTempLocal "call" targetTy loc ctx

  //   let ctx =
  //     addStmt (XNativeCallStmt(funSerial, args, xLocalPlace result, loc)) ctx

  //   XLocalRval(result, loc), ctx

  | HCallProcEN _, _ -> unreachable expr

  | HCallTailRecEN, _ :: args ->
    let bodyDef = ctx.CurrentBodyOpt |> Option.defaultWith unreachable

    let entryBlockId = bodyDef.EntryBlockId
    assert (entryBlockId <> -1)

    let _, ctx = xgExprsToRval args ctx

    // FIXME: assign to args
    // let ctx =
    //   match listTryZip bodyDef.ArgLocals args with
    //   | zipped, [], [] ->
    //     zipped
    //     |> List.fold
    //          (fun ctx (localId, arg) ->
    //            ctx
    //            |> addStmt (XAssignStmt(xLocalPlace localId, arg, loc)))
    //          ctx
    //   | _ -> unreachable ()

    let ctx = ctx |> setTerminator (XJumpTk entryBlockId)

    XUnitRval loc, ctx

  | _ ->
    ctx.Trace "TODO: unimplemented node expr {0} ({1})" [ __dump kind; Loc.toString loc ]
    let _args, ctx = (args, ctx) |> xgExprListToArg
    XUnitRval loc, ctx

// -----------------------------------------------
// expr: exprToXxx flavors
// -----------------------------------------------

let private xgExprToLocal (expr: HExpr, ctx: Ctx) : XLocalId * Ctx =
  let ty, loc = expr |> exprExtract
  let ty, ctx = xgTy ty ctx
  let rval, ctx = xgExprToRval expr ctx
  rvalToLocal rval ty loc ctx

let private xgExprToArg (expr: HExpr, ctx: Ctx) : XArg * Ctx =
  let rval, ctx = xgExprToRval expr ctx

  match xArgOfRval rval with
  | Some it -> it, ctx

  | None ->
    let ty, loc = exprExtract expr
    let ty, ctx = xgTy ty ctx
    rvalToArg rval ty loc ctx

let private xgExprListToArg (exprs, ctx) : XArg list * Ctx =
  exprs |> List.mapFold (fun ctx expr -> xgExprToArg (expr, ctx)) ctx

let private xgExprToRval (expr: HExpr) (ctx: Ctx) : XRval * Ctx =
  match expr with
  | HLitExpr(lit, loc) -> XLitRval(lit, loc), ctx

  | HVarExpr(varSerial, ty, loc) ->
    let ty, ctx = xgTy ty ctx
    let localId, ctx = xgVar varSerial ty ctx
    XLocalRval(localId, loc), ctx

  | HFunExpr _ -> failwith "fun expr must occur as callee or arg of closure"
  | HVariantExpr _ -> xgVariantExpr expr ctx

  | HPrimExpr(prim, targetTy, loc) ->
    let tyInfo = primTyInfo prim [] targetTy
    xgPrimExpr prim tyInfo loc ctx

  | HMatchExpr _ ->
    let arg, ctx = xgMatchExpr expr ctx
    xRvalOfArg arg, ctx

  | HNodeExpr _ -> xgNodeExpr expr ctx

  | HBlockExpr(stmts, last) ->
    let ctx = xgStmts stmts ctx
    xgExprToRval last ctx

  | HNavExpr _ // HNavExpr is resolved in RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

let private xgExprsToRval exprs ctx =
  exprs |> List.mapFold (fun ctx expr -> xgExprToRval expr ctx) ctx

let private xgExprAsStmt (expr: HExpr) (ctx: Ctx) : Ctx =
  match expr with
  | HLitExpr _
  | HVarExpr _
  | HFunExpr _
  | HVariantExpr _ -> ctx

  | _ when ctx.TerminatorOpt |> Option.isSome ->
    ctx.Trace "unreachable expr deleted {0} {1}" [ Loc.toString (exprToLoc expr); __dump expr ]

    ctx

  | HBlockExpr(stmts, last) ->
    let ctx = xgStmts stmts ctx
    xgExprAsStmt last ctx

  | _ ->
    let _, ctx = xgExprToArg (expr, ctx)
    ctx

let private xgStmts (stmts: HStmt list) (ctx: Ctx) : Ctx = List.fold xgStmt ctx stmts

// -----------------------------------------------
// decls
// -----------------------------------------------

let private xgLetFunStmt (letFunStmt: HStmt) (ctx: Ctx) : Ctx =
  assert (ctx.CurrentBlockOpt |> Option.isNone)
  assert (ctx.Stmts |> List.isEmpty)
  assert (ctx.TerminatorOpt |> Option.isNone)
  assert (ctx.CurrentBodyOpt |> Option.isNone)
  assert (ctx.Locals |> TMap.isEmpty)
  assert (ctx.Blocks |> TMap.isEmpty)

  let funSerial, argPats, bodyExpr, loc =
    match letFunStmt with
    | HLetFunStmt(funSerial, argPats, body, loc) -> funSerial, argPats, body, loc
    | _ -> unreachable ()

  let funDef = ctx.Funs |> mapFind funSerial
  let bodyTy, bodyLoc = exprExtract bodyExpr

  let bodyDef: XBodyDef =
    { Name = funDef.Name
      Loc = funDef.Loc

      ArgTys = []
      ResultTy = XUnitTy
      Locals = emptyLocals
      ArgLocals = []
      ResultLocal = -1
      Blocks = emptyBlocks
      EntryBlockId = -1 }

  let ctx =
    { ctx with
        CurrentBodyOpt = Some bodyDef }

  let argTys, resultTy, ctx =
    let argTys, ctx =
      argPats |> List.mapFold (fun ctx pat -> xgTy (patToTy pat) ctx) ctx

    let resultTy, ctx = xgTy bodyTy ctx
    argTys, resultTy, ctx

  let entryBlockId, resultLocal, argLocals, ctx =
    let entryBlockId, ctx = freshBlock ctx
    let noBlock, ctx = enterBlock entryBlockId ctx

    let ctx =
      { ctx with
          CurrentBodyOpt =
            Some
              { bodyDef with
                  EntryBlockId = entryBlockId } }

    let resultLocal, ctx =
      let name = (funDef.Name + "_result")
      addTempLocal name bodyTy bodyLoc ctx

    let argLocals, ctx = xgArgPats funDef.Name argPats ctx

    let resultRval, ctx = xgExprToRval bodyExpr ctx

    let ctx =
      ctx
      |> addStmt (xAssignStmtToLocalFromRval resultLocal resultRval bodyLoc)
      |> setTerminator XReturnTk

    let ctx = leaveBlock noBlock ctx
    entryBlockId, resultLocal, argLocals, ctx

  let bodyDef =
    let locals =
      ctx.Locals
      |> TMap.map (fun localId (localDef: XLocalDef) ->
        if argLocals |> List.exists (fun a -> a = localId) then
          { localDef with Arg = true }
        else
          localDef)

    { bodyDef with
        Locals = locals
        Blocks = ctx.Blocks
        ArgTys = argTys
        ResultTy = resultTy
        ArgLocals = argLocals
        ResultLocal = resultLocal
        EntryBlockId = entryBlockId }

  { ctx with
      Bodies = ctx.Bodies |> TMap.add (funSerialToBodyId funSerial) bodyDef
      CurrentBodyOpt = None
      Locals = emptyLocals
      Blocks = emptyBlocks }

let private xgStmt (ctx: Ctx) (stmt: HStmt) : Ctx =
  match stmt with
  | HExprStmt expr -> xgExprAsStmt expr ctx
  | HLetValStmt _ -> xgLetValStmt stmt ctx
  | HLetFunStmt _ -> xgLetFunStmt stmt ctx
  | HNativeDeclStmt(embed, args, _) -> todo ()

let private xgDecl (ctx: Ctx) (stmt: HStmt) : Ctx =
  match stmt with
  | HExprStmt expr when hxIsUnitLit expr -> ()

  | HExprStmt expr -> ctx.Trace "// top-level non-fun: {0} {1}" [ exprToLoc expr |> Loc.toString; __dump expr ]

  | HLetValStmt(pat, _, loc) -> ctx.Trace "// top-level let-val: {0} ({1})" [ __dump pat; Loc.toString loc ]

  | HLetFunStmt(_, _, _, loc) -> ctx.Trace "// top-level fun: {0}" [ Loc.toString loc ]
  | HNativeDeclStmt(embed, args, _) -> todo ()

  xgStmt ctx stmt

let private xgModule (ctx: Ctx) (m: HModule2) =
  let ctx = m.Stmts |> List.fold xgDecl ctx

  ctx

let xirGen (trace: TraceFun) (modules: HModule2 list, hirCtx: HirCtx) : XProgram =
  let ctx = ofTyCtx trace hirCtx |> initializeCtx hirCtx

  modules |> List.fold xgModule ctx |> toProgram
