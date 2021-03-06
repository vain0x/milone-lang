module rec generic_right_angles.Program

// Right angle brackets '>' is distinct from shift operators.

type L<'T> = 'T list

let main _ =
  // End of type arguments.
  let n : L<L<L<int>>> = []
  //              ^^^

  let ok =
    match n with
    | [] -> true
    | _ -> false

  assert ok

  // Comparison.
  assert (3 >= 2)

  // Bit shift.
  assert (2 <<< 3 = 16)
  0
