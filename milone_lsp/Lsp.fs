/// Module for LSP to talk directly to MiloneLang compiler.
module rec MiloneLsp.Lsp

open MiloneLang
open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.Hir
open MiloneLsp.Util

let private defaultTimeout = 5 * 1000

// Re-exports.
type Pos = Syntax.Pos
type Loc = Syntax.Loc

// -----------------------------------------------
// Host
// -----------------------------------------------

type private DocVersion = int
type private FilePath = string
type private ProjectName = string
type private ModuleName = string

[<NoEquality; NoComparison>]
type LangServiceDocs =
  { FindDocId: ProjectName -> ModuleName -> DocId option
    GetVersion: DocId -> DocVersion
    GetText: DocId -> DocVersion * string
    GetProjectName: DocId -> ProjectName option }

[<NoEquality; NoComparison>]
type LangServiceHost =
  { MiloneHome: FilePath
    Docs: LangServiceDocs }

// -----------------------------------------------
// Syntax
// -----------------------------------------------

let private tokenizeHost = tokenizeHostNew ()

let private tokenAsTriviaOrError (token, pos) =
  match token with
  | ErrorToken error -> Some(Some(tokenizeErrorToString error, pos))
  | _ when isTrivia token -> Some None
  | _ -> None

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

let private tokenizeWithCache (ls: LangServiceState) docId =
  let currentVersion = ls.Host.Docs.GetVersion docId

  let cacheOpt =
    ls.TokenizeFullCache |> MutMap.tryFind docId

  match cacheOpt with
  | Some (v, tokens) when v >= currentVersion ->
      // eprintfn "tokens cache reused: %s v%d" docId v
      tokens

  | _ ->
      // match cacheOpt with
      // | Some (v, _) -> eprintfn "tokens cache invalidated: v%d -> v%d" v currentVersion
      // | _ -> eprintfn "tokens cache not found: v%d" currentVersion

      let _, text = ls.Host.Docs.GetText docId

      let tokens =
        text |> SyntaxTokenize.tokenizeAll tokenizeHost

      ls.TokenizeFullCache
      |> MutMap.insert docId (currentVersion, tokens)
      |> ignore

      tokens

let private parseWithCache (ls: LangServiceState) docId =
  let currentVersion = ls.Host.Docs.GetVersion docId

  let cacheOpt = ls.ParseCache |> MutMap.tryFind docId
  match cacheOpt with
  | Some (v, (ast, errors)) when v >= currentVersion ->
      // eprintfn "parse cache reused: %s v%d" docId v
      docId, ast, errors

  | _ ->
      // match cacheOpt with
      // | Some (v, _) -> eprintfn "parse cache invalidated: v%d -> v%d" v currentVersion
      // | _ -> eprintfn "parse cache not found: v%d" currentVersion

      // Tokenize.
      let tokens = tokenizeWithCache ls docId

      // Remove trivias.
      let tokenizeErrors, tokens =
        tokens |> partition1 tokenAsTriviaOrError

      // Parse.
      let ast, parseErrors =
        tokens |> Array.toList |> SyntaxParse.parse

      let errors =
        List.append (tokenizeErrors |> Array.choose id |> List.ofArray) parseErrors

      ls.ParseCache
      |> MutMap.insert docId (currentVersion, (ast, errors))
      |> ignore

      docId, ast, errors

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

  let docVersions = MutMap()

  let fetchModule (projectName: string) (_projectDir: string) (moduleName: string) =
    match ls.Host.Docs.FindDocId projectName moduleName with
    | None -> None
    | Some docId ->
        docVersions
        |> MutMap.insert docId (ls.Host.Docs.GetVersion docId)
        |> ignore

        parseWithCache ls docId |> Some

  let compileCtx =
    { compileCtx with
        // FIXME: read .milone_project
        Projects =
          compileCtx.Projects
          |> mapAdd "MiloneStd" (ls.Host.MiloneHome + "/milone_libs/MiloneStd")

        FetchModule = fetchModule }

  let expr, nameCtx, errors = Cli.syntacticallyAnalyze compileCtx
  if errors |> List.isEmpty |> not then
    None, errors, docVersions
  else
    match Cli.semanticallyAnalyze cliHost Cli.Quiet (expr, nameCtx, []) with
    | Cli.SemaAnalysisOk (expr, tyCtx) -> Some(expr, tyCtx), [], docVersions

    | Cli.SemaAnalysisNameResError errors ->
        let errors =
          errors
          |> List.map (fun (log, loc) -> Hir.nameResLogToString log, loc)

        None, errors, docVersions

    | Cli.SemaAnalysisTypingError tyCtx ->
        let errors =
          tyCtx.Logs
          |> List.map (fun (log, loc) -> Hir.logToString (tyDisplayFn tyCtx) log, loc)

        None, errors, docVersions

let bundleWithCache (ls: LangServiceState) projectDir =
  let docsAreAllFresh (docs: MutMap<DocId, DocVersion>) =
    docs
    |> Seq.forall (fun (KeyValue (docId, version)) -> ls.Host.Docs.GetVersion docId <= version)

  let cacheOpt =
    ls.BundleCache |> MutMap.tryFind projectDir

  match cacheOpt with
  | Some (opt, errors, docs) when docsAreAllFresh docs ->
      // eprintfn "bundle cache reused"
      opt, errors

  | _ ->
      // match cacheOpt with
      // | Some _ -> eprintfn "bundle cache invalidated"
      // | _ -> eprintfn "bundle cache not found"

      let opt, errors, versions = doBundle ls projectDir

      ls.BundleCache
      |> MutMap.insert projectDir (opt, errors, versions)
      |> ignore

      opt, errors

// -----------------------------------------------
// State
// -----------------------------------------------

type private ProjectDir = string

type private TokenizeFullResult = (Token * Pos) list

type private ParseResult = ARoot * (string * Pos) list

type private BundleResult = (HExpr * Typing.TyCtx) option * (string * Loc) list * MutMap<DocId, DocVersion>

[<NoEquality; NoComparison>]
type LangServiceState =
  private { TokenizeFullCache: MutMap<DocId, DocVersion * TokenizeFullResult>
            ParseCache: MutMap<DocId, DocVersion * ParseResult>

            BundleCache: MutMap<ProjectDir, BundleResult>

            Host: LangServiceHost }

let private isTrivia token =
  match token with
  | BlankToken
  | NewlinesToken
  | CommentToken -> true

  | _ -> false

type Visitor =
  { OnDiscardPat: Ty * Loc -> unit
    OnVar: VarSerial * Ty * Loc -> unit
    OnFun: FunSerial * Ty option * Loc -> unit
    OnVariant: VariantSerial * Ty * Loc -> unit }

let private dfsPat (visitor: Visitor) pat =
  match pat with
  | HLitPat _ -> ()
  | HDiscardPat (ty, loc) -> visitor.OnDiscardPat(ty, loc)
  | HRefPat (varSerial, ty, loc) -> visitor.OnVar(varSerial, ty, loc)
  | HVariantPat (variantSerial, ty, loc) -> visitor.OnVariant(variantSerial, ty, loc)

  | HNodePat (_, pats, _, _) ->
      for pat in pats do
        dfsPat visitor pat

  | HAsPat (bodyPat, varSerial, loc) ->
      let ty = patToTy bodyPat
      visitor.OnVar(varSerial, ty, loc)
      dfsPat visitor bodyPat

  | HOrPat (l, r, _) ->
      dfsPat visitor l
      dfsPat visitor r

let private dfsExpr (visitor: Visitor) expr =
  match expr with
  | HLitExpr _ -> ()
  | HRefExpr (varSerial, ty, loc) -> visitor.OnVar(varSerial, ty, loc)
  | HFunExpr (funSerial, ty, loc) -> visitor.OnFun(funSerial, Some ty, loc)
  | HVariantExpr (variantSerial, ty, loc) -> visitor.OnVariant(variantSerial, ty, loc)
  | HPrimExpr _ -> ()

  | HMatchExpr (cond, arms, _, _) ->
      dfsExpr visitor cond

      for pat, guard, expr in arms do
        dfsPat visitor pat
        dfsExpr visitor guard
        dfsExpr visitor expr

  | HRecordExpr (baseOpt, fields, _, _) ->
      baseOpt |> Option.iter (dfsExpr visitor)

      for _, field, _ in fields do
        dfsExpr visitor field

  | HNavExpr (expr, _, _, _) -> dfsExpr visitor expr

  | HInfExpr (_, exprs, _, _) ->
      for expr in exprs do
        dfsExpr visitor expr

  | HBlockExpr (stmts, expr) ->
      for stmt in stmts do
        dfsExpr visitor stmt

      dfsExpr visitor expr

  | HLetValExpr (_, pat, init, next, _, _) ->
      dfsPat visitor pat
      dfsExpr visitor init
      dfsExpr visitor next

  | HLetFunExpr (funSerial, _, argPats, body, next, _, loc) ->
      visitor.OnFun(funSerial, None, loc)

      for argPat in argPats do
        dfsPat visitor argPat

      dfsExpr visitor body
      dfsExpr visitor next

  | HTyDeclExpr _
  | HOpenExpr _ -> ()

  | HModuleExpr (_, body, _) ->
      for stmt in body do
        dfsExpr visitor stmt

  | HModuleSynonymExpr _ -> ()

module LangService =
  let create (host: LangServiceHost): LangServiceState =
    { TokenizeFullCache = MutMap()
      ParseCache = MutMap()
      BundleCache = MutMap()
      Host = host }

  let validateProject projectDir (ls: LangServiceState) = bundleWithCache ls projectDir |> snd

  let hover projectDir (docId: DocId) (targetPos: Pos) (ls: LangServiceState) =
    let resultOpt, errors = bundleWithCache ls projectDir
    match resultOpt with
    | None ->
        eprintfn "hover: no bundle result: %A" errors
        None

    | Some (expr, tyCtx) ->
        let tokens = tokenizeWithCache ls docId

        // find token position
        let rec go tokens =
          match tokens with
          | []
          | [ _ ] -> None

          | (token, p1) :: (((_, p2) :: _) as tokens) ->
              if not (isTrivia token)
                 && (p1 <= targetPos)
                 && targetPos <= p2 then
                Some(token, p1)
              else if p1 > targetPos then
                None
              else
                go tokens

        match go tokens with
        | None ->
            eprintfn "hover: token not found on position: docId=%s %d" docId (List.length tokens)
            None

        | Some (token, tokenPos) ->
            let tokenLoc =
              let y, x = tokenPos
              docId, y, x

            // eprintfn "hover: %A, tokenLoc=%A" token tokenLoc

            let mutable contentOpt = None

            let onVisit tyOpt loc =
              // eprintfn "hover: loc=%A tyOpt=%A" loc (tyOpt |> Option.map (tyDisplayFn tyCtx))
              if loc = tokenLoc then contentOpt <- tyOpt

            let visitor: Visitor =
              { OnDiscardPat = fun (ty, loc) -> onVisit (Some ty) loc
                OnVar = fun (_varSerial, ty, loc) -> onVisit (Some ty) loc
                OnFun = fun (_funSerial, tyOpt, loc) -> onVisit tyOpt loc
                OnVariant = fun (_variantSerial, ty, loc) -> onVisit (Some ty) loc }

            dfsExpr visitor expr

            match contentOpt with
            | None -> None
            | Some ty ->
                let contents = tyDisplayFn tyCtx ty
                Some contents
