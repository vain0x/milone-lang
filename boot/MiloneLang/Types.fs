namespace rec MiloneLang

  /// Location = (rowIndex, columnIndex).
  type Loc = int * int

  [<RequireQualifiedAccess>]
  type Err =
    | UnifyTy
      of Ty * Ty * Loc

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
    /// `|>`
    | Pipe
    /// Comparison.
    | Cmp
    | And
    | Or
    /// `..`
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
    /// `.[ ]`
    | Index

  /// Type definition.
  [<RequireQualifiedAccess>]
  type TyDef =
    /// Union type. Variants: (ident, serial, has-argument, argument type).
    | Union
      of (string * int * bool * Ty) list

  /// Pattern in AST.
  [<RequireQualifiedAccess>]
  type HPat =
    | Lit
      of Lit * Loc
    /// `[]`
    | Nil
      of itemTy:Ty * Loc
    /// Variable reference pattern or `_`.
    | Ref
      of ident:string * serial:int * Ty * Loc
    | Call
      of callee:HPat * args:HPat list * Ty * Loc
    /// `::`
    | Cons
      of HPat * HPat * itemTy:Ty * Loc
    | Tuple
      of HPat list * tupleTy:Ty * Loc
    /// Type annotation pattern, e.g. `x : int`.
    | Anno
      of HPat * Ty * Loc

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

  [<RequireQualifiedAccess>]
  type InfOp =
    /// Type annotation `x : 'x`.
    | Anno
    /// `x; y`
    | AndThen
    /// Call to a function, not a function object.
    | Call
    /// Call to a function object.
    | Exec
    /// Tuple constructor, e.g. `x, y, z`.
    | Tuple
    /// List constructor, e.g. `[x; y; z]`.
    | List
      of itemTy:Ty
    /// Function object constructor.
    | Fun
      of funSerial:int

  /// Expression in AST. `a` is typically a source location info.
  [<RequireQualifiedAccess>]
  type HExpr =
    | Lit
      of Lit * Loc
    /// Variable reference.
    | Ref
      of ident:string * serial:int * arity:int * Ty * Loc
    /// If-then-else. Else clause is `()` if omit.
    | If
      of pred:HExpr * thenCl:HExpr * elseCl:HExpr * Ty * Loc
    | Match
      of target:HExpr * (HPat * HExpr) list * Ty * Loc
    /// `s.m`
    | Nav
      of subject:HExpr * message:string * Ty * Loc
    /// Binary operation, e.g. `x + y`.
    | Op
      of Op * HExpr * HExpr * Ty * Loc
    /// Operation with infinite arguments.
    | Inf
      of InfOp * HExpr list * Ty * Loc
    | Let
      of pat:HPat * init:HExpr * Loc
    | LetFun
      of ident:string * serial:int * args:HPat list * body:HExpr * resultTy:Ty * Loc
    /// Type definition.
    | TyDef
      of ident:string * serial:int * TyDef * Loc
    | Error
      of string * Loc

  /// Type definition in mid-level IR.
  [<RequireQualifiedAccess>]
  type MTyDef =
    /// Union type. Variants: (serial, argument type, variant type) list.
    | Union
      of (int * bool * MTy * MTy) list

  /// Type in middle IR.
  [<RequireQualifiedAccess>]
  type MTy =
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
  type MExpr =
    | Lit
      of Lit * Loc
    | Default
      of MTy * Loc
    | Ref
      of serial:int * arity:int * MTy * Loc
    | Variant
      of tySerial:int * serial:int * MTy * Loc
    | UniOp
      of MUniOp * arg:MExpr * resultTy:MTy * Loc
    | Op
      of MOp * left:MExpr * right:MExpr * resultTy:MTy * Loc

  /// Variable initializer in mid-level IR.
  [<RequireQualifiedAccess>]
  type MInit =
    /// Remain uninitialized at first; initialized later by `MStmt.Set`.
    | UnInit
    | Expr
      of MExpr
    /// Call to normal function.
    | Call
      of callee:MExpr * args:MExpr list * calleeTy:MTy
    /// Call to function object.
    | Exec
      of callee:MExpr * args:MExpr list
    /// Creates a function object, packing environment.
    | Fun
      of subFunSerial:int * envSerial:int
    | Box
      of MExpr
    | Cons
      of head:MExpr * tail:MExpr * itemTy:MTy
    | Tuple
      of items:MExpr list
    | Union
      of serial:int * arg:MExpr * MTy

  /// Statement in middle IR.
  /// Doesn't introduce global things, e.g. functions.
  [<RequireQualifiedAccess>]
  type MStmt =
    /// Statement to evaluate an expression, e.g. `f ();`.
    | Do
      of MExpr * Loc
    /// Declare a local variable.
    | LetVal
      of serial:int * MInit * MTy * Loc
    /// Set to uninitialized local variable.
    | Set
      of serial:int * init:MExpr * Loc
    | Return
      of MExpr * Loc
    | Label
      of string * Loc
    | Goto
      of string * Loc
    | GotoUnless
      of MExpr * string * Loc
    | Exit
      of MExpr * Loc

  /// Declaration in middle IR.
  [<RequireQualifiedAccess>]
  type MDecl =
    | LetFun
      of callee:int * args:(int * int * MTy * Loc) list * caps:(int * int * MTy * Loc) list * resultTy:MTy * body:MStmt list * Loc
    | TyDef
      of int * TyDef * Loc

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
