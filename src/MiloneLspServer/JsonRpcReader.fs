// Read JSON RPC messages from standard input.
//
// (Current error handling isn't fully compliant with JSON-RPC.)
module rec MiloneLspServer.JsonRpcReader

open System
open System.IO
open MiloneLspServer.JsonValue
open MiloneLspServer.JsonSerialization

let openStdin () : BinaryReader =
  let input = System.Console.OpenStandardInput()
  new BinaryReader(input)

type private State =
  { Buf: byte []
    BufLen: int
    Closed: bool }

[<Literal>]
let private BufCapacity = 2000000 // 2MB

let private newState () : State =
  { Buf = Array.zeroCreate BufCapacity
    BufLen = 0
    Closed = false }

/// Removes leading part of buffer and moves rest to front.
let private shiftBuffer len (state: State) : State =
  let buf, bufLen = state.Buf, state.BufLen

  // eprintfn "shift: len=%d (bufLen=%d -> %d)" len bufLen (bufLen - len)
  System.Array.Copy(buf, len, buf, 0, bufLen - len)

  { state with BufLen = bufLen - len }

/// Reads from stream and writes data to internal buffer.
let private readToBuffer (reader: BinaryReader) (state: State) : State =
  if not state.Closed then
    let stream = reader.BaseStream
    let buf, bufLen = state.Buf, state.BufLen

    if bufLen = BufCapacity then
      // Reader buffer is full. Incoming message seems too large.
      failwith "ERROR: Reader buffer"

    let len =
      stream.Read(buf, bufLen, BufCapacity - bufLen)

    // eprintfn "read: %d (%d -> %d)" len bufLen (bufLen + len)

    if len > 0 then
      { state with BufLen = bufLen + len }
    else
      // eprintfn "read: get closed"
      assert (len = 0)
      { state with Closed = true }
  else
    // eprintfn "read: already closed"
    state

let private lineToString (buf: byte []) (lfIndex: int) : string =
  assert (buf.[lfIndex] = byte '\n')

  let i = lfIndex

  let len =
    if i >= 1 && buf.[i - 1] = byte '\r' then
      i - 1
    else
      i

  Text.Encoding.UTF8.GetString(buf, 0, len)

let private readLine (reader: BinaryReader) (state: State) : string option * State =
  // eprintfn "readLine"
  let buf, bufLen = state.Buf, state.BufLen

  let i =
    Array.FindIndex(buf, 0, bufLen, Predicate((=) (byte '\n')))

  if i >= 0 then
    let line = lineToString buf i
    let state = shiftBuffer (i + 1) state
    Some line, state
  else if state.Closed then
    None, state
  else
    let state = readToBuffer reader state
    readLine reader state

let private readBytes (reader: BinaryReader) len (state: State) : byte [] option * State =
  // eprintfn "readBytes len=%d" len
  let buf, bufLen = state.Buf, state.BufLen

  if bufLen >= len then
    let data = buf.[0..len]
    let state = shiftBuffer len state
    Some data, state
  else if state.Closed then
    None, state
  else
    let state = readToBuffer reader state
    readBytes reader len state

let private readHeader (reader: BinaryReader) (contentLengthOpt: int option) (state: State) : int option * State =
  let lineOpt, state = readLine reader state

  match lineOpt with
  | None -> None, state

  | Some "" ->
    // \n\n is read, which indicates the start of body.

    match contentLengthOpt with
    | None -> failwith "ERROR: Body started before content length specified"

    | Some len when uint len >= uint BufCapacity -> failwithf "ERROR: Content-Length invalid (%d)" len

    | Some len ->
      // eprintfn "begin body (len = %d)" len
      Some len, state

  | Some line ->
    // eprintfn "header: %s" line

    let line = line.TrimEnd()

    if line.StartsWith("Content-Length:") then
      let len =
        let n = "Content-Length:".Length
        line.[n..].Trim() |> int

      // eprintfn "received Content-Length: %d" len
      readHeader reader (Some len) state
    else
      // ignore unsupported header
      readHeader reader contentLengthOpt state

let private readBody (reader: BinaryReader) (contentLength: int) (state: State) : JsonValue * State =
  let bodyOpt, state = readBytes reader contentLength state

  match bodyOpt with
  | None -> failwith "ERROR: input stream closed in the middle of body"

  | Some body ->
    // eprintfn "body.length = %d" body.Length
    jsonDeserializeBytes body, state

[<NoEquality; NoComparison>]
type JsonRpcReader = private JsonRpcReader of reader: BinaryReader * stateRef: State ref

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type JsonRpcReadResult =
  | Received of JsonValue
  | Stopped

module JsonRpcReader =
  let create (reader: BinaryReader) : JsonRpcReader =
    JsonRpcReader(reader, ref (newState ()))

  /// Reads next message.
  ///
  /// Returns:
  ///   - (Received message) if received
  ///   - Stopped if the underlying stream has been closed
  ///
  /// This function blocks the current thread.
  /// This isn't thread-safe.
  let read (self: JsonRpcReader) : JsonRpcReadResult =
    let (JsonRpcReader (reader, stateRef)) = self
    let state = stateRef.contents

    let contentLengthOpt, state = readHeader reader None state

    match contentLengthOpt with
    | Some contentLength ->
      let value, state = readBody reader contentLength state
      stateRef.contents <- state
      JsonRpcReadResult.Received value

    | None -> JsonRpcReadResult.Stopped
