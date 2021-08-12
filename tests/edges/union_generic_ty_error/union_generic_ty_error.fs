module rec union_generic_ty_error.Program

type private MyOption<'T> =
  | MyNone
  | MySome of 'T

let main _ =
  match MySome 42 with
  | MyNone -> assert false
  | MySome (s: string) -> assert (s <> "")

  0
