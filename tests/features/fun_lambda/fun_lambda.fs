module rec fun_lambda.Program

// Anonymous function expression (so-called "lambda", incorrectly) is supported.
// Syntax is subtle.

let layoutTest () =
  let apply f x = f x

  let a =
    2
    |> apply
         (fun x -> // callee can be deeper than arguments
           x + 3)

  assert (a = 5)

let main _ =
  let twice f x = x |> f |> f

  let x =
    40
    |> twice
         (fun x ->
           let y = x + 1
           y)

  assert (x = 42)

  assert ((fun x y -> x / y + 0) 84 2 = 42)

  layoutTest ()
  0
