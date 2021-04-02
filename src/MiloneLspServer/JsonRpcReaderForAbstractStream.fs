module rec MiloneLspServer.JsonRpcReaderForAbstractStream

// (Not compliant with JSON-RPC for now.)

open System.IO
open System.Threading
open MiloneLspServer.JsonValue
open MiloneLspServer.JsonSerialization

type ExitCode = int

[<NoEquality; NoComparison>]
type JsonRpcReaderHost =
  {
    /// Reads a line from some byte stream.
    /// Used for headers.
    ReadLine: unit -> string option

    /// Reads a block of data with specified length from some byte stream.
    /// Used for bodies.
    ReadBytes: int -> byte [] option }

[<NoEquality; NoComparison>]
type private State = State of len: int option

let private readHeader (host: JsonRpcReaderHost) (state: State) : int option =
  match host.ReadLine() with
  | None -> None

  | Some "" ->
      // \n\n is read, which indicates the start of body.

      match state with
      | State None -> failwith "ERROR: Body started before content length specified"

      | State (Some len) ->
          // eprintfn "begin body (len = %d)" len
          Some len

  | Some line ->
      // eprintfn "header: %s" line

      let line = line.Trim()

      if line.StartsWith("Content-Length:") then
        let len =
          let n = "Content-Length:".Length
          line.[n..].Trim() |> int

        // eprintfn "received Content-Length: %d" len
        let state = State(Some len)
        readHeader host state

      else
        // ignore unsupported header
        readHeader host state

let private readBody (host: JsonRpcReaderHost) (len: int) : JsonValue =
  match host.ReadBytes len with
  | None -> failwith "ERROR: unexpected EOF in the middle of body"

  | Some body ->
      // eprintfn "body.length = %d" body.Length
      jsonDeserializeBytes body

type DrainFun = unit -> JsonValue list

/// Starts an asynchronous loop to read from stream.
let startJsonRpcReader (host: JsonRpcReaderHost) : Async<unit> * DrainFun =
  let queue =
    System.Collections.Concurrent.ConcurrentQueue<JsonValue>()

  let signal = new ManualResetEventSlim()

  let work =
    let rec go () =
      async {
        match readHeader host (State None) with
        | None -> ()

        | Some contentLength ->
            let value = readBody host contentLength
            queue.Enqueue(value)
            signal.Set()
            return! go ()
      }

    go ()

  let itemAcc = ResizeArray()

  let rec drain () =
    let rec go () =
      match queue.TryDequeue() with
      | true, value ->
          itemAcc.Add(value)
          go ()

      | false, _ ->
          let items = List.ofSeq itemAcc
          itemAcc.Clear()
          items

    match go () with
    | [] ->
        signal.Wait()
        drain ()

    | items ->
        signal.Reset()
        items

  work, drain
