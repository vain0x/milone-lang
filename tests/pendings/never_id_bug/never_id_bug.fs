module rec never_id_bug.Program

// Generated code causes a compiler warning
// when a never value is applied to the id function.

// let private repro () =
//   match Some(exit 0: never) with
//   | Some n -> id n
//   | _ -> ()

// let main _ =
//   repro ()
//   0

// Generated code (in MiloneCore_Prelude.c):

// _Noreturn void MiloneCore_Prelude_NeverNeverFun1_id(char idArg_) {
// }

// Compiler warning:

// MiloneCore_Prelude.c:10:1: warning: ‘noreturn’ function does return
//    10 | }
//       | ^

let main _ = 0
