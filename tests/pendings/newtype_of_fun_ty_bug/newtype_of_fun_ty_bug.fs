module rec newtype_of_fun_ty_bug.Program

// Repro.
// Newtype of function type is buggy. Invalid code is generated.

// Guess: arity check doesn't count newtype unwrapping. Unwrapping a newtype of function changes arity of object. Arity computation is inconsistent between Syntax and Translation.

// type private F = F of (unit -> int)

// let main _ =
//   let getF = fun () -> F(fun () -> 42)
//   let (F f) = getF ()
//   assert (f () = 42)
//   0
