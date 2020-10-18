module MiloneLsp.LspServer

open MiloneLsp.JsonValue
open MiloneLsp.JsonSerialization
open MiloneLsp.JsonRpcWriter

let jInt (value: int): JsonValue = value |> float |> JNumber

let freshMsgId: unit -> int =
  let mutable lastId = 0
  fun () ->
    lastId <- lastId + 1
    lastId

let entry key jsonValue: JsonValue =
  match jsonValue with
  | JObject map ->
      match map |> Map.tryFind key with
      | Some value -> value

      | None -> failwithf "missed key %s in '%s'" key (jsonDisplay jsonValue)

  | _ -> failwithf "Expected a map with key:%s but not: '%s'" key (jsonDisplay jsonValue)

let expectString jsonValue: string =
  match jsonValue with
  | JString value -> value

  | _ -> failwithf "Expected a string but: %s" (jsonDisplay jsonValue)

let expectNumber jsonValue: float =
  match jsonValue with
  | JNumber value -> value

  | _ -> failwithf "Expected a number but: %s" (jsonDisplay jsonValue)

let lspServer () =
  let freshMsgId () = freshMsgId () |> jInt

  let mutable exitCode = 1

  fun (jsonValue: JsonValue) ->
    eprintfn "received %A" jsonValue
    let getMsgId () = jsonValue |> entry "id"

    match jsonValue |> entry "method" |> expectString with
    | "initialize" ->
        jsonRpcWriteWithTemplate "initialize_response" [ "MSG_ID", getMsgId () ]
        None

    | "shutdown" ->
        exitCode <- 0
        jsonRpcWriteWithTemplate "shutdown_response" [ "MSG_ID", getMsgId () ]
        None

    | "exit" -> Some exitCode

    | "textDocument/didOpen" ->
        let uri =
          jsonValue
          |> entry "params"
          |> entry "textDocument"
          |> entry "uri"

        let pos row column =
          [ "line", jInt row
            "character", jInt column ]
          |> Map.ofList
          |> JObject

        let range start endPos =
          [ "start", start; "end", endPos ]
          |> Map.ofList
          |> JObject

        let paramsValue =
          [ "uri", uri
            "diagnostics",
            JArray [ JObject
                       (Map.ofList [ "range", range (pos 0 0) (pos 0 2)
                                     "message", JString "hi!" ]) ] ]
          |> Map.ofList
          |> JObject

        jsonRpcWriteWithParams "textDocument/publishDiagnostics" paramsValue
        None

    | _ -> None
