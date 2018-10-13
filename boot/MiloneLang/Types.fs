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
  type Pattern =
    | Unit
    | Ident
      of string

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
      of ident:string * 'a
    | Call
      of Expr<'a> * Expr<'a> list * 'a
    | Add
      of Expr<'a> * Expr<'a> * 'a
    | Let
      of ident:string * init:Expr<'a> * 'a
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
    | Add
      of CExpr * CExpr
    | Prim
      of CPrim
    | Call
      of CExpr * args:CExpr list

  /// Statement in C language.
  [<RequireQualifiedAccess>]
  type CStmt =
    | Expr
      of CExpr
    | Let
      of name:string * ty:CTy * init:CExpr
    | Return
      of CExpr option

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
