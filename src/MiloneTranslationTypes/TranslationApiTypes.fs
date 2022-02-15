module rec MiloneTranslationTypes.TranslationApiTypes

open MiloneShared.SharedTypes
open MiloneTranslationTypes.HirTypes

type WriteLogFun = string -> unit
type CCode = string

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type TranslationApi =
  { CodeGenHir: WriteLogFun -> HProgram * HirCtx -> (DocId * CCode) list }
