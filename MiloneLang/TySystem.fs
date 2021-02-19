/// ## Type System
///
/// Provides functions about type system.
///
/// This module is mainly used in Typing and Monomorphizing.
module rec MiloneLang.TySystem

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.TypeFloat
open MiloneLang.TypeIntegers
open MiloneLang.Hir

module TMap = MiloneStd.StdMap
module S = MiloneStd.StdString

let emptyTyLevels: AssocMap<TySerial, Level> = TMap.empty compare

let emptyBinding: AssocMap<TySerial, Ty> = TMap.empty compare

// -----------------------------------------------
// Tk
// -----------------------------------------------

let private tkEncode tk =
  let isMutToInt isMut =
    match isMut with
    | IsConst -> 1
    | IsMut -> 2

  match tk with
  | ErrorTk _ -> 0, 0
  | IntTk flavor -> 1, intFlavorToOrdinary flavor
  | FloatTk flavor -> 2, floatFlavorToOrdinary flavor
  | BoolTk -> 3, 0
  | CharTk -> 4, 0
  | StrTk -> 5, 0
  | ObjTk -> 6, 0
  | FunTk -> 7, 0
  | TupleTk -> 8, 0
  | OptionTk -> 9, 0
  | ListTk -> 10, 0

  | VoidTk -> 11, 0
  | NativePtrTk isMut -> 12, isMutToInt isMut
  | NativeFunTk -> 13, 0

  | MetaTk (tySerial, _) -> 20, tySerial
  | SynonymTk tySerial -> 21, tySerial
  | UnionTk tySerial -> 22, tySerial
  | RecordTk tySerial -> 23, tySerial

  | NativeTypeTk _
  | UnresolvedTk _
  | UnresolvedVarTk _ -> failwith "NEVER"

let tkCompare l r =
  match l, r with
  | NativeTypeTk l, NativeTypeTk r -> compare l r

  | NativeTypeTk _, _ -> -1
  | _, NativeTypeTk _ -> 1

  | UnresolvedTk (lQuals, lSerial), UnresolvedTk (rQuals, rSerial) ->
      pairCompare (listCompare compare) compare (lQuals, lSerial) (rQuals, rSerial)

  | UnresolvedTk _, _ -> -1
  | _, UnresolvedTk _ -> 1

  | _ -> pairCompare compare compare (tkEncode l) (tkEncode r)

let tkEqual l r = tkCompare l r = 0

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
let tyIsFreeIn ty tySerial: bool =
  let rec go ty =
    match ty with
    | Ty (MetaTk (s, _), _) -> s <> tySerial

    | Ty (_, []) -> true

    | Ty (tk, ty :: tys) -> go ty && go (Ty(tk, tys))

  go ty

/// Gets if the type is monomorphic.
/// Assume all bound type variables are substituted.
let tyIsMonomorphic ty: bool =
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
let rec tyToArgList ty =
  let rec go n acc ty =
    match ty with
    | Ty (FunTk, [ sTy; tTy ]) -> go (n + 1) (sTy :: acc) tTy
    | tTy -> n, List.rev acc, tTy

  go 0 [] ty

/// Checks if the type contains no bound meta types.
let private tyIsFullySubstituted (isBound: TySerial -> bool) ty: bool =
  let rec go ty =
    match ty with
    | Ty (MetaTk (tySerial, _), _) -> isBound tySerial |> not
    | Ty (_, tyArgs) -> List.forall go tyArgs

  go ty

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
let tyExpandSynonym useTyArgs defTySerials bodyTy: Ty =
  // Checked in NameRes.
  assert (List.length defTySerials = List.length useTyArgs)

  let assignment =
    match listTryZip defTySerials useTyArgs with
    | assignment, [], [] -> assignment
    | _ -> failwith "NEVER"

  tyAssign assignment bodyTy

/// Expands all synonyms inside of a type.
let tyExpandSynonyms (expand: TySerial -> TyDef option) ty: Ty =
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
let tyGeneralize (isOwned: TySerial -> bool) (ty: Ty): TyScheme =
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
        let tk = tkDisplay (fun _ -> failwith "NEVER") tk

        match args with
        | [] -> tk
        | _ ->
            let args = args |> List.map (go 0) |> S.concat ", "
            tk + "<" + args + ">"

  go 0 ty

// -----------------------------------------------
// Context-free functions
// -----------------------------------------------

let private getLevel tyLevels levelChanges tySerial: Level =
  match levelChanges |> TMap.tryFind tySerial with
  | Some level -> level
  | _ ->
      tyLevels
      |> TMap.tryFind tySerial
      |> Option.defaultValue 0

let private metaTyIsBound tys binding tySerial: bool =
  TMap.containsKey tySerial binding
  || (match tys |> TMap.tryFind tySerial with
      | Some (MetaTyDef _) -> true
      | _ -> false)

let private tyExpandMeta tys binding tySerial: Ty option =
  match binding |> TMap.tryFind tySerial with
  | (Some _) as it -> it
  | _ ->
      match tys |> TMap.tryFind tySerial with
      | Some (MetaTyDef ty) -> Some ty
      | _ -> None

let doInstantiateTyScheme
  (serial: int)
  (level: Level)
  (tyLevels: AssocMap<TySerial, Level>)
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

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type UnifyCtx =
  { Serial: int
    LogAcc: (Log * Loc) list

    /// Binding of meta types during unification.
    Binding: AssocMap<TySerial, Ty>

    /// For existing meta types: level up during unification.
    /// For new unbound meta types: set current level.
    LevelChanges: AssocMap<TySerial, Level> }

let private isMetaOf tySerial ty =
  match ty with
  | Ty (MetaTk (s, _), _) -> s = tySerial
  | _ -> false

let typingSubst tys binding ty: Ty = tySubst (tyExpandMeta tys binding) ty

let typingExpandSynonyms tys ty =
  tyExpandSynonyms (fun tySerial -> tys |> TMap.tryFind tySerial) ty

/// Adds type-var/type binding.
let private typingBind tys tyLevels binding levelChanges tySerial ty =
  assert (tyIsFullySubstituted (metaTyIsBound tys binding) ty)

  // Self-binding never occurs due to occurrence check.
  assert (isMetaOf tySerial ty |> not)

  let binding = binding |> TMap.add tySerial ty

  // Reduce level of meta tys in the referent ty to the meta ty's level at most.
  let levelChanges =
    let level = getLevel tyLevels levelChanges tySerial

    ty
    |> tyCollectFreeVars
    |> List.fold
         (fun levelChanges tySerial ->
           let currentLevel = getLevel tyLevels levelChanges tySerial

           if currentLevel <= level then
             // Already non-deep enough.
             levelChanges
           else
             // Prevent this meta ty from getting generalized until level of the bound meta ty.
             levelChanges |> TMap.add tySerial level)
         levelChanges

  binding, levelChanges

[<NoEquality; NoComparison>]
type private MetaTyUnifyResult =
  | DidExpand of Ty
  | DidBind of UnifyCtx
  | DidRecurse

let private unifyMetaTy tys tyLevels tySerial otherTy (ctx: UnifyCtx) =
  match tyExpandMeta tys ctx.Binding tySerial with
  | Some ty -> DidExpand ty

  | _ ->
      match typingSubst tys ctx.Binding otherTy with
      | Ty (MetaTk (otherSerial, _), _) when otherSerial = tySerial -> DidBind ctx

      | otherTy when tyIsFreeIn otherTy tySerial |> not ->
          // ^ Occurrence check.
          DidRecurse

      | otherTy ->
          let binding, levelChanges =
            typingBind tys tyLevels ctx.Binding ctx.LevelChanges tySerial otherTy

          let ctx =
            { ctx with
                Binding = binding
                LevelChanges = levelChanges }

          DidBind ctx

let private unifySynonymTy level tys tySerial useTyArgs loc (ctx: UnifyCtx) =
  let defTySerials, bodyTy =
    match tys |> TMap.tryFind tySerial with
    | Some (SynonymTyDef (_, defTySerials, bodyTy, _)) -> defTySerials, bodyTy
    | _ -> failwith "NEVER"

  // Checked in NameRes.
  assert (List.length defTySerials = List.length useTyArgs)

  let instantiatedTy, ctx =
    let serial, levelChanges, bodyTy, _ =
      doInstantiateTyScheme ctx.Serial level ctx.LevelChanges defTySerials bodyTy loc

    bodyTy,
    { ctx with
        Serial = serial
        LevelChanges = levelChanges }

  let expandedTy =
    tyExpandSynonym useTyArgs defTySerials bodyTy

  expandedTy, instantiatedTy, ctx

/// Solves type equation `lty = rty` as possible
/// to add type-var/type bindings.
let typingUnify level tys tyLevels (lty: Ty) (rty: Ty) (loc: Loc) (ctx: UnifyCtx) =
  let addLog kind lTy rTy (ctx: UnifyCtx) =
    { ctx with
        LogAcc = (Log.TyUnify(kind, lTy, rTy), loc) :: ctx.LogAcc }

  let rec go lTy rTy (ctx: UnifyCtx) =
    match lTy, rTy with
    | Ty (MetaTk (l, _), _), Ty (MetaTk (r, _), _) when l = r -> ctx

    | Ty (MetaTk (lSerial, _), _), _ ->
        match unifyMetaTy tys tyLevels lSerial rTy ctx with
        | DidExpand ty -> go ty rTy ctx
        | DidBind ctx -> ctx
        | DidRecurse -> addLog TyUnifyLog.SelfRec lTy rTy ctx

    | _, Ty (MetaTk (rSerial, _), _) ->
        match unifyMetaTy tys tyLevels rSerial lTy ctx with
        | DidExpand ty -> go lTy ty ctx
        | DidBind ctx -> ctx
        | DidRecurse -> addLog TyUnifyLog.SelfRec lTy rTy ctx

    | Ty (lTk, lTyArgs), Ty (rTk, rTyArgs) when tkEqual lTk rTk ->
        let rec gogo lTyArgs rTyArgs (ctx: UnifyCtx) =
          match lTyArgs, rTyArgs with
          | [], [] -> ctx

          | l :: lTyArgs, r :: rTyArgs -> ctx |> go l r |> gogo lTyArgs rTyArgs

          | _ -> addLog TyUnifyLog.Mismatch lTy rTy ctx

        gogo lTyArgs rTyArgs ctx

    | Ty (SynonymTk tySerial, tyArgs), _ ->
        let ty1, ty2, ctx =
          unifySynonymTy level tys tySerial tyArgs loc ctx

        ctx |> go ty1 ty2 |> go ty1 rTy

    | _, Ty (SynonymTk tySerial, tyArgs) ->
        let ty1, ty2, ctx =
          unifySynonymTy level tys tySerial tyArgs loc ctx

        ctx |> go ty1 ty2 |> go ty1 lTy

    | Ty _, _ -> addLog TyUnifyLog.Mismatch lTy rTy ctx

  go lty rty ctx
