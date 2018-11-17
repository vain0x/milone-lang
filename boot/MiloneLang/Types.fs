namespace rec MiloneLang

  /// Location = (rowIndex, columnIndex).
  type Loc = int * int

  /// Word or punctuation in source code.
  [<RequireQualifiedAccess>]
  type Token =
    | Bool
      of bool
    | Int
      of int
    | Char
      of char
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
    /// `..`
    | Range
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
    | Of

  /// Type of expressions.
  [<RequireQualifiedAccess>]
  type Ty =
    | Error
    | Unit
    | Bool
    | Int
    | Char
    | Str
    | Range
    | Obj
    /// Type reference, i.e. name of some type.
    | Ref
      of ident:string * serial:int
    | Var
      of string
    | Fun
      of Ty * Ty
    | Tuple
      of Ty list
    | List
      of Ty

  /// Precedence level of binary operators.
  [<RequireQualifiedAccess>]
  type OpLevel =
    | Mul
    | Add
    | Cons
    /// Comparison.
    | Cmp
    | Pipe
    | And
    | Or
    | Range

  /// Binary operators in AST.
  [<RequireQualifiedAccess>]
  type Op =
    /// `*` Multiplier
    | Mul
    /// `/` Divisor
    | Div
    /// `%` Modulo
    | Mod
    /// `+` Addition
    | Add
    /// `-` Subtract
    | Sub
    /// `=` Equal
    | Eq
    /// `<>` Not Equal
    | Ne
    /// `<` Less than
    | Lt
    /// `<=` Less than or equal to
    | Le
    /// `>` Greater than
    | Gt
    /// `>=` Greater than or equal to
    | Ge
    /// `|>`
    | Pipe
    /// `&&`
    | And
    /// `||`
    | Or
    /// `f x` Application
    | App
    /// `::` Construction
    | Cons
      of Ty
    /// `..`
    | Range

  /// Type definition.
  [<RequireQualifiedAccess>]
  type TyDef =
    /// Union type. Variants: (ident, serial, has-argument, argument type).
    | Union
      of (string * int * bool * Ty) list

  /// Pattern in AST.
  [<RequireQualifiedAccess>]
  type Pat<'a> =
    | Lit
      of Lit * 'a
    | Unit
      of 'a
    /// `[]`
    | Nil
      of itemTy:Ty * 'a
    /// Variable reference pattern or `_`.
    | Ref
      of ident:string * serial:int * Ty * 'a
    | Call
      of callee:Pat<'a> * args:Pat<'a> list * Ty * 'a
    /// `::`
    | Cons
      of Pat<'a> * Pat<'a> * itemTy:Ty * 'a
    | Tuple
      of Pat<'a> list * tupleTy:Ty * 'a
    /// Type annotation pattern, e.g. `x : int`.
    | Anno
      of Pat<'a> * Ty * 'a

  /// Literal of primitive value.
  [<RequireQualifiedAccess>]
  type Lit =
    | Bool
      of bool
    | Int
      of int
    | Char
      of char
    | Str
      of string

  /// Value-level identifier.
  [<RequireQualifiedAccess>]
  type ValueIdent =
    | Var
    | Fun
      of arity:int
    /// Variant of union with no argument.
    | Variant
      of tySerial:int

  /// Expression in AST. `a` is typically a source location info.
  [<RequireQualifiedAccess>]
  type Expr<'a> =
    | Lit
      of Lit * 'a
    | Unit
      of 'a
    /// Variable reference.
    | Ref
      of ident:string * serial:int * arity:int * Ty * 'a
    | List
      of Expr<'a> list * itemTy:Ty * 'a
    /// If-then-else. Else clause is `()` if omit.
    | If
      of pred:Expr<'a> * thenCl:Expr<'a> * elseCl:Expr<'a> * Ty * 'a
    | Match
      of target:Expr<'a> * (Pat<'a> * Expr<'a>) list * Ty * 'a
    /// `s.m`
    | Nav
      of subject:Expr<'a> * message:string * Ty * 'a
    /// `x.[i]`
    | Index
      of Expr<'a> * Expr<'a> * Ty * 'a
    /// Binary operation, e.g. `x + y`.
    | Op
      of Op * Expr<'a> * Expr<'a> * Ty * 'a
    /// Tuple constructor, e.g. `x, y, z`.
    | Tuple
      of Expr<'a> list * itemTys:Ty list * 'a
    /// Type annotation `x : 'x`.
    | Anno
      of Expr<'a> * Ty * 'a
    /// `x; y`
    | AndThen
      of Expr<'a> list * Ty * 'a
    | Let
      of pat:Pat<'a> * init:Expr<'a> * 'a
    /// Type definition.
    | TyDef
      of ident:string * serial:int * TyDef * 'a

  /// Type definition in mid-level IR.
  [<RequireQualifiedAccess>]
  type MTyDef =
    /// Union type. Variants: (serial, argument type, variant type) list.
    | Union
      of (int * bool * MTy * MTy) list

  /// Type in middle IR.
  [<RequireQualifiedAccess>]
  type MTy =
    | Unit
    /// Boolean.
    | Bool
    /// Integer.
    | Int
    /// Character.
    | Char
    /// String.
    | Str
    /// Object.
    | Obj
    /// Reference to named type.
    | Ref
      of int
    /// Function type, e.g. `int -> int`.
    | Fun
      of MTy * MTy
    | List
      of MTy
    | Tuple
      of MTy list

  /// Unary operator in middle IR.
  /// Or primitive function with single parameter.
  [<RequireQualifiedAccess>]
  type MUniOp =
    | Not
    | StrPtr
    | StrLen
    | Unbox
    /// Projection. Get an item of tuple.
    | Proj
      of int
    /// Get union tag.
    | Tag
    | GetVariant
      of int
    | ListIsEmpty
    | ListHead
    | ListTail
    | Exit

  /// Binary operator in middle IR.
  /// Or primitive function with two parameters.
  [<RequireQualifiedAccess>]
  type MOp =
    | Mul
    | Div
    | Mod
    | Add
    | Sub
    | Eq
    | Ne
    | Lt
    | Le
    /// Concatenate two strings.
    | StrAdd
    /// Compare two strings.
    | StrCmp
    /// Get a char.
    | StrIndex

  /// Expression in middle IR.
  [<RequireQualifiedAccess>]
  type MExpr<'a> =
    | Lit
      of Lit * 'a
    | Default
      of MTy * 'a
    | Ref
      of serial:int * arity:int * MTy * 'a
    | Variant
      of tySerial:int * serial:int * MTy * 'a
    | UniOp
      of MUniOp * arg:MExpr<'a> * resultTy:MTy * 'a
    | Op
      of MOp * left:MExpr<'a> * right:MExpr<'a> * resultTy:MTy * 'a

  /// Variable initializer in mid-level IR.
  [<RequireQualifiedAccess>]
  type MInit<'a> =
    /// Remain uninitialized at first; initialized later by `MStmt.Set`.
    | UnInit
    | Expr
      of MExpr<'a>
    | Call
      of callee:MExpr<'a> * args:MExpr<'a> list
    | App
      of callee:MExpr<'a> * arg:MExpr<'a>
    /// Creates a function object, packing environment.
    | Fun
      of subFunSerial:int * envSerial:int
    | Box
      of MExpr<'a>
    | Cons
      of head:MExpr<'a> * tail:MExpr<'a> * itemTy:MTy
    | Tuple
      of items:MExpr<'a> list
    | Union
      of serial:int * arg:MExpr<'a> * MTy

  /// Statement in middle IR.
  /// Doesn't introduce global things, e.g. functions.
  [<RequireQualifiedAccess>]
  type MStmt<'a> =
    /// Statement to evaluate an expression, e.g. `f ();`.
    | Do
      of MExpr<'a> * 'a
    /// Declare a local variable.
    | LetVal
      of serial:int * MInit<'a> * MTy * 'a
    /// Set to uninitialized local variable.
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
      of callee:int * args:(int * int * MTy * 'a) list * caps:(int * int * MTy * 'a) list * resultTy:MTy * body:MStmt<'a> list * 'a
    | TyDef
      of int * TyDef * 'a

  /// Type in C language.
  [<RequireQualifiedAccess>]
  type CTy =
    | Void
    | Int
    | Char
    | Ptr
      of CTy
    | FunPtr
      of CTy list * CTy
    | Struct
      of ident:string
    | Enum
      of ident:string

  [<RequireQualifiedAccess>]
  type CUniOp =
    | Not
    | Deref

  [<RequireQualifiedAccess>]
  type COp =
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

  /// Expression in C language.
  [<RequireQualifiedAccess>]
  type CExpr =
    /// `{}`
    | Default
    | Int
      of int
    | Char
      of char
    | StrRaw
      of string
    | StrObj
      of string
    | Ref
      of string
    /// `(struct T){.x = x, ..}` Initializer.
    | Init
      of fields:(string * CExpr) list * CTy
    /// Projection. Get an item of tuple.
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
      of CUniOp * CExpr
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
    /// `U* x = (U*)malloc(sizeof T);`
    | LetAlloc
      of ident:string * valTy:CTy * ptrTy:CTy
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
      of ident:string * fields:(string * CTy) list * variants:(string * CTy) list
    | Enum
      of ident:string * variants:string list
    | Fun
      of ident:string * args:(string * CTy) list * CTy * body:CStmt list
