/// # KirToHir
///
/// Convert KIR back to HIR.

module rec MiloneLang.KirHir

open MiloneLang.Types
open MiloneLang.Records
open MiloneLang.Helpers

type KirToHirCtx = KirToHirCtx of unit

type private ctx = KirToHirCtx

let private findVarDef _ = failwith ""
let private findFunDef _ = failwith ""

// /// Primitive in KIR.
// type KPrim =
//   | KMovePrim

//   // Arithmetic:
//   | KAddPrim
//   | KSubPrim
//   | KMulPrim
//   | KDivPrim
//   | KModPrim

//   // Comparison:
//   | KEqualPrim
//   | KLessPrim

//   // Bool:
//   | KNotPrim

//   // String:
//   | KIndexPrim
//   | KStrLengthPrim
//   | KStrGetSlicePrim

//   // List, option:
//   | KConsPrim
//   | KSomePrim

//   // Tuple:
//   | KTuplePrim

//   // Function, closure:
//   | KClosurePrim
//   | KCallProcPrim
//   | KCallClosurePrim

//   // obj:
//   | KBoxPrim
//   | KUnboxPrim

//   // Others:
//   | KExitPrim
//   | KAssertPrim
//   | KCharPrim
//   | KIntPrim
//   | KStringPrim
//   | KPrintfnPrim
//   | KInRegionPrim
//   | KNativeFunPrim of Ident * Arity

let private khTerm (term: KTerm) ctx =
  match term with
  | KLitTerm (lit, loc) -> HLitExpr(lit, loc)

  | KVarTerm (varSerial, ty, loc)
  | KLabelTerm (varSerial, ty, loc) -> HRefExpr(varSerial, ty, loc)

  | KNilTerm (itemTy, loc) -> hxNil itemTy loc

  | KNoneTerm (itemTy, loc) -> HPrimExpr(HPrim.OptionNone, tyList itemTy, loc)

  | KUnitTerm loc -> hxUnit loc

let private khNode (node: KNode) ctx =
  match node with
  | KJumpNode (funSerial, args, loc) ->
    let callee =
      let funTy = findFunDef funSerial
      HRefExpr(funSerial, funTy, loc)

    let args =
      args |> listMap (fun term -> khTerm term ctx)

    hxCallProc callee args tyUnit loc

  | KSwitchNode (cond, arms, loc) -> failwith ""

  | KSelectNode (term, path, result, cont, loc) ->
    let lhs = khTerm term ctx

    match path with
    | KFieldPath (i, loc) -> failwith ""

    | KTagPath loc ->
      // InfOp
      failwith ""

    | KPayloadPath (varSerial, loc) -> failwith ""

  | KPrimNode (prim, args, results, conts, loc) -> failwith ""

let private khFunBinding binding next nextTy ctx =
  let (KFunBinding (funSerial, args, body, loc)) = binding

  // Vis not used later, so every fun can be private.
  let isMainFun, funTy =
    match findVarDef funSerial with
    | FunDef (ident, _, TyScheme (_, funTy), _) -> ident = "main", funTy

    | _ -> failwith ""

  let argPats =
    let rec go args funTy =
      match args, funTy with
      | arg :: args, AppTy (FunTyCtor, [ sTy; tTy ]) -> HRefPat(arg, sTy, loc) :: go args tTy

      | _ -> failwithf "NEVER: illegal KFunBinding. %A" binding

    go args funTy

  let body = khNode body ctx

  HLetFunExpr(funSerial, PrivateVis, isMainFun, argPats, body, next, nextTy, loc)

let kirHir (root: KRoot, ctx: ctx) : HExpr * ctx =
  let (KRoot (bindings, node)) = root

  let rec go (root, ctx) = ()

  failwith ""
