namespace rec MiloneLang

  [<RequireQualifiedAccess>]
  type Token =
    | Int
      of int
    | Ident
      of string
    | Punct
      of string

  [<RequireQualifiedAccess>]
  type PrimFun =
    | EmitOut

  [<RequireQualifiedAccess>]
  type Expr =
    | Int
      of int
    | Prim
      of PrimFun
    | Call
      of Expr * list<Expr>
    | Add
      of Expr * Expr

  [<RequireQualifiedAccess>]
  type Stmt =
    | FunDecl
      of string * Expr

  [<RequireQualifiedAccess>]
  type Value =
    | Int
      of int
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
