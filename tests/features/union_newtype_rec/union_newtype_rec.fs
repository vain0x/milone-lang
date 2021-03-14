module rec union_newtype_rec.Program

/// Self-recursive newtype variant.
type MyList = MyList of int * MyList option

let main _ =
  let first = MyList(0, None)

  let myCons head tail = MyList(head, Some tail)

  let second = myCons 1 first

  match first with
  | MyList (0, None) -> ()
  | _ -> assert false

  match second with
  | MyList (_, Some (MyList (value, _))) -> assert (value = 0)
  | _ -> assert false

  0
