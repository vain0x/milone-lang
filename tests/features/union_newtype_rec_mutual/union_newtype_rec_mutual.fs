module rec union_newtype_rec_mutual.Program

// Mutually recursive newtype variants.

type Odd = Odd of int * Even option
type Even = Even of string * Odd option

let main _ =
  let one = Odd(1, None)
  let two = Even("two", Some one)
  let three = Odd(3, Some two)
  let four = Even("four", Some three)

  match four with
  | Even (s4, Some (Odd (n3, Some (Even (s2, Some (Odd (n1, None))))))) ->
      assert (n1 = 1)
      assert (s2 = "two")
      assert (n3 = 3)
      assert (s4 = "four")

  | _ -> assert false

  0
