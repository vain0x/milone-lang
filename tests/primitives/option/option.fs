module rec option.Program

// Option types.

let basicSomeCase () =
  match Some 1 with
  | None -> assert false

  | Some 1 -> ()

  | _ -> assert false

let basicNoneCase () =
  match None with
  | Some "a" -> assert false

  | None -> ()

  | _ -> assert false

// Just testing MIR's match-to-switch conversion,
// which is temporary necessary until pattern matching compilation is done.
let basicMatchCase () =
  match Some() with
  | None -> assert false
  | _ -> ()

let main _ =
  basicSomeCase ()
  basicNoneCase ()
  basicMatchCase ()
  0
