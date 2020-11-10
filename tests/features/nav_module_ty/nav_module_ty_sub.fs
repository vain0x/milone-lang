module rec nav_module_ty.nav_module_ty_sub

type Node =
  | Leaf of int
  | Node of Node * Node
