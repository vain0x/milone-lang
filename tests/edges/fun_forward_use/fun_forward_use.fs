// Fixed.

// In module rec, functions can be used before declaration.
// That makes type inference ~slightly tricky~ broken for now.

// Here, `g` is not declared and it has provisional type.
// Type of `f` is inferred to `unit -> 'a`, too generic.
let private f () = g ()

// Here, type of `g` is concluded to `unit -> int`.
// And then provisional type used above is unified to the actual type:
//        unit -> 'a
//    vs. unit -> int
// This unification should fail since 'a is already quantified.
let private g () = 0

let private test () =
  assert (f () = 0)

  // Since f is inferred too generic, f can return any type.
  assert (f () = "")
  ()

test ()
