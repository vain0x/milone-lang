module rec pat_variant_fun_without_payload_err.Program

// Variant that has payload must be occur as pattern with payload pattern.

type IntWrapper = IntWrapper of int

let someString (value: string) = Some value

let wrapInt (value: int) = IntWrapper value

let main _ =
  match someString with
  | Some -> ()
  | _ -> assert false

  match wrapInt with
  | IntWrapper -> ()
  | _ -> assert false

  assert false
  0
