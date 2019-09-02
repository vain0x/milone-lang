let bindInt (f: int -> string -> unit) (x: int) = f x

// Not capturing.
let printInt value label =
  printfn "%d: %s" value label

let main _ =
  let print42 = bindInt printInt 42
  print42 "The answer"

  let d = "'"
  // Capturing `d`.
  let rec der (n: int) (f: string) =
    if n = 0 then
      printfn "%s" f
    else
      der (n - 1) (f + d)
  let der2 = bindInt der 2
  der2 "f"

  0
