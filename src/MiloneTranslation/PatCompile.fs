module rec MiloneTranslation.PatCompile

open Std.StdError
open MiloneShared.SharedTypes
open MiloneTranslation.Hir
open MiloneTranslation.HirTypes

/// Constant value to be compared.
type PConst =
  | PLitConst of Lit * Loc
  | PDiscriminantConst of VariantSerial

type PConstVariant = PConstVariant of VariantSerial

type PFunVariant = PFunVariant of VariantSerial

type PPatKind =
  | WildcardPat
  | TuplePat of PPat list

  | LitPat of Lit

  | VariantPat of PConstVariant
  | VariantAppPat of PFunVariant * PPat

type private PPat = PPatKind * VarSerial option

type PPart =
  | PHeadPart
  | PTailPart
  | PVariantTagPart
  | PVariantPayloadPart

  /// i'th field of tuple
  | PItemPart of index: int

type private PPath = PPart list

type private PCond = PPath

type PTerm =
  /// Evaluating this term causes runtime error. Represents the end of non-exhaustive matching.
  | PAbortTerm

  | PSelectTerm of PPart * next: PTerm

  | PGuardTerm of ClauseIndex * body: PTerm * alt: PTerm

  | PBodyTerm of ClauseIndex

  /// Jump to another clause.
  | PFallbackTerm of ClauseIndex

  | PLetTerm of VarSerial * init: PCond * next: PTerm

  /// Conditional branching on some scalar or string.
  | PSwitchTerm of cond: PCond * cases: (PConst * PTerm) list * defaultCl: PTerm

  | PIfTerm of PPath * PConst * body: PTerm * alt: PTerm

  | PMatchListTerm of cond: PCond * nilCl: PTerm * consCl: PTerm

/// Index of clause in match expression.
type private ClauseIndex = int

let private pcNodePat pat body alt =
  let kind, argPats, _ty, _loc =
    match pat with
    | HNodePat (kind, argPats, ty, loc) -> kind, argPats, ty, loc
    | _ -> unreachable ()

  match kind, argPats with
  // | HAbortPN, _ -> PAbortTerm

  | HNilPN, _ -> PMatchListTerm([], body, alt)

  | HConsPN, [ headPat; tailPat ] -> todo ()
  | HConsPN, _ -> unreachable ()

  | HVariantAppPN variantSerial, [ payloadPat ] -> todo ()
  | HVariantAppPN _, _ -> unreachable ()

  | HTuplePN, [] -> todo ()
  | HTuplePN, _ -> todo ()

  | HBoxPN, [ itemPat ] -> todo ()
  | HBoxPN, _ -> unreachable ()
// | HNonePN, _ -> PMatchOptionTerm([], body, alt)
// | HSomeAppPN, [ itemPat ] -> PMatchOptionTerm([], alt, PSelectTerm(PSomeContentPart, pcPat itemPat body alt))

let private pcPat pat body alt : PTerm =
  match pat with
  | HLitPat (lit, loc) -> PSwitchTerm([], [ PLitConst(lit, loc), body ], alt)

  | HDiscardPat _ -> body
  | HVarPat (varSerial, _, _) -> PLetTerm(varSerial, [], body)

  | HVariantPat _ -> todo ()
  | HNodePat _ -> pcNodePat pat body alt

  | HAsPat (bodyPat, varSerial, _) -> PLetTerm(varSerial, [], pcPat bodyPat body alt)

  | HOrPat _ -> unreachable () // resolved by normalization

// -----------------------------------------------
// PIR gen
// -----------------------------------------------

let patCompileForMatchExprToBlocks (pats: HPat list) : PTerm list =
  let n = List.length pats

  pats
  |> List.mapi (fun (i: int) (pat: HPat) ->
    let alt =
      if i + 1 < n then
        PFallbackTerm(i + 1)
      else
        // exhaust
        PAbortTerm

    pcPat pat (PGuardTerm(i, PBodyTerm i, alt)) alt)
