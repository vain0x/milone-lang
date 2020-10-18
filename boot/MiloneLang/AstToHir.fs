/// Converts an abstract syntax tree (AST)
/// to high-level intermediate representation (HIR).
///
/// ## Motivation
///
/// 1. AST should be decoupled with HIR.
///
/// AST is for syntactical analysis/transformations
/// but HIR is for semantic analysis/transformations.
/// The two have different concerns and grow independently.
///
/// 2. AST is redundant and confusing
///
/// AST is optimal for humans but not for analysis.
/// For example, `[1; 2]` and `1 :: 2 :: []` have the same meaning
/// and no need to be distinct for the compiler, i.e. *syntax sugar*.
/// This stage is the best place to desugar them.
///
/// Another example, `let` expressions are confusing whether
/// they introduce either functions or variables. The two kind of
/// entities have different behavior in the following stages.
module rec MiloneLang.AstToHir

open MiloneLang.Types
open MiloneLang.Helpers

let opToPrim op =
  match op with
  | Op.Add -> HPrim.Add

  | Op.Sub -> HPrim.Sub

  | Op.Mul -> HPrim.Mul

  | Op.Div -> HPrim.Div

  | Op.Mod -> HPrim.Mod

  | Op.Eq -> HPrim.Eq

  | Op.Lt -> HPrim.Lt

  | Op.Cons -> HPrim.Cons

  | Op.Ne
  | Op.Le
  | Op.Gt
  | Op.Ge
  | Op.And
  | Op.Or
  | Op.App
  | Op.Pipe -> failwithf "NEVER: %A" op

/// `[x; y; ..]`. Desugar to a chain of (::).
let desugarListLitPat pats pos =
  assert (pats |> listIsEmpty |> not)

  let rec go pats =
    match pats with
    | [] -> APat.ListLit([], pos)

    | head :: tail ->
        let tail = go tail
        APat.Cons(head, tail, pos)

  go pats

/// `[x; y; ..]` ==> `x :: y :: .. :: []`
let desugarListLitExpr items pos =
  assert (items |> listIsEmpty |> not)

  let rec go items =
    match items with
    | [] -> AExpr.ListLit([], pos)

    | head :: tail ->
        let tail = go tail
        AExpr.Bin(Op.Cons, head, tail, pos)

  go items

/// Desugar `if` to `match`.
/// `if cond then body else alt` ==>
/// `match cond with | true -> body | false -> alt`.
let desugarIf cond body alt pos =
  let alt =
    match alt with
    | AExpr.Missing _ -> axUnit pos
    | _ -> alt

  let arms =
    [ AArm(apTrue pos, axTrue pos, body, pos)
      AArm(apFalse pos, axTrue pos, alt, pos) ]

  AExpr.Match(cond, arms, pos)

/// Desugar to let expression.
/// `fun x y .. -> z` ==> `let f x y .. = z in f`
let desugarFun pats body pos =
  let ident = "fun"
  let pat = APat.Fun(ident, pats, pos)
  let next = AExpr.Ident(ident, pos)
  AExpr.Let(pat, body, next, pos)

/// Desugar `-x` to `0 - x`.
let desugarUniNeg arg pos =
  let zero = AExpr.Lit(Lit.Int 0, pos)
  AExpr.Bin(Op.Sub, zero, arg, pos)

/// `l <> r` ==> `not (l = r)`
let desugarBinNe l r pos =
  let eqExpr = AExpr.Bin(Op.Eq, l, r, pos)
  axNot eqExpr pos

/// `l <= r` ==> `not (r < l)`
/// NOTE: Evaluation order does change.
let desugarBinLe l r pos =
  let ltExpr = AExpr.Bin(Op.Lt, r, l, pos)
  axNot ltExpr pos

/// `l > r` ==> `r < l`
/// NOTE: Evaluation order does change.
let desugarBinGt l r pos = AExpr.Bin(Op.Lt, r, l, pos)

/// `l >= r` ==> `not (l < r)`
let desugarBinGe l r pos =
  let ltExpr = AExpr.Bin(Op.Lt, l, r, pos)
  axNot ltExpr pos

/// `l && r` ==> `if l then r else false`
let desugarBinAnd l r pos = desugarIf l r (axFalse pos) pos

/// `l || r` ==> `if l then true else r`
let desugarBinOr l r pos = desugarIf l (axTrue pos) r pos

/// `x |> f` ==> `f x`
/// NOTE: Evaluation order does change.
let desugarBinPipe l r pos = AExpr.Bin(Op.App, r, l, pos)

/// `s.[l .. r]` ==> `String.getSlice l r x`
/// NOTE: Evaluation order does change.
let tryDesugarIndexRange expr pos =
  match expr with
  | AExpr.Index (s, AExpr.Range ([ l; r ], _), _) ->
      let getSlice =
        AExpr.Nav(AExpr.Ident("String", pos), "getSlice", pos)

      true, axApp3 getSlice l r s pos

  | _ -> false, expr

/// Analyzes let syntax.
///
/// Annotation move just for simplification:
/// `let p : ty = body` ==>
///   `let p = body : ty`
///
/// Let to let-fun:
/// `let f x = body` ==>
///   `let-fun f(x) = body`
///
/// Let to let-val:
/// `let pat = body` ==>
///   `let-val pat = body`
let desugarLet pat body next pos =
  match pat with
  | APat.Anno (pat, annoTy, annoLoc) ->
      let body = AExpr.Anno(body, annoTy, annoLoc)
      desugarLet pat body next pos

  | APat.Fun (ident, args, _) -> ALet.LetFun(ident, args, body, next, pos)

  | _ -> ALet.LetVal(pat, body, next, pos)

let astToHirTy (ty: ATy, nameCtx: NameCtx): Ty * NameCtx =
  match ty with
  | ATy.Missing loc -> Ty.Error loc, nameCtx

  | ATy.App (ident, argTys, _) ->
      let tySerial, nameCtx = nameCtx |> nameCtxAdd ident
      let argTys, nameCtx = (argTys, nameCtx) |> stMap astToHirTy
      tyRef tySerial argTys, nameCtx

  | ATy.Suffix (lTy, ident, _) ->
      let lTy, nameCtx = (lTy, nameCtx) |> astToHirTy
      let tySerial, nameCtx = nameCtx |> nameCtxAdd ident
      tyRef tySerial [ lTy ], nameCtx

  | ATy.Tuple (itemTys, _) ->
      let itemTys, nameCtx = (itemTys, nameCtx) |> stMap astToHirTy
      tyTuple itemTys, nameCtx

  | ATy.Fun (sTy, tTy, _) ->
      let sTy, nameCtx = (sTy, nameCtx) |> astToHirTy
      let tTy, nameCtx = (tTy, nameCtx) |> astToHirTy
      tyFun sTy tTy, nameCtx

let astToHirPat (pat: APat, nameCtx: NameCtx): HPat * NameCtx =
  match pat with
  | APat.Missing (_, loc) -> failwithf "Missing pattern %A" loc

  | APat.Lit (lit, loc) -> HPat.Lit(lit, loc), nameCtx

  | APat.Ident (ident, loc) ->
      let serial, nameCtx = nameCtx |> nameCtxAdd ident
      HPat.Ref(serial, noTy, loc), nameCtx

  | APat.ListLit ([], loc) -> patNil noTy loc, nameCtx

  | APat.ListLit (pats, loc) ->
      let pat = desugarListLitPat pats loc
      (pat, nameCtx) |> astToHirPat

  | APat.Nav (l, r, loc) ->
      let l, nameCtx = (l, nameCtx) |> astToHirPat
      HPat.Nav(l, r, noTy, loc), nameCtx

  | APat.Call (calleePat, argPats, loc) ->
      let calleePat, nameCtx = (calleePat, nameCtx) |> astToHirPat
      let argPats, nameCtx = (argPats, nameCtx) |> stMap astToHirPat
      HPat.Call(calleePat, argPats, noTy, loc), nameCtx

  | APat.Cons (head, tail, loc) ->
      let head, nameCtx = (head, nameCtx) |> astToHirPat
      let tail, nameCtx = (tail, nameCtx) |> astToHirPat
      HPat.Cons(head, tail, noTy, loc), nameCtx

  | APat.TupleLit (pats, loc) ->
      let pats, nameCtx = (pats, nameCtx) |> stMap astToHirPat
      HPat.Tuple(pats, noTy, loc), nameCtx

  | APat.As (pat, ident, loc) ->
      let serial, nameCtx = nameCtx |> nameCtxAdd ident
      let pat, nameCtx = (pat, nameCtx) |> astToHirPat
      HPat.As(pat, serial, loc), nameCtx

  | APat.Anno (pat, ty, loc) ->
      let pat, nameCtx = (pat, nameCtx) |> astToHirPat
      let ty, nameCtx = (ty, nameCtx) |> astToHirTy
      HPat.Anno(pat, ty, loc), nameCtx

  | APat.Or (l, r, loc) ->
      let l, nameCtx = (l, nameCtx) |> astToHirPat
      let r, nameCtx = (r, nameCtx) |> astToHirPat
      HPat.Or(l, r, noTy, loc), nameCtx

  | APat.Fun (_, _, loc) -> failwithf "Invalid occurrence of fun pattern: %A" loc

let astToHirExpr (expr: AExpr, nameCtx: NameCtx): HExpr * NameCtx =
  match expr with
  | AExpr.Missing loc -> HExpr.Error("Missing expression", loc), nameCtx

  | AExpr.Lit (lit, loc) -> HExpr.Lit(lit, loc), nameCtx

  | AExpr.Ident (ident, loc) ->
      // NOTE: Work in a local function to reduce the size of stack frames of `astToHirExpr`.
      let doArm () =
        let serial, nameCtx = nameCtx |> nameCtxAdd ident
        HExpr.Ref(serial, noTy, loc), nameCtx

      doArm ()

  | AExpr.ListLit ([], loc) -> hxNil noTy loc, nameCtx

  | AExpr.ListLit (items, loc) ->
      let doArm () =
        let expr = desugarListLitExpr items loc
        (expr, nameCtx) |> astToHirExpr

      doArm ()

  | AExpr.If (cond, body, alt, loc) ->
      let doArm () =
        let expr = desugarIf cond body alt loc
        (expr, nameCtx) |> astToHirExpr

      doArm ()

  | AExpr.Match (target, arms, loc) ->
      let doArm () =
        // Desugar `| pat -> body` to `| pat when true -> body` so that all arms have guard expressions.
        let onArm (AArm (pat, guard, body, loc), nameCtx) =
          let pat, nameCtx = (pat, nameCtx) |> astToHirPat

          let guard, nameCtx =
            match guard with
            | AExpr.Missing _ -> hxTrue loc, nameCtx
            | _ -> (guard, nameCtx) |> astToHirExpr

          let body, nameCtx = (body, nameCtx) |> astToHirExpr
          (pat, guard, body), nameCtx

        let target, nameCtx = (target, nameCtx) |> astToHirExpr
        let arms, nameCtx = (arms, nameCtx) |> stMap onArm
        HExpr.Match(target, arms, noTy, loc), nameCtx

      doArm ()

  | AExpr.Fun (pats, body, loc) ->
      let doArm () =
        let expr = desugarFun pats body loc
        (expr, nameCtx) |> astToHirExpr

      doArm ()

  | AExpr.Nav (l, r, loc) ->
      let doArm () =
        let l, nameCtx = (l, nameCtx) |> astToHirExpr
        HExpr.Nav(l, r, noTy, loc), nameCtx

      doArm ()

  | AExpr.Index (l, r, loc) ->
      let doArm () =
        match tryDesugarIndexRange expr loc with
        | true, expr -> (expr, nameCtx) |> astToHirExpr

        | false, _ ->
            let l, nameCtx = (l, nameCtx) |> astToHirExpr
            let r, nameCtx = (r, nameCtx) |> astToHirExpr

            let hxIndex =
              hxApp (hxApp (HExpr.Prim(HPrim.Index, noTy, loc)) l noTy loc) r noTy loc

            hxIndex, nameCtx

      doArm ()

  | AExpr.Uni (UniOp.Neg, arg, loc) ->
      let doArm () =
        let expr = desugarUniNeg arg loc
        (expr, nameCtx) |> astToHirExpr

      doArm ()

  | AExpr.Bin (Op.Ne, l, r, loc) ->
      let doArm () =
        let expr = desugarBinNe l r loc
        (expr, nameCtx) |> astToHirExpr

      doArm ()

  | AExpr.Bin (Op.Le, l, r, loc) ->
      let doArm () =
        let expr = desugarBinLe l r loc
        (expr, nameCtx) |> astToHirExpr

      doArm ()

  | AExpr.Bin (Op.Gt, l, r, loc) ->
      let doArm () =
        let expr = desugarBinGt l r loc
        (expr, nameCtx) |> astToHirExpr

      doArm ()

  | AExpr.Bin (Op.Ge, l, r, loc) ->
      let doArm () =
        let expr = desugarBinGe l r loc
        (expr, nameCtx) |> astToHirExpr

      doArm ()

  | AExpr.Bin (Op.And, l, r, loc) ->
      let doArm () =
        let expr = desugarBinAnd l r loc
        (expr, nameCtx) |> astToHirExpr

      doArm ()

  | AExpr.Bin (Op.Or, l, r, loc) ->
      let doArm () =
        let expr = desugarBinOr l r loc
        (expr, nameCtx) |> astToHirExpr

      doArm ()

  | AExpr.Bin (Op.Pipe, l, r, loc) ->
      let doArm () =
        let expr = desugarBinPipe l r loc
        (expr, nameCtx) |> astToHirExpr

      doArm ()

  | AExpr.Bin (Op.App, l, r, loc) ->
      let doArm () =
        let l, nameCtx = (l, nameCtx) |> astToHirExpr
        let r, nameCtx = (r, nameCtx) |> astToHirExpr
        hxApp l r noTy loc, nameCtx

      doArm ()

  | AExpr.Bin (op, l, r, loc) ->
      let doArm () =
        let prim = op |> opToPrim
        let l, nameCtx = (l, nameCtx) |> astToHirExpr
        let r, nameCtx = (r, nameCtx) |> astToHirExpr
        let primExpr = HExpr.Prim(prim, noTy, loc)
        hxApp (hxApp primExpr l noTy loc) r noTy loc, nameCtx

      doArm ()

  | AExpr.Range (_, loc) -> HExpr.Error("Invalid use of range syntax.", loc), nameCtx

  | AExpr.TupleLit (items, loc) ->
      let doArm () =
        let items, nameCtx = (items, nameCtx) |> stMap astToHirExpr
        hxTuple items loc, nameCtx

      doArm ()

  | AExpr.Anno (body, ty, loc) ->
      let doArm () =
        let body, nameCtx = (body, nameCtx) |> astToHirExpr
        let ty, nameCtx = (ty, nameCtx) |> astToHirTy
        hxAnno body ty loc, nameCtx

      doArm ()

  | AExpr.Semi (exprs, loc) ->
      let doArm () =
        assert (exprs |> listIsEmpty |> not)
        let exprs, nameCtx = (exprs, nameCtx) |> stMap astToHirExpr
        hxSemi exprs loc, nameCtx

      doArm ()

  | AExpr.Let (pat, body, next, loc) ->
      let doArm () =
        match desugarLet pat body next loc with
        | ALet.LetFun (ident, args, body, next, loc) ->
            let serial, nameCtx = nameCtx |> nameCtxAdd ident
            let isMainFun = false // Name resolution should correct this.
            let args, nameCtx = (args, nameCtx) |> stMap astToHirPat
            let body, nameCtx = (body, nameCtx) |> astToHirExpr
            let next, nameCtx = (next, nameCtx) |> astToHirExpr
            HExpr.LetFun(serial, isMainFun, args, body, next, noTy, loc), nameCtx

        | ALet.LetVal (pat, body, next, loc) ->
            let pat, nameCtx = (pat, nameCtx) |> astToHirPat
            let body, nameCtx = (body, nameCtx) |> astToHirExpr
            let next, nameCtx = (next, nameCtx) |> astToHirExpr
            HExpr.Let(pat, body, next, noTy, loc), nameCtx

      doArm ()

  | AExpr.TySynonym (ident, ty, loc) ->
      let doArm () =
        let serial, nameCtx = nameCtx |> nameCtxAdd ident
        let ty, nameCtx = (ty, nameCtx) |> astToHirTy
        HExpr.TyDecl(serial, TyDecl.Synonym(ty, loc), loc), nameCtx

      doArm ()

  | AExpr.TyUnion (ident, variants, loc) ->
      let doArm () =
        let onVariant (AVariant (ident, payloadTy, _variantLoc), nameCtx) =
          let serial, nameCtx = nameCtx |> nameCtxAdd ident

          let hasPayload, payloadTy, nameCtx =
            match payloadTy with
            | Some ty ->
                let ty, nameCtx = (ty, nameCtx) |> astToHirTy
                true, ty, nameCtx
            | None -> false, tyUnit, nameCtx

          (ident, serial, hasPayload, payloadTy), nameCtx

        let unionSerial, nameCtx = nameCtx |> nameCtxAdd ident
        let variants, nameCtx = (variants, nameCtx) |> stMap onVariant
        HExpr.TyDecl(unionSerial, TyDecl.Union(ident, variants, loc), loc), nameCtx

      doArm ()

  | AExpr.Open (path, loc) ->
      let doArm () = HExpr.Open(path, loc), nameCtx
      doArm ()

let astToHir (expr: AExpr, nameCtx: NameCtx): HExpr * NameCtx = (expr, nameCtx) |> astToHirExpr
