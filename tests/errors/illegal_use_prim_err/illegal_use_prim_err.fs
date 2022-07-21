module rec illegal_use_prim_err.Program

let main _ =
  let _ = __discriminant 0
  let _ = __discriminant (Some 0)

  0
