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

  [<RequireQualifiedAccess>]
  /// Primitive function.
  type PrimFun =
    | Printfn

  [<RequireQualifiedAccess>]
  type OpLevel =
    | Add
    | Mul
    /// Comparison
    | Cmp
    | And
    | Or

  [<RequireQualifiedAccess>]
  type Op =
    | Add
    | Sub
    | Mul
    | Div
    | Mod
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

  /// Pattern in AST.
  [<RequireQualifiedAccess>]
  type Pat<'a> =
    | Unit
      of 'a
    | Ident
      of ident:string * serial: int * 'a
    | Anno
      of Pat<'a> * Ty * 'a

  /// Expression in AST. `a` is loc, ty, etc.
  [<RequireQualifiedAccess>]
  type Expr<'a> =
    | Unit
      of 'a
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

  /// Type in C language.
  [<RequireQualifiedAccess>]
  type CTy =
    | Void
    | Int
    | Char
    | Ptr
      of CTy

  [<RequireQualifiedAccess>]
  type CPrim =
    | Malloc
    | Printf

  [<RequireQualifiedAccess>]
  type COp =
    | Add
    | Sub
    | Mul
    | Div
    | Mod
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

  /// Expression in C language.
  [<RequireQualifiedAccess>]
  type CExpr =
    | Unit
    | Int
      of int
    | Str
      of string
    | Ref
      of string
    | Prim
      of CPrim
    | Call
      of CExpr * args:CExpr list * CTy
    | Op
      of COp * CExpr * CExpr * CTy
    | Set
      of CExpr * CExpr * CTy

  /// Statement in C language.
  [<RequireQualifiedAccess>]
  type CStmt =
    /// `x;`
    | Expr
      of CExpr
    /// `T x = a;`
    | Let
      of name:string * ty:CTy * init:CExpr option
    | Return
      of CExpr option
    | If
      of pred:CExpr * thenCl:CStmt list * elseCl:CStmt list

  /// Function definition in C language.
  [<RequireQualifiedAccess>]
  type CFun =
    {
      Name: string
      Params: (string * CTy) list
      Body: CStmt list
    }

  /// Top-level definition in C language.
  [<RequireQualifiedAccess>]
  type CDecl =
    | Fun
      of CFun
