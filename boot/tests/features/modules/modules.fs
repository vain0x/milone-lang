module rec modules

open modules.helpers
open modules.helpers

let main _ =
  // `helpers.Val` is available
  let n =
    match Int 0 with
    | Int x -> x

  // `helpers.f` is available
  let m = f n

  m