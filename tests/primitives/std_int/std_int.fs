module rec std_int.Program

module I = MiloneStd.StdInt

let tryParseTest () =
  let parseOk (s: string) =
    match I.tryParse s with
    | Some value -> value

    | None ->
        printfn "should parse: %s" s
        assert false
        0

  let parseError (s: string) =
    match I.tryParse s with
    | None -> true
    | Some value ->
        printfn "should not parse: %s -> %d" s value
        false

  assert (parseOk "0" = 0)
  assert (parseOk "000" = 0)
  assert (parseOk "0010" = 10)
  assert (parseOk "42" = 42)
  assert (parseOk " 	            42             	 " = 42)
  assert (parseOk "+81" = 81)
  assert (parseOk "-1" + 1 = 0)
  assert (parseOk "2147483647" = 2147483647)
  assert (parseOk "-2147483648" + 1 = -2147483647)
  assert (parseOk "123456789123456789".[0..4] = 12345)

  assert (parseError "")
  assert (parseError "   ")
  assert (parseError "\x00 1")
  assert (parseError "+ 81")
  assert (parseError "2147483648")
  assert (parseError "-2147483649")
  assert (parseError "0x0")
  assert (parseError "0.0")
  assert (parseError ".0")
  assert (parseError "1e9")

let main _ =
  tryParseTest ()
  0
