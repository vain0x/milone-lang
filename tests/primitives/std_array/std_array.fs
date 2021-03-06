module rec std_array.Program

module A = MiloneStd.StdArray

let get (i: int) (array: A.Array<_>) =
  match A.tryItem i array with
  | Some it -> it
  | None ->
      printfn "out of range: i=%d len=%d" i (A.length array)
      assert false
      exit 1

let initTest () =
  let emptyArray = A.init 0 (fun (_: int) -> assert false)
  assert (A.length emptyArray = 0)

  let a369 = A.init 3 (fun n -> (n + 1) * 3)
  assert (A.length a369 = 3)
  assert (get 0 a369 = 3)
  assert (get 1 a369 = 6)
  assert (get 2 a369 = 9)

let rangeTest () =
  let a012 = A.range 3

  assert (A.length a012 = 3)
  assert (get 0 a012 = 0)
  assert (get 1 a012 = 1)
  assert (get 2 a012 = 2)

let tryItemTest () =
  let a012 = A.range 3

  let bad = -127

  let at (i: int) (array: A.Array<_>) =
    match A.tryItem i array with
    | Some it -> it
    | None -> bad

  assert (at (-1) a012 = bad)
  assert (at 0 a012 = 0)
  assert (at 2 a012 = 2)
  assert (at 3 a012 = bad)

  let emptyArray = A.empty ()
  assert (at 0 emptyArray = bad)

let sliceTest () =
  let ten = A.range 10

  let three = A.slice 1 4 ten
  assert (A.length three = 3)
  assert (get 0 three = 1)
  assert (get 2 three = 3)

  // starts from 0
  let behind = A.slice (-1) 2 ten
  assert (A.length behind = 2)
  assert (get 1 behind = 1)

  // ends until 10
  let beyond = A.slice 7 11 ten
  assert (A.length beyond = 3)
  assert (get 0 beyond = 7)
  assert (get 2 beyond = 9)

let unconsTest () =
  let a123 = A.init 3 (fun (n: int) -> n + 1)

  match A.uncons a123 with
  | None -> assert false
  | Some (n1, a23) ->
      assert (n1 = 1)
      assert (A.length a23 = 2)

      match A.uncons (A.skip 1 a23) with
      | None -> assert false
      | Some (n3, empty) ->
          assert (n3 = 3)
          assert (A.length empty = 0)

          match A.uncons empty with
          | None -> ()
          | Some _ -> assert false

let mapTest () =
  let mapped =
    A.mapi (fun i n -> i * 10 + n) (A.range 3)

  assert (A.length mapped = 3)
  assert (get 0 mapped = 0)
  assert (get 1 mapped = 11)
  assert (get 2 mapped = 22)

let chooseTest () =
  let chosen =
    A.choose (fun n -> if n % 2 = 0 then Some(n * 2) else None) (A.range 6)

  assert (A.length chosen = 3)
  assert (get 0 chosen = 0)
  assert (get 1 chosen = 4)
  assert (get 2 chosen = 8)

  let empty =
    A.choose (fun (_: int) -> None: int option) (A.range 3)

  assert (A.length empty = 0)

let foldTest () =
  let sum =
    A.fold (fun state i -> state * 10 + (i + 1)) 0 (A.range 3)

  assert (sum = 123)

// let scanTest () =
//   let states =
//     A.scan (fun state i -> state * 10 + (i + 1)) 0 (A.range 3)

//   assert (A.length states = 3)
//   assert (get 0 states = 1)
//   assert (get 1 states = 12)
//   assert (get 2 states = 123)

let ofListTest () =
  let ol = A.ofList [ 2; 3; 5 ]
  assert (A.length ol = 3)
  assert (get 0 ol = 2)
  assert (get 1 ol = 3)
  assert (get 2 ol = 5)

let toListTest () =
  let tl = A.toList (A.range 3)

  match tl with
  | [ n0; n1; n2 ] ->
      assert (n0 = 0)
      assert (n1 = 1)
      assert (n2 = 2)

  | _ -> ()

let main _ =
  initTest ()
  rangeTest ()
  tryItemTest ()
  sliceTest ()
  unconsTest ()
  mapTest ()
  chooseTest ()
  foldTest ()
  // scanTest ()
  ofListTest ()
  toListTest ()
  0
