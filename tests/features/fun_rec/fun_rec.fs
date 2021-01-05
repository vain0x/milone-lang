module rec fun_rec.Program

// Function defined with `let rec` is recursive.

let main _ =
  let source = "hello world"
  let len = source.Length

  let rec go i =
    if i < len then
      if source.[i] = 'o' then printfn "%d" i
      go (i + 1)

  go 0
  0
