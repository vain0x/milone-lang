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

let codeGenHir (writeLog: WriteLogFun) (modules: Hir.HProgram, hirCtx: HirCtx) : (DocId * CCode) list =
  writeLog "RecordRes"
  let modules, hirCtx = RecordRes.recordRes (modules, hirCtx)

  writeLog "Derive"
  let modules, hirCtx = Derive.deriveOps (modules, hirCtx)

  writeLog "ClosureConversion"

  let modules, hirCtx =
    ClosureConversion.closureConversion (modules, hirCtx)

  writeLog "EtaExpansion"

  let modules, hirCtx =
    EtaExpansion.etaExpansion (modules, hirCtx)

  writeLog "ComputeTyArgs"

  let modules, hirCtx =
    AutoBoxing.computeFunTyArgs (modules, hirCtx)

  writeLog "AutoBoxing"
  let modules, hirCtx = AutoBoxing.autoBox (modules, hirCtx)

  writeLog "Hoist"
  let modules, hirCtx = Hoist.hoist (modules, hirCtx)

  writeLog "TailRecOptimizing"

  let modules, hirCtx =
    TailRecOptimizing.tailRecOptimize (modules, hirCtx)

  writeLog "Monomorphizing"
  let modules, hirCtx = Monomorphizing.monify (modules, hirCtx)

  // Reduce info of variables.
  let modules: Hir.HModule2 list =
    modules
    |> List.map (fun (m: Hir.HModule) ->
      let varNameMap =
        m.Vars
        |> TMap.map (fun _ (varDef: Hir.VarDef) -> varDef.Name)

      let m: Hir.HModule2 =
        { DocId = m.DocId
          Vars = varNameMap
          Stmts = m.Stmts }

      m)

  writeLog "MonoTy"
  let modules, hirCtx = MonoTy.monoTy (modules, hirCtx)

  writeLog "Mir"
  let modules, mirCtx = MirGen.mirify (modules, hirCtx)

  writeLog "CirGen"
  let modules = CirGen.genCir (modules, mirCtx)

  writeLog "CirDump"

  let cFiles =
    modules
    |> List.map (fun (docId, cir) -> docId, CirDump.cirDump cir)

  cFiles

let codeGenUsingXir (writeLog: WriteLogFun) (modules: Hir.HProgram, hirCtx: HirCtx) =
  writeLog "RecordRes"
  let modules, hirCtx = RecordRes.recordRes (modules, hirCtx)

  writeLog "Derive"
  let modules, hirCtx = Derive.deriveOps (modules, hirCtx)

  writeLog "ClosureConversion"

  let modules, hirCtx =
    ClosureConversion.closureConversion (modules, hirCtx)

  writeLog "EtaExpansion"

  let modules, hirCtx =
    EtaExpansion.etaExpansion (modules, hirCtx)

  writeLog "ComputeTyArgs"

  let modules, hirCtx =
    AutoBoxing.computeFunTyArgs (modules, hirCtx)

  writeLog "AutoBoxing"
  let modules, hirCtx = AutoBoxing.autoBox (modules, hirCtx)

  writeLog "Hoist"
  let modules, hirCtx = Hoist.hoist (modules, hirCtx)

  writeLog "TailRecOptimizing"

  let modules, hirCtx =
    TailRecOptimizing.tailRecOptimize (modules, hirCtx)

  writeLog "Monomorphizing"
  let modules, hirCtx = Monomorphizing.monify (modules, hirCtx)

  // Reduce info of variables.
  let modules: Hir.HModule2 list =
    modules
    |> List.map (fun (m: Hir.HModule) ->
      let varNameMap =
        m.Vars
        |> TMap.map (fun _ (varDef: Hir.VarDef) -> varDef.Name)

      let m: Hir.HModule2 =
        { DocId = m.DocId
          Vars = varNameMap
          Stmts = m.Stmts }

      m)

  writeLog "MonoTy"
  let modules, hirCtx = MonoTy.monoTy (modules, hirCtx)

  let trace fmt args = __trace (S.format fmt args)
  let program = XirGen.xirGen trace (modules, hirCtx)
  // xirReuse trace program |> ignore
  XirToCir.xirToCir trace program |> ignore
  trace "OK" [ __dump program ]
