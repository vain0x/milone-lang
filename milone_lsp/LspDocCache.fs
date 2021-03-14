module rec MiloneLsp.LspDocCache

open MiloneLsp.Util

/// Text doc that is opened in editor.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type DocData =
  {
    /// String to identify the document. E.g. `file:///home/owner/.../foo.milone`.
    Uri: string

    /// Number to identify an edition of the document.
    Version: int

    Text: string }

/// List of docs open in editor, keyed by URI.
let private docs = MutMap<string, DocData>()

let findDoc (uri: string) : DocData option =
  // eprintfn "INFO: Doc find uri:'%s'" uri

  match docs.TryGetValue(uri) with
  | true, docData -> Some docData
  | false, _ -> None

let openDoc (uri: string) (version: int) (text: string) =
  let docData : DocData =
    { Uri = uri
      Version = version
      Text = text }

  // eprintfn "INFO: Doc opened uri:'%s' v:%d len:%d" uri version text.Length
  docs.Add(uri, docData)

let changeDoc (uri: string) (version: int) (text: string) : unit =
  match findDoc uri with
  | Some _ ->
      let docData : DocData =
        { Uri = uri
          Version = version
          Text = text }

      docs.[uri] <- docData

  | None -> openDoc uri version text

let closeDoc (uri: string) : unit =
  // eprintfn "INFO: Doc closed uri:'%s'" uri
  docs.Remove(uri) |> ignore
