module rec MiloneTranslation.XirReuse

open MiloneShared.SharedTypes
open MiloneShared.TypeFloat
open MiloneShared.TypeIntegers
open MiloneShared.Util
open MiloneTranslation.Xir

module S = MiloneStd.StdString
module TMap = MiloneStd.StdMap
module TSet = MiloneStd.StdSet

let private listContains (x: int) (xs: int list) = xs |> List.exists (fun y -> x = y)

// -----------------------------------------------
// XIR helpers
// -----------------------------------------------

let private xtEncode (ty: XTy) : int =
  let pair (l: int) (r: int) =
    assert (l < 30 && r < 10000000)
    l * 10000000 + r

  let just (x: int) = pair x 0

  match ty with
  | XUnitTy -> just 1
  | XIntTy flavor -> pair 2 (intFlavorToOrdinary flavor)
  | XStrTy -> just 2
  | XBoolTy -> just 3
  | XUnionTy id -> pair 4 id
  | XRecordTy id -> pair 5 id
  | XFunTy id -> pair 6 id

let xtCompare (l: XTy) (r: XTy) : int = compare (xtEncode l) (xtEncode r)

let xtEqual (l: XTy) (r: XTy) : bool = xtCompare l r = 0

let private xArgToUse (arg: XArg) : XLocalId list =
  match arg with
  | XLitArg _
  | XUnitArg _
  | XDiscriminantArg _ -> []

  | XLocalArg (local, _) -> [ local ]

let private xRvalToUse (rval: XRval) : XLocalId list =
  match rval with
  | XLitRval _
  | XUnitRval _
  | XDiscriminantRval _ -> []

  | XLocalRval (local, _) -> [ local ]
  | XPlaceRval (place, _) -> [ place.Local ]

  | XUnaryRval (_, arg, _) -> xArgToUse arg
  | XBinaryRval (_, l, r, _) -> List.append (xArgToUse l) (xArgToUse r)
  | XAggregateRval (_, args, _) -> List.collect xArgToUse args

let private xStmtToDef (stmt: XStmt) : XLocalId list =
  match stmt with
  | XAssignStmt (place, _, _) -> [ place.Local ]
  | XCallStmt (_, _, place, _) -> [ place.Local ]

  | XPrintfnStmt _
  | XPtrWriteStmt _ -> []

let private xStmtToUse (stmt: XStmt) : XLocalId list =
  match stmt with
  | XAssignStmt (place, _, _) -> [ place.Local ]
  | XCallStmt (_, _, place, _) -> [ place.Local ]

  | XPrintfnStmt _
  | XPtrWriteStmt _ -> []

let private xTerminatorToUse (terminator: XTerminator) : XLocalId list =
  match terminator with
  | XUnreachableTk
  | XExitTk _
  | XReturnTk
  | XJumpTk _ -> []

  | XIfTk (arg, _, _, _) -> xArgToUse arg

let private xTerminatorToSuccessors (terminator: XTerminator) : XBlockId list =
  match terminator with
  | XUnreachableTk
  | XExitTk _
  | XReturnTk -> []

  | XJumpTk blockId -> [ blockId ]
  | XIfTk (_, body, alt, _) -> [ body; alt ]

type private Rewriter =
  { OnLocal: XLocalId -> XLocalId
    OnPlace: XPlace -> XPlace
    OnArg: XArg -> XArg
    OnRval: XRval -> XRval }

let private newRewriterOfLocalMapper onLocal : Rewriter =
  let onPlace =
    fun (place: XPlace) ->
      { place with
          Local = onLocal place.Local }

  let onArg =
    fun arg ->
      match arg with
      | XUnitArg _
      | XLitArg _
      | XDiscriminantArg _ -> arg

      | XLocalArg (local, loc) -> XLocalArg(onLocal local, loc)

  let onRval rval =
    match rval with
    | XLitRval _
    | XUnitRval _
    | XDiscriminantRval _ -> rval

    | XLocalRval (local, loc) -> XLocalRval(onLocal local, loc)
    | XPlaceRval (place, loc) -> XPlaceRval(onPlace place, loc)
    | XUnaryRval (unary, arg, loc) -> XUnaryRval(unary, onArg arg, loc)
    | XBinaryRval (binary, l, r, loc) -> XBinaryRval(binary, onArg l, onArg r, loc)
    | XAggregateRval (kind, args, loc) -> XAggregateRval(kind, List.map onArg args, loc)

  { OnLocal = onLocal
    OnPlace = onPlace
    OnArg = onArg
    OnRval = onRval }

let private xStmtMap (rewriter: Rewriter) (stmt: XStmt) : XStmt =
  match stmt with
  | XAssignStmt (place, rval, loc) -> XAssignStmt(rewriter.OnPlace place, rewriter.OnRval rval, loc)

  | XCallStmt (body, args, result, loc) -> XCallStmt(body, List.map rewriter.OnArg args, rewriter.OnPlace result, loc)

  | XPrintfnStmt (args, loc) -> XPrintfnStmt(List.map rewriter.OnArg args, loc)

  | XPtrWriteStmt (l, r, loc) -> XPtrWriteStmt(rewriter.OnArg l, rewriter.OnArg r, loc)

let private xTerminatorMap (rewriter: Rewriter) (terminator: XTerminator) : XTerminator =
  match terminator with
  | XUnreachableTk
  | XReturnTk
  | XJumpTk _ -> terminator

  | XExitTk arg -> XExitTk(rewriter.OnArg arg)
  | XIfTk (arg, body, alt, loc) -> XIfTk(rewriter.OnArg arg, body, alt, loc)

// -----------------------------------------------
// Context
// -----------------------------------------------

type private Ctx =
  { Blocks: AssocMap<XBlockId, XBlockDef>
    EntryBlock: XBlockId
    ResultLocal: XLocalId

    CurrentLocal: XLocalId

    /// Successors of each block.
    /// (For each entry `b, [s]`, s may jump to b.)
    SuccessorMap: AssocMap<XBlockId, XBlockId list>

    LiveIn: AssocSet<XBlockId * XLocalId>
    LiveOut: AssocSet<XBlockId * XLocalId>
    SomethingHappened: bool }

let private ctxOfBodyDef (bodyDef: XBodyDef) : Ctx = todo ()

let private successors blockId ctx = ctx.SuccessorMap |> mapFind blockId

let private isLiveIn blockId localId (ctx: Ctx) =
  ctx.LiveIn |> TSet.contains (blockId, localId)

let private isLiveOut blockId localId (ctx: Ctx) =
  ctx.LiveOut |> TSet.contains (blockId, localId)

let private takeSomethingHappened (ctx: Ctx) : bool * Ctx =
  ctx.SomethingHappened, { ctx with SomethingHappened = false }

let private markAsSomethingHappened (ctx: Ctx) : Ctx =
  if ctx.SomethingHappened then
    ctx
  else
    { ctx with SomethingHappened = true }

let private markAsLiveInAll blockId localIds (ctx: Ctx) =
  { ctx with
      LiveIn =
        ctx.LiveIn
        |> forList TSet.add (localIds |> List.map (fun local -> blockId, local))

      SomethingHappened = true }

let private markAsLiveInOut blockId localId liveIn liveOut (ctx: Ctx) =
  let pair = blockId, localId

  let getLiveIn =
    liveIn
    && (ctx.LiveIn |> TSet.contains pair |> not)

  let getLiveOut =
    liveOut
    && (ctx.LiveOut |> TSet.contains pair |> not)

  if getLiveIn || getLiveOut then
    { ctx with
        LiveIn =
          if getLiveIn then
            ctx.LiveIn |> TSet.add pair
          else
            ctx.LiveIn

        LiveOut =
          if getLiveOut then
            ctx.LiveOut |> TSet.add pair
          else
            ctx.LiveOut

        SomethingHappened = true }
  else
    ctx

let private xrBlock (blockId: XBlockId) (ctx: Ctx) : Ctx =
  let blockDef = ctx.Blocks |> mapFind blockId
  let local = ctx.CurrentLocal

  let liveOut =
    let isLiveOutAsResultLocal () =
      match blockDef.Terminator with
      | XReturnTk -> ctx.ResultLocal = local
      | _ -> false

    isLiveOut blockId local ctx
    || xTerminatorToSuccessors blockDef.Terminator
       |> List.exists (fun b -> isLiveIn b local ctx)
    || isLiveOutAsResultLocal ()

  let liveIn =
    let isDefined () =
      blockDef.Stmts
      |> List.exists (fun stmt -> xStmtToDef stmt |> listContains local)

    isLiveIn blockId local ctx
    || (liveOut && not (isDefined ()))

  markAsLiveInOut blockId local liveIn liveOut ctx

let private xrBody (bodyDef: XBodyDef) : XBodyDef =
  let ctx = ctxOfBodyDef bodyDef

  let ctx =
    markAsLiveInAll bodyDef.EntryBlockId (bodyDef.Locals |> TMap.toKeys) ctx

  // FIXME: topological sort
  let blocks = bodyDef.Blocks |> TMap.toKeys

  let rec go (ctx: Ctx) =
    let ctx =
      bodyDef.Locals
      |> TMap.fold
           (fun (ctx: Ctx) localId _ ->
             let ctx = { ctx with CurrentLocal = localId }
             ctx |> forList xrBlock blocks)
           ctx

    let happened, ctx = takeSomethingHappened ctx
    if happened then go ctx else ctx

  let ctx = go ctx
  // TODO: when a local is defined, try to pick another local of the same type whose lifetime is disjoint, and (if any) replace it with the other.

  bodyDef

// ===============================================

let xirReuse (program: XProgram) : XProgram =
  let bodies =
    program.Bodies
    |> TMap.map (fun (_: XBodyId) bodyDef -> xrBody bodyDef)

  { program with Bodies = bodies }
