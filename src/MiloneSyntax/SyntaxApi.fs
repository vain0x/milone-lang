/// # SyntaxApi
///
/// Exposed API of the project.
module rec MiloneSyntax.SyntaxApi

open MiloneShared.SharedTypes
open MiloneShared.Util
open MiloneSyntax.Syntax

module ArityCheck = MiloneSyntax.ArityCheck
module AstBundle = MiloneSyntax.AstBundle
module AstToHir = MiloneSyntax.AstToHir
module C = MiloneStd.StdChar
module NameRes = MiloneSyntax.NameRes
module S = MiloneStd.StdString
module SyntaxParse = MiloneSyntax.SyntaxParse
module SyntaxTokenize = MiloneSyntax.SyntaxTokenize
module Tir = MiloneSyntax.Tir
module TMap = MiloneStd.StdMap
module TSet = MiloneStd.StdSet
module Typing = MiloneSyntax.Typing
module TySystem = MiloneSyntax.TySystem

type private ProjectName = string
type private ProjectDir = string
type private ModuleName = string
type private SourceCode = string

/// `.fs` or `.milone`.
type private SourceExt = string

// -----------------------------------------------
// MiloneCore resolution
// -----------------------------------------------

// FIXME: move to ast bundle?

/// Generates decls for each MiloneCore module
/// whose name appears in the token stream.
let private resolveMiloneCoreDeps tokens ast =
  let knownNames = [ "List"; "Option"; "String" ]

  let isKnownName moduleName =
    knownNames
    |> List.exists (fun name -> name = moduleName)

  let moduleMap =
    let rec go acc tokens =
      match tokens with
      | [] -> acc
      | (IdentToken moduleName, pos) :: (DotToken, _) :: tokens -> go ((moduleName, pos) :: acc) tokens
      | _ :: tokens -> go acc tokens

    let moduleNames = go [] tokens

    let add acc (moduleName, pos) =
      if (acc |> TMap.containsKey moduleName |> not)
         && isKnownName moduleName then
        acc |> TMap.add moduleName pos
      else
        acc

    moduleNames |> List.fold add (TMap.empty compare)

  let insertOpenDecls decls =
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

  match ast with
  | AExprRoot decls -> AExprRoot(insertOpenDecls decls)
  | AModuleRoot (name, decls, pos) -> AModuleRoot(name, insertOpenDecls decls, pos)

// -----------------------------------------------
// Utilities
// -----------------------------------------------

let getMiloneHomeFromEnv (getEnv: string -> string option) : string =
  match getEnv "MILONE_HOME" with
  | Some miloneHome ->
      assert (miloneHome <> "")
      miloneHome

  | None ->
      match getEnv "HOME" with
      | Some home -> home + "/.milone"
      | None -> failwith "$MILONE_HOME and $HOME are missing."

let private findProjectWith
  (projects: TMap.TreeMap<ProjectName, ProjectDir>)
  (entryProjectDir: ProjectDir)
  (projectName: ProjectName)
  =
  match projects |> TMap.tryFind projectName with
  | Some it -> it
  | None -> entryProjectDir + "/../" + projectName

/// Reads a file to get source code of specified module.
let private readModuleInProjectWith
  (readTextFile: string -> string option)
  (projectDir: ProjectDir)
  (moduleName: ModuleName)
  : (ModuleName * SourceExt * SourceCode) option =
  let read (ext: SourceExt) =
    match readTextFile (projectDir + "/" + moduleName + ext) with
    | Some contents -> Some(moduleName, ext, contents)
    | None -> None

  match read ".milone" with
  | (Some _) as it -> it
  | None -> read ".fs"

type private ModuleSyntaxData = DocId * ARoot * (string * Pos) list

let parseModuleWith (docId: DocId) (tokens: (Token * Pos) list) : ModuleSyntaxData =
  let errorTokens, tokens = tokens |> List.partition isErrorToken
  let ast, parseErrors = tokens |> SyntaxParse.parse

  let errors =
    List.append (tokenizeErrors errorTokens) parseErrors

  let ast =
    if errors |> List.isEmpty then
      resolveMiloneCoreDeps tokens ast
    else
      ast

  docId, ast, errors

type private FetchModuleFun = ProjectName -> ModuleName -> ModuleSyntaxData option

let private fetchModuleWith
  (readTextFile: string -> string option)
  (projects: TMap.TreeMap<ProjectName, ProjectDir>)
  (entryProjectDir: ProjectDir)
  (tokenize: SourceCode -> (Token * Pos) list)
  (projectName: ProjectName)
  (moduleName: ModuleName)
  : ModuleSyntaxData option =
  let projectDir =
    findProjectWith projects entryProjectDir projectName

  match readModuleInProjectWith readTextFile projectDir moduleName with
  | None -> None
  | Some (docId, _, contents) ->
      contents
      |> tokenize
      |> parseModuleWith docId
      |> Some

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
  |> List.map
       (fun token ->
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

let private collectTypingErrors (tyCtx: Typing.TyCtx) : SyntaxError list option =
  let logs = tyCtx.Logs

  if List.isEmpty logs then
    None
  else
    let tyDisplayFn ty =
      let getTyName tySerial =
        tyCtx.Tys
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
    MiloneHome: ProjectDir

    /// path -> contents option
    ReadTextFile: string -> string option

    WriteLog: string -> unit }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type SyntaxCtx =
  { Projects: TMap.TreeMap<ProjectName, ProjectDir>
    FetchModule: FetchModuleFun
    Host: SyntaxHost }

let syntaxCtxNew (host: SyntaxHost) : SyntaxCtx =
  let entryProjectName = host.EntryProjectName
  let entryProjectDir = host.EntryProjectDir
  let miloneHome = host.MiloneHome

  let projects =
    TMap.empty compare
    |> TMap.add "MiloneCore" (miloneHome + "/milone_libs/MiloneCore")
    |> TMap.add "MiloneStd" (miloneHome + "/milone_libs/MiloneStd")
    |> TMap.add entryProjectName entryProjectDir

  let tokenize =
    SyntaxTokenize.tokenize (tokenizeHostNew ())

  { Projects = projects
    FetchModule = fetchModuleWith host.ReadTextFile projects entryProjectDir tokenize
    Host = host }

// -----------------------------------------------
// Analysis
// -----------------------------------------------

[<NoEquality; NoComparison>]
type SyntaxAnalysisResult =
  | SyntaxAnalysisOk of Tir.HProgram * Typing.TyCtx
  | SyntaxAnalysisError of SyntaxError list * Typing.TyCtx option

/// Creates a TIR and collects errors
/// by loading source files and processing.
let performSyntaxAnalysis (ctx: SyntaxCtx) : SyntaxAnalysisResult =
  let writeLog = ctx.Host.WriteLog

  writeLog "AstBundle"

  let modules, nameCtx, bundleErrors =
    AstBundle.bundleCompatible ctx.FetchModule ctx.Host.EntryProjectName

  if bundleErrors |> List.isEmpty |> not then
    SyntaxAnalysisError(bundleErrors, None)
  else
    writeLog "NameRes"
    let modules, scopeCtx = NameRes.nameRes (modules, nameCtx)

    match collectNameResErrors scopeCtx.Logs with
    | Some errors -> SyntaxAnalysisError(errors, None)

    | None ->
        writeLog "Typing"
        let modules, tyCtx = Typing.infer (modules, scopeCtx, [])

        writeLog "ArityCheck"
        let tyCtx = ArityCheck.arityCheck (modules, tyCtx)

        match collectTypingErrors tyCtx with
        | Some errors -> SyntaxAnalysisError(errors, Some tyCtx)
        | None -> SyntaxAnalysisOk(modules, tyCtx)
