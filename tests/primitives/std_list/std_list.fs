module rec std_list.Program

// Tests MiloneStd/List.fs (incomplete)

module S = MiloneStd.StdString

/// Expects two `int-list`s are equal.
let private eq (expected: int list) actual : bool =
  let debug (xs: int list) = xs |> List.map string |> S.concat ", "

  let expected = debug expected
  let actual = debug actual

  if expected = actual then
    true
  else
    printfn "expected: %s\nactual: %s\n" expected actual
    false

// ===============================================

let testSkipWhile (gen: int -> int list) =
  assert (gen 5 |> List.skipWhile (fun _ -> true) |> eq [])

  assert (gen 5
          |> List.skipWhile (fun n -> n % 2 = 0)
          |> eq [ 1; 2; 3; 4 ])

// ===============================================

let testUnzip () =
  let xs, ys =
    List.unzip [ 0, 1
                 1, 1
                 2, 2
                 3, 3
                 4, 5 ]

  assert (xs |> eq [ 0; 1; 2; 3; 4 ])
  assert (ys |> eq [ 1; 1; 2; 3; 5 ])

// ===============================================

let main _ =
  /// Generates 0..n-1
  let rec gen n =
    let rec go acc i =
      if i = 0 then
        acc
      else
        let i = i - 1
        go (i :: acc) i

    go [] n

  assert (gen 0 |> List.isEmpty)

  assert (gen 5
          |> List.fold (fun (x: int) (y: int) -> x + y) 0 = 0 + 1 + 2 + 3 + 4)

  let gen = gen

  testSkipWhile gen
  testUnzip ()
  0
