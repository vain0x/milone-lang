module MiloneLsp.LspServer

open System.Threading
open MiloneLsp.JsonValue
open MiloneLsp.JsonSerialization
open MiloneLsp.JsonRpcWriter
open MiloneLsp.Lsp

type private Position = int * int

type private Range = Position * Position

// -----------------------------------------------
// JSON helper
// -----------------------------------------------

let private jOfInt (value: int): JsonValue = JNumber(float value)

let private jOfObj (assoc: (string * JsonValue) list) = JObject(Map.ofList assoc)

let private jOfPos (row: int, column: int): JsonValue =
  jOfObj [ "line", jOfInt row
           "character", jOfInt column ]

let private jOfRange (start: Position, endValue: Position): JsonValue =
  jOfObj [ "start", jOfPos start
           "end", jOfPos endValue ]

let private jAt index jsonValue: JsonValue =
  match jsonValue with
  | JArray list -> List.item index list

  | _ -> failwithf "Expected a list with index: %d; but was: '%s'" index (jsonDisplay jsonValue)

let private jTryFind key jsonValue: JsonValue option =
  match jsonValue with
  | JObject map -> Map.tryFind key map
  | _ -> None

let private jFind key jsonValue: JsonValue =
  match jsonValue with
  | JObject map ->
      match map |> Map.tryFind key with
      | Some value -> value

      | None -> failwithf "Missed key '%s' in object: '%s'" key (jsonDisplay jsonValue)

  | _ -> failwithf "Expected a map with key '%s'; but was '%s'" key (jsonDisplay jsonValue)

let private jFind2 key1 key2 jsonValue: JsonValue = jsonValue |> jFind key1 |> jFind key2

let private jFind3 key1 key2 key3 jsonValue: JsonValue =
  jsonValue
  |> jFind key1
  |> jFind key2
  |> jFind key3

let private jFields2 key1 key2 jsonValue: JsonValue * JsonValue =
  jsonValue |> jFind key1, jsonValue |> jFind key2

let private jFields3 key1 key2 key3 jsonValue: JsonValue * JsonValue * JsonValue =
  jsonValue |> jFind key1, jsonValue |> jFind key2, jsonValue |> jFind key3

let private jToString jsonValue: string =
  match jsonValue with
  | JString value -> value

  | _ -> failwithf "Expected a string but: %s" (jsonDisplay jsonValue)

let private jToNumber jsonValue: float =
  match jsonValue with
  | JNumber value -> value

  | _ -> failwithf "Expected a number but: %s" (jsonDisplay jsonValue)

let private jToInt jsonValue: int = jsonValue |> jToNumber |> int

let private jToBool jsonValue: bool =
  match jsonValue with
  | JBoolean value -> value
  | _ -> false

let private jToPos jsonValue: Position =
  let row, column =
    jsonValue |> jFields2 "line" "character"

  jToInt row, jToInt column

let private jToRange jsonValue: Range =
  let start, endPos = jsonValue |> jFields2 "start" "end"
  jToPos start, jToPos endPos

// MarkupContent
// let jOfMarkupContentAsMarkdown (text: string) =
//   jOfObj [ "kind", JString "markdown"
//            "value", JString text ]

let private jOfMarkdownString (text: string) =
  jOfObj [ "language", JString "markdown"
           "value", JString text ]

// -----------------------------------------------
// LSP types
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private InitializeParam = { RootUriOpt: string option }

let private parseInitializeParam jsonValue: InitializeParam =
  let rootUriOpt =
    try
      jsonValue
      |> jFind2 "params" "rootUri"
      |> jToString
      |> Some
    with _ -> None

  { RootUriOpt = rootUriOpt }

let private createInitializeResult () =
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

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private DidOpenParam =
  { Uri: string
    Version: int
    Text: string }

let private parseDidOpenParam jsonValue: DidOpenParam =
  let docParam =
    jsonValue |> jFind2 "params" "textDocument"

  let uri, version, text =
    docParam |> jFields3 "uri" "version" "text"

  let uri, version, text =
    jToString uri, jToInt version, jToString text

  { Uri = uri
    Version = version
    Text = text }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private DidChangeParam =
  { Uri: string
    Version: int
    Text: string }

let private parseDidChangeParam jsonValue: DidChangeParam =
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

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private DidCloseParam = { Uri: string }

let private parseDidCloseParam jsonValue: DidCloseParam =
  let uri =
    jsonValue
    |> jFind3 "params" "textDocument" "uri"
    |> jToString

  { Uri = uri }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private DocumentPositionParam = { Uri: string; Pos: Pos }

let private parseDocumentPositionParam jsonValue: DocumentPositionParam =
  let uri =
    jsonValue
    |> jFind3 "params" "textDocument" "uri"
    |> jToString

  let pos =
    jsonValue |> jFind2 "params" "position" |> jToPos

  { Uri = uri; Pos = pos }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private ReferencesParam =
  { Uri: string
    Pos: Pos
    IncludeDecl: bool }

let private parseReferencesParam jsonValue: ReferencesParam =
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
// LspError
// -----------------------------------------------

type private MsgId = JsonValue

[<NoEquality; NoComparison>]
type private LspError =
  | CancelledRequestError of msgId: MsgId
  | MethodNotFoundError of msgId: MsgId

// -----------------------------------------------
// LspIncome
// -----------------------------------------------

/// Incoming message.
[<NoEquality; NoComparison>]
type private LspIncome =
  // Initialize/shutdown messages.
  | InitializeRequest of MsgId * InitializeParam
  | InitializedNotification
  | ShutdownRequest of MsgId
  | ExitNotification

  // Document changes.
  | DidOpenNotification of DidOpenParam
  | DidChangeNotification of DidChangeParam
  | DidCloseNotification of DidCloseParam

  // Queries.
  | DiagnosticsRequest
  | DefinitionRequest of MsgId * DocumentPositionParam
  | ReferencesRequest of MsgId * ReferencesParam
  | DocumentHighlightRequest of MsgId * DocumentPositionParam
  | HoverRequest of MsgId * DocumentPositionParam

  // Others.
  | CancelRequestNotification of MsgId
  | ErrorIncome of LspError

[<NoEquality; NoComparison>]
type private ProcessResult =
  | Continue
  | Exit of exitCode: int

let private parseIncome (jsonValue: JsonValue): LspIncome =
  let getMsgId () = jsonValue |> jFind "id"

  let methodName = jsonValue |> jFind "method" |> jToString

  match methodName with
  | "initialize" -> InitializeRequest(getMsgId (), parseInitializeParam jsonValue)
  | "initialized" -> InitializedNotification
  | "shutdown" -> ShutdownRequest(getMsgId ())
  | "exit" -> ExitNotification

  | "textDocument/didOpen" -> DidOpenNotification(parseDidOpenParam jsonValue)
  | "textDocument/didChange" -> DidChangeNotification(parseDidChangeParam jsonValue)
  | "textDocument/didClose" -> DidCloseNotification(parseDidCloseParam jsonValue)

  | "textDocument/definition" -> DefinitionRequest(getMsgId (), parseDocumentPositionParam jsonValue)
  | "textDocument/references" -> ReferencesRequest(getMsgId (), parseReferencesParam jsonValue)
  | "textDocument/documentHighlight" -> DocumentHighlightRequest(getMsgId (), parseDocumentPositionParam jsonValue)
  | "textDocument/hover" -> HoverRequest(getMsgId (), parseDocumentPositionParam jsonValue)

  | "$/cancelRequest" -> CancelRequestNotification(jsonValue |> jFind2 "params" "id")

  | methodName ->
      eprintfn "[TRACE] Unknown methodName: '%s'." methodName

      let msgId =
        jsonValue
        |> jTryFind "id"
        |> Option.defaultValue JNull

      ErrorIncome(MethodNotFoundError msgId)

let private doPublishDiagnostics (uri: string) (errors: (string * int * int * int * int) list): unit =
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

let private validateWorkspace (rootUriOpt: string option): unit =
  for uri, errors in LspLangService.validateWorkspace rootUriOpt do
    let errors =
      [ for msg, pos in errors do
          let row, column = pos
          yield msg, row, column, row, column ]

    doPublishDiagnostics uri errors

let private processNext (): LspIncome -> ProcessResult =
  let mutable exitCode: int = 1
  let mutable rootUriOpt: string option = None

  fun (income: LspIncome) ->
    match income with
    | InitializeRequest (msgId, param) ->
        rootUriOpt <- param.RootUriOpt
        // eprintfn "rootUriOpt = %A" rootUriOpt

        let result = createInitializeResult ()
        jsonRpcWriteWithResult msgId result
        Continue

    | InitializedNotification -> Continue

    | ShutdownRequest msgId ->
        exitCode <- 0
        jsonRpcWriteWithResult msgId JNull
        Continue

    | ExitNotification -> Exit exitCode

    | DidOpenNotification p ->
        let uri, version, text = p.Uri, p.Version, p.Text

        LspDocCache.openDoc uri version text
        Continue

    | DidChangeNotification p ->
        let uri, version, text = p.Uri, p.Version, p.Text

        LspDocCache.changeDoc uri version text
        Continue

    | DidCloseNotification p ->
        let uri = p.Uri

        LspDocCache.closeDoc uri
        Continue

    | DiagnosticsRequest ->
        validateWorkspace rootUriOpt
        Continue

    | DefinitionRequest (msgId, p) ->
        // <https://microsoft.github.io/language-server-protocol/specifications/specification-current/#textDocument_definition>

        let uri, pos = p.Uri, p.Pos

        let result =
          LspLangService.definition rootUriOpt uri pos
          |> List.map
               (fun (docId, range) ->
                 jOfObj [ "uri", JString docId
                          "range", jOfRange range ])
          |> JArray

        jsonRpcWriteWithResult msgId result
        Continue

    | ReferencesRequest (msgId, p) ->
        // <https://microsoft.github.io/language-server-protocol/specifications/specification-current/#textDocument_references>

        let uri, pos, includeDecl = p.Uri, p.Pos, p.IncludeDecl

        let result =
          LspLangService.references rootUriOpt uri pos includeDecl
          |> List.map
               (fun (docId, range) ->
                 jOfObj [ "uri", JString docId
                          "range", jOfRange range ])
          |> JArray

        jsonRpcWriteWithResult msgId result
        Continue

    | DocumentHighlightRequest (msgId, p) ->
        // <https://microsoft.github.io/language-server-protocol/specifications/specification-current/#textDocument_documentHighlight>

        let uri, pos = p.Uri, p.Pos

        let reads, writes =
          LspLangService.documentHighlight rootUriOpt uri pos

        let toHighlights kind posList =
          posList
          |> Seq.map
               (fun (start, endPos) ->
                 jOfObj [ "range", jOfRange (start, endPos)
                          "kind", jOfInt kind ])

        let result =
          JArray [ yield! toHighlights 2 reads
                   yield! toHighlights 3 writes ]

        jsonRpcWriteWithResult msgId result
        Continue

    | HoverRequest (msgId, p) ->
        // https://microsoft.github.io/language-server-protocol/specifications/specification-current/#textDocument_hover

        let uri, pos = p.Uri, p.Pos

        let contents = LspLangService.hover rootUriOpt uri pos

        let result =
          match contents with
          | [] -> JNull
          | _ ->
              jOfObj [ "contents", contents |> List.map jOfMarkdownString |> JArray
                       // "range", jOfRange range
                        ]

        jsonRpcWriteWithResult msgId result
        Continue

    | CancelRequestNotification _ -> Continue

    | ErrorIncome error ->
        let methodNotFoundCode = -32601
        let requestCancelledCode = -32800

        match error with
        | CancelledRequestError msgId ->
            let error =
              jOfObj [ "code", jOfInt requestCancelledCode
                       "message", JString "Request is cancelled." ]

            jsonRpcWriteWithError msgId error
            Continue

        | MethodNotFoundError msgId ->
            let error =
              jOfObj [ "code", jOfInt methodNotFoundCode
                       "message", JString "Unknown method." ]

            jsonRpcWriteWithError msgId error
            Continue

// -----------------------------------------------
// Request preprocess
// -----------------------------------------------

let private preprocess (incomes: LspIncome list): LspIncome list =
  let doesUpdateDiagnostics income =
    match income with
    | InitializedNotification _
    | DidOpenNotification _
    | DidChangeNotification _
    | DidCloseNotification _ -> true

    | _ -> false

  // Add diagnostics request if some document changed.
  let incomes =
    if incomes |> List.exists doesUpdateDiagnostics then
      List.append incomes [ DiagnosticsRequest ]
    else
      incomes

  // Replace request and cancellation with cancellation error.
  let incomes =
    let asCancelRequest income =
      match income with
      | CancelRequestNotification msgId -> Some msgId
      | _ -> None

    let asMsgId income =
      match income with
      | DefinitionRequest (msgId, _)
      | ReferencesRequest (msgId, _)
      | DocumentHighlightRequest (msgId, _)
      | HoverRequest (msgId, _) -> Some msgId

      | _ -> None

    let cancelledIds =
      incomes
      |> List.choose asCancelRequest
      |> Set.ofList

    if Set.isEmpty cancelledIds then
      incomes
    else
      incomes
      |> List.choose
           (fun income ->
             if income |> asCancelRequest |> Option.isSome then
               None
             else
               match asMsgId income with
               | Some msgId when Set.contains msgId cancelledIds -> ErrorIncome(CancelledRequestError msgId) |> Some

               | _ -> Some income)

  incomes

// -----------------------------------------------
// Server
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type LspServerHost =
  { DrainRequests: unit -> JsonValue list }

let lspServer (host: LspServerHost): Async<int> =
  async {
    let onRequest = processNext ()

    let rec go incomes =
      async {
        match incomes with
        | [] ->
            let incomes =
              host.DrainRequests()
              |> List.map parseIncome
              |> preprocess

            return! go incomes

        | income :: incomes ->
            // eprintfn "[TRACE] process %A" income

            match onRequest income with
            | Exit it -> return it
            | Continue -> return! go incomes
      }

    return! go []
  }
