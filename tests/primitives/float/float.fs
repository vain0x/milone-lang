module rec float.Program

// float type is supported.

let all pred xs =
  let rec go xs =
    match xs with
    | [] -> true
    | x :: xs -> pred x && go xs

  go xs

let main _ =
  // Float literals.
  let zeros =
    [ 0.0
      0.
      000.000
      0e0
      0E0
      0E+9
      0E-9
      00.00e-00 ]

  assert (all (fun x -> x = 0.0) zeros)

  let values =
    [ 1.0
      42.195
      1e9
      1E9
      1e+9
      1E+9
      1e-9
      1E-9
      1e+23
      1e-23
      6.02e-23 ]

  assert (all (fun x -> x > 0.0) values)

  // Arithmetic operations.
  assert (2.3 + 4.5 > 6.0)
  assert (44.0 - 2.0 = 42.0)
  assert (2.25 * 2.0 = 4.5)
  assert (8.0 / 2.0 = 4.0)

  // Comparison.
  assert (0.0 = 0.0)
  assert (0.0 <> 1.0)

  assert (2.0 < 3.0)
  assert (2.0 <= 2.0)
  assert (2.0 <= 3.0)

  assert (3.0 > 2.0)
  assert (2.0 >= 2.0)
  assert (3.0 >= 2.0)

  // Conversion from/to int.
  assert (int 3.14 = 3)
  assert (float 3 = 3.0)

  // Conversion to string.
  // FIXME: Formatting should be compatible with .NET?
  assert (string 3.14 = "3.140000")

  // Conversion from string.
  assert (float "3.14" = 3.14)

  // Formatting with printfn.
  printfn "Assume PI is %f." 3.14
  0
