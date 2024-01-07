module rec MiloneCli.PlatformWindows

open MiloneShared.Util
open MiloneSyntax.SyntaxApiTypes
open Std.StdError
open Std.StdMap
open Std.StdPath

module S = Std.StdString

// -----------------------------------------------
// Utils
// -----------------------------------------------

type Guid = Guid of string
type NewGuidFun = unit -> Guid

module private Guid =
  let toString (Guid s) = s

module private Path =
  let dirname (path: Path) : Path =
    let rec go (s: string) =
      match S.findLastIndex "/" s with
      | Some 0 -> path // FIXME: what is parent of root?

      | Some i when i = s.Length - 1 -> go (S.truncate (s.Length - 1) s)

      | Some i -> Path(S.truncate i s)

      | None -> Path "" // FIXME: what to do?

    path |> Path.trimEndSep |> Path.toString |> go

  // #pathJoin
  let join (basePath: Path) (name: Path) : Path =
    let isRooted =
      (name |> Path.toString |> S.startsWith "/")
      || (name |> Path.toString |> S.slice 1 2 = ":")

    if isRooted then
      name
    else
      Path(Path.toString basePath + "/" + Path.toString name)

type private FileExistsFun = Path -> bool

let private findMSBuild (fileExists: FileExistsFun) : Path =
  let pathsPre2019 =
    let years = [ 2019; 2017; 2015 ]

    let editions =
      [ "Community"
        "Enterprise"
        "Professional"
        "BuildTools" ]

    years
    |> List.collect (fun (year: int) ->
      editions
      |> List.map (fun edition ->
        Path(
          "C:/Program Files (x86)/Microsoft Visual Studio/"
          + string year
          + "/"
          + edition
          + "/MSBuild/Current/Bin/MSBuild.exe"
        )))

  let paths =
    let year = 2022

    let editions =
      [ "Community"
        "Enterprise"
        "Professional"
        "BuildTools" ]

    editions
    |> List.map (fun edition ->
      Path(
        "C:/Program Files/Microsoft Visual Studio/"
        + string year
        + "/"
        + edition
        + "/MSBuild/Current/Bin/MSBuild.exe"
      ))

  List.append paths pathsPre2019
  |> List.tryFind fileExists
  |> Option.defaultValue (Path "MSBuild.exe")

// -----------------------------------------------
// Guid files
// -----------------------------------------------

// `guid.txt` is a file to save generated project GUIDs.
// GUIDs should be stable to avoid disrupting incremental build.

// File format is simple key-value pairs:
// `<KEY>=<VALUE>` per line.

let private parseGuidFile (text: string) =
  text
  |> S.toLines
  |> List.choose (fun line ->
    let key, value, eq = line |> S.cut "="
    if eq then Some(key, Guid value) else None)

let private associateGuids (newGuidFun: NewGuidFun) keys text =
  let mapping = parseGuidFile text |> TMap.ofList compare

  let entries =
    keys
    |> List.map (fun key ->
      match mapping |> TMap.tryFind key with
      | Some value -> key, value
      | None -> key, newGuidFun ())

  let text =
    entries
    |> List.map (fun (key, guid) -> key + "=" + Guid.toString guid + "\n")
    |> S.concat ""

  let mapping = entries |> TMap.ofList compare

  mapping, text

// -----------------------------------------------
// Interface
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ProjectOnWindows =
  { ProjectName: string
    CFiles: Path list

    ExeFile: Path
    OutputOpt: Path option
    // FIXME: support csanitize, cstd, objList
    BinaryType: BinaryType
    SubSystem: SubSystem
    CcList: Path list
    Libs: string list
    /// Symbol names to be exported by `/EXPORT` link option
    Exports: string list

    RunAfterBuilt: bool }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type BuildOnWindowsParams =
  { Projects: ProjectOnWindows list

    SlnName: string
    MiloneHome: Path
    TargetDir: Path
    IsRelease: bool

    NewGuid: NewGuidFun
    DirCreate: Path -> unit
    FileExists: FileExistsFun
    FileRead: Path -> string option
    FileWrite: Path -> string -> unit
    CopyFile: string -> string -> unit
    RunCommand: Path -> string list -> unit }

let buildOnWindows (p: BuildOnWindowsParams) : unit =
  let configuration = if p.IsRelease then "Release" else "Debug"

  // Retrieve or generate GUID for solution and VC++ projects.
  let slnGuid, guidMap =
    let path = Path.join p.TargetDir (Path "guid.txt")

    let text = path |> p.FileRead |> Option.defaultValue "" |> S.trimEnd

    let guidMap, guidText =
      let projectNames =
        p.Projects
        |> List.map (fun (q: ProjectOnWindows) -> q.ProjectName)
        |> listSort compare

      associateGuids p.NewGuid ("sln" :: projectNames) text

    let slnGuid, guidMap =
      match guidMap |> TMap.remove "sln" with
      | Some it, guidMap -> it, guidMap
      | None, _ -> unreachable ()

    p.FileWrite path guidText

    slnGuid, guidMap

  let projects =
    p.Projects
    |> List.map (fun (q: ProjectOnWindows) ->
      let guid =
        match guidMap |> TMap.tryFind q.ProjectName with
        | Some it -> it
        | None -> unreachable ()

      q, guid)

  let slnFile = Path.join p.TargetDir (Path(p.SlnName + ".sln"))

  let slnXml =
    let p: SolutionXmlParams =
      { SlnGuid = slnGuid

        Projects = projects |> List.map (fun (q: ProjectOnWindows, guid) -> q.ProjectName, guid) }

    renderSolutionXml p

  let vcxProjects =
    projects
    |> List.map (fun (q: ProjectOnWindows, projectGuid) ->
      let vcxprojFile =
        Path.join p.TargetDir (Path(q.ProjectName + "/" + q.ProjectName + ".vcxproj"))

      let vcxprojXml =
        let runtimeDir = Path.join p.MiloneHome (Path "src/libmilonert") |> Path.toString

        let p: VcxProjectParams =
          { MiloneTargetDir = p.TargetDir
            CFiles = List.append q.CFiles q.CcList
            Libs = q.Libs |> List.map Path
            Exports = q.Exports
            ProjectGuid = projectGuid
            ProjectName = q.ProjectName
            IncludeDir = runtimeDir
            RuntimeDir = runtimeDir

            ConfigurationType =
              match q.BinaryType with
              | BinaryType.Exe -> "Application"
              | BinaryType.SharedObj -> "DynamicLibrary"
              | BinaryType.StaticLib -> "StaticLibrary"

            SubSystem =
              match q.SubSystem with
              | SubSystem.Console -> "Console"
              | SubSystem.Windows -> "Windows"

            Macro =
              match q.SubSystem with
              | SubSystem.Console -> "_CONSOLE"
              | SubSystem.Windows -> "_WINDOWS" }

        renderVcxProjectXml p

      vcxprojFile, vcxprojXml)

  ((slnFile, slnXml) :: vcxProjects)
  |> List.fold
    (fun () (filePath, contents) ->
      p.DirCreate(Path.dirname filePath)
      p.FileWrite filePath contents)
    ()

  // Build with MSBuild.
  let msBuild = findMSBuild p.FileExists

  p.RunCommand
    msBuild
    [ Path.toString slnFile
      "-p:Configuration=" + configuration + ";Platform=x64"
      "-v:quiet"
      "-nologo" ]

  // Copy output.
  projects
  |> List.fold
    (fun () (q: ProjectOnWindows, _) ->
      match q.OutputOpt with
      | Some output ->
        p.DirCreate(Path.dirname output)
        p.CopyFile (Path.toString q.ExeFile) (Path.toString output)

      | None -> ())
    ()

let runOnWindows (p: BuildOnWindowsParams) (args: string list) : unit =
  let q =
    match p.Projects |> List.tryFind (fun (q: ProjectOnWindows) -> q.RunAfterBuilt) with
    | Some it -> it
    | None -> unreachable ()

  buildOnWindows p
  p.RunCommand q.ExeFile args

// =============================================================================

// -----------------------------------------------
// Template: solution
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private SolutionXmlParams =
  { SlnGuid: Guid

    // `(projectName, projectGuid) list`
    Projects: (string * Guid) list }

let private renderSolutionXml (p: SolutionXmlParams) : string =
  """Microsoft Visual Studio Solution File, Format Version 12.00
# Visual Studio Version 17
VisualStudioVersion = 17.5.33414.496
MinimumVisualStudioVersion = 10.0.40219.1
"""
  + (p.Projects
     |> List.map (fun (projectName, projectGuid) ->
       """Project("{${GUID1}}") = "${PROJECT_NAME}", "${PROJECT_NAME}\${PROJECT_NAME}.vcxproj", "{${PROJECT_GUID}}"
EndProject
"""
       |> S.replace "${GUID1}" (Guid.toString projectGuid)
       |> S.replace "${PROJECT_GUID}" (Guid.toString projectGuid)
       |> S.replace "${PROJECT_NAME}" projectName)
     |> S.concat "")
  + """Global
	GlobalSection(SolutionConfigurationPlatforms) = preSolution
		Debug|x64 = Debug|x64
		Debug|x86 = Debug|x86
		Release|x64 = Release|x64
		Release|x86 = Release|x86
	EndGlobalSection
	GlobalSection(ProjectConfigurationPlatforms) = postSolution
"""
  + (p.Projects
     |> List.map (fun (_, projectGuid) ->
       """		{${PROJECT_GUID}}.Debug|x64.ActiveCfg = Debug|x64
		{${PROJECT_GUID}}.Debug|x64.Build.0 = Debug|x64
		{${PROJECT_GUID}}.Debug|x86.ActiveCfg = Debug|Win32
		{${PROJECT_GUID}}.Debug|x86.Build.0 = Debug|Win32
		{${PROJECT_GUID}}.Release|x64.ActiveCfg = Release|x64
		{${PROJECT_GUID}}.Release|x64.Build.0 = Release|x64
		{${PROJECT_GUID}}.Release|x86.ActiveCfg = Release|Win32
		{${PROJECT_GUID}}.Release|x86.Build.0 = Release|Win32
"""
       |> S.replace "${PROJECT_GUID}" (Guid.toString projectGuid))
     |> S.concat "")
  + """	EndGlobalSection
	GlobalSection(SolutionProperties) = preSolution
		HideSolutionNode = FALSE
	EndGlobalSection
"""
  + ("""	GlobalSection(ExtensibilityGlobals) = postSolution
		SolutionGuid = {${SLN_GUID}}
	EndGlobalSection
EndGlobal
"""
     |> S.replace "${SLN_GUID}" (Guid.toString p.SlnGuid))

// -----------------------------------------------
// Template: vcxproj
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private VcxProjectParams =
  { MiloneTargetDir: Path
    CFiles: Path list
    Libs: Path list
    Exports: string list

    ProjectGuid: Guid
    ProjectName: string
    IncludeDir: string
    RuntimeDir: string
    ConfigurationType: string
    Macro: string
    SubSystem: string }

let private renderVcxProjectXml (p: VcxProjectParams) : string =
  """<?xml version="1.0" encoding="utf-8"?>
<Project DefaultTargets="Build" xmlns="http://schemas.microsoft.com/developer/msbuild/2003">
  <ItemGroup Label="ProjectConfigurations">
    <ProjectConfiguration Include="Debug|Win32">
      <Configuration>Debug</Configuration>
      <Platform>Win32</Platform>
    </ProjectConfiguration>
    <ProjectConfiguration Include="Release|Win32">
      <Configuration>Release</Configuration>
      <Platform>Win32</Platform>
    </ProjectConfiguration>
    <ProjectConfiguration Include="Debug|x64">
      <Configuration>Debug</Configuration>
      <Platform>x64</Platform>
    </ProjectConfiguration>
    <ProjectConfiguration Include="Release|x64">
      <Configuration>Release</Configuration>
      <Platform>x64</Platform>
    </ProjectConfiguration>
  </ItemGroup>
  <PropertyGroup Label="Globals">
    <VCProjectVersion>16.0</VCProjectVersion>
    <Keyword>Win32Proj</Keyword>
    <ProjectGuid>{${PROJECT_GUID}}</ProjectGuid>
    <RootNamespace>${PROJECT_NAME}</RootNamespace>
    <WindowsTargetPlatformVersion>10.0</WindowsTargetPlatformVersion>
  </PropertyGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.Default.props" />
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'" Label="Configuration">
    <ConfigurationType>${CONFIGURATION_TYPE}</ConfigurationType>
    <UseDebugLibraries>true</UseDebugLibraries>
    <PlatformToolset>v143</PlatformToolset>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'" Label="Configuration">
    <ConfigurationType>${CONFIGURATION_TYPE}</ConfigurationType>
    <UseDebugLibraries>false</UseDebugLibraries>
    <PlatformToolset>v143</PlatformToolset>
    <WholeProgramOptimization>true</WholeProgramOptimization>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'" Label="Configuration">
    <ConfigurationType>${CONFIGURATION_TYPE}</ConfigurationType>
    <UseDebugLibraries>true</UseDebugLibraries>
    <PlatformToolset>v143</PlatformToolset>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'" Label="Configuration">
    <ConfigurationType>${CONFIGURATION_TYPE}</ConfigurationType>
    <UseDebugLibraries>false</UseDebugLibraries>
    <PlatformToolset>v143</PlatformToolset>
    <WholeProgramOptimization>true</WholeProgramOptimization>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.props" />
  <ImportGroup Label="ExtensionSettings">
  </ImportGroup>
  <ImportGroup Label="Shared">
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>
  <ImportGroup Label="PropertySheets" Condition="'$(Configuration)|$(Platform)'=='Release|x64'">
    <Import Project="$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props" Condition="exists('$(UserRootDir)\Microsoft.Cpp.$(Platform).user.props')" Label="LocalAppDataPlatform" />
  </ImportGroup>"""
  + """
  <PropertyGroup Label="UserMacros" />
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
    <LinkIncremental>true</LinkIncremental>
    <OutDir>$(SolutionDir)i686-pc-windows-msvc-debug\</OutDir>
    <IntDir>$(SolutionDir)i686-pc-windows-msvc-debug-obj\</IntDir>
    <TargetName>${PROJECT_NAME}</TargetName>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
    <LinkIncremental>false</LinkIncremental>
    <OutDir>$(SolutionDir)i686-pc-windows-msvc-release\</OutDir>
    <IntDir>$(SolutionDir)i686-pc-windows-msvc-release-obj\</IntDir>
    <TargetName>${PROJECT_NAME}</TargetName>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
    <LinkIncremental>true</LinkIncremental>
    <OutDir>$(SolutionDir)x86_64-pc-windows-msvc-debug\</OutDir>
    <IntDir>$(SolutionDir)x86_64-pc-windows-msvc-debug-obj\</IntDir>
    <TargetName>${PROJECT_NAME}</TargetName>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'">
    <LinkIncremental>false</LinkIncremental>
    <OutDir>$(SolutionDir)x86_64-pc-windows-msvc-release\</OutDir>
    <IntDir>$(SolutionDir)x86_64-pc-windows-msvc-release-obj\</IntDir>
    <TargetName>${PROJECT_NAME}</TargetName>
  </PropertyGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <SDLCheck>true</SDLCheck>
      <PreprocessorDefinitions>_CRT_SECURE_NO_WARNINGS;WIN32;_DEBUG;${MACRO};%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <ConformanceMode>true</ConformanceMode>
      <AdditionalIncludeDirectories>${INCLUDE_DIR}</AdditionalIncludeDirectories>
      <AdditionalOptions>/utf-8 %(AdditionalOptions)</AdditionalOptions>
      <DisableSpecificWarnings>4101;4102;5105</DisableSpecificWarnings>
      <LanguageStandard_C>stdc17</LanguageStandard_C>
    </ClCompile>
    <Link>
      <SubSystem>${SUBSYSTEM}</SubSystem>
      <GenerateDebugInformation>true</GenerateDebugInformation>
      <AdditionalDependencies>${LIBS};kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)</AdditionalDependencies>
      <AdditionalOptions>${EXPORTS} %(AdditionalOptions)</AdditionalOptions>
    </Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <FunctionLevelLinking>true</FunctionLevelLinking>
      <IntrinsicFunctions>true</IntrinsicFunctions>
      <SDLCheck>true</SDLCheck>
      <PreprocessorDefinitions>_CRT_SECURE_NO_WARNINGS;WIN32;NDEBUG;${MACRO};%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <ConformanceMode>true</ConformanceMode>
      <AdditionalIncludeDirectories>${INCLUDE_DIR}</AdditionalIncludeDirectories>
      <AdditionalOptions>/utf-8 %(AdditionalOptions)</AdditionalOptions>
      <DisableSpecificWarnings>4101;4102;5105</DisableSpecificWarnings>
      <LanguageStandard_C>stdc17</LanguageStandard_C>
      <RuntimeLibrary>MultiThreaded</RuntimeLibrary>
    </ClCompile>
    <Link>
      <SubSystem>${SUBSYSTEM}</SubSystem>
      <EnableCOMDATFolding>true</EnableCOMDATFolding>
      <OptimizeReferences>true</OptimizeReferences>
      <GenerateDebugInformation>true</GenerateDebugInformation>
      <AdditionalDependencies>${LIBS};kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)</AdditionalDependencies>
      <AdditionalOptions>${EXPORTS} %(AdditionalOptions)</AdditionalOptions>
    </Link>
  </ItemDefinitionGroup>"""
  + """
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <SDLCheck>true</SDLCheck>
      <PreprocessorDefinitions>_CRT_SECURE_NO_WARNINGS;_DEBUG;${MACRO};%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <ConformanceMode>true</ConformanceMode>
      <AdditionalIncludeDirectories>${INCLUDE_DIR}</AdditionalIncludeDirectories>
      <AdditionalOptions>/utf-8 %(AdditionalOptions)</AdditionalOptions>
      <DisableSpecificWarnings>4101;4102;5105</DisableSpecificWarnings>
      <LanguageStandard_C>stdc17</LanguageStandard_C>
    </ClCompile>
    <Link>
      <SubSystem>${SUBSYSTEM}</SubSystem>
      <GenerateDebugInformation>true</GenerateDebugInformation>
      <AdditionalDependencies>${LIBS};kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)</AdditionalDependencies>
      <AdditionalOptions>${EXPORTS} %(AdditionalOptions)</AdditionalOptions>
    </Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <FunctionLevelLinking>true</FunctionLevelLinking>
      <IntrinsicFunctions>true</IntrinsicFunctions>
      <SDLCheck>true</SDLCheck>
      <PreprocessorDefinitions>_CRT_SECURE_NO_WARNINGS;NDEBUG;${MACRO};%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <ConformanceMode>true</ConformanceMode>
      <AdditionalIncludeDirectories>${INCLUDE_DIR}</AdditionalIncludeDirectories>
      <AdditionalOptions>/utf-8 %(AdditionalOptions)</AdditionalOptions>
      <DisableSpecificWarnings>4101;4102;5105</DisableSpecificWarnings>
      <LanguageStandard_C>stdc17</LanguageStandard_C>
      <RuntimeLibrary>MultiThreaded</RuntimeLibrary>
    </ClCompile>
    <Link>
      <SubSystem>${SUBSYSTEM}</SubSystem>
      <EnableCOMDATFolding>true</EnableCOMDATFolding>
      <OptimizeReferences>true</OptimizeReferences>
      <GenerateDebugInformation>true</GenerateDebugInformation>
      <AdditionalDependencies>${LIBS};kernel32.lib;user32.lib;gdi32.lib;winspool.lib;comdlg32.lib;advapi32.lib;shell32.lib;ole32.lib;oleaut32.lib;uuid.lib;odbc32.lib;odbccp32.lib;%(AdditionalDependencies)</AdditionalDependencies>
      <AdditionalOptions>${EXPORTS} %(AdditionalOptions)</AdditionalOptions>
    </Link>
  </ItemDefinitionGroup>
  <ItemGroup>
    <ClCompile Include="${RUNTIME_DIR}\milone.c" />
    <ClCompile Include="${RUNTIME_DIR}\milone_platform.c" />
    ${SRCS}
  </ItemGroup>
  <ItemGroup>
    <ClInclude Include="${RUNTIME_DIR}\milone.h" />
  </ItemGroup>
  <Import Project="$(VCTargetsPath)\Microsoft.Cpp.targets" />
  <ImportGroup Label="ExtensionTargets">
  </ImportGroup>
</Project>
"""
  |> S.replace "${PROJECT_GUID}" (Guid.toString p.ProjectGuid)
  |> S.replace "${PROJECT_NAME}" p.ProjectName
  |> S.replace "${RUNTIME_DIR}" p.RuntimeDir
  |> S.replace "${INCLUDE_DIR}" p.IncludeDir
  |> S.replace "${CONFIGURATION_TYPE}" p.ConfigurationType
  |> S.replace "${MACRO}" p.Macro
  |> S.replace "${SUBSYSTEM}" p.SubSystem
  |> S.replace
       "${SRCS}"
       (p.CFiles
        |> List.map (fun cFile ->
          let path = Path.toString cFile

          "<ClCompile Include=\"" + path + "\"/>")
        |> S.concat "\n  ")

  |> S.replace "${LIBS}" (p.Libs |> List.map Path.toString |> S.concat ";")
  |> S.replace
       "${EXPORTS}"
       (p.Exports
        |> List.map (fun name -> "/EXPORT:" + name)
        |> S.concat " ")
