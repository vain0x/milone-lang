// FIXME: separate project
module rec MiloneLspServer.LspTests

open MiloneLspServer.Lsp

module S = MiloneStd.StdString

let private expect opt =
  match opt with
  | Some it -> it
  | None -> failwith "Expected some"

let private toLines (s: string) =
  s.TrimEnd().Replace("\r\n", "\n").Split("\n")
  |> Array.mapi (fun i item -> i, item)
  |> Array.toList

let private testReferencesRequest () =
  let projectDir = "./TestProject"
  let docId = "TestProject.TestProject"

  let text =
    """
      module rec TestProject.Program

      let main _ =
        let foo = 0
        //  ^def
        let _ = foo
        //      ^use
        0
    """

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
          | _ -> (0, "// Missing")

      GetProjectName = fun docId -> Some(docId.Split(".").[0]) }

  let host: Lsp.LangServiceHost =
    { MiloneHome = "?unexisting"
      Docs = docs }

  let ls = LangService.create host

  let lines = text |> toLines

  let anchors =
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

  let debug xs =
    xs
    |> List.sort
    |> List.map (fun (row, column, anchor) -> sprintf "%d:%d %s" row column anchor)
    |> S.concat "\n"

  let expected = anchors |> debug

  let actual =
    let row, column, _ = anchors |> List.tryHead |> expect

    match ls
          |> LangService.findRefs projectDir docId (row, column)
      with
    | None -> "No results."

    | Some (defs, uses) ->
      Seq.append (defs |> Seq.map (fun (_, (y, x)) -> y, x, "def")) (uses |> Seq.map (fun (_, (y, x)) -> y, x, "use"))
      |> Seq.toList
      |> debug

  if actual <> expected then
    eprintfn "actual = %s\nexpected = %s" actual expected
    assert (actual <> expected)

let lspTests () =
  eprintfn "Test mode."
  testReferencesRequest ()
  exit 0
