module rec fun_nonrec_err.Program

// Function defined with non-rec let can't recursively call itself.

let main _ =
  // let nonRecLoop (i: int) =
  //   assert (i <> 0)
  //   nonRecLoop (i + 1)

  // nonRecLoop 0
  1
