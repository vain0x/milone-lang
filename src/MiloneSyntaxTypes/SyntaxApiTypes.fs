module rec MiloneSyntaxTypes.SyntaxApiTypes

open MiloneShared.SharedTypes
open Std.StdPath
open MiloneSyntaxTypes.SyntaxTypes
open MiloneSyntaxTypes.TirTypes

/// `MILONE_HOME`
type MiloneHome = string

type WriteLogFun = string -> unit

type private SyntaxError = string * Loc

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type FetchModuleHost =
  { EntryProjectDir: ProjectDir
    EntryProjectName: ProjectName
    MiloneHome: MiloneHome

    ReadTextFile: ReadTextFileFun
    WriteLog: WriteLogFun }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type BinaryType =
  /// Executable.
  | Exe
  /// Shared object (.so) or dynamic-link library (.dll).
  | SharedObj
  /// Archive (.a) or static library (.lib).
  | StaticLib

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type SubSystem =
  | Console
  | Windows

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ManifestData =
  { /// Referenced non-entry projects.
    /// Path is relative to current project directory (where the manifest is).
    Projects: (ProjectName * ProjectDir * Loc) list
    Errors: (string * Loc) list

    // #experimental
    BinaryType: (BinaryType * Loc) option
    SubSystem: SubSystem option
    CSanitize: string option
    CStd: string
    CcList: (Path * Loc) list
    ObjList: (Path * Loc) list
    Libs: (string * Loc) list
    /// Passed to cc to compile a source file, only on Linux.
    LinuxCFlags: string option
    /// Passed to cc to link object files, only on Linux.
    LinuxLinkFlags: string option }

[<Struct; NoEquality; NoComparison>]
type SyntaxCtx = SyntaxCtx of obj

type SyntaxLayers = ModuleSyntaxData list list

[<NoEquality; NoComparison>]
type SyntaxAnalysisResult =
  | SyntaxAnalysisOk of TProgram * TirCtx
  | SyntaxAnalysisError of SyntaxError list * TirCtx option

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type SyntaxApi =
  { // getMiloneHomeEnv -> getHomeEnv -> MiloneHome
    GetMiloneHomeFromEnv: (unit -> string option) -> (unit -> string option) -> string
    SyntaxErrorsToString: SyntaxError list -> string
    NewSyntaxCtx: FetchModuleHost -> SyntaxCtx
    GetManifest: SyntaxCtx -> ManifestData
    PerformSyntaxAnalysis: SyntaxCtx -> SyntaxLayers * SyntaxAnalysisResult
    GenSyntaxTree: TokenizeFullResult -> ARoot -> SyntaxTree
    DumpSyntax: string -> string * ModuleSyntaxError list }
