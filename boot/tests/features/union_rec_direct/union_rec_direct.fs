/// Example of directly recursive discriminated union type.
/// Without indirection, this type has infinite size.
type Expr =
  | Int
    of int
  | Add
    of Expr * Expr

let main _ =
  let rec eval expr =
    match expr with
    | Expr.Int value ->
      value
    | Expr.Add (l, r) ->
      eval l + eval r

  let expr =
    Expr.Add (Expr.Int 11, Expr.Add (Expr.Int 22, Expr.Int 9))
  assert (eval expr = 42)

  0
