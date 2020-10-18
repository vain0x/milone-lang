module MiloneLsp.LspLangService

open MiloneLang.Types

let tryReadFile fileName =
  try
    if System.IO.File.Exists(fileName)
    then System.IO.File.ReadAllText(fileName) |> Ok
    else Error(exn ("not existing"))

  with err -> Error err

let dirIsExcluded (dir: string) =
  let name = System.IO.Path.GetFileName(dir)

  name.StartsWith(".")
  || name.Contains("~")
  || name = "node_modules"
  || name = "target"
  || name = "bin"
  || name = "obj"

// ---------------------------------------------
// Document store
// ---------------------------------------------

type TokenizeResult = (Token * Loc) list

type ParseResult = AExpr * (string * Loc) list

type DocData =
  { Uri: string
    Version: int
    Text: string
    mutable Ok: bool
    mutable TokenizeResultOpt: TokenizeResult option
    mutable ParseResultOpt: ParseResult option }

let docs =
  System.Collections.Generic.Dictionary<string, DocData>()

let findDoc (uri: string): DocData option =
  match docs.TryGetValue(uri) with
  | true, docData -> Some docData
  | false, _ -> None

let openDoc (uri: string) (version: int) (text: string) =
  let docData: DocData =
    { Uri = uri
      Version = version
      Text = text
      Ok = true
      TokenizeResultOpt = None
      ParseResultOpt = None }

  eprintfn "INFO: Document opened uri:'%s' v:%d len:%d" uri version text.Length
  docs.Add(uri, docData)

let changeDoc (uri: string) (version: int) (text: string): unit =
  match findDoc uri with
  | Some _ ->
      let docData =
        { Uri = uri
          Version = version
          Text = text
          Ok = true
          TokenizeResultOpt = None
          ParseResultOpt = None }

      eprintfn "INFO: Document changed uri:'%s' v:%d len:%d" uri version text.Length
      docs.[uri] <- docData

  | None -> openDoc uri version text

let closeDoc (uri: string): unit =
  eprintfn "INFO: Document closed uri:'%s'" uri
  docs.Remove(uri) |> ignore

// ---------------------------------------------
// Analysis
// ---------------------------------------------

let tokenizeWithCaching (docData: DocData): TokenizeResult =
  match docData.TokenizeResultOpt with
  | Some it -> it

  | None ->
      let result = MiloneLang.Lexing.tokenize docData.Text
      docData.TokenizeResultOpt <- Some result
      result

let parseWithCaching (docData: DocData): ParseResult =
  match docData.ParseResultOpt with
  | Some it -> it

  | None ->
      let tokens = tokenizeWithCaching docData
      let result = MiloneLang.Parsing.parse tokens

      let ok =
        let _, errors = result
        List.isEmpty errors

      docData.ParseResultOpt <- Some result
      docData.Ok <- docData.Ok && ok
      result

let validateDoc (uri: string): (string * Loc) list =
  match findDoc uri with
  | Some docData ->
      let _, errors = parseWithCaching docData
      errors

  | None -> []

type ProjectInfo =
  { ProjectDir: string
    ProjectName: string
    EntryFile: string }

let validateWorkspace (rootUriOpt: string option): (string * string * Loc) list =
  match rootUriOpt with
  | None -> []
  | Some rootUri ->
      try
        let projects: ResizeArray<ProjectInfo> = ResizeArray()

        let rootDir = System.Uri(rootUri).LocalPath
        eprintfn "rootDir = '%s'" rootDir

        // Find projects recursively.
        let mutable stack = System.Collections.Generic.Stack()
        stack.Push(rootDir)

        while stack.Count <> 0 do
          let dir = stack.Pop()
          eprintfn "dir: '%s'" dir

          let projectName =
            System.IO.Path.GetFileNameWithoutExtension(dir)

          let tryAddProject entryFile =
            if System.IO.File.Exists(entryFile) then
              let project: ProjectInfo =
                { ProjectDir = dir
                  ProjectName = projectName
                  EntryFile = entryFile }

              projects.Add(project)

          tryAddProject (System.IO.Path.Combine(dir, projectName + ".milone"))
          tryAddProject (System.IO.Path.Combine(dir, projectName + ".fs"))

          let subdirs =
            try
              System.IO.Directory.GetDirectories(dir)
            with _ ->
              eprintfn "couldn't get list of files: '%s'" dir
              [||]

          for subdir in subdirs do
            if subdir |> dirIsExcluded |> not then stack.Push(subdir)

        // Process each project.
        for project in projects do
          let { ProjectDir = projectDir; ProjectName = projectName; EntryFile = entryFile } = project

          // Bundle.
          let expr, nameCtx, errorListList =
            let readModuleFile moduleName =
              eprintfn "readModuleFile '%s'" moduleName
              match tryReadFile (System.IO.Path.Combine(projectDir, moduleName + ".milone")) with
              | Ok it -> it
              | Error _ ->
                  match tryReadFile (System.IO.Path.Combine(projectDir, moduleName + ".fs")) with
                  | Ok it -> it
                  | Error _ ->
                      eprintfn "Module '%s' is missing in '%s'." moduleName projectDir
                      ""

            let parseModule (moduleName: string) tokens =
              eprintfn "parse: '%s'" moduleName
              MiloneLang.Parsing.parse tokens

            let nameCtx = MiloneLang.Helpers.nameCtxEmpty ()

            MiloneLang.Bundling.parseProjectModules readModuleFile parseModule projectName nameCtx

          // Name resolution.
          let expr, scopeCtx =
            MiloneLang.NameRes.nameRes (expr, nameCtx)

          // Type inference.
          let _expr, tyCtx =
            MiloneLang.Typing.infer (expr, scopeCtx, errorListList)

          // Collect errors.
          let errors =
            tyCtx
            |> MiloneLang.Records.tyCtxGetLogs
            |> List.map (fun (log, loc) -> MiloneLang.Helpers.logToString loc log, loc)

          eprintfn "validateWorkspace: errors = %A" errors
        []
      with err ->
        eprintfn "validateWorkspace: exn %A" err
        []
