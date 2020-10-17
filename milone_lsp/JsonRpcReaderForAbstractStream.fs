module rec MiloneLsp.JsonRpcReaderForAbstractStream

// (Not compilant with JSON-RPC for now.)

open System.IO
open MiloneLsp.JsonValue
open MiloneLsp.JsonSerialization

type ExitCode = int

type JsonRpcReaderHost =
  {
    /// Reads a line from some byte stream.
    /// Used for headers.
    ReadLine: unit -> string option

    /// Reads a block of data with specified length from some byte stream.
    /// Used for bodies.
    ReadBytes: int -> byte [] option

    /// Processes an incoming message. Returns an exit code to break or None to continue.
    ProcessIncomingMsg: JsonValue -> ExitCode option }

type private State = State of len: int option

let private readHeader (host: JsonRpcReaderHost) (state: State): ExitCode =
  match host.ReadLine() with
  | None -> failwith "ERROR: STDIN closed before exit notification."

  | Some "" ->
      // \n\n is read, which indicates the start of body.

      match state with
      | State None -> failwith "ERROR: Body started before content length specified"

      | State (Some len) ->
          eprintfn "begin body (len = %d)" len
          readBody host len

  | Some line ->
      eprintfn "header: %s" line

      let line = line.Trim()
      if line.StartsWith("Content-Length:") then
        let len =
          let n = "Content-Length:".Length
          line.[n..].Trim() |> int

        eprintfn "received Content-Length: %d" len
        let state = State(Some len)
        readHeader host state

      else
        // ignore unsupported header
        readHeader host state

let readBody host (len: int): ExitCode =
  match host.ReadBytes len with
  | None -> failwith "ERROR: unexpected EOF in the middle of body"

  | Some body ->
      eprintfn "body.length = %d" body.Length

      let jsonValue = jsonDeserializeBytes body

      match host.ProcessIncomingMsg jsonValue with
      | Some exitCode -> exitCode

      | None -> readHeader host (State None)

/// Starts a loop to read from stream and process each message.
let startJsonRpcReader (host: JsonRpcReaderHost): ExitCode = readHeader host (State None)
