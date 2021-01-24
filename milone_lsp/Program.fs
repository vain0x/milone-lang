module rec MiloneLsp.Program

open MiloneLsp.JsonRpcReaderForAbstractStream
open MiloneLsp.JsonRpcReaderForStdIn
open MiloneLsp.LspServer

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
  } |> Async.RunSynchronously
