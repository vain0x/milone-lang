/// Entry point of the milone-lang compiler.
module rec MiloneLang.EntryPoint

// HACK: "MiloneOnly" module is automatically loaded in Bundling and opened in NameRes.
// open MiloneLang.MiloneOnly

// See libcore for implementations.
open MiloneCore.List
open MiloneCore.Option

open MiloneLang.Cli

let private argCount (): int = (__nativeFun "arg_count" 1) ()

let private argGet (i: int): string = (__nativeFun "arg_get" 1) i

let private profileInit (): Profiler =
  let state: obj = (__nativeFun "milone_profile_init" 1) 0
  Profiler state

let private profileLog (msg: string) (Profiler state): unit =
  ((__nativeFun "milone_profile_log" 2) msg state: int)
  |> ignore

let private fileExists (filePath: string): bool = (__nativeFun "file_exists" 1) filePath

let private fileReadAllText (filePath: string): string =
  (__nativeFun "file_read_all_text" 1) filePath

let private getEnv (name: string): string = (__nativeFun "milone_get_env" 1) name

let private argList () =
  let rec go acc i =
    if i = 0 then acc else go (argGet (i - 1) :: acc) (i - 1)

  go [] (argCount ())

let private readFile filePath =
  if fileExists filePath then fileReadAllText filePath |> Some else None

[<EntryPoint>]
let main _ =
  let args = argList ()

  let miloneHome = getEnv "MILONE_HOME"

  let host: CliHost =
    { Args = args
      MiloneHome = miloneHome
      ProfileInit = profileInit
      ProfileLog = profileLog
      FileReadAllText = readFile }

  cli host
