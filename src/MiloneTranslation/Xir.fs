module rec MiloneTranslation.Xir

open MiloneShared.SharedTypes
open MiloneShared.TypeFloat
open MiloneShared.TypeIntegers
open MiloneStd.StdMap
open MiloneTranslation.Hir

type XBodyId = int
type XBlockId = int
type XLocalId = int
type XPtrTyId = int
type XVariantId = int
type XUnionTyId = int
type XFieldId = int
type XRecordTyId = int
type XFunTyId = int

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
type XRecordDef = { Name: string; Fields: XFieldId list }

type XTy =
  | XUnitTy
  | XIntTy of IntFlavor
  | XStrTy
  | XBoolTy
  | XUnionTy of XUnionTyId
  | XRecordTy of XRecordTyId
  | XFunTy of XFunTyId

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
// terminator
// -----------------------------------------------

let xTerminatorToSuccessors (terminator: XTerminator) : XBlockId list =
  match terminator with
  | XUnreachableTk
  | XExitTk _
  | XReturnTk -> []

  | XJumpTk blockId -> [ blockId ]
  | XIfTk (_, body, alt, _) -> [ body; alt ]
