module rec std_string.Program

// Tests for MiloneStd.StdString.

module S = MiloneStd.StdString

let unwrap opt =
  match opt with
  | Some value -> value

  | None ->
    printfn "Can't unwrap None."
    exit 1

let isEmptyTest () =
  assert (S.isEmpty "")
  assert (S.isEmpty "\x00" |> not)

let tryItemTest () =
  assert (S.tryItem 0 "" |> Option.isNone)
  assert (S.tryItem (-1) "a" |> Option.isNone)
  assert (S.tryItem 1 "a" |> Option.isNone)
  assert ((S.tryItem 2 "abc" |> unwrap) = 'c')

let startsWithTest () =
  assert (S.startsWith "/bin" "/usr/bin" |> not)
  assert (S.startsWith "/bin" "/bin/ls")
  assert (S.startsWith "" "")

let endsWithTest () =
  assert (S.endsWith "/bin" "/usr/bin")
  assert (S.endsWith "/bin" "/bin/ls" |> not)
  assert (S.endsWith "" "")

let findIndexTest () =
  assert (S.findIndex "ab" "" |> Option.isNone)
  assert (S.findIndex "ab" "cacbc" |> Option.isNone)

  assert ((S.findIndex "ab" "abcc" |> unwrap) = 0)
  assert ((S.findIndex "ab" "ccabccabcc" |> unwrap) = 2)
  assert ((S.findIndex "" "" |> unwrap) = 0)

let findLastIndexTest () =
  assert (S.findLastIndex "ab" "" |> Option.isNone)
  assert (S.findLastIndex "ab" "cacbc" |> Option.isNone)

  assert ((S.findLastIndex "ab" "ccab" |> unwrap) = 2)
  assert ((S.findLastIndex "ab" "ccabccabcc" |> unwrap) = 6)
  assert ((S.findLastIndex "" "" |> unwrap) = 0)

let containsTest () =
  assert (S.contains "ab" "cacbc" |> not)
  assert (S.contains "ab" "ccabccabcc")
  assert (S.contains "" "")

let truncateTest () =
  assert (S.truncate (-1) "ab" = "")
  assert (S.truncate 0 "ab" = "")
  assert (S.truncate 1 "ab" = "a")
  assert (S.truncate 2 "ab" = "ab")
  assert (S.truncate 3 "ab" = "ab")

let skipTest () =
  assert (S.skip (-1) "ab" = "ab")
  assert (S.skip 0 "ab" = "ab")
  assert (S.skip 1 "ab" = "b")
  assert (S.skip 2 "ab" = "")
  assert (S.skip 3 "ab" = "")

let sliceTest () =
  assert (S.slice (-2) (-1) "ab" = "")
  assert (S.slice (-1) 1 "ab" = "a")
  assert (S.slice 0 1 "ab" = "a")
  assert (S.slice 0 2 "ab" = "ab")
  assert (S.slice 0 3 "ab" = "ab")
  assert (S.slice 1 2 "ab" = "b")
  assert (S.slice 1 3 "ab" = "b")
  assert (S.slice 2 3 "ab" = "")

let trimTest () =
  assert (S.trim "  ab  " = "ab")
  assert (S.trimStart "  ab  " = "ab  ")
  assert (S.trimEnd " ab" = " ab")

let replaceTest () =
  assert (S.replace "a" "A" "abaca" = "AbAcA")
  assert (S.replace "xy" "yx" "xyxyx" = "yxyxx")
  assert (S.replace "" "" "as is" = "as is")
  assert (S.replace "aa" "a" "aaaaa" = "aaa")

let private toLowerTest () =
  assert (S.toLower "a To Z 🐧" = "a to z 🐧")
  assert (S.toLower "" = "")

let private toUpperTest () =
  assert (S.toUpper "a To Z 🐧" = "A TO Z 🐧")
  assert (S.toUpper "" = "")

let private cutTest () =
  let run sep s expected =
    let debug (s1, s2, ok: bool) = s1 + ";" + s2 + ";" + string ok
    debug (S.cut sep s) = debug expected

  // Basic.
  assert (run "," "one,two,three" ("one", "two,three", true))
  // Empty separator.
  assert (run "" "foo" ("", "foo", true))
  // Empty elements.
  assert (run "," ",," ("", ",", true))
  // Not separated.
  assert (run "," "foo" ("foo", "", false))
  // Trailing separator.
  assert (run "," "foo," ("foo", "", true))
  // Separator overlapped.
  assert (run ",," ",,," ("", ",", true))
  // Binary in case.
  assert (run "\x00" "+\x00-\x00" ("+", "-\x00", true))

let private cutLastTest () =
  let run sep s expected =
    let debug (s1, s2, ok: bool) = s1 + ";" + s2 + ";" + string ok
    debug (S.cutLast sep s) = debug expected

  // Basic.
  assert (run "." "file.generated.txt" ("file.generated", "txt", true))

  // Edges.
  assert (run "" "input" ("input", "", true))
  assert (run "sep" "" ("", "", false))
  assert (run "" "" ("", "", true))

let private splitTest () =
  let run sep s expected =
    let debug xs = xs |> S.concat ";"
    debug (S.split sep s) = debug expected

  // Basic.
  assert (run "," "one,two,three" [ "one"; "two"; "three" ])
  // Not separated.
  assert (run "," "foo" [ "foo" ])
  // Empty input.
  assert (run "," "" [ "" ])
  // Leading/trailing separators.
  assert (run "," ",foo," [ ""; "foo"; "" ])
  // Separator overlapped.
  assert (run ",," ",,," [ ""; "," ])

let private stripStartTest () =
  let run prefix s expected =
    let debug (s, ok: bool) = s + ";" + string ok
    debug (S.stripStart prefix s) = debug expected

  // Basic.
  assert (run "un" "unhappy" ("happy", true))
  assert (run "un" "lucky" ("lucky", false))

  // Edges.
  assert (run "" "foo" ("foo", true))
  assert (run "un" "" ("", false))
  assert (run "" "" ("", true))

let private stripEndTest () =
  let run suffix s expected =
    let debug (s, ok: bool) = s + ";" + string ok
    debug (S.stripEnd suffix s) = debug expected

  // Basic.
  assert (run "apple" "pineapple" ("pine", true))
  assert (run "apple" "pine" ("pine", false))

  // Edges.
  assert (run "" "input" ("input", true))
  assert (run "sep" "" ("", false))
  assert (run "" "" ("", true))

let private toLinesTest () =
  assert ((S.toLines "a\nb\nc" |> S.concat ";") = "a;b;c")
  assert ((S.toLines "a\nb\nc\n" |> S.concat ";") = "a;b;c;")
  assert ((S.toLines "a" |> S.concat ";") = "a")
  assert ((S.toLines "\n" |> S.concat ";") = ";")
  assert ((S.toLines "" |> S.concat ";") = "")

let concatTest () =
  assert (S.concat ", " [ "ab"; "cd"; "ef" ] = "ab, cd, ef")
  assert (S.concat "" [] = "")

let main _ =
  isEmptyTest ()
  tryItemTest ()

  // Search.
  startsWithTest ()
  endsWithTest ()
  findIndexTest ()
  findLastIndexTest ()
  containsTest ()

  // Slice.
  truncateTest ()
  skipTest ()
  sliceTest ()

  // Trim.
  trimTest ()

  // Replace.
  replaceTest ()
  toLowerTest ()
  toUpperTest ()

  // Split.
  cutTest ()
  cutLastTest ()
  splitTest ()
  stripStartTest ()
  stripEndTest ()
  toLinesTest ()

  // Concat.
  concatTest ()
  0
