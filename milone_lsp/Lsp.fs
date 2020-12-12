/// Module for LSP to talk directly to MiloneLang compiler.
module rec MiloneLsp.Lsp

open MiloneLang
open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLsp.Util

let private defaultTimeout = 5 * 1000

// Re-exports.
type Pos = Syntax.Pos
type Loc = Syntax.Loc

// -----------------------------------------------
// Host
// -----------------------------------------------

type private FilePath = string
type private ProjectName = string
type private ModuleName = string

[<NoEquality; NoComparison>]
type LangServiceDocs =
  { FindDocId: ProjectName -> ModuleName -> DocId option
    GetText: DocId -> string
    GetProjectName: DocId -> ProjectName option }

[<NoEquality; NoComparison>]
type LangServiceHost =
  { MiloneHome: FilePath
    Docs: LangServiceDocs }

// -----------------------------------------------
// Syntax
// -----------------------------------------------

// let private tokenizeHost = tokenizeHostNew ()

// let private tokenAsError token =
//   match token with
//   | ErrorToken error, pos -> Some(tokenizeErrorToString error, pos)
//   | _ -> None

// let private doTokenize text =
//   let result =
//     doWithTimeout defaultTimeout (fun () -> SyntaxTokenize.tokenize tokenizeHost text)

//   match result with
//   | Ok it -> it

//   | Error ex ->
//       eprintfn "[ERROR] doTokenize: %s" (ex.ToString())

//       let msg =
//         "FATAL: Exception during tokenization. "
//         + ex.Message

//       [ ErrorToken(OtherTokenizeError msg), (0, 0) ]

// let private doParse tokens =
//   let result =
//     doWithTimeout defaultTimeout (fun () -> SyntaxParse.parse tokens)

//   match result with
//   | Ok it -> it

//   | Error ex ->
//       eprintfn "[ERROR] doParse: %s" (ex.ToString())

//       let msg =
//         "FATAL: Exception while parsing. " + ex.Message

//       AExprRoot [], [ msg, (0, 0) ]

// -----------------------------------------------
// Semantic analysis
// -----------------------------------------------

let private tyDisplayFn (tyCtx: Typing.TyCtx) ty =
  let getTyName tySerial =
    tyCtx.Tys
    |> mapTryFind tySerial
    |> Option.map Hir.tyDefToName

  TySystem.tyDisplay getTyName ty

let private doBundle (ls: LangServiceState) projectDir =
  let cliHost =
    Program.dotnetCliHost [] ls.Host.MiloneHome

  let compileCtx =
    Cli.compileCtxNew cliHost Cli.Quiet projectDir

  let readModuleFile projectName (_projectDir: string) moduleName =
    match ls.Host.Docs.FindDocId projectName moduleName with
    | Some docId ->
        let text = ls.Host.Docs.GetText docId
        Some(docId, text)

    | None -> None

  let compileCtx =
    { compileCtx with
        // FIXME: read .milone_project
        Projects =
          compileCtx.Projects
          |> mapAdd "MiloneStd" (ls.Host.MiloneHome + "/milone_libs/MiloneStd")
        ReadModuleFile = readModuleFile }

  let expr, nameCtx, errors = Cli.syntacticallyAnalyze compileCtx
  if errors |> List.isEmpty |> not then
    None, errors
  else
    match Cli.semanticallyAnalyze cliHost Cli.Quiet (expr, nameCtx, []) with
    | Cli.SemaAnalysisOk (expr, tyCtx) -> Some(expr, tyCtx), []

    | Cli.SemaAnalysisNameResError errors ->
        let errors =
          errors
          |> List.map (fun (log, loc) -> Hir.nameResLogToString log, loc)

        None, errors

    | Cli.SemaAnalysisTypingError tyCtx ->
        let errors =
          tyCtx.Logs
          |> List.map (fun (log, loc) -> Hir.logToString (tyDisplayFn tyCtx) log, loc)

        None, errors

// -----------------------------------------------
// State
// -----------------------------------------------

[<NoEquality; NoComparison>]
type LangServiceState = private { Host: LangServiceHost }

module LangService =
  let create (host: LangServiceHost): LangServiceState = { Host = host }

  let validateProject projectDir (ls: LangServiceState) = doBundle ls projectDir |> snd
