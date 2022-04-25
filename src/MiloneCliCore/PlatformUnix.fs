module rec MiloneCliCore.PlatformUnix

open Std.StdError
open Std.StdPath
open MiloneShared.Util

module S = Std.StdString

// -----------------------------------------------
// Utils
// -----------------------------------------------

let private escapeShellWord (s: string) : string =
  s
  |> S.replace "\\" "\\\\"
  |> S.replace "!" "\\!"
  |> S.replace "$" "\\$"
  |> S.replace "'" "\\'"
  |> S.replace "\"" "\\\""

let private quoteShellWord (s: string) : string = "\"" + escapeShellWord s + "\""

/// Formats a string of shell command fragment:
///   `&& mkdir -p <OUTPUT-DIR> && cp <EXE> <OUTPUT>`
let private andCopyCommand exeFile outputOpt =
  match outputOpt with
  | None -> ""

  | Some output ->
    "&& mkdir -p $(dirname "
    + quoteShellWord (Path.toString output)
    + ") && cp -f "
    + quoteShellWord (Path.toString exeFile)
    + " "
    + quoteShellWord (Path.toString output)

// -----------------------------------------------
// Interface
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type BuildOnUnixParams =
  { CFiles: Path list
    TargetDir: Path
    IsRelease: bool
    ExeFile: Path
    OutputOpt: Path option
    MiloneHome: Path
    CSanitize: string option
    CStd: string
    CcList: Path list
    ObjList: Path list
    Libs: string list

    // Effects
    DirCreate: Path -> unit
    FileWrite: Path -> string -> unit
    ExecuteInto: string -> Never }

let private toRenderNinjaParams (p: BuildOnUnixParams) : RenderNinjaFileParams =
  { TargetDir = p.TargetDir
    CFiles = p.CFiles
    ExeFile = p.ExeFile
    MiloneHome = p.MiloneHome
    CDebug = not p.IsRelease
    COptimize = p.IsRelease
    CSanitize = p.CSanitize
    CStd = p.CStd
    CcList = p.CcList
    ObjList = p.ObjList
    Libs = p.Libs }

let buildOnUnix (p: BuildOnUnixParams) : Never =
  let targetDir = p.TargetDir

  let ninjaFile =
    Path(Path.toString targetDir + "/build.ninja")

  let ninjaExe =
    Path.toString p.MiloneHome + "/bin/ninja"

  let ninjaScript = renderNinjaFile (toRenderNinjaParams p)

  p.DirCreate targetDir
  p.FileWrite ninjaFile ninjaScript

  p.ExecuteInto(
    quoteShellWord ninjaExe
    + " -f "
    + quoteShellWord (Path.toString ninjaFile)
    + " "
    + quoteShellWord (Path.toString p.ExeFile)
    + andCopyCommand p.ExeFile p.OutputOpt
  )

let runOnUnix (p: BuildOnUnixParams) (args: string list) : Never =
  let targetDir = p.TargetDir
  let exeFile = p.ExeFile

  let ninjaExe =
    Path.toString p.MiloneHome + "/bin/ninja"

  let ninjaFile =
    Path(Path.toString targetDir + "/build.ninja")

  let buildScript = renderNinjaFile (toRenderNinjaParams p)

  p.DirCreate targetDir
  p.FileWrite ninjaFile buildScript

  p.ExecuteInto(
    quoteShellWord ninjaExe
    + " -f "
    + quoteShellWord (Path.toString ninjaFile)
    + " 1>&2 && "
    + quoteShellWord (Path.toString exeFile)
    + andCopyCommand exeFile p.OutputOpt
    + (args
       |> List.map (fun arg -> " " + quoteShellWord arg)
       |> S.concat "")
  )

// -----------------------------------------------
// Templating
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private RenderNinjaFileParams =
  { TargetDir: Path
    CFiles: Path list
    ExeFile: Path
    MiloneHome: Path

    CDebug: bool
    COptimize: bool
    CStd: string
    CSanitize: string option
    CcList: Path list
    ObjList: Path list
    Libs: string list }

let private renderNinjaFile (p: RenderNinjaFileParams) : string =
  let miloneHome = Path.toString p.MiloneHome
  let targetDir = Path.toString p.TargetDir
  let exeFile = Path.toString p.ExeFile

  let cFile name =
    let name = Path.toString name
    targetDir + "/" + name

  let objFile name =
    let name = Path.fileStem name |> Path.toString
    targetDir + "/" + name + ".o"

  let rules =
    """# Generated by milone command.

builddir = ${TARGET_DIR}

include_flag = -I${MILONE_HOME}/src/libmilonert
milone_h = ${MILONE_HOME}/src/libmilonert/milone.h
milone_c = ${MILONE_HOME}/src/libmilonert/milone.c
milone_o = ${TARGET_DIR}/milone.o
milone_platform_c = ${MILONE_HOME}/src/libmilonert/milone_platform.c
milone_platform_o = ${TARGET_DIR}/milone_platform.o
exe_file = ${EXE_FILE}

rule cc
  description = cc $in
  command = $${CC:-gcc} ${C_FLAGS} -c $include_flag $in -o $out

rule link
  description = link $out
  command = $${CC:-gcc} $in -o $out ${LINK_FLAGS}

build $milone_o: cc $milone_c | $milone_h
build $milone_platform_o: cc $milone_platform_c | $milone_h

"""

  let sanitizerFlags =
    match p.CSanitize with
    | Some value -> [ "-fsanitize=" + value ]
    | None -> []

  let cFlags =
    let debug =
      if p.CDebug then
        [ "-g" ]
      else
        [ "-DNDEBUG" ]

    let optimize = if p.COptimize then "-O2" else "-O1"
    let std = "-std=" + p.CStd

    List.append debug [ optimize; std ]
    |> List.append sanitizerFlags
    |> S.concat " "

  let linkFlags =
    p.Libs
    |> List.map (fun lib -> "-l" + lib)
    |> List.append sanitizerFlags
    |> S.concat " "

  let build =
    let rules =
      rules
      |> S.replace "${EXE_FILE}" exeFile
      |> S.replace "${MILONE_HOME}" miloneHome
      |> S.replace "${TARGET_DIR}" targetDir
      |> S.replace "${C_FLAGS}" cFlags
      |> S.replace "${LINK_FLAGS}" linkFlags

    [ rules ]

  let build =
    p.CcList
    |> List.fold
         (fun build name ->
           build
           |> cons "build "
           |> cons (objFile name)
           |> cons ": cc "
           |> cons (Path.toString name)
           |> cons "| $milone_h\n\n")
         build

  let build =
    List.fold
      (fun build name ->
        build
        |> cons "build "
        |> cons (objFile name)
        |> cons ": cc "
        |> cons (cFile name)
        |> cons " | $milone_h"
        |> cons "\n\n")
      build
      p.CFiles

  let build =
    let objFiles =
      List.append p.CcList p.CFiles
      |> List.map objFile
      |> List.append (p.ObjList |> List.map Path.toString)
      |> S.concat " "

    build
    |> cons "build $exe_file: link $milone_o $milone_platform_o "
    |> cons objFiles
    |> cons "\n"

  build |> List.rev |> S.concat ""
