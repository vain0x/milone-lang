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

let tkEqual first second = tkCompare first second = 0

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

  | IndexTrait (lTy, rTy, outputTy) -> IndexTrait(f lTy, f rTy, f outputTy)

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

let tyCompare first second =
  match first, second with
  | Ty (firstTk, firstTys), Ty (secondTk, secondTys) ->
      let c = tkCompare firstTk secondTk

      if c <> 0 then
        c
      else
        listCompare tyCompare firstTys secondTys

let tyEqual first second = tyCompare first second = 0

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
// Type inference context
// -----------------------------------------------

/// Type inference context.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type TyContext =
  { Serial: Serial
    Level: Level
    Tys: AssocMap<TySerial, TyDef>
    TyLevels: AssocMap<TySerial, Level>

    /// Binding of meta types made by unification.
    /// Levels default to the current level.
    Binding: AssocMap<TySerial, Ty>

    /// Changes of meta type levels by unification.
    LevelChanges: AssocMap<TySerial, Level> }

let emptyTyLevels: AssocMap<TySerial, Level> = TMap.empty compare
let emptyBindings: AssocMap<TySerial, Ty> = TMap.empty compare

let private tyContextUnify lTy rTy loc (logAcc: _ list, ctx: TyContext): _ list * TyContext =
  let unifyCtx: UnifyCtx =
    { Serial = ctx.Serial
      Binding = ctx.Binding
      LevelChanges = ctx.LevelChanges
      LogAcc = logAcc }

  let unifyCtx: UnifyCtx =
    typingUnify ctx.Level ctx.Tys ctx.TyLevels lTy rTy loc unifyCtx

  let ctx: TyContext =
    { ctx with
        Serial = unifyCtx.Serial
        Binding = unifyCtx.Binding
        LevelChanges = unifyCtx.LevelChanges }

  unifyCtx.LogAcc, ctx

let private tyContextGetLevel tyLevels levelChanges tySerial: Level =
  match levelChanges |> TMap.tryFind tySerial with
  | Some level -> level
  | _ ->
      tyLevels
      |> TMap.tryFind tySerial
      |> Option.defaultValue 0

let private tyContextExpandMeta tys binding tySerial: Ty option =
  match binding |> TMap.tryFind tySerial with
  | (Some _) as it -> it
  | _ ->
      match tys |> TMap.tryFind tySerial with
      | Some (MetaTyDef ty) -> Some ty
      | _ -> None

// -----------------------------------------------
// Type inference algorithm
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type UnifyCtx =
  { Serial: int
    Binding: AssocMap<TySerial, Ty>
    LevelChanges: AssocMap<TySerial, Level>
    LogAcc: (Log * Loc) list }

let private isMetaOf tySerial ty =
  match ty with
  | Ty (MetaTk (s, _), _) -> s = tySerial
  | _ -> false

/// Adds type-var/type binding.
let private typingBind tys tyLevels binding levelChanges tySerial ty =
  let ty = typingSubst tys binding ty

  // Self-binding never occurs due to occurrence check.
  assert (isMetaOf tySerial ty |> not)

  let binding = binding |> TMap.add tySerial ty

  // Reduce level of meta tys in the referent ty to the meta ty's level at most.
  let levelChanges =
    let level =
      tyContextGetLevel tyLevels levelChanges tySerial

    ty
    |> tyCollectFreeVars
    |> List.fold
         (fun levelChanges tySerial ->
           let currentLevel =
             tyContextGetLevel tyLevels levelChanges tySerial

           if currentLevel <= level then
             // Already non-deep enough.
             levelChanges
           else
             // Prevent this meta ty from getting generalized until level of the bound meta ty.
             levelChanges |> TMap.add tySerial level)
         levelChanges

  binding, levelChanges

let private typingSubst tys binding ty: Ty =
  tySubst (tyContextExpandMeta tys binding) ty

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

let tyExpandSynonym useTyArgs defTySerials bodyTy =
  // Checked in NameRes.
  assert (List.length defTySerials = List.length useTyArgs)

  // Expand synonym.
  let assignment =
    match listTryZip defTySerials useTyArgs with
    | assignment, [], [] -> assignment
    | _ -> failwith "NEVER"

  tyAssign assignment bodyTy

let tyExpandSynonyms expand ty =
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

let typingExpandSynonyms (ctx: TyContext) ty =
  let rec go ty =
    match ty with
    | Ty (SynonymTk tySerial, useTyArgs) ->
        match ctx.Tys |> TMap.tryFind tySerial with
        | Some (SynonymTyDef (_, defTySerials, bodyTy, _)) ->
            tyExpandSynonym useTyArgs defTySerials bodyTy
            |> go

        | _ -> Ty(SynonymTk tySerial, useTyArgs)

    | Ty (tk, tyArgs) -> Ty(tk, tyArgs |> List.map go)

  go ty

[<NoEquality; NoComparison>]
type private MetaTyUnifyResult =
  | DidExpand of Ty
  | DidBind of UnifyCtx
  | DidRecurse

let private unifyMetaTy tys tyLevels tySerial otherTy (ctx: UnifyCtx) =
  match tyContextExpandMeta tys ctx.Binding tySerial with
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

let typingResolveTraitBound logAcc (ctx: TyContext) theTrait loc =
  let theTrait =
    theTrait
    |> traitMapTys
         (fun ty ->
           ty
           |> typingSubst ctx.Tys ctx.Binding
           |> typingExpandSynonyms ctx)

  /// integer, bool, char, or string
  let expectBasic ty (logAcc, ctx) =
    match ty with
    | Ty (ErrorTk _, _)
    | Ty (IntTk _, [])
    | Ty (FloatTk _, [])
    | Ty (BoolTk, [])
    | Ty (CharTk, [])
    | Ty (StrTk, [])
    | Ty (NativePtrTk _, _) -> logAcc, ctx

    | _ -> (Log.TyBoundError theTrait, loc) :: logAcc, ctx

  match theTrait with
  | AddTrait ty ->
      match ty with
      | Ty (ErrorTk _, _)
      | Ty (IntTk _, [])
      | Ty (FloatTk _, [])
      | Ty (CharTk, [])
      | Ty (StrTk, []) -> logAcc, ctx

      | _ ->
          // Coerce to int by default.
          tyContextUnify ty tyInt loc (logAcc, ctx)

  | EqualTrait ty -> (logAcc, ctx) |> expectBasic ty

  | CompareTrait ty -> (logAcc, ctx) |> expectBasic ty

  | IndexTrait (lTy, rTy, resultTy) ->
      match lTy with
      | Ty (ErrorTk _, _) -> [], ctx

      | Ty (StrTk, []) ->
          (logAcc, ctx)
          |> tyContextUnify rTy tyInt loc
          |> tyContextUnify resultTy tyChar loc

      | _ -> (Log.TyBoundError theTrait, loc) :: logAcc, ctx

  | IsIntTrait ty ->
      match ty with
      | Ty (ErrorTk _, _)
      | Ty (IntTk _, []) -> logAcc, ctx

      | _ ->
          // Coerce to int by default.
          tyContextUnify ty tyInt loc (logAcc, ctx)

  | IsNumberTrait ty ->
      match ty with
      | Ty (ErrorTk _, _)
      | Ty (IntTk _, [])
      | Ty (FloatTk _, []) -> logAcc, ctx

      | _ ->
          // Coerce to int by default.
          tyContextUnify ty tyInt loc (logAcc, ctx)

  | ToCharTrait ty ->
      match ty with
      | Ty (ErrorTk _, _)
      | Ty (IntTk _, [])
      | Ty (FloatTk _, [])
      | Ty (CharTk, [])
      | Ty (StrTk, []) -> logAcc, ctx

      | _ -> (Log.TyBoundError theTrait, loc) :: logAcc, ctx

  | ToIntTrait ty ->
      match ty with
      | Ty (ErrorTk _, _)
      | Ty (IntTk _, [])
      | Ty (FloatTk _, [])
      | Ty (CharTk, [])
      | Ty (StrTk, [])
      | Ty (NativePtrTk _, _) -> logAcc, ctx

      | _ -> (Log.TyBoundError theTrait, loc) :: logAcc, ctx

  | ToFloatTrait ty ->
      match ty with
      | Ty (ErrorTk _, _)
      | Ty (IntTk _, [])
      | Ty (FloatTk _, [])
      | Ty (StrTk, []) -> logAcc, ctx

      | _ -> (Log.TyBoundError theTrait, loc) :: logAcc, ctx

  | ToStringTrait ty -> (logAcc, ctx) |> expectBasic ty

  | PtrTrait ty ->
      match ty with
      | Ty (ErrorTk _, _)
      | Ty (IntTk (IntFlavor (_, IPtr)), [])
      | Ty (ObjTk, [])
      | Ty (ListTk, _)
      | Ty (NativePtrTk _, _)
      | Ty (NativeFunTk, _) -> logAcc, ctx

      | _ -> (Log.TyBoundError theTrait, loc) :: logAcc, ctx
