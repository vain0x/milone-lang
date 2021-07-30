module MiloneLspServer.JsonRpcWriter

open MiloneLspServer.JsonValue
open MiloneLspServer.JsonSerialization

/// Writes a string (that represents a body of single message)
/// to STDOUT in the format of JSON-RPC.
let private jsonRpcWriteString: string -> unit =
  let buf = System.Console.OpenStandardOutput()
  let writer = new System.IO.BinaryWriter(buf)

  fun msg ->
    // eprintfn "write %s" msg
    let bytes = System.Text.Encoding.UTF8.GetBytes(msg)

    writer.Write(System.Text.Encoding.UTF8.GetBytes(sprintf "Content-Length: %d\r\n\r\n" bytes.Length))
    writer.Write(bytes)
    writer.Flush()

/// Writes a JSON-RPC message with result field. (For LSP responses.)
let jsonRpcWriteWithResult (id: JsonValue) (result: JsonValue) : unit =
  let jsonValue =
    [ "jsonrpc", JString "2.0"
      "id", id
      "result", result ]
    |> Map.ofList
    |> JObject

  jsonRpcWriteString (jsonDisplay jsonValue + "\n")

/// Writes a JSON-RPC message with params field. (For LSP notifications.)
let jsonRpcWriteWithParams (methodName: string) (paramsValue: JsonValue) : unit =
  let jsonValue =
    [ "jsonrpc", JString "2.0"
      "method", JString methodName
      "params", paramsValue ]
    |> Map.ofList
    |> JObject

  jsonRpcWriteString (jsonDisplay jsonValue + "\n")

let jsonRpcWriteWithError (id: JsonValue) (error: JsonValue) : unit =
  let jsonValue =
    [ "jsonrpc", JString "2.0"
      "id", id
      "error", error ]
    |> Map.ofList
    |> JObject

  jsonRpcWriteString (jsonDisplay jsonValue + "\n")
