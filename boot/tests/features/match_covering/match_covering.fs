type Node =
  | Leaf
  | Node of Node * Node

let main _ =
  match false with
  | false ->
    ()
  | true ->
    assert false

  match false, true with
  | false, false ->
    assert false

  | false, true ->
    ()

  | true, false ->
    assert false
  
  | true, true ->
    assert false

  match [1; 2] with
  | [] ->
    ()
  | _ :: _ ->
    ()

  match Leaf with
  | Leaf ->
    ()

  | Node (Leaf, Leaf) ->
    assert false

  | Node (Node _, Leaf) ->
    assert false

  | Node (Leaf, Node _) ->
    assert false

  | Node (Node _, Node _) ->
    assert false

  0
