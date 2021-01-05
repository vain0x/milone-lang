module rec module_synonym.Program

// S is defined as alias of `module_synonym.sub`
// and `sub` is added to the project.
module S = module_synonym.sub

let main _ =
  assert (S.inc 2 = 3)
  0
