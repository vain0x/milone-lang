// Commands for packaging, install and uninstall.
module internal MyBuildTool.Packaging

open System
open System.IO
open MyBuildTool.MyShell
open MyBuildTool.PlatformInfo
open MyBuildTool.Util

let private MiloneVersion: string = "0.6.0"
let private AssetsDir: string = __SOURCE_DIRECTORY__ + "/assets"
let private Cwd: string = Environment.CurrentDirectory

// -----------------------------------------------
// Helper
// -----------------------------------------------

let private RunDotnetPublish (projectDir, outputDir) : Action =
  Run(
    "dotnet",
    [ "publish"
      projectDir
      "--runtime"
      Platform.RuntimeIdentifier
      "--self-contained"
      "true"
      "-c"
      "Release"
      "-o"
      outputDir
      "-nologo"
      "-v:quiet"
      "-consoleLoggerParameters:NoSummary" ],
    [],
    None
  )

let private RunPwsh command : Action =
  Run(
    "C:/Windows/System32/WindowsPowerShell/v1.0/powershell.exe",
    [ "-NoLogo"; "-NoProfile"; "-NonInteractive"; "-c"; command ],
    [],
    Path.GetDirectoryName(command) |> Some
  )

let private destFiles (destDir: string) =
  let exeExt = Platform.ExeExt
  let destMiloneHome = $"{destDir}/share/milone"

  {| BinDir = $"{destDir}/bin"
     MiloneExe = $"{destDir}/bin/milone{exeExt}"
     MiloneHome = destMiloneHome
     MiloneLspDir = $"{destMiloneHome}/bin/milone_lsp"
     SrcDir = $"{destMiloneHome}/src"
     VersionFile = $"{destMiloneHome}/version" |}

// -----------------------------------------------
// Package
// -----------------------------------------------

// IMPORTANT!
//    This script must be sync with
//    binary_package.md, INSTALL.md, and install/uninstall scripts.

/// Generates a binary package.
let private generateBinaryPackage (destDir: string) =
  let onLinux = Platform.Current = Platform.Linux
  let dest = destFiles destDir

  io "package" {
    // Make structure.
    RemoveDir destDir
    MakeDir dest.BinDir
    MakeDir dest.MiloneHome

    // Build.
    Run(
      "dotnet",
      ("run --project src/MiloneCli -- build --release src/MiloneCli"
       |> StringExt.split " "),
      [ "MILONE_HOME", Cwd ],
      None
    )

    CopyFile(Platform.GeneratedExeFile, dest.MiloneExe)

    if onLinux then
      Run("strip", [ "-s"; dest.MiloneExe ], [], None)

    // Record version.
    RunWith(
      dest.MiloneExe,
      [ "--version" ],
      fun version ->
        let version = StringExt.trim version
        assert (version = MiloneVersion)
        writeFile dest.VersionFile $"{version}\n"
    )

    // Build LSP server.
    RunDotnetPublish("src/MiloneLspServer", dest.MiloneLspDir)
    RemoveFilesWithFilter(dest.MiloneLspDir, [ "*.pdb" ])

    // Copy runtime files.
    CopyDirWithFilter("src/libmilonert", $"{dest.SrcDir}/libmilonert", [ "*.c"; "*.h"; "LICENSE" ])
    CopyDirWithFilter("src/MiloneCore", $"{dest.SrcDir}/MiloneCore", [ "*.fs"; "*.milone"; "LICENSE" ])
    CopyDirWithFilter("src/Std", $"{dest.SrcDir}/Std", [ "*.fs"; "*.milone"; "LICENSE" ])

    // Add assets.
    let installScript, uninstallScript =
      match Platform.Current with
      | Platform.Linux -> $"{AssetsDir}/install.sh", $"{AssetsDir}/uninstall.sh"
      | Platform.Windows -> $"{AssetsDir}/install.ps1", $"{AssetsDir}/uninstall.ps1"

    CopyFiles(
      [ "README.md"
        "LICENSE"
        $"{AssetsDir}/INSTALL.md"
        installScript
        uninstallScript ],
      destDir
    )
  }

// -----------------------------------------------
// Pack
// -----------------------------------------------

/// Makes a compressed binary package to upload.
let internal commandPack () =
  let triplet = Platform.Triplet

  let version = MiloneVersion
  let destName = $"milone-{version}"

  io "pack" {
    generateBinaryPackage $"target/{destName}"

    // Compress.
    let outFile =
      match Platform.Current with
      | Platform.Linux -> $"target/milone-{version}-{triplet}.tar.gz"
      | Platform.Windows -> $"target/milone-{version}-{triplet}.zip"

    RemoveFile outFile

    match Platform.Current with
    | Platform.Linux -> Run("tar", [ "cf"; outFile; "-C"; "target"; destName ], [], None)
    | Platform.Windows ->
      Do("compress", (fun () -> Compression.ZipFile.CreateFromDirectory($"target/{destName}", outFile)))

    ReadBytesWith(
      outFile,
      fun contents ->
        let hash = Sha256.compute contents
        printfn "%s  %s" hash (Path.GetFileName(outFile))
    )

    Echo $"Generated {outFile}"
    Echo $"milone-lang v{version} is packed successfully!"
  }

// -----------------------------------------------
// self-install
// -----------------------------------------------

let internal commandSelfInstall () : Action =
  let destDir = $"{Cwd}/target/milone-{MiloneVersion}"

  io "self-install" {
    generateBinaryPackage destDir

    match Platform.Current with
    | Platform.Linux -> Run("/bin/sh", [ $"{destDir}/install.sh" ], [], Some destDir)
    | Platform.Windows -> RunPwsh $"{destDir}/install.ps1"
  }

// -----------------------------------------------
// self-uninstall
// -----------------------------------------------

let internal commandSelfUninstall () =
  io "uninstall" {
    match Platform.Current with
    | Platform.Linux -> Run("/bin/sh", [ $"{AssetsDir}/uninstall.sh" ], [], None)
    | Platform.Windows -> RunPwsh $"{AssetsDir}/uninstall.ps1"
  }
