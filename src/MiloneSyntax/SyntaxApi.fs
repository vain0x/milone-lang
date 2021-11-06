/// # SyntaxApi
///
/// Exposed API of the project.
module rec MiloneSyntax.SyntaxApi

open MiloneShared.SharedTypes
open MiloneShared.Util
open MiloneSyntax.Syntax
open MiloneStd.StdMap
open MiloneStd.StdPath

module ArityCheck = MiloneSyntax.ArityCheck
module AstBundle = MiloneSyntax.AstBundle
module NameRes = MiloneSyntax.NameRes
module Manifest = MiloneSyntax.Manifest
module S = MiloneStd.StdString
module SyntaxParse = MiloneSyntax.SyntaxParse
module SyntaxTokenize = MiloneSyntax.SyntaxTokenize
module Tir = MiloneSyntax.Tir
module Typing = MiloneSyntax.Typing
module TySystem = MiloneSyntax.TySystem

/// `.fs` or `.milone`.
type private SourceExt = string

/// `MILONE_HOME`
type private MiloneHome = string

type private FileExistsFun = string -> bool

let private changeExt (ext: FileExt) (path: string) : string =
  assert (ext |> S.startsWith ".")

  let (Path basename), _ = Path path |> Path.cutExt
  basename + ext

// -----------------------------------------------
// Std library
// -----------------------------------------------

let private getStdLibNames () = [ "MiloneCore"; "MiloneStd" ]

let private computeStdLibProjectDir (miloneHome: MiloneHome) (projectName: ProjectName) : ProjectDir =
  miloneHome + "/milone_libs/" + projectName

let getStdLibProjects (miloneHome: MiloneHome) : (ProjectName * ProjectDir) list =
  getStdLibNames ()
  |> List.map (fun name -> name, computeStdLibProjectDir miloneHome name)

// -----------------------------------------------
// Prelude resolution
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ModuleKind =
  | MiloneCore
  | Regular

let getModuleKind projectName _moduleName =
  match projectName with
  | "MiloneCore" -> ModuleKind.MiloneCore
  | _ -> ModuleKind.Regular

let private preludeFuns = [ "ignore"; "id"; "fst"; "snd" ]

let private knownModules =
  [ "List"
    "Option"
    "Prelude"
    "String" ]

let private isPreludeFun funName =
  preludeFuns
  |> List.exists (fun name -> name = funName)

let private isKnownModule moduleName =
  knownModules
  |> List.exists (fun name -> name = moduleName)

/// Generates decls for each MiloneCore module
/// whose name appears in the token stream.
let private resolveMiloneCoreDeps kind tokens ast =
  let analyze tokens =
    let rec go preludeOpt acc tokens =
      match tokens with
      | [] -> preludeOpt, acc

      | (IdentToken name, pos) :: tokens when Option.isNone preludeOpt && isPreludeFun name -> go (Some pos) acc tokens

      | (IdentToken moduleName, pos) :: (DotToken, _) :: tokens -> go preludeOpt ((moduleName, pos) :: acc) tokens

      | _ :: tokens -> go preludeOpt acc tokens

    let preludeOpt, moduleNames = go None [] tokens

    let add acc (moduleName, pos) =
      if (acc |> TMap.containsKey moduleName |> not)
         && isKnownModule moduleName then
        acc |> TMap.add moduleName pos
      else
        acc

    let moduleMap =
      moduleNames |> List.fold add (TMap.empty compare)

    preludeOpt, moduleMap

  let insertOpenDecls decls =
    let preludeOpt, moduleMap = analyze tokens

    let decls =
      moduleMap
      |> TMap.fold
           (fun decls moduleName pos ->
             AModuleSynonymDecl(
               Name(moduleName, pos),
               [ Name("MiloneCore", pos)
                 Name(moduleName, pos) ],
               pos
             )
             :: decls)
           decls

    match preludeOpt with
    | Some pos ->
      AOpenDecl(
        [ Name("MiloneCore", pos)
          Name("Prelude", pos) ],
        pos
      )
      :: decls
    | None -> decls

  let updateAst ast =
    let (ARoot (headOpt, decls)) = ast
    ARoot(headOpt, insertOpenDecls decls)

  match kind with
  | ModuleKind.MiloneCore -> ast
  | _ -> updateAst ast

// -----------------------------------------------
// Utilities
// -----------------------------------------------

let getMiloneHomeFromEnv (getMiloneHomeEnv: unit -> string option) (getHomeEnv: unit -> string option) : MiloneHome =
  match getMiloneHomeEnv () with
  | Some miloneHome ->
    assert (miloneHome <> "")
    miloneHome

  | None ->
    match getHomeEnv () with
    | Some home -> home + "/.milone"
    | None -> failwith "$MILONE_HOME and $HOME are missing."

/// Computes preferred filename of source file.
let chooseSourceExt (fileExists: FileExistsFun) filename =
  let fs = changeExt ".fs" filename

  if fileExists filename || not (fileExists fs) then
    filename
  else
    fs

let private readManifestFile (readTextFile: ReadTextFileFun) (projectDir: ProjectDir) : Future<Manifest.ManifestData> =
  let manifestFile = projectDir |> Manifest.getManifestPath
  let docId: DocId = manifestFile

  manifestFile
  |> readTextFile
  |> Future.map (Manifest.parseManifestOpt docId)

let private findProjectWith
  (projects: TreeMap<ProjectName, ProjectDir>)
  (entryProjectDir: ProjectDir)
  (projectName: ProjectName)
  =
  match projects |> TMap.tryFind projectName with
  | Some it -> it
  | None -> entryProjectDir + "/../" + projectName

/// Reads a file to get source code of specified module.
let private readModuleInProjectWith
  (readTextFile: ReadTextFileFun)
  (projectDir: ProjectDir)
  (moduleName: ModuleName)
  : Future<(SourceExt * SourceCode) option> =
  let read (ext: SourceExt) =
    readTextFile (projectDir + "/" + moduleName + ext)
    |> Future.map (fun result ->
      match result with
      | Some contents -> Some(ext, contents)
      | None -> None)

  read ".milone"
  |> Future.andThen (fun result ->
    match result with
    | (Some _) as it -> Future.just it
    | None -> read ".fs")

let parseModuleWith (docId: DocId) (kind: ModuleKind) (tokens: (Token * Pos) list) : ModuleSyntaxData =
  let errorTokens, tokens = tokens |> List.partition isErrorToken

  let ast, parseErrors = tokens |> SyntaxParse.parse

  let errors =
    List.append (tokenizeErrors errorTokens) parseErrors

  let ast =
    if errors |> List.isEmpty then
      resolveMiloneCoreDeps kind tokens ast
    else
      ast

  docId, ast, errors

let private fetchModuleWith
  (readTextFile: ReadTextFileFun)
  (projects: TreeMap<ProjectName, ProjectDir>)
  (entryProjectDir: ProjectDir)
  (tokenize: SourceCode -> (Token * Pos) list)
  (projectName: ProjectName)
  (moduleName: ModuleName)
  : Future<ModuleSyntaxData option> =
  let projectDir =
    findProjectWith projects entryProjectDir projectName

  readModuleInProjectWith readTextFile projectDir moduleName
  |> Future.map (fun result ->
    match result with
    | None -> None

    | Some (_, contents) ->
      let docId =
        AstBundle.computeDocId projectName moduleName

      let kind = getModuleKind projectName moduleName

      contents
      |> tokenize
      |> parseModuleWith docId kind
      |> Some)

// -----------------------------------------------
// Error processing
// -----------------------------------------------

type private SyntaxError = string * Loc

let private isErrorToken token =
  match token with
  | ErrorToken _, _ -> true
  | _ -> false

let private tokenizeErrors errorTokens =
  errorTokens
  |> List.map (fun token ->
    match token with
    | ErrorToken error, pos -> tokenizeErrorToString error, pos
    | _ -> unreachable ())

let private collectNameResErrors logs : SyntaxError list option =
  if List.isEmpty logs then
    None
  else
    logs
    |> List.map (fun (log, loc) -> Tir.nameResLogToString log, loc)
    |> Some

let private collectTypingErrors (tirCtx: Tir.TirCtx) : SyntaxError list option =
  let logs = tirCtx.Logs

  if List.isEmpty logs then
    None
  else
    let tyDisplayFn ty =
      let getTyName tySerial =
        tirCtx.Tys
        |> TMap.tryFind tySerial
        |> Option.map Tir.tyDefToName

      TySystem.tyDisplay getTyName ty

    logs
    |> List.map (fun (log, loc) -> Tir.logToString tyDisplayFn log, loc)
    |> Some

let syntaxErrorsToString (errors: SyntaxError list) : string =
  errors
  |> listSort (fun (_, l) (_, r) -> locCompare l r)
  |> List.map (fun (msg, loc) -> "#error " + locToString loc + " " + msg + "\n")
  |> S.concat ""

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type SyntaxHost =
  { EntryProjectDir: ProjectDir
    EntryProjectName: ProjectName
    MiloneHome: MiloneHome

    ReadTextFile: ReadTextFileFun
    WriteLog: string -> unit }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type SyntaxCtx =
  { Projects: TreeMap<ProjectName, ProjectDir>
    Manifest: Manifest.ManifestData
    Errors: (string * Loc) list
    FetchModule: FetchModuleFun
    Host: SyntaxHost }

let syntaxCtxNew (host: SyntaxHost) : SyntaxCtx =
  let entryProjectName = host.EntryProjectName
  let entryProjectDir = host.EntryProjectDir
  let miloneHome = host.MiloneHome

  let manifest =
    readManifestFile host.ReadTextFile entryProjectDir
    |> Future.wait // FIXME: avoid blocking

  let projects =
    let manifestProjects =
      manifest.Projects
      |> List.map (fun (name, dir, _) -> name, entryProjectDir + "/" + dir)

    let projects = TMap.ofList compare manifestProjects

    getStdLibProjects miloneHome
    |> List.fold (fun projects (name, dir) -> projects |> TMap.add name dir) projects
    |> TMap.add entryProjectName entryProjectDir

  let tokenize =
    SyntaxTokenize.tokenize (tokenizeHostNew ())

  { Projects = projects
    Manifest = manifest
    Errors = manifest.Errors
    FetchModule = fetchModuleWith host.ReadTextFile projects entryProjectDir tokenize
    Host = host }

// -----------------------------------------------
// Analysis
// -----------------------------------------------

[<NoEquality; NoComparison>]
type SyntaxAnalysisResult =
  | SyntaxAnalysisOk of Tir.TProgram * Tir.TirCtx
  | SyntaxAnalysisError of SyntaxError list * Tir.TirCtx option

/// Creates a TIR and collects errors
/// by loading source files and processing.
let performSyntaxAnalysis (ctx: SyntaxCtx) : SyntaxAnalysisResult =
  let writeLog = ctx.Host.WriteLog

  writeLog "AstBundle"

  let modules, nameCtx, bundleErrors =
    AstBundle.bundle ctx.FetchModule ctx.Host.EntryProjectName

  let errors = List.append ctx.Errors bundleErrors

  if errors |> List.isEmpty |> not then
    SyntaxAnalysisError(errors, None)
  else
    writeLog "NameRes"
    let modules, nameResResult = NameRes.nameRes (modules, nameCtx)

    match collectNameResErrors nameResResult.Logs with
    | Some errors -> SyntaxAnalysisError(errors, None)

    | None ->
      writeLog "Typing"
      let modules, tirCtx = Typing.infer (modules, nameResResult)

      writeLog "ArityCheck"
      let tirCtx = ArityCheck.arityCheck (modules, tirCtx)

      match collectTypingErrors tirCtx with
      | Some errors -> SyntaxAnalysisError(errors, Some tirCtx)
      | None -> SyntaxAnalysisOk(modules, tirCtx)
