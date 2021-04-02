module rec MiloneLspServer.Program

open MiloneLspServer.JsonRpcReaderForAbstractStream
open MiloneLspServer.JsonRpcReaderForStdIn
open MiloneLspServer.LspServer

[<EntryPoint>]
let main _ =
  async {
    let readLine, readBytes = jsonRpcReaderForStdIn ()

    let requestReader, drainRequests =
      startJsonRpcReader
        { ReadLine = readLine
          ReadBytes = readBytes }

    Async.Start(requestReader)
    return! lspServer { DrainRequests = drainRequests }
  }
  |> Async.RunSynchronously
