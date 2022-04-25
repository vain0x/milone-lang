/// # Cir
///
/// Defines types and functions for the C language intermediate representation (CIR).
///
/// CIR is conceptually an abstract syntax tree of the C language.
///
/// CIR is generated by `cirGen` from MIR
/// and gets pretty-printed to a string by `cirDump`.
/// C compiler will compile the generated C codes
/// to finally make a milone-lang code executable.
module rec MiloneTranslation.Cir

open MiloneShared.TypeFloat
open MiloneShared.TypeIntegers

type private Ident = string

// -----------------------------------------------
// CIR types
// -----------------------------------------------

type CLabel = string

[<NoEquality; NoComparison>]
type CTyInstance =
  | CTyDeclared
  | CTyDefined

/// Type in CIR.
[<NoEquality; NoComparison>]
type CTy =
  | CVoidTy
  | CIntTy of IntFlavor
  | CFloatTy of FloatFlavor
  | CBoolTy
  | CCharTy
  | CPtrTy of CTy
  | CConstPtrTy of CTy
  | CStructTy of Ident
  | CEnumTy of Ident
  | CEmbedTy of string

/// Unary operators in CIR.
[<NoEquality; NoComparison>]
type CUnary =
  /// `-x`
  | CMinusUnary

  /// `!p`
  | CNotUnary

  /// `&x`
  | CAddressOfUnary

  /// `*p`
  | CDerefUnary

/// Binary operators in CIR.
[<NoEquality; NoComparison>]
type CBinary =
  | CMulBinary
  | CDivBinary
  | CModuloBinary
  | CAddBinary
  | CSubBinary
  | CBitAndBinary
  | CBitOrBinary
  | CBitXorBinary
  | CLeftShiftBinary
  | CRightShiftBinary
  | CEqualBinary
  | CNotEqualBinary
  | CLessBinary
  | CLessEqualBinary
  | CGreaterBinary
  | CGreaterEqualBinary

/// Expression in CIR.
[<NoEquality; NoComparison>]
type CExpr =
  | CIntExpr of text: string * IntFlavor
  | CDoubleExpr of text: string
  | CCharExpr of char

  /// E.g. `"hi"`
  | CStringLitExpr of string

  /// E.g. `(struct String){.ptr = "hi", .len = 2}`
  | CStringInitExpr of string

  /// Variable.
  | CVarExpr of Ident

  /// `(struct T){.x = x, ..}` Initializer.
  | CInitExpr of fields: (Ident * CExpr) list * CTy

  /// `(T)x`
  | CCastExpr of CExpr * CTy

  /// `a.x`
  | CDotExpr of CExpr * Ident

  /// `p->x`
  | CArrowExpr of CExpr * Ident

  /// `a[i]`
  | CIndexExpr of CExpr * CExpr

  | CCallExpr of CExpr * args: CExpr list
  | CSizeOfExpr of CTy
  | CTyPlaceholderExpr of CTy
  | CUnaryExpr of CUnary * CExpr
  | CBinaryExpr of CBinary * CExpr * CExpr
  | CNativeExpr of string * CExpr list

/// Statement in CIR.
[<NoEquality; NoComparison>]
type CStmt =
  /// `x;`
  | CExprStmt of CExpr

  /// `T x = a;`
  | CLetStmt of Ident * init: CExpr option * CTy

  /// `x = a;`
  | CSetStmt of CExpr * CExpr

  | CLabelStmt of CLabel
  | CGotoStmt of CLabel
  | CGotoIfStmt of CExpr * CLabel
  | CIfStmt of CExpr * CStmt * CStmt
  /// `if (cond) stmt;`
  | CIfStmt1 of CExpr * CStmt

  /// clause: (caseLiterals, isDefault, body).
  | CSwitchStmt of cond: CExpr * clauses: (CExpr list * bool * CStmt) list

  | CReturnStmt of CExpr option
  | CNativeStmt of string * args: CExpr list

/// Directive or definition in CIR.
[<NoEquality; NoComparison>]
type CDecl =
  /// `#error` directive to cause compile error manually.
  | CErrorDecl of message: string * line: int

  /// `typedef ResultTy (*Ident)(ArgTy1, ArgTy2, ..);`
  | CFunPtrTyDef of Ident * argTys: CTy list * resultTy: CTy

  /// Definition of struct type including anonymous union.
  /// ```c
  /// struct K {
  ///   fields...;
  ///
  ///   union {  // Omit if no variants.
  ///     variants...;
  ///   };
  /// };
  /// ```
  | CStructDecl of Ident * fields: (Ident * CTy) list * variants: (Ident * CTy) list

  | CStructForwardDecl of Ident

  /// Definition of enum type.
  | CEnumDecl of Ident * variants: Ident list

  /// Definition of global var.
  | CStaticVarDecl of Ident * CTy
  | CInternalStaticVarDecl of Ident * CTy
  | CExternVarDecl of Ident * CTy

  | CFunForwardDecl of Ident * argTys: CTy list * resultTy: CTy

  | CFunDecl of Ident * args: (Ident * CTy) list * resultTy: CTy * body: CStmt list

  | CStaticFunDecl of Ident * args: (Ident * CTy) list * resultTy: CTy * body: CStmt list

  | CNativeDecl of string
