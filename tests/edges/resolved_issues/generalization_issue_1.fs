// Fixed.

// Invalid C code was generated.

// The reason was:
// Meta types bounded by traits (constraints) can be generalized.
// Functions that generalized these meta types have too generic type schemes.
// Use of functions with incorrect type arguments becomes incorrect code.

let private test () =
  // This emits invalid C code. Bug.
  assert (List.fold (fun x y -> x + y) "" [ "x"; "y"; "z" ] = "xyz")
  ()

test ()

// In (fun x y -> x + y), (+) is codegen'd as int -> int -> int.
// int fun_(int x_22, int y_3) {
//     return (x_22 + y_3);
// }

// On partial app, (+) is string -> string -> string. Inconsistent.
// struct String fun_1(void const* env_, struct String arg_, struct String arg_1) {
//     struct String call_1 = fun_(arg_, arg_1);
//     return call_1;
// }
