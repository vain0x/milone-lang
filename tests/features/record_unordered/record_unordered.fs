module rec record_unordered.Program

// Record creation with shuffled fields.

type Person = { Name: string; Age: int }

let main _ =
  let _john : Person = { Name = "John Doe"; Age = 16 }
  let _jane : Person = { Age = 18; Name = "Jane Doe" }
  0
