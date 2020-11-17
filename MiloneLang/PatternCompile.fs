module rec MiloneLang.PatternCompile

open MiloneLang.Helpers
open MiloneLang.Types
open MiloneLang.TySystem
open MiloneLang.Typing

let private litCmp l r =
  match l, r with
  | BoolLit l, BoolLit r -> (if l then 1 else 0) - (if r then 1 else 0)
  | BoolLit _, _ -> -1
  | _, BoolLit _ -> 1

  | IntLit l, IntLit r -> intCmp l r
  | IntLit _, _ -> -1
  | _, IntLit _ -> 1

  | CharLit l, CharLit r -> intCmp (int l) (int r)
  | CharLit _, _ -> -1
  | _, CharLit _ -> 1

  | StrLit l, StrLit r -> strCmp l r

// -----------------------------------------------
// PIR
// -----------------------------------------------

// Intermediate representation for pattern matching compilation.
// OR patterns and AS patterns are collapsed.

/// Constant value.
type private PConst =
  | PLitConst of Lit
  | PVariantTagConst of VariantSerial

type private ConstVariant =
  | NoneVariant
  | NilVariant
  | ConstVariant of VariantSerial

type private FunVariant =
  | SomeVariant
  | FunVariant of VariantSerial

/// Type that affects pattern matching.
type private PTy =
  | PBoolTy
  | PTupleTy of PTy list
  | PListTy of PTy

  /// Type that could match with literal patterns but never be exhaustive: int, char, string.
  | PLitTy

  /// Type that cannot be handled by pattern matching such as functions.
  | PUnknownTy // of Ty

/// Pattern.
type private PPat =
  | LitPat of Lit

  | WildcardPat

  | NilPat
  | ConsPat of (PPat * VarSerial option) * (PPat * VarSerial option)

  | NonePat
  | SomePat of (PPat * VarSerial option)

  | ConstVariantPat of VariantSerial
  | FunVariantPat of FunVariant * (PPat * VarSerial option)
  | TuplePat of (PPat * VarSerial option) list

type private PPath =
  | PSelfPath

  | PSomeContentPath
  | PHeadPath of PPath
  | PTailPath of PPath
  | PVariantTagPath
  | PVariantPayloadPath

  /// i'th field of tuple
  | PItemPath of index: int * PPath

type private PCond = PPath

type private PTerm =
  /// Evaluating this term causes runtime error. Represents the end of non-exhaustive matching.
  | PAbortTerm

  /// Some part of `cond` value provided to current pattern matching.
  | PCondTerm of VarSerial * PPath

  /// Use of i'th clause's guard.
  | PGuardTerm of clauseIndex: int * body: PTerm * alt: PTerm

  /// i'th clause's body
  | PBodyTerm of clauseIndex: int

  | PLetTerm of VarSerial * init: PPath * next: PTerm

  | PIfTerm of cond: PCond * body: PTerm * alt: PTerm

  /// Conditional branching on some scalar or string.
  | PSwitchTerm of cond: PCond * cases: (PConst * PTerm) list * defaultCl: PTerm

  | PMatchListTerm of cond: PCond * nilCl: PTerm * consCl: PTerm

  | PMatchOptionTerm of cond: PCond * noneCl: PTerm * someCl: PTerm

  /// Flat pattern matching on union type.
  ///
  /// All variants must be of the same type.
  | PMatchUnionTerm of cond: PCond * clauses: (VariantSerial * PTerm) list

type private ClauseIndex = int

/// (clause index, patterns, is guarded, binding list).
///
/// Internal representation of clause.
type private PClause = ClauseIndex * (PPat * VarSerial option) list * bool * PTerm

/// Wraps an term in `let` expression if a variable is provided (optionally).
///
/// FIXME: the variable should be used as condition for rest of pattern matching.
let private tryBind (varOpt: VarSerial option) (cond: PPath) term: PTerm =
  match varOpt with
  | Some v -> PLetTerm(v, cond, term)
  | None -> term

/// -1 pat.
let private matchOnUnknownTy (cond: PCond) (clauses: PClause list): PClause list =
  clauses
  |> List.map (fun clause ->
       let ci, pats, isGuarded, body = clause

       match pats with
       | (WildcardPat, varOpt) :: pats ->
           let body = tryBind varOpt cond body
           ci, pats, isGuarded, body

       | _ -> failwith "NEVER: Type error.")

/// -1 pat.
let private matchOnLitTy (cond: PCond) (clauses: PClause list): AssocMap<Lit, PClause list> * PClause list =
  let rec go (clauses: PClause list) =
    match clauses with
    | [] -> mapEmpty litCmp, []

    | (ci, pats, isGuarded, body) :: clauses ->
        let cases, defaultClauses = go clauses

        match pats with
        | (LitPat lit, varOpt) :: pats ->
            let caseMap =
              let body = tryBind varOpt cond body

              let clauses =
                cases |> mapTryFind lit |> Option.defaultValue []

              cases
              |> mapAdd lit ((ci, pats, isGuarded, body) :: clauses)

            caseMap, defaultClauses

        | (WildcardPat, varOpt) :: pats ->
            let defaultClauses =
              let body = tryBind varOpt cond body
              (ci, pats, isGuarded, body) :: defaultClauses

            cases, defaultClauses

        | _ -> failwith "NEVER: Type error."

  go clauses

let private matchOnTupleTy (itemTys: _ list) (cond: PCond) clauses =
  clauses
  |> List.map (fun clause ->
       let ci, pats, isGuarded, body = clause

       match pats with
       | (TuplePat itemPats, varOpt) :: pats ->
           assert (List.length itemPats = List.length itemTys)

           let body = tryBind varOpt cond body
           let pats = List.append itemPats pats
           ci, pats, isGuarded, body

       | (WildcardPat, varOpt) :: pats ->
           let body = tryBind varOpt cond body

           let pats =
             itemTys
             |> List.fold (fun pats _ -> (WildcardPat, None) :: pats) pats

           ci, pats, isGuarded, body

       | _ -> failwith "NEVER: Type error.")

/// (true clauses, false clauses).
///
/// Both -1 pat.
let private matchOnBoolTy cond (clauses: PClause list): PClause list * PClause list =
  let rec go clauses =
    match clauses with
    | [] -> [], []

    | (ci, pats, isGuarded, body) :: clauses ->
        let trueClauses, falseClauses = go clauses

        match pats with
        | (LitPat (BoolLit true), varOpt) :: pats ->
            let body = tryBind varOpt cond body

            let trueClauses =
              (ci, pats, isGuarded, body) :: trueClauses

            trueClauses, falseClauses

        | (LitPat (BoolLit false), varOpt) :: pats ->
            let body = tryBind varOpt cond body

            let falseClauses =
              (ci, pats, isGuarded, body) :: falseClauses

            trueClauses, falseClauses

        | (WildcardPat, varOpt) :: pats ->
            let body = tryBind varOpt cond body

            let clause: PClause = ci, pats, isGuarded, body

            clause :: trueClauses, clause :: falseClauses

        | _ -> failwith "NEVER: Type error."

  go clauses

/// (hasCons, nil clauses, cons clauses).
///
/// Nil clauses: -1 pat. Cons clauses: +1 pat.
let private matchOnListTy cond (clauses: PClause list): bool * PClause list * PClause list =
  let rec go clauses =
    match clauses with
    | [] -> false, [], []

    | (ci, pats, isGuarded, body) :: clauses ->
        let hasCons, nilClauses, consClauses = go clauses

        match pats with
        | (NilPat, varOpt) :: pats ->
            let body = tryBind varOpt cond body

            let nilClauses =
              (ci, pats, isGuarded, body) :: nilClauses

            hasCons, nilClauses, consClauses

        | (ConsPat (head, tail), varOpt) :: pats ->
            let body = tryBind varOpt cond body

            let consClauses =
              (ci, head :: tail :: pats, isGuarded, body)
              :: consClauses

            true, nilClauses, consClauses

        | (WildcardPat, varOpt) :: pats ->
            let nilClauses =
              let body = tryBind varOpt cond body
              (ci, pats, isGuarded, body) :: nilClauses

            let consClauses =
              let body = tryBind varOpt cond body
              (ci, (WildcardPat, None) :: (WildcardPat, None) :: pats, isGuarded, body)
              :: consClauses

            hasCons, nilClauses, consClauses

        | _ -> failwith "NEVER: Type error."

  go clauses

/// (exhaustivity, compiled match expression).
///
/// Compiles pattern matching.
let private doCompile (conds: (PPath * PTy) list) (clauses: PClause list): bool * PTerm =
  match conds with
  | [] ->
      let rec go (clauses: PClause list) =
        match clauses with
        | [] ->
            // Not exhaustive.
            false, PAbortTerm

        | (_, _, false, body) :: _ ->
            // Success of exhaustive matching.
            true, body

        | (clauseIndex, _, true, body) :: clauses ->
            let exhaustive, alt = go clauses
            let body = PGuardTerm(clauseIndex, body, alt)
            exhaustive, body

      go clauses

  | (cond, PBoolTy) :: conds ->
      let trueClauses, falseClauses = matchOnBoolTy cond clauses

      let trueExhaust, trueBody = doCompile conds trueClauses
      let falseExhaust, falseBody = doCompile conds falseClauses

      let exhaust = trueExhaust && falseExhaust
      let body = PIfTerm(cond, trueBody, falseBody)
      exhaust, body

  | (cond, PTupleTy itemTys) :: conds ->
      let clauses = matchOnTupleTy itemTys cond clauses

      let conds =
        let itemConds =
          itemTys
          |> List.mapi (fun i itemTy -> (PItemPath(i, cond), itemTy))

        List.append itemConds conds

      doCompile conds clauses

  | (cond, (PListTy itemTy as listTy)) :: conds ->
      let hasCons, nilClauses, consClauses = matchOnListTy cond clauses

      // If clauses contain no `::` patterns, the tail part can be handled
      // only by wildcard patterns, which is now equivalent to unknown type.
      // Without this, infinite recursion.
      let tailTy = if hasCons then listTy else PUnknownTy

      let nilExhaust, nilBody = doCompile conds nilClauses

      let consExhaust, consBody =
        doCompile
          ((PHeadPath cond, itemTy)
           :: (PTailPath cond, tailTy)
           :: conds)
          consClauses

      let exhaust = nilExhaust && consExhaust
      let body = PMatchListTerm(cond, nilBody, consBody)
      exhaust, body

  | (cond, PLitTy _) :: conds ->
      let caseMap, defaultClauses = matchOnLitTy cond clauses

      if caseMap |> mapIsEmpty then
        // Avoid generating redundant, default-only switch.
        doCompile conds defaultClauses
      else
        let cases =
          caseMap
          |> mapFold (fun acc lit clauses ->
               let _, body = doCompile conds clauses
               (PLitConst lit, body) :: acc) []

        let exhaust, defaultBody = doCompile conds defaultClauses

        exhaust, PSwitchTerm(cond, cases, defaultBody)

  | (cond, PUnknownTy _) :: conds ->
      let clauses = matchOnUnknownTy cond clauses

      doCompile conds clauses

// -----------------------------------------------
// Context
// -----------------------------------------------

type private PcCtx =
  { Vars: AssocMap<VarSerial, VarDef>
    Tys: AssocMap<TySerial, TyDef> }

let private ofTyCtx (tyCtx: TyCtx): PcCtx = { Vars = tyCtx.Vars; Tys = tyCtx.Tys }

let private toTyCtx (tyCtx: TyCtx) (ctx: PcCtx): TyCtx = { tyCtx with Vars = ctx.Vars }

// -----------------------------------------------
// HIR types/patterns to PIR
// -----------------------------------------------

let private pcTy (ctx: PcCtx) ty: PTy =
  match ty with
  | AppTy (BoolTyCtor, _) -> PBoolTy

  | AppTy (IntTyCtor, _)
  | AppTy (CharTyCtor, _)
  | AppTy (StrTyCtor, _) -> PLitTy

  | AppTy (TupleTyCtor, itemTys) ->
      let itemTys = itemTys |> List.map (pcTy ctx)
      PTupleTy itemTys

  | AppTy (ListTyCtor, tyArgs) ->
      match tyArgs with
      | [ itemTy ] ->
          let itemTy = itemTy |> pcTy ctx
          PListTy itemTy

      | _ -> failwith "NEVER"

  | _ -> PUnknownTy

let private pcPat (ctx: PcCtx) pat: PPat * VarSerial option =
  let todo () = failwithf "unimplemented. %A" pat

  match pat with
  | HLitPat (lit, _) -> LitPat lit, None

  | HNilPat _ -> NilPat, None

  | HNonePat _
  | HSomePat _ -> todo ()

  | HDiscardPat _ -> WildcardPat, None

  | HRefPat (varSerial, _, _) ->
      match ctx.Vars |> mapTryFind varSerial with
      | Some (VarDef _) -> WildcardPat, Some varSerial
      | Some (VariantDef _) -> todo ()
      | _ -> failwithf "NEVER: Fun pattern? %A" pat

  | HConsPat (l, r, _, _) ->
      let l = l |> pcPat ctx
      let r = r |> pcPat ctx
      ConsPat(l, r), None

  | HTuplePat ([], _, _) -> TuplePat [], None

  | HTuplePat (itemPats, _, _) ->
      let itemPats = itemPats |> List.map (pcPat ctx)
      TuplePat itemPats, None

  | HCallPat (callee, args, _, _) ->
      match callee, args with
      | HSomePat _, [ payload ] -> SomePat(pcPat ctx payload), None

      | _ -> todo ()

  | HAsPat (bodyPat, varSerial, _) ->
      match pcPat ctx bodyPat with
      | bodyPat, None -> bodyPat, Some varSerial

      | _, Some _ ->
          // This happens when `v as u` or `(_ as u) as w` etc. This should be error in typing?
          todo ()

  | HOrPat _ -> todo ()

  | HNavPat _ -> failwith "NEVER: HNavPat is resolved in NameRes"
  | HBoxPat _ -> failwith "NEVER: HBoxPat is generated in AutoBoxing"
  | HAnnoPat _ -> failwith "NEVER: HAnnoPat is resolved in Typing."

// -----------------------------------------------
// Control
// -----------------------------------------------

let private pcExpr (expr, ctx: PcCtx) =
  let todo () = failwithf "unimplemented. %A" expr

  match expr with
  | HMatchExpr (cond, arms, ty, loc) ->
      printfn "\nmatch expr: %s\n" (objToString ("match:", cond, arms, ty, loc))

      let condTy = cond |> exprToTy |> pcTy ctx

      let clauses: PClause list =
        arms
        |> List.mapi (fun (ci: ClauseIndex) (pat, guard, _body) ->
             let pat = pat |> pcPat ctx
             let isGuarded = guard |> hxIsAlwaysTrue |> not
             ci, [ pat ], isGuarded, PBodyTerm ci)

      let exhaustive, term = doCompile [ PSelfPath, condTy ] clauses
      printfn "\nmatch result: %s\n" (objToString (exhaustive, term))

      expr, ctx

  | HLetValExpr (vis, pat, body, next, ty, loc) ->
      // unimplemented
      let doArm () =
        // let pat = pat |> pcPat ctx
        let body, ctx = (body, ctx) |> pcExpr
        let next, ctx = (next, ctx) |> pcExpr
        HLetValExpr(vis, pat, body, next, ty, loc), ctx

      doArm ()

  | HLetFunExpr (callee, vis, isMainFun, args, body, next, ty, loc) ->
      // unimplemented

      let doArm () =
        let body, ctx = (body, ctx) |> pcExpr
        let next, ctx = (next, ctx) |> pcExpr
        HLetFunExpr(callee, vis, isMainFun, args, body, next, ty, loc), ctx

      doArm ()

  | HLitExpr _
  | HPrimExpr _
  | HRefExpr _
  | HTyDeclExpr _
  | HOpenExpr _ -> expr, ctx

  | HNavExpr (l, r, ty, loc) ->
      let doArm () =
        let l, ctx = (l, ctx) |> pcExpr
        HNavExpr(l, r, ty, loc), ctx

      doArm ()

  | HInfExpr (infOp, items, ty, loc) ->
      let doArm () =
        let items, ctx = (items, ctx) |> stMap pcExpr
        HInfExpr(infOp, items, ty, loc), ctx

      doArm ()

  | HErrorExpr (error, loc) -> failwithf "Never: %s at %A" error loc
  | HRecordExpr _ -> failwith "NEVER: record expr is resolved in type elaborating"
  | HModuleExpr _ -> failwith "NEVER: module is resolved in name res"

// -----------------------------------------------
// Interface
// -----------------------------------------------

let patternCompile (expr: HExpr, tyCtx: TyCtx) =
  let ctx = ofTyCtx tyCtx

  let expr, ctx = (expr, ctx) |> pcExpr

  let tyCtx = ctx |> toTyCtx tyCtx
  expr, tyCtx
