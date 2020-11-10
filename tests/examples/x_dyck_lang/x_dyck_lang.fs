let main _ =
  let rec go (s : string) i d =
    if i >= s.Length then
      d = 0
    else if s.[i] = '(' then
      go s (i + 1) (d + 1)
    else if d <= 0 then
      false
    else
      go s (i + 1) (d - 1)
  let parse (s : string) =
    if go s 0 0 then "Accept" else "Reject"

  let case1 = "()"
  let case2 = "()((())(()))()"
  let case3 = "(()"
  let case4 = ")("

  printfn "case1 (A): %s" (parse case1)
  printfn "case2 (A): %s" (parse case2)
  printfn "case3 (R): %s" (parse case3)
  printfn "case4 (R): %s" (parse case4)

  0
