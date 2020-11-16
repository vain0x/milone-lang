module rec MiloneLang.PatternCompile

open MiloneLang.Helpers
open MiloneLang.Types
open MiloneLang.TySystem
open MiloneLang.Typing

type private ConstVariant =
  | NoneVariant
  | NilVariant
  | ConstVariant of VariantSerial

type private FunVariant =
  | SomeVariant
  | FunVariant of VariantSerial

/// Pattern.
type private P =
  | LitPat of Lit

  | WildcardPat

  | NilPat
  | ConsPat of P * P

  | NonePat
  | SomePat of P

  | ConstVariantPat of VariantSerial
  | FunVariantPat of FunVariant * P
  | TuplePat of P list

type private PPath =
  | PSelfPath
  | PSomeContentPath
  | PHeadPath
  | PTailPath
  | PVariantTagPath
  | PVariantPayloadPath
  | PItemPath of int

/// (clause index, patterns, is guarded, binding list).
///
/// Internal representation of clause.
type private PClause = int * (P * VarSerial option) list * bool * (VarSerial * PPath) list

let private addBindingOpt varOpt (cond: PPath) bindings =
  match varOpt with
  | Some v -> (v, cond) :: bindings
  | None -> bindings

/// -1 pat.
let private matchOnUnitTy (clauses: PClause list): PClause list =
  clauses
  |> List.map (fun clause ->
       let clauseIndex, pats, isGuarded, bindings = clause

       match pats with
       | _ :: pats -> clauseIndex, pats, isGuarded, bindings
       | [] -> failwith "NEVER")

/// (true clauses, false clauses). +0 pats.
let private matchOnBoolTy cond (clauses: PClause list): PClause list * PClause list =
  let rec go clauses =
    match clauses with
    | [] -> [], []

    | (c, pats, isGuarded, bindings) :: clauses ->
        let trueClauses, falseClauses = go clauses

        match pats with
        | (LitPat (BoolLit true), varOpt) :: pats ->
            let trueClauses =
              (c, (WildcardPat, None) :: pats, isGuarded, addBindingOpt varOpt cond bindings)
              :: trueClauses

            trueClauses, falseClauses

        | (LitPat (BoolLit false), varOpt) :: pats ->
            let falseClauses =
              (c, (WildcardPat, None) :: pats, isGuarded, addBindingOpt varOpt cond bindings)
              :: falseClauses

            trueClauses, falseClauses

        | (WildcardPat, varOpt) :: pats ->
            let clause: PClause =
              c, (WildcardPat, None) :: pats, isGuarded, addBindingOpt varOpt cond bindings

            clause :: trueClauses, clause :: falseClauses

        | _ -> failwith "NEVER"

  go clauses

/// (used clause indexes, bindings).
let private doMatch conds (clauses: PClause list): bool * int list * (VarSerial * PPath) list =
  match conds with
  | [] ->
      let rec go acc bindings clauses =
        match clauses with
        | [] ->
            // Not exhaustive.
            false, acc, bindings

        | (clauseIndex, _, false, bindings) :: _ -> true, clauseIndex :: acc, bindings

        | (clauseIndex, _, true, bindings) :: clauses -> go (clauseIndex :: acc) bindings clauses

      go [] [] clauses

  | (_, AppTy (TupleTyCtor, [])) :: conds ->
      let clauses = matchOnUnitTy clauses
      failwith ""

  | (cond, AppTy (BoolTyCtor, [])) :: conds ->
      let trueClauses, falseClauses = matchOnBoolTy cond clauses

      let trueExhaust, trueUsedClauses, trueBindings = doMatch conds trueClauses

      let falseExhaust, falseUsedClauses, falseBindings = doMatch conds trueClauses

      // FIXME: binding can't be combined such way
      trueExhaust && falseExhaust, List.append trueUsedClauses falseUsedClauses, List.append trueBindings falseBindings

  | (cond, AppTy (TupleTyCtor, itemTy :: itemTys)) :: conds -> failwith ""
  | _ -> failwith ""

let private onMatch cond arms = ()

let patternCompile (expr: HExpr, tyCtx: TyCtx) = expr, tyCtx
