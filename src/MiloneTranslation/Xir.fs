module rec MiloneTranslation.Xir

open MiloneShared.SharedTypes
open MiloneShared.TypeFloat
open MiloneShared.TypeIntegers
open MiloneStd.StdMap
open MiloneTranslation.Hir

type XBodyId = int
type XBlockId = int
type XLocalId = int
type XFunTyId = int
type XListTyId = int
type XNativePtrTyId = int
type XNativeFunTyId = int
type XNativeEmbedTy = int
type XVariantId = int
type XUnionTyId = int
type XRecordTyId = int

/// (record, index)
type XFieldId = XRecordTyId * int

type XVariantDef =
  { Name: string
    HasPayload: bool
    PayloadTy: XTy
    IsNewtype: bool }

// type XUnionCause =
//   | XOptionUc
//   | XListUc

[<RequireQualifiedAccess>]
type XUnionDef =
  { Name: string
    Variants: XVariantId list }

// type XRecordCause =
//   | XTupleRc
//   | XUserRc

[<RequireQualifiedAccess>]
type XRecordDef =
  { Name: string
    Fields: (string * XTy) list }

type XTy =
  | XIntTy of IntFlavor
  | XFloatTy of FloatFlavor
  | XUnitTy
  | XBoolTy
  | XCharTy
  | XStrTy
  | XUnionTy of XUnionTyId
  | XRecordTy of XRecordTyId

  | XFunTy of XFunTyId
  | XListTy of XListTyId

  // FFI types.
  | XVoidPtrTy of IsMut
  | XNativePtrTy of IsMut * XNativePtrTyId
  | XNativeFunTy of XNativeFunTyId
  | XNativeEmbedTy of XNativeEmbedTy

[<RequireQualifiedAccess>]
type XPart =
  | Deref
  | Discriminant
  | Field of index: int
  | Payload of XVariantId

[<RequireQualifiedAccess>]
type XPlace = { Local: XLocalId; Path: XPart list }

type XArg =
  | XUnitArg of Loc
  | XLitArg of Lit * Loc
  | XDiscriminantArg of XVariantId * Loc
  | XLocalArg of XLocalId * Loc

type XUnary =
  | XMinusUnary
  | XNotUnary
  | XStrLengthUnary

type XBinary =
  | XScalarAddBinary
  | XStrAddBinary
  | XPtrAddBinary
  | XScalarSubBinary
  | XScalarMulBinary
  | XScalarDivBinary
  | XScalarModuloBinary
  | XScalarEqualBinary
  | XStrEqualBinary
  | XScalarLessBinary
  | XStrLessBinary
  | XScalarCompareBinary
  | XStrCompareBinary

  | XStrIndexBinary

[<RequireQualifiedAccess>]
type XRvalKind = | StrSlice

type XAggregateKind =
  | XVariantAk of XVariantId
  | XRecordAk of XRecordTyId

type XRval =
  // extends XArg
  | XLitRval of Lit * Loc
  | XUnitRval of Loc
  | XDiscriminantRval of XVariantId * Loc
  | XLocalRval of XLocalId * Loc
  | XPlaceRval of XPlace * Loc

  | XUnaryRval of XUnary * XArg * Loc
  | XBinaryRval of XBinary * XArg * XArg * Loc
  | XNodeRval of XRvalKind * XArg list * Loc
  | XAggregateRval of XAggregateKind * XArg list * Loc

type XStmt =
  | XAssignStmt of XPlace * XRval * Loc
  | XCallStmt of XBodyId * XArg list * XPlace * Loc
  | XNativeCallStmt of FunSerial * XArg list * XPlace * Loc
  | XAssertStmt of XArg * Loc
  | XInRegionStmt of XArg * Loc
  | XPrintfnStmt of XArg list * Loc

type XTerminator =
  | XUnreachableTk
  | XExitTk of XArg
  | XReturnTk
  | XJumpTk of XBlockId
  | XIfTk of XArg * XBlockId * XBlockId * Loc
// | XSwitchTk of XArg * (int * XBlockId) list

[<RequireQualifiedAccess>]
type XLocalDef =
  { Name: string option
    Id: XLocalId
    Arg: bool
    Ty: XTy
    Loc: Loc }

[<RequireQualifiedAccess>]
type XBlockDef =
  { Stmts: XStmt list
    Terminator: XTerminator }

[<RequireQualifiedAccess>]
type XBodyDef =
  { Name: string

    ArgTys: XTy list
    ResultTy: XTy

    Locals: TreeMap<XLocalId, XLocalDef>
    ArgLocals: XLocalId list
    ResultLocal: XLocalId
    Blocks: TreeMap<XBlockId, XBlockDef>
    EntryBlockId: XBlockId

    Loc: Loc }

[<RequireQualifiedAccess>]
type XProgram =
  { Bodies: TreeMap<XBodyId, XBodyDef>
    MainId: XBodyId }

// -----------------------------------------------
// ty
// -----------------------------------------------

let private compareInt (l: int) r = compare l r

module XTy =
  let toOrder ty =
    let ofPair (x: int) (y: int) = (x <<< 25) ||| y
    let ofSingle x = ofPair x 0

    match ty with
    | XIntTy flavor -> ofPair 1 (intFlavorToOrdinary flavor)
    | XFloatTy flavor -> ofPair 2 (floatFlavorToOrdinary flavor)
    | XUnitTy -> ofSingle 3
    | XBoolTy -> ofSingle 4
    | XCharTy -> ofSingle 5
    | XStrTy -> ofSingle 6

    | XUnionTy unionTyId -> ofPair 11 unionTyId
    | XRecordTy recordTyId -> ofPair 12 recordTyId
    | XFunTy funTyId -> ofPair 13 funTyId
    | XListTy listTyId -> ofPair 14 listTyId

    | XVoidPtrTy IsMut -> ofSingle 21
    | XVoidPtrTy IsConst -> ofSingle 22
    | XNativePtrTy (IsMut, nativePtrTyId) -> ofPair 23 nativePtrTyId
    | XNativePtrTy (IsConst, nativePtrTyId) -> ofPair 24 nativePtrTyId
    | XNativeFunTy nativeFunTyId -> ofPair 25 nativeFunTyId
    | XNativeEmbedTy nativeEmbedTyId -> ofPair 26 nativeEmbedTyId

  let compare l r = compareInt (toOrder l) (toOrder r)

// -----------------------------------------------
// terminator
// -----------------------------------------------

let xTerminatorToSuccessors (terminator: XTerminator) : XBlockId list =
  match terminator with
  | XUnreachableTk
  | XExitTk _
  | XReturnTk -> []

  | XJumpTk blockId -> [ blockId ]
  | XIfTk (_, body, alt, _) -> [ body; alt ]
