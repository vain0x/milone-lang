module rec native_size_of_val.Program

// Compiler intrinsic to obtain size of value.
// See also x_native_code.md in docs.

let listToArraySize xs =
  match xs with
  | [] -> 0

  | x :: _ ->
    let itemSize = __sizeOfVal x

    let rec go n xs =
      match xs with
      | [] -> n
      | _ :: xs -> go (n + 1) xs

    let n = go 0 xs

    itemSize * n

let main _ =
  assert (listToArraySize [ 2; 3; 5 ] = 3 * 4)
  assert (listToArraySize [ "x"; "y" ] = 2 * 16)
  0
