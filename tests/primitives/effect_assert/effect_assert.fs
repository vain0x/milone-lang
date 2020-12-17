module rec effect_assert.Program

let main _ =
  assert true
  printfn "pass"

  printfn "Notice: test 'effect_assert' intentionally prints an assertion error:"
  assert false
  printfn "not pass"
  0
