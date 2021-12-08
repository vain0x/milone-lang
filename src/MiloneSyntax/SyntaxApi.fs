/// # SyntaxApi
///
/// Exposed API of the project.
module rec MiloneSyntax.SyntaxApi

open MiloneShared.SharedTypes
open MiloneShared.UtilParallel
open MiloneShared.Util
open MiloneSyntax.Syntax
open MiloneStd.StdMap

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

/// File extension. Starts with `.`.
type private FileExt = string

/// `MILONE_HOME`
type private MiloneHome = string

type private FileExistsFun = string -> bool
type private WriteLogFun = string -> unit

let private changeExt (ext: FileExt) (path: string) : string =
  assert (ext |> S.startsWith "." && ext <> ".")

  let dirname, basename =
    match path |> S.cutLast "/" with
    | dirname, basename, true -> dirname + "/", basename
    | s, _, _ -> "", s

  let stem =
    let s = basename

    match s |> S.findIndex "." with
    | Some i when 0 < i && i < s.Length -> S.truncate i s
    | _ -> s

  dirname + stem + ext

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
let private optionIdents = [ "option"; "None"; "Some" ]
let private resultIdents = [ "Result"; "Ok"; "Error" ]

let private knownModules =
  [ "List"
    "Option"
    "Prelude"
    "Result"
    "String" ]

let private isPreludeFun funName =
  preludeFuns
  |> List.exists (fun name -> name = funName)

let private isOptionIdent ident =
  optionIdents |> List.exists (fun x -> x = ident)

let private isResultIdent ident =
  resultIdents |> List.exists (fun x -> x = ident)

let private isKnownModule moduleName =
  knownModules
  |> List.exists (fun name -> name = moduleName)

/// Generates decls for each MiloneCore module
/// whose name appears in the token stream.
let private resolveMiloneCoreDeps kind tokens ast =
  let analyze tokens =
    let rec go preludeOpt optionOpt resultOpt acc tokens =
      match tokens with
      | [] -> preludeOpt, optionOpt, resultOpt, acc

      | (IdentToken name, pos) :: tokens when Option.isNone preludeOpt && isPreludeFun name ->
        go (Some pos) optionOpt resultOpt acc tokens

      | (IdentToken name, pos) :: tokens when Option.isNone optionOpt && isOptionIdent name ->
        go preludeOpt (Some pos) resultOpt acc tokens

      | (IdentToken name, pos) :: tokens when Option.isNone resultOpt && isResultIdent name ->
        go preludeOpt optionOpt (Some pos) acc tokens

      | (IdentToken moduleName, pos) :: (DotToken, _) :: tokens ->
        go preludeOpt optionOpt resultOpt ((moduleName, pos) :: acc) tokens

      | _ :: tokens -> go preludeOpt optionOpt resultOpt acc tokens

    let preludeOpt, optionOpt, resultOpt, moduleNames = go None None None [] tokens

    let add acc (moduleName, pos) =
      if (acc |> TMap.containsKey moduleName |> not)
         && isKnownModule moduleName then
        acc |> TMap.add moduleName pos
      else
        acc

    let moduleMap =
      moduleNames |> List.fold add (TMap.empty compare)

    preludeOpt, optionOpt, resultOpt, moduleMap

  let insertOpenDecls decls =
    let preludeOpt, optionOpt, resultOpt, moduleMap = analyze tokens

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

    let decls =
      match preludeOpt with
      | Some pos ->
        AOpenDecl(
          [ Name("MiloneCore", pos)
            Name("Prelude", pos) ],
          pos
        )
        :: decls
      | None -> decls

    let decls =
      match optionOpt with
      | Some pos ->
        AOpenDecl(
          [ Name("MiloneCore", pos)
            Name("Option", pos) ],
          pos
        )
        :: decls
      | None -> decls

    match resultOpt with
    | Some pos ->
      AOpenDecl(
        [ Name("MiloneCore", pos)
          Name("Result", pos) ],
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

let readSourceFile (readTextFile: ReadTextFileFun) filename : Future<string option> =
  readTextFile filename
  |> Future.andThen (fun result ->
    match result with
    | (Some _) as it -> Future.just it
    | None -> readTextFile (changeExt ".fs" filename))

let parseModule (docId: DocId) (kind: ModuleKind) (tokens: TokenizeResult) : ModuleSyntaxData =
  let errorTokens, tokens = tokens |> List.partition isErrorToken

  let ast, parseErrors = tokens |> SyntaxParse.parse

  let errors =
    List.append (tokenizeErrors errorTokens) parseErrors

  let ast =
    if errors |> List.isEmpty then
      resolveMiloneCoreDeps kind tokens ast
    else
      ast

  docId, tokens, ast, errors

// -----------------------------------------------
// FetchModule
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type FetchModuleHost =
  { EntryProjectDir: ProjectDir
    EntryProjectName: ProjectName
    MiloneHome: MiloneHome

    ReadTextFile: ReadTextFileFun
    WriteLog: WriteLogFun }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private FetchModuleCtx =
  { Projects: TreeMap<ProjectName, ProjectDir>
    Manifest: Manifest.ManifestData
    TokenizeHost: TokenizeHost
    Host: FetchModuleHost }

let private readManifestFile (readTextFile: ReadTextFileFun) projectDir =
  let manifestFile = projectDir |> Manifest.getManifestPath
  let docId: DocId = manifestFile

  manifestFile
  |> readTextFile
  |> Future.map (Manifest.parseManifestOpt docId)

let private prepareFetchModule (host: FetchModuleHost) : Manifest.ManifestData * FetchModuleFun =
  let entryProjectName = host.EntryProjectName
  let entryProjectDir = host.EntryProjectDir
  let miloneHome = host.MiloneHome
  let readTextFile = host.ReadTextFile
  let tokenizeHost = tokenizeHostNew ()

  let manifest =
    readManifestFile readTextFile entryProjectDir
    |> Future.wait // #avoidBlocking

  let projects =
    let manifestProjects =
      manifest.Projects
      |> List.map (fun (name, dir, _) -> name, entryProjectDir + "/" + dir)

    let projects = TMap.ofList compare manifestProjects

    getStdLibProjects miloneHome
    |> List.fold (fun projects (name, dir) -> projects |> TMap.add name dir) projects
    |> TMap.add entryProjectName entryProjectDir

  let fetchModule: FetchModuleFun =
    fun projectName moduleName ->
      let filename =
        let projectDir =
          match projects |> TMap.tryFind projectName with
          | Some it -> it
          | None -> entryProjectDir + "/../" + projectName

        projectDir + "/" + moduleName + ".milone"

      readSourceFile readTextFile filename
      |> Future.map (fun result ->
        match result with
        | None -> None

        | Some text ->
          let docId =
            AstBundle.computeDocId projectName moduleName

          let kind = getModuleKind projectName moduleName

          text
          |> SyntaxTokenize.tokenize tokenizeHost
          |> parseModule docId kind
          |> Some)

  manifest, fetchModule

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
type SyntaxCtx =
  private
    { EntryProjectName: ProjectName
      Manifest: Manifest.ManifestData
      FetchModule: FetchModuleFun
      WriteLog: WriteLogFun }

/// Using file system.
let newSyntaxCtx (host: FetchModuleHost) : SyntaxCtx =
  let manifest, fetchModule = prepareFetchModule host

  { EntryProjectName = host.EntryProjectName
    Manifest = manifest
    FetchModule = fetchModule
    WriteLog = host.WriteLog }

module SyntaxCtx =
  let getManifest (ctx: SyntaxCtx) = ctx.Manifest

  let withFetchModule fetchModule (ctx: SyntaxCtx) =
    { ctx with FetchModule = fetchModule ctx.FetchModule }

// -----------------------------------------------
// Analysis
// -----------------------------------------------

type SyntaxLayers = ModuleSyntaxData list list

[<NoEquality; NoComparison>]
type SyntaxAnalysisResult =
  | SyntaxAnalysisOk of Tir.TProgram * Tir.TirCtx
  | SyntaxAnalysisError of SyntaxError list * Tir.TirCtx option

/// Creates a TIR and collects errors
/// by loading source files and processing.
let performSyntaxAnalysis (ctx: SyntaxCtx) : SyntaxLayers * SyntaxAnalysisResult =
  let writeLog = ctx.WriteLog
  let manifestErrors = ctx.Manifest.Errors

  writeLog "AstBundle"

  let layers, nameCtx, bundleErrors =
    AstBundle.bundle ctx.FetchModule ctx.EntryProjectName

  let syntaxLayers = layers |> List.map (List.map fst)

  let errors = List.append manifestErrors bundleErrors

  if errors |> List.isEmpty |> not then
    syntaxLayers, SyntaxAnalysisError(errors, None)
  else
    writeLog "NameRes"

    let modules, nameResResult =
      let modules =
        layers
        |> List.map (fun modules -> modules |> List.map (fun (_, m) -> m))

      NameRes.nameRes (modules, nameCtx)

    match collectNameResErrors nameResResult.Logs with
    | Some errors -> syntaxLayers, SyntaxAnalysisError(errors, None)

    | None ->
      writeLog "Typing"
      let modules, tirCtx = Typing.infer (modules, nameResResult)

      writeLog "ArityCheck"
      let tirCtx = ArityCheck.arityCheck (modules, tirCtx)

      match collectTypingErrors tirCtx with
      | Some errors -> syntaxLayers, SyntaxAnalysisError(errors, Some tirCtx)
      | None -> syntaxLayers, SyntaxAnalysisOk(modules, tirCtx)
