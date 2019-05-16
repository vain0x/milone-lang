namespace rec MiloneLang

/// Location = (rowIndex, columnIndex).
type Loc = int * int

/// Diagnostic; something bad in source code in terms of language server protocol.
[<RequireQualifiedAccess>]
type Diag =
  | Err
    of string * Loc

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
  | As
  | When
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
  | In

/// Type constructors.
type TyCon =
  | Bool
  | Int
  | Char
  | Str
  | Range
  | Obj
  | Fun
  | Tuple
  | List
  /// Identifier which refers to a specific type, e.g. `Option`.
  | RefIdent
    of ident:string
  /// Type reference, i.e. some union type.
  | Ref
    of serial:int

/// Type of expressions.
[<RequireQualifiedAccess>]
type Ty =
  | Error
  /// Type variable, i.e. some binding.
  | Meta
    of serial:int
  | Con
    of TyCon * Ty list

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

/// Type declaration.
[<RequireQualifiedAccess>]
type TyDecl =
  /// Union type.
  /// Variants: (ident, serial, has-argument, argument type).
  | Union
    of ident:string * variants:(string * int * bool * Ty) list * Loc

/// Type definition.
[<RequireQualifiedAccess>]
type TyDef =
  /// Bound type variable.
  | Meta
    of ident:string * Ty * Loc
  | Union
    of ident:string * variants:int list * Loc

/// Variable definition in high-level IR.
[<RequireQualifiedAccess>]
type VarDef =
  | Var
    of ident:string * Ty * Loc
  | Fun
    of ident:string * arity:int * Ty * Loc
  /// Variant constructor.
  | Variant
    of ident:string * tySerial:int * hasArg:bool * argTy:Ty * Ty * Loc

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
  | As
    of HPat * ident:string * serial:int * Loc
  /// Type annotation pattern, e.g. `x : int`.
  | Anno
    of HPat * Ty * Loc
  | Or
    of HPat * HPat * Ty * Loc

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

/// Primitive in high-level IR.
[<RequireQualifiedAccess>]
type HPrim =
  | Not
  | Exit
  | Box
  | Unbox
  | Printfn
  | StrSlice
  | StrLength
  | Char
  | Int
  | String

[<RequireQualifiedAccess>]
type HValRef =
  | Var
    of serial:int
  | Prim
    of HPrim

/// Expression in AST.
[<RequireQualifiedAccess>]
type HExpr =
  | Lit
    of Lit * Loc
  /// Variable reference.
  | Ref
    of ident:string * HValRef * arity:int * Ty * Loc
  /// If-then-else. Else clause is `()` if omit.
  | If
    of pred:HExpr * thenCl:HExpr * elseCl:HExpr * Ty * Loc
  | Match
    of target:HExpr * (HPat * HExpr * HExpr) list * Ty * Loc
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
    of pat:HPat * init:HExpr * next:HExpr * Ty * Loc
  | LetFun
    of ident:string * serial:int * args:HPat list * body:HExpr * next:HExpr * Ty * Loc
  /// Type declaration.
  | TyDef
    of ident:string * serial:int * TyDecl * Loc
  | Error
    of string * Loc

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

/// Intermediate language between HIR and MIR for match expressions.
[<RequireQualifiedAccess>]
type MatchIR =
  | PatLabel
    of string
  | Pat
    of HPat * nextLabel:string
  | GoBody
    of bodyLabel:string
  | BodyLabel
    of bodyLabel:string
  | Guard
    of guard:HExpr * nextLabel:string
  | Body
    of body:HExpr

/// Expression in middle IR.
[<RequireQualifiedAccess>]
type MExpr =
  | Lit
    of Lit * Loc
  | Default
    of Ty * Loc
  | Ref
    of serial:int * arity:int * Ty * Loc
  | Prim
    of HPrim * Ty * Loc
  | Fun
    of serial:int * Ty * Loc
  | Variant
    of tySerial:int * serial:int * Ty * Loc
  | UniOp
    of MUniOp * arg:MExpr * resultTy:Ty * Loc
  | Op
    of MOp * left:MExpr * right:MExpr * resultTy:Ty * Loc

/// Variable initializer in mid-level IR.
[<RequireQualifiedAccess>]
type MInit =
  /// Remain uninitialized at first; initialized later by `MStmt.Set`.
  | UnInit
  | Expr
    of MExpr
  /// Call to normal function.
  | Call
    of callee:MExpr * args:MExpr list * calleeTy:Ty
  /// Call to function object.
  | Exec
    of callee:MExpr * args:MExpr list
  /// Creates a function object, packing environment.
  | Fun
    of subFunSerial:int * envSerial:int
  | Box
    of MExpr
  | Cons
    of head:MExpr * tail:MExpr * itemTy:Ty
  | Tuple
    of items:MExpr list
  | Union
    of serial:int * arg:MExpr * Ty

/// Statement in middle IR.
/// Doesn't introduce global things, e.g. functions.
[<RequireQualifiedAccess>]
type MStmt =
  /// Statement to evaluate an expression, e.g. `f ();`.
  | Do
    of MExpr * Loc
  /// Declare a local variable.
  | LetVal
    of serial:int * MInit * Ty * Loc
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
    of callee:int * args:(int * int * Ty * Loc) list * resultTy:Ty * body:MStmt list * Loc
  // FIXME: Unused!
  | TyDef

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
type CBinOp =
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
  | BinOp
    of CBinOp * CExpr * CExpr

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
  /// `#error` directive to cause compile error manually.
  | ErrDir
    of message:string * line:int
  | Struct
    of ident:string * fields:(string * CTy) list * variants:(string * CTy) list
  | Enum
    of ident:string * variants:string list
  | Fun
    of ident:string * args:(string * CTy) list * CTy * body:CStmt list
