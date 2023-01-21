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
open Std.StdError
open Std.StdMap
open MiloneSyntax.Tir
open MiloneSyntax.TirTypes

module S = Std.StdString

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
  | StringTk -> just 5
  | NeverTk -> just 26 // to be reordered
  | ObjTk -> just 6
  | FunTk -> just 7
  | TupleTk -> just 8
  | ListTk -> just 10

  | OwnTk -> just 11
  | VoidPtrTk isMut -> pair 12 (isMutToInt isMut)
  | NativePtrTk mode -> pair 13 (RefMode.toInt mode)
  | FunPtrTk -> just 14

  | MetaTk (tySerial, _) -> pair 20 tySerial
  | UnivTk (tySerial, _, _) -> pair 25 tySerial // to be reordered
  | SynonymTk tySerial -> pair 21 tySerial
  | UnionTk (tySerial, _) -> pair 22 tySerial
  | RecordTk (tySerial, _) -> pair 23 tySerial
  | OpaqueTk tySerial -> pair 24 tySerial

  | NativeTypeTk _
  | InferTk _ -> unreachable ()

let tkCompare l r : int =
  match l, r with
  | NativeTypeTk l, NativeTypeTk r -> compare l r
  | NativeTypeTk _, _ -> -1
  | _, NativeTypeTk _ -> 1

  | InferTk _, InferTk _ -> 0
  | InferTk _, _ -> -1
  | _, InferTk _ -> 1

  | _ -> tkEncode l - tkEncode r

let tkEqual l r : bool = tkCompare l r = 0

let tkDisplay getTyName tk =
  match tk with
  | ErrorTk loc -> "{error}@" + Loc.toString loc
  | IntTk flavor -> fsharpIntegerTyName flavor
  | FloatTk flavor -> fsharpFloatTyName flavor
  | BoolTk -> "bool"
  | CharTk -> "char"
  | StringTk -> "string"
  | NeverTk -> "never"
  | ObjTk -> "obj"
  | FunTk -> "fun"
  | TupleTk -> "tuple"
  | ListTk -> "list"
  | OwnTk -> "Own"
  | VoidPtrTk IsMut -> "voidptr"
  | VoidPtrTk IsConst -> "VoidInPtr"
  | NativePtrTk RefMode.ReadWrite -> "nativeptr"
  | NativePtrTk RefMode.ReadOnly -> "InPtr"
  | NativePtrTk RefMode.WriteOnly -> "OutPtr"
  | FunPtrTk -> "FunPtr"
  | NativeTypeTk _ -> "__nativeType"
  | MetaTk (tySerial, _) -> getTyName tySerial
  | UnivTk (_, name, _) -> name
  | SynonymTk tySerial -> getTyName tySerial
  | RecordTk (tySerial, _) -> getTyName tySerial
  | OpaqueTk tySerial -> getTyName tySerial
  | UnionTk (tySerial, _) -> getTyName tySerial
  | InferTk _ -> "_"

// -----------------------------------------------
// Traits (HIR)
// -----------------------------------------------

module Trait =
  let private newUnary unary ty = Trait.Unary(unary, ty)

  let newAdd ty = newUnary UnaryTrait.Add ty
  let newEqual ty = newUnary UnaryTrait.Equal ty
  let newCompare ty = newUnary UnaryTrait.Compare ty
  let newIntLike ty = newUnary UnaryTrait.IntLike ty
  let newNumberLike ty = newUnary UnaryTrait.NumberLike ty
  let newToInt flavor ty = newUnary (UnaryTrait.ToInt flavor) ty
  let newToFloat ty = newUnary UnaryTrait.ToFloat ty
  let newToChar ty = newUnary UnaryTrait.ToChar ty
  let newToString ty = newUnary UnaryTrait.ToString ty
  let newPtrLike ty = newUnary UnaryTrait.PtrLike ty
  let newPtrSize ty = newUnary UnaryTrait.PtrSize ty

  let newIndex lTy rTy tTy = Trait.Index(lTy, rTy, tTy)
  let newPtrCast srcTy destTy = Trait.PtrCast(srcTy, destTy)

  /// Converts a trait by applying `onTy` on each types inside it.
  let map (onTy: Ty -> Ty) (t: Trait) =
    match t with
    | Trait.Unary(unary, ty) -> Trait.Unary(unary, onTy ty)
    | Trait.Index(lTy, rTy, tTy) -> Trait.Index(onTy lTy, onTy rTy, onTy tTy)
    | Trait.PtrCast(srcTy, destTy) -> Trait.PtrCast(onTy srcTy, onTy destTy)

  /// Creates a list of types that appear in the trait.
  let collectTys (t: Trait) =
    match t with
    | Trait.Unary(_, ty) -> [ ty ]
    | Trait.Index(lTy, rTy, tTy) -> [ lTy; rTy; tTy ]
    | Trait.PtrCast(srcTy, destTy) -> [ srcTy; destTy ]

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

/// Checks if a type syntactically contains any meta or universal type.
let private tyContainsMetaOrUniv ty =
  match ty with
  | Ty(MetaTk _, _)
  | Ty(UnivTk _, _) -> true

  | Ty(_, tyArgs) ->
    let rec argLoop args =
      match args with
      | a :: args -> tyContainsMetaOrUniv a || argLoop args
      | _ -> false

    argLoop tyArgs

/// Converts a type by replacing meta types and universal types as possible.
let tyAssignByMap (assignmentMap: TreeMap<TySerial, Ty>) ty =
  let rec assignRec ty =
    match ty with
    | Ty (MetaTk (tySerial, _), _) ->
      match assignmentMap |> TMap.tryFind tySerial with
      | Some ty -> assignRec ty
      | None -> ty

    | Ty (UnivTk (tySerial, _, _), _) ->
      match assignmentMap |> TMap.tryFind tySerial with
      | Some ty -> assignRec ty
      | None -> ty

    | Ty (tk, tyArgs) -> Ty(tk, List.map assignRec tyArgs)

  if tyContainsMetaOrUniv ty then
    assignRec ty
  else
    ty

/// Converts a type by replacing meta types and universal types as possible.
let tyAssignByList (assignment: (TySerial * Ty) list) ty =
  if tyContainsMetaOrUniv ty then
    tyAssignByMap (TMap.ofList compare assignment) ty
  else
    ty

/// Checks if a type structurally contains any meta type.
/// (perf: This runs frequently and should be efficient.)
let rec tyContainsMeta ty =
  match ty with
  | Ty(MetaTk _, _) -> true

  | Ty(_, tyArgs) ->
    let rec argLoop args =
      match args with
      | a :: args -> tyContainsMeta a || argLoop args
      | _ -> false

    argLoop tyArgs

/// Substitutes meta types in a type as possible.
/// (perf: This runs frequently and should be efficient.)
let tySubst (substMeta: TySerial -> Ty option) ty =
  let rec substRec ty =
    match ty with
    | Ty (MetaTk (tySerial, _), _) ->
      match substMeta tySerial with
      | Some ty -> substRec ty
      | None -> ty

    | Ty (tk, tyArgs) ->
      let rec substMap acc tys =
        match tys with
        | [] -> List.rev acc
        | t :: tys -> substMap (substRec t :: acc) tys

      Ty(tk, substMap [] tyArgs)

  if tyContainsMeta ty then
    substRec ty
  else
    ty

/// Expands a synonym type using its definition and type args.
let tyExpandSynonym useTyArgs defTySerials bodyTy : Ty =
  // Checked in NameRes.
  assert (List.length defTySerials = List.length useTyArgs)

  let assignment =
    match listTryZip defTySerials useTyArgs with
    | assignment, [], [] -> assignment
    | _ -> unreachable ()

  tyAssignByList assignment bodyTy

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
let tyGeneralize (canGeneralize: TySerial -> bool) (ty: Ty) : TyScheme =
  let collectMetaAndUniv ty =
    let rec go acc ty =
      match ty with
      | Ty (MetaTk (serial, _), _) -> serial :: acc
      | Ty (UnivTk (serial, _, _), _) -> serial :: acc
      | Ty (_, tyArgs) -> tyArgs |> List.fold go acc

    go [] ty |> listUnique compare

  let tyVars =
    collectMetaAndUniv ty |> List.filter canGeneralize

  TyScheme(tyVars, ty)

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

    | Ty (ListTk, [ itemTy ]) -> paren 30 (go 30 itemTy + " list")

    | Ty (MetaTk (tySerial, loc), _) ->
      match getTyName tySerial with
      | Some name -> "{" + name + "}@" + Loc.toString loc
      | None -> "{?" + string tySerial + "}@" + Loc.toString loc

    | Ty (UnivTk (_, name, _), _) -> name
    | Ty (SynonymTk tySerial, args) -> nominal tySerial args
    | Ty (UnionTk (tySerial, _), args) -> nominal tySerial args
    | Ty (RecordTk (tySerial, _), args) -> nominal tySerial args
    | Ty (OpaqueTk tySerial, args) -> nominal tySerial args

    | Ty (tk, args) ->
      let tk = tkDisplay (fun _ -> unreachable ()) tk

      match args with
      | [] -> tk
      | _ ->
        let args = args |> List.map (go 0) |> S.concat ", "
        tk + "<" + args + ">"

  go 0 ty

// -----------------------------------------------
// Context-free functions
// -----------------------------------------------

let doInstantiateTyScheme
  (serial: int)
  (tySerials: TySerial list)
  (ty: Ty)
  (loc: Loc)
  =
  let serial, assignment =
    tySerials
    |> List.fold
         (fun (serial, assignment) tySerial ->
           let serial = serial + 1

           let assignment =
             (tySerial, tyMeta serial loc) :: assignment

           serial, assignment)
         (serial, [])

  let ty = tyAssignByList assignment ty
  serial, ty, assignment

// -----------------------------------------------
// Unification
// -----------------------------------------------

type UnifyResult =
  | UnifyOk
  | UnifyOkWithStack of (Ty * Ty) list
  | UnifyError of Log * Loc
  | UnifyExpandMeta of metaSerial: TySerial * other: Ty * isLeft: bool
  | UnifyExpandSynonym of synonymSerial: TySerial * synonymArgs: Ty list * other: Ty * isLeft: bool

let unifyNext (lTy: Ty) (rTy: Ty) (loc: Loc) : UnifyResult =
  let mismatchError () =
    UnifyError(Log.TyUnify(TyUnifyLog.Mismatch, lTy, rTy), loc)

  match lTy, rTy with
  | Ty (MetaTk _, _), _
  | _, Ty (MetaTk _, _) ->
    match lTy, rTy with
    | Ty (MetaTk (l, _), _), Ty (MetaTk (r, _), _) when l = r -> UnifyOk

    | Ty (MetaTk (lSerial, _), _), _ -> UnifyExpandMeta(lSerial, rTy, true)
    | _, Ty (MetaTk (rSerial, _), _) -> UnifyExpandMeta(rSerial, lTy, false)

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
    | Ty (SynonymTk tySerial, tyArgs), _ -> UnifyExpandSynonym(tySerial, tyArgs, rTy, true)
    | _, Ty (SynonymTk tySerial, tyArgs) -> UnifyExpandSynonym(tySerial, tyArgs, lTy, false)
    | _ -> unreachable ()

  | Ty (ErrorTk _, _), _
  | _, Ty (ErrorTk _, _) -> UnifyOk

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

let typingExpandSynonyms tys ty =
  tyExpandSynonyms (fun tySerial -> tys |> TMap.tryFind tySerial) ty
