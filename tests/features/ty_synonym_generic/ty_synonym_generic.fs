module rec ty_synonym_generic.Program

type Stack<'T> = 'T list

let newStack (): Stack<_> = []

let main _ =
  let _stack = 1 :: newStack ()
  0
