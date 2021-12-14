module rec MiloneLspServer.Program

open System
open System.IO
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
// Entrypoint
// -----------------------------------------------

[<EntryPoint>]
let main (args: string array) =
  match args with
  | [| "test" |] -> LspTests.lspTests (getHost ())
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
              |> ignore

          Host = getHost () }
      |> Async.StartChild

    startJsonRpcReader
      { Reader = reader
        GetQueueLength = fun () -> queueLength
        OnMessage = onMessage }
    |> Async.Start

    return! consumerWork
  }
  |> Async.RunSynchronously
