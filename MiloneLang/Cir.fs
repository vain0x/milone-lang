module rec MiloneLang.Cir

open MiloneLang.Types

// -----------------------------------------------
// CIR types
// -----------------------------------------------

type CLabel = string

[<NoEquality; NoComparison>]
type CTyInstance =
  | CTyDeclared
  | CTyDefined

/// Type in C language.
[<NoEquality; NoComparison>]
type CTy =
  | CVoidTy
  | CIntTy
  | CUInt32Ty
  | CCharTy
  | CPtrTy of CTy
  | CFunPtrTy of argTys: CTy list * resultTy: CTy
  | CStructTy of Ident
  | CEnumTy of Ident

/// Unary operators in C language.
[<NoEquality; NoComparison>]
type CUnary =
  /// `!p`
  | CNotUnary

  /// `*p`
  | CDerefUnary

/// Binary operators in C language.
[<NoEquality; NoComparison>]
type CBinary =
  | CMulBinary
  | CDivBinary
  | CModBinary
  | CAddBinary
  | CSubBinary
  | CEqualBinary
  | CNotEqualBinary
  | CLessBinary
  | CLessEqualBinary
  | CGreaterBinary
  | CGreaterEqualBinary

/// Expression in C language.
[<NoEquality; NoComparison>]
type CExpr =
  /// `(struct K){}`
  | CDefaultExpr

  | CIntExpr of int
  | CCharExpr of char

  /// E.g. `"hi"`
  | CStrRawExpr of string

  /// E.g. `(struct String){.str = "hi", .len = 2}`
  | CStrObjExpr of string

  /// Variable.
  | CRefExpr of Ident

  /// `(struct T){.x = x, ..}` Initializer.
  | CInitExpr of fields: (Ident * CExpr) list * CTy

  /// Projection. Field access of tuple.
  | CProjExpr of CExpr * index: int

  /// `(T)x`
  | CCastExpr of CExpr * CTy

  /// `a.x`
  | CNavExpr of CExpr * Ident

  /// `p->x`
  | CArrowExpr of CExpr * Ident

  /// `a[i]`
  | CIndexExpr of CExpr * CExpr

  | CCallExpr of CExpr * args: CExpr list
  | CUnaryExpr of CUnary * CExpr
  | CBinaryExpr of CBinary * CExpr * CExpr

/// Statement in C language.
[<NoEquality; NoComparison>]
type CStmt =
  /// `x;`
  | CExprStmt of CExpr

  /// `T x = a;`
  | CLetStmt of Ident * init: CExpr option * CTy

  /// `U* x = (U*)malloc(sizeof T);`
  | CLetAllocStmt of Ident * valPtrTy: CTy * varTy: CTy

  /// `x = a;`
  | CSetStmt of CExpr * CExpr

  | CLabelStmt of CLabel
  | CGotoStmt of CLabel
  | CGotoIfStmt of CExpr * CLabel
  | CIfStmt of CExpr * CStmt list * CStmt list

  /// clause: (caseLiterals, isDefault, body).
  | CSwitchStmt of cond: CExpr * clauses: (CExpr list * bool * CStmt list) list

  | CReturnStmt of CExpr option

/// Top-level definition in C language.
[<NoEquality; NoComparison>]
type CDecl =
  /// `#error` directive to cause compile error manually.
  | CErrorDecl of message: string * line: int

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

  /// Definition of enum type.
  | CEnumDecl of Ident * variants: Ident list

  /// Definition of global var.
  | CStaticVarDecl of Ident * CTy

  | CFunDecl of Ident * args: (Ident * CTy) list * resultTy: CTy * body: CStmt list
