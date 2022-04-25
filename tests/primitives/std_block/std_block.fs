module rec std_block.Program

open Std.Block

module B = Std.Block.Block

let private get (i: int) (block: Block<_>) =
  match B.tryItem i block with
  | Some it -> it
  | None ->
    printfn "out of range: i=%d len=%d" i (B.length block)
    assert false
    exit 1

let private initTest () =
  let emptyBlock = B.init 0 (fun (_: int) -> assert false)
  assert (B.length emptyBlock = 0)

  let b369 = B.init 3 (fun n -> (n + 1) * 3)
  assert (B.length b369 = 3)
  assert (get 0 b369 = 3)
  assert (get 1 b369 = 6)
  assert (get 2 b369 = 9)

let private rangeTest () =
  let b012 = B.range 3

  assert (B.length b012 = 3)
  assert (get 0 b012 = 0)
  assert (get 1 b012 = 1)
  assert (get 2 b012 = 2)

let private tryItemTest () =
  let b012 = B.range 3

  let bad = -127

  let at (i: int) (array: Block<_>) =
    match B.tryItem i array with
    | Some it -> it
    | None -> bad

  assert (at (-1) b012 = bad)
  assert (at 0 b012 = 0)
  assert (at 2 b012 = 2)
  assert (at 3 b012 = bad)

  let emptyArray = B.empty ()
  assert (at 0 emptyArray = bad)

let private sliceTest () =
  let ten = B.range 10

  let three = B.slice 1 4 ten
  assert (B.length three = 3)
  assert (get 0 three = 1)
  assert (get 2 three = 3)

  // starts from 0
  let behind = B.slice (-1) 2 ten
  assert (B.length behind = 2)
  assert (get 1 behind = 1)

  // ends until 10
  let beyond = B.slice 7 11 ten
  assert (B.length beyond = 3)
  assert (get 0 beyond = 7)
  assert (get 2 beyond = 9)

let private unconsTest () =
  let a123 = B.init 3 (fun (n: int) -> n + 1)

  match B.uncons a123 with
  | None -> assert false
  | Some (n1, a23) ->
    assert (n1 = 1)
    assert (B.length a23 = 2)

    match B.uncons (B.skip 1 a23) with
    | None -> assert false
    | Some (n3, empty) ->
      assert (n3 = 3)
      assert (B.length empty = 0)

      match B.uncons empty with
      | None -> ()
      | Some _ -> assert false

let private mapTest () =
  let mapped =
    B.mapi (fun i n -> i * 10 + n) (B.range 3)

  assert (B.length mapped = 3)
  assert (get 0 mapped = 0)
  assert (get 1 mapped = 11)
  assert (get 2 mapped = 22)

let private chooseTest () =
  let chosen =
    B.choose (fun n -> if n % 2 = 0 then Some(n * 2) else None) (B.range 6)

  assert (B.length chosen = 3)
  assert (get 0 chosen = 0)
  assert (get 1 chosen = 4)
  assert (get 2 chosen = 8)

  let empty =
    B.choose (fun (_: int) -> None: int option) (B.range 3)

  assert (B.length empty = 0)

let private foldTest () =
  let sum =
    B.fold (fun state i -> state * 10 + (i + 1)) 0 (B.range 3)

  assert (sum = 123)

// let scanTest () =
//   let states =
//     B.scan (fun state i -> state * 10 + (i + 1)) 0 (B.range 3)

//   assert (B.length states = 3)
//   assert (get 0 states = 1)
//   assert (get 1 states = 12)
//   assert (get 2 states = 123)

let private ofListTest () =
  let ol = B.ofList [ 2; 3; 5 ]
  assert (B.length ol = 3)
  assert (get 0 ol = 2)
  assert (get 1 ol = 3)
  assert (get 2 ol = 5)

let private toListTest () =
  let tl = B.toList (B.range 3)

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
