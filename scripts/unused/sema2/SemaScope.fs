/// # SemaScope
///
/// Rules about scoping.

module rec MiloneLang.SemaScope

open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.Hir


// -----------------------------------------------
// Interface
// -----------------------------------------------

type SemaDb =
  { ProjectNs: AssocMap<string, string>
    ValueNs: AssocMap<string, ValueSymbol>
    TyNs: AssocMap<string, TySymbol> }
