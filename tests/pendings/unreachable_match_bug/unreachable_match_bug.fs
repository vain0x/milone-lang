module rec unreachable_match_bug.Program

// Invalid code is generated
// when a match expression is written in an unreachable branch.

// let private repro () =
//   let x =
//     exit 0
//     0

//   (match x with
//    | _ -> ())

//   ()

// let main _ =
//   repro()
//   0

// Generated code:

// void unreachable_match_bug_unreachable_match_bug_repro(void) {
//     MiloneCore_Prelude_exit(0);
//     milone_never_error("unreachable_match_bug/unreachable_match_bug.milone", 4, 8);
// clause_2:;
//     switch_ = 0;
//     goto switch_next_1;
// switch_next_1:;
//     return;
// }

// Compile error:
// unreachable_match_bug.c:15:5: error: ‘switch_’ undeclared (first use in this function)
//    15 |     switch_ = 0;
//       |     ^~~~~~~

let main _ = 0
