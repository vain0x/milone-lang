let main _ =
  match () with
  | () -> ()

  match true with
  | false -> exit 1
  | true -> ()
  | _ -> exit 1

  match 1 with
  | 0 -> exit 1
  | 1 -> ()
  | _ -> exit 1

  match 'a' with
  | 'A' -> exit 1
  | 'a' -> ()
  | _ -> exit 1

  match "a" with
  | "an" -> exit 1
  | "a" -> ()
  | _ -> exit 1

  0