module rec MiloneTranslationTypes.TranslationApiTypes

open MiloneShared.SharedTypes
open MiloneTranslationTypes.HirTypes

type EntrypointName = string
type WriteLogFun = string -> unit
type CCode = string

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type TranslationApi =
  { CodeGenHir: EntrypointName -> WriteLogFun -> HProgram * HirCtx -> (DocId * CCode) list }
