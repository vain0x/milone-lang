module rec MiloneLspServer.LspDocCache

open MiloneLspServer.Util

/// Text doc that is opened in editor.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type DocData =
  {
    /// String to identify the document. E.g. `file:///home/owner/.../foo.milone`.
    Uri: Uri

    /// Number to identify an edition of the document.
    Version: int

    Text: string }

/// List of docs open in editor, keyed by URI.
let private docs = MutMap<Uri, DocData>()

let findDoc (uri: Uri) : DocData option =
  traceFn "Doc find uri:'%A'" (string uri)

  match docs.TryGetValue(uri) with
  | true, docData -> Some docData
  | false, _ -> None

let openDoc (uri: Uri) (version: int) (text: string) =
  let docData: DocData =
    { Uri = uri
      Version = version
      Text = text }

  debugFn "Doc opened uri:'%A' v:%d len:%d" uri version text.Length
  docs.Add(uri, docData)

let changeDoc (uri: Uri) (version: int) (text: string) : unit =
  match findDoc uri with
  | Some _ ->
    let docData: DocData =
      { Uri = uri
        Version = version
        Text = text }

    docs.[uri] <- docData

  | None -> openDoc uri version text

let closeDoc (uri: Uri) : unit =
  debugFn "Doc closed uri:'%A'" uri
  docs.Remove(uri) |> ignore
