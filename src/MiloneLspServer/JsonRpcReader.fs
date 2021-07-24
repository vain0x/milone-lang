// Read JSON RPC messages from standard input.
//
// (Current error handling isn't compliant with JSON-RPC.)
module rec MiloneLspServer.JsonRpcReader

open System
open System.IO
open System.Threading
open MiloneLspServer.JsonValue
open MiloneLspServer.JsonSerialization

[<NoEquality; NoComparison>]
type JsonRpcReaderHost =
  { Reader: BinaryReader

    GetQueueLength: unit -> int

    /// Sends an incoming message.
    OnMessage: JsonValue -> unit }

let openStdin () : BinaryReader =
  let input = System.Console.OpenStandardInput()
  new BinaryReader(input)

type private State =
  { Buf: byte []
    BufLen: int
    Closed: bool }

let private initialCapacity = 8000
let private maxCapacity = 1100100

let private newState () : State =
  { Buf = Array.zeroCreate initialCapacity
    BufLen = 0
    Closed = false }

/// Grows buffer exponentially.
let private growBuffer (minimum: int) (state: State) : State =
  let capacity = state.Buf.Length
  let newCapacity = max minimum (capacity * 2)

  if newCapacity > maxCapacity then
    failwithf "too large message (%d)" newCapacity

  // eprintfn "grow: cap=%d -> %d (bufLen=%d)" capacity newCapacity state.BufLen
  let mutable buf = state.Buf
  Array.Resize(&buf, newCapacity)
  { state with Buf = buf }

/// Shrinks buffer if large.
let private shrinkBuffer (state: State) : State =
  let bufLen, capacity = state.BufLen, state.Buf.Length
  let newCapacity = max initialCapacity (capacity / 4)

  if capacity > initialCapacity
     && bufLen <= newCapacity then
    // eprintfn "shrink: cap=%d -> %d (bufLen=%d)" capacity newCapacity bufLen
    let mutable buf = state.Buf
    Array.Resize(&buf, newCapacity)
    { state with Buf = buf }
  else
    state

/// Removes leading part of buffer and moves rest to front.
let private shiftBuffer len (state: State) : State =
  let buf, bufLen = state.Buf, state.BufLen

  // eprintfn "shift: len=%d (bufLen=%d -> %d)" len bufLen (bufLen - len)
  System.Array.Copy(buf, len, buf, 0, bufLen - len)

  shrinkBuffer { state with BufLen = bufLen - len }

/// Reads from stream and writes data to internal buffer.
let private readToBuffer (host: JsonRpcReaderHost) (state: State) : State =
  if not state.Closed then
    let stream = host.Reader.BaseStream
    let buf, bufLen = state.Buf, state.BufLen
    let capacity = buf.Length

    let len =
      stream.Read(buf, bufLen, capacity - bufLen)

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

let private readLine (host: JsonRpcReaderHost) (state: State) : string option * State =
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
    let state = readToBuffer host state
    readLine host state

let private readBytes (host: JsonRpcReaderHost) len (state: State) : byte [] option * State =
  // eprintfn "readBytes len=%d" len
  let buf, bufLen = state.Buf, state.BufLen
  let capacity = buf.Length

  if bufLen >= len then
    let data = buf.[0..len]
    let state = shiftBuffer len state
    Some data, state
  else if state.Closed then
    None, state
  else if len > capacity then
    let state = growBuffer len state
    readBytes host len state
  else
    let state = readToBuffer host state
    readBytes host len state

let private readHeader (host: JsonRpcReaderHost) (contentLengthOpt: int option) (state: State) : int option * State =
  let lineOpt, state = readLine host state

  match lineOpt with
  | None -> None, state

  | Some "" ->
    // \n\n is read, which indicates the start of body.

    match contentLengthOpt with
    | None -> failwith "ERROR: Body started before content length specified"

    | Some len when uint len >= uint maxCapacity -> failwithf "ERROR: Content-Length invalid (%d)" len

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
      readHeader host (Some len) state
    else
      // ignore unsupported header
      readHeader host contentLengthOpt state

let private readBody (host: JsonRpcReaderHost) (contentLength: int) (state: State) : JsonValue * State =
  let bodyOpt, state = readBytes host contentLength state

  match bodyOpt with
  | None -> failwith "ERROR: input stream closed in the middle of body"

  | Some body ->
    // eprintfn "body.length = %d" body.Length
    jsonDeserializeBytes body, state

/// Starts an asynchronous loop to read from stream.
let startJsonRpcReader (host: JsonRpcReaderHost) : Async<unit> =
  let rec go state =
    async {
      if host.GetQueueLength() >= 300 then
        eprintfn "reader: delaying"
        do! Async.Sleep(TimeSpan.FromSeconds(0.5))
        return! go state
      else
        let contentLengthOpt, state = readHeader host None state

        match contentLengthOpt with
        | None ->
          // eprintfn "jsonRpcReader: stopped"
          ()

        | Some contentLength ->
          let value, state = readBody host contentLength state
          host.OnMessage(value)
          return! go state
    }

  go (newState ())
