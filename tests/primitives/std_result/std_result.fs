module rec std_result.Program

open Std.StdResult

module S = Std.StdString

let private ok: Result<int, string> = Ok 42
let private error: Result<int, string> = Error "Bad"

let private unwrapOk result =
  match result with
  | Ok value -> value

  | Error e ->
    printfn "Error(%s)" e
    assert false
    exit 1

let private unwrapError result =
  match result with
  | Ok value ->
    printfn "Ok(%d)" value
    assert false
    exit 1

  | Error e -> e

let private testVariantWiseFunctions () =
  assert (ok |> Result.isOk)
  assert (error |> Result.isOk |> not)
  assert (ok |> Result.isError |> not)
  assert (error |> Result.isError)

  assert (ok |> Result.asOk |> Option.isSome)
  assert (error |> Result.asOk |> Option.isNone)
  assert (ok |> Result.asError |> Option.isNone)
  assert (error |> Result.asError |> Option.isSome)

let private testDefaultValue () =
  assert (ok |> Result.defaultValue 1 = 42)
  assert (error |> Result.defaultValue 1 = 1)

  assert (ok
          |> Result.defaultWith (fun _ ->
            assert false
            1) = 42)

  assert (error
          |> Result.defaultWith (fun e ->
            assert (e = "Bad")
            1) = 1)

let private testOrElse () =
  assert (ok |> Result.orElse error |> unwrapOk = 42)
  assert (error |> Result.orElse ok |> unwrapOk = 42)

  assert (ok
          |> Result.orElseWith (fun _ ->
            assert false
            error)
          |> unwrapOk = 42)

  assert (error
          |> Result.orElseWith (fun e ->
            assert (e = "Bad")
            ok)
          |> unwrapOk = 42)

let private testEquals () =
  let equals =
    let intEquals = fun (x: int) y -> x = y
    let stringEquals = fun (x: string) y -> x = y
    Result.equals intEquals stringEquals

  assert (equals ok error |> not)
  assert (equals ok ok)
  assert (equals error error)
  assert (equals (Ok 2) (Ok 3) |> not)
  assert (equals (Error "A") (Error "B") |> not)

let private testCompare () =
  let c: Result<int, string> -> _ -> _ = Result.compare compare compare

  assert (c ok error > 0)
  assert (c error ok < 0)
  assert (c ok ok = 0)
  assert (c error error = 0)
  assert (c (Ok 2) (Ok 3) < 0)
  assert (c (Error "A") (Error "B") < 0)

let private testDebug () =
  let d: Result<int, string> -> _ = Result.debug string string

  assert (d ok = "Ok(42)")
  assert (d error = "Error(Bad)")

let private testChoose () =
  let okList, errorList =
    [ 0; 1; 2; 3; 4 ]
    |> ResultList.choose (fun x ->
      if x % 2 = 0 then
        Ok((x / 2) * 10)
      else
        Error(string x + " is odd"))

  assert (okList |> List.map string |> S.concat "; " = "0; 10; 20")
  assert (errorList |> S.concat "; " = "1 is odd; 3 is odd")

let main _ =
  testVariantWiseFunctions ()
  testDefaultValue ()
  testOrElse ()
  testEquals ()
  testCompare ()
  testDebug ()
  testChoose ()
  0
