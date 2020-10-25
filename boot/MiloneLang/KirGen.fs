/// # KirGen
///
/// Generate continuation passing style (CPS) intermediate representation, KIR
/// from HIR.
///
/// This is not only a data transformation but also:
///
/// - resolve pattern matching

module rec MiloneLang.KirGen

open MiloneLang.Types
open MiloneLang.Records
open MiloneLang.Helpers

let kirGen (_expr: HExpr, tyCtx: TyCtx): KRoot * TyCtx =
  KRoot([], KPrimNode(KExitPrim, [], [], [], noLoc)), tyCtx
