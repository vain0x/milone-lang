module rec MiloneLsp.Program

open MiloneLsp.JsonRpcReaderForAbstractStream
open MiloneLsp.JsonRpcReaderForStdIn
open MiloneLsp.LspServer

[<EntryPoint>]
let main _ =
  let readLine, readBytes = jsonRpcReaderForStdIn ()

  startJsonRpcReader
    { ReadLine = readLine
      ReadBytes = readBytes
      ProcessIncomingMsg = lspServer () }
