module rec LetGlobalLazyInit

let f () =
  box 1

let boxedValue = box 1

let main _ =
  assert (f () |> unbox = 1)
  0
