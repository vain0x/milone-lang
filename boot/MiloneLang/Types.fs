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
  /// Primitive functions.
  type PrimFun =
    | EmitOut
    | Printfn

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

  [<RequireQualifiedAccess>]
  type Stmt =
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
