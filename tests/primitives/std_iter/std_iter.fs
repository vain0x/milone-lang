module rec std_iter.Program

open Std.StdIter

module S = Std.StdString

let private bang () : 'T =
  exit 1
  bang ()

/// Generates integers from 0 to n (exclusive).
let private gen (n: int) : Iter<int> = Iter.range 0 n

let private cat (xs: Iter<int>) : int = Iter.fold (fun n x -> n * 10 + x) 0 xs

let private testNext () =
  let xs: Iter<int> = Iter.range 1 4
  let xs1 = xs

  let xs =
    match Iter.next xs with
    | None -> bang (assert false)

    | Some (x, xs) ->
      assert (x = 1)
      xs

  let xs =
    match Iter.next xs with
    | None -> bang (assert false)

    | Some (x, xs) ->
      assert (x = 2)
      xs

  let xs =
    match Iter.next xs with
    | None -> bang (assert false)

    | Some (x, xs) ->
      assert (x = 3)
      xs

  match Iter.next xs with
  | None -> ()
  | Some _ -> bang (assert false)

  // fused
  match Iter.next xs with
  | None -> ()
  | Some _ -> bang (assert false)

  // it's stateless
  match Iter.next xs1 with
  | None -> bang (assert false)

  | Some (x, xs) -> assert (x = 1)

let private testEmpty () =
  let xs: Iter<string> = Iter.empty ()

  assert (Option.isNone (Iter.next xs))

let private testSingleton () =
  let xs = Iter.singleton "foo"

  match Iter.next xs with
  | None -> assert false
  | Some (x, xs) ->
    assert (x = "foo")

    match Iter.next xs with
    | None -> ()
    | Some _ -> assert false

let private testInit () =
  assert (Iter.init 5 (fun i -> i + 1) |> cat = 12345)
  ()

let private testReplicate () =
  assert (Iter.replicate 0 "x" |> Iter.isEmpty)

  assert (Iter.replicate 2 "x"
          |> Iter.toList
          |> S.concat "," = "x,x")

let private testUnfold () =
  let n =
    Iter.unfold
      (fun i ->
        if i <= 3 then
          Some(i * i, i + 1)
        else
          None)
      1
    |> cat

  assert (n = 149)

let private testMap () =
  assert (gen 0
          |> Iter.map (fun _ -> bang (assert false))
          |> cat = 0)

  assert (gen 3 |> Iter.map (fun x -> x + 1) |> cat = 123)

  assert (gen 3
          |> Iter.map (fun x -> x * 2)
          |> Iter.map (fun x -> x + 1)
          |> cat = 135)

let private testChoose () =
  let n =
    gen 6
    |> Iter.choose (fun n -> if n % 2 = 0 then Some(n * 2) else None)
    |> cat

  assert (n = 48)

let private testCollect () =
  let n =
    gen 4
    |> Iter.collect (fun n -> Iter.replicate n n)
    |> cat

  assert (n = 122333)

let private testScan () =
  let s =
    gen 4
    |> Iter.scan (fun n x -> n * 10 + x) 0
    |> Iter.map string
    |> Iter.toList
    |> S.concat ","

  assert (s = "0,1,12,123")

let private testFilter () =
  let n =
    gen 11 |> Iter.filter (fun n -> n % 2 = 1) |> cat

  assert (n = 13579)

let private testMapI () =
  let s =
    gen 3
    |> Iter.map (fun (i: int) -> string (i + 1))
    |> Iter.mapi (fun (i: int) x -> string i + ":" + x)
    |> Iter.toList
    |> S.concat ","

  assert (s = "0:1,1:2,2:3")

let private testIndexed () =
  let s =
    gen 3
    |> Iter.map (fun (i: int) -> string (i + 1))
    |> Iter.indexed
    |> Iter.map (fun (i: int, x) -> string i + ":" + x)
    |> Iter.toList
    |> S.concat ","

  assert (s = "0:1,1:2,2:3")

let private testAppend () =
  let s =
    Iter.append (gen 3) (gen 2)
    |> Iter.map string
    |> Iter.toList
    |> S.concat ","

  assert (s = "0,1,2,0,1")

let private testIsEmpty () =
  assert (gen 0 |> Iter.isEmpty)
  assert (gen 1 |> Iter.isEmpty |> not)
  assert (gen 2 |> Iter.isEmpty |> not)

let private testFold () =
  let xs: Iter<int> = Iter.range 1 4
  assert (cat xs = 123)

let private testForall () =
  assert (gen 3
          |> Iter.forall (fun (i: int) -> 0 <= i && i < 3))

  assert (gen 3
          |> Iter.forall (fun (i: int) ->
            assert (i <= 1) // Loop stops at i = 1.
            i <> 1)
          |> not)

let private testExists () =
  assert (gen 3
          |> Iter.exists (fun (i: int) ->
            assert (i <= 1) // Loop stops at i = 1.
            i = 1))

let private testTryPick () =
  match gen 3
        |> Iter.tryPick (fun i -> if i = 1 then Some "one" else None)
    with
  | Some "one" -> ()
  | _ -> assert false

  match gen 3
        |> Iter.tryPick (fun i ->
          if i = 3 then
            bang (assert false)
          else
            None)
    with
  | Some _ -> assert false
  | _ -> ()

let private testOfOption () =
  assert (cat (Iter.ofOption None) = 0)
  assert (cat (Iter.ofOption (Some 2)) = 2)

let private testOfList () =
  let xs: Iter<int> = Iter.ofList [ 2; 3; 5 ]
  assert (cat xs = 235)

  let ys = Iter.ofList [ 2 ]
  assert (cat ys = 2)

  let zs = Iter.ofList []
  assert (cat zs = 0)

let private testToList () =
  let xs = Iter.ofList [ 2; 3; 5 ] |> Iter.toList

  assert (List.fold (fun n x -> n * 10 + x) 0 xs = 235)

  let ys =
    Iter.ofList [ "x"; "y"; "z" ] |> Iter.toList

  assert (List.fold (fun (x: string) y -> x + y) "" ys = "xyz")

let main _ =
  testNext ()
  testEmpty ()
  testSingleton ()
  testInit ()
  testReplicate ()
  testUnfold ()
  testMap ()
  testChoose ()
  testCollect ()
  testScan ()
  testFilter ()
  testMapI ()
  testIndexed ()
  testAppend ()
  testIsEmpty ()
  testFold ()
  testForall ()
  testExists ()
  testTryPick ()
  testOfOption ()
  testOfList ()
  testToList ()
  0
