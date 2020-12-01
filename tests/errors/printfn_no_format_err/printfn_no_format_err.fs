module rec printfn_no_format_err.Program

// printfn requires a string literal as first argument.

let main _ =
  let msg = "hello!"
  printfn msg
  assert false
  0
