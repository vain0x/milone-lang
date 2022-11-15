module rec resolved_issues.Program

// -----------------------------------------------
// fun_arity_never_result_bug
// -----------------------------------------------

// Type: Invalid code generation

// Description:
// At the time when never-returning functions have the generic-returning signature (_ -> 'T),
// it was a problem that the return type ('T) is bound to a function type.

// Resolution: At v0.6.0 never type was introduced and the issue had gone.

let private testFunArityNeverResultBug () =
  let unreachable () : never = exit 1
  let f =
    match 1 with
    | 1 -> id: int -> int
    | _ -> unreachable ()
  //       ^^^

  assert (f 1 = 1)

// Generated code:

// struct IntIntFun1 fun_arity_never_result_bug_fun_arity_never_result_bug_UnitIntIntFun2_unreachable(void) {
//     struct UnitIntIntFun2 call_ = fun_arity_never_result_bug_fun_arity_never_result_bug_StringUnitIntIntFun3_failwithf((struct String){.ptr = "NEVER: %A", .len = 9});
//     struct IntIntFun1 app_ = call_.fun(call_.env);
//     return app_;
// }

// Note `call_.fun` is error, lack of arguments.

// ===============================================

let main _ =
  testFunArityNeverResultBug ()
  0
