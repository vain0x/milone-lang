module rec record_with_nested.Program

// FIXME: Nested record is unimplemented.
// type Date = { Year: int; Month: int; Date: int }
type Date = int * int * int

type Person =
  { Name: string
    Age: int
    Birthday: Date }

let newPerson (): Person =
  { Name = "Jane Doe"
    Age = 16
    // Birthday = { Year = 2007; Month = 8; Date = 31 } }
    Birthday = 2007, 8, 31 }

let main _ =
  let john = { newPerson () with Name = "John Doe" }

  let name = john.Name
  assert (name.Length = 8)
  0
