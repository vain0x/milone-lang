module rec modules

open modules.helpers
open modules.helpers

let main _ =
  let n =
    // imported variant
    match Int 0 with
    // pattern of imported variant
    | Int x -> x

    // nav pattern of imported type
    | Val.Str _ -> 0

  // `helpers.f` is imported
  let m = f n

  m
