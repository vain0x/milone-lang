module rec nav_ty.sub

type Node =
  | Leaf of int
  | Node of Node * Node
