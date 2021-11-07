module rec MiloneLspServer.LspUtil

open MiloneLspServer.Util
open MiloneStd.StdMap

// -----------------------------------------------
// Docs
// -----------------------------------------------

/// Text doc that is opened in editor.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type DocData =
  { /// Number to identify an edition of the document.
    Version: int
    Text: string }

type Docs = TreeMap<Uri, DocData>

module Docs =
  let empty: Docs = TMap.empty compare

  let find (uri: Uri) (docs: Docs) : DocData option =
    traceFn "Doc find uri:'%A'" (string uri)
    docs |> TMap.tryFind uri

  let add (uri: Uri) (version: int) (text: string) (docs: Docs) =
    let docData: DocData = { Version = version; Text = text }

    debugFn "Doc opened uri:'%A' v:%d len:%d" uri version text.Length
    docs |> TMap.add uri docData

  let update (uri: Uri) (version: int) (text: string) (docs: Docs) : Docs =
    let docData: DocData = { Version = version; Text = text }

    debugFn "Doc changed uri:'%A' v:%d len:%d" uri version text.Length
    docs |> TMap.add uri docData

  let remove (uri: Uri) (docs: Docs) : Docs =
    debugFn "Doc closed uri:'%A'" uri
    docs |> TMap.remove uri |> snd
