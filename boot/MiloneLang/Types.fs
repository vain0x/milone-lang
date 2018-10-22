namespace rec MiloneLang

  /// Location = (rowIndex, columnIndex).
  type Loc = int * int

  [<RequireQualifiedAccess>]
  type Token =
    | Unit
    | Int
      of int
    | Str
      of string
    | Ident
      of string
    | Let
    | If
    | Then
    | Else
    /// `(`
    | ParenL
    /// `)`
    | ParenR
    /// `:`
    | Colon
    /// `->`
    | Arrow
    /// Punctuation.
    | Punct
      of string

  /// Type of expressions.
  [<RequireQualifiedAccess>]
  type Ty =
    | Unit
    | Bool
    | Int
    | Str
    | Var
      of string
    | Fun
      of Ty * Ty
    | Tuple
      of Ty * Ty

  [<RequireQualifiedAccess>]
  /// Primitive function.
  type PrimFun =
    | Printfn
    | Fst

  [<RequireQualifiedAccess>]
  type OpLevel =
    | Mul
    | Add
    /// Comparison
    | Cmp
    | And
    | Or
    | Tie

  [<RequireQualifiedAccess>]
  type Op =
    | Mul
    | Div
    | Mod
    | Add
    | Sub
    //// Equal
    | Eq
    /// Not Equal
    | Ne
    /// Less than
    | Lt
    /// Less than or equal to
    | Le
    /// Greater than
    | Gt
    /// Greater than or equal to
    | Ge
    | And
    | Or
    /// Comma to make a tuple
    | Tie

  /// Pattern in AST.
  [<RequireQualifiedAccess>]
  type Pat<'a> =
    | Unit
      of 'a
    | Ident
      of ident:string * serial: int * 'a
    | Tuple
      of Pat<'a> * Pat<'a> * 'a
    | Anno
      of Pat<'a> * Ty * 'a

  /// Expression in AST. `a` is loc, ty, etc.
  [<RequireQualifiedAccess>]
  type Expr<'a> =
    | Unit
      of 'a
    | Bool
      of bool * 'a
    | Int
      of int * 'a
    | Str
      of string * 'a
    /// Primitive.
    | Prim
      of PrimFun * 'a
    /// Variable reference.
    | Ref
      of ident:string * serial:int * 'a
    | If
      of pred:Expr<'a> * thenCl:Expr<'a> * elseCl:Expr<'a> * 'a
    /// `f x y ..`
    | Call
      of Expr<'a> * Expr<'a> list * 'a
    | Op
      of Op * Expr<'a> * Expr<'a> * 'a
    /// Type annotation `x : 'x`.
    | Anno
      of Expr<'a> * Ty * 'a
    /// `x; y`
    | AndThen
      of Expr<'a> list * 'a
    | Let
      of pats:Pat<'a> list * init:Expr<'a> * 'a

  /// Type in middle IR.
  /// These have statically fixed size to be placed on stack.
  [<RequireQualifiedAccess>]
  type MTy =
    | Unit
    | Bool
    | Int
    | Str
    | Fun
      of MTy * MTy
    | Box
      of MBoxTy

  /// Type in middle IR.
  /// This kind of values may have dynamic size, so you can't use directly.
  [<RequireQualifiedAccess>]
  type MBoxTy =
    | Unit
    | Bool
    | Int
    | Str
    | Fun
      of MTy * MTy
    | Tuple
      of MTy * MTy

  [<RequireQualifiedAccess>]
  type MPrim =
    | Printfn
    // Compare two strings.
    | StrCmp

  /// Operator in middle IR.
  [<RequireQualifiedAccess>]
  type MOp =
    | Mul
    | Div
    | Mod
    | Add
    | Sub
    //// Equal
    | Eq
    /// Not Equal
    | Ne
    /// Less than
    | Lt
    /// Less than or equal to
    | Le
    /// Greater than
    | Gt
    /// Greater than or equal to
    | Ge

  /// Expression in middle IR.
  [<RequireQualifiedAccess>]
  type MExpr<'a> =
    | Unit
      of 'a
    | Bool
      of bool * 'a
    | Int
      of int * 'a
    | Str
      of string * 'a
    /// Primitive.
    | Prim
      of MPrim * 'a
    /// Variable reference.
    | Ref
      of serial:int * 'a
    /// Wrap value with box (heap allocated container).
    | Box
      of MExpr<'a> * 'a
    /// Get value from a box.
    | Unbox
      of MExpr<'a> * int * 'a
    | Call
      of callee:MExpr<'a> * args:MExpr<'a> list * 'a
    | Op
      of MOp * left:MExpr<'a> * right:MExpr<'a> * 'a

  /// Statement in middle IR.
  [<RequireQualifiedAccess>]
  type MStmt<'a> =
    /// Expression statement.
    | Expr
      of MExpr<'a> * 'a
    /// Local variable declaration.
    | LetVal
      of serial:int * init:MExpr<'a> option * 'a
    /// Declare box variable and emplace contents.
    | LetBox
      of serial:int * elems:(MExpr<'a> * 'a) list * 'a
    /// Set to local variable.
    | Set
      of serial:int * init:MExpr<'a> * 'a
    | Return
      of MExpr<'a> * 'a
    | If
      of pred:MExpr<'a> * thenCl:MStmt<'a> list * elseCl:MStmt<'a> list * 'a

  /// Declaration in middle IR.
  [<RequireQualifiedAccess>]
  type MDecl<'a> =
    | LetFun
      of callee:int * args:(int * 'a) list * result:MTy * body:MStmt<'a> list * 'a

  /// Variant of union `Box`.
  [<RequireQualifiedAccess>]
  type CBoxTy =
    | Self
    | Int
    | Str
    | Tuple
      of CTy list

  /// Type in C language.
  [<RequireQualifiedAccess>]
  type CTy =
    | Void
    | Int
    | Char
    | Ptr
      of CTy
    /// Union of primitive types. Defined by emitted code.
    | Box
      of CBoxTy

  [<RequireQualifiedAccess>]
  type CPrim =
    | Malloc
    | Printf

  [<RequireQualifiedAccess>]
  type COp = MOp

  /// Expression in C language.
  [<RequireQualifiedAccess>]
  type CExpr =
    | Int
      of int
    | Str
      of string
    | Prim
      of CPrim
    | Ref
      of string * CTy
    /// Wrap with `Box`.
    | Box
      of CExpr * CBoxTy
    /// Get content of `Box`.
    | Unbox
      of CExpr * int * CBoxTy * CTy
    | Cast
      of CExpr * CTy
    | Call
      of CExpr * args:CExpr list * CTy
    | Op
      of COp * CExpr * CExpr * CTy

  /// Statement in C language.
  [<RequireQualifiedAccess>]
  type CStmt =
    /// `x;`
    | Expr
      of CExpr
    /// `T x = a;`
    | Let
      of ident:string * init:CExpr option * CTy
    /// `x = a;`
    | Set
      of CExpr * CExpr * CTy
    /// `Box b = {.t = ..}`
    | LetBox
      of ident:string * int
    /// `((Box)b).t[i] = a;`
    | Emplace
      of CExpr * int * CExpr
    | Return
      of CExpr option
    | If
      of pred:CExpr * thenCl:CStmt list * elseCl:CStmt list

  /// Top-level definition in C language.
  [<RequireQualifiedAccess>]
  type CDecl =
    | Fun
      of ident:string * args:(string * CTy) list * CTy * body:CStmt list
