module rec match_nested_nonbinding.Program

// Invalid code was generated in the case
// for nested, non-binding matching on union.

type MyBool =
  | MyFalse
  | MyTrue

type MyOption =
  | MySome of MyBool
  | MyNone

let main _ =
  match MySome MyTrue with
  | MySome MyTrue -> ()
  | MySome _ -> assert false
  | MyNone -> assert false

  0
