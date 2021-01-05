module rec pat_discard.Program

let main _ =
  let f () = printfn "hello"
  let _, _ = f (), f ()
  0
