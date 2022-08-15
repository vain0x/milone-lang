module rec MiloneCli.ModuleFetch

open MiloneShared.SharedTypes
open MiloneShared.UtilParallel
open MiloneShared.UtilSymbol
open MiloneSyntax.SyntaxApiTypes
open MiloneSyntax.SyntaxTypes
open Std.StdMap

module S = Std.StdString

/// File extension. Starts with `.`.
type private FileExt = string

type private FileExistsFun = string -> bool

type private FetchModuleFun2 =
  ProjectName
    -> ModuleName
    -> Future<(ModuleSyntaxData2 * (ProjectName * ModuleName * Pos) list * ModuleSyntaxError list) option>

// -----------------------------------------------
// Util
// -----------------------------------------------

// note: avoid using this function so that DocId can be computed by clients.
let computeDocId (p: ProjectName) (m: ModuleName) : DocId = Symbol.intern (p + "." + m)

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type FetchModuleHost =
  { EntryProjectDir: ProjectDir
    EntryProjectName: ProjectName
    EntryModulePathOpt: string option
    MiloneHome: MiloneHome
    Manifest: ManifestData

    ReadTextFile: ReadTextFileFun
    WriteLog: WriteLogFun }

let prepareFetchModule (sApi: SyntaxApi) (host: FetchModuleHost) : FetchModuleFun2 =
  let entryProjectName = host.EntryProjectName
  let entryProjectDir = host.EntryProjectDir
  let miloneHome = host.MiloneHome
  let readTextFile = host.ReadTextFile
  let manifest = host.Manifest

  let projects =
    let manifestProjects =
      manifest.Projects
      |> List.map (fun (name, dir, _) -> name, entryProjectDir + "/" + dir)

    let projects = TMap.ofList compare manifestProjects

    sApi.GetStdLibProjects miloneHome
    |> List.fold (fun projects (name, dir) -> projects |> TMap.add name dir) projects
    |> TMap.add entryProjectName entryProjectDir

  let fetchModule: FetchModuleFun2 =
    fun projectName moduleName ->
      let filename =
        match host.EntryModulePathOpt with
        | Some path when
          projectName = entryProjectName
          && moduleName = entryProjectName
          ->
          path
        | _ ->
          let projectDir =
            match projects |> TMap.tryFind projectName with
            | Some it -> it
            | None -> entryProjectDir + "/../" + projectName

          projectDir + "/" + moduleName + ".milone"

      sApi.ReadSourceFile readTextFile filename
      |> Future.map (fun result ->
        match result with
        | None -> None

        | Some text ->
          // #parse
          let docId = computeDocId projectName moduleName

          let beingCore = projectName = "MiloneCore"
          let ast, errors = sApi.Parse beingCore text

          let s: ModuleSyntaxData2 =
            { ProjectName = projectName
              ModuleName = moduleName
              DocId = docId
              Ast = ast }

          let dependentModules = sApi.FindDependentModules ast

          Some(s, dependentModules, errors))

  fetchModule
