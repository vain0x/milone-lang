let main _ =
  match () with
  | () -> ()

  match true with
  | false -> assert false
  | true -> ()

  match 1 with
  | 0 -> assert false
  | 1 -> ()
  | _ -> assert false

  match 'a' with
  | 'A' -> assert false
  | 'a' -> ()
  | _ -> assert false

  match "a" with
  | "an" -> assert false
  | "a" -> ()
  | _ -> assert false

  0
