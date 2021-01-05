module rec bool_if_expr_complicated.Program

let main _ =
  if true then
    printfn "then"
    let hello = "hello"
    if true then
      0
    else
      printfn "else: %s" hello
      1
  else
    printfn "else"
    1
