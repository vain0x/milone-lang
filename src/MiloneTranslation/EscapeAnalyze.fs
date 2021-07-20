module rec MiloneTranslation.EscapeAnalyze

open MiloneShared.SharedTypes
open MiloneShared.Util
open MiloneTranslation.Hir

module TMap = MiloneStd.StdMap
module TSet = MiloneStd.StdSet

/// Bit flag to indicate which part of value is escaping.
///
/// - 0: the value and its contents are no escaping
/// - 1: the value itself it no escaping, but its contents are.
/// - 2: the value itself and its contents are escaping.
type private Escaping =
  | NotEscaping
  | PartiallyEscaping
  | TotallyEscaping

let private encode x =
  match x with
  | NotEscaping -> 0
  | PartiallyEscaping -> 1
  | TotallyEscaping -> -1

let private decode x =
  match x with
  | 0 -> NotEscaping
  | 1 -> PartiallyEscaping
  | _ -> TotallyEscaping

let private escapingEqual l r = encode l = encode r
let private conj l r = decode (encode l &&& encode r)
let private disj (l: Escaping) (r: Escaping) = decode (encode l ||| encode r)
let private notEscaping (x: Escaping) = escapingEqual x NotEscaping
let private isPartial (x: Escaping) = escapingEqual x PartiallyEscaping
let private isTotal (x: Escaping) = escapingEqual x TotallyEscaping

let private patFoldVars (onVar: 'S -> VarSerial -> 'S) (state: 'S) (pat: HPat) : 'S =
  let rec go state pat =
    match pat with
    | HLitPat _
    | HDiscardPat _
    | HVariantPat _ -> state

    | HVarPat (_, varSerial, _, _) -> onVar state varSerial

    | HNodePat (_, args, _, _) -> List.fold go state args
    | HAsPat (bodyPat, varSerial, _) -> go (onVar state varSerial) bodyPat
    | HOrPat (l, r, _) -> go (go state l) r

  go state pat

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private Ctx =
  { Vars: AssocMap<VarSerial, VarDef>
    Funs: AssocMap<FunSerial, FunDef>
    Variants: AssocMap<VariantSerial, VariantDef>
    Tys: AssocMap<TySerial, TyDef>

    VarEscapeMap: AssocMap<VarSerial, Escaping>
    ArgEscapeMap: AssocMap<FunSerial * int, Escaping>
    SomethingHappened: bool }

let private ofTyCtx (tyCtx: TyCtx) : Ctx =
  { Vars = tyCtx.Vars
    Funs = tyCtx.Funs
    Variants = tyCtx.Variants
    Tys = tyCtx.Tys

    VarEscapeMap = TMap.empty varSerialCompare
    ArgEscapeMap = TMap.empty (pairCompare funSerialCompare compare)
    SomethingHappened = false }

// let private toTyCtx (tyCtx: TyCtx) (ctx: Ctx) : TyCtx = tyCtx

let private takeSomethingHappened (ctx: Ctx) =
  ctx.SomethingHappened, { ctx with SomethingHappened = false }

let private varToEscaping varSerial (ctx: Ctx) =
  ctx.VarEscapeMap
  |> TMap.tryFind varSerial
  |> Option.defaultValue NotEscaping

let private argToEscaping funSerial index (ctx: Ctx) =
  ctx.ArgEscapeMap
  |> TMap.tryFind (funSerial, index)
  |> Option.defaultValue NotEscaping

let private markVarAsEscaping varSerial (escaping: Escaping) loc (ctx: Ctx) =
  if notEscaping escaping then
    ctx
  else
    let current = varToEscaping varSerial ctx
    let next = disj current escaping

    if escapingEqual current next then
      ctx
    else
      printfn "// var %s %s -> %s" (ctx.Vars |> mapFind varSerial).Name (locToString loc) (objToString next)

      { ctx with
          VarEscapeMap = ctx.VarEscapeMap |> TMap.add varSerial next
          SomethingHappened = true }

let private markArgAsEscaping funSerial index (escaping: Escaping) loc (ctx: Ctx) =
  if notEscaping escaping then
    ctx
  else
    let current = argToEscaping funSerial index ctx
    let next = disj current escaping

    if escapingEqual current next then
      ctx
    else
      printfn "// arg %s#%d %s -> %s" (ctx.Funs |> mapFind funSerial).Name index (locToString loc) (objToString next)

      { ctx with
          ArgEscapeMap =
            ctx.ArgEscapeMap
            |> TMap.add (funSerial, index) next
          SomethingHappened = true }

// -----------------------------------------------
// Control
// -----------------------------------------------

/// Compute escaping for `cond` of pattern matching.
let private patToEscaping pat (ctx: Ctx) =
  let rec go escaping pat =
    match pat with
    | _ when notEscaping escaping -> NotEscaping

    | HLitPat _
    | HDiscardPat _
    | HVariantPat _ -> NotEscaping

    | HVarPat (_, varSerial, _, _) -> conj escaping (varToEscaping varSerial ctx)

    | HNodePat (kind, args, _, _) ->
      let escaping =
        match kind, args with
        | HNilPN, _
        | HNonePN, _
        | HTuplePN, []
        | HVariantAppPN _, []
        | HAbortPN, _ -> NotEscaping

        | _ -> conj escaping PartiallyEscaping

      args
      |> List.map (go escaping)
      |> List.fold disj NotEscaping

    | HAsPat (bodyPat, varSerial, _) ->
      let escaping =
        conj escaping (varToEscaping varSerial ctx)

      go escaping bodyPat

    | HOrPat (l, r, _) -> disj (go escaping l) (go escaping r)

  go TotallyEscaping pat

let private patsToEscaping (pats: HPat list) (ctx: Ctx) =
  pats
  |> List.map (fun pat -> patToEscaping pat ctx)
  |> List.fold disj NotEscaping

let private processCallFunExpr funSerial (args: HExpr list) ctx =
  args
  |> List.mapi (fun i arg -> argToEscaping funSerial i ctx, arg)

let private uniformly escaping args : (Escaping * HExpr) list =
  args |> List.map (fun arg -> escaping, arg)

let private processCallPrimExpr prim args =
  match prim, args with
  | HPrim.Not, _
  | HPrim.Add, _
  | HPrim.Sub, _
  | HPrim.Mul, _
  | HPrim.Div, _
  | HPrim.Modulo, _
  | HPrim.BitAnd, _
  | HPrim.BitOr, _
  | HPrim.BitXor, _
  | HPrim.LeftShift, _
  | HPrim.RightShift, _
  | HPrim.Equal, _
  | HPrim.Less, _
  | HPrim.Compare, _
  | HPrim.ToInt _, _
  | HPrim.ToFloat _, _
  | HPrim.Char, _
  | HPrim.String, _
  | HPrim.StrLength, _
  | HPrim.Exit, _
  | HPrim.Assert, _
  | HPrim.Printfn, _
  | HPrim.InRegion, _
  | HPrim.PtrRead, _ -> uniformly NotEscaping args

  | HPrim.Unbox, _ -> uniformly PartiallyEscaping args

  | HPrim.Box, _
  | HPrim.BoxOnStack, _
  | HPrim.OptionSome, _
  | HPrim.Cons, _
  | HPrim.NativeCast, _ -> uniformly TotallyEscaping args

  | HPrim.PtrWrite, [ ptr; i; value ] ->
    [ NotEscaping, ptr
      NotEscaping, i
      TotallyEscaping, value ]
  | HPrim.PtrWrite, _ -> unreachable ()

  | HPrim.OptionNone, _
  | HPrim.Nil, _ -> unreachable () // Can't be called.

let private processNodeExpr kind args ctx =
  match kind, args with
  | HAbortEN, _
  | HMinusEN, _
  | HIndexEN, _
  | HNativeFunEN _, _
  | HSizeOfValEN, _ -> uniformly NotEscaping args

  | HRecordItemEN _, _ -> uniformly PartiallyEscaping args

  | HSliceEN, _ // NOTE: indices don't escape indeed but no need to be strict.
  | HCallClosureEN, _ // NOTE: closure may return its env, so it escapes on called.
  | HTupleEN, _
  | HRecordEN, _
  | HClosureEN _, _
  | HCallNativeEN _, _
  | HNativeExprEN _, _
  | HNativeDeclEN _, _
  | HNativeStmtEN _, _ -> uniformly TotallyEscaping args

  | HCallProcEN, (HFunExpr (funSerial, _, _) as callee) :: args ->
    (NotEscaping, callee)
    :: processCallFunExpr funSerial args ctx
  | HCallProcEN, (HPrimExpr (prim, _, _) as callee) :: args ->
    (NotEscaping, callee)
    :: processCallPrimExpr prim args
  | HCallProcEN, callee :: args ->
    (NotEscaping, callee)
    :: uniformly TotallyEscaping args
  | HCallTailRecEN, callee :: args ->
    (NotEscaping, callee)
    :: uniformly TotallyEscaping args
  | HCallProcEN, _
  | HCallTailRecEN, _ -> unreachable ()

  | HAppEN, _ -> unreachable () // HAppEN is resolved in EtaExpansion.

/// `escaping` param indicates how the target of the expr is escaping.
let private eaExpr escaping expr (ctx: Ctx) : Ctx =
  match expr with
  | HLitExpr _
  | HFunExpr _
  | HVariantExpr _
  | HPrimExpr _ -> ctx

  | HVarExpr (varSerial, _, loc) -> markVarAsEscaping varSerial escaping loc ctx

  | HNodeExpr (kind, args, _, _) ->
    invoke
      (fun () ->
        let args =
          if notEscaping escaping then
            uniformly NotEscaping args
          else
            processNodeExpr kind args ctx

        args
        |> List.fold (fun ctx (escaping, arg) -> eaExpr escaping arg ctx) ctx)

  | HMatchExpr (cond, arms, _, _) ->
    let pats () =
      arms |> List.map (fun (pat, _, _) -> pat)

    let bodies () =
      arms |> List.map (fun (_, _, body) -> body)

    invoke
      (fun () ->
        ctx
        |> eaExprs escaping (bodies ())
        |> eaExpr (patsToEscaping (pats ()) ctx) cond)

  | HBlockExpr (stmts, last) ->
    invoke
      (fun () ->
        ctx
        |> eaExpr escaping last
        |> eaExprs escaping (List.rev stmts))

  | HLetValExpr (pat, init, next, _, _) ->
    invoke
      (fun () ->
        assert (hxIsUnitLit next) // let-next is resolved in Hoist.

        eaExpr (conj escaping (patToEscaping pat ctx)) init ctx)

  | HLetFunExpr (callee, _, _, args, body, next, _, loc) ->
    invoke
      (fun () ->
        assert (hxIsUnitLit next) // let-next is resolved in Hoist.

        let funName = (ctx.Funs |> mapFind callee).Name
        // printfn "// enter let-fun %s @%s" funName (locToString loc)
        let ctx = eaExpr escaping body ctx

        let ctx =
          args
          |> List.fold
               (fun (i, ctx) arg ->
                 //  printfn "// arg? %s#%d %s" funName i (patToEscaping arg ctx |> objToString)

                 let ctx =
                   markArgAsEscaping callee i (patToEscaping arg ctx) loc ctx

                 i + 1, ctx)
               (0, ctx)
          |> snd

        ctx)

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

let private eaExprs escaping exprs (ctx: Ctx) : Ctx =
  ctx
  |> forList (fun expr ctx -> eaExpr escaping expr ctx) exprs

// -----------------------------------------------
// Rewrite
// -----------------------------------------------

let private rewriteExpr escaping expr (ctx: Ctx) =
  match expr with
  | HLitExpr _
  | HVarExpr _
  | HFunExpr _
  | HVariantExpr _
  | HPrimExpr _ -> expr

  | HNodeExpr (kind, args, ty, loc) ->
    let doDefault () =
      let arity = List.length args

      let args =
        if notEscaping escaping then
          uniformly NotEscaping args
        else
          processNodeExpr kind args ctx

      let args = rewriteArgs args ctx

      assert (List.length args = arity)
      HNodeExpr(kind, args, ty, loc)

    invoke
      (fun () ->
        match kind, args with
        | HCallProcEN, (HFunExpr (funSerial, _, _) as callee) :: args ->
          let args =
            rewriteArgs (processCallFunExpr funSerial args ctx) ctx

          HNodeExpr(HCallProcEN, callee :: args, ty, loc)

        | HCallProcEN, HPrimExpr (HPrim.Cons, _, _) :: _ when not (isTotal escaping) ->
          printfn "// cons-on-stack @%s (%s)" (locToString loc) (objToString escaping)
          doDefault ()

        | HCallProcEN, HPrimExpr (HPrim.Box, primTy, primLoc) :: args when not (isTotal escaping) ->
          printfn "// box-on-stack @%s (%s)" (locToString loc) (objToString escaping)

          let callee =
            HPrimExpr(HPrim.BoxOnStack, primTy, primLoc)

          let args =
            rewriteArgs (processNodeExpr kind (callee :: args) ctx) ctx

          HNodeExpr(HCallProcEN, args, ty, loc)

        | _ -> doDefault ())

  | HMatchExpr (cond, arms, ty, loc) ->
    let pats () =
      arms |> List.map (fun (pat, _, _) -> pat)

    invoke
      (fun () ->
        let cond =
          rewriteExpr (patsToEscaping (pats ()) ctx) cond ctx

        let arms =
          arms
          |> List.map
               (fun (pat, guard, body) ->
                 let guard = rewriteExpr NotEscaping guard ctx
                 let body = rewriteExpr escaping body ctx
                 pat, guard, body)

        HMatchExpr(cond, arms, ty, loc))

  | HBlockExpr (stmts, last) ->
    invoke
      (fun () ->
        let stmts = rewriteExprs escaping stmts ctx
        let last = rewriteExpr escaping last ctx
        HBlockExpr(stmts, last))

  | HLetValExpr (pat, init, next, ty, loc) ->
    invoke
      (fun () ->
        assert (hxIsUnitLit next) // let-next is resolved in Hoist.

        let init =
          rewriteExpr (conj escaping (patToEscaping pat ctx)) init ctx

        HLetValExpr(pat, init, next, ty, loc))

  | HLetFunExpr (callee, isRec, vis, args, body, next, ty, loc) ->
    invoke
      (fun () ->
        assert (hxIsUnitLit next) // let-next is resolved in Hoist.
        let body = rewriteExpr escaping body ctx
        HLetFunExpr(callee, isRec, vis, args, body, next, ty, loc))

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

let private rewriteExprs escaping exprs (ctx: Ctx) : HExpr list =
  exprs
  |> List.map (fun expr -> rewriteExpr escaping expr ctx)

let private rewriteArgs args (ctx: Ctx) =
  args
  |> List.map (fun (escaping, arg) -> rewriteExpr escaping arg ctx)

// ===============================================

let escapeAnalyze (decls: HExpr list, tyCtx: TyCtx) : HExpr list * TyCtx =
  let ctx = ofTyCtx tyCtx

  printfn "// escapeAnalyze begin"

  let ctx =
    let rec go round ctx =
      let modified, ctx =
        ctx
        |> eaExprs TotallyEscaping decls
        |> takeSomethingHappened

      if modified then
        assert (round < 10000000)
        go (round + 1) ctx
      else
        printfn "// escapeAnalyze finished in %d rounds" (round + 1)
        ctx

    go 0 ctx

  let decls = rewriteExprs TotallyEscaping decls ctx
  decls, tyCtx
