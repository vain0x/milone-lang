module MiloneLsp.JsonRpcWriter

open MiloneLsp.JsonValue
open MiloneLsp.JsonSerialization

/// Writes a string (that represents a body of single message)
/// to STDOUT in the format of JSON-RPC.
let private jsonRpcWriteString: string -> unit =
  let buf = System.Console.OpenStandardOutput()
  let writer = new System.IO.BinaryWriter(buf)

  fun msg ->
    eprintfn "write %s" msg
    let bytes = System.Text.Encoding.UTF8.GetBytes(msg)

    writer.Write(System.Text.Encoding.UTF8.GetBytes(sprintf "Content-Length: %d\r\n\r\n" bytes.Length))
    writer.Write(bytes)
    writer.Flush()

/// Writes a JSON-RPC message using template file.
let jsonRpcWriteWithTemplate (name: string) (values: (string * JsonValue) list): unit =
  // eprintfn "template '%s' values=%A" name values

  let templateText =
    let dir =
      System.IO.Path.GetDirectoryName(System.Reflection.Assembly.GetExecutingAssembly().Location)

    System.IO.File.ReadAllText(System.IO.Path.Combine(dir, "..", "..", "..", "templates", sprintf "%s.json" name))

  // eprintfn "    '%s'" templateText

  let text =
    // Replace placeholders.
    let mutable buf = System.Text.StringBuilder(templateText)
    for key, value in values do
      buf.Replace(sprintf "\"${%s}\"" key, jsonDisplay value)
      |> ignore
    let text = buf.ToString()

    // eprintfn "    -> '%s'" text
    // eprintfn "    -> %A" (jsonDeserializeString text)

    // Format.
    jsonDisplay (jsonDeserializeString text) + "\n"

  jsonRpcWriteString text

/// Writes a JSON-RPC message with result field. (For LSP responses.)
let jsonRpcWriteWithResult (id: JsonValue) (result: JsonValue): unit =
  let jsonValue =
    [ "jsonrpc", JString "2.0"
      "id", id
      "result", result ]
    |> Map.ofList
    |> JObject

  jsonRpcWriteString (jsonDisplay jsonValue + "\n")

/// Writes a JSON-RPC message with params field. (For LSP notifications.)
let jsonRpcWriteWithParams (methodName: string) (paramsValue: JsonValue): unit =
  let jsonValue =
    [ "jsonrpc", JString "2.0"
      "method", JString methodName
      "params", paramsValue ]
    |> Map.ofList
    |> JObject

  jsonRpcWriteString (jsonDisplay jsonValue + "\n")
