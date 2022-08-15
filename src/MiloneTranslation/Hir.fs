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
open Std.StdError
open Std.StdMap
open MiloneTranslation.HirTypes

module S = Std.StdString

// -----------------------------------------------
// Types (HIR/MIR)
// -----------------------------------------------

let tyInt = Ty(IntTk I32, [])

let tyNativeInt = Ty(IntTk IPtr, [])

let tyBool = Ty(BoolTk, [])

let tyFloat = Ty(FloatTk F64, [])

let tyChar = Ty(CharTk, [])

let tyString = Ty(StringTk, [])

let tyObj = Ty(ObjTk, [])

let tyTuple tys = Ty(TupleTk, tys)

let tyList ty = Ty(ListTk, [ ty ])

let tyFun sourceTy targetTy = Ty(FunTk, [ sourceTy; targetTy ])

let tyNativeFun paramTys resultTy =
  Ty(FunPtrTk, List.append paramTys [ resultTy ])

let tyUnit = tyTuple []

let tyMeta serial loc = Ty(MetaTk(serial, loc), [])

let tyUnion tySerial tyArgs = Ty(UnionTk tySerial, tyArgs)

let tyRecord tySerial tyArgs = Ty(RecordTk tySerial, tyArgs)

// -----------------------------------------------
// Type definitions (HIR)
// -----------------------------------------------

let tyDefToName tyDef =
  match tyDef with
  | UnionTyDef (name, _, _, _) -> name
  | RecordTyDef (name, _, _, _, _) -> name
  | OpaqueTyDef (name, _) -> name

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
  | StringLit _ -> tyString

// -----------------------------------------------
// Patterns (HIR)
// -----------------------------------------------

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

      | HNilPN, _
      | HConsPN, _
      | HVariantAppPN _, _ -> false

      | HTuplePN, _
      | HBoxPN, _ -> argPats |> List.forall go

    | HAsPat (bodyPat, _, _) -> go bodyPat
    | HOrPat (l, r, _) -> go l || go r

  go pat

// -----------------------------------------------
// Expressions (HIR)
// -----------------------------------------------

let hxLetIn stmt next = HBlockExpr([ stmt ], next)

let hxTrue loc = HLitExpr(BoolLit true, loc)

let hxApp f x ty loc = HNodeExpr(HAppEN, [ f; x ], ty, loc)

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

let hArmMap (onPat: HPat -> HPat) (onExpr: HExpr -> HExpr) (arm: HPat * HExpr * HExpr) =
  let pat, guard, body = arm
  onPat pat, onExpr guard, onExpr body

let exprMap (f: Ty -> Ty) (expr: HExpr) : HExpr =
  let goPat pat = patMap f pat
  let goStmt stmt = stmtMap f stmt

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
    | HBlockExpr (stmts, last) -> HBlockExpr(List.map goStmt stmts, go last)

  go expr

let exprToTy expr =
  let ty, _ = exprExtract expr
  ty

let exprToLoc expr =
  let _, loc = exprExtract expr
  loc

// -----------------------------------------------
// HStmt
// -----------------------------------------------

let stmtToLoc stmt : Loc =
  match stmt with
  | HExprStmt expr -> exprToLoc expr
  | HLetValStmt (_, _, a) -> a
  | HLetFunStmt (_, _, _, a) -> a
  | HNativeDeclStmt (_, _, a) -> a

let stmtMap (f: Ty -> Ty) stmt =
  let onPat pat = patMap f pat
  let onExpr expr = exprMap f expr

  match stmt with
  | HExprStmt expr -> HExprStmt(onExpr expr)
  | HLetValStmt (pat, init, loc) -> HLetValStmt(onPat pat, onExpr init, loc)
  | HLetFunStmt (funSerial, argPats, body, loc) -> HLetFunStmt(funSerial, List.map onPat argPats, onExpr body, loc)
  | HNativeDeclStmt (code, args, loc) -> HNativeDeclStmt(code, List.map onExpr args, loc)

let private stmtMapExpr (f: HExpr -> HExpr) stmt =
  match stmt with
  | HExprStmt expr -> HExprStmt(f expr)
  | HLetValStmt (pat, init, loc) -> HLetValStmt(pat, f init, loc)
  | HLetFunStmt (funSerial, argPats, body, loc) -> HLetFunStmt(funSerial, argPats, f body, loc)
  | HNativeDeclStmt (code, args, loc) -> HNativeDeclStmt(code, List.map f args, loc)

let private stmtFoldExpr (folder: 'S -> HExpr -> 'S) (state: 'S) stmt =
  match stmt with
  | HExprStmt expr -> folder state expr
  | HLetValStmt (_, init, _) -> folder state init
  | HLetFunStmt (_, _, body, _) -> folder state body
  | HNativeDeclStmt (code, args, loc) -> List.fold folder state args

// -----------------------------------------------
// HProgram
// -----------------------------------------------

let emptyVars: TreeMap<VarSerial, VarDef> = TMap.empty varSerialCompare

module HProgram =
  let mapExpr (f: HExpr -> HExpr) (program: HProgram) : HProgram =
    program
    |> List.map (fun (m: HModule) -> { m with Stmts = m.Stmts |> List.map (stmtMapExpr f) })

  let foldExpr (f: 'S -> HExpr -> 'S) (state: 'S) (program: HProgram) : 'S =
    program
    |> List.fold (fun (state: 'S) (m: HModule) -> m.Stmts |> List.fold (stmtFoldExpr f) state) state

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
  | StringTk -> just 5
  | ObjTk -> just 6
  | FunTk -> just 7
  | TupleTk -> just 8
  | ListTk -> just 10

  | VoidPtrTk isMut -> pair 11 (isMutToInt isMut)
  | NativePtrTk mode -> pair 12 (RefMode.toInt mode)
  | FunPtrTk -> just 13

  | MetaTk (tySerial, _) -> pair 20 tySerial
  | UnionTk tySerial -> pair 22 tySerial
  | RecordTk tySerial -> pair 23 tySerial
  | OpaqueTk tySerial -> pair 24 tySerial

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
  | StringTk -> "string"
  | ObjTk -> "obj"
  | FunTk -> "fun"
  | TupleTk -> "tuple"
  | ListTk -> "list"
  | VoidPtrTk IsMut -> "voidptr"
  | VoidPtrTk IsConst -> "VoidInPtr"
  | NativePtrTk RefMode.ReadWrite -> "nativeptr"
  | NativePtrTk RefMode.ReadOnly -> "InPtr"
  | NativePtrTk RefMode.WriteOnly -> "OutPtr"
  | FunPtrTk -> "FunPtr"
  | NativeTypeTk _ -> "__nativeType"
  | MetaTk (tySerial, _) -> getTyName tySerial
  | RecordTk tySerial -> getTyName tySerial
  | UnionTk tySerial -> getTyName tySerial
  | OpaqueTk tySerial -> getTyName tySerial

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
      tys |> List.mapFold (fun ctx ty -> go ty ctx) ctx

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
      | StringTk -> "String", ctx

      | MetaTk _
      | ObjTk -> "Object", ctx

      | TupleTk when List.isEmpty tyArgs -> "Unit", ctx
      | TupleTk -> variadicGeneric "Tuple"

      | ListTk -> fixedGeneric "List"

      | VoidPtrTk IsMut -> "VoidPtr", ctx
      | VoidPtrTk IsConst -> "VoidInPtr", ctx
      | NativePtrTk RefMode.ReadWrite -> fixedGeneric "MutPtr"
      | NativePtrTk RefMode.ReadOnly -> fixedGeneric "InPtr"
      | NativePtrTk RefMode.WriteOnly -> fixedGeneric "OutPtr"
      | FunPtrTk -> variadicGeneric "FunPtr"
      | NativeTypeTk name -> S.replace " " "_" name, ctx

      | FunTk ->
        let arity, argTys, resultTy = tyToArgList ty

        let argTys, ctx = mangleList argTys ctx
        let resultTy, ctx = ctx |> go resultTy

        let funTy =
          (argTys |> S.concat "")
          + resultTy
          + "Fun"
          + string arity

        funTy, ctx

      | UnionTk _
      | RecordTk _
      | OpaqueTk _ ->
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

// Unification here is one-way, unlike unification for type inference.
// Unification must succeeds. That is, there is a substitution that holds s(lTy) = rTy.

let unifyOneWay folder state (lTy: Ty) (rTy: Ty) =
  let rec go state lTy rTy =
    match lTy, rTy with
    | Ty (MetaTk (l, _), _), Ty (MetaTk (r, _), _) when l = r -> state

    | Ty (MetaTk (tySerial, _), _), _ -> folder state tySerial rTy
    | _, Ty (MetaTk (_, _), _) -> state // Allowed. (GrayInstantiation ensures the meta type is consistent with lTy.)

    | Ty (lTk, lTyArgs), Ty (rTk, rTyArgs) ->
      assert (tkEqual lTk rTk)

      let pairs =
        match listTryZip lTyArgs rTyArgs with
        | it, [], [] -> it
        | _ -> unreachable ()

      pairs
      |> List.fold (fun acc (lTy, rTy) -> go acc lTy rTy) state

  go state lTy rTy
