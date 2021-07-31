module rec module_forward_reference_bug.Program

// bug: module contents can't be forward reference.

module rec Early =
  let f () = 2
// Here g in Late is considered undefined.
// (The name 'g' here should denote to some value; but not found.)
// let f () = Late.g ()

module rec Late =
  let g () = 2

let main _ =
  assert (Early.f () = 2)
  0
