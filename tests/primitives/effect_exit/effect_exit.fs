module rec effect_exit.Program

let main _ =
  let t = exit 1
  let (x: int), (y: string) = t
  printfn "%s" (exit 2)

  // The argument type is inferred as int.
  exit (unbox (box 1))

  exit 0
