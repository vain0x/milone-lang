module rec ty_synonym_undefined_ty_var_err.Program

// Error if synonym definition contains undefined type variables.

type Synonym<'T> = 'T * 'U

let main _ =
  let s: Synonym<_> = 2, "x"
  0
