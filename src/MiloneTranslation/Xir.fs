module rec MiloneTranslation.Xir

open MiloneShared.SharedTypes
open MiloneShared.TypeFloat
open MiloneShared.TypeIntegers
open MiloneShared.Util
open MiloneTranslation.Hir

type XBodyId = int
type XBlockId = int
type XLocalId = int
type XPtrTyId = int
// type XVariantId = int
type XUnionTyId = int
type XRecordTyId = int
type XFunTyId = int

type XTy =
  | XUnitTy
  | XIntTy of IntFlavor
  | XStrTy
  | XBoolTy
  // | XUnionTy of XUnionTyId
  // | XRecordTy of XRecordTyId
  | XFunTy of XFunTyId
// | XGenericTy of index: int

type XArg =
  | XUnitArg of Loc
  | XLitArg of Lit * Loc
  // | XDiscriminantArg of XVariantId
  | XLocalArg of XLocalId * Loc

type XUnary =
  | XMinusUnary
  | XNotUnary

type XBinary =
  | XAddBinary
  | XStrAddBinary

type XRval =
  // extends XArgs
  | XLitRval of Lit * Loc
  | XUnitRval of Loc
  | XLocalRval of XLocalId * Loc

  | XUnaryRval of XUnary * XArg * Loc
  | XBinaryRval of XBinary * XArg * XArg * Loc

type XStmt =
  | XAssignStmt of XLocalId * XArg * Loc
  | XPrintfnStmt of XArg list * Loc
  | XPtrWriteStmt of XArg * XArg * Loc

type XTerminator =
  | XUnreachableTk
  | XExitTk of XArg * Loc
  | XReturnTk of XArg
  | XJumpTk of XBlockId
  | XIfTk of XArg * XBlockId * XBlockId * Loc
// | XSwitchTk of XArg * (int * XBlockId) list

type XLocalDef =
  { Name: string option
    Id: XLocalId
    Ty: XTy
    Loc: Loc }

type XBlockDef =
  { Stmts: XStmt list
    Terminator: XTerminator }

type XBodyDef =
  { Name: string

    ArgTys: XTy list
    ResultTy: XTy

    Locals: AssocMap<XLocalId, XLocalDef>
    Blocks: AssocMap<XBlockId, XBlockDef>
    EntryBlockId: XBlockId

    Loc: Loc }

type XProgram =
  { Bodies: AssocMap<XBodyId, XBodyDef>
    MainId: XBodyId }
