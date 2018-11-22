module MiloneLang.Helpers

/// `List.map`, modifying context.
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

let litTy (lit: Lit): Ty =
  match lit with
  | Lit.Bool _ -> Ty.Bool
  | Lit.Int _ -> Ty.Int
  | Lit.Char _ -> Ty.Char
  | Lit.Str _ -> Ty.Str

let litMTy (lit: Lit): MTy =
  match lit with
  | Lit.Bool _ -> MTy.Bool
  | Lit.Int _ -> MTy.Int
  | Lit.Char _ -> MTy.Char
  | Lit.Str _ -> MTy.Str

let patExtract (pat: Pat<'a>): Ty * 'a =
  match pat with
  | Pat.Lit (lit, a) ->
    litTy lit, a
  | Pat.Unit a ->
    Ty.Unit, a
  | Pat.Nil (itemTy, a) ->
    Ty.List itemTy, a
  | Pat.Ref (_, _, ty, a) ->
    ty, a
  | Pat.Call (_, _, ty, a) ->
    ty, a
  | Pat.Cons (_, _, itemTy, a) ->
    Ty.List itemTy, a
  | Pat.Tuple (_, ty, a) ->
    ty, a
  | Pat.Anno (_, ty, a) ->
    ty, a

let patMap (f: Ty -> Ty) (g: 'a -> 'b) (pat: Pat<'a>): Pat<'b> =
  let rec go pat =
    match pat with
    | Pat.Lit (lit, a) ->
      Pat.Lit (lit, g a)
    | Pat.Unit a ->
      Pat.Unit (g a)
    | Pat.Nil (itemTy, a) ->
      Pat.Nil (f itemTy, g a)
    | Pat.Ref (ident, serial, ty, a) ->
      Pat.Ref (ident, serial, f ty, g a)
    | Pat.Call (callee, args, ty, a) ->
      Pat.Call (go callee, List.map go args, f ty, g a)
    | Pat.Cons (l, r, itemTy, a) ->
      Pat.Cons (go l, go r, f itemTy, g a)
    | Pat.Tuple (itemPats, ty, a) ->
      Pat.Tuple (List.map go itemPats, f ty, g a)
    | Pat.Anno (pat, ty, a) ->
      Pat.Anno (go pat, f ty, g a)
  go pat

let exprExtract (expr: Expr<'a>): Ty * 'a =
  match expr with
  | Expr.Lit (lit, a) ->
    litTy lit, a
  | Expr.Unit a ->
    Ty.Unit, a
  | Expr.Ref (_, _, _, ty, a) ->
    ty, a
  | Expr.List (_, itemTy, a) ->
    Ty.List itemTy, a
  | Expr.If (_, _, _, ty, a) ->
    ty, a
  | Expr.Match (_, _, ty, a) ->
    ty, a
  | Expr.Nav (_, _, ty, a) ->
    ty, a
  | Expr.Index (_, _, ty, a) ->
    ty, a
  | Expr.Op (_, _, _, ty, a) ->
    ty, a
  | Expr.Tuple (_, itemTys, a) ->
    Ty.Tuple itemTys, a
  | Expr.Anno (_, ty, a) ->
    ty, a
  | Expr.AndThen (_, ty, a) ->
    ty, a
  | Expr.Let (_, _, a) ->
    Ty.Unit, a
  | Expr.TyDef (_, _, _, a) ->
    Ty.Unit, a

let exprMap (f: Ty -> Ty) (g: 'a -> 'b) (expr: Expr<'a>): Expr<'b> =
  let goPat pat =
    patMap f g pat
  let rec go expr =
    match expr with
    | Expr.Lit (lit, a) ->
      Expr.Lit (lit, g a)
    | Expr.Unit a ->
      Expr.Unit (g a)
    | Expr.Ref (ident, serial, arity, ty, a) ->
      Expr.Ref (ident, serial, arity, f ty, g a)
    | Expr.List (items, itemTy, a) ->
      Expr.List (List.map go items, f itemTy, g a)
    | Expr.If (pred, thenCl, elseCl, ty, a) ->
      Expr.If (go pred, go thenCl, go elseCl, f ty, g a)
    | Expr.Match (target, arms, ty, a) ->
      let arms = arms |> List.map (fun (pat, body) -> goPat pat, go body)
      Expr.Match (go target, arms, f ty, g a)
    | Expr.Nav (sub, mes, ty, a) ->
      Expr.Nav (go sub, mes, f ty, g a)
    | Expr.Index (l, r, ty, a) ->
      Expr.Index (go l, go r, f ty, g a)
    | Expr.Op (Op.Cons itemTy, l, r, ty, a) ->
      Expr.Op (Op.Cons (f itemTy), go l, go r, f ty, g a)
    | Expr.Op (op, l, r, ty, a) ->
      Expr.Op (op, go l, go r, f ty, g a)
    | Expr.Tuple (exprs, itemTys, a) ->
      Expr.Tuple (List.map go exprs, List.map f itemTys, g a)
    | Expr.Anno (expr, ty, a) ->
      Expr.Anno (go expr, f ty, g a)
    | Expr.AndThen (exprs, ty, a) ->
      Expr.AndThen (List.map go exprs, f ty, g a)
    | Expr.Let (pat, init, a) ->
      Expr.Let (goPat pat, go init, g a)
    | Expr.TyDef (ident, serial, tyDef, a) ->
      Expr.TyDef (ident, serial, tyDef, g a)
  go expr

let exprTy expr =
  let ty, _ = exprExtract expr
  ty

let exprArity expr =
  match expr with
  | Expr.Ref (_, _, arity, _, _) ->
    arity
  | _ ->
    1

let mexprExtract expr =
  match expr with
  | MExpr.Default (ty, loc) -> ty, loc
  | MExpr.Lit (lit, loc) -> litMTy lit, loc
  | MExpr.Ref (_, _, ty, loc) -> ty, loc
  | MExpr.Variant (_, _, ty, loc) -> ty, loc
  | MExpr.UniOp (_, _, ty, loc) -> ty, loc
  | MExpr.Op (_, _, _, ty, loc) -> ty, loc

let mexprTy expr =
  let ty, _ = mexprExtract expr
  ty

let opIsComparison op =
  match op with
  | MOp.Eq
  | MOp.Ne
  | MOp.Lt
  | MOp.Le ->
    true
  | _ ->
    false

let noArity = 0

/// Placeholder. No variable serials in the parsing phase.
let noSerial = 0

/// Placeholder. No type info in the parsing phase.
let noTy = Ty.Error

[<Literal>]
let SerialNot = -1

[<Literal>]
let SerialExit = -2

[<Literal>]
let SerialBox = -3

[<Literal>]
let SerialUnbox = -4

[<Literal>]
let SerialPrintfn = -5

[<Literal>]
let SerialStrSlice = -6

[<Literal>]
let SerialStrLength = -7

let knownSerials =
  [
    SerialNot
    SerialExit
    SerialBox
    SerialUnbox
    SerialPrintfn
    SerialStrSlice
    SerialStrLength
  ]

let analyzeFormat (format: string) =
  let rec go i =
    if i >= format.Length then
      Ty.Unit
    else
      if i + 1 < format.Length && format.[i] = '%' then
        match format.[i + 1] with
        | 's' ->
          Ty.Fun (Ty.Str, go (i + 2))
        | 'd' ->
          Ty.Fun (Ty.Int, go (i + 2))
        | 'c' ->
          Ty.Fun (Ty.Char, go (i + 2))
        | _ ->
          go (i + 2)
      else
        go (i + 1)
  Ty.Fun (Ty.Str, go 0)

let rec arityTy ty =
  match ty with
  | Ty.Fun (_, ty) ->
    1 + arityTy ty
  | _ ->
    0