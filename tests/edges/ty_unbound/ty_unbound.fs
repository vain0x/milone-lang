module rec ty_unbound.Program

// Unbound type variable should be degenerated.

let assertIsEmpty xs = assert (List.isEmpty xs)

let main _ =
  // The item type of list is unbound, so `assertIsEmpty` used here is polymorphic
  // after type inference.
  assertIsEmpty []
  0
