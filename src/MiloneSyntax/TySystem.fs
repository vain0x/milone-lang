/// ## Type System
///
/// Provides functions about type system.
///
/// This module is mainly used in Typing and Monomorphizing.
module rec MiloneSyntax.TySystem

open MiloneShared.SharedTypes
open MiloneShared.TypeFloat
open MiloneShared.TypeIntegers
open MiloneShared.Util
open MiloneStd.StdMap
open MiloneSyntax.Tir

module S = MiloneStd.StdString

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
  | ErrorTk _ -> just 0
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
  | SynonymTk tySerial -> pair 21 tySerial
  | UnionTk tySerial -> pair 22 tySerial
  | RecordTk tySerial -> pair 23 tySerial

  | NativeTypeTk _
  | UnresolvedTk _
  | UnresolvedVarTk _ -> unreachable ()

let tkCompare l r : int =
  match l, r with
  | NativeTypeTk l, NativeTypeTk r -> compare l r

  | NativeTypeTk _, _ -> -1
  | _, NativeTypeTk _ -> 1

  | UnresolvedTk (lQuals, lSerial), UnresolvedTk (rQuals, rSerial) ->
    pairCompare (listCompare compare) compare (lQuals, lSerial) (rQuals, rSerial)

  | UnresolvedTk _, _ -> -1
  | _, UnresolvedTk _ -> 1

  | _ -> tkEncode l - tkEncode r

let tkEqual l r : bool = tkCompare l r = 0

let tkDisplay getTyName tk =
  match tk with
  | ErrorTk loc -> "{error}@" + locToString loc
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
  | SynonymTk tySerial -> getTyName tySerial
  | RecordTk tySerial -> getTyName tySerial
  | UnionTk tySerial -> getTyName tySerial
  | UnresolvedTk (_, serial) -> "?" + string serial
  | UnresolvedVarTk (serial, _) -> "'" + string serial

// -----------------------------------------------
// Traits (HIR)
// -----------------------------------------------

let traitMapTys f it =
  match it with
  | AddTrait ty -> AddTrait(f ty)
  | EqualTrait ty -> EqualTrait(f ty)
  | CompareTrait ty -> CompareTrait(f ty)
  | IndexTrait (lTy, rTy, resultTy) -> IndexTrait(f lTy, f rTy, f resultTy)
  | IsIntTrait ty -> IsIntTrait(f ty)
  | IsNumberTrait ty -> IsNumberTrait(f ty)
  | ToCharTrait ty -> ToCharTrait(f ty)
  | ToIntTrait ty -> ToIntTrait(f ty)
  | ToFloatTrait ty -> ToFloatTrait(f ty)
  | ToStringTrait ty -> ToStringTrait(f ty)
  | PtrTrait ty -> PtrTrait(f ty)

// -----------------------------------------------
// Types (HIR/MIR)
// -----------------------------------------------

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

let tyAssign assignment ty =
  tySubst (fun tySerial -> assocTryFind compare tySerial assignment) ty

/// Expands a synonym type using its definition and type args.
let tyExpandSynonym useTyArgs defTySerials bodyTy : Ty =
  // Checked in NameRes.
  assert (List.length defTySerials = List.length useTyArgs)

  let assignment =
    match listTryZip defTySerials useTyArgs with
    | assignment, [], [] -> assignment
    | _ -> unreachable ()

  tyAssign assignment bodyTy

/// Expands all synonyms inside of a type.
let tyExpandSynonyms (expand: TySerial -> TyDef option) ty : Ty =
  let rec go ty =
    match ty with
    | Ty (SynonymTk tySerial, useTyArgs) ->
      match expand tySerial with
      | Some (SynonymTyDef (_, defTySerials, bodyTy, _)) ->
        tyExpandSynonym useTyArgs defTySerials bodyTy
        |> go

      | _ -> Ty(SynonymTk tySerial, useTyArgs)

    | Ty (tk, tyArgs) -> Ty(tk, tyArgs |> List.map go)

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

/// Converts a type to human readable string.
let tyDisplay getTyName ty =
  let rec go (outerBp: int) ty =
    let paren (bp: int) s =
      if bp >= outerBp then
        s
      else
        "(" + s + ")"

    let nominal tySerial args =
      let tk =
        match tySerial |> getTyName with
        | Some name -> name
        | None -> "?" + string tySerial

      match args with
      | [] -> tk
      | _ ->
        let args = args |> List.map (go 0) |> S.concat ", "
        tk + "<" + args + ">"

    match ty with
    | Ty (FunTk, [ sTy; tTy ]) -> paren 10 (go 11 sTy + " -> " + go 10 tTy)

    | Ty (TupleTk, []) -> "unit"

    | Ty (TupleTk, itemTys) ->
      "("
      + (itemTys |> List.map (go 20) |> S.concat " * ")
      + ")"

    | Ty (OptionTk, [ itemTy ]) -> paren 30 (go 30 itemTy + " option")

    | Ty (ListTk, [ itemTy ]) -> paren 30 (go 30 itemTy + " list")

    | Ty (MetaTk (tySerial, loc), _) ->
      match getTyName tySerial with
      | Some name -> "{" + name + "}@" + locToString loc
      | None -> "{?" + string tySerial + "}@" + locToString loc

    | Ty (SynonymTk tySerial, args) -> nominal tySerial args
    | Ty (UnionTk tySerial, args) -> nominal tySerial args
    | Ty (RecordTk tySerial, args) -> nominal tySerial args

    | Ty (tk, args) ->
      let tk = tkDisplay (fun _ -> unreachable ()) tk

      match args with
      | [] -> tk
      | _ ->
        let args = args |> List.map (go 0) |> S.concat ", "
        tk + "<" + args + ">"

  go 0 ty

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
      | RecordTk _ -> unreachable () // Must be stored in memo.

      | ErrorTk _
      | SynonymTk _ -> unreachable () // Resolved in Typing.

      | UnresolvedTk _
      | UnresolvedVarTk _ -> unreachable () // Resolved in NameRes..

    // Memoization.
    match TMap.tryFind ty ctx with
    | Some name -> name, ctx

    | None ->
      let name, ctx = doMangle ()
      name, TMap.add ty name ctx

  go ty memo

// -----------------------------------------------
// Context-free functions
// -----------------------------------------------

let private getLevel tyLevels levelChanges tySerial : Level =
  match levelChanges |> TMap.tryFind tySerial with
  | Some level -> level
  | _ ->
    tyLevels
    |> TMap.tryFind tySerial
    |> Option.defaultValue 0

let private metaTyIsBound tys binding tySerial : bool =
  TMap.containsKey tySerial binding
  || (match tys |> TMap.tryFind tySerial with
      | Some (MetaTyDef _) -> true
      | _ -> false)

let private tyExpandMeta tys binding tySerial : Ty option =
  match binding |> TMap.tryFind tySerial with
  | (Some _) as it -> it
  | _ ->
    match tys |> TMap.tryFind tySerial with
    | Some (MetaTyDef ty) -> Some ty
    | _ -> None

let doInstantiateTyScheme
  (serial: int)
  (level: Level)
  (tyLevels: TreeMap<TySerial, Level>)
  (tySerials: TySerial list)
  (ty: Ty)
  (loc: Loc)
  =
  let serial, tyLevels, assignment =
    tySerials
    |> List.fold
         (fun (serial, tyLevels, assignment) tySerial ->
           let serial = serial + 1
           let tyLevels = tyLevels |> TMap.add serial level

           let assignment =
             (tySerial, tyMeta serial loc) :: assignment

           serial, tyLevels, assignment)
         (serial, tyLevels, [])

  let ty = tyAssign assignment ty
  serial, tyLevels, ty, assignment

// -----------------------------------------------
// Unification
// -----------------------------------------------

type UnifyResult =
  | UnifyOk
  | UnifyOkWithStack of (Ty * Ty) list
  | UnifyError of Log * Loc
  | UnifyExpandMeta of metaSerial: TySerial * other: Ty
  | UnifyExpandSynonym of synonymSerial: TySerial * synonymArgs: Ty list * other: Ty

let unifyNext (lTy: Ty) (rTy: Ty) (loc: Loc) : UnifyResult =
  let mismatchError () =
    UnifyError(Log.TyUnify(TyUnifyLog.Mismatch, lTy, rTy), loc)

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

  | Ty (SynonymTk _, _), _
  | _, Ty (SynonymTk _, _) ->
    match lTy, rTy with
    | Ty (SynonymTk tySerial, tyArgs), _ -> UnifyExpandSynonym(tySerial, tyArgs, rTy)
    | _, Ty (SynonymTk tySerial, tyArgs) -> UnifyExpandSynonym(tySerial, tyArgs, lTy)
    | _ -> unreachable ()

  | _ -> mismatchError ()

[<RequireQualifiedAccess>]
type UnifyAfterExpandMetaResult =
  | OkNoBind
  | OkBind
  | Error of Log * Loc

let unifyAfterExpandMeta lTy rTy tySerial otherTy loc =
  match otherTy with
  | Ty (MetaTk (otherSerial, _), _) when otherSerial = tySerial -> UnifyAfterExpandMetaResult.OkNoBind

  | _ when tyIsFreeIn otherTy tySerial |> not ->
    // ^ Occurrence check.
    UnifyAfterExpandMetaResult.Error(Log.TyUnify(TyUnifyLog.SelfRec, lTy, rTy), loc)

  | _ -> UnifyAfterExpandMetaResult.OkBind

let typingSubst tys binding ty : Ty = tySubst (tyExpandMeta tys binding) ty

let typingExpandSynonyms tys ty =
  tyExpandSynonyms (fun tySerial -> tys |> TMap.tryFind tySerial) ty
