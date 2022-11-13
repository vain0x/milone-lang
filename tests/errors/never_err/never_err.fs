module rec never_err.Program

type private MyRecord = { F: char }

let private crash () : never = exit 1

// ===============================================

// Never works as a generic value only in particular places.
// In other places, the never type is just single type that is different than other types.

// Never expression can't pass in a function argument of another type.
let private testArg () =
  let f (_: bool) = ()

  // Error: Type mismatch never <> bool
  f (crash ())

// Never expression can't assign to field of another type.
let private testFieldInit () : MyRecord =
  // Error: Type mismatch never <> char
  { F = crash () }

// Never expression can't be passed in a variant constructor that expects another type.
let private testWrap () : string option =
  // Error: Type mismatch never <> string
  Some(crash ())

// Never expression can't be used as an operand that expects another type.
let private testOperand () : int =
  // Error: Type mismatch never <> int
  1 + crash ()

let main _ =
  testArg ()
  testFieldInit () |> ignore
  testWrap () |> ignore
  testOperand () |> ignore
  1
