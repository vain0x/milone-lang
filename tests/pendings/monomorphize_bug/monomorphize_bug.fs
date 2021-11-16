module rec monomorphize_bug.Program

let main _ =
  // This emits invalid C code. Bug.
  // assert (List.fold (fun x y -> x + y) "" [ "x"; "y"; "z" ] = "xyz")
  0

// In (fun x y -> x + y), (+) is codegen'd as int -> int -> int.
// int fun_(int x_22, int y_3) {
//     return (x_22 + y_3);
// }

// On partial app, (+) is string -> string -> string. Inconsistent.
// struct String fun_1(void const* env_, struct String arg_, struct String arg_1) {
//     struct String call_1 = fun_(arg_, arg_1);
//     return call_1;
// }
