module rec MiloneTranslation.EscapeAnalyze

open MiloneShared.SharedTypes
open MiloneShared.Util
open MiloneTranslation.Hir

module TMap = MiloneStd.StdMap
module TSet = MiloneStd.StdSet

type private Escaping =
  | IsEscaping
  | NotEscaping

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

    Escaped: AssocSet<int>
    EscapedArgs: AssocSet<FunSerial * int>
    SomethingHappened: bool }

let private ofTyCtx (tyCtx: TyCtx) : Ctx =
  { Vars = tyCtx.Vars
    Funs = tyCtx.Funs
    Variants = tyCtx.Variants
    Tys = tyCtx.Tys

    Escaped = TMap.empty compare
    EscapedArgs = TMap.empty (pairCompare funSerialCompare compare)
    SomethingHappened = false }

// let private toTyCtx (tyCtx: TyCtx) (ctx: Ctx) : TyCtx = tyCtx

let private takeSomethingHappened (ctx: Ctx) =
  ctx.SomethingHappened, { ctx with SomethingHappened = false }

let private markVarAsEscaping varSerial (ctx: Ctx) =
  let n = varSerialToInt varSerial

  if ctx.Escaped |> TSet.contains n then
    ctx
  else
    { ctx with
        Escaped = ctx.Escaped |> TSet.add n
        SomethingHappened = true }

let private markArgAsEscaping funSerial index (ctx: Ctx) =
  let pair = funSerial, index

  if ctx.EscapedArgs |> TSet.contains pair then
    ctx
  else
    { ctx with
        EscapedArgs = ctx.EscapedArgs |> TSet.add pair
        SomethingHappened = true }

let private isVarEscaping varSerial (ctx: Ctx) =
  ctx.Escaped
  |> TSet.contains (varSerialToInt varSerial)

let private isArgEscaping funSerial index (ctx: Ctx) =
  ctx.EscapedArgs
  |> TSet.contains (funSerial, index)

// -----------------------------------------------
// Control
// -----------------------------------------------

/// Does pat contain an escaping variable?
let private patToEscaping pat (ctx: Ctx) =
  patFoldVars
    (fun (escaping: Escaping) varSerial ->
      match escaping with
      | IsEscaping -> IsEscaping
      | _ when isVarEscaping varSerial ctx -> IsEscaping
      | NotEscaping -> NotEscaping)
    NotEscaping
    pat

/// Is target escaping and then does one of pat contains an escaping variable?
let private patsToEscaping escaping (pats: HPat list) (ctx: Ctx) =
  match escaping with
  | NotEscaping -> NotEscaping

  | IsEscaping ->
    pats
    |> List.fold
         (fun escaping pat ->
           match escaping with
           | NotEscaping -> patToEscaping pat ctx
           | IsEscaping -> IsEscaping)
         NotEscaping

let private processCallFunExpr funSerial args ctx =
  args
  |> List.fold
       (fun (i, (escapingArgs, nonEscapingArgs)) arg ->
         if isArgEscaping funSerial i ctx then
           i + 1, (arg :: escapingArgs, nonEscapingArgs)
         else
           i + 1, (escapingArgs, arg :: nonEscapingArgs))
       (0, ([], []))
  |> snd

/// Returns (escaping args, non-escaping-args).
let private processCallPrimExpr prim args =
  match prim, args with
  // Everything escaping.
  | HPrim.Box, _
  | HPrim.Unbox, _
  | HPrim.OptionSome, _
  | HPrim.Cons, _
  | HPrim.NativeCast, _ -> args, []

  // Everything non-escaping.
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
  | HPrim.PtrRead, _ -> [], args

  | HPrim.PtrWrite, [ ptr; i; value ] -> [ ptr; i ], [ value ]
  | HPrim.PtrWrite, _ -> unreachable ()

  | HPrim.OptionNone, _
  | HPrim.Nil, _ -> unreachable () // Can't be called.

  | HPrim.BoxOnStack, _ -> unreachable () // HPrim.BoxOnStack is generated in EscapeAnalyze.

/// Returns (escaping args, non-escaping args).
let private processNodeExpr kind args ctx =
  match kind, args with
  // Everything escaping.
  | HSliceEN, _ // NOTE: indices doesn't escape indeed but no need to be strict.
  | HCallClosureEN, _ // NOTE: closure may return its env, so it escapes on called.
  | HTupleEN, _
  | HRecordEN, _
  | HRecordItemEN _, _
  | HClosureEN _, _
  | HCallNativeEN _, _
  | HNativeExprEN _, _
  | HNativeDeclEN _, _
  | HNativeStmtEN _, _ -> args, []

  // Everything non-escaping.
  | HAbortEN, _
  | HMinusEN, _
  | HIndexEN, _ -> [], args

  | HCallProcEN, HFunExpr (funSerial, _, _) :: args -> processCallFunExpr funSerial args ctx
  | HCallProcEN, HPrimExpr (prim, _, _) :: args -> processCallPrimExpr prim args
  | HCallProcEN, callee :: args -> args, [ callee ]
  | HCallTailRecEN, callee :: args -> args, [ callee ]
  | HCallProcEN, _
  | HCallTailRecEN, _ -> unreachable ()

  | HNativeFunEN _, _
  | HSizeOfValEN, _ -> [], [] // Ignorable.

  | HAppEN, _ -> unreachable () // HAppEN is resolved in EtaExpansion.

let private eaExpr escaping expr (ctx: Ctx) : Ctx =
  match expr with
  | HLitExpr _
  | HFunExpr _
  | HVariantExpr _
  | HPrimExpr _ -> ctx

  | HVarExpr (varSerial, _, loc) ->
    match escaping with
    | IsEscaping when not (isVarEscaping varSerial ctx) ->
      // printfn "// var marked as escaping @%s" (locToString loc)
      ()
    | _ -> ()

    match escaping with
    | IsEscaping -> markVarAsEscaping varSerial ctx
    | NotEscaping -> ctx

  | HNodeExpr (kind, args, _, _) ->
    invoke
      (fun () ->
        let escapingArgs, nonEscapingArgs =
          match escaping with
          | NotEscaping -> [], args
          | IsEscaping -> processNodeExpr kind args ctx

        eaExprs escaping escapingArgs ctx
        |> eaExprs NotEscaping nonEscapingArgs)

  | HMatchExpr (cond, arms, _, _) ->
    invoke
      (fun () ->
        let pats () =
          arms |> List.map (fun (pat, _, _) -> pat)

        let bodies () =
          arms |> List.map (fun (_, _, body) -> body)

        let ctx = eaExprs escaping (bodies ()) ctx

        let ctx =
          let escaping = patsToEscaping escaping (pats ()) ctx
          eaExpr escaping cond ctx

        ctx)

  | HBlockExpr (stmts, last) ->
    invoke
      (fun () ->
        ctx
        |> eaExpr escaping last
        |> eaExprs NotEscaping (List.rev stmts))

  | HLetValExpr (pat, init, next, _, _) ->
    invoke
      (fun () ->
        assert (hxIsUnitLit next) // let-next is resolved in Hoist.

        let escaping = patToEscaping pat ctx
        eaExpr escaping init ctx)

  | HLetFunExpr (callee, _, _, args, body, next, _, loc) ->
    invoke
      (fun () ->
        assert (hxIsUnitLit next) // let-next is resolved in Hoist.

        let ctx =
          args
          |> List.fold
               (fun (i, ctx) arg ->
                 let ctx =
                   match patToEscaping arg ctx with
                   | IsEscaping -> markArgAsEscaping callee i ctx
                   | NotEscaping -> ctx

                 i + 1, ctx)
               (0, ctx)
          |> snd

        // printfn "// enter let-fun %s @%s" (ctx.Funs |> mapFind callee).Name (locToString loc)
        eaExpr IsEscaping body ctx)

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
      // FIXME: check escaping-ness for args
      let args = rewriteExprs escaping args ctx
      HNodeExpr(kind, args, ty, loc)

    invoke
      (fun () ->
        match escaping, kind, args with
        | NotEscaping, HCallProcEN, HPrimExpr (HPrim.Cons, _, _) :: _ ->
          printfn "// cons-on-stack @%s" (locToString loc)
          doDefault ()

        | NotEscaping, HCallProcEN, HPrimExpr (HPrim.Box, primTy, primLoc) :: args ->
          printfn "// box-on-stack @%s" (locToString loc)

          let callee =
            HPrimExpr(HPrim.BoxOnStack, primTy, primLoc)

          let args = rewriteExprs IsEscaping args ctx
          HNodeExpr(HCallProcEN, callee :: args, ty, loc)

        | NotEscaping, HCallProcEN, (HFunExpr (funSerial, _, _) as callee) :: args ->
          let args =
            args
            |> List.mapi
                 (fun i arg ->
                   let escaping =
                     if isArgEscaping funSerial i ctx then
                       IsEscaping
                     else
                       NotEscaping

                   rewriteExpr escaping arg ctx)

          HNodeExpr(HCallProcEN, callee :: args, ty, loc)

        | _ -> doDefault ())

  | HMatchExpr (cond, arms, ty, loc) ->
    invoke
      (fun () ->
        let cond = rewriteExpr escaping cond ctx

        let arms =
          arms
          |> List.map
               (fun (pat, guard, body) ->
                 let guard = rewriteExpr escaping guard ctx
                 let body = rewriteExpr escaping body ctx
                 pat, guard, body)

        HMatchExpr(cond, arms, ty, loc))

  | HBlockExpr (stmts, last) ->
    invoke
      (fun () ->
        let stmts = rewriteExprs NotEscaping stmts ctx
        let last = rewriteExpr escaping last ctx
        HBlockExpr(stmts, last))

  | HLetValExpr (pat, init, next, ty, loc) ->
    invoke
      (fun () ->
        assert (hxIsUnitLit next) // let-next is resolved in Hoist.

        let init =
          let escaping = patToEscaping pat ctx
          rewriteExpr escaping init ctx

        HLetValExpr(pat, init, next, ty, loc))

  | HLetFunExpr (callee, isRec, vis, args, body, next, ty, loc) ->
    invoke
      (fun () ->
        assert (hxIsUnitLit next) // let-next is resolved in Hoist.
        let body = rewriteExpr IsEscaping body ctx
        HLetFunExpr(callee, isRec, vis, args, body, next, ty, loc))

  | HNavExpr _ -> unreachable () // HNavExpr is resolved in NameRes, Typing, or RecordRes.
  | HRecordExpr _ -> unreachable () // HRecordExpr is resolved in RecordRes.

let private rewriteExprs escaping exprs (ctx: Ctx) : HExpr list =
  exprs
  |> List.map (fun expr -> rewriteExpr escaping expr ctx)

// ===============================================

let escapeAnalyze (decls: HExpr list, tyCtx: TyCtx) : HExpr list * TyCtx =
  let ctx = ofTyCtx tyCtx

  let ctx =
    let rec go round ctx =
      let modified, ctx =
        ctx
        |> eaExprs NotEscaping decls
        |> takeSomethingHappened

      if modified then
        assert (round < 10000000)
        go (round + 1) ctx
      else
        // printfn "// escapeAnalyze finished in %d rounds" (round + 1)
        ctx

    go 0 ctx

  let decls = rewriteExprs NotEscaping decls ctx
  decls, tyCtx
