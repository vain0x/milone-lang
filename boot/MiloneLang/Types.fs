namespace rec MiloneLang

  /// Location = (rowIndex, columnIndex).
  type Loc = int * int

  [<RequireQualifiedAccess>]
  type Token =
    | Int
      of int
    | Str
      of string
    | Ident
      of string
    | Do
    | Let
    | Rec
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
    | Private
    | Internal
    | Public
    | Module
    | Namespace
    | Open
    | Type

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
    | List
      of Ty

  [<RequireQualifiedAccess>]
  /// Primitive function.
  type PrimFun =
    | Exit
    | Printfn

  [<RequireQualifiedAccess>]
  type OpLevel =
    | Mul
    | Add
    | Cons
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
    /// `::`
    | Cons
    /// Comma to make a tuple
    | Tie

  /// Pattern in AST.
  [<RequireQualifiedAccess>]
  type Pat<'a> =
    | Unit
      of 'a
    | Int
      of int * 'a
    | Nil
      of 'a
    | Ident
      of ident:string * serial: int * 'a
    | Cons
      of Pat<'a> * Pat<'a> * 'a
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
    | List
      of Expr<'a> list * 'a
    | If
      of pred:Expr<'a> * thenCl:Expr<'a> * elseCl:Expr<'a> * 'a
    | Match
      of target:Expr<'a> * (Pat<'a> * Expr<'a>) * (Pat<'a> * Expr<'a>) * 'a
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
    | List
      of MTy
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

  /// Expression in middle IR.
  [<RequireQualifiedAccess>]
  type MExpr<'a> =
    /// Default value of the type.
    | Unit
      of MTy * 'a
    | Bool
      of bool * 'a
    | Int
      of int * 'a
    | Str
      of string * 'a
    | Nil
      of itemTy:MTy * 'a
    /// Primitive.
    | Prim
      of MPrim * 'a
    /// Variable reference.
    | Ref
      of serial:int * MTy * 'a
    | ListIsEmpty
      of MExpr<'a> * itemTy:MTy * 'a
    | ListHead
      of MExpr<'a> * itemTy:MTy * 'a
    | ListTail
      of MExpr<'a> * itemTy:MTy * 'a
    /// Projection. Gets an element of tuple.
    | Proj
      of MExpr<'a> * int * elemTy:MTy * 'a
    | Index
      of MExpr<'a> * MExpr<'a> * itemTy:MTy * 'a
    /// Call a function.
    /// This must occur in variable initializer if impure.
    | Call
      of callee:MExpr<'a> * args:MExpr<'a> list * resultTy:MTy * 'a
    | UniOp
      of MUniOp * arg:MExpr<'a> * resultTy:MTy * 'a
    | Op
      of MOp * left:MExpr<'a> * right:MExpr<'a> * resultTy:MTy * 'a

  /// Statement in middle IR.
  [<RequireQualifiedAccess>]
  type MStmt<'a> =
    /// Expression statement.
    | Expr
      of MExpr<'a> * 'a
    /// Local variable declaration.
    | LetVal
      of serial:int * init:MExpr<'a> option * MTy * 'a
    | LetCons
      of serial:int * head:MExpr<'a> * tail:MExpr<'a> * itemTy:MTy * 'a
    /// Declares a tuple box variable filled by elements.
    | LetTuple
      of serial:int * elems:MExpr<'a> list * tupleTy:MTy * 'a
    /// Set to local variable.
    | Set
      of serial:int * init:MExpr<'a> * 'a
    | Return
      of MExpr<'a> * 'a
    | Label
      of string * 'a
    | Goto
      of string * 'a
    | GotoUnless
      of MExpr<'a> * string * 'a

  /// Declaration in middle IR.
  [<RequireQualifiedAccess>]
  type MDecl<'a> =
    | LetFun
      of callee:int * args:(int * MTy * 'a) list * resultTy:MTy * body:MStmt<'a> list * 'a

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
    | Arrow
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
    /// `T* x = (T*)malloc(sizeof T);`
    | LetAlloc
      of ident:string * valTy:CTy
    /// `x = a;`
    | Set
      of CExpr * CExpr
    | Label
      of string
    | Goto
      of string
    | GotoUnless
      of CExpr * string
    | Return
      of CExpr option

  /// Top-level definition in C language.
  [<RequireQualifiedAccess>]
  type CDecl =
    | Struct
      of ident:string * fields:(string * CTy) list
    | Fun
      of ident:string * args:(string * CTy) list * CTy * body:CStmt list
