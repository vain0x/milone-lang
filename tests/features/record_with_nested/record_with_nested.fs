module rec record_with_nested.Program

type Date = { Year: int; Month: int; Date: int }

type Person =
  { Name: string
    Age: int
    Birthday: Date }

let newPerson (): Person =
  { Name = "Jane Doe"
    Age = 16
    Birthday = { Year = 2007; Month = 8; Date = 31 } }

let main _ =
  let john = { newPerson () with Name = "John Doe" }

  let name = john.Name
  assert (name.Length = 8)
  0
