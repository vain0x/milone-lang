// FIXME: separate project
module rec MiloneLspServer.LspTests

open MiloneLspServer.Lsp
open MiloneLspServer.LspUtil

module S = MiloneStd.StdString
module LLS = MiloneLspServer.LspLangService
module WorkspaceAnalysis = LLS.WorkspaceAnalysis

let private expect msg opt =
  match opt with
  | Some it -> it
  | None -> failwithf "Expected some: %A" msg

let private toLines (s: string) =
  s.TrimEnd().Replace("\r\n", "\n").Split("\n")
  |> Array.mapi (fun i item -> i, item)
  |> Array.toList

let private splitLast xs =
  match xs |> List.rev with
  | last :: nonLast -> Some(List.rev nonLast, last)
  | [] -> None

// -----------------------------------------------
// tests
// -----------------------------------------------

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
    assert false
    false

/// Parses a text as multiple files.
///
/// Each file is separated by header line `# file: ...`.
///
/// ```
/// # file: /path/to/File1.txt
/// This is contents of `File1.txt`.
///
/// # file: /path/to/File2.yml
/// - This is
/// - contents of
/// - 'File2.yml'
/// ```
let private parseFiles text : (string * string) list =
  let lines = text |> toLines |> List.map snd

  let rec goBody acc xs =
    match xs with
    | x :: _ when x |> S.startsWith "# file:" |> not -> goBody (x :: acc) xs
    | _ -> acc, xs

  let rec goFiles acc lines =
    match lines with
    | [] -> acc

    | line :: lines ->
      let dir, ok = line |> S.stripStart "# file:"

      if not ok then
        failwith "should start with `# file:`"

      let bodyAcc, lines = goBody [] lines

      let file =
        dir, bodyAcc |> List.rev |> S.concat "\n"

      goFiles (file :: acc) lines

  goFiles [] lines

/// Collects all anchors which represent a position in text with label.
///
/// ## Single anchor
///
/// Typically an anchor is written as:
///
/// ```fs
///     let f () = 42   // arbitrary code here
///     //  ^def
/// ```
///
/// In the example, `^def` is an anchor that points to `f` in the previous line and is labeled with `def`.
///
/// ## Multiple anchors
///
/// In rare case, a line contains multiple anchors.
/// There are two ways to write labels.
/// First, each caret is followed by its label.
///
/// ```fs
///     let foo () = goo ()
///     //  ^def     ^use
/// ```
///
/// In the example, `foo` is pointed by an anchor with label `def`,
/// and `goo` is pointed by anchor with label `use`.
///
/// Alternatively, after the final anchor on the line,
/// put all labels separated by semicolon `;`s.
///
/// ```fs
///     let x, y, z = triple
///     //  ^  ^  ^   ^     def; def; def; use
/// ```
///
/// In the example `x`, `y`, `z`, `triple` are pointed by anchors.
/// Label of them are, respectively, `def`, `def`, `def`, `use`.
let private parseAnchors text : ((int * int) * string) list =
  let lines = text |> toLines

  lines
  |> List.collect (fun (row, line) ->
    if row >= 1
       && line |> S.trimStart |> S.startsWith "//"
       && line |> S.contains "^" then
      let parts = line |> S.split "^"

      let posList, rest =
        match splitLast parts with
        | None -> [], ""
        | Some (nonLastParts, rest) ->
          let posList, _ =
            nonLastParts
            |> List.mapFold
                 (fun column (part: string) ->
                   let column = column + part.Length
                   let pos = row - 1, column
                   pos, column + "^".Length)
                 0

          posList, rest

      let labels =
        let parts = parts |> List.skip 1 |> List.map S.trim
        let rest = rest |> S.trim

        if parts
           |> List.forall (fun s -> s |> S.isEmpty |> not) then
          parts
        else if rest <> "" then
          rest |> S.split ";"
        else
          []

      let caretCount = List.length posList
      let labelCount = List.length labels

      if caretCount <> labelCount then
        failwithf "Mismatch number of anchor labels: %d carets, %d labels at row %d" caretCount labelCount row

      List.zip posList labels
    else
      [])

// -----------------------------------------------
// in-memory project
// -----------------------------------------------

let private projectDir = "/example.com/TestProject"
let private projectName = "TestProject"
let private docId = "TestProject.TestProject"

let private components (path: string) =
  if path = "/" then
    []
  else
    let pathname, ok = path |> S.stripStart "/"

    if not ok then
      failwithf "not supported relative path: %s" path

    S.split "/" pathname

let private stripCommonPrefix equals prefix xs =
  match prefix, xs with
  | p :: ps, x :: xs when equals p x -> stripCommonPrefix equals ps xs
  | _ -> prefix, xs

let private ensureNormalization hint path =
  let normalized = LLS.normalize path

  if path <> normalized then
    eprintfn "warn: %s non-normal filepath used.\n  given: %s\n  normal: %s" hint path normalized

  normalized

let private dirEntriesIn files dir =
  let dir = ensureNormalization "DirEntries" dir
  let dirComponents = components dir

  let files, subdirs =
    files
    |> List.filter (fun (path, _) -> path |> S.startsWith dir)
    |> List.fold
         (fun (fileAcc, subdirAcc) (path, _) ->
           let _, x =
             stripCommonPrefix (=) dirComponents (components path)

           match x with
           | [ filename ] -> dir + "/" + filename :: fileAcc, subdirAcc
           | subdir :: _ -> fileAcc, dir + "/" + subdir :: subdirAcc
           | _ -> fileAcc, subdirAcc)
         ([], [])

  let files = files |> List.sort
  let subdirs = subdirs |> set |> Set.toList // unique

  files, subdirs

let private testDirEntries () =
  let files =
    [ "/$/CmdFoo/CmdFoo.milone"
      "/$/CmdFoo/Types.milone"
      "/$/LibBar/Types.milone"
      "/$/LibBar/Domain.milone"
      "/$/README.md" ]
    |> List.map (fun path -> path, "")

  let f dir expected =
    let actual = dirEntriesIn files dir

    if actual <> expected then
      eprintfn "actual: %A\nexpected: %A" actual expected
      assert false

  f "/$" ([ "/$/README.md" ], [ "/$/CmdFoo"; "/$/LibBar" ])

  f
    "/$/CmdFoo"
    ([ "/$/CmdFoo/CmdFoo.milone"
       "/$/CmdFoo/Types.milone" ],
     [])

let private createWorkspaceAnalysisWithFiles files =
  let miloneHome = "/$/.milone"
  let rootDir = "/$/root"

  let fileMap =
    files
    |> List.map (fun (name, contents) -> LLS.normalize name, contents)
    |> Map.ofList

  let host: LLS.WorkspaceAnalysisHost =
    { MiloneHome = miloneHome

      FileExists =
        fun path ->
          let path = ensureNormalization "FileEntries" path
          fileMap |> Map.containsKey (LLS.normalize path)

      DirEntries = dirEntriesIn files }

  let wa =
    WorkspaceAnalysis.empty host
    |> LLS.onInitialized (
      rootDir
      |> LLS.uriOfFilePath
      |> Uri.toString
      |> Some
    )

  files
  |> List.fold
       (fun wa (path, contents) ->
         wa
         |> WorkspaceAnalysis.didOpenDoc (LLS.uriOfFilePath path) 1 contents)
       wa

let private getProject name (wa: LLS.WorkspaceAnalysis) =
  wa.ProjectList
  |> List.tryFind (fun (p: LLS.ProjectInfo) -> p.ProjectName = name)
  |> expect ("project " + name)

let private createSingleFileProject text action =
  let wa =
    createWorkspaceAnalysisWithFiles [ "/$/root/TestProject/TestProject.milone", text ]

  wa
  |> LLS.doWithProjectAnalysis (getProject "TestProject" wa) action

let private doTestRefsSingleFile title text (ls: ProjectAnalysis) : bool * ProjectAnalysis =
  let anchors = parseAnchors text

  let firstAnchor =
    anchors |> List.tryHead |> expect "anchor"

  let debug xs =
    xs
    |> List.sort
    |> List.map (fun ((y, x), anchor) -> sprintf "%d:%d %s" y x anchor)
    |> S.concat "\n"

  let expected = anchors |> debug

  let actual, ls =
    let pos, _ = firstAnchor

    match ls |> LLS.ProjectAnalysis.findRefs docId pos with
    | None, ls ->
      let errors, ls =
        ls |> LLS.ProjectAnalysis.validateProject

      let msg =
        if errors |> List.isEmpty then
          "No result."
        else
          sprintf "Compile error: %A" errors

      msg, ls

    | Some (defs, uses), _ ->
      let collect kind xs =
        xs |> Seq.map (fun (_, pos) -> pos, kind)

      let a =
        Seq.append (collect "def" defs) (collect "use" uses)
        |> Seq.toList
        |> debug

      a, ls

  actual |> assertEqual title expected, ls

let private testRefsSingleFile title text : bool =
  createSingleFileProject text (doTestRefsSingleFile title text)
  |> fst

let private doTestHoverSingleFile title text expected ls : bool * _ =
  let targetPos, _ =
    parseAnchors text
    |> List.tryHead
    |> expect "anchor"

  let debug xs =
    xs
    |> List.sort
    |> List.map (fun (row, column, anchor) -> sprintf "%d:%d %s" row column anchor)
    |> S.concat "\n"

  let actual, ls =
    match ls |> LLS.ProjectAnalysis.hover docId targetPos with
    | None, ls ->
      let errors, ls =
        ls |> LLS.ProjectAnalysis.validateProject

      let msg =
        if errors |> List.isEmpty then
          "No result."
        else
          sprintf "Compile error: %A" errors

      msg, ls

    | Some it, ls -> it, ls

  actual |> assertEqual title expected, ls

let private testHoverSingleFile title text expected : bool =
  createSingleFileProject text (doTestHoverSingleFile title text expected)
  |> fst

let private doTestRenameSingleFile title text newName expected ls : bool * _ =
  let targetPos, _ =
    parseAnchors text
    |> List.tryHead
    |> expect "anchor"

  let debug xs =
    xs
    |> List.sort
    |> List.map (fun (row, column, newName) -> sprintf "%d:%d %s" row column newName)
    |> S.concat "\n"

  let actual, ls =
    match ls
          |> LLS.ProjectAnalysis.rename docId targetPos newName
      with
    | [], ls ->
      let errors, ls =
        ls |> LLS.ProjectAnalysis.validateProject

      let msg =
        if errors |> List.isEmpty then
          "No result."
        else
          sprintf "Compile error: %A" errors

      msg, ls

    | changes, ls ->
      changes
      |> List.map (fun (_, (((y, x), _), newName)) -> y, x, newName)
      |> debug,
      ls

  actual |> assertEqual title expected, ls

let private testRenameSingleFile title text newName expected : bool =
  createSingleFileProject text (doTestRenameSingleFile title text newName expected)
  |> fst

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
        //           ^use

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
        //               ^use
          pair.First

        let second (pair: MyPair) =
        //                ^use
          let _ : unit -> MyPair * int = fun () -> pair, 0
          //              ^use
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
// Rename
// -----------------------------------------------

let private testRename () =
  [ testRenameSingleFile
      "var"
      """
        module rec TestProject.Program

        let main _ =
          let foo = 42
          //  ^baz

          foo
      //  ^baz
      """
      "baz"
      """4:14 baz
7:10 baz""" ]

// -----------------------------------------------
// DocumentSymbol
// -----------------------------------------------

let private doTestDocumentSymbolSingleFile title expected (ls: ProjectAnalysis) : bool * ProjectAnalysis =
  let debug xs =
    xs
    |> List.sortBy (fun (_, _, pos) -> pos)
    |> List.map (fun (name, kind, (y, x)) -> sprintf "%d:%d %s (%d)" y x name kind)
    |> S.concat "\n"

  let actual, _ =
    ls |> LLS.ProjectAnalysis.documentSymbol docId

  actual
  |> List.map (fun (name, kind, (pos, _)) -> name, kind, pos)
  |> debug
  |> assertEqual title expected,
  ls

let private testDocumentSymbolSingleFile title text expected : bool =
  createSingleFileProject text (doTestDocumentSymbolSingleFile title expected)
  |> fst

let private testDocumentSymbol () =
  [ testDocumentSymbolSingleFile
      "documentSymbol"
      """
        module rec TestProject.Program

        open MiloneStd.StdMap

        module S = MiloneStd.StdString

        type Int = int

        type Record = { F: int }

        type Union =
          | V of int

        let f () =
          ()

        let main _ =
          let localVar =
            1

          let localFun () =
            ()

          0
      """
      """1:31 Program (2)
5:15 S (2)
7:13 Int (5)
9:13 Record (5)
11:13 Union (5)
14:12 f (12)
17:12 main (12)
21:14 localFun (12)""" ]

// -----------------------------------------------
// Completion
// -----------------------------------------------

let private doTestCompletion (p: LLS.ProjectInfo) (wa: LLS.WorkspaceAnalysis) title text expected ls : bool * _ =
  let targetPos, _ =
    parseAnchors text
    |> List.tryHead
    |> expect "anchor"

  let debug xs = xs |> List.sort |> S.concat "\n"

  let actual, ls =
    match ls
          |> LLS.ProjectAnalysis.completion wa.StdLibModules wa.Host.DirEntries p.ProjectDir docId targetPos
      with
    | [], ls ->
      let errors, ls =
        ls |> LLS.ProjectAnalysis.validateProject

      let msg =
        if errors |> List.isEmpty then
          "No result."
        else
          sprintf "Compile error: %A" errors

      msg, ls

    | result, ls -> debug result, ls

  actual |> assertEqual title (debug expected), ls

let private testCompletionMultipleFiles title files expected : bool =
  let wa = createWorkspaceAnalysisWithFiles files

  let path, text =
    files
    |> List.tryFind (fun (_, text) -> parseAnchors text |> List.isEmpty |> not)
    |> expect "anchor"

  let p =
    let projectName =
      path
      |> LLS.dirname
      |> Option.map LLS.basename
      |> expect "project"

    getProject projectName wa

  LLS.doWithProjectAnalysis p (doTestCompletion p wa title text expected) wa
  |> fst

let private testCompletionSingleFile title text expected : bool =
  testCompletionMultipleFiles title [ "/$/root/TestProject/TestProject.milone", text ] expected

let private testCompletion () =
  [ testCompletionSingleFile
      "local var"
      """
        module rec TestProject.Program

        let main _ =
          let () =
            let y = ()
            y

          let x = 1

      //  ^cursor
          0
      """
      [ "main"; "x" ]

  // testCompletionSingleFile
  //   "dot"
  //   """
  //     module rec TestProject.Program

  //     let main _ =
  //       List.   (x.y)
  //   //       ^cursor
  //       0
  //   """
  //   [ "List.*" ]
   ]

// -----------------------------------------------
// Diagnostics
// -----------------------------------------------

// Run server (stateful).

let private testDiagnostics miloneHome =
  let workDir = System.Environment.CurrentDirectory

  let rootUri =
    workDir |> LLS.uriOfFilePath |> Uri.toString

  let wa = WorkspaceAnalysis.empty miloneHome
  let wa = LLS.onInitialized (Some rootUri) wa

  let result, wa = WorkspaceAnalysis.diagnostics wa
  assert (List.length result = 0)

  let filename =
    System.IO.Path.Combine(workDir, "tests/DiagnosticsTest/DiagnosticsTest.milone")

  let fileUri = LLS.uriOfFilePath filename
  let initialText = System.IO.File.ReadAllText(filename)

  let result, wa =
    try
      let text =
        initialText.Replace("// let x 0", "let x 0")

      System.IO.File.WriteAllText(filename, text)

      let wa =
        WorkspaceAnalysis.didChangeFile fileUri wa

      WorkspaceAnalysis.diagnostics wa
    finally
      System.IO.File.WriteAllText(filename, initialText)

  assert (List.length result = 1)

  for uri, errors in result do
    for msg, (y1, x1), (y2, x2) in errors do
      printfn "error: \"%s\" %s:%d:%d..%d:%d" msg (Uri.toString uri) (y1 + 1) (x1 + 1) (y2 + 1) (x2 + 1)

  // highlight (main function)
  let wa =
    WorkspaceAnalysis.didChangeFile fileUri wa

  let reads, writes, _ =
    WorkspaceAnalysis.documentHighlight fileUri (2, 4) wa

  printfn "reads: %A" reads
  printfn "writes: %A" writes
  assert (List.length writes = 1)

// -----------------------------------------------
// Interface
// -----------------------------------------------

let lspTests miloneHome =
  testDirEntries ()

  let code =
    [ testRefs ()
      testHover ()
      testRename ()
      testDocumentSymbol ()
      testCompletion () ]
    |> List.collect id
    |> runTests

  if code = 0 then
    testDiagnostics miloneHome

  exit code
