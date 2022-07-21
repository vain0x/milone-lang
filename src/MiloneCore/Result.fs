module rec MiloneCore.Result

type Result<'T, 'E> =
  | Error of 'E
  | Ok of 'T

let bind binder result =
  match result with
  | Ok value -> binder value
  | Error e -> Error e

let map mapping result =
  match result with
  | Ok value -> Ok(mapping value)
  | Error e -> Error e

let mapError mapping result =
  match result with
  | Ok value -> Ok value
  | Error e -> Error(mapping e)
