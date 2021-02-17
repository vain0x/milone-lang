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
[<NoEquality; NoComparison>]
type TyContext =
  { Serial: Serial
    Level: Level
    Tys: AssocMap<TySerial, TyDef>
    TyLevels: AssocMap<TySerial, Level> }

let private addTyDef tySerial tyDef (ctx: TyContext) =
  { ctx with
      Tys = ctx.Tys |> TMap.add tySerial tyDef }

// -----------------------------------------------
// Type inference algorithm
// -----------------------------------------------

let private isMetaOf tySerial ty =
  match ty with
  | Ty (MetaTk (s, _), _) -> s = tySerial
  | _ -> false

/// Adds type-var/type binding.
let typingBind (ctx: TyContext) tySerial ty =
  let ty = typingSubst ctx ty

  // Self-binding never occurs due to occurrence check.
  assert (isMetaOf tySerial ty |> not)

  // Reduce level of meta tys in the referent ty to the meta ty's level at most.
  let tyLevels =
    let level =
      ctx.TyLevels
      |> TMap.tryFind tySerial
      |> Option.defaultValue 0

    ty
    |> tyCollectFreeVars
    |> List.fold
         (fun tyLevels tySerial ->
           let currentLevel =
             ctx.TyLevels
             |> TMap.tryFind tySerial
             |> Option.defaultValue 0

           if currentLevel <= level then
             // Already non-deep enough.
             tyLevels
           else
             // Prevent this meta ty from getting generalized until level of the bound meta ty.
             tyLevels |> TMap.add tySerial level)
         ctx.TyLevels

  let ctx =
    ctx
    |> addTyDef tySerial (MetaTyDef ty)

  { ctx with TyLevels = tyLevels }

/// Substitutes occurrences of already-inferred type vars
/// with their results.
let typingSubst (ctx: TyContext) ty: Ty =
  let substMeta tySerial =
    match ctx.Tys |> TMap.tryFind tySerial with
    | Some (MetaTyDef ty) -> Some ty
    | _ -> None

  tySubst substMeta ty

let tyExpandSynonym useTyArgs defTySerials bodyTy =
  // Checked in NameRes.
  assert (List.length defTySerials = List.length useTyArgs)

  // Expand synonym.
  let assignment =
    match listTryZip defTySerials useTyArgs with
    | assignment, [], [] -> assignment
    | _ -> failwith "NEVER"

  let substMeta tySerial =
    assignment |> assocTryFind compare tySerial

  tySubst substMeta bodyTy

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
  | DidBind of TyContext
  | DidRecurse

let private unifyMetaTy tySerial otherTy loc (ctx: TyContext) =
  match ctx.Tys |> TMap.tryFind tySerial with
  | Some (MetaTyDef ty) -> DidExpand ty

  | _ ->
      match typingSubst ctx otherTy with
      | Ty (MetaTk (otherSerial, _), _) when otherSerial = tySerial -> DidBind ctx

      | otherTy when tyIsFreeIn otherTy tySerial |> not ->
          // ^ Occurrence check.
          DidRecurse

      | otherTy -> DidBind(typingBind ctx tySerial otherTy)

let private unifySynonymTy tySerial useTyArgs loc (ctx: TyContext) =
  let defTySerials, bodyTy =
    match ctx.Tys |> TMap.tryFind tySerial with
    | Some (SynonymTyDef (_, defTySerials, bodyTy, _)) -> defTySerials, bodyTy
    | _ -> failwith "NEVER"

  // Checked in NameRes.
  assert (List.length defTySerials = List.length useTyArgs)

  let instantiatedTy, ctx =
    let assignment, ctx =
      defTySerials
      |> List.fold
           (fun (assignment, ctx: TyContext) defTySerial ->
             let newTySerial = ctx.Serial + 1

             let assignment =
               (defTySerial, (tyMeta newTySerial loc))
               :: assignment

             let ctx =
               let tyLevels =
                 ctx.TyLevels |> TMap.add newTySerial ctx.Level

               { ctx with
                   Serial = newTySerial
                   TyLevels = tyLevels }

             assignment, ctx)
           ([], ctx)

    let substMeta tySerial =
      assignment |> assocTryFind compare tySerial

    tySubst substMeta bodyTy, ctx

  let expandedTy =
    let assignment =
      match listTryZip defTySerials useTyArgs with
      | assignment, [], [] -> assignment
      | _ -> failwith "NEVER"

    let substMeta tySerial =
      assignment |> assocTryFind compare tySerial

    tySubst substMeta bodyTy

  expandedTy, instantiatedTy, ctx

/// Solves type equation `lty = rty` as possible
/// to add type-var/type bindings.
let typingUnify logAcc (ctx: TyContext) (lty: Ty) (rty: Ty) (loc: Loc) =
  let addLog kind lTy rTy logAcc ctx =
    (Log.TyUnify(kind, lTy, rTy), loc) :: logAcc, ctx

  let rec go lTy rTy (logAcc, ctx) =
    match lTy, rTy with
    | Ty (MetaTk (l, _), _), Ty (MetaTk (r, _), _) when l = r -> logAcc, ctx

    | Ty (MetaTk (lSerial, loc), _), _ ->
        match unifyMetaTy lSerial rTy loc ctx with
        | DidExpand ty -> go ty rTy (logAcc, ctx)
        | DidBind ctx -> logAcc, ctx
        | DidRecurse -> addLog TyUnifyLog.SelfRec lTy rTy logAcc ctx

    | _, Ty (MetaTk (rSerial, loc), _) ->
        match unifyMetaTy rSerial lTy loc ctx with
        | DidExpand ty -> go lTy ty (logAcc, ctx)
        | DidBind ctx -> logAcc, ctx
        | DidRecurse -> addLog TyUnifyLog.SelfRec lTy rTy logAcc ctx

    | Ty (lTk, lTyArgs), Ty (rTk, rTyArgs) when tkEqual lTk rTk ->
        let rec gogo lTyArgs rTyArgs (logAcc, ctx) =
          match lTyArgs, rTyArgs with
          | [], [] -> logAcc, ctx

          | l :: lTyArgs, r :: rTyArgs -> (logAcc, ctx) |> go l r |> gogo lTyArgs rTyArgs

          | _ -> addLog TyUnifyLog.Mismatch lTy rTy logAcc ctx

        gogo lTyArgs rTyArgs (logAcc, ctx)

    | Ty (SynonymTk tySerial, tyArgs), _ ->
        let ty1, ty2, ctx = unifySynonymTy tySerial tyArgs loc ctx
        (logAcc, ctx) |> go ty1 ty2 |> go ty1 rTy

    | _, Ty (SynonymTk tySerial, tyArgs) ->
        let ty1, ty2, ctx = unifySynonymTy tySerial tyArgs loc ctx
        (logAcc, ctx) |> go ty1 ty2 |> go ty1 lTy

    | Ty _, _ -> addLog TyUnifyLog.Mismatch lTy rTy logAcc ctx

  go lty rty (logAcc, ctx)

let typingResolveTraitBound logAcc (ctx: TyContext) theTrait loc =
  let theTrait =
    theTrait
    |> traitMapTys (fun ty -> ty |> typingSubst ctx |> typingExpandSynonyms ctx)

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
          typingUnify logAcc ctx ty tyInt loc

  | EqualTrait ty -> (logAcc, ctx) |> expectBasic ty

  | CompareTrait ty -> (logAcc, ctx) |> expectBasic ty

  | IndexTrait (lTy, rTy, resultTy) ->
      match lTy with
      | Ty (ErrorTk _, _) -> [], ctx

      | Ty (StrTk, []) ->
          let logAcc, ctx = typingUnify logAcc ctx rTy tyInt loc

          let logAcc, ctx =
            typingUnify logAcc ctx resultTy tyChar loc

          logAcc, ctx

      | _ -> (Log.TyBoundError theTrait, loc) :: logAcc, ctx

  | IsIntTrait ty ->
      match ty with
      | Ty (ErrorTk _, _)
      | Ty (IntTk _, []) -> logAcc, ctx

      | _ ->
          // Coerce to int by default.
          typingUnify logAcc ctx ty tyInt loc

  | IsNumberTrait ty ->
      match ty with
      | Ty (ErrorTk _, _)
      | Ty (IntTk _, [])
      | Ty (FloatTk _, []) -> logAcc, ctx

      | _ ->
          // Coerce to int by default.
          typingUnify logAcc ctx ty tyInt loc

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
