module rec record_with.Program

type Person = { Name: string; Age: int }

let main _ =
  let john: Person = { Name = "John Doe"; Age = 16 }
  let jane: Person = { john with Name = "Jane Doe" }

  assert (john.Name = "John Doe")
  assert (jane.Name = "Jane Doe")
  assert (jane.Age = 16)

  let john: Person = { john with Age = john.Age + 1 }
  assert (john.Age = 17)
  0
