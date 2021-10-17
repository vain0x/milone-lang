/// # TranslationApi
///
/// Exposes functions for transformation and code generation.
module rec MiloneTranslation.TranslationApi

open MiloneShared.SharedTypes
open MiloneStd.StdMap
open MiloneTranslation.Hir

module S = MiloneStd.StdString
module AutoBoxing = MiloneTranslation.AutoBoxing
module CirDump = MiloneTranslation.CirDump
module CirGen = MiloneTranslation.CirGen
module ClosureConversion = MiloneTranslation.ClosureConversion
module Derive = MiloneTranslation.Derive
module EtaExpansion = MiloneTranslation.EtaExpansion
module Hoist = MiloneTranslation.Hoist
module MirGen = MiloneTranslation.MirGen
module Monomorphizing = MiloneTranslation.Monomorphizing
module MonoTy = MiloneTranslation.MonoTy
module RecordRes = MiloneTranslation.RecordRes
module TailRecOptimizing = MiloneTranslation.TailRecOptimizing

type private WriteLogFun = string -> unit
type private CCode = string

let codeGenHir (writeLog: WriteLogFun) (modules: Hir.HProgram, tyCtx: TyCtx) : (DocId * CCode) list =
  writeLog "RecordRes"
  let modules, tyCtx = RecordRes.recordRes (modules, tyCtx)

  writeLog "Derive"
  let modules, tyCtx = Derive.deriveOps (modules, tyCtx)

  writeLog "ClosureConversion"

  let modules, tyCtx =
    ClosureConversion.closureConversion (modules, tyCtx)

  writeLog "EtaExpansion"

  let modules, tyCtx =
    EtaExpansion.etaExpansion (modules, tyCtx)

  writeLog "ComputeTyArgs"

  let modules, tyCtx =
    AutoBoxing.computeFunTyArgs (modules, tyCtx)

  writeLog "AutoBoxing"
  let modules, tyCtx = AutoBoxing.autoBox (modules, tyCtx)

  writeLog "Hoist"
  let modules, tyCtx = Hoist.hoist (modules, tyCtx)

  writeLog "TailRecOptimizing"

  let modules, tyCtx =
    TailRecOptimizing.tailRecOptimize (modules, tyCtx)

  writeLog "Monomorphizing"
  let modules, tyCtx = Monomorphizing.monify (modules, tyCtx)

  // Reduce info of variables.
  let modules: Hir.HModule2 list =
    modules
    |> List.map
         (fun (m: Hir.HModule) ->
           let varNameMap =
             m.Vars
             |> TMap.map (fun _ (varDef: Hir.VarDef) -> varDef.Name)

           let m: Hir.HModule2 =
             { DocId = m.DocId
               Vars = varNameMap
               Stmts = m.Stmts }

           m)

  writeLog "MonoTy"
  let modules, tyCtx = MonoTy.monoTy (modules, tyCtx)

  writeLog "Mir"
  let modules, mirCtx = MirGen.mirify (modules, tyCtx)

  writeLog "CirGen"
  let modules = CirGen.genCir (modules, mirCtx)

  writeLog "CirDump"

  let cFiles =
    modules
    |> List.map (fun (docId, cir) -> docId, CirDump.cirDump cir)

  cFiles
