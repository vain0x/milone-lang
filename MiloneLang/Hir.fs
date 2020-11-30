/// # Hir
///
/// Provides types and functions for high-level intermediate representation (HIR).
///
/// HIR is functional-style. Similar to milone-lang's syntax.
///
/// ## Lifecycle
///
/// HIR is generated in `AstToHir` for each file
/// and all modules of a project are *concatenated* in `Bundling`.
///
/// Most of analysis (for error reporting and soundness)
/// and transformations (for code generation) are performed on it.
///
/// Finally HIR is converted to MIR in `MirGen`.
///
/// See `Cli.fs` for details.
module rec MiloneLang.Hir

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.TypeFloat
open MiloneLang.TypeIntegers

/// Unique serial number to identify something
/// such as variables, nominal types, etc.
type Serial = int

// -----------------------------------------------
// HIR types
// -----------------------------------------------

/// Serial number of types.
type TySerial = Serial

/// Serial number of variables.
[<Struct; NoEquality; NoComparison>]
type VarSerial = VarSerial of Serial

/// Serial number of functions.
[<Struct; NoEquality; NoComparison>]
type FunSerial = FunSerial of Serial

/// Serial number of variants.
[<Struct; NoEquality; NoComparison>]
type VariantSerial = VariantSerial of Serial

/// Number of parameters.
type Arity = int

/// Let-depth, i.e. the number of ancestral let nodes
/// of the place where the meta type is introduced.
/// Used for polymorphic type inference.
/// E.g. in `let x: 'x = ((let y: 'y = a: 'a); b: 'b)`,
///   `'x`: 0, `'y`: 1, `'a`: 2, `'b`: 1
/// Only one exception: recursive function have let-depth deeper by 1.
type LetDepth = int

/// Where variable is stored.
[<NoEquality; NoComparison>]
type StorageModifier =
  /// On stack.
  | AutoSM

  /// On static storage.
  | StaticSM

[<Struct>]
[<NoEquality; NoComparison>]
type NameCtx = NameCtx of map: AssocMap<Serial, Ident> * lastSerial: Serial

[<NoEquality; NoComparison>]
type IsMut =
  | IsConst
  | IsMut

/// Type constructor.
[<Struct>]
[<NoEquality; NoComparison>]
type TyCtor =
  | IntTyCtor of intFlavor: IntFlavor
  | FloatTyCtor of floatFlavor: FloatFlavor
  | BoolTyCtor
  | CharTyCtor
  | StrTyCtor
  | ObjTyCtor

  /// Ty args must be `[s; t]`.
  | FunTyCtor

  | TupleTyCtor

  /// Ty args must be `[t]`.
  | ListTyCtor

  // FFI types.
  | VoidTyCtor
  | NativePtrTyCtor of nativePtrIsMut: IsMut

  // Nominal types.
  | SynonymTyCtor of synonymTy: TySerial
  | UnionTyCtor of unionTy: TySerial
  | RecordTyCtor of recordTy: TySerial

  /// Unresolved type. Generated in AstToHir, resolved in NameRes.
  | UnresolvedTyCtor of unresolvedSerial: Serial

/// Type of expressions.
[<Struct>]
[<NoEquality; NoComparison>]
type Ty =
  | ErrorTy of errorLoc: Loc

  /// Type variable to be bound or quantified..
  | MetaTy of metaTySerial: Serial * metaLoc: Loc

  /// Type application.
  | AppTy of TyCtor * tyArgs: Ty list

/// Potentially polymorphic type.
[<Struct>]
[<NoEquality; NoComparison>]
type TyScheme = TyScheme of tyVars: TySerial list * Ty

/// Type specification.
[<Struct>]
[<NoEquality; NoComparison>]
type TySpec = TySpec of Ty * Trait list

/// Trait, a constraint about types.
// NOTE: `trait` is a reserved word in F#.
[<NoEquality; NoComparison>]
type Trait =
  /// The type supports `+`.
  | AddTrait of Ty

  /// The type supports `=`.
  | EqTrait of Ty

  /// The type supports `<`.
  | CmpTrait of Ty

  /// For `l: lTy, r: rTy`, `l.[r]` is allowed.
  | IndexTrait of lTy: Ty * rTy: Ty * resultTy: Ty

  /// Integer type. Defaults to int.
  | IsIntTrait of Ty

  /// Integer or float type. Defaults to int.
  | IsNumberTrait of Ty

  /// Type supports conversion to integer.
  | ToIntTrait of Ty

  | ToFloatTrait of Ty

  /// Type can be applied to `string` function.
  | ToStringTrait of Ty

  | PtrTrait of Ty

/// Type declaration.
[<NoEquality; NoComparison>]
type TyDecl =
  | TySynonymDecl of Ty * Loc

  /// Union type.
  /// Variants: (ident, serial, has-payload, payload type).
  | UnionTyDecl of Ident * variants: (Ident * VariantSerial * bool * Ty) list * Loc

  | RecordTyDecl of Ident * fields: (Ident * Ty * Loc) list * Loc

/// Type definition.
[<NoEquality; NoComparison>]
type TyDef =
  /// Bound type variable.
  | MetaTyDef of Ident * Ty * Loc

  | UniversalTyDef of Ident * Loc

  | SynonymTyDef of Ident * TySerial list * Ty * Loc

  | UnionTyDef of Ident * VariantSerial list * Loc

  | RecordTyDef of Ident * fields: (Ident * Ty * Loc) list * Loc

[<Struct; NoEquality; NoComparison>]
type ModuleTySerial = ModuleTySerial of Serial

//// Module is a type so that it can be used as namespace.
[<NoEquality; NoComparison>]
type ModuleTyDef = { Name: Ident; Loc: Loc }

/// Definition of named value in HIR.
[<NoEquality; NoComparison>]
type VarDef = VarDef of Ident * StorageModifier * Ty * Loc

[<NoEquality; NoComparison>]
type FunDef =
  { Name: Ident
    Arity: Arity
    Ty: TyScheme
    Loc: Loc }

[<NoEquality; NoComparison>]
type VariantDef =
  { Name: Ident
    UnionTySerial: TySerial
    HasPayload: bool
    PayloadTy: Ty
    VariantTy: Ty
    Loc: Loc }

[<Struct; NoEquality; NoComparison>]
type ValueSymbol =
  | VarSymbol of varSerial: VarSerial
  | FunSymbol of funSerial: FunSerial
  | VariantSymbol of variantSerial: VariantSerial

[<Struct; NoEquality; NoComparison>]
type TySymbol =
  | MetaTySymbol of tySerial: TySerial
  | UnivTySymbol of univTySerial: TySerial
  | SynonymTySymbol of synonymTySerial: TySerial
  | UnionTySymbol of unionTySerial: TySerial
  | RecordTySymbol of recordTySerial: TySerial
  | ModuleTySymbol of moduleTySerial: ModuleTySerial

/// Pattern in HIR.
[<NoEquality; NoComparison>]
type HPat =
  | HLitPat of Lit * Loc

  /// `[]`
  | HNilPat of itemTy: Ty * Loc

  | HNonePat of itemTy: Ty * Loc
  | HSomePat of itemTy: Ty * Loc

  /// `_`
  | HDiscardPat of Ty * Loc

  /// Variable pattern.
  | HRefPat of VarSerial * Ty * Loc

  /// Variant pattern.
  | HVariantPat of VariantSerial * Ty * Loc

  /// Navigation, e.g. `Result.Ok _`.
  | HNavPat of HPat * Ident * Ty * Loc

  /// Variant decomposition, e.g. `Some x`.
  | HCallPat of callee: HPat * args: HPat list * Ty * Loc

  /// `::`
  | HConsPat of HPat * HPat * itemTy: Ty * Loc

  /// e.g. `x, y, z`
  | HTuplePat of HPat list * tupleTy: Ty * Loc

  /// Used to dereference a box inside of pattern matching.
  ///
  /// To match a value `v: obj` with box pattern `box p: T`,
  /// match `unbox v: T` with `p: T`.
  ///
  /// This is only generated internally in AutoBoxing.
  /// Not a part of F# nor milone-lang syntax.
  /// Unlike `:? T`, unboxing is unchecked.
  | HBoxPat of HPat * Loc

  | HAsPat of HPat * VarSerial * Loc

  /// Type annotation, e.g. `x: int`.
  | HAnnoPat of HPat * Ty * Loc

  /// Disjunction.
  | HOrPat of HPat * HPat * Ty * Loc

/// Primitive in HIR.
[<RequireQualifiedAccess>]
[<Struct>]
[<NoEquality; NoComparison>]
type HPrim =
  // operator:
  | Not
  | Add
  | Sub
  | Mul
  | Div
  | Mod
  | BitAnd
  | BitOr
  | BitXor
  | LeftShift
  | RightShift
  | Eq
  | Lt
  | Compare

  // conversion:
  | ToInt of toIntFlavor: IntFlavor
  | ToFloat of toFloatFlavor: FloatFlavor
  | Char
  | String
  | Box
  | Unbox

  // string:
  | StrLength

  // option:
  | OptionNone
  | OptionSome

  // list:
  | Nil
  | Cons

  // effects:
  | Exit
  | Assert
  | Printfn
  | InRegion
  | NativeFun
  | NativeCast

[<RequireQualifiedAccess>]
[<Struct>]
[<NoEquality; NoComparison>]
type InfOp =
  | Abort

  | App

  /// `..`.
  ///
  /// Every occurrence of this is currently error
  /// because valid use (`s.[l..r]`) gets rewritten in AstToHir.
  | Range

  /// Type annotation `x : 'x`.
  | Anno

  /// `x; y`
  | Semi

  /// `s.[i]`
  | Index

  /// `s.[l .. r]`
  | Slice

  /// Direct call to procedure or primitive.
  | CallProc

  /// Indirect call to closure.
  | CallClosure

  /// Direct call to current procedure at the end of function (i.e. tail-call).
  | CallTailRec

  /// Direct call to native fun.
  | CallNative of funName: string

  /// Tuple constructor, e.g. `x, y, z`.
  | Tuple

  /// Closure constructor.
  | Closure

  /// Record creation.
  ///
  /// Unlike record expr, it's guaranteed that
  /// all of fields are specified in order of declaration.
  | Record

  /// Gets i'th field of record.
  | RecordItem of index: int

/// Expression in HIR.
[<NoEquality; NoComparison>]
type HExpr =
  | HLitExpr of Lit * Loc

  /// Name of variable.
  | HRefExpr of VarSerial * Ty * Loc

  /// Name of function.
  | HFunExpr of FunSerial * Ty * Loc

  /// Name of variant.
  | HVariantExpr of VariantSerial * Ty * Loc

  | HPrimExpr of HPrim * Ty * Loc

  | HRecordExpr of HExpr option * fields: (Ident * HExpr * Loc) list * Ty * Loc

  /// arms: (pat, guard, body). Guard is `true` if omit.
  | HMatchExpr of cond: HExpr * arms: (HPat * HExpr * HExpr) list * Ty * Loc

  /// E.g. `List.isEmpty`, `str.Length`
  | HNavExpr of HExpr * Ident * Ty * Loc

  /// Some built-in operation.
  | HInfExpr of InfOp * HExpr list * Ty * Loc

  | HLetValExpr of Vis * pat: HPat * init: HExpr * next: HExpr * Ty * Loc
  | HLetFunExpr of FunSerial * Vis * isMainFun: bool * args: HPat list * body: HExpr * next: HExpr * Ty * Loc

  /// Type declaration.
  | HTyDeclExpr of TySerial * Vis * tyArgs: TySerial list * TyDecl * Loc
  | HOpenExpr of Ident list * Loc
  | HModuleExpr of ModuleTySerial * body: HExpr * next: HExpr * Loc

[<RequireQualifiedAccess>]
[<NoEquality; NoComparison>]
type MonoMode =
  | Monify
  | RemoveGenerics

// -----------------------------------------------
// Errors
// -----------------------------------------------

[<NoEquality; NoComparison>]
type NameResLog =
  | UndefinedValueError of name: string
  | UndefinedTyError of name: string
  | FunPatError of name: string
  | TyArityError of name: string * actual: int * expected: int
  | ModuleUsedAsTyError of name: string
  | OtherNameResLog of msg: string

[<RequireQualifiedAccess>]
[<NoEquality; NoComparison>]
type TyUnifyLog =
  | SelfRec
  | Mismatch

[<RequireQualifiedAccess>]
[<NoEquality; NoComparison>]
type Log =
  | NameResLog of NameResLog
  | TyUnify of TyUnifyLog * lRootTy: Ty * rRootTy: Ty * lTy: Ty * rTy: Ty
  | TyBoundError of Trait
  | RedundantFieldError of ty: Ident * field: Ident
  | MissingFieldsError of ty: Ident * fields: Ident list
  | Error of string

// -----------------------------------------------
// Name context
// -----------------------------------------------

let nameCtxEmpty () = NameCtx(mapEmpty compare, 0)

let nameCtxAdd name (NameCtx (map, serial)) =
  let serial = serial + 1
  let map = map |> mapAdd serial name
  serial, NameCtx(map, serial)

// -----------------------------------------------
// Types (HIR/MIR)
// -----------------------------------------------

/// Placeholder. No type info in the parsing phase.
let noTy = ErrorTy noLoc

let tyInt =
  AppTy(IntTyCtor(IntFlavor(Signed, I32)), [])

let tyBool = AppTy(BoolTyCtor, [])

let tyFloat = AppTy(FloatTyCtor F64, [])

let tyChar = AppTy(CharTyCtor, [])

let tyStr = AppTy(StrTyCtor, [])

let tyObj = AppTy(ObjTyCtor, [])

let tyTuple tys = AppTy(TupleTyCtor, tys)

let tyList ty = AppTy(ListTyCtor, [ ty ])

let tyFun sourceTy targetTy = AppTy(FunTyCtor, [ sourceTy; targetTy ])

let tyUnit = tyTuple []

let tySynonym tySerial tyArgs = AppTy(SynonymTyCtor tySerial, tyArgs)

let tyUnion tySerial = AppTy(UnionTyCtor tySerial, [])

let tyRecord tySerial = AppTy(RecordTyCtor tySerial, [])

// -----------------------------------------------
// Type definitions (HIR)
// -----------------------------------------------

let moduleTySerialToInt (ModuleTySerial serial) = serial

let moduleTySerialCmp l r =
  moduleTySerialToInt l - moduleTySerialToInt r

let tyDefToName tyDef =
  match tyDef with
  | MetaTyDef (name, _, _) -> name
  | UniversalTyDef (name, _) -> name
  | SynonymTyDef (name, _, _, _) -> name
  | UnionTyDef (name, _, _) -> name
  | RecordTyDef (name, _, _) -> name

// -----------------------------------------------
// Variable definitions (HIR)
// -----------------------------------------------

let varSerialToInt (VarSerial serial) = serial

let varSerialCmp l r =
  compare (varSerialToInt l) (varSerialToInt r)

let funSerialToInt (FunSerial serial) = serial

let funSerialCmp l r =
  compare (funSerialToInt l) (funSerialToInt r)

let variantSerialToInt (VariantSerial serial) = serial

let variantSerialCmp l r =
  compare (variantSerialToInt l) (variantSerialToInt r)

let varDefToName varDef =
  match varDef with
  | VarDef (name, _, _, _) -> name

// -----------------------------------------------
// Literals
// -----------------------------------------------

let litToTy (lit: Lit): Ty =
  match lit with
  | BoolLit _ -> tyBool
  | IntLit _ -> tyInt
  | FloatLit _ -> tyFloat
  | CharLit _ -> tyChar
  | StrLit _ -> tyStr

// -----------------------------------------------
// Primitives (HIR)
// -----------------------------------------------

let primFromIdent ident =
  match ident with
  | "not" -> HPrim.Not |> Some

  | "exit" -> HPrim.Exit |> Some

  | "assert" -> HPrim.Assert |> Some

  | "box" -> HPrim.Box |> Some

  | "unbox" -> HPrim.Unbox |> Some

  | "printfn" -> HPrim.Printfn |> Some

  | "compare" -> HPrim.Compare |> Some

  | "char" -> HPrim.Char |> Some

  | "int"
  | "int32" -> HPrim.ToInt(IntFlavor(Signed, I32)) |> Some
  | "uint"
  | "uint32" -> HPrim.ToInt(IntFlavor(Unsigned, I32)) |> Some
  | "sbyte"
  | "int8" -> HPrim.ToInt(IntFlavor(Signed, I8)) |> Some
  | "byte"
  | "uint8" -> HPrim.ToInt(IntFlavor(Unsigned, I8)) |> Some

  | "int16" -> HPrim.ToInt(IntFlavor(Signed, I16)) |> Some
  | "int64" -> HPrim.ToInt(IntFlavor(Signed, I64)) |> Some
  | "nativeint" -> HPrim.ToInt(IntFlavor(Signed, IPtr)) |> Some
  | "uint16" -> HPrim.ToInt(IntFlavor(Unsigned, I16)) |> Some
  | "uint64" -> HPrim.ToInt(IntFlavor(Unsigned, I64)) |> Some
  | "unativeint" -> HPrim.ToInt(IntFlavor(Unsigned, IPtr)) |> Some

  | "float" -> HPrim.ToFloat F64 |> Some
  | "float32" -> HPrim.ToFloat F32 |> Some

  | "string" -> HPrim.String |> Some

  | "None" -> HPrim.OptionNone |> Some

  | "Some" -> HPrim.OptionSome |> Some

  | "inRegion" -> HPrim.InRegion |> Some

  | "__nativeFun" -> HPrim.NativeFun |> Some
  | "__nativeCast" -> HPrim.NativeCast |> Some

  | _ -> None

let primToTySpec prim =
  let meta id = MetaTy(id, noLoc)
  let mono ty = TySpec(ty, [])
  let poly ty traits = TySpec(ty, traits)

  match prim with
  | HPrim.Add ->
      let addTy = meta 1
      poly (tyFun addTy (tyFun addTy addTy)) [ AddTrait addTy ]

  | HPrim.Sub
  | HPrim.Mul
  | HPrim.Div
  | HPrim.Mod ->
      let ty = meta 1
      poly (tyFun ty (tyFun ty ty)) [ IsNumberTrait ty ]

  | HPrim.BitAnd
  | HPrim.BitOr
  | HPrim.BitXor ->
      let ty = meta 1
      poly (tyFun ty (tyFun ty ty)) [ IsIntTrait ty ]

  | HPrim.LeftShift
  | HPrim.RightShift ->
      let ty = meta 1
      poly (tyFun ty (tyFun tyInt ty)) [ IsIntTrait ty ]

  | HPrim.Eq ->
      let eqTy = meta 1
      poly (tyFun eqTy (tyFun eqTy tyBool)) [ EqTrait eqTy ]

  | HPrim.Lt ->
      let cmpTy = meta 1
      poly (tyFun cmpTy (tyFun cmpTy tyBool)) [ CmpTrait cmpTy ]

  | HPrim.Compare ->
      let cmpTy = meta 1
      poly (tyFun cmpTy (tyFun cmpTy tyInt)) [ CmpTrait cmpTy ]

  | HPrim.Nil ->
      let itemTy = meta 1
      poly (tyList itemTy) []

  | HPrim.Cons ->
      let itemTy = meta 1
      let listTy = tyList itemTy
      poly (tyFun itemTy (tyFun listTy listTy)) []

  | HPrim.OptionNone ->
      let itemTy = meta 1
      poly (tyList itemTy) []

  | HPrim.OptionSome ->
      let itemTy = meta 1
      let listTy = tyList itemTy
      poly (tyFun itemTy listTy) []

  | HPrim.Not -> mono (tyFun tyBool tyBool)

  | HPrim.Exit ->
      let resultTy = meta 1
      poly (tyFun tyInt resultTy) []

  | HPrim.Assert -> mono (tyFun tyBool tyUnit)

  | HPrim.Box ->
      let itemTy = meta 1
      poly (tyFun itemTy tyObj) []

  | HPrim.Unbox ->
      let itemTy = meta 1
      poly (tyFun tyObj itemTy) []

  | HPrim.Char ->
      // FIXME: `char` can take non-int types.
      mono (tyFun tyInt tyChar)

  | HPrim.ToInt flavor ->
      let toIntTy = meta 1
      let resultTy = AppTy(IntTyCtor flavor, [])
      poly (tyFun toIntTy resultTy) [ ToIntTrait toIntTy ]

  | HPrim.ToFloat flavor ->
      let srcTy = meta 1
      let resultTy = AppTy(FloatTyCtor flavor, [])
      poly (tyFun srcTy resultTy) [ ToFloatTrait srcTy ]

  | HPrim.String ->
      let toStrTy = meta 1
      poly (tyFun toStrTy tyStr) [ ToStringTrait toStrTy ]

  | HPrim.StrLength -> mono (tyFun tyStr tyInt)

  | HPrim.InRegion -> mono (tyFun (tyFun tyUnit tyInt) tyInt)

  | HPrim.Printfn
  | HPrim.NativeFun ->
      // Incorrect use of this primitive is handled as error before instantiating its type.
      failwith "NEVER"

  | HPrim.NativeCast ->
      let srcTy = meta 1
      let destTy = meta 2
      poly (tyFun srcTy destTy) [ PtrTrait srcTy; PtrTrait destTy ]

// -----------------------------------------------
// Patterns (HIR)
// -----------------------------------------------

let rec patExtract (pat: HPat): Ty * Loc =
  match pat with
  | HLitPat (lit, a) -> litToTy lit, a
  | HNilPat (itemTy, a) -> tyList itemTy, a
  | HNonePat (itemTy, a) -> tyList itemTy, a
  | HSomePat (itemTy, a) -> tyList itemTy, a
  | HDiscardPat (ty, a) -> ty, a
  | HRefPat (_, ty, a) -> ty, a
  | HVariantPat (_, ty, a) -> ty, a
  | HNavPat (_, _, ty, a) -> ty, a
  | HCallPat (_, _, ty, a) -> ty, a
  | HConsPat (_, _, itemTy, a) -> tyList itemTy, a
  | HTuplePat (_, ty, a) -> ty, a
  | HBoxPat (_, a) -> tyObj, a
  | HAsPat (pat, _, a) ->
      let ty, _ = patExtract pat
      ty, a
  | HAnnoPat (_, ty, a) -> ty, a
  | HOrPat (_, _, ty, a) -> ty, a

let patMap (f: Ty -> Ty) (g: Loc -> Loc) (pat: HPat): HPat =
  let rec go pat =
    match pat with
    | HLitPat (lit, a) -> HLitPat(lit, g a)
    | HNilPat (itemTy, a) -> HNilPat(f itemTy, g a)
    | HNonePat (itemTy, a) -> HNonePat(f itemTy, g a)
    | HSomePat (itemTy, a) -> HSomePat(f itemTy, g a)
    | HDiscardPat (ty, a) -> HDiscardPat(f ty, g a)
    | HRefPat (serial, ty, a) -> HRefPat(serial, f ty, g a)
    | HVariantPat (variantSerial, ty, a) -> HVariantPat(variantSerial, f ty, g a)
    | HNavPat (l, r, ty, a) -> HNavPat(go l, r, f ty, g a)
    | HCallPat (callee, args, ty, a) -> HCallPat(go callee, List.map go args, f ty, g a)
    | HConsPat (l, r, itemTy, a) -> HConsPat(go l, go r, f itemTy, g a)
    | HTuplePat (itemPats, ty, a) -> HTuplePat(List.map go itemPats, f ty, g a)
    | HBoxPat (itemPat, a) -> HBoxPat(go itemPat, g a)
    | HAsPat (pat, serial, a) -> HAsPat(go pat, serial, g a)
    | HAnnoPat (pat, ty, a) -> HAnnoPat(go pat, f ty, g a)
    | HOrPat (first, second, ty, a) -> HOrPat(go first, go second, f ty, g a)

  go pat

let patToTy pat = pat |> patExtract |> fst

let patToLoc pat =
  let _, loc = patExtract pat
  loc

/// Converts a pattern in disjunctive normal form.
/// E.g. `A, [B | C]` → `(A | [B]), (A | [C])`
let patNormalize pat =
  let rec go pat =
    match pat with
    | HLitPat _
    | HDiscardPat _
    | HRefPat _
    | HVariantPat _
    | HNilPat _
    | HNonePat _
    | HSomePat _ -> [ pat ]
    | HNavPat (l, r, ty, loc) -> go l |> List.map (fun l -> HNavPat(l, r, ty, loc))
    | HCallPat (callee, [ arg ], ty, loc) ->
        go callee
        |> List.collect (fun callee ->
             go arg
             |> List.map (fun arg -> HCallPat(callee, [ arg ], ty, loc)))
    | HConsPat (l, r, ty, loc) ->
        go l
        |> List.collect (fun l ->
             go r
             |> List.map (fun r -> HConsPat(l, r, ty, loc)))
    | HTuplePat (itemPats, ty, loc) ->
        let rec gogo itemPats =
          match itemPats with
          | [] -> [ [] ]
          | itemPat :: itemPats ->
              let itemPat = go itemPat
              gogo itemPats
              |> List.collect (fun itemPats ->
                   itemPat
                   |> List.map (fun itemPat -> itemPat :: itemPats))

        gogo itemPats
        |> List.map (fun itemPats -> HTuplePat(itemPats, ty, loc))

    | HBoxPat (itemPat, loc) ->
        go itemPat
        |> List.map (fun itemPat -> HBoxPat(itemPat, loc))

    | HAsPat (bodyPat, varSerial, loc) ->
        go bodyPat
        |> List.map (fun bodyPat -> HAsPat(bodyPat, varSerial, loc))

    | HAnnoPat (pat, annoTy, loc) ->
        go pat
        |> List.map (fun pat -> HAnnoPat(pat, annoTy, loc))

    | HOrPat (first, second, _, _) -> List.append (go first) (go second)
    | HCallPat _ -> failwith "Unimpl"

  go pat

// -----------------------------------------------
// Expressions (HIR)
// -----------------------------------------------

let hxTrue loc = HLitExpr(litTrue, loc)

let hxFalse loc = HLitExpr(litFalse, loc)

let hxApp f x ty loc = HInfExpr(InfOp.App, [ f; x ], ty, loc)

let hxAnno expr ty loc = HInfExpr(InfOp.Anno, [ expr ], ty, loc)

let hxSemi items loc =
  HInfExpr(InfOp.Semi, items, exprToTy (List.last items), loc)

let hxCallProc callee args resultTy loc =
  HInfExpr(InfOp.CallProc, callee :: args, resultTy, loc)

let hxCallClosure callee args resultTy loc =
  HInfExpr(InfOp.CallClosure, callee :: args, resultTy, loc)

let hxTuple items loc =
  HInfExpr(InfOp.Tuple, items, tyTuple (List.map exprToTy items), loc)

let hxUnit loc = hxTuple [] loc

let hxNil itemTy loc = HPrimExpr(HPrim.Nil, tyList itemTy, loc)

let hxIsUnitLit expr =
  match expr with
  | HInfExpr (InfOp.Tuple, [], _, _) -> true
  | _ -> false

let hxIsAlwaysTrue expr =
  match expr with
  | HLitExpr (BoolLit true, _) -> true
  | _ -> false

let exprExtract (expr: HExpr): Ty * Loc =
  match expr with
  | HLitExpr (lit, a) -> litToTy lit, a
  | HRefExpr (_, ty, a) -> ty, a
  | HFunExpr (_, ty, a) -> ty, a
  | HVariantExpr (_, ty, a) -> ty, a
  | HPrimExpr (_, ty, a) -> ty, a
  | HRecordExpr (_, _, ty, a) -> ty, a
  | HMatchExpr (_, _, ty, a) -> ty, a
  | HNavExpr (_, _, ty, a) -> ty, a
  | HInfExpr (_, _, ty, a) -> ty, a
  | HLetValExpr (_, _, _, _, ty, a) -> ty, a
  | HLetFunExpr (_, _, _, _, _, _, ty, a) -> ty, a
  | HTyDeclExpr (_, _, _, _, a) -> tyUnit, a
  | HOpenExpr (_, a) -> tyUnit, a
  | HModuleExpr (_, _, _, a) -> tyUnit, a

let exprMap (f: Ty -> Ty) (g: Loc -> Loc) (expr: HExpr): HExpr =
  let goPat pat = patMap f g pat

  let rec go expr =
    match expr with
    | HLitExpr (lit, a) -> HLitExpr(lit, g a)
    | HRefExpr (serial, ty, a) -> HRefExpr(serial, f ty, g a)
    | HFunExpr (serial, ty, a) -> HFunExpr(serial, f ty, g a)
    | HVariantExpr (serial, ty, a) -> HVariantExpr(serial, f ty, g a)
    | HPrimExpr (prim, ty, a) -> HPrimExpr(prim, f ty, g a)

    | HRecordExpr (baseOpt, fields, ty, a) ->
        let baseOpt = baseOpt |> Option.map go

        let fields =
          fields
          |> List.map (fun (name, init, a) -> name, go init, g a)

        HRecordExpr(baseOpt, fields, f ty, g a)

    | HMatchExpr (cond, arms, ty, a) ->
        let arms =
          arms
          |> List.map (fun (pat, guard, body) -> goPat pat, go guard, go body)

        HMatchExpr(go cond, arms, f ty, g a)
    | HNavExpr (sub, mes, ty, a) -> HNavExpr(go sub, mes, f ty, g a)
    | HInfExpr (infOp, args, resultTy, a) -> HInfExpr(infOp, List.map go args, f resultTy, g a)
    | HLetValExpr (vis, pat, init, next, ty, a) -> HLetValExpr(vis, goPat pat, go init, go next, f ty, g a)
    | HLetFunExpr (serial, vis, isMainFun, args, body, next, ty, a) ->
        HLetFunExpr(serial, vis, isMainFun, List.map goPat args, go body, go next, f ty, g a)
    | HTyDeclExpr (serial, vis, tyArgs, tyDef, a) -> HTyDeclExpr(serial, vis, tyArgs, tyDef, g a)
    | HOpenExpr (path, a) -> HOpenExpr(path, g a)
    | HModuleExpr (name, body, next, a) -> HModuleExpr(name, go body, go next, g a)

  go expr

let exprToTy expr =
  let ty, _ = exprExtract expr
  ty

let exprToLoc expr =
  let _, loc = exprExtract expr
  loc

/// Insert the second expression to the bottom of the first expression.
/// This is bad way because of variable capturing issues and program size/depth issue.
let spliceExpr firstExpr secondExpr =
  let rec go expr =
    match expr with
    | HLetValExpr (vis, pat, init, next, ty, loc) ->
        let next = go next
        HLetValExpr(vis, pat, init, next, ty, loc)
    | HLetFunExpr (serial, vis, isMainFun, args, body, next, ty, loc) ->
        let next = go next
        HLetFunExpr(serial, vis, isMainFun, args, body, next, ty, loc)
    | HInfExpr (InfOp.Semi, exprs, ty, loc) ->
        let rec goLast exprs =
          match exprs with
          | [] -> [ secondExpr ]
          | [ lastExpr ] -> [ go lastExpr ]
          | x :: xs -> x :: goLast xs

        let exprs = goLast exprs
        HInfExpr(InfOp.Semi, exprs, ty, loc)
    | HModuleExpr (name, body, next, loc) ->
        let next = go next
        HModuleExpr(name, body, next, loc)
    | _ -> hxSemi [ expr; secondExpr ] noLoc

  go firstExpr

// -----------------------------------------------
// Print Formats
// -----------------------------------------------

let analyzeFormat (format: string) =
  let rec go i =
    if i >= format.Length then
      tyUnit
    else if i + 1 < format.Length && format.[i] = '%' then
      match format.[i + 1] with
      | 's' -> tyFun tyStr (go (i + 2))
      | 'd' -> tyFun tyInt (go (i + 2))
      | 'f' -> tyFun tyFloat (go (i + 2))
      | 'c' -> tyFun tyChar (go (i + 2))
      | _ -> go (i + 2)
    else
      go (i + 1)

  tyFun tyStr (go 0)

// -----------------------------------------------
// Logs
// -----------------------------------------------

let nameResLogToString log =
  match log with
  | UndefinedValueError name ->
      "The name '"
      + name
      + "' here should denote to some value; but not found."

  | UndefinedTyError name ->
      "The name '"
      + name
      + "' here should denote to some type; but not found."

  | FunPatError name ->
      "The name '"
      + name
      + "' here is a function, which can't be used as a pattern."

  | TyArityError ("_", _, _) -> "'_' can't have type arguments."

  | TyArityError (name, actual, expected) ->
      "Type arity mismatch. The type '"
      + name
      + "' expected "
      + string expected
      + " arguments; but given "
      + string actual
      + "."

  | ModuleUsedAsTyError name ->
      "The name '"
      + name
      + "' here should denote to some type; but is a module name."

  | OtherNameResLog msg -> msg

let logToString tyDisplay loc log =
  let loc = loc |> locToString

  match log with
  | Log.NameResLog log -> loc + " " + nameResLogToString log

  | Log.TyUnify (TyUnifyLog.SelfRec, _, _, lTy, rTy) ->
      sprintf "%s Recursive type occurred while unifying '%s' to '%s'." loc (tyDisplay lTy) (tyDisplay rTy)

  | Log.TyUnify (TyUnifyLog.Mismatch, lRootTy, rRootTy, lTy, rTy) ->
      sprintf
        "%s Type mismatch: '%s' <> '%s'. Occurred while unifying '%s' to '%s'."
        loc
        (tyDisplay lTy)
        (tyDisplay rTy)
        (tyDisplay lRootTy)
        (tyDisplay rRootTy)

  | Log.TyBoundError (AddTrait ty) -> sprintf "%s No support (+) for '%s' yet" loc (tyDisplay ty)

  | Log.TyBoundError (EqTrait ty) -> sprintf "%s No support equality for '%s' yet" loc (tyDisplay ty)

  | Log.TyBoundError (CmpTrait ty) -> sprintf "%s No support comparison for '%s' yet" loc (tyDisplay ty)

  | Log.TyBoundError (IndexTrait (lTy, rTy, _)) ->
      sprintf "%s No support indexing operation: lhs = '%s', rhs = '%s'." loc (tyDisplay lTy) (tyDisplay rTy)

  | Log.TyBoundError (IsIntTrait ty) -> sprintf "%s Expected int or some integer type but was '%s'" loc (tyDisplay ty)

  | Log.TyBoundError (IsNumberTrait ty) -> sprintf "%s Expected int or float type but was '%s'" loc (tyDisplay ty)

  | Log.TyBoundError (ToIntTrait ty) -> sprintf "%s Can't convert to integer from '%s'" loc (tyDisplay ty)

  | Log.TyBoundError (ToFloatTrait ty) -> sprintf "%s Can't convert to float from '%s'" loc (tyDisplay ty)

  | Log.TyBoundError (ToStringTrait ty) -> sprintf "%s Can't convert to string from '%s'" loc (tyDisplay ty)

  | Log.TyBoundError (PtrTrait ty) -> sprintf "%s Expected a pointer type but was '%s'" loc (tyDisplay ty)

  | Log.RedundantFieldError (recordName, fieldName) ->
      sprintf "%s The field '%s' is redundant for record '%s'." loc fieldName recordName

  | Log.MissingFieldsError (recordName, fieldNames) ->
      let fields = fieldNames |> strJoin ", "

      sprintf "%s Record '%s' must have fields: '%s'." loc recordName fields

  | Log.Error msg -> loc + " " + msg
