namespace rec MiloneLang

  /// Location = (rowIndex, columnIndex).
  type Loc = int * int

  [<RequireQualifiedAccess>]
  type Token =
    | Unit
    | Int
      of int
    | String
      of string
    | Ident
      of string
    | Let
    | If
    | Then
    | Else
    | ParenL
    | ParenR
    // Punctuation.
    | Punct
      of string

  /// Type of expressions.
  [<RequireQualifiedAccess>]
  type Ty =
    | Unit
    | Bool
    | Int
    | Str
    | Fun
      of Ty * Ty
    | Var
      of string

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
      of name:string * serial: int * 'a

  /// Expression in AST.
  [<RequireQualifiedAccess>]
  type Expr<'a> =
    | Unit
      of 'a
    | Int
      of int * 'a
    | String
      of string * 'a
    /// Primitive.
    | Prim
      of PrimFun * 'a
    /// Variable reference.
    | Ref
      of ident:string * serial:int * 'a
    | If
      of pred:Expr<'a> * thenCl:Expr<'a> * elseCl:Expr<'a> * 'a
    | Call
      of Expr<'a> * Expr<'a> list * 'a
    | Op
      of Op * Expr<'a> * Expr<'a> * 'a
    | Let
      of pats:Pat<'a> list * init:Expr<'a> * 'a
    /// x; y; z
    | Begin
      of Expr<'a> list * 'a

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
    | Op
      of COp * CExpr * CExpr
    | Prim
      of CPrim
    | Call
      of CExpr * args:CExpr list
    | Set
      of CExpr * CExpr

  /// Statement in C language.
  [<RequireQualifiedAccess>]
  type CStmt =
    | Expr
      of CExpr
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
      Body: CStmt list
    }

  /// Top-level definition in C language.
  [<RequireQualifiedAccess>]
  type CDecl =
    | Fun
      of CFun
