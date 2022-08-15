module rec MiloneTranslation.TranslationApiTypes

open MiloneShared.SharedTypes
open MiloneTranslation.HirTypes

/// Name of entrypoint function, typically `main`
type EntrypointName = string

/// Name of symbol to be exported
type ExportName = string

type WriteLogFun = string -> unit
type CCode = string

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type TranslationApi =
  { CodeGenHir: EntrypointName -> WriteLogFun -> HProgram * HirCtx -> (DocId * CCode) list * ExportName list }
