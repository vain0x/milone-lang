module rec nav_module_ty.Program

// You can refer to types defined in another module with dot notation (nav).

open nav_module_ty.nav_module_ty_sub

// Shadow imported symbols.
// let Leaf = ()
// let Node = ()

// FIXME: dot notation in type is not parsed correctly
// Define abbreviation of type in another module.
// type Node = unit
type MyNode = nav_module_ty_sub.Node

let main _ =
  let leaf n = nav_module_ty_sub.Leaf n
  let node l r = nav_module_ty_sub.Node(l, r)

  let t = node (leaf 2) (node (leaf 3) (leaf 5))

  match t with
  // FIXME: abbreviation of union doesn't work as namespace of variants
  // | MyNode.Leaf _ -> ...

  | Node (Leaf x, _) -> assert (x = 2)
  | _ -> assert false

  0
