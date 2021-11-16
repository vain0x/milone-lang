module rec MiloneLspServer.Program

open MiloneLspServer.JsonRpcReader
open MiloneLspServer.LspServer

module LspTests = MiloneLspServer.LspTests

[<EntryPoint>]
let main (args: string array) =
  match args with
  | [| "test" |] -> LspTests.lspTests ()
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
        { RequestReceived = requestReceivedEvent.Publish

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
