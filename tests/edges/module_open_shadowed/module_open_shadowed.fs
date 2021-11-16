module rec module_open_shadowed.Program

open module_open_shadowed.sub

let g () = "g is shadowed"

let main _ =
  assert (f 40 = 42) // not shadowed

  assert (g () = "g is shadowed")

  let () =
    let f () = "f is locally shadowed"
    assert (f () = "f is locally shadowed")

  0
