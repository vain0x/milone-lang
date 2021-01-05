module rec ty_var.Program

// Type variable is available in ascription.

let pair (_: 'x * 'x) = 2

// FIXME: Without ascription, the result type is inferred too generic
//        since trait bounds are processed after generalization
//        (bounds should be processed *before* generalization ideally).
let useStringIndexWithoutAscription x: char =
  // This unifies type of x to string.
  let _ = pair (x, "")

  // This passes the type check without explicit x: string ascription.
  x.[0]

let useTyVarInBody (x: 'T) =
  let xs: 'T list = []
  x, xs

let main _ =
  assert (pair (0, 0) = 2)
  assert (pair ("", "") = 2)

  assert (useStringIndexWithoutAscription "a" = 'a')

  match useTyVarInBody "b" with
  | _, s :: _ -> assert (s.[0] = 'b')
  | _ -> ()
  0
