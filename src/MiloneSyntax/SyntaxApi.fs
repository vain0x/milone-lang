/// # SyntaxApi
///
/// Exposed API of the project.
module rec MiloneSyntax.SyntaxApi

open MiloneShared.SharedTypes
open MiloneShared.UtilParallel
open MiloneShared.Util
open MiloneShared.UtilSymbol
open Std.StdError
open Std.StdMap
open MiloneSyntax.Syntax
open MiloneSyntaxTypes.SyntaxTypes
open MiloneSyntaxTypes.SyntaxApiTypes

module ArityCheck = MiloneSyntax.ArityCheck
module AstBundle = MiloneSyntax.AstBundle
module OwnershipCheck = MiloneSyntax.OwnershipCheck
module NameRes = MiloneSyntax.NameRes
module Manifest = MiloneSyntax.Manifest
module S = Std.StdString
module SyntaxParse = MiloneSyntax.SyntaxParse
module SyntaxTokenize = MiloneSyntax.SyntaxTokenize
module SyntaxTreeGen = MiloneSyntax.SyntaxTreeGen
module Tir = MiloneSyntax.Tir
module Typing = MiloneSyntax.Typing
module TySystem = MiloneSyntax.TySystem
module TirTypes = MiloneSyntaxTypes.TirTypes

/// `.fs` or `.milone`.
type private SourceExt = string

/// File extension. Starts with `.`.
type private FileExt = string

type private FileExistsFun = string -> bool

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

let private getStdLibNames () = [ "MiloneCore"; "Std" ]

let private computeStdLibProjectDir (miloneHome: MiloneHome) (projectName: ProjectName) : ProjectDir =
  miloneHome + "/src/" + projectName

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

let getModuleKind projectName (_: ModuleName) =
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
               pos,
               Name(moduleName, pos),
               pos,
               [ Name("MiloneCore", pos)
                 Name(moduleName, pos) ]
             )
             :: decls)
           decls

    let decls =
      match preludeOpt with
      | Some pos ->
        AOpenDecl(
          pos,
          [ Name("MiloneCore", pos)
            Name("Prelude", pos) ]
        )
        :: decls
      | None -> decls

    let decls =
      match optionOpt with
      | Some pos ->
        AOpenDecl(
          pos,
          [ Name("MiloneCore", pos)
            Name("Option", pos) ]
        )
        :: decls
      | None -> decls

    match resultOpt with
    | Some pos ->
      AOpenDecl(
        pos,
        [ Name("MiloneCore", pos)
          Name("Result", pos) ]
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
    | Some home -> home + "/.local/share/milone"
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
type private FetchModuleCtx =
  { Projects: TreeMap<ProjectName, ProjectDir>
    Manifest: ManifestData
    TokenizeHost: TokenizeHost
    Host: FetchModuleHost }

let private readManifestFile (readTextFile: ReadTextFileFun) projectDir =
  let manifestFile = projectDir |> Manifest.getManifestPath
  let docId: DocId = Symbol.intern manifestFile

  manifestFile
  |> readTextFile
  |> Future.map (Manifest.parseManifestOpt docId)

let private prepareFetchModule (host: FetchModuleHost) : ManifestData * FetchModuleFun =
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

let private collectTypingErrors (tirCtx: TirTypes.TirCtx) : SyntaxError list option =
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
  |> listSort (fun (_, l) (_, r) -> Loc.compare l r)
  |> List.map (fun (msg, loc) -> "#error " + Loc.toString loc + " " + msg + "\n")
  |> S.concat ""

// -----------------------------------------------
// Context
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type SyntaxCtx =
  private
    { EntryProjectName: ProjectName
      Manifest: ManifestData
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

/// Creates a TIR and collects errors
/// by loading source files and processing.
let performSyntaxAnalysis (ctx: SyntaxCtx) : SyntaxLayers * SyntaxAnalysisResult =
  let writeLog = ctx.WriteLog
  let manifestErrors = ctx.Manifest.Errors

  writeLog "AstBundle"

  let layers, bundleErrors =
    AstBundle.bundle ctx.FetchModule ctx.EntryProjectName

  let syntaxLayers = layers |> List.map (List.map fst)

  let errors = List.append manifestErrors bundleErrors

  if errors |> List.isEmpty |> not then
    syntaxLayers, SyntaxAnalysisError(errors, None)
  else
    writeLog "NameRes"

    let modules, nameResResult =
      let modules: NModuleRoot list list =
        layers
        |> List.map (fun modules ->
          modules
          |> List.map (fun (syntaxData, root) ->
            let docId, _, _, _ = syntaxData
            docId, root))

      NameRes.nameRes modules

    match collectNameResErrors nameResResult.Logs with
    | Some errors -> syntaxLayers, SyntaxAnalysisError(errors, None)

    | None ->
      writeLog "Typing"
      let modules, tirCtx = Typing.infer (modules, nameResResult)

      writeLog "ArityCheck"
      let tirCtx = ArityCheck.arityCheck (modules, tirCtx)

      writeLog "OwnershipCheck"

      let modules, tirCtx =
        OwnershipCheck.ownershipCheck (modules, tirCtx)

      match collectTypingErrors tirCtx with
      | Some errors -> syntaxLayers, SyntaxAnalysisError(errors, Some tirCtx)
      | None -> syntaxLayers, SyntaxAnalysisOk(modules, tirCtx)

// -----------------------------------------------
// Dump
// -----------------------------------------------

let dumpSyntax (text: string) : string * ModuleSyntaxError list =
  let host = tokenizeHostNew ()
  let tokens = SyntaxTokenize.tokenizeAll host text

  let ast, errors =
    SyntaxTokenize.tokenize host text
    |> SyntaxParse.parse

  let tree = SyntaxTreeGen.dumpTree tokens ast
  tree, errors

// -----------------------------------------------
// Interface
// -----------------------------------------------

let newSyntaxApi () : SyntaxApi =
  let wrap (ctx: SyntaxCtx) = SyntaxCtx(box ctx)
  let unwrap (SyntaxCtx ctx) : SyntaxCtx = unbox ctx

  { GetMiloneHomeFromEnv = getMiloneHomeFromEnv
    SyntaxErrorsToString = syntaxErrorsToString
    NewSyntaxCtx = fun host -> newSyntaxCtx host |> wrap
    GetManifest = fun ctx -> ctx |> unwrap |> SyntaxCtx.getManifest
    PerformSyntaxAnalysis = fun ctx -> ctx |> unwrap |> performSyntaxAnalysis
    GenSyntaxTree = SyntaxTreeGen.genSyntaxTree
    DumpSyntax = dumpSyntax }
