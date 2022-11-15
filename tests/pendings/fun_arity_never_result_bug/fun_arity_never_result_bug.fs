module rec fun_arity_never_result_bug.Program

// Invalid code is generated.
// Expected: Arity check reports an error or compiler generates working code.

let private unreachable context : never =
  printfn "NEVER"
  assert false
  unreachable context

let main _ =
  let f =
    match 1 with
    | 1 -> id: int -> int
    | _ -> unreachable ()

  assert (f 2 = 2)
  0

// Generated code:

// struct IntIntFun1 fun_arity_never_result_bug_fun_arity_never_result_bug_UnitIntIntFun2_unreachable(void) {
//     struct UnitIntIntFun2 call_ = fun_arity_never_result_bug_fun_arity_never_result_bug_StringUnitIntIntFun3_failwithf((struct String){.ptr = "NEVER: %A", .len = 9});
//     struct IntIntFun1 app_ = call_.fun(call_.env);
//     return app_;
// }

// Note `call_.fun` is error, lack of arguments.

// Workaround: Eta-expand manually.
// let main _ =
//   let f =
//     match 1 with
//     | 1 -> id: int -> int
//     | _ -> fun _ -> unreachable ()
//   //       ^^^^^ eta-expansion

//   assert (f 2 = 2)
//   0
