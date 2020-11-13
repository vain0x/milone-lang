/// ## Type System
///
/// Provides functions about type system.
///
/// This module is mainly used in Typing and Monomorphizing.
module rec MiloneLang.TySystem

open MiloneLang.Types
open MiloneLang.Records
open MiloneLang.Helpers

// -----------------------------------------------
// TyCtor
// -----------------------------------------------

let tyCtorToInt tyCtor =
  match tyCtor with
  | BoolTyCtor -> 1

  | IntTyCtor -> 2

  | UIntTyCtor -> 9

  | CharTyCtor -> 3

  | StrTyCtor -> 4

  | ObjTyCtor -> 5

  | FunTyCtor -> 6

  | TupleTyCtor -> 7

  | ListTyCtor -> 8

  | RefTyCtor tySerial ->
      assert (tySerial >= 0)
      10 + tySerial

let tyCtorHash tyCtor = tyCtor |> tyCtorToInt |> intHash

let tyCtorCmp first second =
  intCmp (tyCtorToInt first) (tyCtorToInt second)

let tyCtorEq first second = tyCtorCmp first second = 0

let tyCtorDisplay getTyIdent tyCtor =
  match tyCtor with
  | BoolTyCtor -> "bool"
  | IntTyCtor -> "int"
  | UIntTyCtor -> "uint"
  | CharTyCtor -> "char"
  | StrTyCtor -> "string"
  | ObjTyCtor -> "obj"
  | FunTyCtor -> "fun"
  | TupleTyCtor -> "tuple"
  | ListTyCtor -> "list"
  | RefTyCtor tySerial -> getTyIdent tySerial

// -----------------------------------------------
// Traits (HIR)
// -----------------------------------------------

let traitMapTys f it =
  match it with
  | AddTrait ty -> AddTrait(f ty)

  | ScalarTrait ty -> ScalarTrait(f ty)

  | EqTrait ty -> EqTrait(f ty)

  | CmpTrait ty -> CmpTrait(f ty)

  | IndexTrait (lTy, rTy, outputTy) -> IndexTrait(f lTy, f rTy, f outputTy)

  | ToIntTrait ty -> ToIntTrait(f ty)

  | ToStringTrait ty -> ToStringTrait(f ty)

// -----------------------------------------------
// Types (HIR/MIR)
// -----------------------------------------------

let tyHash ty: uint =
  match ty with
  | ErrorTy _ -> intHash 1

  | MetaTy (tySerial, _) -> intHash 2 |> hashCombine (intHash tySerial)

  | AppTy (tyCtor, tys) ->
      intHash 3
      |> hashCombine (tyCtorHash tyCtor)
      |> hashCombine (listHash tyHash tys)

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

let tyPrimFromIdent ident tys loc =
  match ident, tys with
  | "unit", [] -> tyUnit

  | "bool", [] -> tyBool

  | "int", [] -> tyInt

  | "uint", [] -> tyUInt

  | "char", [] -> tyChar

  | "string", [] -> tyStr

  | "obj", [] -> tyObj

  | "option", [ itemTy ] ->
      // FIXME: option is just an alias of list for now
      tyList itemTy

  | "list", [ itemTy ] -> tyList itemTy

  | "AssocMap", [ keyTy; valueTy ] -> tyAssocMap keyTy valueTy

  | "AssocSet", [ itemTy ] -> tyAssocMap itemTy tyUnit

  | _ ->
      printfn "#error tyPrimFromIdent ident=%s loc=%s" ident (locToString loc)
      ErrorTy loc

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
///
/// getTyIdent: serial -> ident option. Gets ident of type by serial.
let tyDisplay getTyIdent ty =
  let tyEq4 ty1 ty2 ty3 ty4 =
    [ ty2; ty3; ty4 ] |> List.forall (tyEq ty1)

  let rec go (outerBp: int) ty =
    let paren (bp: int) s =
      if bp >= outerBp then s else "(" + s + ")"

    match ty with
    | ErrorTy loc -> "{error}@" + locToString loc

    | MetaTy (tySerial, loc) ->
        match getTyIdent tySerial with
        | Some ident -> "{" + ident + "}@" + locToString loc
        | None -> "{?" + string tySerial + "}@" + locToString loc

    | AppTy (FunTyCtor, [ sTy; tTy ]) -> paren 10 (go 11 sTy + " -> " + go 10 tTy)

    // AssocMap
    | AppTy (TupleTyCtor,
             [
               // trie
               AppTy (ListTyCtor,
                      [ AppTy (TupleTyCtor,
                               [
                                 // hash
                                 AppTy (UIntTyCtor, _);
                                 // assoc
                                 AppTy (ListTyCtor, [ AppTy (TupleTyCtor, [ keyTy1; valueTy ]) ]) ]) ]);
               // hash fun
               AppTy (FunTyCtor, [ keyTy2; AppTy (UIntTyCtor, _) ]);
               // compare fun
               AppTy (FunTyCtor, [ keyTy3; AppTy (FunTyCtor, [ keyTy4; AppTy (IntTyCtor, _) ]) ]) ]) when tyEq4
                                                                                                            keyTy1
                                                                                                            keyTy2
                                                                                                            keyTy3
                                                                                                            keyTy4 ->
        match valueTy with
        | AppTy (TupleTyCtor, []) -> "AssocSet<" + go 0 keyTy1 + ">"
        | _ ->
            "AssocMap<"
            + go 0 keyTy1
            + ", "
            + go 0 valueTy
            + ">"

    | AppTy (TupleTyCtor, []) -> "unit"

    | AppTy (TupleTyCtor, itemTys) ->
        "("
        + (itemTys |> List.map (go 20) |> strJoin " * ")
        + ")"

    | AppTy (ListTyCtor, [ itemTy ]) -> paren 30 (go 30 itemTy + " list")

    | AppTy (RefTyCtor tySerial, args) ->
        let tyCtor =
          match tySerial |> getTyIdent with
          | Some ident -> ident
          | None -> "?" + string tySerial

        match args with
        | [] -> tyCtor
        | _ ->
            let args = args |> List.map (go 0) |> strJoin ", "
            tyCtor + "<" + args + ">"

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

    | AppTy _, _ -> addLog TyUnifyLog.Mismatch lTy rTy logAcc ctx

  go lty rty (logAcc, ctx)

let typingResolveTraitBound logAcc (ctx: TyContext) theTrait loc =
  let theTrait =
    theTrait |> traitMapTys (typingSubst ctx)

  let expectScalar ty (logAcc, ctx) =
    match ty with
    | ErrorTy _
    | AppTy (BoolTyCtor, [])
    | AppTy (IntTyCtor, [])
    | AppTy (UIntTyCtor, [])
    | AppTy (CharTyCtor, [])
    | AppTy (StrTyCtor, []) -> logAcc, ctx

    | _ -> (Log.TyBoundError theTrait, loc) :: logAcc, ctx

  match theTrait with
  | AddTrait ty ->
      match ty with
      | ErrorTy _
      | AppTy (UIntTyCtor, [])
      | AppTy (StrTyCtor, []) -> logAcc, ctx

      | _ ->
          // Coerce to int by default.
          typingUnify logAcc ctx ty tyInt loc

  | ScalarTrait ty ->
      match ty with
      | ErrorTy _
      | AppTy (IntTyCtor, [])
      | AppTy (UIntTyCtor, []) -> logAcc, ctx

      | _ ->
          // Coerce to int by default.
          typingUnify logAcc ctx ty tyInt loc

  | EqTrait ty -> (logAcc, ctx) |> expectScalar ty

  | CmpTrait ty -> (logAcc, ctx) |> expectScalar ty

  | IndexTrait (lTy, rTy, resultTy) ->
      match lTy with
      | ErrorTy _ -> [], ctx

      | AppTy (StrTyCtor, []) ->
          let logAcc, ctx = typingUnify logAcc ctx rTy tyInt loc

          let logAcc, ctx =
            typingUnify logAcc ctx resultTy tyChar loc

          logAcc, ctx

      | _ -> (Log.TyBoundError theTrait, loc) :: logAcc, ctx

  | ToIntTrait ty -> (logAcc, ctx) |> expectScalar ty

  | ToStringTrait ty -> (logAcc, ctx) |> expectScalar ty
