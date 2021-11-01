// FIXME: separate project
module rec MiloneLspServer.LspTests

open MiloneLspServer.Lsp

let private testPrintSyntaxTree () =
  let docId = "TestProject.Program"

  let docMap =
    let text =
      "module rec TestProject.Program\nlet main _ = 0\n"

    Map.ofList [ docId, (1, text) ]

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

  eprintfn "%s" (LangService.parse ls docId)

let lspTests () =
  eprintfn "Test mode."
  testPrintSyntaxTree ()
  exit 0
