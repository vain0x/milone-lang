module rec fun_forward_reference_inference_bug.Program

// Function inference works incorrectly.

// // Call function defined later. type of value is not determined here.
// let fun1 value = fun2 value [ "" ]

// let fun2 (value: int) (list: string list) = value + 1, list

// let main _ =
//   let n, _ = fun1 2
//   assert (n = 3)
//   0

let main _ = 0
