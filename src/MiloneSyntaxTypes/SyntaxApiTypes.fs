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
type ManifestData =
  { /// Referenced non-entry projects.
    /// Path is relative to current project directory (where the manifest is).
    Projects: (ProjectName * ProjectDir * Loc) list
    Errors: (string * Loc) list

    // #experimental
    CSanitize: string option
    CStd: string
    CcList: (Path * Loc) list
    ObjList: (Path * Loc) list
    Libs: (string * Loc) list }

[<Struct; NoEquality; NoComparison>]
type SyntaxCtx = SyntaxCtx of obj

type SyntaxLayers = ModuleSyntaxData list list

[<NoEquality; NoComparison>]
type SyntaxAnalysisResult =
  | SyntaxAnalysisOk of TProgram * TirCtx
  | SyntaxAnalysisError of SyntaxError list * TirCtx option

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type SyntaxApi =
  { /// getMiloneHomeEnv -> getHomeEnv -> MiloneHome
    GetMiloneHomeFromEnv: (unit -> string option) -> (unit -> string option) -> string
    SyntaxErrorsToString: SyntaxError list -> string
    NewSyntaxCtx: FetchModuleHost -> SyntaxCtx
    GetManifest: SyntaxCtx -> ManifestData
    PerformSyntaxAnalysis: SyntaxCtx -> SyntaxLayers * SyntaxAnalysisResult
    DumpSyntax: string -> string * ModuleSyntaxError list }
