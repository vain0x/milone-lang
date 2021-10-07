module rec fun_forward_reference_inference_bug.Program

// Function inference works incorrectly.

// Call function defined later. type of value is not determined here.
let fun1 value = fun2 value

let g () = fun1 ""

let fun2 (value: int) = value + 1

let main _ =
  let n = fun1 2
  assert (n = 3)

  let x = g ()
  0
