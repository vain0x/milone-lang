module rec MiloneTranslation.XirToCir

open MiloneShared.TypeIntegers
open MiloneShared.SharedTypes
open MiloneShared.Util
open MiloneStd.StdMap
open MiloneStd.StdMultimap
open MiloneStd.StdSet
open MiloneTranslation.Cir
open MiloneTranslation.Xir

module S = MiloneStd.StdString

type private TraceFun = string -> string list -> unit

let private cInt = CIntTy(IntFlavor(Signed, I32))

let private cUnitExpr: CExpr =
  CIntExpr("/*unit*/0", IntFlavor(Signed, I32))

let private cZeroExpr: CExpr = CIntExpr("0", IntFlavor(Signed, I32))

let private cIntExpr (n: int) =
  CIntExpr(string n, IntFlavor(Signed, I32))

let private cIntCompareFun = CVarExpr "int_compare"
let private cStrAddFun = CVarExpr "str_add"
let private cStrCompareFun = CVarExpr "str_compare"
let private cStrSliceFun = CVarExpr "str_slice"
let private cUnreachableFun = CVarExpr "/*unreachable*/abort"
let private cExitFun = CVarExpr "exit"
let private cAssertFun = CVarExpr "milone_assert"

let private cLabelOf (blockId: XBlockId) : CLabel = "L" + string blockId

let private cLocStmt (loc: Loc) =
  CNativeStmt("    // loc: " + Loc.toString loc + "\n", [])

// -----------------------------------------------
// Context
// -----------------------------------------------

// Read context.
type private Rx = { BodyDef: XBodyDef; Trace: TraceFun }

// Write context.
type private Wx =
  { Stmts: CStmt list
    Decls: CDecl list }

let private newRx trace (bodyDef: XBodyDef) : Rx = { BodyDef = bodyDef; Trace = trace }

let private newWx () : Wx = { Stmts = []; Decls = [] }

let private addStmt stmt (wx: Wx) = { wx with Stmts = stmt :: wx.Stmts }
let private addDecl decl (wx: Wx) = { wx with Decls = decl :: wx.Decls }

// #genLit
let private xcLit lit : CExpr =
  match lit with
  | IntLit text -> CIntExpr(text, IntFlavor(Signed, I32))
  | IntLitWithFlavor (text, flavor) -> CIntExpr(text, flavor)
  | FloatLit text -> CDoubleExpr text
  | BoolLit false -> CVarExpr "false"
  | BoolLit true -> CVarExpr "true"
  | CharLit value -> CCharExpr value
  | StrLit value -> CStrObjExpr value

let private xcDiscriminantConst variantId = todo ()
let private xcLocal (localId: XLocalId) = CVarExpr("l" + string localId) // FIXME: impl

let private xcPlace (place: XPlace) =
  let rec go l path =
    match path with
    | [] -> l
    | part :: path ->
      let l =
        match part with
        | XPart.Deref -> CUnaryExpr(CDerefUnary, l)
        | XPart.Discriminant -> CDotExpr(l, "discriminant")
        | XPart.Field index -> CDotExpr(l, "t" + string index)
        | XPart.Payload variantId -> todo ()

      go l path

  go (xcLocal place.Local) place.Path

let private xcArg (arg: XArg) =
  match arg with
  | XLitArg (lit, _) -> xcLit lit
  | XUnitArg _ -> cUnitExpr
  | XDiscriminantArg (variantId, _) -> xcDiscriminantConst variantId
  | XLocalArg (localId, _) -> xcLocal localId

let private xcRval (rval: XRval) =
  match rval with
  | XLitRval (lit, _) -> xcLit lit
  | XUnitRval _ -> cUnitExpr
  | XDiscriminantRval (variantId, _) -> xcDiscriminantConst variantId
  | XLocalRval (localId, _) -> xcLocal localId

  | XPlaceRval (place, _) -> xcPlace place

  | XUnaryRval (unary, xArg, _) ->
    let cArg = xcArg xArg

    match unary with
    | XMinusUnary -> CUnaryExpr(CMinusUnary, cArg)
    | XNotUnary -> CUnaryExpr(CNotUnary, cArg)
    | XStrLengthUnary -> CDotExpr(cArg, "len")

  | XBinaryRval (binary, l, r, _) ->
    let l = xcArg l
    let r = xcArg r

    match binary with
    | XScalarAddBinary
    | XPtrAddBinary -> CBinaryExpr(CAddBinary, l, r)
    | XStrAddBinary -> CCallExpr(cStrAddFun, [ l; r ])

    | XScalarSubBinary -> CBinaryExpr(CSubBinary, l, r)
    | XScalarMulBinary -> CBinaryExpr(CMulBinary, l, r)
    | XScalarDivBinary -> CBinaryExpr(CDivBinary, l, r)
    | XScalarModuloBinary -> CBinaryExpr(CModuloBinary, l, r)

    | XScalarEqualBinary -> CBinaryExpr(CEqualBinary, l, r)
    | XStrEqualBinary -> CUnaryExpr(CNotUnary, CCallExpr(cStrCompareFun, [ l; r ]))
    | XScalarLessBinary -> CBinaryExpr(CLessBinary, l, r)
    | XStrLessBinary -> CBinaryExpr(CLessBinary, CCallExpr(cStrCompareFun, [ l; r ]), cZeroExpr)
    | XScalarCompareBinary -> CCallExpr(cIntCompareFun, [ l; r ]) // FIXME: flavor, float compare etc.
    | XStrCompareBinary -> CCallExpr(cStrCompareFun, [ l; r ])
    | XStrIndexBinary -> CIndexExpr(CDotExpr(l, "str"), r)

  | XNodeRval (kind, args, _) ->
    let args = args |> List.map xcArg

    match kind, args with
    | XRvalKind.StrSlice, [ l; r; s ] -> CCallExpr(cStrSliceFun, [ l; r; s ])
    | XRvalKind.StrSlice, _ -> unreachable ()

  | XAggregateRval (kind, args, _) ->
    match kind, args with
    | XVariantAk variantId, [ payload ] -> todo () // (struct K){.d = d, .payload = arg}
    | XVariantAk _, _ -> unreachable ()

    | XRecordAk recordId, _ -> todo () // (struct K){.t0 = a0, ...}

let private xcStmt (wx: Wx) stmt : Wx =
  match stmt with
  | XAssignStmt (place, rval, _) -> addStmt (CSetStmt(xcPlace place, xcRval rval)) wx

  | XCallStmt (bodyId, args, result, _) ->
    let callee = CVarExpr("body_" + string bodyId) // FIXME: bodyId to function name
    let args = args |> List.map xcArg

    wx
    |> addStmt (CSetStmt(xcPlace result, CCallExpr(callee, args)))

  | XNativeCallStmt (_, args, result, _) ->
    // FIXME: funSerial to fun name
    let callee = CVarExpr "__nativeFun__"
    let args = args |> List.map xcArg

    wx
    |> addStmt (CSetStmt(xcPlace result, CCallExpr(callee, args)))

  | XAssertStmt (arg, loc) ->
    let (Loc (docId, y, x)) = loc

    let args =
      [ xcArg arg
        CStrRawExpr docId
        cIntExpr y
        cIntExpr x ]

    wx
    |> addStmt (CExprStmt(CCallExpr(cAssertFun, args)))

  | XInRegionStmt (_, _) -> todo ()

  | XPrintfnStmt (args, _) ->
    // FIXME: convert string to char *
    wx
    |> addStmt (CExprStmt(CCallExpr(CVarExpr "printf", args |> List.map xcArg)))

let private xcTerminator (wx: Wx) (terminator: XTerminator) : Wx =
  match terminator with
  | XExitTk arg ->
    wx
    |> addStmt (CExprStmt(CCallExpr(cExitFun, [ xcArg arg ])))

  | XUnreachableTk ->
    wx
    |> addStmt (CExprStmt(CCallExpr(cUnreachableFun, [])))

  | XReturnTk ->
    // FIXME: return ResultLocal unless void
    wx |> addStmt (CReturnStmt None)

  | XJumpTk blockId -> wx |> addStmt (CGotoStmt(cLabelOf blockId))

  | XIfTk (cond, body, alt, _) ->
    let body = cLabelOf body
    let alt = cLabelOf alt

    wx
    |> addStmt (CIfStmt(xcArg cond, [ CGotoStmt body ], [ CGotoStmt alt ]))

let private xcBlock (wx: Wx) (blockId: XBlockId) (blockDef: XBlockDef) : Wx =
  // emit C label
  let wx =
    addStmt (CLabelStmt(cLabelOf blockId)) wx

  let wx = blockDef.Stmts |> List.fold xcStmt wx
  xcTerminator wx blockDef.Terminator

let private xcBody (rx: Rx) (wx: Wx) : Wx =
  let rec go doneSet blockId (wx: Wx) : Wx * _ =
    if doneSet |> TSet.contains blockId then
      wx, doneSet
    else
      let doneSet = doneSet |> TSet.add blockId
      let blockDef = rx.BodyDef.Blocks |> mapFind blockId

      // FIXME: declare locals
      // FIXME: compute blockId-label relations
      let wx = xcBlock wx blockId blockDef

      xTerminatorToSuccessors blockDef.Terminator
      |> List.fold (fun (wx, doneSet) blockId -> go doneSet blockId wx) (wx, doneSet)

  assert (List.isEmpty wx.Stmts)

  // Generate body.
  let wx =
    let wx = wx |> addStmt (cLocStmt rx.BodyDef.Loc)

    go (TSet.empty compare) rx.BodyDef.EntryBlockId wx
    |> fst

  // Emit decl.
  let wx =
    let stmts, wx =
      List.rev wx.Stmts, { wx with Stmts = [] }

    let funDecl =
      CFunDecl(rx.BodyDef.Name, [], CVoidTy, stmts)

    addDecl funDecl wx

  wx

// ===============================================

let private locToDoc (loc: Loc) : DocId =
  let (Loc (doc, _, _)) = loc
  doc

let private splitByDoc (program: XProgram) : (DocId * (XBodyId * XBodyDef) list) list =
  program.Bodies
  |> TMap.fold
       (fun map bodyId (bodyDef: XBodyDef) ->
         let docId, _ = Loc.toDocPos bodyDef.Loc
         map |> Multimap.add docId (bodyId, bodyDef))
       (TMap.empty compare)
  |> TMap.toList

let xirToCir (trace: TraceFun) (program: XProgram) : (DocId * CDecl list) list =
  program
  |> splitByDoc
  |> List.map (fun (docId, bodiesRev) ->
    let wx = newWx ()

    let wx =
      bodiesRev
      |> List.rev
      |> List.fold
           (fun wx (_bodyId, bodyDef) ->
             let rx = newRx trace bodyDef
             xcBody rx wx)
           wx

    assert (List.isEmpty wx.Stmts)
    docId, List.rev wx.Decls)
