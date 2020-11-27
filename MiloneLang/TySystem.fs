/// ## Type System
///
/// Provides functions about type system.
///
/// This module is mainly used in Typing and Monomorphizing.
module rec MiloneLang.TySystem

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.TypeIntegers
open MiloneLang.Hir

// -----------------------------------------------
// TyCtor
// -----------------------------------------------

let private tyCtorEncode tyCtor =
  match tyCtor with
  | IntTyCtor flavor -> 1, intFlavorToOrdinary flavor
  | BoolTyCtor -> 2, 0
  | CharTyCtor -> 4, 0
  | StrTyCtor -> 5, 0
  | ObjTyCtor -> 6, 0
  | FunTyCtor -> 7, 0
  | TupleTyCtor -> 8, 0
  | ListTyCtor -> 9, 0

  | SynonymTyCtor tySerial -> 21, tySerial
  | UnionTyCtor tySerial -> 22, tySerial
  | RecordTyCtor tySerial -> 23, tySerial
  | UnresolvedTyCtor serial -> 24, serial

let tyCtorCmp l r =
  pairCmp intCmp intCmp (tyCtorEncode l) (tyCtorEncode r)

let tyCtorEq first second = tyCtorCmp first second = 0

let tyCtorDisplay getTyName tyCtor =
  match tyCtor with
  | IntTyCtor flavor -> fsharpIntegerTyName flavor
  | BoolTyCtor -> "bool"
  | CharTyCtor -> "char"
  | StrTyCtor -> "string"
  | ObjTyCtor -> "obj"
  | FunTyCtor -> "fun"
  | TupleTyCtor -> "tuple"
  | ListTyCtor -> "list"
  | SynonymTyCtor tySerial -> getTyName tySerial
  | RecordTyCtor tySerial -> getTyName tySerial
  | UnionTyCtor tySerial -> getTyName tySerial
  | UnresolvedTyCtor serial -> "?" + string serial

// -----------------------------------------------
// Traits (HIR)
// -----------------------------------------------

let traitMapTys f it =
  match it with
  | AddTrait ty -> AddTrait(f ty)

  | EqTrait ty -> EqTrait(f ty)

  | CmpTrait ty -> CmpTrait(f ty)

  | IndexTrait (lTy, rTy, outputTy) -> IndexTrait(f lTy, f rTy, f outputTy)

  | IsIntTrait ty -> IsIntTrait(f ty)

  | ToIntTrait ty -> ToIntTrait(f ty)

  | ToStringTrait ty -> ToStringTrait(f ty)

// -----------------------------------------------
// Types (HIR/MIR)
// -----------------------------------------------

let tyIsUnit ty =
  match ty with
  | AppTy (TupleTyCtor, []) -> true
  | _ -> false

let tyIsFun ty =
  match ty with
  | AppTy (FunTyCtor, _) -> true
  | _ -> false

let tyCmp first second =
  match first, second with
  | ErrorTy first, ErrorTy second -> locCmp first second

  | ErrorTy _, _ -> -1

  | _, ErrorTy _ -> 1

  | MetaTy (firstSerial, firstLoc), MetaTy (secondSerial, secondLoc) ->
      if firstSerial <> secondSerial then intCmp firstSerial secondSerial else locCmp firstLoc secondLoc

  | MetaTy _, _ -> -1

  | _, MetaTy _ -> 1

  | AppTy (firstTyCtor, firstTys), AppTy (secondTyCtor, secondTys) ->
      let c = tyCtorCmp firstTyCtor secondTyCtor
      if c <> 0 then c else listCmp tyCmp firstTys secondTys

let tyEq first second = tyCmp first second = 0

/// Gets if the specified type variable doesn't appear in a type.
let tyIsFreeIn ty tySerial: bool =
  let rec go ty =
    match ty with
    | ErrorTy _
    | AppTy (_, []) -> true

    | AppTy (tyCtor, ty :: tys) -> go ty && go (AppTy(tyCtor, tys))

    | MetaTy (s, _) -> s <> tySerial

  go ty

/// Gets if the type is monomorphic.
/// Assume all bound type variables are substituted.
let tyIsMonomorphic ty: bool =
  let rec go tys =
    match tys with
    | [] -> true

    | MetaTy _ :: _ -> false

    | ErrorTy _ :: tys -> go tys

    | AppTy (_, tys1) :: tys2 -> go tys1 && go tys2

  go [ ty ]

/// Gets a list of type variables.
/// Assume all bound type variables are substituted.
let tyCollectFreeVars ty =
  let rec go fvAcc tys =
    match tys with
    | [] -> fvAcc

    | ErrorTy _ :: tys
    | AppTy (_, []) :: tys -> go fvAcc tys

    | AppTy (_, tys1) :: tys2 ->
        let acc = go fvAcc tys1
        let acc = go acc tys2
        acc

    | MetaTy (serial, _) :: tys ->
        let acc = serial :: fvAcc
        go acc tys

  go [] [ ty ] |> listUnique intCmp

/// Converts nested function type to multi-arguments function type.
let rec tyToArgList ty =
  let rec go n acc ty =
    match ty with
    | AppTy (FunTyCtor, [ sTy; tTy ]) -> go (n + 1) (sTy :: acc) tTy
    | tTy -> n, List.rev acc, tTy

  go 0 [] ty

/// Substitutes meta types in a type as possible.
let tySubst (substMeta: TySerial -> Ty option) ty =
  let rec go ty =
    match ty with
    | ErrorTy _
    | AppTy (_, []) -> ty

    | AppTy (tyCtor, tys) -> AppTy(tyCtor, List.map go tys)

    | MetaTy (tySerial, _) ->
        match substMeta tySerial with
        | Some ty -> go ty

        | None -> ty

  go ty

/// Converts a type to human readable string.
let tyDisplay getTyName ty =
  let tyEq4 ty1 ty2 ty3 ty4 =
    [ ty2; ty3; ty4 ] |> List.forall (tyEq ty1)

  let rec go (outerBp: int) ty =
    let paren (bp: int) s =
      if bp >= outerBp then s else "(" + s + ")"

    let nominal tySerial args =
      let tyCtor =
        match tySerial |> getTyName with
        | Some name -> name
        | None -> "?" + string tySerial

      match args with
      | [] -> tyCtor
      | _ ->
          let args = args |> List.map (go 0) |> strJoin ", "
          tyCtor + "<" + args + ">"

    match ty with
    | ErrorTy loc -> "{error}@" + locToString loc

    | MetaTy (tySerial, loc) ->
        match getTyName tySerial with
        | Some name -> "{" + name + "}@" + locToString loc
        | None -> "{?" + string tySerial + "}@" + locToString loc

    | AppTy (FunTyCtor, [ sTy; tTy ]) -> paren 10 (go 11 sTy + " -> " + go 10 tTy)

    | AppTy (TupleTyCtor, []) -> "unit"

    | AppTy (TupleTyCtor, itemTys) ->
        "("
        + (itemTys |> List.map (go 20) |> strJoin " * ")
        + ")"

    | AppTy (ListTyCtor, [ itemTy ]) -> paren 30 (go 30 itemTy + " list")

    | AppTy (SynonymTyCtor tySerial, args) -> nominal tySerial args
    | AppTy (UnionTyCtor tySerial, args) -> nominal tySerial args
    | AppTy (RecordTyCtor tySerial, args) -> nominal tySerial args

    | AppTy (tyCtor, args) ->
        let tyCtor =
          tyCtorDisplay (fun _ -> failwith "NEVER") tyCtor

        match args with
        | [] -> tyCtor
        | _ ->
            let args = args |> List.map (go 0) |> strJoin ", "
            tyCtor + "<" + args + ">"

  go 0 ty

// -----------------------------------------------
// Type inference context
// -----------------------------------------------

/// Type inference context.
[<NoEquality; NoComparison>]
type TyContext =
  { Serial: Serial
    LetDepth: LetDepth
    Tys: AssocMap<TySerial, TyDef>
    TyDepths: AssocMap<TySerial, LetDepth> }

let private addTyDef tySerial tyDef (ctx: TyContext) =
  { ctx with
      Tys = ctx.Tys |> mapAdd tySerial tyDef }

// -----------------------------------------------
// Type inference algorithm
// -----------------------------------------------

/// Adds type-var/type binding.
let typingBind (ctx: TyContext) tySerial ty loc =
  // FIXME: track identifier
  let noIdent = "unknown"

  // Don't bind itself.
  match typingSubst ctx ty with
  | MetaTy (s, _) when s = tySerial -> ctx
  | ty ->
      // Reduce depth of meta tys in the referent ty to the meta ty's depth at most.
      let tyDepths =
        let depth = ctx.TyDepths |> mapFind tySerial

        ty
        |> tyCollectFreeVars
        |> List.fold (fun tyDepths tySerial ->
             let currentDepth = ctx.TyDepths |> mapFind tySerial

             if currentDepth <= depth then
               // Already non-deep enough.
               tyDepths
             else
               // Prevent this meta ty from getting generalized until depth of the bound meta ty.
               tyDepths |> mapAdd tySerial depth) ctx.TyDepths

      let ctx =
        ctx
        |> addTyDef tySerial (MetaTyDef(noIdent, ty, loc))

      { ctx with TyDepths = tyDepths }

/// Substitutes occurrences of already-inferred type vars
/// with their results.
let typingSubst (ctx: TyContext) ty: Ty =
  let substMeta tySerial =
    match ctx.Tys |> mapTryFind tySerial with
    | Some (MetaTyDef (_, ty, _)) -> Some ty
    | _ -> None

  tySubst substMeta ty

let tyExpandSynonym useTyArgs defTySerials bodyTy =
  // Checked in NameRes.
  assert (List.length defTySerials = List.length useTyArgs)

  // Expand synonym.
  let assignment = List.zip defTySerials useTyArgs

  let substMeta tySerial =
    assignment |> assocTryFind intCmp tySerial

  tySubst substMeta bodyTy

let tyExpandSynonyms expand ty =
  let rec go ty =
    match ty with
    | AppTy (SynonymTyCtor tySerial, useTyArgs) ->
        match expand tySerial with
        | Some (SynonymTyDef (_, defTySerials, bodyTy, _)) ->
            tyExpandSynonym useTyArgs defTySerials bodyTy
            |> go

        | _ -> AppTy(SynonymTyCtor tySerial, useTyArgs)

    | AppTy (tyCtor, tyArgs) -> AppTy(tyCtor, tyArgs |> List.map go)

    | _ -> ty

  go ty

let typingExpandSynonyms (ctx: TyContext) ty =
  let rec go ty =
    match ty with
    | AppTy (SynonymTyCtor tySerial, useTyArgs) ->
        match ctx.Tys |> mapTryFind tySerial with
        | Some (SynonymTyDef (_, defTySerials, bodyTy, _)) ->
            tyExpandSynonym useTyArgs defTySerials bodyTy
            |> go

        | _ -> AppTy(SynonymTyCtor tySerial, useTyArgs)

    | AppTy (tyCtor, tyArgs) -> AppTy(tyCtor, tyArgs |> List.map go)

    | _ -> ty

  go ty

[<NoEquality; NoComparison>]
type private MetaTyUnifyResult =
  | DidExpand of Ty
  | DidBind of TyContext
  | DidRecurse

let private unifyMetaTy tySerial otherTy loc (ctx: TyContext) =
  match ctx.Tys |> mapTryFind tySerial with
  | Some (MetaTyDef (_, ty, _)) -> DidExpand ty

  | _ ->
      match typingSubst ctx otherTy with
      | MetaTy (otherSerial, _) when otherSerial = tySerial -> DidBind ctx

      | otherTy when tyIsFreeIn otherTy tySerial |> not ->
          // ^ Occurrence check.
          DidRecurse

      | otherTy -> DidBind(typingBind ctx tySerial otherTy loc)

let private isSynonym (ctx: TyContext) tySerial =
  match ctx.Tys |> mapTryFind tySerial with
  | Some (SynonymTyDef _) -> true
  | _ -> false

let private asSynonym (ctx: TyContext) tySerial =
  match ctx.Tys |> mapTryFind tySerial with
  | Some (SynonymTyDef (_, defTySerials, bodyTy, _)) -> defTySerials, bodyTy
  | _ -> failwith "Expected synonym. Check with isSynonym first."

let private unifySynonymTy tySerial useTyArgs loc (ctx: TyContext) =
  let defTySerials, bodyTy = asSynonym ctx tySerial

  // Checked in NameRes.
  assert (List.length defTySerials = List.length useTyArgs)

  let instantiatedTy, ctx =
    let assignment, ctx =
      defTySerials
      |> List.fold (fun (assignment, ctx: TyContext) defTySerial ->
           let newTySerial = ctx.Serial + 1

           let assignment =
             (defTySerial, (MetaTy(newTySerial, loc)))
             :: assignment

           let ctx =
             let tyDepths =
               ctx.TyDepths |> mapAdd newTySerial ctx.LetDepth

             { ctx with
                 Serial = newTySerial
                 TyDepths = tyDepths }

           assignment, ctx) ([], ctx)

    let substMeta tySerial =
      assignment |> assocTryFind intCmp tySerial

    tySubst substMeta bodyTy, ctx

  let expandedTy =
    let assignment = List.zip defTySerials useTyArgs

    let substMeta tySerial =
      assignment |> assocTryFind intCmp tySerial

    tySubst substMeta bodyTy

  expandedTy, instantiatedTy, ctx

/// Solves type equation `lty = rty` as possible
/// to add type-var/type bindings.
let typingUnify logAcc (ctx: TyContext) (lty: Ty) (rty: Ty) (loc: Loc) =
  let lRootTy, rRootTy = lty, rty

  let addLog kind lTy rTy logAcc ctx =
    let lRootTy = typingSubst ctx lRootTy
    let rRootTy = typingSubst ctx rRootTy
    (Log.TyUnify(kind, lRootTy, rRootTy, lTy, rTy), loc)
    :: logAcc,
    ctx

  let rec go lTy rTy (logAcc, ctx) =
    match lTy, rTy with
    | ErrorTy _, _
    | _, ErrorTy _ -> logAcc, ctx

    | MetaTy (l, _), MetaTy (r, _) when l = r -> logAcc, ctx

    | MetaTy (lSerial, loc), _ ->
        match unifyMetaTy lSerial rTy loc ctx with
        | DidExpand ty -> go ty rTy (logAcc, ctx)
        | DidBind ctx -> logAcc, ctx
        | DidRecurse -> addLog TyUnifyLog.SelfRec lTy rTy logAcc ctx

    | _, MetaTy (rSerial, loc) ->
        match unifyMetaTy rSerial lTy loc ctx with
        | DidExpand ty -> go lTy ty (logAcc, ctx)
        | DidBind ctx -> logAcc, ctx
        | DidRecurse -> addLog TyUnifyLog.SelfRec lTy rTy logAcc ctx

    | AppTy (lTyCtor, lTyArgs), AppTy (rTyCtor, rTyArgs) when tyCtorEq lTyCtor rTyCtor ->
        let rec gogo lTyArgs rTyArgs (logAcc, ctx) =
          match lTyArgs, rTyArgs with
          | [], [] -> logAcc, ctx

          | l :: lTyArgs, r :: rTyArgs -> (logAcc, ctx) |> go l r |> gogo lTyArgs rTyArgs

          | _ -> addLog TyUnifyLog.Mismatch lTy rTy logAcc ctx

        gogo lTyArgs rTyArgs (logAcc, ctx)

    | AppTy (SynonymTyCtor tySerial, tyArgs), _ when tySerial |> isSynonym ctx ->
        let ty1, ty2, ctx = unifySynonymTy tySerial tyArgs loc ctx
        (logAcc, ctx) |> go ty1 ty2 |> go ty1 rTy

    | _, AppTy (SynonymTyCtor tySerial, tyArgs) when tySerial |> isSynonym ctx ->
        let ty1, ty2, ctx = unifySynonymTy tySerial tyArgs loc ctx
        (logAcc, ctx) |> go ty1 ty2 |> go ty1 lTy

    | AppTy _, _ -> addLog TyUnifyLog.Mismatch lTy rTy logAcc ctx

  go lty rty (logAcc, ctx)

let typingResolveTraitBound logAcc (ctx: TyContext) theTrait loc =
  let theTrait =
    theTrait
    |> traitMapTys (fun ty -> ty |> typingSubst ctx |> typingExpandSynonyms ctx)

  /// integer, bool, char, or string
  let expectBasic ty (logAcc, ctx) =
    match ty with
    | ErrorTy _
    | AppTy (IntTyCtor _, [])
    | AppTy (BoolTyCtor, [])
    | AppTy (CharTyCtor, [])
    | AppTy (StrTyCtor, []) -> logAcc, ctx

    | _ -> (Log.TyBoundError theTrait, loc) :: logAcc, ctx

  match theTrait with
  | AddTrait ty ->
      match ty with
      | ErrorTy _
      | AppTy (IntTyCtor _, [])
      | AppTy (CharTyCtor _, [])
      | AppTy (StrTyCtor, []) -> logAcc, ctx

      | _ ->
          // Coerce to int by default.
          typingUnify logAcc ctx ty tyInt loc

  | EqTrait ty -> (logAcc, ctx) |> expectBasic ty

  | CmpTrait ty -> (logAcc, ctx) |> expectBasic ty

  | IndexTrait (lTy, rTy, resultTy) ->
      match lTy with
      | ErrorTy _ -> [], ctx

      | AppTy (StrTyCtor, []) ->
          let logAcc, ctx = typingUnify logAcc ctx rTy tyInt loc

          let logAcc, ctx =
            typingUnify logAcc ctx resultTy tyChar loc

          logAcc, ctx

      | _ -> (Log.TyBoundError theTrait, loc) :: logAcc, ctx

  | IsIntTrait ty ->
      match ty with
      | ErrorTy _
      | AppTy (IntTyCtor _, []) -> logAcc, ctx

      | _ ->
          // Coerce to int by default.
          typingUnify logAcc ctx ty tyInt loc

  | ToIntTrait ty ->
      match ty with
      | ErrorTy _
      | AppTy (IntTyCtor _, [])
      | AppTy (CharTyCtor, [])
      | AppTy (StrTyCtor, []) -> logAcc, ctx

      | _ -> (Log.TyBoundError theTrait, loc) :: logAcc, ctx

  | ToStringTrait ty -> (logAcc, ctx) |> expectBasic ty
