module internal MyBuildTool.PlatformInfo

open System

[<RequireQualifiedAccess>]
type internal Platform =
  | Linux
  | Windows

module internal Platform =
  let internal Current: Platform =
    match Environment.OSVersion.Platform with
    | PlatformID.Win32NT -> Platform.Windows
    | _ -> Platform.Linux

  let internal ExeExt: string =
    match Current with
    | Platform.Linux -> ""
    | Platform.Windows -> ".exe"

  let internal Triplet: string =
    match Current with
    | Platform.Linux -> "x86_64-unknown-linux-gnu"
    | Platform.Windows -> "x86_64-pc-windows-msvc"

  let internal GeneratedExeFile: string =
    match Current with
    | Platform.Linux -> "target/MiloneCli/x86_64-unknown-linux-gnu-release/MiloneCli"
    | Platform.Windows -> "target/MiloneCli/x86_64-pc-windows-msvc-release/MiloneCli.exe"

  let internal RuntimeIdentifier =
    match Current with
    | Platform.Linux -> "linux-x64"
    | Platform.Windows -> "win10-x64"
