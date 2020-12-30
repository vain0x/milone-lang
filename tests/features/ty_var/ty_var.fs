module rec ty_var.Program

// Type variable is available in annotation.

let pair (_: 'x * 'x) = 2

let useStringIndexWithoutAnnotation x =
  // This unifies type of x to string.
  let _ = pair (x, "")

  // This passes the type check without explicit x: string annotation.
  x.[0]

let useTyVarInBody (x: 'T) =
  let xs: 'T list = []
  x, xs

let main _ =
  assert (pair (0, 0) = 2)
  assert (pair ("", "") = 2)

  assert (useStringIndexWithoutAnnotation "a" = 'a')

  match useTyVarInBody "b" with
  | _, s :: _ -> assert (s.[0] = 'b')
  | _ -> ()
  0
