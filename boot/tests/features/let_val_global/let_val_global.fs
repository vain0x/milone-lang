let success = 0

let f () = success

let g () = f ()

let main _ =
  g ()
