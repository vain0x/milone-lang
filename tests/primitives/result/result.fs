module rec result.Program

// Result type.

let private unexpected result =
  match result with
  | Ok value -> printfn "Ok(%d)" value
  | Error e -> printfn "Error(%s)" e

  assert false
  exit 1

let private unwrapOk result =
  match result with
  | Ok value -> value
  | _ -> unexpected result

let private unwrapError result =
  match result with
  | Error e -> e
  | _ -> unexpected result

let private testBind () =
  let divBy2 (n: int) =
    if n % 2 = 0 then
      Ok(n / 2)
    else
      Error "Odd"

  assert (Ok 2 |> Result.bind divBy2 |> unwrapOk = 1)
  assert (Ok 3 |> Result.bind divBy2 |> unwrapError = "Odd")
  assert (Error "Bad" |> Result.bind divBy2 |> unwrapError = "Bad")

let private testMap () =
  let inc (n: int) = n + 1

  assert (Ok 2 |> Result.map inc |> unwrapOk = 3)
  assert (Error "Bad" |> Result.map inc |> unwrapError = "Bad")

let private testMapError () =
  let bang (s: string) = s + "!"

  assert (Ok 2 |> Result.mapError bang |> unwrapOk = 2)
  assert (Error "Bad" |> Result.mapError bang |> unwrapError = "Bad!")

let main _ =
  testBind ()
  testMap ()
  testMapError ()
  0
