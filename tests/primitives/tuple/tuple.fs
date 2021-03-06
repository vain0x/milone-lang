module rec tuple.Program

// Tuple creation and decomposition.

let main _ =
  let a = 1, "snd"
  let x, _x = a
  printfn "%d" x

  let b = "fst", 2
  let y, _y = b
  printfn "%s" y

  let z, w = "z", "w"
  printfn "z=%s" z
  printfn "w=%s" w

  let (p, q), r = ("p", "q"), "r"
  printfn "p=%s" p
  0
