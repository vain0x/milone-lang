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
    | Match
    | With
    /// `(`
    | ParenL
    /// `)`
    | ParenR
    /// `[`
    | BracketL
    /// `]`
    | BracketR
    /// `:`
    | Colon
    /// `.`
    | Dot
    /// `|`
    | Pipe
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
    | Exit
    | Printfn

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
    /// Equal
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
    | Int
      of int * 'a
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
    | Match
      of target:Expr<'a> * arm:(Pat<'a> * Expr<'a>) * 'a
    /// `x.[i]`
    | Index
      of Expr<'a> * Expr<'a> * 'a
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
  [<RequireQualifiedAccess>]
  type MTy =
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
    | Exit
    | Printfn
    /// Concatenates two strings.
    | StrAdd
    /// Compare two strings.
    | StrCmp

  [<RequireQualifiedAccess>]
  type MUniOp =
    | Not

  /// Operator in middle IR.
  /// Operands must be int.
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
    /// `&&`
    /// We don't use this for `&&` from Milone-lang
    /// but for generated codes.
    | And

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
    /// Projection. Gets an element of tuple.
    | Proj
      of MExpr<'a> * int * 'a
    | Index
      of MExpr<'a> * MExpr<'a> * 'a
    /// Call a function.
    /// This must occur in variable initializer if impure.
    | Call
      of callee:MExpr<'a> * args:MExpr<'a> list * 'a
    | UniOp
      of MUniOp * arg:MExpr<'a> * 'a
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
    /// Declares a tuple box variable filled by elements.
    | LetTuple
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

  /// Type in C language.
  [<RequireQualifiedAccess>]
  type CTy =
    | Void
    | Int
    | Char
    | Ptr
      of CTy
    | Struct
      of ident:string

  [<RequireQualifiedAccess>]
  type CPrim =
    | Malloc
    | Printf

  [<RequireQualifiedAccess>]
  type COp = MOp

  /// Expression in C language.
  [<RequireQualifiedAccess>]
  type CExpr =
    /// `{}`
    | Default
    | Int
      of int
    | Str
      of string
    | Prim
      of CPrim
    | Ref
      of string
    /// Projection. Get an element from tuple box.
    | Proj
      of CExpr * int
    | Cast
      of CExpr * CTy
    | Nav
      of CExpr * field:string
    /// `a[i]`
    | Index
      of CExpr * CExpr
    | Call
      of CExpr * args:CExpr list
    | UniOp
      of MUniOp * CExpr
    | Op
      of COp * CExpr * CExpr

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
      of CExpr * CExpr
    | Return
      of CExpr option
    | If
      of pred:CExpr * thenCl:CStmt list * elseCl:CStmt list

  /// Top-level definition in C language.
  [<RequireQualifiedAccess>]
  type CDecl =
    | Struct
      of ident:string * fields:(string * CTy) list
    | Fun
      of ident:string * args:(string * CTy) list * CTy * body:CStmt list
