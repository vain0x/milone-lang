module rec MiloneLspServer.Program

open System
open MiloneLspServer.JsonRpcReader
open MiloneLspServer.LspServer

// FIXME: shouldn't depend
module SyntaxApi = MiloneSyntax.SyntaxApi

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

// -----------------------------------------------
// Entrypoint
// -----------------------------------------------

[<EntryPoint>]
let main (args: string array) =
  match args with
  | [| "test" |] -> LspTests.lspTests miloneHome
  | _ -> ()

  async {
    use reader = openStdin ()
    let mutable queueLength = 0
    let requestReceivedEvent = Event<_>()

    let onMessage (msg: JsonValue) =
      System.Threading.Interlocked.Increment(&queueLength)
      |> ignore

      requestReceivedEvent.Trigger(msg)

    let! consumerWork =
      lspServer
        { MiloneHome = miloneHome
          RequestReceived = requestReceivedEvent.Publish

          OnQueueLengthChanged =
            fun len ->
              System.Threading.Interlocked.Exchange(&queueLength, len)
              |> ignore }
      |> Async.StartChild

    startJsonRpcReader
      { Reader = reader
        GetQueueLength = fun () -> queueLength
        OnMessage = onMessage }
    |> Async.Start

    return! consumerWork
  }
  |> Async.RunSynchronously
