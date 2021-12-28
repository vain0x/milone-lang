module rec newtype_of_fun_ty_bug.Program

// Repro.
// Newtype of function type is buggy. Invalid code is generated.

type private F = F of (unit -> int)

let main _ =
  let getF = fun () -> F(fun () -> 42)
  let (F f) = getF ()
  assert (f () = 42)
  0
