module rec record_private_fields.Program

// Visibility modifiers parse (but are unimplemented.)

type Id = private { Inner: int }

type AbstractStructure =
  private
    { X1: int
      X2: int
      X3: int
      X4: int
      X5: int }

let main _ = 0
