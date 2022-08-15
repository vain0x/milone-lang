module rec MiloneSyntaxTypes.SyntaxApiTypes

open MiloneShared.SharedTypes
open MiloneShared.UtilParallel
open MiloneSyntaxTypes.SyntaxTypes
open MiloneSyntaxTypes.TirTypes
open Std.StdPath

/// `MILONE_HOME`
type MiloneHome = string

type WriteLogFun = string -> unit

type SyntaxError = string * Loc

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

type SyntaxLayers = ModuleSyntaxData2 list list

[<NoEquality; NoComparison>]
type SyntaxAnalysisResult =
  | SyntaxAnalysisOk of TProgram * TirCtx
  | SyntaxAnalysisError of SyntaxError list * TirCtx option

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type SyntaxApi =
  { // getMiloneHomeEnv -> getHomeEnv -> MiloneHome
    GetMiloneHomeFromEnv: (unit -> string option) -> (unit -> string option) -> string
    GetStdLibProjects: MiloneHome -> (ProjectName * ProjectDir) list
    ReadSourceFile: ReadTextFileFun -> string -> Future<string option>
    ParseManifest: DocId -> string -> ManifestData
    // beingCore:bool
    Parse: bool -> SourceCode -> ARoot * ModuleSyntaxError list
    FindDependentModules: ARoot -> (ProjectName * ModuleName * Pos) list

    SyntaxErrorsToString: SyntaxError list -> string

    PerformSyntaxAnalysis: WriteLogFun -> SyntaxLayers -> SyntaxAnalysisResult

    GenSyntaxTree: TokenizeFullResult -> ARoot -> SyntaxTree
    DumpSyntax: string -> string * ModuleSyntaxError list }
