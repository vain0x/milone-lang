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

let valueTy (value: Value): Ty =
  match value with
  | Value.Bool _ -> Ty.Bool
  | Value.Int _ -> Ty.Int
  | Value.Char _ -> Ty.Char
  | Value.Str _ -> Ty.Str

let valueMTy (value: Value): MTy =
  match value with
  | Value.Bool _ -> MTy.Bool
  | Value.Int _ -> MTy.Int
  | Value.Char _ -> MTy.Char
  | Value.Str _ -> MTy.Str

let patExtract (pat: Pat<'a>): Ty * 'a =
  match pat with
  | Pat.Value (value, a) ->
    valueTy value, a
  | Pat.Unit a ->
    Ty.Unit, a
  | Pat.Nil (itemTy, a) ->
    Ty.List itemTy, a
  | Pat.Ref (_, _, ty, a) ->
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
    | Pat.Value (value, a) ->
      Pat.Value (value, g a)
    | Pat.Unit a ->
      Pat.Unit (g a)
    | Pat.Nil (itemTy, a) ->
      Pat.Nil (f itemTy, g a)
    | Pat.Ref (ident, serial, ty, a) ->
      Pat.Ref (ident, serial, f ty, g a)
    | Pat.Cons (l, r, itemTy, a) ->
      Pat.Cons (go l, go r, f itemTy, g a)
    | Pat.Tuple (itemPats, ty, a) ->
      Pat.Tuple (List.map go itemPats, f ty, g a)
    | Pat.Anno (pat, ty, a) ->
      Pat.Anno (go pat, f ty, g a)
  go pat

let exprExtract (expr: Expr<'a>): Ty * 'a =
  match expr with
  | Expr.Value (value, a) ->
    valueTy value, a
  | Expr.Unit a ->
    Ty.Unit, a
  | Expr.Ref (_, _, ty, a) ->
    ty, a
  | Expr.List (_, itemTy, a) ->
    Ty.List itemTy, a
  | Expr.If (_, _, _, ty, a) ->
    ty, a
  | Expr.Match (_, _, _, ty, a) ->
    ty, a
  | Expr.Nav (_, _, ty, a) ->
    ty, a
  | Expr.Index (_, _, ty, a) ->
    ty, a
  | Expr.Call (_, _, ty, a) ->
    ty, a
  | Expr.Op (_, _, _, ty, a) ->
    ty, a
  | Expr.Tuple (_, ty, a) ->
    ty, a
  | Expr.Anno (_, ty, a) ->
    ty, a
  | Expr.AndThen (_, ty, a) ->
    ty, a
  | Expr.Let (_, _, a) ->
    Ty.Unit, a

let exprMap (f: Ty -> Ty) (g: 'a -> 'b) (expr: Expr<'a>): Expr<'b> =
  let goPat pat =
    patMap f g pat
  let rec go expr =
    match expr with
    | Expr.Value (value, a) ->
      Expr.Value (value, g a)
    | Expr.Unit a ->
      Expr.Unit (g a)
    | Expr.Ref (ident, serial, ty, a) ->
      Expr.Ref (ident, serial, f ty, g a)
    | Expr.List (items, itemTy, a) ->
      Expr.List (List.map go items, f itemTy, g a)
    | Expr.If (pred, thenCl, elseCl, ty, a) ->
      Expr.If (go pred, go thenCl, go elseCl, f ty, g a)
    | Expr.Match (target, (pat1, body1), (pat2, body2), ty, a) ->
      let arm1 = (goPat pat1, go body1)
      let arm2 = (goPat pat2, go body2)
      Expr.Match (go target, arm1, arm2, f ty, g a)
    | Expr.Nav (sub, mes, ty, a) ->
      Expr.Nav (go sub, mes, f ty, g a)
    | Expr.Index (l, r, ty, a) ->
      Expr.Index (go l, go r, f ty, g a)
    | Expr.Call (callee, args, ty, a) ->
      Expr.Call (go callee, List.map go args, f ty, g a)
    | Expr.Op (op, l, r, ty, a) ->
      Expr.Op (op, go l, go r, f ty, g a)
    | Expr.Tuple (exprs, ty, a) ->
      Expr.Tuple (List.map go exprs, f ty, g a)
    | Expr.Anno (expr, ty, a) ->
      Expr.Anno (go expr, f ty, g a)
    | Expr.AndThen (exprs, ty, a) ->
      Expr.AndThen (List.map go exprs, f ty, g a)
    | Expr.Let (pats, init, a) ->
      Expr.Let (List.map goPat pats, go init, g a)
  go expr

let exprTy expr =
  let ty, _ = exprExtract expr
  ty

let mexprExtract expr =
  match expr with
  | MExpr.Default (ty, loc) -> ty, loc
  | MExpr.Value (value, loc) -> valueMTy value, loc
  | MExpr.Ref (_, ty, loc) -> ty, loc
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

let knownSerials =
  [
    SerialNot
    SerialExit
    SerialBox
    SerialUnbox
    SerialPrintfn
    SerialStrSlice
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
