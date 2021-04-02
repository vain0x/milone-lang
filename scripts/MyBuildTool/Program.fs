module rec MyBuildTool.Program

open System

let private helpText () =
  """MyBuildTool: Build tool for milone-lang project."""

[<EntryPoint>]
let main argv =
  match Array.toList argv with
  | []
  | "help" :: _
  | "-h" :: _
  | "--help" :: _ ->
      printfn "%s" (helpText ())
      exit 0

  | "version" :: _
  | "-V" :: _
  | "--version" :: _ ->
      printfn "0.1.0"
      exit 0

  | arg :: _ ->
      printfn "ERROR: Unknown arg: '%s'.\n" arg
      printfn "%s" (helpText ())
      exit 1
