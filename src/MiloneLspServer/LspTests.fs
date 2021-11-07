// FIXME: separate project
module rec MiloneLspServer.LspTests

open MiloneLspServer.Lsp

module S = MiloneStd.StdString

let private expect msg opt =
  match opt with
  | Some it -> it
  | None -> failwithf "Expected some: %A" msg

let private toLines (s: string) =
  s.TrimEnd().Replace("\r\n", "\n").Split("\n")
  |> Array.mapi (fun i item -> i, item)
  |> Array.toList

let private runTests cases =
  let pass, fail =
    cases
    |> Seq.fold
         (fun (pass, fail) ok ->
           if ok then
             pass + 1, fail
           else
             pass, fail + 1)
         (0, 0)

  let status, code = if fail = 0 then "OK", 0 else "FAIL", 1

  eprintfn "%s: pass %d / fail %d / total %d" status pass fail (pass + fail)
  code

let private assertEqual (title: string) (expected: string) (actual: string) : bool =
  if actual = expected then
    if System.Environment.GetEnvironmentVariable("VERBOSE") = "1" then
      eprintfn "Pass %s:\n%s\n" title actual

    true
  else
    eprintfn "Assertion violation: %s\n  actual = %s\n  expected = %s" title actual expected
    false

let private testRefsSingleFile title text : bool =
  let projectDir = "./TestProject"
  let docId = "TestProject.TestProject"
  let docMap = Map.ofList [ docId, (1, text) ]

  let docs: LangServiceDocs =
    { FindDocId =
        fun p m ->
          let docId = sprintf "%s.%s" p m

          if docMap |> Map.containsKey docId then
            Some docId
          else
            None

      GetVersion =
        fun docId ->
          match docMap |> Map.tryFind docId with
          | Some (version, _) -> version
          | _ -> 0

      GetText =
        fun docId ->
          match docMap |> Map.tryFind docId with
          | Some it -> it
          | _ -> (0, "// Missing") }

  let host: Lsp.LangServiceHost =
    { MiloneHome = "?unexisting"
      Docs = docs
      MiloneHomeModules = fun () -> []
      FindModulesInDir = fun _ -> [] }

  let ls = LangService.create host

  let anchors =
    let lines = text |> toLines

    lines
    |> List.collect (fun (row, line) ->
      if row >= 1
         && line |> S.trimStart |> S.startsWith "//" then
        match line |> S.cut "^" with
        | leading, rest, true ->
          let column = leading.Length

          rest
          |> S.split ","
          |> List.map (fun anchor -> row - 1, column, anchor)
        | _ -> []
      else
        [])

  let firstAnchor =
    anchors
    |> List.tryHead
    |> expect (title + " should have anchor")

  let debug xs =
    xs
    |> List.sort
    |> List.map (fun (row, column, anchor) -> sprintf "%d:%d %s" row column anchor)
    |> S.concat "\n"

  let expected = anchors |> debug

  let actual =
    let row, column, _ = firstAnchor

    match ls
          |> LangService.findRefs projectDir docId (row, column)
      with
    | None ->
      let errors =
        ls |> LangService.validateProject projectDir

      if errors |> List.isEmpty then
        "No result."
      else
        sprintf "Compile error: %A" errors

    | Some (defs, uses) ->
      let collect kind xs =
        xs |> Seq.map (fun (_, (y, x)) -> y, x, kind)

      Seq.append (collect "def" defs) (collect "use" uses)
      |> Seq.toList
      |> debug

  actual |> assertEqual title expected

let private testHoverSingleFile title text expected : bool =
  let projectDir = "./TestProject"
  let docId = "TestProject.TestProject"
  let docMap = Map.ofList [ docId, (1, text) ]

  let docs: LangServiceDocs =
    { FindDocId =
        fun p m ->
          let docId = sprintf "%s.%s" p m

          if docMap |> Map.containsKey docId then
            Some docId
          else
            None

      GetVersion =
        fun docId ->
          match docMap |> Map.tryFind docId with
          | Some (version, _) -> version
          | _ -> 0

      GetText =
        fun docId ->
          match docMap |> Map.tryFind docId with
          | Some it -> it
          | _ -> (0, "// Missing") }

  let host: Lsp.LangServiceHost =
    { MiloneHome = "?unexisting"
      Docs = docs
      MiloneHomeModules = fun () -> []
      FindModulesInDir = fun _ -> [] }

  let ls = LangService.create host

  let targetPos =
    let lines = text |> toLines

    lines
    |> List.tryPick (fun (row, line) ->
      if row >= 1
         && line |> S.trimStart |> S.startsWith "//" then
        match line |> S.findIndex "^" with
        | Some column -> Some(row - 1, column)
        | _ -> None
      else
        None)
    |> expect (title + " should have cursor")

  let debug xs =
    xs
    |> List.sort
    |> List.map (fun (row, column, anchor) -> sprintf "%d:%d %s" row column anchor)
    |> S.concat "\n"

  let actual =
    match ls |> LangService.hover projectDir docId targetPos with
    | None ->
      let errors =
        ls |> LangService.validateProject projectDir

      if errors |> List.isEmpty then
        "No result."
      else
        sprintf "Compile error: %A" errors

    | Some it -> it

  actual |> assertEqual title expected

// -----------------------------------------------
// Refs
// -----------------------------------------------

let testRefs () =
  [ testRefsSingleFile
      "local var"
      """
        module rec TestProject.Program

        let main _ =
          let foo = 0
          //  ^def
          let _ = foo
          //      ^use
          0
      """

    testRefsSingleFile
      "static var"
      """
        module rec TestProject.Program

        let constant = 42
        //  ^def

        let n = constant + 1
        //      ^use

        let _n =
          let constant = "shadowing"
          constant

        let main _ =
          printfn "%d" constant
          //           ^use
          0
      """

    testRefsSingleFile
      "local fun"
      """
        module rec TestProject.Program

        let main _ =
          let f () = 0
          //  ^def

          let g () = f ()
          //         ^use

          let _n = f ()
          //       ^use

          let f = () // Shadowing.
          let _ = f
          0
      """

    testRefsSingleFile
      "static fun"
      """
        module rec TestProject.Program

        let fact (n: int): int =
        //  ^def
          if n = 0 then 1 else fact (n - 1) * n
        //                     ^use

        let main _ = fact 5
        //           ^use
      """

    testRefsSingleFile
      "unit-like variant"
      """
        module rec TestProject.Program

        type MyOption =
          | MyNone
        //  ^def
          | MySome of int

        let none () = MyNone
        //            ^use

        let main _ =
          match none () with
          | MyNone -> 0
        //  ^use
          | _ -> 1
      """

    testRefsSingleFile
      "primitive"
      """
        module rec TestProject.Program

        let main _ =
          // FIXME: it fails without whitespace
          printfn "%s" ( string 42)
          //             ^use
          printfn "%s" ( string 42.0)
          //             ^use
          0
      """

    testRefsSingleFile
      "value-carrying variant"
      """
        module rec TestProject.Program

        type MyOption =
          | MyNone
          | MySome of int
        //  ^def

        let some x = MySome x
        //           ^use

        let someFun = MySome
        //            ^use

        let main _ =
          match some 1 with
          | MySome _ -> 0
        //  ^use
          | _ -> 1
      """

    testRefsSingleFile
      "field"
      """
        module rec TestProject.Program

        type MyPair =
          { First: int
        //  ^def
            Second: string }

        let pair x y : MyPair =
          { First = x
        //  ^use
            Second = y }

        let first (pair: MyPair) =
          pair.First
        //     ^use

        let main _ = 0
      """

    testRefsSingleFile
      "union type"
      """
        module rec TestProject.Program

        type MyOption =
        //   ^def
          | MyNone
          | MySome of int

        let some x : MyOption = MySome x
        //                      ^use
        // FIXME: incorrect range

        let main _ = 0
      """

    testRefsSingleFile
      "record type"
      """
        module rec TestProject.Program

        type MyPair =
        //   ^def
          { First: int
            Second: string }

        let pair x y : MyPair =
        //             ^use
          { First = x
            Second = y }

        let first (pair: MyPair) =
        // FIXME: detect this
          pair.First

        let second (pair: MyPair) =
        //                ^use
          let _ : unit -> MyPair * int = fun () -> pair, 0
          // FIXME: detect this
          pair.Second

        let main _ = 0
      """ ]

// -----------------------------------------------
// Hover
// -----------------------------------------------

let private testHover () =
  [ testHoverSingleFile
      "var"
      """
        module rec TestProject.Program

        let main _ =
          let foo = 42
          //  ^cursor
          0
      """
      "int"

    // FIXME: it seems incorrect
    testHoverSingleFile
      "fun"
      """
        module rec TestProject.Program

        let pair (x: int) (y: string) : int * string = x, y
        //  ^cursor

        let main _ = 0
      """
      "string -> int -> (int * string)"

    testHoverSingleFile
      "user-defined type var"
      """
        module rec TestProject.Program

        type MyUnit = | MyUnit
        type MyBox = { Value: int }

        let main _ =
          let it =
          //  ^cursor
            let b : MyBox = { Value = 42 }
            MyUnit, b
          0
      """
      "(MyUnit * MyBox)"

    testHoverSingleFile
      "no hover"
      """
        module rec TestProject.Program

        let main _ = 0
        //         ^cursor
      """
      "No result." ]

// -----------------------------------------------
// Interface
// -----------------------------------------------

let lspTests () =
  List.collect id [ testRefs (); testHover () ]
  |> runTests
  |> exit
