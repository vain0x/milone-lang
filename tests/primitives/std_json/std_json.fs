module rec std_json.Program

open Std.StdJson

module C = Std.StdChar
module S = Std.StdString

let private success title (text: string) expected =
  match Json.parsePartial 0 text.Length text with
  | ParseOk (value, i) when text |> S.skip i |> S.trim = "" ->
    let actual = Json.dump value

    if actual = expected then
      printfn "OK: %s" title
    else
      printfn "ERROR: %s\nactual: %s\nexpected: %s" title actual expected

  | ParseOk (value, i) -> printfn "ERROR: %s Parse stopped at %d\nvalue: %s" title i (Json.dump value)

  | ParseErr (i, kind) -> printfn "ERROR: %s Parse error at %d" title i

let private testParseSuccess () =
  success "spaces" "  \n  42  \n\n  " "42"
  success "empty array" "[]" "[]"
  success "constants" "[ null, true, false ]" "[null,true,false]"

  success "string" "\"hello\"" "\"hello\""
  success "string (empty)" "\"\"" "\"\""
  success "string (escape)" "\"\\\\ \\\" \\t \\r\\n \\u732b\"" "\"\\\\ \\\" \\t \\r\\n 猫\""

  success "int" "42" "42"
  success "int (negative)" "-1" "-1"
  success "int array" "[0, 1, 2]" "[0,1,2]"

  success "float" "3.14" "3.14"
  success "float (starts with point)" ".1" "0.1"
  success "float (exponential)" "1e9" "1000000000"
  success "float (exponential of minus)" "1e-3" "0.001"
  success "float (full)" "0.42e+5" "42000"
  success "float with exp" "6.02e-23" "6.02e-23"

  success "empty object" "{}" "{}"
  success "singleton object" """{ "a": null }""" """{"a":null}"""
  success "object" """{ "t": true, "f": false }""" """{"t":true,"f":false}"""

  success
    "nested object"
    """
      {
        "animals": {
          "dogs": ["poodle", "akita"],
          "cats": ["persian", "bengal"]
        },
        "plants": ["cherry", "maple"]
      }
    """
    """{"animals":{"dogs":["poodle","akita"],"cats":["persian","bengal"]},"plants":["cherry","maple"]}"""

let private testDump () =
  let f title input expected =
    let actual = Json.dump input

    if actual = expected then
      printfn "OK: %s" title
    else
      printfn "ERROR: %s\nactual: %s\nexpected: %s" title actual expected
      assert false

  f "null" JNull "null"
  f "true" (JBoolean true) "true"
  f "false" (JBoolean false) "false"

  f "string (empty)" (JString "") "\"\""
  f "string (escape)" (JString "\"\\ \t \r\n") "\"\\\"\\\\ \\t \\r\\n\""
  f "string (control)" (JString "\x00\x08\x0c\x1f") "\"\\u0000\\b\\f\\u001f\""

  let jInt (n: int) = JNumber(float n)
  f "float (zero)" (jInt 0) "0"
  f "float (positive int)" (jInt 42) "42"
  f "float (negative int)" (jInt (-23)) "-23"
  f "float (positive float)" (JNumber 3.14) "3.14"
  f "float (negative float)" (JNumber(-23.456)) "-23.456"
  f "float (int+eps)" (JNumber(2.0 + 1e-15)) "2"
  f "float (int-eps)" (JNumber(3.0 - 1e-15)) "3"
  f "float (too small)" (JNumber(float "6.02e-23")) "6.02e-23"
  f "float (too large)" (JNumber(float "6.02e+23")) "6.02e+23"

  f "array (empty)" (JArray []) "[]"

  f
    "array"
    (JArray [ JNull
              JBoolean true
              JBoolean false ])
    "[null,true,false]"

  f "object (empty)" (JObject []) "{}"

  f
    "object"
    (JObject [ "t", JBoolean true
               "f", JBoolean false ])
    """{"t":true,"f":false}"""

let private main _ =
  testParseSuccess ()
  testDump ()
  0
