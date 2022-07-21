module rec union_generic_newtype_issue.Program

// Repro. There was an issue that when type argument of generic union is a newtype
// it was not unwrapped and generated code was inconsistent.

type private MyOption<'T> =
  | MyNone
  | MySome of 'T

type private Newtype = Newtype of int * int

let private f () = MySome(Newtype(1, 0))

let main _ =
  match f () with
  | MySome _ -> ()
  | MyNone _ -> assert false

  0
