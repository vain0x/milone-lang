module rec MiloneLspServer.Program

open System
open System.Collections.Generic
open System.IO
open System.Threading
open System.Threading.Channels
open MiloneShared.UtilParallel
open MiloneLspServer.JsonRpcReader
open MiloneLspServer.LspServer
open MiloneLspServer.Util

// FIXME: shouldn't depend
module SyntaxApi = MiloneSyntax.SyntaxApi

module LLS = MiloneLspServer.LspLangService
module LspTests = MiloneLspServer.LspTests

// -----------------------------------------------
// .NET functions
// -----------------------------------------------

let private opt (s: string) =
  match s with
  | null
  | "" -> None
  | _ -> Some s

let private getMiloneHomeEnv () =
  Environment.GetEnvironmentVariable("MILONE_HOME")
  |> opt

let private getHomeEnv () =
  Environment.GetFolderPath(Environment.SpecialFolder.UserProfile)
  |> opt

let private miloneHome =
  SyntaxApi.getMiloneHomeFromEnv getMiloneHomeEnv getHomeEnv
  |> LLS.normalize

let private readTextFile (filePath: string) : Future<string option> =
  try
    if File.Exists(filePath) then
      File.ReadAllTextAsync(filePath)
      |> Future.ofTask
      |> Future.map Some
    else
      Future.just None
  with
  | _ -> Future.just None

let private getHost () : LLS.WorkspaceAnalysisHost =
  { MiloneHome = miloneHome

    FileExists =
      fun path ->
        traceFn "FileExists (%s)" path
        File.Exists path

    ReadTextFile =
      fun path ->
        traceFn "ReadTextFile (%s)" path
        readTextFile path

    DirEntries =
      fun dir ->
        traceFn "DirEntries (%s)" dir

        let collect paths =
          paths |> Array.map LLS.normalize |> Array.toList

        collect (Directory.GetFiles(dir)), collect (Directory.GetDirectories(dir)) }

// -----------------------------------------------
// Actors
// -----------------------------------------------

// Program works concurrently in a way based on the actor model.
//
// An actor is single long-running procedure.
// Actors run in parallel.
// Each actor owns a channel that only the actor can receive from.
//
// Actors can and only can interact with other actors
// by sending messages to their channels.
//
// Actors don't share mutable states except for channels
// so that mutation of states don't cause data races.
//
// There are three actors here:
//
// - Reader:
//      Reader actor reads from standard input for incoming LSP messages
//      and sends to Server actor and Canceller actor.
// - Server:
//      Server actor receives LSP messages from its channel (sent by Reader)
//      to process them.
//      This also writes LSP messages to standard output to for the LSP client.
// - Canceller:
//      Canceller actor manages message Ids and cancellation tokens
//      to signal tokens on cancel.
//      Note Reader actor can't do this task
//      because Reader needs to wait for standard input, can't have their own channel
//      and can't tell which messages are processed (if I understand correctly).
//
// To shutdown the program gracefully, these actors end to run by themselves.
//
// - Reader stops when standard input is closed.
// - Server and Canceller accepts "shutdown" message from channel.

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private ServerMsg =
  | Receive of JsonValue * LspIncome * CancellationToken option
  | Shutdown

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private CancellerMsg =
  | Start of msgId: JsonValue * CancellationTokenSource
  | End of msgId: JsonValue
  | Cancel of msgId: JsonValue
  | Shutdown

let private summarizeMsg msg =
  let id =
    match msg with
    | JObject map ->
      match map |> Map.tryFind "id" with
      | Some (JString it) -> it
      | Some (JNumber it) -> string it
      | _ -> "_"
    | _ -> "_"

  let m =
    match msg with
    | JObject map ->
      match map |> Map.tryFind "method" with
      | Some (JString it) -> it
      | _ -> "??"
    | _ -> "??"

  $"{id}:{m}"

[<EntryPoint>]
let main (args: string array) =
  match args with
  | [| "test" |] -> LspTests.lspTests (getHost ())
  | _ -> ()

  async {
    // Cancellation token of the program.
    let! serverCt = Async.CancellationToken

    use _ctRegistration =
      serverCt.Register(Action(fun () -> traceFn "serverCt gets cancelled."))

    let serverChannel = Channel.CreateBounded<ServerMsg>(3000)

    let cancellerChannel =
      Channel.CreateBounded<CancellerMsg>(3000)

    let readChannel (channel: Channel<'T>) =
      channel.Reader.ReadAsync(serverCt).AsTask()
      |> Async.AwaitTask

    let writeChannel msg (channel: Channel<'T>) =
      channel.Writer.WriteAsync(msg, serverCt).AsTask()
      |> Async.AwaitTask

    use input = openStdin ()

    traceFn "program (thread:%d)" Environment.CurrentManagedThreadId

    let! readerCompleter =
      let reader = JsonRpcReader.create input

      let rec loop () =
        async {
          traceFn "reader reading (thread:%d)" Environment.CurrentManagedThreadId

          match JsonRpcReader.read reader with
          | JsonRpcReadResult.Received msg ->
            traceFn "reader received %s" (summarizeMsg msg)

            let income = parseIncome msg

            match LspIncome.asCancelRequest income with
            | Some msgId ->
              traceFn "reader requests cancel of %A" msgId
              do! writeChannel (CancellerMsg.Cancel msgId) cancellerChannel
              return! loop ()

            | None ->
              let mutable ctOpt = None

              match LspIncome.asMsgId income with
              | Some msgId ->
                let cts = new CancellationTokenSource()
                traceFn "reader notified start of %A" msgId
                do! writeChannel (CancellerMsg.Start(msgId, cts)) cancellerChannel
                ctOpt <- Some cts.Token

              | None -> ()

              do! writeChannel (ServerMsg.Receive(msg, income, ctOpt)) serverChannel
              return! loop ()

          | JsonRpcReadResult.Stopped ->
            traceFn "reader stopped"
            return! writeChannel ServerMsg.Shutdown serverChannel
        }

      Async.StartChild(loop ())

    let! serverCompleter =
      let server = LspServer.create (getHost ())

      // true if the published diagnostics are still fresh.
      let mutable diagnosticsFresh = false

      let rec loop () =
        async {
          traceFn "server reading (thread:%d)" Environment.CurrentManagedThreadId

          match! readChannel serverChannel with
          | ServerMsg.Receive (msg, income, ctOpt) ->
            traceFn "server received (%s) (thread:%d)" (summarizeMsg msg) Environment.CurrentManagedThreadId

            let mutable cancelled = false

            match ctOpt with
            | Some ct when ct.IsCancellationRequested -> cancelled <- true
            | Some ct ->
              do! Async.Sleep(30) // Wait for cancellation.
              cancelled <- ct.IsCancellationRequested
            | None -> ()

            if not cancelled then
              let ct =
                ctOpt
                |> Option.defaultValue CancellationToken.None

              let result = LspServer.processNext income ct server

              match LspIncome.asMsgId income with
              | Some msgId ->
                traceFn "server end process %A" msgId
                do! writeChannel (CancellerMsg.End msgId) cancellerChannel

              | None -> ()

              match result with
              | Continue ->
                diagnosticsFresh <-
                  diagnosticsFresh
                  && not (LspIncome.affectsDiagnostics income)

                // Automatically update diagnostics
                // if the last result isn't fresh (or not published yet)
                // after some query request.
                if not diagnosticsFresh && LspIncome.isQuery income then
                  let ct = CancellationToken.None

                  match LspServer.processNext LspIncome.diagnostics ct server with
                  | Continue ->
                    diagnosticsFresh <- true
                    return! loop ()

                  | Exit _ -> return! failwith "unreachable"
                else
                  return! loop ()

              | Exit exitCode -> return exitCode
            else
              traceFn "server cancelled %A" (summarizeMsg msg)
              return! loop ()

          | ServerMsg.Shutdown -> return 0
        }

      Async.StartChild(
        async {
          let! exitCode = loop ()
          traceFn "server shutting down (code:%d)" exitCode
          do! writeChannel CancellerMsg.Shutdown cancellerChannel
          return exitCode
        }
      )

    let! cancellerCompleter =
      let mutable map =
        Dictionary<JsonValue, CancellationTokenSource>()

      let clear () =
        for cts in map.Values do
          cts.Dispose()

        map.Clear()

      let rec loop () =
        async {
          traceFn "canceller reading (thread:%d)" Environment.CurrentManagedThreadId

          match! readChannel cancellerChannel with
          | CancellerMsg.Start (msgId, cts) ->
            traceFn "canceller received start of %A" msgId

            if map.Count >= 3100100 then
              warnFn "Canceller map clears because of too large size."
              clear ()

            let ok = map.TryAdd(msgId, cts)
            if not ok then cts.Dispose() // Duplicated msgId.
            return! loop ()

          | CancellerMsg.End msgId ->
            traceFn "canceller received end of %A" msgId

            match map.TryGetValue(msgId) with
            | true, cts ->
              map.Remove(msgId) |> ignore
              cts.Dispose()

            | false, _ ->
              traceFn "canceller, End of %A not found" msgId
              ()

            return! loop ()

          | CancellerMsg.Cancel msgId ->
            traceFn "canceller received cancel of %A" msgId

            match map.TryGetValue(msgId) with
            | true, cts ->
              map.Remove(msgId) |> ignore
              cts.Cancel()

            | false, _ ->
              traceFn "canceller, cancel of %A not found" msgId
              ()

            return! loop ()

          | CancellerMsg.Shutdown ->
            traceFn "canceller shutting down"
            clear ()
        }

      Async.StartChild(
        async {
          try
            return! loop ()
          with
          | ex -> errorFn "canceller failed: %A" ex
        }
      )

    do! readerCompleter
    do! cancellerCompleter
    let! exitCode = serverCompleter
    traceFn "gracefully exit"
    return exitCode
  }
  |> Async.RunSynchronously
