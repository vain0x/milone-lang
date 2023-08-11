module rec MiloneCli.BackendZig

open Std.Path
open Std.StdPath
open MiloneSyntax.SyntaxApiTypes
open MiloneCli.NinjaFileGen

module S = Std.StdString

// -----------------------------------------------
// Interface
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type BuildWithZigParams =
  { CFiles: Path list
    TargetDir: Path
    IsRelease: bool
    ExeFile: Path
    OutputOpt: Path option
    MiloneHome: Path
    BinaryType: BinaryType
    CSanitize: string option
    CStd: string
    CcList: Path list
    ObjList: Path list
    Libs: string list
    LinuxCFlags: string
    LinuxLinkFlags: string

    // Effects
    DirCreate: Path -> unit
    FileWrite: Path -> string -> unit
    RunCommand: Path -> string list -> unit }

let buildWithZig (p: BuildWithZigParams) : int =
  let targetDir = Path.toString p.TargetDir
  let miloneHome = Path.toString p.MiloneHome

  let ninjaFile = Pathname.join targetDir "build.ninja"
  let ninjaExe = Pathname.join miloneHome "bin/ninja.exe"

  let project: NinjaProjectParams =
    let cFiles =
      List.append p.CcList p.CFiles
      |> List.map (fun path ->
        let name = Path.toString path
        let c = Pathname.join targetDir name
        let o = Pathname.join targetDir (Pathname.stem name + ".obj")
        c, o)

    let sanitizerFlags =
      match p.CSanitize with
      | Some value -> [ "-fsanitize=" + value ]
      | None -> []

    let cFlags =
      let pic =
        match p.BinaryType with
        | BinaryType.Exe -> []
        | BinaryType.SharedObj
        | BinaryType.StaticLib -> [ "-fPIC" ]

      let debug = if not p.IsRelease then [ "-g"; "-D_DEBUG" ] else [ "-DNDEBUG" ]

      let optimize = if p.IsRelease then "-O2" else "-O1"
      let std = "-std=" + p.CStd

      let definedMacro =
        "WIN32;_WIN32;UNICODE;_UNICODE"
        |> S.split ";"
        |> List.map (fun s -> "-D" + s)

      List.collect
        id
        [ [ "-I" + miloneHome + "/src/libmilonert"; "-c" ]
          pic
          debug
          [ optimize; std ]
          sanitizerFlags
          definedMacro
          [ p.LinuxCFlags ] ]

    let linkRule =
      match p.BinaryType with
      | BinaryType.Exe
      | BinaryType.SharedObj -> "link"
      | BinaryType.StaticLib -> "archive"

    let linkFlags =
      let binaryFlag =
        match p.BinaryType with
        | BinaryType.Exe
        | BinaryType.StaticLib -> []
        | BinaryType.SharedObj -> [ "-shared" ]

      let lFlags =
        let defaultLibs = [ "c"; "bcrypt"; "winmm" ]
        List.append p.Libs defaultLibs |> List.map (fun lib -> "-l" + lib)

      List.collect id [ binaryFlag; lFlags; sanitizerFlags; [ p.LinuxLinkFlags ] ]

    let linkInputs =
      p.ObjList |> List.map (fun o -> Pathname.join targetDir (Path.toString o))

    { ProjectName = "main"
      OutputFile = Path.toString p.ExeFile
      CopyOpt = Option.map Path.toString p.OutputOpt
      CFlags = cFlags
      CFiles = cFiles
      LinkRule = linkRule
      LinkFlags = linkFlags
      LinkInputs = linkInputs }

  let ninjaScript =
    let a: NinjaFileParams =
      { TargetDir = targetDir
        MiloneHome = miloneHome

        CcCmd = "zig.exe cc"
        ArCmd = "zig.exe ar"
        CpCmd = "cmd /c copy"
        ObjExt = ".obj" }

    generateNinjaFile a [ project ]

  // $ mkdir -p target
  p.DirCreate p.TargetDir
  // $ do >build.ninja
  p.FileWrite (Path.ofString ninjaFile) ninjaScript
  // $ ninja -f build.ninja all
  p.RunCommand (Path.ofString ninjaExe) [ "-f"; ninjaFile; "all" ]
  0

let runWithZig (p: BuildWithZigParams) (args: string list) : int =
  buildWithZig p |> ignore
  p.RunCommand p.ExeFile args
  0
