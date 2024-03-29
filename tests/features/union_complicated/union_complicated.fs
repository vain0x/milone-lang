// Complicated test of discriminated union types.
module rec union_complicated.Program

// A union that contains the list of self.
type Node =
  | Leaf of int
  | Node of Node list

// Unions that mutually recursive via lists, tuples and functions.
type First = First of (((First * Second) list -> First list * Second list))

type Second = Second of (((First * Second) list -> First list * Second list))

type Third =
  | Leaf3
  | Node3 of (int * Third) list

let main _ =
  match
    Node [ Node [ Leaf 1; Leaf 2 ]
           Node []
           Node [ Leaf 3 ] ]
    with
  | Node (Node (Leaf x :: Leaf y :: []) :: Node [] :: Node (Leaf z :: []) :: []) -> assert (x = 1 && y = 2 && z = 3)
  | _ -> assert false

  let first, second =
    let f (_: (First * Second) list) : (First list * Second list) = [], []
    First f, Second f

  match [ 0, Leaf3 ] with
  | [ 0, Leaf3 ] -> ()
  | _ -> assert false

  0
