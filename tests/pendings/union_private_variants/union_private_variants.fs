module rec union_private_variants.Program

// Visibility modifiers parse (but are unimplemented.)

// Note `type ID = private ID` doesn't parse in F#.

type Unknown = private | Unknown

type Id = private Id of int

type AbstractEvent =
  private
  | E1 of int
  | E2 of int

let main _ = 0
