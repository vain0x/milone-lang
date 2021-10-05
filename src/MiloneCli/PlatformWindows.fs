module rec MiloneCli.PlatformWindows

open MiloneStd.StdPath

module S = MiloneStd.StdString

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
  let years = [ 2019; 2017; 2015; 2021 ]

  let editions =
    [ "Community"
      "Enterprise"
      "Professional"
      "BuildTools" ]

  let msBuildPath (year: int) edition =
    Path(
      "C:/Program Files (x86)/Microsoft Visual Studio/"
      + string year
      + "/"
      + edition
      + "/MSBuild/Current/Bin/MSBuild.exe"
    )

  years
  |> List.collect
       (fun year ->
         editions
         |> List.map (fun edition -> msBuildPath year edition))
  |> List.tryFind fileExists
  |> Option.defaultValue (Path "MSBuild.exe")

// -----------------------------------------------
// Interface
// -----------------------------------------------

type BuildOnWindowsParams =
  { ProjectName: string
    CFiles: Path list

    MiloneHome: Path
    TargetDir: Path

    NewGuid: NewGuidFun
    DirCreate: Path -> unit
    FileExists: FileExistsFun
    FileWrite: Path -> string -> unit
    RunCommand: Path -> string list -> unit }

let buildOnWindows (p: BuildOnWindowsParams) : unit =
  // Generate solution/project files for VC++ project.
  let projectGuid = p.NewGuid()

  let slnFile =
    Path.join p.TargetDir (Path(p.ProjectName + ".sln"))

  let slnXml =
    let p: SolutionXmlParams =
      { ProjectGuid = projectGuid
        ProjectName = p.ProjectName
        Guid1 = p.NewGuid()
        Guid2 = p.NewGuid() }

    renderSolutionXml p

  let vcxprojFile =
    Path.join p.TargetDir (Path(p.ProjectName + "/" + p.ProjectName + ".vcxproj"))

  let vcxprojXml =
    let runtimeDir =
      Path.join p.MiloneHome (Path "runtime")
      |> Path.toString

    let p: VcxProjectParams =
      { MiloneTargetDir = p.TargetDir
        CFiles = p.CFiles
        ProjectGuid = projectGuid
        ProjectName = p.ProjectName
        IncludeDir = runtimeDir
        RuntimeDir = runtimeDir }

    renderVcxProjectXml p

  [ slnFile, slnXml
    vcxprojFile, vcxprojXml ]
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
      "-p:Configuration=Release;Platform=x64"
      "-v:quiet"
      "-nologo" ]

type RunOnWindowsParams =
  { // Milone build result
    ProjectName: string
    CFiles: Path list

    // Build options
    MiloneHome: Path
    TargetDir: Path

    // Run options
    Args: string list

    // Effects
    NewGuid: NewGuidFun
    DirCreate: Path -> unit
    FileExists: FileExistsFun
    FileWrite: Path -> string -> unit
    RunCommand: Path -> string list -> unit }

let runOnWindows (p: RunOnWindowsParams) : unit =
  let () =
    let p: BuildOnWindowsParams =
      { ProjectName = p.ProjectName
        CFiles = p.CFiles
        MiloneHome = p.MiloneHome
        TargetDir = p.TargetDir
        NewGuid = p.NewGuid
        DirCreate = p.DirCreate
        FileExists = p.FileExists
        FileWrite = p.FileWrite
        RunCommand = p.RunCommand }

    buildOnWindows p

  let exeFile =
    Path.join p.TargetDir (Path("target/x64-Release-bin/" + p.ProjectName + ".exe"))

  p.RunCommand exeFile p.Args

// =============================================================================

// -----------------------------------------------
// Template: solution
// -----------------------------------------------

type private SolutionXmlParams =
  { Guid1: Guid
    Guid2: Guid
    ProjectGuid: Guid
    ProjectName: string }

let private renderSolutionXml (p: SolutionXmlParams) : string =
  """Microsoft Visual Studio Solution File, Format Version 12.00
# Visual Studio Version 16
VisualStudioVersion = 16.0.30225.117
MinimumVisualStudioVersion = 10.0.40219.1
Project("{${GUID1}}") = "${PROJECT_NAME}", "${PROJECT_NAME}\${PROJECT_NAME}.vcxproj", "{${PROJECT_GUID}}"
EndProject
Global
	GlobalSection(SolutionConfigurationPlatforms) = preSolution
		Debug|x64 = Debug|x64
		Debug|x86 = Debug|x86
		Release|x64 = Release|x64
		Release|x86 = Release|x86
	EndGlobalSection
	GlobalSection(ProjectConfigurationPlatforms) = postSolution
		{${PROJECT_GUID}}.Debug|x64.ActiveCfg = Debug|x64
		{${PROJECT_GUID}}.Debug|x64.Build.0 = Debug|x64
		{${PROJECT_GUID}}.Debug|x86.ActiveCfg = Debug|Win32
		{${PROJECT_GUID}}.Debug|x86.Build.0 = Debug|Win32
		{${PROJECT_GUID}}.Release|x64.ActiveCfg = Release|x64
		{${PROJECT_GUID}}.Release|x64.Build.0 = Release|x64
		{${PROJECT_GUID}}.Release|x86.ActiveCfg = Release|Win32
		{${PROJECT_GUID}}.Release|x86.Build.0 = Release|Win32
	EndGlobalSection
	GlobalSection(SolutionProperties) = preSolution
		HideSolutionNode = FALSE
	EndGlobalSection
	GlobalSection(ExtensibilityGlobals) = postSolution
		SolutionGuid = {${GUID2}}
	EndGlobalSection
EndGlobal
"""
  |> S.replace "${GUID1}" (Guid.toString p.Guid1)
  |> S.replace "${GUID2}" (Guid.toString p.Guid2)
  |> S.replace "${PROJECT_GUID}" (Guid.toString p.ProjectGuid)
  |> S.replace "${PROJECT_NAME}" p.ProjectName

// -----------------------------------------------
// Template: vcxproj
// -----------------------------------------------

type private VcxProjectParams =
  { MiloneTargetDir: Path
    CFiles: Path list

    ProjectGuid: Guid
    ProjectName: string
    IncludeDir: string
    RuntimeDir: string }

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
    <ConfigurationType>Application</ConfigurationType>
    <UseDebugLibraries>true</UseDebugLibraries>
    <PlatformToolset>v142</PlatformToolset>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <UseDebugLibraries>false</UseDebugLibraries>
    <PlatformToolset>v142</PlatformToolset>
    <WholeProgramOptimization>true</WholeProgramOptimization>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <UseDebugLibraries>true</UseDebugLibraries>
    <PlatformToolset>v142</PlatformToolset>
    <CharacterSet>Unicode</CharacterSet>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'" Label="Configuration">
    <ConfigurationType>Application</ConfigurationType>
    <UseDebugLibraries>false</UseDebugLibraries>
    <PlatformToolset>v142</PlatformToolset>
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
    <OutDir>$(SolutionDir)target\$(Platform)-$(Configuration)-bin\</OutDir>
    <IntDir>$(SolutionDir)target\$(Platform)-$(Configuration)-obj\</IntDir>
    <TargetName>${PROJECT_NAME}</TargetName>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
    <LinkIncremental>false</LinkIncremental>
    <OutDir>$(SolutionDir)target\$(Platform)-$(Configuration)-bin\</OutDir>
    <IntDir>$(SolutionDir)target\$(Platform)-$(Configuration)-obj\</IntDir>
    <TargetName>${PROJECT_NAME}</TargetName>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
    <LinkIncremental>true</LinkIncremental>
    <OutDir>$(SolutionDir)target\$(Platform)-$(Configuration)-bin\</OutDir>
    <IntDir>$(SolutionDir)target\$(Platform)-$(Configuration)-obj\</IntDir>
    <TargetName>${PROJECT_NAME}</TargetName>
  </PropertyGroup>
  <PropertyGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'">
    <LinkIncremental>false</LinkIncremental>
    <OutDir>$(SolutionDir)target\$(Platform)-$(Configuration)-bin\</OutDir>
    <IntDir>$(SolutionDir)target\$(Platform)-$(Configuration)-obj\</IntDir>
    <TargetName>${PROJECT_NAME}</TargetName>
  </PropertyGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|Win32'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <SDLCheck>true</SDLCheck>
      <PreprocessorDefinitions>_CRT_SECURE_NO_WARNINGS;WIN32;_DEBUG;_CONSOLE;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <ConformanceMode>true</ConformanceMode>
      <AdditionalIncludeDirectories>${INCLUDE_DIR}</AdditionalIncludeDirectories>
      <AdditionalOptions>/utf-8 %(AdditionalOptions)</AdditionalOptions>
      <DisableSpecificWarnings>4101;4102;5105</DisableSpecificWarnings>
      <LanguageStandard_C>stdc17</LanguageStandard_C>
    </ClCompile>
    <Link>
      <SubSystem>Console</SubSystem>
      <GenerateDebugInformation>true</GenerateDebugInformation>
    </Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Release|Win32'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <FunctionLevelLinking>true</FunctionLevelLinking>
      <IntrinsicFunctions>true</IntrinsicFunctions>
      <SDLCheck>true</SDLCheck>
      <PreprocessorDefinitions>_CRT_SECURE_NO_WARNINGS;WIN32;NDEBUG;_CONSOLE;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <ConformanceMode>true</ConformanceMode>
      <AdditionalIncludeDirectories>${INCLUDE_DIR}</AdditionalIncludeDirectories>
      <AdditionalOptions>/utf-8 %(AdditionalOptions)</AdditionalOptions>
      <DisableSpecificWarnings>4101;4102;5105</DisableSpecificWarnings>
      <LanguageStandard_C>stdc17</LanguageStandard_C>
      <RuntimeLibrary>MultiThreaded</RuntimeLibrary>
    </ClCompile>
    <Link>
      <SubSystem>Console</SubSystem>
      <EnableCOMDATFolding>true</EnableCOMDATFolding>
      <OptimizeReferences>true</OptimizeReferences>
      <GenerateDebugInformation>true</GenerateDebugInformation>
    </Link>
  </ItemDefinitionGroup>"""
  + """
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Debug|x64'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <SDLCheck>true</SDLCheck>
      <PreprocessorDefinitions>_CRT_SECURE_NO_WARNINGS;_DEBUG;_CONSOLE;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <ConformanceMode>true</ConformanceMode>
      <AdditionalIncludeDirectories>${INCLUDE_DIR}</AdditionalIncludeDirectories>
      <AdditionalOptions>/utf-8 %(AdditionalOptions)</AdditionalOptions>
      <DisableSpecificWarnings>4101;4102;5105</DisableSpecificWarnings>
      <LanguageStandard_C>stdc17</LanguageStandard_C>
    </ClCompile>
    <Link>
      <SubSystem>Console</SubSystem>
      <GenerateDebugInformation>true</GenerateDebugInformation>
    </Link>
  </ItemDefinitionGroup>
  <ItemDefinitionGroup Condition="'$(Configuration)|$(Platform)'=='Release|x64'">
    <ClCompile>
      <WarningLevel>Level3</WarningLevel>
      <FunctionLevelLinking>true</FunctionLevelLinking>
      <IntrinsicFunctions>true</IntrinsicFunctions>
      <SDLCheck>true</SDLCheck>
      <PreprocessorDefinitions>_CRT_SECURE_NO_WARNINGS;NDEBUG;_CONSOLE;%(PreprocessorDefinitions)</PreprocessorDefinitions>
      <ConformanceMode>true</ConformanceMode>
      <AdditionalIncludeDirectories>${INCLUDE_DIR}</AdditionalIncludeDirectories>
      <AdditionalOptions>/utf-8 %(AdditionalOptions)</AdditionalOptions>
      <DisableSpecificWarnings>4101;4102;5105</DisableSpecificWarnings>
      <LanguageStandard_C>stdc17</LanguageStandard_C>
      <RuntimeLibrary>MultiThreaded</RuntimeLibrary>
    </ClCompile>
    <Link>
      <SubSystem>Console</SubSystem>
      <EnableCOMDATFolding>true</EnableCOMDATFolding>
      <OptimizeReferences>true</OptimizeReferences>
      <GenerateDebugInformation>true</GenerateDebugInformation>
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
  |> S.replace
       "${SRCS}"
       (p.CFiles
        |> List.map
             (fun cFile ->
               let path = Path.toString cFile

               "<ClCompile Include=\"../" + path + "\"/>")
        |> S.concat "\n  ")
