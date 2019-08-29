module rec MiloneLang.Helpers

open MiloneLang.Types

let listUnique (xs: 'x list): 'x list =
  xs |> set |> Set.toList

/// `List.map`, modifying context.
///
/// USAGE:
///   let ys, ctx = (xs, ctx) |> stMap (fun (x, ctx) -> y, ctx)
let stMap f (xs, ctx) =
  let rec go acc (xs, ctx) =
    match xs with
    | [] ->
      List.rev acc, ctx
    | x :: xs ->
      let y, ctx = f (x, ctx)
      go (y :: acc) (xs, ctx)
  go [] (xs, ctx)

/// `List.bind`, modifying context.
///
/// USAGE:
///   let ys, ctx = (xs, ctx) |> stFlatMap (fun (x, ctx) -> ys, ctx)
let stFlatMap f (xs, ctx) =
  let rec go acc xs ctx =
    match xs with
    | [] ->
      List.rev acc, ctx
    | x :: xs ->
      let acc, ctx = f (x, acc, ctx)
      go acc xs ctx
  go [] xs ctx

/// `Option.map`, modifying context.
let stOptionMap f (x, ctx) =
  match x with
  | Some x ->
    let x, ctx = f (x, ctx)
    Some x, ctx
  | None ->
    None, ctx

/// Maps over a list, collecting things, mutating context.
let exMap f (xs, acc, ctx) =
  let rec go ys xs acc ctx =
    match xs with
    | [] ->
      List.rev ys, acc, ctx
    | x :: xs ->
      let y, acc, ctx = f (x, acc, ctx)
      go (y :: ys) xs acc ctx
  go [] xs acc ctx

let cons head tail = head :: tail

/// No location information. Should be fixed.
let noLoc = -1, -1

// -----------------------------------------------
// Name context
// -----------------------------------------------

let nameCtxEmpty () =
  NameCtx (Map.empty, 0)

let nameCtxAdd ident (NameCtx (map, serial)) =
  let serial = serial + 1
  let map = map |> Map.add serial ident
  serial, NameCtx (map, serial)

// -----------------------------------------------
// Types
// -----------------------------------------------

/// Placeholder. No type info in the parsing phase.
let noTy = Ty.Error noLoc

let tyBool = Ty.Con (TyCon.Bool, [])

let tyInt = Ty.Con (TyCon.Int, [])

let tyChar = Ty.Con (TyCon.Char, [])

let tyStr = Ty.Con (TyCon.Str, [])

let tyObj = Ty.Con (TyCon.Obj, [])

let tyRange = Ty.Con (TyCon.Range, [])

let tyTuple tys =
  Ty.Con (TyCon.Tuple, tys)

let tyList ty =
  Ty.Con (TyCon.List, [ty])

let tyFun sourceTy targetTy =
  Ty.Con (TyCon.Fun, [sourceTy; targetTy])

let tyUnit =
  tyTuple []

let tyRef serial tys =
  Ty.Con (TyCon.Ref serial, tys)

let rec arityTy ty =
  match ty with
  | Ty.Con (TyCon.Fun, [_; ty]) ->
    1 + arityTy ty
  | _ ->
    0

/// Converts nested function type to multi-arguments function type.
let rec rollFunTy ty =
  let rec go n acc ty =
    match ty with
    | Ty.Con (TyCon.Fun, [sTy; tTy]) ->
      go (n + 1) (sTy :: acc) tTy
    | tTy ->
      n, List.rev acc, tTy
  go 0 [] ty

// -----------------------------------------------
// Type definitions (HIR)
// -----------------------------------------------

let tyDefIdent tyDef =
  match tyDef with
  | TyDef.Meta (ident, _, _) -> ident
  | TyDef.Union (ident, _, _) -> ident

// -----------------------------------------------
// Variable definitions (HIR)
// -----------------------------------------------

let varDefIdent varDef =
  match varDef with
  | VarDef.Var (ident, _, _) -> ident
  | VarDef.Fun (ident, _, _, _) -> ident
  | VarDef.Variant (ident, _, _, _, _, _) -> ident

// -----------------------------------------------
// Literals
// -----------------------------------------------

let litTy (lit: Lit): Ty =
  match lit with
  | Lit.Bool _ -> tyBool
  | Lit.Int _ -> tyInt
  | Lit.Char _ -> tyChar
  | Lit.Str _ -> tyStr

// -----------------------------------------------
// Primitives (HIR)
// -----------------------------------------------

let primToArity prim =
  match prim with
  | HPrim.Not
  | HPrim.Exit
  | HPrim.Assert
  | HPrim.Box
  | HPrim.Unbox
  | HPrim.StrLength
  | HPrim.Char
  | HPrim.Int
  | HPrim.String ->
    1
  | HPrim.StrSlice ->
    3
  | HPrim.Printfn ->
    9999
  | HPrim.NativeFun (_, arity) ->
    arity

// -----------------------------------------------
// Patterns (HIR)
// -----------------------------------------------

let patUnit loc =
  HPat.Tuple ([], tyUnit, loc)

let rec patExtract (pat: HPat): Ty * Loc =
  match pat with
  | HPat.Lit (lit, a) ->
    litTy lit, a
  | HPat.Nil (itemTy, a) ->
    tyList itemTy, a
  | HPat.Ref (_, _, ty, a) ->
    ty, a
  | HPat.Nav (_, _, ty, a) ->
    ty, a
  | HPat.Call (_, _, ty, a) ->
    ty, a
  | HPat.Cons (_, _, itemTy, a) ->
    tyList itemTy, a
  | HPat.Tuple (_, ty, a) ->
    ty, a
  | HPat.As (pat, _, _, a) ->
    let ty, _ = patExtract pat
    ty, a
  | HPat.Anno (_, ty, a) ->
    ty, a
  | HPat.Or (_, _, ty, a) ->
    ty, a

let patMap (f: Ty -> Ty) (g: Loc -> Loc) (pat: HPat): HPat =
  let rec go pat =
    match pat with
    | HPat.Lit (lit, a) ->
      HPat.Lit (lit, g a)
    | HPat.Nil (itemTy, a) ->
      HPat.Nil (f itemTy, g a)
    | HPat.Ref (ident, serial, ty, a) ->
      HPat.Ref (ident, serial, f ty, g a)
    | HPat.Nav (pat, ident, ty, a) ->
      HPat.Nav (pat, ident, f ty, g a)
    | HPat.Call (callee, args, ty, a) ->
      HPat.Call (go callee, List.map go args, f ty, g a)
    | HPat.Cons (l, r, itemTy, a) ->
      HPat.Cons (go l, go r, f itemTy, g a)
    | HPat.Tuple (itemPats, ty, a) ->
      HPat.Tuple (List.map go itemPats, f ty, g a)
    | HPat.As (pat, ident, serial, a) ->
      HPat.As (go pat, ident, serial, g a)
    | HPat.Anno (pat, ty, a) ->
      HPat.Anno (go pat, f ty, g a)
    | HPat.Or (first, second, ty, a) ->
      HPat.Or (go first, go second, f ty, g a)
  go pat

/// Converts a pattern in disjunctive normal form.
/// E.g. `A, [B | C]` → `(A | [B]), (A | [C])`
let patNormalize pat =
  let rec go pat =
    match pat with
    | HPat.Lit _
    | HPat.Ref _
    | HPat.Nil _ ->
      [pat]
    | HPat.Nav (pat, ident, ty, loc) ->
      go pat |> List.map
        (fun pat -> HPat.Nav (pat, ident, ty, loc))
    | HPat.Call (callee, [arg], ty, loc) ->
      go callee |> List.collect (fun callee ->
        go arg |> List.map (fun arg ->
          HPat.Call (callee, [arg], ty, loc)
        ))
    | HPat.Cons (l, r, ty, loc) ->
      go l |> List.collect (fun l ->
        go r |> List.map (fun r ->
          HPat.Cons (l, r, ty, loc)
        ))
    | HPat.Tuple (itemPats, ty, loc) ->
      let rec gogo itemPats =
        match itemPats with
        | [] -> [[]]
        | itemPat :: itemPats ->
          let itemPat = go itemPat
          gogo itemPats |> List.collect (fun itemPats ->
            itemPat |> List.map (fun itemPat ->
              itemPat :: itemPats
            ))
      gogo itemPats |> List.map
        (fun itemPats -> HPat.Tuple (itemPats, ty, loc))
    | HPat.As (innerPat, _, _, _) ->
      match go innerPat with
      | [_] ->
        [pat]
      | _ ->
        failwith "Unimpl: Can't use AS patterns conjunction with OR patterns"
    | HPat.Anno (pat, annoTy, loc) ->
      go pat |> List.map
        (fun pat -> HPat.Anno (pat, annoTy, loc))
    | HPat.Or (first, second, _, _) ->
      List.append (go first) (go second)
    | HPat.Call _ ->
      failwith "Unimpl"
  go pat

// -----------------------------------------------
// Expressions (HIR)
// -----------------------------------------------

let hxTrue loc =
  HExpr.Lit (Lit.Bool true, loc)

let hxFalse loc =
  HExpr.Lit (Lit.Bool false, loc)

let hxIndex l r ty loc =
  HExpr.Bin (Op.Index, l, r, ty, loc)

let hxAnno expr ty loc =
  HExpr.Inf (InfOp.Anno, [expr], ty, loc)

let hxSemi items loc =
  HExpr.Inf (InfOp.Semi, items, exprTy (List.last items), loc)

let hxCallProc callee args resultTy loc =
  HExpr.Inf (InfOp.CallProc, callee :: args, resultTy, loc)

let hxCallClosure callee args resultTy loc =
  HExpr.Inf (InfOp.CallClosure, callee :: args, resultTy, loc)

let hxTuple items loc =
  HExpr.Inf (InfOp.Tuple, items, tyTuple (List.map exprTy items), loc)

let hxUnit loc =
  hxTuple [] loc

let hxList items itemTy loc =
  HExpr.Inf (InfOp.List itemTy, items, tyList itemTy, loc)

let hxNil itemTy loc =
  hxList [] itemTy loc

let exprExtract (expr: HExpr): Ty * Loc =
  match expr with
  | HExpr.Lit (lit, a) ->
    litTy lit, a
  | HExpr.Ref (_, _, ty, a) ->
    ty, a
  | HExpr.If (_, _, _, ty, a) ->
    ty, a
  | HExpr.Match (_, _, ty, a) ->
    ty, a
  | HExpr.Nav (_, _, ty, a) ->
    ty, a
  | HExpr.Bin (_, _, _, ty, a) ->
    ty, a
  | HExpr.Inf (_, _, ty, a) ->
    ty, a
  | HExpr.Let (_, _, _, ty, a) ->
    ty, a
  | HExpr.LetFun (_, _, _, _, _, ty, a) ->
    ty, a
  | HExpr.TyDef (_, _, _, a) ->
    tyUnit, a
  | HExpr.Open (_, a) ->
    tyUnit, a
  | HExpr.Error (_, a) ->
    Ty.Error a, a

let exprMap (f: Ty -> Ty) (g: Loc -> Loc) (expr: HExpr): HExpr =
  let goPat pat =
    patMap f g pat
  let rec go expr =
    match expr with
    | HExpr.Lit (lit, a) ->
      HExpr.Lit (lit, g a)
    | HExpr.Ref (ident, serial, ty, a) ->
      HExpr.Ref (ident, serial, f ty, g a)
    | HExpr.If (pred, thenCl, elseCl, ty, a) ->
      HExpr.If (go pred, go thenCl, go elseCl, f ty, g a)
    | HExpr.Match (target, arms, ty, a) ->
      let arms =
        arms |> List.map (fun (pat, guard, body) ->
          goPat pat, go guard, go body)
      HExpr.Match (go target, arms, f ty, g a)
    | HExpr.Nav (sub, mes, ty, a) ->
      HExpr.Nav (go sub, mes, f ty, g a)
    | HExpr.Bin (op, l, r, ty, a) ->
      HExpr.Bin (op, go l, go r, f ty, g a)
    | HExpr.Inf (InfOp.List itemTy, items, resultTy, a) ->
      HExpr.Inf (InfOp.List (f itemTy), List.map go items, f resultTy, g a)
    | HExpr.Inf (infOp, args, resultTy, a) ->
      HExpr.Inf (infOp, List.map go args, f resultTy, g a)
    | HExpr.Let (pat, init, next, ty, a) ->
      HExpr.Let (goPat pat, go init, go next, f ty, g a)
    | HExpr.LetFun (ident, serial, args, body, next, ty, a) ->
      HExpr.LetFun (ident, serial, List.map goPat args, go body, go next, f ty, g a)
    | HExpr.TyDef (ident, serial, tyDef, a) ->
      HExpr.TyDef (ident, serial, tyDef, g a)
    | HExpr.Open (path, a) ->
      HExpr.Open (path, g a)
    | HExpr.Error (error, a) ->
      HExpr.Error (error, g a)
  go expr

let exprTy expr =
  let ty, _ = exprExtract expr
  ty

// -----------------------------------------------
// Binary Operators (MIR)
// -----------------------------------------------

let opIsComparison op =
  match op with
  | MOp.Eq
  | MOp.Ne
  | MOp.Lt
  | MOp.Le ->
    true
  | _ ->
    false

// -----------------------------------------------
// Expressions (MIR)
// -----------------------------------------------

let mexprExtract expr =
  match expr with
  | MExpr.Default (ty, loc) -> ty, loc
  | MExpr.Lit (lit, loc) -> litTy lit, loc
  | MExpr.Ref (_, ty, loc) -> ty, loc
  | MExpr.Proc (_, ty, loc) -> ty, loc
  | MExpr.Variant (_, _, ty, loc) -> ty, loc
  | MExpr.Uni (_, _, ty, loc) -> ty, loc
  | MExpr.Bin (_, _, _, ty, loc) -> ty, loc

let mexprTy expr =
  let ty, _ = mexprExtract expr
  ty

// -----------------------------------------------
// Print Formats
// -----------------------------------------------

let analyzeFormat (format: string) =
  let rec go i =
    if i >= format.Length then
      tyUnit
    else
      if i + 1 < format.Length && format.[i] = '%' then
        match format.[i + 1] with
        | 's' ->
          tyFun tyStr (go (i + 2))
        | 'd' ->
          tyFun tyInt (go (i + 2))
        | 'c' ->
          tyFun  tyChar (go (i + 2))
        | _ ->
          go (i + 2)
      else
        go (i + 1)
  tyFun tyStr (go 0)
