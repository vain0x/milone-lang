// should be separate project
module rec MiloneLspServer.LspTests

open MiloneShared.UtilParallel
open MiloneShared.UtilSymbol
open MiloneLspServer.Lsp
open MiloneLspServer.LspUtil

module S = Std.StdString
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

let private pathToProjectName path =
  path
  |> Path.dirname
  |> Option.map Path.basename
  |> expect "project"

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

let private firstPos anchors =
  anchors |> List.tryHead |> expect "anchor" |> fst

// -----------------------------------------------
// in-memory project
// -----------------------------------------------

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
  let normalized = Path.normalize path

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

let private dummyMiloneHome = "/$/.milone"
let private dummyRootDir = "/$/root"
let private dummyRootUri = uriOfFilePath dummyRootDir

let private createWorkspaceAnalysisHostWithFiles files : LLS.WorkspaceAnalysisHost =
  let fileMap =
    files
    |> List.map (fun (name, contents) -> Path.normalize name, contents)
    |> Map.ofList

  let host: LLS.WorkspaceAnalysisHost =
    { MiloneHome = dummyMiloneHome

      FileExists =
        fun path ->
          let path = ensureNormalization "FileEntries" path
          fileMap |> Map.containsKey path

      ReadTextFile =
        fun path ->
          let path = ensureNormalization "ReadTextFile" path
          fileMap |> Map.tryFind path |> Future.just

      DirEntries = dirEntriesIn files }

  host

let private createWorkspaceAnalysisWithFiles files =
  let host =
    createWorkspaceAnalysisHostWithFiles files

  WorkspaceAnalysis.create host
  |> WorkspaceAnalysis.onInitialized (Some dummyRootUri)

// Update underlying file system.
//
// File changes aren't notified. Call didOpenFile etc.
let private withFiles files wa =
  wa
  |> WorkspaceAnalysis.withHost (createWorkspaceAnalysisHostWithFiles files)

let private getProject name (wa: LLS.WorkspaceAnalysis) =
  wa.ProjectList
  |> List.tryFind (fun (p: LLS.ProjectInfo) -> p.ProjectName = name)
  |> expect ("project " + name)

let private createSingleFileProject text action =
  let wa =
    createWorkspaceAnalysisWithFiles [ "/$/root/TestProject/TestProject.milone", text ]

  let docId = Symbol.intern "TestProject.TestProject"

  wa
  |> LLS.doWithProjectAnalysis (getProject "TestProject" wa) (action docId)

/// Gets compilation errors or `No result.`.
/// Use this when analysis result is empty.
let private debugProject pa : string * ProjectAnalysis =
  let errors, pa =
    pa |> LLS.ProjectAnalysis.validateProject

  let msg =
    if errors |> List.isEmpty then
      "No result."
    else
      sprintf "Compile error: %A" errors

  msg, pa

let private doTestRefsSingleFile title text docId (pa: ProjectAnalysis) : bool * ProjectAnalysis =
  let anchors = parseAnchors text
  let targetPos = firstPos anchors

  let debug xs =
    xs
    |> List.sort
    |> List.map (fun ((y, x), anchor) -> sprintf "%d:%d %s" y x anchor)
    |> S.concat "\n"

  let expected = anchors |> debug

  let actual, pa =
    match pa |> LLS.ProjectAnalysis.findRefs docId targetPos with
    | None, pa -> debugProject pa

    | Some (defs, uses), _ ->
      let collect kind xs =
        xs |> Seq.map (fun (_, pos) -> pos, kind)

      let a =
        Seq.append (collect "def" defs) (collect "use" uses)
        |> Seq.toList
        |> debug

      a, pa

  actual |> assertEqual ("refs: " + title) expected, pa

let private testRefsSingleFile title text : bool =
  createSingleFileProject text (doTestRefsSingleFile title text)
  |> fst

let private doTestHoverSingleFile title text expected docId pa : bool * _ =
  let targetPos = firstPos (parseAnchors text)

  let debug xs =
    xs
    |> List.sort
    |> List.map (fun (row, column, anchor) -> sprintf "%d:%d %s" row column anchor)
    |> S.concat "\n"

  let actual, pa =
    match pa |> LLS.ProjectAnalysis.hover1 docId targetPos with
    | None, pa -> debugProject pa
    | Some it, pa -> it, pa

  actual |> assertEqual ("hover: " + title) expected, pa

let private testHoverSingleFile title text expected : bool =
  createSingleFileProject text (doTestHoverSingleFile title text expected)
  |> fst

let private doTestRenameSingleFile title text newName expected docId pa : bool * _ =
  let targetPos = firstPos (parseAnchors text)

  let debug xs =
    xs
    |> List.sort
    |> List.map (fun (row, column, newName) -> sprintf "%d:%d %s" row column newName)
    |> S.concat "\n"

  let actual, pa =
    match pa
          |> LLS.ProjectAnalysis.rename docId targetPos newName
      with
    | [], pa -> debugProject pa

    | changes, pa ->
      changes
      |> List.map (fun (_, (((y, x), _), newName)) -> y, x, newName)
      |> debug,
      pa

  actual |> assertEqual title expected, pa

let private testRenameSingleFile title text newName expected : bool =
  createSingleFileProject text (doTestRenameSingleFile title text newName expected)
  |> fst

// -----------------------------------------------
// DocChange
// -----------------------------------------------

let private testDocChange () =
  let path = "/$/root/TestProject/TestProject.milone"
  let uri = uriOfFilePath path

  // (File of version N has a diagnostic at row N.)
  let diagnosticsToVersion diagnostics =
    match diagnostics with
    | [ _, [ _, (row, _), _ ] ] -> "v" + string row
    | _ -> failwithf "diagnostics: %A" diagnostics

  let d2, wa =
    createWorkspaceAnalysisWithFiles [ path, "\nv1" ]
    |> withFiles [ path, "\n\nv2" ]
    |> WorkspaceAnalysis.didChangeFile uri
    |> WorkspaceAnalysis.diagnostics

  assert (d2
          |> diagnosticsToVersion
          |> assertEqual "v2" "v2")

  // Open doc is used.
  let d3, wa =
    wa
    |> WorkspaceAnalysis.didOpenDoc uri 3 "\n\n\nv3"
    |> WorkspaceAnalysis.diagnostics

  assert (d3
          |> diagnosticsToVersion
          |> assertEqual "v3" "v3")

  // Change doc is affected.
  let d4, wa =
    wa
    |> WorkspaceAnalysis.didChangeDoc uri 4 "\n\n\n\nv4"
    |> WorkspaceAnalysis.diagnostics

  assert (d4
          |> diagnosticsToVersion
          |> assertEqual "v4" "v4")

  // Change doc so that next diagnostics aren't suppressed.
  let wa =
    wa
    |> WorkspaceAnalysis.didChangeDoc uri 5 "\n\n\n\n\nv5"

  // Change of file is ignored when doc is open.
  let d5, wa =
    wa
    |> withFiles [ path, "\n\n\n\n\n\nv6" ]
    |> WorkspaceAnalysis.didChangeFile uri
    |> WorkspaceAnalysis.diagnostics

  assert (d5
          |> diagnosticsToVersion
          |> assertEqual "v5" "v5")

  // After doc is closed, file is open.
  let d6, wa =
    wa
    |> WorkspaceAnalysis.didCloseDoc uri
    |> WorkspaceAnalysis.diagnostics

  assert (d6
          |> diagnosticsToVersion
          |> assertEqual "v6" "v6")

  // After file is also closed.
  let d7, _ =
    wa
    |> withFiles []
    |> WorkspaceAnalysis.didCloseFile uri
    |> WorkspaceAnalysis.diagnostics

  match d7 with
  | [ _, [] ] -> () // OK, diagnostics cleared.
  | _ -> failwithf "diagnostics %A" d7

  [ true ]

// -----------------------------------------------
// Refs
// -----------------------------------------------

let private testRefs () =
  [ testRefsSingleFile
      "local var"
      """
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
        let main _ =
          // FIXME: it fails without whitespace
          printfn "%s" ( string 42)
          //             ^use
          printfn "%s" ( string 42.0)
          //             ^use
          0
      """

    // FIXME: position of final use is incorrect
    testRefsSingleFile
      "value-carrying variant"
      """
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
        //        ^use
          | _ -> 1
      """

    testRefsSingleFile
      "field"
      """
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
        let pair (x: int) (y: string) : int * string = x, y
        //  ^cursor

        let main _ = 0
      """
      "string -> int -> (int * string)"

    testHoverSingleFile
      "user-defined type var"
      """
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
        let main _ =
          let foo = 42
          //  ^baz

          foo
      //  ^baz
      """
      "baz"
      """2:14 baz
5:10 baz""" ]

// -----------------------------------------------
// DocumentSymbol
// -----------------------------------------------

let private doTestDocumentSymbolSingleFile title expected docId (pa: ProjectAnalysis) : bool * ProjectAnalysis =
  let debug xs =
    xs
    |> List.sortBy (fun (_, _, pos) -> pos)
    |> List.map (fun (name, kind, (y, x)) -> sprintf "%d:%d %s (%d)" y x name kind)
    |> S.concat "\n"

  let actual, _ =
    pa |> LLS.ProjectAnalysis.documentSymbol docId

  actual
  |> List.map (fun (name, kind, (pos, _)) -> name, kind, pos)
  |> debug
  |> assertEqual title expected,
  pa

let private testDocumentSymbolSingleFile title text expected : bool =
  createSingleFileProject text (doTestDocumentSymbolSingleFile title expected)
  |> fst

let private testDocumentSymbol () =
  [ testDocumentSymbolSingleFile
      "documentSymbol"
      """
        module rec TestProject.Program

        open Std.StdMap

        module S = Std.StdString

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
      """1:8 TestProject (2)
5:15 S (2)
7:13 Int (5)
9:13 Record (5)
11:13 Union (5)
14:12 f (12)
17:12 main (12)
21:14 localFun (12)""" ]

// -----------------------------------------------
// CodeAction
// -----------------------------------------------

// generate module head
let private testCodeActionGenerateModuleHead () =
  let path = "/$/root/TestProject/TestProject.milone"

  let wa =
    createWorkspaceAnalysisWithFiles [ path, "" ]

  let range: Range = Range.zero

  let result, _ =
    wa
    |> WorkspaceAnalysis.codeAction (uriOfFilePath path) range

  let actual =
    result
    |> List.choose (fun (title, edit) ->
      let edit =
        edit
        |> List.collect (fun (_, changes) ->
          changes
          |> List.filter (fun (_, text) -> text |> S.contains "module rec")
          |> List.map snd)

      if edit |> List.isEmpty |> not then
        Some(title, edit |> S.concat "\n")
      else
        None)

  let debug xs =
    xs
    |> List.sort
    |> List.map (fun (x, y) -> x + ": " + y)
    |> S.concat "\n"

  let expected =
    """Generate module head: module rec TestProject.TestProject
"""

  actual
  |> debug
  |> assertEqual "module head" expected

let private testCodeActionGenerateOpen () =
  let path = "/$/root/TestProject/TestProject.milone"

  let text =
    """
      open Std.StdMap

      let f = X.
      //        ^cursor
    """

  let files =
    [ "/$/root/TestProject/Other.milone",
      """
        module X =
          let foo () = ()
      """

      path, text ]

  let wa = createWorkspaceAnalysisWithFiles files

  let cursorPos = text |> parseAnchors |> firstPos

  let result, _ =
    let range: Range = cursorPos, cursorPos

    wa
    |> WorkspaceAnalysis.codeAction (uriOfFilePath path) range

  let actual =
    result
    |> List.choose (fun (title, edit) ->
      if title |> S.contains "open" then
        let edit =
          edit
          |> List.collect (fun (_, changes) ->
            changes
            |> List.map (fun (((row, _), _), text) -> string row + ": " + text))

        if edit |> List.isEmpty |> not then
          Some(title, edit |> S.concat "\n")
        else
          None
      else
        None)

  let debug xs =
    xs
    |> List.sort
    |> List.map (fun (x, y) -> x + ": " + y)
    |> S.concat "\n"

  let expected =
    """Generate open: 2: open TestProject.Other
"""

  actual
  |> debug
  |> assertEqual "generate open" expected

let private testCodeActionGenerateModuleSynonym () =
  let path = "/$/root/TestProject/TestProject.milone"

  let text =
    """
      module C = Std.StdChar

      let f = S.
      //        ^cursor
    """

  let files =
    [ "/$/root/TestProject/Other.milone",
      """
        module S = Std.StdString
      """

      path, text ]

  let wa = createWorkspaceAnalysisWithFiles files

  let cursorPos = text |> parseAnchors |> firstPos

  let result, _ =
    let range: Range = cursorPos, cursorPos

    wa
    |> WorkspaceAnalysis.codeAction (uriOfFilePath path) range

  let actual =
    result
    |> List.choose (fun (title, edit) ->
      let edit =
        edit
        |> List.collect (fun (_, changes) ->
          changes
          |> List.filter (fun (_, text) -> text |> S.contains "module S")
          |> List.map (fun (((row, _), _), text) -> string row + " " + text))

      if edit |> List.isEmpty |> not then
        Some(title, edit |> S.concat "\n")
      else
        None)

  let debug xs =
    xs
    |> List.sort
    |> List.map (fun (x, y) -> x + ": " + y)
    |> S.concat "\n"

  let expected =
    """Generate module synonym: 2 module S = Std.StdString
"""

  actual
  |> debug
  |> assertEqual "generate module synonym" expected

let private testCodeAction () =
  [ testCodeActionGenerateModuleHead ()
    testCodeActionGenerateOpen ()
    testCodeActionGenerateModuleSynonym () ]

// -----------------------------------------------
// Completion
// -----------------------------------------------

let private doTestCompletion (p: LLS.ProjectInfo) (wa: LLS.WorkspaceAnalysis) title text expected docId pa : bool * _ =
  let targetPos = firstPos (parseAnchors text)

  let debug xs = xs |> List.sort |> S.concat "\n"

  let actual, pa =
    match pa
          |> LLS.ProjectAnalysis.completion (WorkspaceAnalysis.getModules p wa) docId targetPos
      with
    | [], pa -> debugProject pa
    | result, pa -> debug result, pa

  actual |> assertEqual title (debug expected), pa

let private testCompletionMultipleFiles title files expected : bool =
  let wa = createWorkspaceAnalysisWithFiles files

  let path, text =
    files
    |> List.tryFind (fun (_, text) -> parseAnchors text |> List.isEmpty |> not)
    |> expect "anchor"

  let docId = LLS.filePathToDocId path
  let p = getProject (pathToProjectName path) wa

  LLS.doWithProjectAnalysis p (doTestCompletion p wa title text expected docId) wa
  |> fst

let private testCompletionSingleFile title text expected : bool =
  testCompletionMultipleFiles title [ "/$/root/TestProject/TestProject.milone", text ] expected

let private testCompletion () =
  [ testCompletionSingleFile
      "local var"
      """
        let localFun () = ()

        let () =
          let invisible = ()
          invisible

        let localVar = 1
                          //
      //^cursor
      """
      [ "localFun"; "localVar" ]

    testCompletionMultipleFiles
      "module name"
      [ "/$/.milone/src/Std/StdFoo.milone", ""
        "/$/root/TestProject/TestProject.milone",
        """
            module rec TestProject.TestProject

            module M =
            //        ^cursor
          """ ]
      [ "Std"; "StdFoo"; "TestProject" ]

    // ns-cases: completion from namespaces.
    testCompletionSingleFile
      "ns: file-local discriminated union"
      """
        type U = A of int | B of string

        let main _ =
          U.A
      //    ^cursor
          0
      """
      [ "A"; "B" ]
    ]

// -----------------------------------------------
// Find projects
// -----------------------------------------------

let private testFindProjects () =
  let files =
    [ "/$/.milone/src/Std/StdFoo.milone", "" ]

  let newFile = "/$/root/TestProject/TestProject.milone"
  let newFiles = (newFile, "") :: files

  let wa =
    createWorkspaceAnalysisWithFiles files
    |> WorkspaceAnalysis.withHost (createWorkspaceAnalysisHostWithFiles newFiles)
    |> WorkspaceAnalysis.didOpenFile (uriOfFilePath newFile)

  [ wa
    |> WorkspaceAnalysis.getProjectDirs
    |> S.concat "; "
    |> assertEqual "after open" "/$/root/TestProject"

    wa
    |> WorkspaceAnalysis.withHost (createWorkspaceAnalysisHostWithFiles files)
    |> WorkspaceAnalysis.didCloseFile (uriOfFilePath newFile)
    |> WorkspaceAnalysis.getProjectDirs
    |> S.concat "; "
    |> assertEqual "after close" "" ]

// -----------------------------------------------
// Diagnostics
// -----------------------------------------------

// Run server (stateful).

let private testDiagnostics host =
  let workDir =
    System.Environment.CurrentDirectory
    |> Path.normalize

  let workDirAsPathname =
    let uri = Uri.toString (uriOfFilePath workDir)
    let i = "file://".Length
    uri.[i..]

  let wa =
    let rootUri = workDir |> uriOfFilePath

    WorkspaceAnalysis.create host
    |> WorkspaceAnalysis.onInitialized (Some rootUri)

  let result, wa = WorkspaceAnalysis.diagnostics wa
  assert (List.length result = 0)

  let filename =
    System.IO.Path.Combine(workDir, "tests/DiagnosticsTest/DiagnosticsTest.milone")

  let fileUri = uriOfFilePath filename
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

  let errors =
    result
    |> List.collect (fun (uri, errors) ->
      errors
      |> List.map (fun (msg, (y1, x1), (y2, x2)) ->
        sprintf "error: \"%s\" %s:%d:%d..%d:%d" msg (Uri.toString uri) (y1 + 1) (x1 + 1) (y2 + 1) (x2 + 1)))

  // highlight (main function)
  let wa =
    WorkspaceAnalysis.didChangeFile fileUri wa

  let reads, writes, _ =
    WorkspaceAnalysis.documentHighlight fileUri (2, 4) wa

  let actual =
    List.append
      errors
      [ sprintf "reads: %A" reads
        sprintf "writes: %A" writes ]

  assert (actual
          |> S.concat "\n"
          |> S.replace workDirAsPathname "$HOME"
          |> assertEqual
               "testDiagnostics"
               """error: "PARSE ERROR: Missing '=' (0:1)" file://$HOME/tests/DiagnosticsTest/DiagnosticsTest.milone:7:1..7:1
reads: []
writes: [((2, 4), (2, 8))]""")

// -----------------------------------------------
// Interface
// -----------------------------------------------

let lspTests host =
  testDirEntries ()

  let code =
    [ testDocChange ()
      testRefs ()
      testHover ()
      testRename ()
      testDocumentSymbol ()
      testCodeAction ()
      testCompletion ()
      testFindProjects () ]
    |> List.collect id
    |> runTests

  if code = 0 then testDiagnostics host

  exit code
