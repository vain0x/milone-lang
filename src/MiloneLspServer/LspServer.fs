module MiloneLspServer.LspServer

open System.Collections.Concurrent
open System.Threading
open MiloneLspServer.JsonValue
open MiloneLspServer.JsonSerialization
open MiloneLspServer.JsonRpcWriter
open MiloneLspServer.LspUtil
open MiloneLspServer.Util

module WorkspaceAnalysis = LspLangService.WorkspaceAnalysis

/// Column index of text. (0-origin. This needs to be computed in UTF-16.)
type private LColumnIndex = int

/// Position of text. (This type is defined in LSP specification.)
type private LPosition = RowIndex * LColumnIndex

/// Range of text. (This type is defined in LSP specification.)
type private LRange = LPosition * LPosition

/// Edit to delete a range and replace it with a text.
type private LTextEdit = LRange * string

// -----------------------------------------------
// JSON helper
// -----------------------------------------------

let private jOfInt (value: int) : JsonValue = JNumber(float value)

let private jOfObj (assoc: (string * JsonValue) list) = JObject(Map.ofList assoc)

let private jOfPos (pos: LPosition) : JsonValue =
  let row, column = pos

  jOfObj [ "line", jOfInt row
           "character", jOfInt column ]

let private jOfRange (range: LRange) : JsonValue =
  let start, endValue = range

  jOfObj [ "start", jOfPos start
           "end", jOfPos endValue ]

let private jAt index jsonValue : JsonValue =
  match jsonValue with
  | JArray list -> List.item index list

  | _ -> failwithf "Expected a list with index: %d; but was: '%s'" index (jsonDisplay jsonValue)

let private jTryFind key jsonValue : JsonValue option =
  match jsonValue with
  | JObject map -> Map.tryFind key map
  | _ -> None

let private jFind key jsonValue : JsonValue =
  match jsonValue with
  | JObject map ->
    match map |> Map.tryFind key with
    | Some value -> value

    | None -> failwithf "Missed key '%s' in object: '%s'" key (jsonDisplay jsonValue)

  | _ -> failwithf "Expected a map with key '%s'; but was '%s'" key (jsonDisplay jsonValue)

let private jFind2 key1 key2 jsonValue : JsonValue = jsonValue |> jFind key1 |> jFind key2

let private jFind3 key1 key2 key3 jsonValue : JsonValue =
  jsonValue
  |> jFind key1
  |> jFind key2
  |> jFind key3

let private jFields2 key1 key2 jsonValue : JsonValue * JsonValue =
  jsonValue |> jFind key1, jsonValue |> jFind key2

let private jFields3 key1 key2 key3 jsonValue : JsonValue * JsonValue * JsonValue =
  jsonValue |> jFind key1, jsonValue |> jFind key2, jsonValue |> jFind key3

let private jToString jsonValue : string =
  match jsonValue with
  | JString value -> value

  | _ -> failwithf "Expected a string but: %s" (jsonDisplay jsonValue)

let private jToNumber jsonValue : float =
  match jsonValue with
  | JNumber value -> value

  | _ -> failwithf "Expected a number but: %s" (jsonDisplay jsonValue)

let private jToInt jsonValue : int = jsonValue |> jToNumber |> int

let private jToBool jsonValue : bool =
  match jsonValue with
  | JBoolean value -> value
  | _ -> false

let private jToArray jsonValue : JsonValue list =
  match jsonValue with
  | JArray items -> items

  | _ -> failwithf "Expected an array but: %s" (jsonDisplay jsonValue)

let private jArrayOrNull items =
  if items |> List.isEmpty |> not then
    JArray items
  else
    JNull

let private jToPos jsonValue : LPosition =
  let row, column =
    jsonValue |> jFields2 "line" "character"

  jToInt row, jToInt column

let private jToRange jsonValue : LRange =
  let start, endPos = jsonValue |> jFields2 "start" "end"
  jToPos start, jToPos endPos

// MarkupContent
// let jOfMarkupContentAsMarkdown (text: string) =
//   jOfObj [ "kind", JString "markdown"
//            "value", JString text ]

let private jOfMarkdownString (text: string) =
  jOfObj [ "language", JString "markdown"
           "value", JString text ]

let private jTextEdit (edit: LTextEdit) =
  let range, newText = edit

  jOfObj [ "range", jOfRange range
           "newText", JString newText ]

let private jWorkspaceEdit changes =
  let changes =
    changes
    |> List.map (fun (uri, edits) -> Uri.toString uri, edits |> List.map jTextEdit |> JArray)

  jOfObj [ "changes", jOfObj changes ]

// -----------------------------------------------
// LSP types
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private InitializeParam = { RootUriOpt: Uri option }

let private parseInitializeParam jsonValue : InitializeParam =
  let rootUriOpt =
    try
      jsonValue
      |> jFind2 "params" "rootUri"
      |> jToString
      |> Uri
      |> Some
    with
    | _ -> None

  { RootUriOpt = rootUriOpt }

let private createInitializeResult () =
  jsonDeserializeString
    """{
      "capabilities": {
          "textDocumentSync": {
              "openClose": true,
              "change": 1
          },
          "codeActionProvider": true,
          "completionProvider": {
            "triggerCharacters": ["."]
          },
          "definitionProvider": true,
          "documentFormattingProvider": true,
          "documentHighlightProvider": true,
          "documentSymbolProvider": true,
          "hoverProvider": true,
          "referencesProvider": true,
          "renameProvider": { "prepareProvider": true }
      },
      "serverInfo": {
          "name": "milone_lsp",
          "version": "0.1.0"
      }
    }"""

let private getUriParam jsonValue : Uri =
  jsonValue
  |> jFind3 "params" "textDocument" "uri"
  |> jToString
  |> Uri

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private DidOpenParam =
  { Uri: Uri
    Version: int
    Text: string }

let private parseDidOpenParam jsonValue : DidOpenParam =
  let docParam =
    jsonValue |> jFind2 "params" "textDocument"

  let uri, version, text =
    docParam |> jFields3 "uri" "version" "text"

  let uri, version, text =
    Uri(jToString uri), jToInt version, jToString text

  { Uri = uri
    Version = version
    Text = text }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private DidChangeParam =
  { Uri: Uri
    Version: int
    Text: string }

let private parseDidChangeParam jsonValue : DidChangeParam =
  let uri, version =
    let uri, version =
      jsonValue
      |> jFind2 "params" "textDocument"
      |> jFields2 "uri" "version"

    Uri(jToString uri), jToInt version

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
type private DidCloseParam = { Uri: Uri }

let private parseDidCloseParam jsonValue : DidCloseParam =
  let uri =
    jsonValue
    |> jFind3 "params" "textDocument" "uri"
    |> jToString
    |> Uri

  { Uri = uri }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private FileChangeType =
  | Created
  | Changed
  | Deleted

let private jToFileChangeType jsonValue =
  match jsonValue |> jToNumber |> int with
  | 1 -> FileChangeType.Created
  | 2 -> FileChangeType.Changed
  | 3 -> FileChangeType.Deleted
  | _ -> failwithf "Invalid FileChangeType: %A." jsonValue

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private FileEvent = { Uri: Uri; Type: FileChangeType }

let private jToFileEvent jsonValue : FileEvent =
  let uri, ty = jFields2 "uri" "type" jsonValue
  let uri = uri |> jToString |> Uri
  let ty = jToFileChangeType ty

  { Uri = uri; Type = ty }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private DidChangeWatchedFilesParam = { Changes: FileEvent list }

let private parseDidChangeWatchedFilesParam jsonValue : DidChangeWatchedFilesParam =
  let changes =
    jsonValue
    |> jFind2 "params" "changes"
    |> jToArray
    |> List.map jToFileEvent

  { Changes = changes }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private DocumentPositionParam = { Uri: Uri; Pos: LPosition }

let private parseDocumentPositionParam jsonValue : DocumentPositionParam =
  let uri =
    jsonValue
    |> jFind3 "params" "textDocument" "uri"
    |> jToString
    |> Uri

  let pos =
    jsonValue |> jFind2 "params" "position" |> jToPos

  { Uri = uri; Pos = pos }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private DocumentRangeParam = { Uri: Uri; Range: LRange }

let private parseDocumentRangeParam jsonValue : DocumentRangeParam =
  let uri =
    jsonValue
    |> jFind3 "params" "textDocument" "uri"
    |> jToString
    |> Uri

  let range =
    jsonValue |> jFind2 "params" "range" |> jToRange

  { Uri = uri; Range = range }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private ReferencesParam =
  { Uri: Uri
    Pos: LPosition
    IncludeDecl: bool }

let private parseReferencesParam jsonValue : ReferencesParam =
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

let private parseDocumentSymbolParam jsonValue =
  jsonValue
  |> jFind3 "params" "textDocument" "uri"
  |> jToString
  |> Uri

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private RenameParam =
  { Uri: Uri
    Pos: LPosition
    NewName: string }

let private parseRenameParam jsonValue : RenameParam =
  let p = parseDocumentPositionParam jsonValue

  let newName =
    jsonValue
    |> jFind2 "params" "newName"
    |> jToString

  { Uri = p.Uri
    Pos = p.Pos
    NewName = newName }

// -----------------------------------------------
// LspError
// -----------------------------------------------

type private MsgId = JsonValue

[<NoEquality; NoComparison>]
type private LspError =
  | CancelledRequestError of msgId: MsgId
  | MethodNotFoundError of msgId: MsgId * methodName: string

// -----------------------------------------------
// LSP misc
// -----------------------------------------------

let private handleRequestError (hint: string) (msgId: JsonValue) (ex: exn) : unit =
  errorFn "%s failed: %A" hint ex

  let msg = sprintf "%s failed (%s)" hint ex.Message

  let error =
    let internalErrorCode = -32603

    jOfObj [ "code", jOfInt internalErrorCode
             "message", JString msg ]

  jsonRpcWriteWithError msgId error

// For when server received a notification and caused an error.
let private showErrorMessage (msg: string) : unit =
  let p =
    jOfObj [ "type", jOfInt 1 // error
             "message", JString msg ]

  jsonRpcWriteWithParams "window/showMessage" p

let private handleNotificationError (hint: string) (ex: exn) : unit =
  errorFn "%s failed: %A" hint ex
  let msg = sprintf "%s failed (%s)" hint ex.Message
  showErrorMessage msg

/// To handle a request, performs an action.
/// If an exception is thrown during the process, send an error response.
let private handleRequestWith hint msgId action : unit =
  let result =
    try
      Ok(action ())
    with
    | ex -> Error ex

  match result with
  | Ok result -> jsonRpcWriteWithResult msgId result
  | Error ex -> handleRequestError hint msgId ex

// To handle an notification, performs an action.
// If an exception is thrown, reports an error.
// Gracefully completed, calls `cont` to send successful messages.
//
// - If handler doesn't send any message on success, pass `id` as `cont` parameter.
let private handleNotificationWith hint action cont : unit =
  let result =
    try
      Ok(action ())
    with
    | ex -> Error ex

  match result with
  | Ok result -> cont result
  | Error ex -> handleNotificationError hint ex

// -----------------------------------------------
// LspIncome
// -----------------------------------------------

/// Incoming message.
[<NoEquality; NoComparison>]
type LspIncome =
  private
  // Initialize/shutdown messages.
  | InitializeRequest of MsgId * InitializeParam
  | InitializedNotification
  | ShutdownRequest of MsgId
  | ExitNotification

  // Document changes.
  | DidOpenNotification of DidOpenParam
  | DidChangeNotification of DidChangeParam
  | DidCloseNotification of DidCloseParam
  | DidChangeWatchedFiles of DidChangeWatchedFilesParam

  // Queries.
  /// Notification to update diagnostics.
  /// This notification is NOT sent by LSP client but is generated inside the server
  /// whenever server receives a kind of requests that invalidate previous diagnostics.
  | DiagnosticsNotification
  | CodeActionRequest of MsgId * DocumentRangeParam
  | CompletionRequest of MsgId * DocumentPositionParam
  /// https://microsoft.github.io/language-server-protocol/specifications/specification-current/#textDocument_definition
  | DefinitionRequest of MsgId * DocumentPositionParam
  /// https://microsoft.github.io/language-server-protocol/specifications/specification-current/#textDocument_references
  | ReferencesRequest of MsgId * ReferencesParam
  /// https://microsoft.github.io/language-server-protocol/specifications/specification-current/#tetDocument_documentHighlight
  | DocumentHighlightRequest of MsgId * DocumentPositionParam
  | DocumentSymbolRequest of MsgId * Uri
  /// https://microsoft.github.io/language-server-protocol/specifications/specification-current/#textDocument_formatting
  | FormattingRequest of MsgId * Uri
  /// https://microsoft.github.io/language-server-protocol/specifications/specification-current/#textDocument_hover
  | HoverRequest of MsgId * DocumentPositionParam
  | PrepareRenameRequest of MsgId * DocumentPositionParam
  | RenameRequest of MsgId * RenameParam

  // Others.
  | RegisterCapabilityResponse of MsgId
  | CancelRequestNotification of MsgId
  | ErrorIncome of LspError

[<NoEquality; NoComparison>]
type ProcessResult =
  | Continue
  | Exit of exitCode: int

let parseIncome (jsonValue: JsonValue) : LspIncome =
  let getMsgId () = jsonValue |> jFind "id"

  let methodName =
    jsonValue
    |> jTryFind "method"
    |> Option.map jToString
    |> Option.defaultValue "$/response"

  match methodName with
  | "initialize" -> InitializeRequest(getMsgId (), parseInitializeParam jsonValue)
  | "initialized" -> InitializedNotification
  | "shutdown" -> ShutdownRequest(getMsgId ())
  | "exit" -> ExitNotification

  | "textDocument/didOpen" -> DidOpenNotification(parseDidOpenParam jsonValue)
  | "textDocument/didChange" -> DidChangeNotification(parseDidChangeParam jsonValue)
  | "textDocument/didClose" -> DidCloseNotification(parseDidCloseParam jsonValue)
  | "workspace/didChangeWatchedFiles" -> DidChangeWatchedFiles(parseDidChangeWatchedFilesParam jsonValue)

  | "textDocument/codeAction" -> CodeActionRequest(getMsgId (), parseDocumentRangeParam jsonValue)
  | "textDocument/completion" -> CompletionRequest(getMsgId (), parseDocumentPositionParam jsonValue)
  | "textDocument/definition" -> DefinitionRequest(getMsgId (), parseDocumentPositionParam jsonValue)
  | "textDocument/references" -> ReferencesRequest(getMsgId (), parseReferencesParam jsonValue)
  | "textDocument/documentHighlight" -> DocumentHighlightRequest(getMsgId (), parseDocumentPositionParam jsonValue)
  | "textDocument/documentSymbol" -> DocumentSymbolRequest(getMsgId (), parseDocumentSymbolParam jsonValue)
  | "textDocument/formatting" -> FormattingRequest(getMsgId (), getUriParam jsonValue)
  | "textDocument/hover" -> HoverRequest(getMsgId (), parseDocumentPositionParam jsonValue)
  | "textDocument/prepareRename" -> PrepareRenameRequest(getMsgId (), parseDocumentPositionParam jsonValue)
  | "textDocument/rename" -> RenameRequest(getMsgId (), parseRenameParam jsonValue)

  | "$/response" -> RegisterCapabilityResponse(getMsgId ())
  | "$/cancelRequest" -> CancelRequestNotification(jsonValue |> jFind2 "params" "id")

  | methodName ->
    let msgId =
      jsonValue
      |> jTryFind "id"
      |> Option.defaultValue JNull

    ErrorIncome(MethodNotFoundError(msgId, methodName))

// Use fixed id because of no further requests.
let private enableDidChangedWatchedFiles () =
  let msgId = JNumber 1.0

  let param =
    jsonDeserializeString
      """
        { "registrations": [
          {
            "id": "1",
            "method": "workspace/didChangeWatchedFiles",
            "registerOptions": {
              "watchers": [
                { "globPattern": "**/*.{fs,milone}" },
                { "globPattern": "**/milone_manifest" }
              ]
            }
          }
        ] }
      """

  jsonRpcWriteWithIdParams "client/registerCapability" msgId param

let private processNext host : LspIncome -> CancellationToken -> ProcessResult =
  let mutable current = WorkspaceAnalysis.create host
  let mutable exitCode: int = 1
  let mutable rootUriOpt: Uri option = None

  fun (income: LspIncome) _ct ->
    match income with
    | InitializeRequest (msgId, param) ->
      handleRequestWith "initialize" msgId (fun () ->
        rootUriOpt <- param.RootUriOpt
        createInitializeResult ())

      Continue

    | InitializedNotification ->
      handleNotificationWith
        "initialized"
        (fun () ->
          let wa =
            WorkspaceAnalysis.onInitialized rootUriOpt current

          current <- wa

          infoFn "findProjects: %A" (WorkspaceAnalysis.getProjectDirs wa)
          enableDidChangedWatchedFiles ())
        id

      Continue

    | ShutdownRequest msgId ->
      exitCode <- 0
      jsonRpcWriteWithResult msgId JNull
      Continue

    | ExitNotification -> Exit exitCode

    | DidOpenNotification p ->
      handleNotificationWith
        "didOpen"
        (fun () -> current <- WorkspaceAnalysis.didOpenDoc p.Uri p.Version p.Text current)
        id

      Continue

    | DidChangeNotification p ->
      handleNotificationWith
        "didChange"
        (fun () -> current <- WorkspaceAnalysis.didChangeDoc p.Uri p.Version p.Text current)
        id

      Continue

    | DidCloseNotification p ->
      handleNotificationWith "didClose" (fun () -> current <- WorkspaceAnalysis.didCloseDoc p.Uri current) id
      Continue

    | DidChangeWatchedFiles p ->
      handleNotificationWith
        "didChangeWatchedFile"
        (fun () ->
          for c in p.Changes do
            debugFn "change %A %s" c.Type (Uri.toString c.Uri)

            match c.Type with
            | FileChangeType.Created -> current <- WorkspaceAnalysis.didOpenFile c.Uri current
            | FileChangeType.Changed -> current <- WorkspaceAnalysis.didChangeFile c.Uri current
            | FileChangeType.Deleted -> current <- WorkspaceAnalysis.didCloseFile c.Uri current)
        id

      Continue

    | DiagnosticsNotification ->
      handleNotificationWith
        "diagnostics"
        (fun () ->
          debugFn "diagnostics"

          let result, wa = WorkspaceAnalysis.diagnostics current
          current <- wa

          result
          |> List.map (fun (Uri uri, errors) ->
            let diagnostics =
              [ for msg, start, endPos in errors do
                  jOfObj [ "range", jOfRange (start, endPos)
                           "message", JString msg
                           "source", JString "milone-lang" ] ]
              |> JArray

            jOfObj [ "uri", JString uri
                     "diagnostics", diagnostics ]))
        (fun paramList ->
          for p in paramList do
            jsonRpcWriteWithParams "textDocument/publishDiagnostics" p)

      Continue

    | CodeActionRequest (msgId, p) ->
      /// Code action with edit.
      let jEditAction title edit =
        jOfObj [ "title", JString title
                 "edit", jWorkspaceEdit edit ]

      handleRequestWith "codeAction" msgId (fun () ->
        let result, wa =
          WorkspaceAnalysis.codeAction p.Uri p.Range current

        current <- wa

        result
        |> List.map (fun (title, edit) -> jEditAction title edit)
        |> jArrayOrNull)

      Continue

    | CompletionRequest (msgId, p) ->
      handleRequestWith "completion" msgId (fun () ->
        let result, wa =
          WorkspaceAnalysis.completion p.Uri p.Pos current

        current <- wa

        result
        |> List.map (fun text -> jOfObj [ "label", JString text ])
        |> jArrayOrNull)

      Continue

    | DefinitionRequest (msgId, p) ->
      handleRequestWith "definition" msgId (fun () ->
        let result, wa =
          WorkspaceAnalysis.definition p.Uri p.Pos current

        current <- wa

        result
        |> List.map (fun (Uri uri, range) ->
          jOfObj [ "uri", JString uri
                   "range", jOfRange range ])
        |> JArray)

      Continue

    | ReferencesRequest (msgId, p) ->
      handleRequestWith "references" msgId (fun () ->
        let result, wa =
          WorkspaceAnalysis.references p.Uri p.Pos p.IncludeDecl current

        result
        |> List.map (fun (Uri uri, range) ->
          jOfObj [ "uri", JString uri
                   "range", jOfRange range ])
        |> JArray)

      Continue

    | DocumentHighlightRequest (msgId, p) ->
      handleRequestWith "documentHighlight" msgId (fun () ->
        let reads, writes, wa =
          WorkspaceAnalysis.documentHighlight p.Uri p.Pos current

        current <- wa

        let toHighlights kind posList =
          posList
          |> Seq.map (fun (start, endPos) ->
            jOfObj [ "range", jOfRange (start, endPos)
                     "kind", jOfInt kind ])

        JArray [ yield! toHighlights 2 reads
                 yield! toHighlights 3 writes ])

      Continue

    | DocumentSymbolRequest (msgId, uri) ->
      handleRequestWith "documentSymbol" msgId (fun () ->
        let symbols, wa =
          WorkspaceAnalysis.documentSymbol uri current

        current <- wa

        // SymbolInformation[]
        symbols
        |> List.map (fun (name, kind, range) ->
          let location =
            jOfObj [ "uri", JString(Uri.toString uri)
                     "range", jOfRange range ]

          jOfObj [ "name", JString name
                   "kind", jOfInt kind
                   "location", location ])
        |> JArray)

      Continue

    | FormattingRequest (msgId, uri) ->
      handleRequestWith "formatting" msgId (fun () ->
        match LspLangService.Formatting.formatting uri current with
        | None -> JNull
        | Some result ->
          result.Edits
          |> List.map (fun (range, text) ->
            // TextEdit
            jOfObj [ "range", jOfRange range
                     "newText", JString text ])
          |> JArray)

      Continue

    | HoverRequest (msgId, p) ->
      handleRequestWith "hover" msgId (fun () ->
        let contents, wa =
          WorkspaceAnalysis.hover p.Uri p.Pos current

        current <- wa

        match contents with
        | [] -> JNull

        | _ ->
          jOfObj [ "contents", contents |> List.map jOfMarkdownString |> JArray
                   // "range", jOfRange range
                    ])

      Continue

    | PrepareRenameRequest (msgId, p) ->
      handleRequestWith "prepareRename" msgId (fun () ->
        // Dry-run rename operation.
        let changes, _ =
          WorkspaceAnalysis.rename p.Uri p.Pos "_" current

        let rangeOpt =
          changes
          |> List.tryPick (fun (uri, changes) ->
            if uri = p.Uri then
              changes
              |> List.tryPick (fun (range, _) ->
                let l, r = range

                // Range.contains?
                // FIXME: Don't compare UTF-16 position and UTF-8 position
                if l <= p.Pos && p.Pos <= r then
                  Some range
                else
                  None)
            else
              None)

        match rangeOpt with
        | Some range -> jOfRange range
        | None -> JNull)

      Continue

    | RenameRequest (msgId, p) ->
      handleRequestWith "rename" msgId (fun () ->
        let changes, wa =
          WorkspaceAnalysis.rename p.Uri p.Pos p.NewName current

        current <- wa

        if changes |> List.isEmpty |> not then
          jWorkspaceEdit changes
        else
          JNull)

      Continue

    | RegisterCapabilityResponse _
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

      | MethodNotFoundError (msgId, methodName) ->
        let error =
          jOfObj [ "code", jOfInt methodNotFoundCode
                   "message", JString "Unknown method."
                   "data", jOfObj [ "methodName", JString methodName ] ]

        jsonRpcWriteWithError msgId error
        Continue

// -----------------------------------------------
// LspIncome
// -----------------------------------------------

module LspIncome =
  let asCancelRequest income =
    match income with
    | CancelRequestNotification msgId -> Some msgId
    | _ -> None

  let asMsgId income =
    match income with
    | CodeActionRequest (msgId, _)
    | CompletionRequest (msgId, _)
    | DefinitionRequest (msgId, _)
    | ReferencesRequest (msgId, _)
    | DocumentHighlightRequest (msgId, _)
    | DocumentSymbolRequest (msgId, _)
    | FormattingRequest (msgId, _)
    | HoverRequest (msgId, _)
    | RenameRequest (msgId, _)
    | RegisterCapabilityResponse msgId -> Some msgId
    | _ -> None

  let affectsDiagnostics income =
    match income with
    | InitializeRequest _
    | DidOpenNotification _
    | DidChangeNotification _
    | DidCloseNotification _
    | DidChangeWatchedFiles _ -> true
    | _ -> false

  let isQuery income =
    match income with
    | CodeActionRequest _
    | CompletionRequest _
    | DefinitionRequest _
    | ReferencesRequest _
    | DocumentHighlightRequest _
    | DocumentSymbolRequest _
    | HoverRequest _ -> true
    | _ -> false

  let diagnostics = DiagnosticsNotification

// -----------------------------------------------
// Server
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type LspServer =
  private
    { ProcessNext: LspIncome -> CancellationToken -> ProcessResult }

module LspServer =
  let create (host: LspLangService.WorkspaceAnalysisHost) : LspServer = { ProcessNext = processNext host }

  let processNext income ct (server: LspServer) = server.ProcessNext income ct
