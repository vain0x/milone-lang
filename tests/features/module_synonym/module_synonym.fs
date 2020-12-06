module rec module_synonym.Program

open module_synonym.sub

module S = module_synonym.sub

let main _ =
  assert (S.inc 2 = 3)
  0
