module MiloneLsp.LspServer

open MiloneLang.Syntax
open MiloneLsp.JsonValue
open MiloneLsp.JsonSerialization
open MiloneLsp.JsonRpcWriter

let jOfInt (value: int): JsonValue = JNumber(float value)

let jOfObj (assoc: (string * JsonValue) list) = JObject(Map.ofList assoc)

let jOfPos (row: int) (column: int): JsonValue =
  jOfObj [ "line", jOfInt row
           "character", jOfInt column ]

let jOfRange (start: JsonValue) (endValue: JsonValue): JsonValue =
  jOfObj [ "start", start
           "end", endValue ]

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

let lspServer (): JsonValue -> int option =
  let freshMsgId () = freshMsgId () |> jOfInt

  let mutable exitCode = 1
  let mutable rootUriOpt: string option = None

  let doPublishDiagnostics (uri: string) (errors: (string * int * int * int * int) list): unit =
    let diagnostics =
      errors
      |> List.map (fun (msg, r1, c1, r2, c2) ->
           let start = jOfPos r1 c1
           let endPos = jOfPos r2 c2

           jOfObj [ "range", jOfRange start endPos
                    "message", JString msg ])
      |> JArray

    let paramsValue =
      jOfObj [ "uri", JString uri
               "diagnostics", diagnostics ]

    jsonRpcWriteWithParams "textDocument/publishDiagnostics" paramsValue

  let validateDoc (uri: string): unit =
    let errors =
      LspLangService.validateDoc uri
      |> List.map (fun (msg, (row, column)) -> msg, row, column, row, column)

    doPublishDiagnostics uri errors

  let validateWorkspace (): unit =
    for uri, errors in LspLangService.validateWorkspace rootUriOpt do
      let errors =
        [ for msg, pos in errors do
            let row, column = pos
            yield msg, row, column, row, column ]

      doPublishDiagnostics uri errors

  fun jsonValue ->
    eprintfn "received %A" jsonValue
    let getMsgId () = jsonValue |> jFind "id"

    match jsonValue |> jFind "method" |> jToString with
    | "initialize" ->
        rootUriOpt <-
          try
            jsonValue
            |> jFind2 "params" "rootUri"
            |> jToString
            |> Some
          with _ -> None
        eprintfn "rootUriOpt = %A" rootUriOpt

        jsonRpcWriteWithTemplate "initialize_response" [ "MSG_ID", getMsgId () ]
        None

    | "shutdown" ->
        exitCode <- 0
        jsonRpcWriteWithTemplate "shutdown_response" [ "MSG_ID", getMsgId () ]
        None

    | "exit" -> Some exitCode

    | "textDocument/didOpen" ->
        let docParam =
          jsonValue |> jFind2 "params" "textDocument"

        let uri, version, text =
          let uri, version, text =
            docParam |> jFields3 "uri" "version" "text"

          jToString uri, jToInt version, jToString text

        LspLangService.openDoc uri version text
        validateDoc uri
        validateWorkspace ()
        None

    | "textDocument/didChange" ->
        let uri, version =
          let docParam =
            jsonValue |> jFind2 "params" "textDocument"

          let uri, version = docParam |> jFields2 "uri" "version"

          jToString uri, jToInt version

        let text =
          jsonValue
          |> jFind2 "params" "contentChanges"
          |> jAt 0
          |> jFind "text"
          |> jToString

        LspLangService.changeDoc uri version text
        validateDoc uri
        validateWorkspace ()
        None

    | "textDocument/didClose" ->
        let uri =
          jsonValue
          |> jFind3 "params" "textDocument" "uri"
          |> jToString

        LspLangService.closeDoc uri
        None

    | methodName ->
        eprintfn "unknown method '%s'" methodName
        None
