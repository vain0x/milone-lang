module rec fun_generic_nesting.Program

// Type inference of nested function in generic function is subtle.

// Updated: Local functions do no longer get generalized.

// let main _ =
//   // Case 1.
//   let myId x =
//     // aux must not be generic.
//     let aux () = x
//     aux ()

//   assert (myId 1 = 1)
//   assert (myId "a" = "a")

//   // Case 2.
//   let goo x =
//     // gooAux must not be generic.
//     let gooAux () = myId x
//     gooAux ()

//   assert (goo 1 = 1)
//   assert (goo "a" = "a")
//   0

let main _ = 0
