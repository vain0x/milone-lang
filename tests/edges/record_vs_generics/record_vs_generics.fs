module rec record_vs_generics.Program

// Make sure that record values can be used in generic functions.

type IntWrapper = { Value: int }

let constant value () = value

let main _ =
  let f = constant ({ Value = 42 }: IntWrapper)

  let wrapper = f ()
  assert (wrapper.Value = 42)
  0
