module rec nav_nested.Program

// Nav patterns and expressions can be nested.

open nav_nested.sub

let main _ =
  let text: sub.SubRecord = { Text = "Hello" }
  assert (text.Text.Length = 5)

  match sub.SubUnion.SubUnion 42 with
  | sub.SubUnion.SubUnion value -> assert (value = 42)
  0
