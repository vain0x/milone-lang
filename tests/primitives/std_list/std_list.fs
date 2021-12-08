module rec std_list.Program

// incomplete

// Tests MiloneCore/List.fs and MiloneStd/StdList.fs

open MiloneStd.StdList

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

let testTakeWhile (gen: int -> int list) =
  assert (gen 3
          |> List.takeWhile (fun _ -> true)
          |> eq [ 0; 1; 2 ])

  assert (gen 6
          |> List.takeWhile (fun n -> n % 3 <> 2)
          |> eq [ 0; 1 ])

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

let private testDrop (gen: int -> int list) =
  assert (gen 5 |> List.drop 0 |> eq (gen 5))
  assert (gen 5 |> List.drop 2 |> eq [ 2; 3; 4 ])
  assert (gen 5 |> List.drop 5 |> eq [])

  // Boundary exceeding.
  assert (gen 5 |> List.drop (-1) |> eq (gen 5))
  assert (gen 5 |> List.drop 6 |> eq [])

let private testZipEx (gen: int -> int list) =
  let xs = gen 3 |> List.map (fun x -> x + 10)
  let ys = gen 5 |> List.map (fun x -> x + 20)

  match List.zipEx xs ys with
  | zipped, l, r ->
    assert (zipped
            |> List.map (fun (x: int, y: int) -> string x + ", " + string y)
            |> S.concat "; " = "10, 20; 11, 21; 12, 22")

    assert (l |> eq [])
    assert (r |> eq [ 23; 24 ])

  | _ -> assert false

let private testSort (gen: int -> int list) =
  assert ([ 3; 1; 4; 1; 5; 9 ]
          |> List.sortWith compare
          |> eq [ 1; 1; 3; 4; 5; 9 ])

  assert ([ 3; 1; 4; 1; 5; 9 ]
          |> List.sortUniqueWith compare
          |> eq [ 1; 3; 4; 5; 9 ])

let private testEquals (gen: int -> int list) =
  let intNil: int list = []
  let intEquals (x: int) y = x = y

  assert (gen 3 |> List.equals intEquals (gen 3))
  assert (intNil |> List.equals intEquals intNil)
  assert ([ 2 ] |> List.equals intEquals [ 3 ] |> not)

let private testCompare (gen: int -> int list) =
  let intNil: int list = []
  let intCompare: int -> _ -> _ = compare

  assert (gen 3 |> List.compare compare (gen 3) = 0)
  assert (intNil |> List.compare compare intNil = 0)

  assert (List.compare compare intNil (gen 1) < 0)
  assert (List.compare compare (gen 1) intNil > 0)
  assert (List.compare compare (gen 2) (gen 3) < 0)
  assert (List.compare compare [ 1 ] (gen 3) > 0)

let private testDebug (gen: int -> int list) =
  let xs: int list = []

  assert (gen 3 |> List.debug string = "[ 0; 1; 2 ]")
  assert ([] |> List.debug id = "[]")

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
  testDrop gen
  testZipEx gen
  testEquals gen
  testCompare gen
  testDebug gen
  0
