module rec modules.Program

open modules.sub
open modules.sub

let main _ =
  let n =
    // imported variant
    match Int 0 with
    // pattern of imported variant
    | Int x -> x

    // nav pattern of imported type
    | Val.Str _ -> 0

  // `sub.f` is imported
  let m = f n

  m
