module rec synonym_arity_err.Program

// Use of generic type synonyms with wrong arity should be reported as error.
// FIXME: arity mismatch causes compile crashes for now, so cannot be tested.

type Stack<'T> = 'T list

// let f (_stack: Stack<int, string>) = ()

let main _ =
  // let _stack: Stack<int, int> = []
  0
