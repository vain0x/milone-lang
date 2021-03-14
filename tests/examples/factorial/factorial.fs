module rec factorial.Program

let main _ =
  let rec factorial x =
    if x = 0 then
      1
    else
      x * factorial (x - 1)

  factorial 5 - 120
