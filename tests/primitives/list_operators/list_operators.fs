module rec list_cons.Program

// List nil constant ([]), cons operator (::), and list literals.

let nilTest () =
  let nil: int list = []

  match nil with
  | [] -> ()
  | _ -> assert false

let cons1Test () =
  let xs: int list = 1 :: []

  match xs with
  | x :: [] -> assert (x = 1)
  | _ -> assert false

let cons2Test () =
  let ys = 2 :: 3 :: []

  match ys with
  | y2 :: y3 :: [] -> assert (y2 = 2 && y3 = 3)
  | _ -> assert false

let literalTest () =
  let zs = [ 2; 3; 5; 7 ]

  match zs with
  | [ z2; z3; z5; z7 ] ->
      assert (z2 = 2)
      assert (z3 = 3)
      assert (z5 = 5)
      assert (z7 = 7)

  | _ -> assert false

let main _ =
  nilTest ()
  cons1Test ()
  cons2Test ()
  literalTest ()
  0
