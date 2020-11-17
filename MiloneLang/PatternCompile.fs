/// # PatternCompile
///
/// Decomposes complex pattern matching into nested if/switch and let expressions for ease of code generation.
///
/// Current algorithm is not optimal yet straightforward.
///
/// ## See also
///
/// - [Semantic Domain\: Pattern compilation made easy](https://semantic-domain.blogspot.com/2012/08/pattern-compilation-made-easy.html)
/// - [Semantic Domain\: An ML implementation of match compilation](https://semantic-domain.blogspot.com/2012/08/an-ml-implementation-of-match.html)
module rec MiloneLang.PatternCompile

open MiloneLang.Helpers
open MiloneLang.Types
open MiloneLang.TySystem
open MiloneLang.Typing

let private boolCmp l r =
  (if l then 1 else 0) - (if r then 1 else 0)

let private litCmp l r =
  match l, r with
  | BoolLit l, BoolLit r -> boolCmp l r
  | BoolLit _, _ -> -1
  | _, BoolLit _ -> 1

  | IntLit l, IntLit r -> intCmp l r
  | IntLit _, _ -> -1
  | _, IntLit _ -> 1

  | CharLit l, CharLit r -> int l - int r
  | CharLit _, _ -> -1
  | _, CharLit _ -> 1

  | StrLit l, StrLit r -> strCmp l r

/// ## Intermediate representation (PIR)
///
/// PIR is intermediate representation for pattern matching compilation.
///
/// ### Elaboration
///
/// Some kind of patterns in HIR are excluded from PIR.
/// Such pattern must be elaborated while lowering.
///
/// *OR*: Patterns including `|` are normalized to disjunctive normal form (DNF) by applying distribution law.
/// E.g. `(0 | 1), (2 | 3)`
///   => `(0, 2) | (0, 3) | (1, 2) | (1, 3)`
///
/// And then match clauses are duplicated for each pattern separated by `|`. E.g.
///
/// ```fsharp
///   match x with
///   | 0
///   | 1 => f ()
/// //=>
///   match x with
///   | 0 => f ()
///   | 1 => f ()
/// ```
///
/// (This behavior makes complexity of compile time and generated code size exponential at worst, though.)
///
/// *Binding*: Variable patterns and `as` patterns are not available in PIR.
/// Instead, every sub-pattern in PIR can have a variable that is assigned to.
/// In other words, PIR patterns are in form of:
///
/// - `<pattern> as <variable>`, or
/// - `<pattern> as _`.
///
/// E.g. `(x, _) as t` in HIR
///   => `((_ as x), (_ as _)) as t` in PIR

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

  /// Type that can match with literal patterns
  /// but never be exhaustive with them: int, char, string.
  | PLitTy

  /// Type that cannot be handled by pattern matching such as functions.
  | PUnknownTy

/// Pattern.
type private PPat =
  | WildcardPat
  | TuplePat of (PPat * VarSerial option) list

  | LitPat of Lit

  | NilPat
  | ConsPat of (PPat * VarSerial option) * (PPat * VarSerial option)

  | NonePat
  | SomePat of PPat * VarSerial option

  | ConstVariantPat of VariantSerial
  | FunVariantPat of FunVariant * (PPat * VarSerial option)

type private PPath =
  | PSelfPath

  | PSomeContentPath of PPath
  | PHeadPath of PPath
  | PTailPath of PPath
  | PVariantTagPath of PPath
  | PVariantPayloadPath of PPath

  /// i'th field of tuple
  | PItemPath of index: int * PPath

type private PCond = PPath

type private PTerm =
  /// Evaluating this term causes runtime error. Represents the end of non-exhaustive matching.
  | PAbortTerm

  /// Some part of `cond` value provided to current pattern matching.
  | PCondTerm of VarSerial * PPath

  /// i'th clause's body
  | PBodyTerm of clauseIndex: int

  /// Use of i'th clause's guard.
  | PGuardTerm of clauseIndex: int * body: PTerm * alt: PTerm

  | PLetTerm of VarSerial * init: PCond * next: PTerm

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

/// (clauseIndex, pats, isGuarded, holedTerm).
///
/// Internal representation of clause.
type private PClause = ClauseIndex * (PPat * VarSerial option) list * bool * (PTerm -> PTerm)

/// Wraps a term in `let` expression if a variable is provided (optionally).
///
/// FIXME: the variable should be used as condition for rest of pattern matching.
let private tryBind (varOpt: VarSerial option) (cond: PPath) hole =
  match varOpt with
  | Some v -> fun term -> PLetTerm(v, cond, hole term)
  | None -> hole

/// -1 pat.
let private matchOnUnknownTy (cond: PCond) (clauses: PClause list): PClause list =
  clauses
  |> List.map (fun clause ->
       let ci, pats, isGuarded, hole = clause

       match pats with
       | (WildcardPat, varOpt) :: pats ->
           let hole = tryBind varOpt cond hole
           ci, pats, isGuarded, hole

       | _ -> failwith "NEVER: Type error.")

/// +(N-1) pats, where N: number of items.
let private matchOnTupleTy (itemTys: _ list) (cond: PCond) clauses =
  clauses
  |> List.map (fun clause ->
       let ci, pats, isGuarded, hole = clause

       match pats with
       | (TuplePat itemPats, varOpt) :: pats ->
           assert (List.length itemPats = List.length itemTys)

           let hole = tryBind varOpt cond hole
           let pats = List.append itemPats pats
           ci, pats, isGuarded, hole

       | (WildcardPat, varOpt) :: pats ->
           let hole = tryBind varOpt cond hole

           let pats =
             itemTys
             |> List.fold (fun pats _ -> (WildcardPat, None) :: pats) pats

           ci, pats, isGuarded, hole

       | _ -> failwith "NEVER: Type error.")

/// (true clauses, false clauses).
///
/// Both -1 pat.
let private matchOnBoolTy cond (clauses: PClause list): PClause list * PClause list =
  let rec go clauses =
    match clauses with
    | [] -> [], []

    | (ci, pats, isGuarded, hole) :: clauses ->
        let trueClauses, falseClauses = go clauses

        match pats with
        | (LitPat (BoolLit true), varOpt) :: pats ->
            let hole = tryBind varOpt cond hole

            let trueClauses =
              (ci, pats, isGuarded, hole) :: trueClauses

            trueClauses, falseClauses

        | (LitPat (BoolLit false), varOpt) :: pats ->
            let hole = tryBind varOpt cond hole

            let falseClauses =
              (ci, pats, isGuarded, hole) :: falseClauses

            trueClauses, falseClauses

        | (WildcardPat, varOpt) :: pats ->
            let hole = tryBind varOpt cond hole

            let clause: PClause = ci, pats, isGuarded, hole

            clause :: trueClauses, clause :: falseClauses

        | _ -> failwith "NEVER: Type error."

  go clauses

/// -1 pat.
let private matchOnLitTy (cond: PCond) (clauses: PClause list): AssocMap<Lit, PClause list> * PClause list =
  let rec go (clauses: PClause list) =
    match clauses with
    | [] -> mapEmpty (fun l r -> litCmp r l), []

    | (ci, pats, isGuarded, hole) :: clauses ->
        let cases, defaultClauses = go clauses

        match pats with
        | (LitPat lit, varOpt) :: pats ->
            let caseMap =
              let hole = tryBind varOpt cond hole

              let clauses =
                cases |> mapTryFind lit |> Option.defaultValue []

              cases
              |> mapAdd lit ((ci, pats, isGuarded, hole) :: clauses)

            caseMap, defaultClauses

        | (WildcardPat, varOpt) :: pats ->
            let defaultClauses =
              let hole = tryBind varOpt cond hole
              (ci, pats, isGuarded, hole) :: defaultClauses

            cases, defaultClauses

        | _ -> failwith "NEVER: Type error."

  go clauses

/// (nil clauses, cons clauses).
///
/// Nil clauses: -1 pat. Cons clauses: +1 pat.
let private matchOnListTy cond (clauses: PClause list): PClause list * PClause list =
  let rec go clauses =
    match clauses with
    | [] -> [], []

    | (ci, pats, isGuarded, hole) :: clauses ->
        let nilClauses, consClauses = go clauses

        match pats with
        | (NilPat, varOpt) :: pats ->
            let hole = tryBind varOpt cond hole

            let nilClauses =
              (ci, pats, isGuarded, hole) :: nilClauses

            nilClauses, consClauses

        | (ConsPat (head, tail), varOpt) :: pats ->
            let hole = tryBind varOpt cond hole

            let consClauses =
              (ci, head :: tail :: pats, isGuarded, hole)
              :: consClauses

            nilClauses, consClauses

        | (WildcardPat, varOpt) :: pats ->
            let nilClauses =
              let hole = tryBind varOpt cond hole
              (ci, pats, isGuarded, hole) :: nilClauses

            let consClauses =
              let hole = tryBind varOpt cond hole
              (ci, (WildcardPat, None) :: (WildcardPat, None) :: pats, isGuarded, hole)
              :: consClauses

            nilClauses, consClauses

        | _ -> failwith "NEVER: Type error."

  go clauses

/// (exhaustive, compiled match expression).
///
/// Compiles pattern matching.
let private doCompile (conds: (PPath * PTy) list) (clauses: PClause list): bool * PTerm =
  let nextPatIsAllWildcard () =
    clauses
    |> List.forall (fun clause ->
         let _, pats, _, _ = clause
         match pats with
         | (WildcardPat, _) :: _ -> true
         | _ -> false)

  match conds with
  | [] ->
      // After all conditions are processed.

      let rec go (clauses: PClause list) =
        match clauses with
        | [] ->
            // Not exhaustive.
            false, PAbortTerm

        | (clauseIndex, pats, isGuarded, hole) :: clauses ->
            // Because length(pats) = length(conds (= [])).
            assert (List.isEmpty pats)

            if isGuarded then
              // if guard() then <enter this clause> else <try rest clauses>
              let exhaustive, alt = go clauses
              exhaustive, hole (PGuardTerm(clauseIndex, PBodyTerm clauseIndex, alt))
            else
              true, hole (PBodyTerm clauseIndex)

      go clauses

  | (cond, PUnknownTy _) :: conds ->
      let clauses = matchOnUnknownTy cond clauses
      doCompile conds clauses

  | (cond, _) :: conds when nextPatIsAllWildcard () ->
      // No nested matching or branching occurs on this condition.
      let clauses = matchOnUnknownTy cond clauses
      doCompile conds clauses

  | (cond, PTupleTy itemTys) :: conds ->
      // If the cond is of tuple type, just expand it.

      let clauses = matchOnTupleTy itemTys cond clauses

      let conds =
        let itemConds =
          itemTys
          |> List.mapi (fun i itemTy -> (PItemPath(i, cond), itemTy))

        List.append itemConds conds

      doCompile conds clauses

  | (cond, PBoolTy) :: conds ->
      let trueClauses, falseClauses = matchOnBoolTy cond clauses

      let trueExhaust, trueBody = doCompile conds trueClauses
      let falseExhaust, falseBody = doCompile conds falseClauses

      let exhaust = trueExhaust && falseExhaust
      let body = PIfTerm(cond, trueBody, falseBody)
      exhaust, body

  | (cond, (PListTy itemTy as listTy)) :: conds ->
      let nilClauses, consClauses = matchOnListTy cond clauses

      let nilExhaust, nilBody = doCompile conds nilClauses

      let consExhaust, consBody =
        doCompile
          ((PHeadPath cond, itemTy)
           :: (PTailPath cond, listTy)
           :: conds)
          consClauses

      let exhaust = nilExhaust && consExhaust
      let body = PMatchListTerm(cond, nilBody, consBody)
      exhaust, body

  | (cond, PLitTy _) :: conds ->
      let caseMap, defaultClauses = matchOnLitTy cond clauses

      // See the guard above.
      assert (caseMap |> mapIsEmpty |> not)

      let cases =
        caseMap
        |> mapFold (fun acc lit clauses ->
             let _, body = doCompile conds clauses
             (PLitConst lit, body) :: acc) []

      let exhaust, defaultBody = doCompile conds defaultClauses

      exhaust, PSwitchTerm(cond, cases, defaultBody)

// -----------------------------------------------
// Context
// -----------------------------------------------

type private PcCtx =
  { Vars: AssocMap<VarSerial, VarDef>
    Tys: AssocMap<TySerial, TyDef> }

let private ofTyCtx (tyCtx: TyCtx): PcCtx = { Vars = tyCtx.Vars; Tys = tyCtx.Tys }

let private toTyCtx (tyCtx: TyCtx) (ctx: PcCtx): TyCtx = { tyCtx with Vars = ctx.Vars }

// -----------------------------------------------
// Conversion from HIR to PIR
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

  | HOrPat _ -> failwith "NEVER: HOrPat is resolved by patNormalize"
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
             let isGuarded = guard |> hxIsAlwaysTrue |> not

             pat
             |> patNormalize
             |> List.map (fun pat ->
                  let pat = pat |> pcPat ctx
                  ci, [ pat ], isGuarded, id))
        |> List.collect id

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

  | HRecordExpr (baseOpt, fields, ty, loc) ->
      let doArm () =
        let baseOpt, ctx = (baseOpt, ctx) |> stOptionMap pcExpr

        let fields, ctx =
          (fields, ctx)
          |> stMap (fun ((fieldIdent, fieldExpr, fieldLoc), ctx) ->
               let fieldExpr, ctx = (fieldExpr, ctx) |> pcExpr
               (fieldIdent, fieldExpr, fieldLoc), ctx)

        HRecordExpr(baseOpt, fields, ty, loc), ctx

      doArm ()

  | HInfExpr (infOp, items, ty, loc) ->
      let doArm () =
        let items, ctx = (items, ctx) |> stMap pcExpr
        HInfExpr(infOp, items, ty, loc), ctx

      doArm ()

  | HErrorExpr _
  | HModuleExpr _ -> failwith "NEVER: HModuleExpr is resolved in NameRes"

// -----------------------------------------------
// Interface
// -----------------------------------------------

let patternCompile (expr: HExpr, tyCtx: TyCtx) =
  let ctx = ofTyCtx tyCtx

  let expr, ctx = (expr, ctx) |> pcExpr

  let tyCtx = ctx |> toTyCtx tyCtx
  expr, tyCtx
