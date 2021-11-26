module rec MiloneCli.BackendCMake

open MiloneStd.StdError
open MiloneStd.StdPath

module S = MiloneStd.StdString

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

// -----------------------------------------------
// Interface
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type BuildWithCMakeParams =
  { CFiles: Path list
    TargetDir: Path
    IsRelease: bool
    ExeFile: Path
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

let private toRenderCMakeListsParams (p: BuildWithCMakeParams) : RenderCMakeListsParams =
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

let buildWithCMake (p: BuildWithCMakeParams) : Never =
  let targetDir = p.TargetDir

  let exeDir, _, _ =
    p.ExeFile |> Path.toString |> S.cutLast "/"

  let cmakeListsFile =
    Path(Path.toString targetDir + "/CMakeLists.txt")

  let cmakeLists =
    renderCMakeLists (toRenderCMakeListsParams p)

  p.DirCreate targetDir
  p.DirCreate(Path exeDir)
  p.FileWrite cmakeListsFile cmakeLists

  p.ExecuteInto(
    "( cd "
    + quoteShellWord (Path.toString targetDir)
    + " && cmake . && cmake --build .; )"
  )

let runWithCMake (p: BuildWithCMakeParams) (args: string list) : Never =
  let targetDir = p.TargetDir
  let exeFile = p.ExeFile

  let exeDir, _, _ =
    exeFile |> Path.toString |> S.cutLast "/"

  let cmakeListsFile =
    Path(Path.toString targetDir + "/CMakeLists.txt")

  let cmakeLists =
    renderCMakeLists (toRenderCMakeListsParams p)

  p.DirCreate targetDir
  p.DirCreate(Path exeDir)
  p.FileWrite cmakeListsFile cmakeLists

  p.ExecuteInto(
    "( cd "
    + quoteShellWord (Path.toString targetDir)
    + " && cmake . 1>&2"
    + " && cmake --build . 1>&2; )"
    + " && "
    + quoteShellWord (Path.toString exeFile)
    + (args
       |> List.map (fun arg -> " " + quoteShellWord arg)
       |> S.concat "")
  )

// -----------------------------------------------
// Templating
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private RenderCMakeListsParams =
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

let private renderCMakeLists (p: RenderCMakeListsParams) : string =
  let miloneHome = Path.toString p.MiloneHome
  let targetDir = Path.toString p.TargetDir
  let exeFile = Path.toString p.ExeFile

  let cFile name =
    let name = Path.toString name
    targetDir + "/" + name

  let template =
    """cmake_minimum_required(VERSION 3.10)
# project(${PROJECT_NAME} VERSION 0.1)
project(${PROJECT_NAME})

# set(CMAKE_C_STANDARD 11)
# set(CMAKE_C_STANDARD_REQUIRED True)

add_executable(${PROJECT_NAME}
    ${C_FILES}
)

set_target_properties(
    ${PROJECT_NAME}
    PROPERTIES
        OUTPUT_NAME "${EXE_FILE}"
        SUFFIX ""

        CMAKE_C_FLAGS "${C_FLAGS}"
)

target_include_directories(
    ${PROJECT_NAME}
    PUBLIC
    "${MILONE_HOME}/runtime"
)

target_link_libraries(
    ${PROJECT_NAME}
    PUBLIC
    ${LINK_FLAGS}
)
"""

  let sanitizerFlags =
    match p.CSanitize with
    | Some value -> [ "-fsanitize=" + value ]
    | None -> []

  let cFlags =
    let debug = if p.CDebug then [ "-g" ] else []
    let optimize = if p.COptimize then "-O2" else "-O1"

    List.append debug [ optimize ]
    |> List.append sanitizerFlags
    |> S.concat " "

  let linkFlags =
    p.Libs
    |> List.append sanitizerFlags
    |> S.concat " "

  let cFiles =
    (miloneHome + "/runtime/milone.c")
    :: (miloneHome + "/runtime/milone_platform.c")
       :: (p.CFiles |> List.map cFile)
    |> S.concat "\n    "

  template
  |> S.replace "${PROJECT_NAME}" "my_app"
  |> S.replace "${EXE_FILE}" exeFile
  |> S.replace "${MILONE_HOME}" miloneHome
  |> S.replace "${TARGET_DIR}" targetDir
  |> S.replace "${C_FLAGS}" cFlags
  |> S.replace "${LINK_FLAGS}" linkFlags
  |> S.replace "${C_FILES}" cFiles
