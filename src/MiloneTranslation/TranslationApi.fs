/// # TranslationApi
///
/// Exposes functions for transformation and code generation.
module rec MiloneTranslation.TranslationApi

open MiloneShared.SharedTypes
open Std.StdMap
open MiloneTranslation.HirTypes
open MiloneTranslation.TranslationApiTypes
open MiloneTranslation.Cir

module S = Std.StdString
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

let private codeGenHir
  entrypointName
  (df: DocIdToModulePath)
  (writeLog: WriteLogFun)
  (modules: HProgram, hirCtx: HirCtx)
  : (DocId * CCode) list * ExportName list =
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
  let modules: HModule2 list =
    modules
    |> List.map (fun (m: HModule) ->
      let varNameMap =
        m.Vars
        |> TMap.map (fun _ (varDef: VarDef) -> varDef.Name)

      let m: HModule2 =
        { DocId = m.DocId
          Vars = varNameMap
          Stmts = m.Stmts }

      m)

  writeLog "MonoTy"
  let modules, hirCtx = MonoTy.monoTy (modules, hirCtx)

  writeLog "Mir"
  let modules, mirCtx = MirGen.mirify (modules, hirCtx)

  writeLog "CirGen"

  let modules =
    CirGen.genCir entrypointName df (modules, mirCtx)

  writeLog "CirDump"

  let cFiles =
    modules
    |> List.map (fun (docId, cir) -> docId, CirDump.cirDump cir)

  let exportNames =
    modules
    |> List.collect (fun (_, decls) ->
      decls
      |> List.choose (fun decl ->
        match decl with
        | CFunDecl (ident, _, _, _, _) -> Some ident
        | _ -> None))

  cFiles, exportNames

let newTranslationApi () : TranslationApi = { CodeGenHir = codeGenHir }
