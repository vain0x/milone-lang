/// Defines the types used in multiple modules.
module rec MiloneLang.Types

/// Location = (rowIndex, columnIndex).
type Loc = int * int

[<RequireQualifiedAccess>]
type TyUnifyLog =
  | SelfRec
  | Mismatch

[<RequireQualifiedAccess>]
type Log =
  | TyUnify
    of TyUnifyLog * lRootTy:Ty * rRootTy:Ty * lTy:Ty * rTy:Ty
  | TyConstraintError
    of TyConstraint
  | Error
    of string

/// Words and punctuations in source code.
[<RequireQualifiedAccess>]
type Token =
  | Error
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
  /// `&`
  | Amp
  /// `&&`
  | AmpAmp
  /// `->`
  | Arrow
  | Colon
  | ColonColon
  | Comma
  | Dot
  | DotDot
  /// `=`
  | Eq
  /// `>`
  | Gt
  /// `>=`
  | GtEq
  /// `<`
  | Lt
  /// `<=`
  | LtEq
  /// `<>`
  | LtGt
  | Minus
  | Percent
  /// `|`
  | Pipe
  /// `|>`
  | PipeGt
  /// `||`
  | PipePipe
  | Plus
  /// `;`
  | Semi
  | Star
  | Slash
  | Private
  | Internal
  | Public
  | Module
  | Namespace
  | Open
  | Type
  | Of
  | Fun
  | In

/// Type expression in AST.
[<RequireQualifiedAccess>]
type ATy =
  | Error
    of string * Loc
  | Missing
    of Loc
  | Ident
    of string * Loc
  | Suffix
    of ATy * string * Loc
  /// Tuple type, e.g. `int * string`.
  | Tuple
    of ATy list * Loc
  /// Function type, e.g. `int -> string`.
  | Fun
    of ATy * ATy * Loc

/// Pattern in AST.
[<RequireQualifiedAccess>]
type APat =
  | Error
    of string * Loc
  | Missing
    of Loc
  | Lit
    of Lit * Loc
  | Ident
    of string * Loc
  | ListLit
    of APat list * Loc
  | Nav
    of APat * string * Loc
  /// Variant deconstruction. e.g. `Some x`.
  | Call
    of APat * APat list * Loc
  /// `::`
  | Cons
    of APat * APat * Loc
  | TupleLit
    of APat list * Loc
  | As
    of APat * string * Loc
  /// Type annotation, e.g. `x: int`.
  | Anno
    of APat * ATy * Loc
  | Or
    of APat * APat * Loc
  /// Function declaration pattern, e.g. `f x y`.
  /// Syntactically distinct from the call pattern.
  | Fun
    of string * APat list * Loc

/// Match arm node in AST.
[<RequireQualifiedAccess>]
type AArm =
  /// (pattern, guard, body).
  | T
    of APat * AExpr * AExpr * Loc

/// Variant node in AST.
[<RequireQualifiedAccess>]
type AVariant =
  /// (identifier, payload-type).
  | T
    of string * ATy option * Loc

/// Let expression in AST.
[<RequireQualifiedAccess>]
type ALet =
  | LetVal
    of APat * AExpr * AExpr * Loc
  | LetFun
    of ident:string * args:APat list * AExpr * AExpr * Loc

/// Body of type definition in AST.
[<RequireQualifiedAccess>]
type ATyDef =
  | Synonym
    of ATy
  | Union
    of AVariant list

/// Expression in AST.
[<RequireQualifiedAccess>]
type AExpr =
  | Error
    of string * Loc
  | Missing
    of Loc
  | Lit
    of Lit * Loc
  | Ident
    of string * Loc
  /// List literal, e.g. `[]`, `[2; 3]`.
  | ListLit
    of AExpr list * Loc
  /// condition, then-clause, else-clause. Else clause is `None` is missing.
  | If
    of AExpr * AExpr * AExpr * Loc
  | Match
    of AExpr * AArm list * Loc
  | Fun
    of APat list * AExpr * Loc
  /// Navigation expression, e.g. `str.Length`.
  | Nav
    of AExpr * string * Loc
  | Index
    of AExpr * AExpr * Loc
  /// Unary operation, e.g. `-x`.
  /// Currently `-` is the only unary operation.
  | Uni
    of UniOp * AExpr * Loc
  /// Binary operation, e.g. `x + y`.
  | Bin
    of Op * AExpr * AExpr * Loc
  /// Range syntax, e.g. `first..last`, `first .. step .. last`.
  | Range
    of AExpr list * Loc
  /// Tuple literal, e.g. `()`, `2, "two"`.
  | TupleLit
    of AExpr list * Loc
  /// Type annotation.
  | Anno
    of AExpr * ATy * Loc
  /// Semicolon-separated expressions.
  | Semi
    of AExpr list * Loc
  /// (pattern, initializer, next). Let-in expression.
  | Let
    of APat * AExpr * AExpr * Loc
  /// Type synonym definition, e.g. `type UserId = int`.
  | TySynonym
    of string * ATy * Loc
  /// Discriminated union type definition, e.g. `type Result = | Ok | Err of int`.
  | TyUnion
    of string * AVariant list * Loc
  | Open
    of string list * Loc

/// Type constructors.
[<RequireQualifiedAccess>]
type TyCon =
  | Bool
  | Int
  | Char
  | Str
  | Obj
  | Fun
  | Tuple
  | List
  /// Type reference, i.e. some union type.
  | Ref
    of serial:int

/// Type of expressions.
[<RequireQualifiedAccess>]
type Ty =
  | Error
    of Loc
  /// Type variable, i.e. some binding.
  | Meta
    of serial:int * Loc
  | Con
    of TyCon * Ty list

/// Generalized type.
[<RequireQualifiedAccess>]
type TyScheme =
  | ForAll of int list * Ty

[<RequireQualifiedAccess>]
type TyConstraint =
  | Add
    of Ty
  | Eq
    of Ty
  | Cmp
    of Ty
  | Index
    of lTy:Ty * rTy:Ty * resultTy:Ty
  | ToInt
    of Ty
  | ToString
    of Ty

/// Type context.
[<RequireQualifiedAccess>]
type TyContext =
  {
    Serial: int
    Tys: Map<int, TyDef>

    /// type serial -> let-depth,
    /// where `let-depth` is the number of ancestral `let` expressions.
    TyDepths: Map<int, int>
  }

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

/// Unary operators in AST.
[<RequireQualifiedAccess>]
type UniOp =
  /// `-`
  | Neg

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
  /// `::` Cons cell constructor
  | Cons
  /// `.[ ]`
  | Index

type NameCtx =
  | NameCtx
    of Map<int, string> * last: int

/// Type declaration.
[<RequireQualifiedAccess>]
type TyDecl =
  | Synonym
    of ty:Ty * Loc
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
    of ident:string * arity:int * TyScheme * Loc
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
  | Nav
    of HPat * string * Ty * Loc
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
  | App
  /// Type annotation `x : 'x`.
  | Anno
  /// `x; y`
  | Semi
  /// Direct call to procedure or primitive.
  | CallProc
  /// Indirect call to closure.
  | CallClosure
  /// Tuple constructor, e.g. `x, y, z`.
  | Tuple
  /// Closure constructor.
  | Closure

/// Primitive in high-level IR.
[<RequireQualifiedAccess>]
type HPrim =
  | Add
  | Sub
  | Mul
  | Div
  | Mod
  | Eq
  | Ne
  | Lt
  | Le
  | Gt
  | Ge
  | Nil
  | Cons
  | Index
  | Not
  | Exit
  | Assert
  | Box
  | Unbox
  | Printfn
  | StrLength
  | StrGetSlice
  | Char
  | Int
  | String
  | NativeFun
    of string * int

/// Expression in AST.
[<RequireQualifiedAccess>]
type HExpr =
  | Lit
    of Lit * Loc
  /// Variable reference.
  | Ref
    of ident:string * serial:int * Ty * Loc
  | Prim
    of HPrim * Ty * Loc
  | Match
    of target:HExpr * (HPat * HExpr * HExpr) list * Ty * Loc
  /// `s.m`
  | Nav
    of subject:HExpr * message:string * Ty * Loc
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
  | Open
    of ident:string list * Loc
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

/// Procedure declaration in middle IR.
[<RequireQualifiedAccess>]
type MProcDecl =
  {
    Callee: int
    /// serial, arity, ty, loc
    Args: (int * int * Ty * Loc) list
    ResultTy: Ty
    Body: MStmt list
    Main: bool
  }

/// Expression in middle IR.
[<RequireQualifiedAccess>]
type MExpr =
  | Lit
    of Lit * Loc
  | Default
    of Ty * Loc
  | Ref
    of serial:int * Ty * Loc
  /// Procedure
  | Proc
    of serial:int * Ty * Loc
  | Variant
    of tySerial:int * serial:int * Ty * Loc
  | Uni
    of MUniOp * arg:MExpr * resultTy:Ty * Loc
  | Bin
    of MOp * left:MExpr * right:MExpr * resultTy:Ty * Loc

/// Variable initializer in mid-level IR.
[<RequireQualifiedAccess>]
type MInit =
  /// Remain uninitialized at first; initialized later by `MStmt.Set`.
  | UnInit
  | Expr
    of MExpr
  /// Call to primitive.
  | CallPrim
    of HPrim * args:MExpr list * primTy:Ty
  /// Direct call to procedure.
  | CallProc
    of callee:MExpr * args:MExpr list * calleeTy:Ty
  /// Indirect call to closure.
  | CallClosure
    of callee:MExpr * args:MExpr list
  /// Construct a closure, packing environment.
  | Closure
    of subFunSerial:int * envSerial:int
  | Box
    of MExpr
  | Indirect
    of MExpr
  | Cons
    of head:MExpr * tail:MExpr
  | Tuple
    of items:MExpr list
  | Variant
    of serial:int * payloadSerial:int

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
  | Proc
    of MProcDecl * Loc

/// Declaration in middle IR.
[<RequireQualifiedAccess>]
type MDecl =
  | Proc
    of MProcDecl * Loc

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
  | Uni
    of CUniOp * CExpr
  | Bin
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
    of ident:string * valPtrTy:CTy * varTy:CTy
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
