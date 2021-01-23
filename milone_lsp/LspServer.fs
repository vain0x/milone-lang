module MiloneLsp.LspServer

open System.Threading
open MiloneLsp.JsonValue
open MiloneLsp.JsonSerialization
open MiloneLsp.JsonRpcWriter
open MiloneLsp.Lsp

type Position = int * int

type Range = Position * Position

// -----------------------------------------------
// JSON helper
// -----------------------------------------------

let jOfInt (value: int): JsonValue = JNumber(float value)

let jOfObj (assoc: (string * JsonValue) list) = JObject(Map.ofList assoc)

let jOfPos (row: int, column: int): JsonValue =
  jOfObj [ "line", jOfInt row
           "character", jOfInt column ]

let jOfRange (start: Position, endValue: Position): JsonValue =
  jOfObj [ "start", jOfPos start
           "end", jOfPos endValue ]

let freshMsgId: unit -> int =
  let mutable lastId = 0

  fun () ->
    lastId <- lastId + 1
    lastId

let jAt index jsonValue: JsonValue =
  match jsonValue with
  | JArray list -> List.item index list

  | _ -> failwithf "Expected a list with index: %d; but was: '%s'" index (jsonDisplay jsonValue)

let jFind key jsonValue: JsonValue =
  match jsonValue with
  | JObject map ->
      match map |> Map.tryFind key with
      | Some value -> value

      | None -> failwithf "Missed key '%s' in object: '%s'" key (jsonDisplay jsonValue)

  | _ -> failwithf "Expected a map with key '%s'; but was '%s'" key (jsonDisplay jsonValue)

let jFind2 key1 key2 jsonValue: JsonValue = jsonValue |> jFind key1 |> jFind key2

let jFind3 key1 key2 key3 jsonValue: JsonValue =
  jsonValue
  |> jFind key1
  |> jFind key2
  |> jFind key3

let jFields2 key1 key2 jsonValue: JsonValue * JsonValue =
  jsonValue |> jFind key1, jsonValue |> jFind key2

let jFields3 key1 key2 key3 jsonValue: JsonValue * JsonValue * JsonValue =
  jsonValue |> jFind key1, jsonValue |> jFind key2, jsonValue |> jFind key3

let jToString jsonValue: string =
  match jsonValue with
  | JString value -> value

  | _ -> failwithf "Expected a string but: %s" (jsonDisplay jsonValue)

let jToNumber jsonValue: float =
  match jsonValue with
  | JNumber value -> value

  | _ -> failwithf "Expected a number but: %s" (jsonDisplay jsonValue)

let jToInt jsonValue: int = jsonValue |> jToNumber |> int

let jToBool jsonValue: bool =
  match jsonValue with
  | JBoolean value -> value
  | _ -> false

let jToPos jsonValue: Position =
  let row, column =
    jsonValue |> jFields2 "line" "character"

  jToInt row, jToInt column

let jToRange jsonValue: Range =
  let start, endPos = jsonValue |> jFields2 "start" "end"
  jToPos start, jToPos endPos

// MarkupContent
// let jOfMarkupContentAsMarkdown (text: string) =
//   jOfObj [ "kind", JString "markdown"
//            "value", JString text ]

let jOfMarkdownString (text: string) =
  jOfObj [ "language", JString "markdown"
           "value", JString text ]

// -----------------------------------------------
// LSP types
// -----------------------------------------------

type InitializeParam = { RootUriOpt: string option }

let parseInitializeParam jsonValue: InitializeParam =
  let rootUriOpt =
    try
      jsonValue
      |> jFind2 "params" "rootUri"
      |> jToString
      |> Some
    with _ -> None

  { RootUriOpt = rootUriOpt }

type DidOpenParam =
  { Uri: string
    Version: int
    Text: string }

let parseDidOpenParam jsonValue: DidOpenParam =
  let docParam =
    jsonValue |> jFind2 "params" "textDocument"

  let uri, version, text =
    docParam |> jFields3 "uri" "version" "text"

  let uri, version, text =
    jToString uri, jToInt version, jToString text

  { Uri = uri
    Version = version
    Text = text }

type DidChangeParam =
  { Uri: string
    Version: int
    Text: string }

let parseDidChangeParam jsonValue: DidChangeParam =
  let uri, version =
    let uri, version =
      jsonValue
      |> jFind2 "params" "textDocument"
      |> jFields2 "uri" "version"

    jToString uri, jToInt version

  let text =
    jsonValue
    |> jFind2 "params" "contentChanges"
    |> jAt 0
    |> jFind "text"
    |> jToString

  { Uri = uri
    Version = version
    Text = text }

type DidCloseParam = { Uri: string }

let parseDidCloseParam jsonValue: DidCloseParam =
  let uri =
    jsonValue
    |> jFind3 "params" "textDocument" "uri"
    |> jToString

  { Uri = uri }

type DocumentPositionParam = { Uri: string; Pos: Pos }

let parseDocumentPositionParam jsonValue: DocumentPositionParam =
  let uri =
    jsonValue
    |> jFind3 "params" "textDocument" "uri"
    |> jToString

  let pos =
    jsonValue |> jFind2 "params" "position" |> jToPos

  { Uri = uri; Pos = pos }

type ReferencesParam =
  { Uri: string
    Pos: Pos
    IncludeDecl: bool }

let parseReferencesParam jsonValue: ReferencesParam =
  let uri, pos =
    let p = parseDocumentPositionParam jsonValue
    p.Uri, p.Pos

  let includeDecl =
    jsonValue
    |> jFind3 "params" "context" "includeDeclaration"
    |> jToBool

  { Uri = uri
    Pos = pos
    IncludeDecl = includeDecl }

// -----------------------------------------------
// Server
// -----------------------------------------------

type LspServerHost =
  { DrainRequests: unit -> JsonValue list }

let lspServer (host: LspServerHost): Async<int> =
  async {
    let freshMsgId () = freshMsgId () |> jOfInt

    let mutable exitCode = 1
    let mutable rootUriOpt: string option = None

    let doPublishDiagnostics (uri: string) (errors: (string * int * int * int * int) list): unit =
      let diagnostics =
        errors
        |> List.map
             (fun (msg, r1, c1, r2, c2) ->
               let start = r1, c1
               let endPos = r2, c2

               jOfObj [ "range", jOfRange (start, endPos)
                        "message", JString msg
                        "source", JString "milone-lang" ])
        |> JArray

      let paramsValue =
        jOfObj [ "uri", JString uri
                 "diagnostics", diagnostics ]

      jsonRpcWriteWithParams "textDocument/publishDiagnostics" paramsValue

    // let validateDoc (uri: string): unit =
    //   let errors =
    //     LspLangService.validateDoc uri
    //     |> List.map (fun (msg, (row, column)) -> msg, row, column, row, column)

    //   doPublishDiagnostics uri errors

    let validateWorkspace (): unit =
      for uri, errors in LspLangService.validateWorkspace rootUriOpt do
        let errors =
          [ for msg, pos in errors do
              let row, column = pos
              yield msg, row, column, row, column ]

        doPublishDiagnostics uri errors

    // <https://microsoft.github.io/language-server-protocol/specifications/specification-current/#textDocument_documentHighlight>
    let documentHighlight uri pos: JsonValue =
      let reads, writes =
        LspLangService.documentHighlight rootUriOpt uri pos

      let toHighlights kind posList =
        posList
        |> Seq.map
             (fun (start, endPos) ->
               jOfObj [ "range", jOfRange (start, endPos)
                        "kind", jOfInt kind ])

      JArray [ yield! toHighlights 2 reads
               yield! toHighlights 3 writes ]

    // https://microsoft.github.io/language-server-protocol/specifications/specification-current/#textDocument_hover
    let hover uri pos: JsonValue =
      let contents = LspLangService.hover rootUriOpt uri pos

      match contents with
      | [] -> JNull
      | _ ->
          jOfObj [ "contents", contents |> List.map jOfMarkdownString |> JArray
                   //  "range", jOfRange range
                    ]

    let onRequest jsonValue =
      // eprintfn "received %A" jsonValue
      let getMsgId () = jsonValue |> jFind "id"

      match jsonValue |> jFind "method" |> jToString with
      | "initialize" ->
          let p = parseInitializeParam jsonValue
          rootUriOpt <- p.RootUriOpt

          eprintfn "rootUriOpt = %A" rootUriOpt

          let result =
            jsonDeserializeString
              """{
              "capabilities": {
                  "textDocumentSync": {
                      "openClose": true,
                      "change": 1
                  },
                  "definitionProvider": true,
                  "documentHighlightProvider": true,
                  "hoverProvider": true,
                  "referencesProvider": true,
                  "renameProvider": false
              },
              "serverInfo": {
                  "name": "milone_lsp",
                  "version": "0.1.0"
              }
            }"""

          jsonRpcWriteWithResult (getMsgId ()) result
          None

      | "initialized" ->
          validateWorkspace ()
          None

      | "shutdown" ->
          exitCode <- 0
          jsonRpcWriteWithResult (getMsgId ()) JNull
          None

      | "exit" -> Some exitCode

      | "textDocument/didOpen" ->
          let uri, version, text =
            let p = parseDidOpenParam jsonValue
            p.Uri, p.Version, p.Text

          LspDocCache.openDoc uri version text
          // validateDoc uri
          validateWorkspace ()
          None

      | "textDocument/didChange" ->
          let uri, version, text =
            let p = parseDidChangeParam jsonValue
            p.Uri, p.Version, p.Text

          LspDocCache.changeDoc uri version text
          // validateDoc uri
          validateWorkspace ()
          None

      | "textDocument/didClose" ->
          let uri =
            let p = parseDidCloseParam jsonValue
            p.Uri

          LspDocCache.closeDoc uri
          validateWorkspace ()
          None

      | "textDocument/documentHighlight" ->
          let uri, pos =
            let p = parseDocumentPositionParam jsonValue
            p.Uri, p.Pos

          let result = documentHighlight uri pos
          jsonRpcWriteWithResult (getMsgId ()) result
          None

      | "textDocument/hover" ->
          let uri, pos =
            let p = parseDocumentPositionParam jsonValue
            p.Uri, p.Pos

          let result = hover uri pos
          jsonRpcWriteWithResult (getMsgId ()) result
          None

      | "textDocument/definition" ->
          // <https://microsoft.github.io/language-server-protocol/specifications/specification-current/#textDocument_definition>

          let uri, pos =
            let p = parseDocumentPositionParam jsonValue
            p.Uri, p.Pos

          let result =
            LspLangService.definition rootUriOpt uri pos
            |> List.map
                 (fun (docId, range) ->
                   jOfObj [ "uri", JString docId
                            "range", jOfRange range ])
            |> JArray

          jsonRpcWriteWithResult (getMsgId ()) result
          None

      | "textDocument/references" ->
          // <https://microsoft.github.io/language-server-protocol/specifications/specification-current/#textDocument_references>

          let uri, pos, includeDecl =
            let p = parseReferencesParam jsonValue
            p.Uri, p.Pos, p.IncludeDecl

          let result =
            LspLangService.references rootUriOpt uri pos includeDecl
            |> List.map
                 (fun (docId, range) ->
                   jOfObj [ "uri", JString docId
                            "range", jOfRange range ])
            |> JArray

          jsonRpcWriteWithResult (getMsgId ()) result
          None

      | methodName ->
          eprintfn "unknown method '%s'" methodName
          None

    let rec go requests =
      async {
        match requests with
        | [] -> return! go (host.DrainRequests())

        | r :: requests ->
            match onRequest r with
            | Some it -> return it
            | None -> return! go requests
      }

    return! go []
  }
