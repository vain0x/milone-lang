module rec MiloneCli.BuildWs

open MiloneShared.SharedTypes
open MiloneShared.Util
open MiloneShared.UtilParallel
open MiloneShared.UtilProfiler
open MiloneShared.UtilSymbol
open Std.StdError
open Std.StdList
open Std.StdMap
open Std.StdPath
open MiloneSyntax.SyntaxTypes
open MiloneSyntax.SyntaxApiTypes
open MiloneTranslation.TranslationApiTypes

// module BuildWs = MiloneCli.BuildWs
module C = Std.StdChar
module S = Std.StdString
module Lower = MiloneCli.Lower
module ModuleFetch = MiloneCli.ModuleFetch
module ModuleLoad = MiloneCli.ModuleLoad
module PL = MiloneCli.PlatformLinux
module PW = MiloneCli.PlatformWindows

let private pathStrTrimEndPathSep (s: string) : string =
  s |> Path.ofString |> Path.trimEndSep |> Path.toString

let private pathStrToStem (s: string) : string =
  s |> Path.ofString |> Path.fileStem |> Path.toString

let private pathStrToFileName (s: string) : string =
  s |> Path.ofString |> Path.basename |> Path.toString

let private pathDirname (s: string) : string =
  match S.findLastIndex "/" s with
  | Some i when i <> 0 -> s.[0 .. i - 1]
  | _ -> failwith ("no dirname of '" + s + "'")

// #pathJoin
let private pathJoin (l: string) (r: string) =
  let slash (s: string) = s |> S.replace "\\" "/"

  let isRooted (s: string) =
    s |> S.startsWith "/" || s.Length >= 3 && s.[1] = ':' && s.[2] = '/'

  let l = slash l
  let r = slash r

  if isRooted r then r
  else if r = "." then l
  else l + "/" + r

type private Origin =
  { DocId: DocId
    ProjectDir: ProjectDir
    ProjectName: ProjectName
    ModuleName: ModuleName
    Pos: Pos }

type private Request =
  { ProjectName: ProjectName
    ModuleName: ModuleName
    Base: ProjectDir
    OriginOpt: Origin option }

type private State =
  { Requested: TreeMap<ProjectDir * ModuleName, unit>
    Map: TreeMap<ProjectDir * ModuleName, ModuleSyntaxData2> }

module private State =
  let internal init: State =
    { Requested = TMap.empty (pairCompare compare compare)
      Map = TMap.empty (pairCompare compare compare) }

  let add (state: State) (projectDir: ProjectDir) (s: ModuleSyntaxData2) =
    { state with
        Map = state.Map |> TMap.add (projectDir, s.ModuleName) s }

type internal BuildWsOptions =
  { MiloneHome: MiloneHome
    WorkDir: string
    ReadTextFile: string -> Future<string option>
    Args: string list }

let internal cliBuildWs (sApi: SyntaxApi) (tApi: TranslationApi) (bo: BuildWsOptions) =
  let stdProjects = sApi.GetStdLibProjects bo.MiloneHome |> TMap.ofList compare
  let tryStd projectName = stdProjects |> TMap.tryFind projectName

  // Compute initial requests: all entry modules of workspaces in the arguments.
  let requests =
    bo.Args
    |> List.map (fun arg ->
      let arg = pathJoin bo.WorkDir arg

      let projectDir = arg |> Path.ofString |> Path.trimEndSep |> Path.toString

      let projectName =
        arg |> Path.ofString |> Path.trimEndSep |> Path.basename |> Path.toString

      printfn "initial %s" projectDir

      ({ Base = projectDir
         ProjectName = projectName
         ModuleName = projectName
         OriginOpt = None }
      : Request))

  let rec loadRec (state: State) (requests: Request list) =
    match requests with
    | [] -> state

    | r :: requests ->
      // Determine the project dir that the requested module should belong to.
      let rProjectDir =
        let baseProjectName = pathStrToFileName r.Base

        if r.ProjectName = baseProjectName then
          r.Base
        else
          match tryStd r.ProjectName with
          | Some it -> it
          | None ->
            // sibling
            pathJoin (pathDirname r.Base) r.ProjectName

      // Suppress duplicated requesting.
      if state.Requested |> TMap.containsKey (rProjectDir, r.ModuleName) then
        printfn "dup %s/%s " rProjectDir r.ModuleName
        loadRec state requests
      else
        let state =
          { state with
              Requested = state.Requested |> TMap.add (rProjectDir, r.ModuleName) () }

        let filename = pathJoin rProjectDir (r.ModuleName + ".milone")
        printfn "fetch %s" filename

        let result =
          sApi.ReadSourceFile bo.ReadTextFile filename
          |> Future.map (fun result ->
            match result with
            | None -> None

            | Some(filename, contents) ->
              let docId = Symbol.intern filename

              let ast, errors =
                let parseInput: ParseInput =
                  { SourceCode = contents
                    BeingCore = r.ProjectName = "MiloneCore" }

                sApi.Parse parseInput

              let s: ModuleSyntaxData2 =
                { ProjectName = r.ProjectName
                  ModuleName = r.ModuleName
                  DocId = docId
                  Ast = ast }

              let dependentModules = sApi.FindDependentModules ast

              Some(s, dependentModules, errors))
          |> Future.wait

        let state, requests =
          match result with
          | None -> state, requests
          | Some(moduleSyntaxData, dependentModules, errors) ->
            let state = State.add state rProjectDir moduleSyntaxData

            // Add dependent modules to requests.
            let requests =
              dependentModules
              |> List.fold
                (fun rs d ->
                  let dProjectName, dModuleName, dPos = d

                  let origin: Origin =
                    { DocId = moduleSyntaxData.DocId
                      ProjectDir = rProjectDir
                      ProjectName = moduleSyntaxData.ProjectName
                      ModuleName = moduleSyntaxData.ModuleName
                      Pos = dPos }

                  let r: Request =
                    { ProjectName = dProjectName
                      ModuleName = dModuleName
                      Base = rProjectDir
                      OriginOpt = Some origin }

                  printfn "  -> %s.%s" dProjectName dModuleName
                  r :: rs)
                requests

            state, requests

        loadRec state requests

  let _result = loadRec State.init requests

  // "file:a/b/c/c.milone"
  // "project:a/b/c/"

  0
