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
    // Punctuation.
    | Punct
      of string

  /// Syntax tree.
  [<RequireQualifiedAccess>]
  type Syn =
    | Unit
    | Int
      of int
    | String
      of string
    | Ident
      of string
    | Term
      of Syn list
    | Expr
      of Syn list
    /// Operator.
    | Op
      of punct:string
    | Let
      of pat:Syn list * body:Syn

  [<RequireQualifiedAccess>]
  /// Primitive function.
  type PrimFun =
    | EmitOut
    | Printfn

  /// Expression.
  [<RequireQualifiedAccess>]
  type Expr =
    | Unit
    | Int
      of int
    | String
      of string
    /// Primitive.
    | Prim
      of PrimFun
    /// Variable reference.
    | Ref
      of string
    | Call
      of Expr * list<Expr>
    | Add
      of Expr * Expr
    /// x; y; z
    | Begin
      of Expr list

  /// Statement.
  [<RequireQualifiedAccess>]
  type Stmt =
    /// Function declaration.
    | FunDecl
      of string * Expr

  [<RequireQualifiedAccess>]
  type Value =
    | Unit
    | Int
      of int
    | String
      of string
    | PrimFun
      of PrimFun

  /// Destination channel of outputs.
  type Dest =
    | StdOut
    | StdErr

  [<RequireQualifiedAccess>]
  type ProcessOutput =
    {
      Outs: list<Dest * string>
      Code: int
    }

  [<RequireQualifiedAccess>]
  type EvalContext =
    {
      Outs: list<Dest * string>
    }

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
