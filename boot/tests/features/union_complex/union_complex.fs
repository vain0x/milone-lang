// Complex test cases for union types.

// A union that contains the list of self.
type Node =
  | Leaf
    of int
  | Node
    of Node list

let main _ =
  match Node [Node [Leaf 1; Leaf 2]; Node []; Node [Leaf 3]] with
  | Node (Node (Leaf x :: Leaf y :: []) :: Node [] :: Node (Leaf z :: []) :: []) ->
    assert (x = 1 && y = 2 && z = 3)
  | _ ->
    assert false

  0
