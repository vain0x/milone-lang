module rec MyBuildTool.Program

open MyBuildTool.MyShell
open MyBuildTool.Packaging
open MyBuildTool.BuildingTests
open MyBuildTool.SelfHostingTests

let private helpText () =
  """MyBuildTool: Build tool for milone-lang project.

SUBCOMMANDS:
    building-tests
    self-hosting-tests
    ... ENV MILONE: Path to 'milone' command

    self-install     install milone locally
    self-uninstall   uninstall it
    pack             make binary package
    ... -n           dry run

    help, -h, --help
    version, -V, --version
"""

// -----------------------------------------------
// Interface
// -----------------------------------------------

[<EntryPoint>]
let main (argv: string array) =
  let args = Array.toList argv

  let dryRun, args = List.contains "-n" args, List.filter ((<>) "-n") args

  let perform = if dryRun then dumpAction else performAction

  match args with
  | []
  | "help" :: _
  | "-h" :: _
  | "--help" :: _ -> printf "%s" (helpText ())

  | "version" :: _
  | "-V" :: _
  | "--version" :: _ -> printfn "0.1.0"

  | "building-tests" :: _ -> commandBuildingTests ()
  | "self-hosting-tests" :: _ -> commandSelfHostingTests ()

  | "self-install" :: _ -> commandSelfInstall () |> perform
  | "self-uninstall" :: _ -> commandSelfUninstall () |> perform
  | "pack" :: _ -> commandPack () |> perform

  | _ ->
    eprintfn "unknown target: %A" argv
    exit 1

  0
