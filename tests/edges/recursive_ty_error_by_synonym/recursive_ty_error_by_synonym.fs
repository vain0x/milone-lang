module rec recursive_ty_error_by_synonym.Program

type Synonym<'T> = 'T

let just (value: 'T) : Synonym<'T> = value

let main _ =
  assert (just 2 = 2)
  0
