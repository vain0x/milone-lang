module rec ty_synonym_cyclic_err.Program

// Cyclic type synonym is forbidden.

type Hungry = unit -> Hungry

type Even = int * Odd

type Odd = string * Even

let main _ =
  let hungry (f: Hungry) = f ()

  assert false
  0
