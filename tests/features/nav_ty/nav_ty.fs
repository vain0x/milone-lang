module rec nav_ty.Program

// You can refer to types defined in another module with dot notation (nav).

open nav_ty.sub

// Shadow imported symbols.
// let Leaf = ()
// let Node = ()

type MyNode = sub.Node

let main _ =
  let leaf n = sub.Leaf n
  let node l r = sub.Node(l, r)

  let t = node (leaf 2) (node (leaf 3) (leaf 5))

  match t with
  // FIXME: abbreviation of union doesn't work as namespace of variants
  // | MyNode.Leaf _ -> ...

  | Node (Leaf x, _) -> assert (x = 2)
  | _ -> assert false

  0
