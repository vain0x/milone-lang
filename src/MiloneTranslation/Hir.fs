/// # Hir
///
/// Provides types and functions for high-level intermediate representation (HIR).
///
/// HIR is functional-style. Similar to milone-lang's syntax.
module rec MiloneTranslation.Hir

open MiloneShared.SharedTypes
open MiloneShared.TypeFloat
open MiloneShared.TypeIntegers
open MiloneShared.Util
open MiloneStd.StdMap

module S = MiloneStd.StdString

// -----------------------------------------------
// HIR types
// -----------------------------------------------

/// Serial number of types.
type TySerial = Serial

/// Serial number of variables.
[<Struct; NoComparison>]
type VarSerial = VarSerial of Serial

/// Serial number of functions.
[<Struct; NoComparison>]
type FunSerial = FunSerial of Serial

/// Serial number of variants.
[<Struct; NoComparison>]
type VariantSerial = VariantSerial of Serial

/// Type constructor.
[<NoEquality; NoComparison>]
type Tk =
  | IntTk of intFlavor: IntFlavor
  | FloatTk of floatFlavor: FloatFlavor
  | BoolTk
  | CharTk
  | StrTk
  | ObjTk

  /// Ty args must be `[s; t]`.
  | FunTk

  | TupleTk

  /// Ty args must be `[t]`.
  | OptionTk
  | ListTk

  // FFI types.
  | VoidTk
  | NativePtrTk of nativePtrIsMut: IsMut
  | NativeFunTk
  | NativeTypeTk of cCode: string

  // Nominal types.
  | MetaTk of metaTy: TySerial * metaLoc: Loc
  | UnionTk of unionTy: TySerial
  | RecordTk of recordTy: TySerial

/// Type of expressions.
[<Struct; NoEquality; NoComparison>]
type Ty =
  /// Type application.
  | Ty of Tk * tyArgs: Ty list

/// Potentially polymorphic type.
[<Struct; NoEquality; NoComparison>]
type TyScheme = TyScheme of tyVars: TySerial list * Ty

/// Type definition.
[<NoEquality; NoComparison>]
type TyDef =
  /// Bound type variable.
  | MetaTyDef of Ty

  | UnionTyDef of Ident * tyArgs: TySerial list * VariantSerial list * Loc

  | RecordTyDef of Ident * fields: (Ident * Ty * Loc) list * IsCRepr * Loc

/// Definition of named value in HIR.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type VarDef =
  { Name: Ident
    IsStatic: IsStatic
    Linkage: Linkage

    /// Remark: After monomorphization, variables occur in multiple monomorphized instances
    ///         and Ty field can contain undefined type variables. It shouldn't be used.
    Ty: Ty

    Loc: Loc }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type FunDef =
  { Name: Ident
    Arity: Arity
    Ty: TyScheme
    Abi: FunAbi
    Linkage: Linkage
    Prefix: string list
    Loc: Loc }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type VariantDef =
  { Name: Ident
    UnionTySerial: TySerial

    /// Whether this is the only variant of the union.
    IsNewtype: bool

    HasPayload: bool
    PayloadTy: Ty
    Loc: Loc }

/// Kind of HNodePat.
[<NoEquality; NoComparison>]
type HPatKind =
  /// `[]`.
  | HNilPN

  /// `p1 :: p2`.
  | HConsPN

  | HNonePN

  /// `Some p1`.
  | HSomeAppPN

  /// `Variant p1`.
  | HVariantAppPN of variantApp: VariantSerial

  /// `p1, p2, ..., pN` or `()`.
  | HTuplePN

  /// Used to dereference a box inside of pattern matching.
  ///
  /// To match a value `v: obj` with box pattern `box p: T`,
  /// match `unbox v: T` with `p: T`.
  ///
  /// This is only generated internally in AutoBoxing.
  /// Not a part of F# nor milone-lang syntax.
  /// Unlike `:? T`, unboxing is unchecked.
  | HBoxPN

  /// Generated after compile error occurred while processing a pattern.
  | HAbortPN

/// Pattern in HIR.
[<NoEquality; NoComparison>]
type HPat =
  | HLitPat of Lit * Loc

  /// `_`.
  | HDiscardPat of Ty * Loc

  /// Variable pattern.
  | HVarPat of VarSerial * Ty * Loc

  /// Variant name pattern.
  | HVariantPat of VariantSerial * Ty * Loc

  | HNodePat of HPatKind * HPat list * Ty * Loc

  | HAsPat of HPat * VarSerial * Loc

  /// Disjunction.
  | HOrPat of HPat * HPat * Loc

/// Primitive in HIR.
[<RequireQualifiedAccess; Struct; NoComparison>]
type HPrim =
  // operator:
  | Not
  | Add
  | Sub
  | Mul
  | Div
  | Modulo
  | BitAnd
  | BitOr
  | BitXor
  | LeftShift
  | RightShift
  | Equal
  | Less
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
  | NativeCast
  | PtrRead
  | PtrWrite

[<NoEquality; NoComparison>]
type HExprKind =
  | HAbortEN

  /// `-x`.
  | HMinusEN

  | HAppEN

  /// `s.[i]`
  | HIndexEN

  /// `s.[l .. r]`
  | HSliceEN

  /// Direct call to procedure or primitive.
  | HCallProcEN

  /// Indirect call to closure.
  | HCallClosureEN

  /// Direct call to current procedure at the end of function (i.e. tail-call).
  | HCallTailRecEN

  /// Direct call to native fun.
  | HCallNativeEN of funName: string

  /// Tuple constructor, e.g. `x, y, z`.
  | HTupleEN

  /// Closure constructor.
  | HClosureEN

  /// Record creation.
  ///
  /// Unlike record expr, it's guaranteed that
  /// all of fields are specified in order of declaration.
  | HRecordEN

  /// Gets i'th field of record.
  | HRecordItemEN of index: int

  /// Use function as function pointer.
  | HNativeFunEN of FunSerial

  /// Embed some C expression to output.
  | HNativeExprEN of nativeExprCode: string

  /// Embed some C statement to output.
  | HNativeStmtEN of nativeStmtCode: string

  /// Embed some C toplevel codes to output.
  | HNativeDeclEN of nativeDeclCode: string

  /// Size of type.
  | HSizeOfValEN

/// Expression in HIR.
[<NoEquality; NoComparison>]
type HExpr =
  | HLitExpr of Lit * Loc

  /// Name of variable.
  | HVarExpr of VarSerial * Ty * Loc

  /// Name of function.
  | HFunExpr of FunSerial * Ty * tyArgs: Ty list * Loc

  /// Name of variant.
  | HVariantExpr of VariantSerial * Ty * Loc

  | HPrimExpr of HPrim * Ty * Loc

  | HRecordExpr of HExpr option * fields: (Ident * HExpr * Loc) list * Ty * Loc

  /// arms: (pat, guard, body). Guard is `true` if omit.
  | HMatchExpr of cond: HExpr * arms: (HPat * HExpr * HExpr) list * Ty * Loc

  /// E.g. `List.isEmpty`, `str.Length`
  | HNavExpr of HExpr * Ident * Ty * Loc

  /// Some built-in operation.
  | HNodeExpr of HExprKind * HExpr list * Ty * Loc

  /// Evaluate a list of expressions and returns the last, e.g. `x1; x2; ...; y`.
  | HBlockExpr of HExpr list * HExpr

  | HLetValExpr of pat: HPat * init: HExpr * next: HExpr * Ty * Loc
  | HLetFunExpr of FunSerial * args: HPat list * body: HExpr * next: HExpr * Ty * Loc

type VarMap = TreeMap<VarSerial, VarDef>
type VarNameMap = TreeMap<VarSerial, Ident>

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type HModule =
  { DocId: DocId

    /// Non-static variables.
    Vars: VarMap

    Stmts: HExpr list }

/// Module. Variable info is reduced.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type HModule2 =
  { DocId: DocId

    /// Non-static variables.
    Vars: VarNameMap

    Stmts: HExpr list }

/// HIR program. (project name, module name, decls) list.
type HProgram = HModule list

// -----------------------------------------------
// HirCtx
// -----------------------------------------------

/// Context of HIR program.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type HirCtx =
  { /// Next serial number.
    Serial: Serial

    Vars: TreeMap<VarSerial, VarDef>
    Funs: TreeMap<FunSerial, FunDef>
    Variants: TreeMap<VariantSerial, VariantDef>

    MainFunOpt: FunSerial option

    Tys: TreeMap<TySerial, TyDef> }

// -----------------------------------------------
// Types (HIR/MIR)
// -----------------------------------------------

let tyInt = Ty(IntTk(IntFlavor(Signed, I32)), [])

let tyNativeInt = Ty(IntTk(IntFlavor(Signed, IPtr)), [])

let tyBool = Ty(BoolTk, [])

let tyFloat = Ty(FloatTk F64, [])

let tyChar = Ty(CharTk, [])

let tyStr = Ty(StrTk, [])

let tyObj = Ty(ObjTk, [])

let tyTuple tys = Ty(TupleTk, tys)

let tyOption ty = Ty(OptionTk, [ ty ])

let tyList ty = Ty(ListTk, [ ty ])

let tyFun sourceTy targetTy = Ty(FunTk, [ sourceTy; targetTy ])

let tyConstPtr itemTy = Ty(NativePtrTk IsConst, [ itemTy ])

let tyNativePtr itemTy = Ty(NativePtrTk IsMut, [ itemTy ])

let tyNativeFun paramTys resultTy =
  Ty(NativeFunTk, List.append paramTys [ resultTy ])

let tyUnit = tyTuple []

let tyMeta serial loc = Ty(MetaTk(serial, loc), [])

let tyUnion tySerial tyArgs = Ty(UnionTk tySerial, tyArgs)

let tyRecord tySerial = Ty(RecordTk tySerial, [])

// -----------------------------------------------
// Type definitions (HIR)
// -----------------------------------------------

let tyDefToName tyDef =
  match tyDef with
  | MetaTyDef _ -> "{bound}"
  | UnionTyDef (name, _, _, _) -> name
  | RecordTyDef (name, _, _, _) -> name

// -----------------------------------------------
// Variable definitions (HIR)
// -----------------------------------------------

let varSerialToInt (VarSerial serial) = serial

let varSerialCompare l r =
  compare (varSerialToInt l) (varSerialToInt r)

let funSerialToInt (FunSerial serial) = serial

let funSerialCompare l r =
  compare (funSerialToInt l) (funSerialToInt r)

let variantSerialToInt (VariantSerial serial) = serial

let variantSerialCompare l r =
  compare (variantSerialToInt l) (variantSerialToInt r)

// -----------------------------------------------
// Literals
// -----------------------------------------------

let litToTy (lit: Lit) : Ty =
  match lit with
  | BoolLit _ -> tyBool
  | IntLit _ -> tyInt
  | IntLitWithFlavor (_, flavor) -> Ty(IntTk flavor, [])
  | FloatLit _ -> tyFloat
  | CharLit _ -> tyChar
  | StrLit _ -> tyStr

// -----------------------------------------------
// Patterns (HIR)
// -----------------------------------------------

let hpAbort ty loc = HNodePat(HAbortPN, [], ty, loc)

let hpVar varSerial ty loc = HVarPat(varSerial, ty, loc)

let hpVariantApp variantSerial payloadPat ty loc =
  HNodePat(HVariantAppPN variantSerial, [ payloadPat ], ty, loc)

let hpTuple itemPats loc =
  let tupleTy = itemPats |> List.map patToTy |> tyTuple
  HNodePat(HTuplePN, itemPats, tupleTy, loc)

let patExtract (pat: HPat) : Ty * Loc =
  match pat with
  | HLitPat (lit, a) -> litToTy lit, a
  | HDiscardPat (ty, a) -> ty, a
  | HVarPat (_, ty, a) -> ty, a
  | HVariantPat (_, ty, a) -> ty, a

  | HNodePat (_, _, ty, a) -> ty, a
  | HAsPat (bodyPat, _, a) -> patToTy bodyPat, a
  | HOrPat (l, _, a) -> patToTy l, a

let patToTy pat = pat |> patExtract |> fst

let patToLoc pat = pat |> patExtract |> snd

let patFold (onVar: 'S -> VarSerial -> Ty -> 'S) (state: 'S) (pat: HPat) : 'S =
  let rec go state pat =
    match pat with
    | HLitPat _
    | HDiscardPat _
    | HVariantPat _ -> state

    | HVarPat (serial, ty, _) -> onVar state serial ty
    | HNodePat (_, args, _, _) -> List.fold go state args
    | HAsPat (bodyPat, serial, _) -> go (onVar state serial (patToTy bodyPat)) bodyPat
    | HOrPat (l, r, _) -> go (go state l) r

  go state pat

let patMap (f: Ty -> Ty) (pat: HPat) : HPat =
  let rec go pat =
    match pat with
    | HLitPat (lit, a) -> HLitPat(lit, a)
    | HDiscardPat (ty, a) -> HDiscardPat(f ty, a)
    | HVarPat (serial, ty, a) -> HVarPat(serial, f ty, a)
    | HVariantPat (serial, ty, a) -> HVariantPat(serial, f ty, a)

    | HNodePat (kind, args, ty, a) -> HNodePat(kind, List.map go args, f ty, a)
    | HAsPat (bodyPat, serial, a) -> HAsPat(go bodyPat, serial, a)
    | HOrPat (l, r, a) -> HOrPat(go l, go r, a)

  go pat

/// Converts a pattern in disjunctive normal form.
/// E.g. `A, [B | C]` → `(A | [B]), (A | [C])`
let patNormalize pat =
  let rec go pat =
    match pat with
    | HLitPat _
    | HDiscardPat _
    | HVarPat _
    | HVariantPat _ -> [ pat ]

    | HNodePat (kind, argPats, ty, loc) ->
      argPats
      |> doNormalizePats
      |> List.map (fun itemPats -> HNodePat(kind, itemPats, ty, loc))

    | HAsPat (bodyPat, serial, loc) ->
      go bodyPat
      |> List.map (fun bodyPat -> HAsPat(bodyPat, serial, loc))

    | HOrPat (l, r, _) -> List.append (go l) (go r)

  go pat

let private doNormalizePats pats =
  match pats with
  | [] -> [ [] ]

  | headPat :: tailPats ->
    let headPats = patNormalize headPat

    doNormalizePats tailPats
    |> List.collect (fun tailPats ->
      headPats
      |> List.map (fun headPat -> headPat :: tailPats))

/// Gets whether a pattern is clearly exhaustive, that is,
/// pattern matching on it always succeeds (assuming type check is passing).
let patIsClearlyExhaustive isNewtypeVariant pat =
  let rec go pat =
    match pat with
    | HLitPat _ -> false

    | HDiscardPat _
    | HVarPat _ -> true

    | HVariantPat (variantSerial, _, _) -> isNewtypeVariant variantSerial

    | HNodePat (kind, argPats, _, _) ->
      match kind, argPats with
      | HVariantAppPN variantSerial, [ payloadPat ] -> isNewtypeVariant variantSerial && go payloadPat

      | HAbortPN, _ -> true

      | HNilPN, _
      | HConsPN, _
      | HNonePN, _
      | HSomeAppPN, _
      | HVariantAppPN _, _ -> false

      | HTuplePN, _
      | HBoxPN, _ -> argPats |> List.forall go

    | HAsPat (bodyPat, _, _) -> go bodyPat
    | HOrPat (l, r, _) -> go l || go r

  go pat

// -----------------------------------------------
// Expressions (HIR)
// -----------------------------------------------

let hxTrue loc = HLitExpr(BoolLit true, loc)

let hxApp f x ty loc = HNodeExpr(HAppEN, [ f; x ], ty, loc)

let hxSemi items loc =
  match splitLast items with
  | Some (stmts, last) -> HBlockExpr(stmts, last)
  | None -> HNodeExpr(HTupleEN, [], tyUnit, loc)

let hxCallProc callee args resultTy loc =
  HNodeExpr(HCallProcEN, callee :: args, resultTy, loc)

let hxCallClosure callee args resultTy loc =
  HNodeExpr(HCallClosureEN, callee :: args, resultTy, loc)

let hxTuple items loc =
  HNodeExpr(HTupleEN, items, tyTuple (List.map exprToTy items), loc)

let hxUnit loc = hxTuple [] loc

let hxIsUnitLit expr =
  match expr with
  | HNodeExpr (HTupleEN, [], _, _) -> true
  | _ -> false

let hxIsAlwaysTrue expr =
  match expr with
  | HLitExpr (BoolLit true, _) -> true
  | _ -> false

let exprExtract (expr: HExpr) : Ty * Loc =
  match expr with
  | HLitExpr (lit, a) -> litToTy lit, a
  | HVarExpr (_, ty, a) -> ty, a
  | HFunExpr (_, ty, _, a) -> ty, a
  | HVariantExpr (_, ty, a) -> ty, a
  | HPrimExpr (_, ty, a) -> ty, a
  | HRecordExpr (_, _, ty, a) -> ty, a
  | HMatchExpr (_, _, ty, a) -> ty, a
  | HNavExpr (_, _, ty, a) -> ty, a
  | HNodeExpr (_, _, ty, a) -> ty, a
  | HBlockExpr (_, last) -> exprExtract last
  | HLetValExpr (_, _, _, ty, a) -> ty, a
  | HLetFunExpr (_, _, _, _, ty, a) -> ty, a

let hArmMap (onPat: HPat -> HPat) (onExpr: HExpr -> HExpr) (arm: HPat * HExpr * HExpr) =
  let pat, guard, body = arm
  onPat pat, onExpr guard, onExpr body

let exprMap (f: Ty -> Ty) (expr: HExpr) : HExpr =
  let goPat pat = patMap f pat

  let rec go expr =
    match expr with
    | HLitExpr (lit, a) -> HLitExpr(lit, a)
    | HVarExpr (serial, ty, a) -> HVarExpr(serial, f ty, a)
    | HFunExpr (serial, ty, tyArgs, a) -> HFunExpr(serial, f ty, List.map f tyArgs, a)
    | HVariantExpr (serial, ty, a) -> HVariantExpr(serial, f ty, a)
    | HPrimExpr (prim, ty, a) -> HPrimExpr(prim, f ty, a)

    | HRecordExpr (baseOpt, fields, ty, a) ->
      let baseOpt = baseOpt |> Option.map go

      let fields =
        fields
        |> List.map (fun (name, init, a) -> name, go init, a)

      HRecordExpr(baseOpt, fields, f ty, a)

    | HMatchExpr (cond, arms, ty, a) ->
      let arms = arms |> List.map (hArmMap goPat go)
      HMatchExpr(go cond, arms, f ty, a)
    | HNavExpr (sub, mes, ty, a) -> HNavExpr(go sub, mes, f ty, a)
    | HNodeExpr (kind, args, resultTy, a) -> HNodeExpr(kind, List.map go args, f resultTy, a)
    | HBlockExpr (stmts, last) -> HBlockExpr(List.map go stmts, go last)
    | HLetValExpr (pat, init, next, ty, a) -> HLetValExpr(goPat pat, go init, go next, f ty, a)
    | HLetFunExpr (serial, args, body, next, ty, a) ->
      HLetFunExpr(serial, List.map goPat args, go body, go next, f ty, a)

  go expr

let exprToTy expr =
  let ty, _ = exprExtract expr
  ty

let exprToLoc expr =
  let _, loc = exprExtract expr
  loc

// -----------------------------------------------
// HProgram
// -----------------------------------------------

let emptyVars: TreeMap<VarSerial, VarDef> = TMap.empty varSerialCompare

module HProgram =
  let mapExpr (f: HExpr -> HExpr) (program: HProgram) : HProgram =
    program
    |> List.map (fun (m: HModule) -> { m with Stmts = m.Stmts |> List.map f })

  let foldExpr (f: 'S -> HExpr -> 'S) (state: 'S) (program: HProgram) : 'S =
    program
    |> List.fold (fun (state: 'S) (m: HModule) -> m.Stmts |> List.fold f state) state

// -----------------------------------------------
// Tk
// -----------------------------------------------

let private tkEncode tk : int =
  let pair l r =
    assert (l < 30 && r < 10000000)
    l * 10000000 + r

  let just x = pair x 0

  let isMutToInt isMut =
    match isMut with
    | IsConst -> 1
    | IsMut -> 2

  match tk with
  | IntTk flavor -> pair 1 (intFlavorToOrdinary flavor)
  | FloatTk flavor -> pair 2 (floatFlavorToOrdinary flavor)
  | BoolTk -> just 3
  | CharTk -> just 4
  | StrTk -> just 5
  | ObjTk -> just 6
  | FunTk -> just 7
  | TupleTk -> just 8
  | OptionTk -> just 9
  | ListTk -> just 10

  | VoidTk -> just 11
  | NativePtrTk isMut -> pair 12 (isMutToInt isMut)
  | NativeFunTk -> just 13

  | MetaTk (tySerial, _) -> pair 20 tySerial
  | UnionTk tySerial -> pair 22 tySerial
  | RecordTk tySerial -> pair 23 tySerial

  | NativeTypeTk _ -> unreachable ()

let tkCompare l r : int =
  match l, r with
  | NativeTypeTk l, NativeTypeTk r -> compare l r

  | NativeTypeTk _, _ -> -1
  | _, NativeTypeTk _ -> 1

  | _ -> tkEncode l - tkEncode r

let tkEqual l r : bool = tkCompare l r = 0

let tkDisplay getTyName tk =
  match tk with
  | IntTk flavor -> fsharpIntegerTyName flavor
  | FloatTk flavor -> fsharpFloatTyName flavor
  | BoolTk -> "bool"
  | CharTk -> "char"
  | StrTk -> "string"
  | ObjTk -> "obj"
  | FunTk -> "fun"
  | TupleTk -> "tuple"
  | OptionTk -> "option"
  | ListTk -> "list"
  | VoidTk -> "void"
  | NativePtrTk IsMut -> "nativeptr"
  | NativePtrTk IsConst -> "__constptr"
  | NativeFunTk -> "__nativeFun"
  | NativeTypeTk _ -> "__nativeType"
  | MetaTk (tySerial, _) -> getTyName tySerial
  | RecordTk tySerial -> getTyName tySerial
  | UnionTk tySerial -> getTyName tySerial

// -----------------------------------------------
// Types (HIR/MIR)
// -----------------------------------------------

let noTy: Ty = Ty(NativeTypeTk "__no_use", [])

let tyIsUnit ty =
  match ty with
  | Ty (TupleTk, []) -> true
  | _ -> false

let tyIsFun ty =
  match ty with
  | Ty (FunTk, _) -> true
  | _ -> false

let tyCompare l r =
  match l, r with
  | Ty (lTk, lTyArgs), Ty (rTk, rTyArgs) ->
    let c = tkCompare lTk rTk

    if c <> 0 then
      c
    else
      listCompare tyCompare lTyArgs rTyArgs

let tyEqual l r = tyCompare l r = 0

/// Gets if the specified type variable doesn't appear in a type.
let private tyIsFreeIn ty tySerial : bool =
  let rec go ty =
    match ty with
    | Ty (MetaTk (s, _), _) -> s <> tySerial

    | Ty (_, []) -> true

    | Ty (tk, ty :: tys) -> go ty && go (Ty(tk, tys))

  go ty

/// Gets if the type is monomorphic.
/// Assume all bound type variables are substituted.
let tyIsMonomorphic ty : bool =
  let rec go tys =
    match tys with
    | [] -> true

    | Ty (MetaTk _, _) :: _ -> false

    | Ty (_, tys1) :: tys2 -> go tys1 && go tys2

  go [ ty ]

/// Gets a list of type variables.
/// Assume all bound type variables are substituted.
let tyCollectFreeVars ty =
  let rec go fvAcc tys =
    match tys with
    | [] -> fvAcc

    | Ty (MetaTk (serial, _), _) :: tys ->
      let acc = serial :: fvAcc
      go acc tys

    | Ty (_, []) :: tys -> go fvAcc tys

    | Ty (_, tys1) :: tys2 ->
      let acc = go fvAcc tys1
      let acc = go acc tys2
      acc

  go [] [ ty ] |> listUnique compare

/// Converts nested function type to multi-arguments function type.
let tyToArgList ty =
  let rec go n acc ty =
    match ty with
    | Ty (FunTk, [ sTy; tTy ]) -> go (n + 1) (sTy :: acc) tTy
    | tTy -> n, List.rev acc, tTy

  go 0 [] ty

/// Substitutes meta types in a type as possible.
let tySubst (substMeta: TySerial -> Ty option) ty =
  let rec go ty =
    match ty with
    | Ty (MetaTk (tySerial, _), _) ->
      match substMeta tySerial with
      | Some ty -> go ty

      | None -> ty

    | Ty (_, []) -> ty

    | Ty (tk, tys) -> Ty(tk, List.map go tys)

  go ty

/// Assume all bound type variables are resolved by `substTy`.
///
/// `isOwned` checks if the type variable is introduced by the most recent `let`.
/// For example, `let f x = (let g = f in g x)` will have too generic type
/// without this checking (according to TaPL).
let tyGeneralize (isOwned: TySerial -> bool) (ty: Ty) : TyScheme =
  let fvs =
    tyCollectFreeVars ty |> List.filter isOwned

  TyScheme(fvs, ty)

/// Generates a unique name from a type.
///
/// Must be used after successful Typing.
let tyMangle (ty: Ty, memo: TreeMap<Ty, string>) : string * TreeMap<Ty, string> =
  let rec go ty ctx =
    let (Ty (tk, tyArgs)) = ty

    let mangleList tys ctx =
      (tys, ctx)
      |> stMap (fun (ty, ctx) -> ctx |> go ty)

    let fixedGeneric (name: string) =
      let tyArgs, ctx = mangleList tyArgs ctx
      S.concat "" tyArgs + name, ctx

    let variadicGeneric (name: string) =
      let arity = List.length tyArgs
      let tyArgs, ctx = mangleList tyArgs ctx
      S.concat "" tyArgs + (name + string arity), ctx

    let doMangle () : string * TreeMap<_, _> =
      match tk with
      | IntTk flavor -> cIntegerTyPascalName flavor, ctx
      | FloatTk flavor -> cFloatTyPascalName flavor, ctx
      | BoolTk -> "Bool", ctx
      | CharTk -> "Char", ctx
      | StrTk -> "String", ctx

      | MetaTk _
      | ObjTk -> "Object", ctx

      | TupleTk when List.isEmpty tyArgs -> "Unit", ctx
      | TupleTk -> variadicGeneric "Tuple"

      | OptionTk -> fixedGeneric "Option"
      | ListTk -> fixedGeneric "List"

      | VoidTk -> "Void", ctx
      | NativePtrTk IsConst -> fixedGeneric "ConstPtr"
      | NativePtrTk IsMut -> fixedGeneric "MutPtr"
      | NativeFunTk -> variadicGeneric "NativeFun"
      | NativeTypeTk name -> name, ctx

      | FunTk ->
        let arity, argTys, resultTy = tyToArgList ty

        let argTys, ctx = mangleList argTys ctx
        let resultTy, ctx = ctx |> go resultTy

        let funTy =
          (argTys |> strConcat)
          + resultTy
          + "Fun"
          + string arity

        funTy, ctx

      | UnionTk _
      | RecordTk _ ->
        // Name must be stored in memo if monomorphic.
        assert (List.isEmpty tyArgs |> not)
        let name = memo |> mapFind (Ty(tk, []))
        variadicGeneric name

    // Memoization.
    match TMap.tryFind ty ctx with
    | Some name -> name, ctx

    | None ->
      let name, ctx = doMangle ()
      name, TMap.add ty name ctx

  go ty memo

// -----------------------------------------------
// Unification
// -----------------------------------------------

[<NoEquality; NoComparison>]
type UnifyResult =
  | UnifyOk
  | UnifyOkWithStack of (Ty * Ty) list
  | UnifyError of Loc
  | UnifyExpandMeta of metaSerial: TySerial * other: Ty
  | UnifyExpandSynonym of synonymSerial: TySerial * synonymArgs: Ty list * other: Ty

let unifyNext (lTy: Ty) (rTy: Ty) (loc: Loc) : UnifyResult =
  let mismatchError () = UnifyError loc

  match lTy, rTy with
  | Ty (MetaTk _, _), _
  | _, Ty (MetaTk _, _) ->
    match lTy, rTy with
    | Ty (MetaTk (l, _), _), Ty (MetaTk (r, _), _) when l = r -> UnifyOk

    | Ty (MetaTk (lSerial, _), _), _ -> UnifyExpandMeta(lSerial, rTy)
    | _, Ty (MetaTk (rSerial, _), _) -> UnifyExpandMeta(rSerial, lTy)

    | _ -> unreachable ()

  | Ty (lTk, lTyArgs), Ty (rTk, rTyArgs) when tkEqual lTk rTk ->
    match lTyArgs, rTyArgs with
    | [], [] -> UnifyOk

    | _ ->
      match listTryZip lTyArgs rTyArgs with
      | tyPairs, [], [] -> UnifyOkWithStack(tyPairs)
      | _ -> mismatchError ()

  | _ -> mismatchError ()

[<RequireQualifiedAccess>]
type UnifyAfterExpandMetaResult =
  | OkNoBind
  | OkBind
  | Error of Loc

let unifyAfterExpandMeta tySerial otherTy loc =
  match otherTy with
  | Ty (MetaTk (otherSerial, _), _) when otherSerial = tySerial -> UnifyAfterExpandMetaResult.OkNoBind

  | _ when tyIsFreeIn otherTy tySerial |> not ->
    // ^ Occurrence check.
    UnifyAfterExpandMetaResult.Error loc

  | _ -> UnifyAfterExpandMetaResult.OkBind
