module rec MiloneTranslation.Xir

open MiloneShared.SharedTypes
open MiloneShared.TypeFloat
open MiloneShared.TypeIntegers
open MiloneShared.Util
open MiloneTranslation.Hir

type XBodyId = int
type XBlockId = int
type XRegId = int
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
  | XRegArg of XRegId * Loc

type XStmt =
  | XAssignStmt of XRegId * XArg * Loc
  | XPrintfnStmt of XArg list * Loc

type XTerminator =
  | XUnreachableTk
  | XExitTk of XArg
  | XReturnTk of XArg
  | XJumpTk of XBlockId
  | XIfTk of XArg * XBlockId * XBlockId * Loc
// | XSwitchTk of XArg * (int * XBlockId) list

type XRegDef =
  { Name: string option
    Id: XRegId
    Ty: XTy
    Loc: Loc }

type XBlockDef =
  { Stmts: XStmt list
    Terminator: XTerminator }

type XBodyDef =
  { Name: string

    ArgTys: XTy list
    ResultTy: XTy

    Regs: AssocMap<XRegId, XRegDef>
    Blocks: AssocMap<XBlockId, XBlockDef>
    EntryBlockId: XBlockId

    Loc: Loc }

type XProgram =
  { Bodies: AssocMap<XBodyId, XBodyDef>
    MainId: XBodyId }
