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
  let mutable exitCode = 1
  let freshMsgId () = freshMsgId () |> jInt

  fun (jsonValue: JsonValue) ->
    let getMsgId () = jsonValue |> entry "id" |> expectNumber

    match jsonValue |> entry "method" |> expectString with
    | "initialize" ->
        jsonRpcWriteWithTemplate "initialize_response" [ "MSG_ID", freshMsgId () ]
        None

    | "shutdown" ->
        exitCode <- 0
        jsonRpcWriteWithTemplate "shutdown_response" [ "MSG_ID", freshMsgId () ]
        None

    | "exit" -> Some exitCode

    | _ ->
        eprintfn "received %A" jsonValue
        None
