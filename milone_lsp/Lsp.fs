/// Module for LSP to talk directly to MiloneLang compiler.
module rec MiloneLsp.Lsp

open MiloneLang
open MiloneLang.Util
open MiloneLang.Syntax
open MiloneLang.Hir
open MiloneLsp.Util

module TMap = MiloneStd.StdMap

// Re-exports.
type Pos = Syntax.Pos
type Loc = Syntax.Loc

type Range = Pos * Pos

// -----------------------------------------------
// Host
// -----------------------------------------------

type private DocVersion = int

type private FilePath = string
type private ProjectName = string
type private ModuleName = string

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type LangServiceDocs =
  { FindDocId: ProjectName -> ModuleName -> DocId option
    GetVersion: DocId -> DocVersion
    GetText: DocId -> DocVersion * string
    GetProjectName: DocId -> ProjectName option }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type LangServiceHost =
  { MiloneHome: FilePath
    Docs: LangServiceDocs }

// -----------------------------------------------
// Syntax
// -----------------------------------------------

let private locOfDocPos (docId: DocId) (pos: Pos) : Loc =
  let y, x = pos
  Loc(docId, y, x)

let private locToDoc (loc: Loc) : DocId =
  let (Loc (docId, _, _)) = loc
  docId

let private locToPos (loc: Loc) : Pos =
  let (Loc (_, y, x)) = loc
  y, x

let private tokenizeHost = tokenizeHostNew ()

let private tokenAsTriviaOrError (token, pos) =
  match token with
  | ErrorToken error -> Some(Some(tokenizeErrorToString error, pos))
  | _ when isTrivia token -> Some None
  | _ -> None

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

      let tokens = List.ofArray tokens

      // Parse.
      let ast, parseErrors = SyntaxParse.parse tokens

      let errors =
        List.append (tokenizeErrors |> Array.choose id |> List.ofArray) parseErrors

      let ast =
        if errors |> List.isEmpty then
          Cli.resolveMiloneCoreDeps tokens ast
        else
          ast

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
    |> TMap.tryFind tySerial
    |> Option.map Hir.tyDefToName

  TySystem.tyDisplay getTyName ty

let private doBundle (ls: LangServiceState) projectDir =
  let cliHost = Program.dotnetCliHost ()

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

  // FIXME: read .milone_project
  let compileCtx =
    { compileCtx with
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

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type LangServiceState =
  private
    { TokenizeFullCache: MutMap<DocId, DocVersion * TokenizeFullResult>
      ParseCache: MutMap<DocId, DocVersion * ParseResult>

      BundleCache: MutMap<ProjectDir, BundleResult>

      Host: LangServiceHost }

let private isTrivia token =
  match token with
  | BlankToken
  | NewlinesToken
  | CommentToken -> true

  | _ -> false

let private findTokenAt (ls: LangServiceState) (docId: DocId) (targetPos: Pos) =
  let tokens = tokenizeWithCache ls docId

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

  go tokens

let private resolveTokenRanges (ls: LangServiceState) docId (posList: Pos list) =
  let tokens = tokenizeWithCache ls docId

  let posSet = MutSet.ofSeq posList
  let ranges = ResizeArray()

  let rec go tokens =
    match tokens with
    | []
    | [ _ ] -> ()

    | (_, p1) :: (((_, p2) :: _) as tokens) ->
        if posSet |> MutSet.remove p1 then
          ranges.Add((p1, p2))

        go tokens

  go tokens
  ranges

[<NoEquality; NoComparison>]
type private DefOrUse =
  | Def
  | Use

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private Visitor =
  { OnDiscardPat: Ty * Loc -> unit
    OnVar: VarSerial * DefOrUse * Ty * Loc -> unit
    OnFun: FunSerial * Ty option * Loc -> unit
    OnVariant: VariantSerial * Ty * Loc -> unit
    OnPrim: HPrim * Ty * Loc -> unit }

let private dfsPat (visitor: Visitor) pat =
  match pat with
  | HLitPat _ -> ()
  | HDiscardPat (ty, loc) -> visitor.OnDiscardPat(ty, loc)
  | HVarPat (_, varSerial, ty, loc) -> visitor.OnVar(varSerial, Def, ty, loc)
  | HVariantPat (variantSerial, ty, loc) -> visitor.OnVariant(variantSerial, ty, loc)

  | HNodePat (_, pats, _, _) ->
      for pat in pats do
        dfsPat visitor pat

  | HAsPat (bodyPat, varSerial, loc) ->
      let ty = patToTy bodyPat
      visitor.OnVar(varSerial, Def, ty, loc)
      dfsPat visitor bodyPat

  | HOrPat (l, r, _) ->
      dfsPat visitor l
      dfsPat visitor r

let private dfsExpr (visitor: Visitor) expr =
  match expr with
  | HLitExpr _ -> ()
  | HVarExpr (varSerial, ty, loc) -> visitor.OnVar(varSerial, Use, ty, loc)
  | HFunExpr (funSerial, ty, loc) -> visitor.OnFun(funSerial, Some ty, loc)
  | HVariantExpr (variantSerial, ty, loc) -> visitor.OnVariant(variantSerial, ty, loc)
  | HPrimExpr (prim, ty, loc) -> visitor.OnPrim(prim, ty, loc)

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

  | HNodeExpr (_, exprs, _, _) ->
      for expr in exprs do
        dfsExpr visitor expr

  | HBlockExpr (stmts, expr) ->
      for stmt in stmts do
        dfsExpr visitor stmt

      dfsExpr visitor expr

  | HLetValExpr (pat, init, next, _, _) ->
      dfsPat visitor pat
      dfsExpr visitor init
      dfsExpr visitor next

  | HLetFunExpr (funSerial, _, _, argPats, body, next, _, loc) ->
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

let private findTyInExpr (ls: LangServiceState) (expr: HExpr) (tyCtx: Typing.TyCtx) (tokenLoc: Loc) =
  let mutable contentOpt = None

  let onVisit tyOpt loc =
    // eprintfn "hover: loc=%A tyOpt=%A" loc (tyOpt |> Option.map (tyDisplayFn tyCtx))
    if loc = tokenLoc then
      contentOpt <- tyOpt

  let visitor : Visitor =
    { OnDiscardPat = fun (ty, loc) -> onVisit (Some ty) loc
      OnVar = fun (_, _, ty, loc) -> onVisit (Some ty) loc
      OnFun = fun (_, tyOpt, loc) -> onVisit tyOpt loc
      OnVariant = fun (_, ty, loc) -> onVisit (Some ty) loc
      OnPrim = fun (_, ty, loc) -> onVisit (Some ty) loc }

  dfsExpr visitor expr
  contentOpt

[<NoComparison>]
type private Symbol =
  | DiscardSymbol
  | PrimSymbol of HPrim
  | ValueSymbol of ValueSymbol
  | TySymbol of TySymbol

let private collectSymbolsInExpr (expr: HExpr) =
  let mutable symbols = ResizeArray()

  let onVisit symbol defOrUse loc = symbols.Add((symbol, defOrUse, loc))

  let visitor : Visitor =
    { OnDiscardPat = fun (_, loc) -> onVisit DiscardSymbol Def loc
      OnVar = fun (varSerial, defOrUse, _, loc) -> onVisit (ValueSymbol(VarSymbol varSerial)) defOrUse loc
      OnFun = fun (funSerial, _, loc) -> onVisit (ValueSymbol(FunSymbol funSerial)) Use loc
      OnVariant = fun (variantSerial, _, loc) -> onVisit (ValueSymbol(VariantSymbol variantSerial)) Use loc
      OnPrim = fun (prim, _, loc) -> onVisit (PrimSymbol prim) Use loc }

  dfsExpr visitor expr
  symbols

let private symbolToName (tyCtx: Typing.TyCtx) symbol =
  match symbol with
  | DiscardSymbol -> Some "_"

  | PrimSymbol prim -> (sprintf "%A" prim).ToLowerInvariant() |> Some

  | ValueSymbol valueSymbol ->
      match valueSymbol with
      | VarSymbol varSerial ->
          tyCtx.Vars
          |> TMap.tryFind varSerial
          |> Option.map (fun (def: VarDef) -> def.Name)
      | FunSymbol funSerial ->
          tyCtx.Funs
          |> TMap.tryFind funSerial
          |> Option.map (fun (def: FunDef) -> def.Name)
      | VariantSymbol variantSerial ->
          tyCtx.Variants
          |> TMap.tryFind variantSerial
          |> Option.map (fun (def: VariantDef) -> def.Name)

  | TySymbol tySymbol ->
      match tySymbol with
      | MetaTySymbol tySerial -> sprintf "?%d" tySerial |> Some

      | UnivTySymbol tySerial
      | SynonymTySymbol tySerial
      | UnionTySymbol tySerial
      | RecordTySymbol tySerial ->
          tyCtx.Tys
          |> TMap.tryFind tySerial
          |> Option.map tyDefToName

let private doCollectSymbolOccurrences
  hint
  projectDir
  (docId: DocId)
  (targetPos: Pos)
  (includeDecl: bool)
  (includeUse: bool)
  (ls: LangServiceState)
  =
  let resultOpt, errors = bundleWithCache ls projectDir

  match resultOpt with
  | None ->
      eprintfn "%s: no bundle result: errors %d" hint (List.length errors)
      []

  | Some (expr, _tyCtx) ->
      let tokenOpt = findTokenAt ls docId targetPos

      match tokenOpt with
      | None ->
          eprintfn "%s: token not found on position: docId=%s pos=%s" hint docId (posToString targetPos)
          []

      | Some (_token, tokenPos) ->
          // eprintfn "%s: tokenPos=%A" hint tokenPos

          let tokenLoc = locOfDocPos docId tokenPos

          let symbols = collectSymbolsInExpr expr

          let symbolIndex =
            symbols.FindIndex(fun (_, _, loc) -> loc = tokenLoc)

          if symbolIndex < 0 then
            eprintfn "%s: no symbol" hint
            []
          else
            let targetSymbol, _, _ = symbols.[symbolIndex]

            let map = MutMultimap.empty ()

            for symbol, defOrUse, loc in symbols do
              match defOrUse with
              | Def when not includeDecl -> ()
              | Use when not includeUse -> ()
              | _ ->
                  if symbol = targetSymbol then
                    map
                    |> MutMultimap.insert (locToDoc loc) (locToPos loc)

            [ for KeyValue (docId, posList) in map do
                for range in resolveTokenRanges ls docId (List.ofSeq posList) do
                  docId, range ]

module LangService =
  let create (host: LangServiceHost) : LangServiceState =
    { TokenizeFullCache = MutMap()
      ParseCache = MutMap()
      BundleCache = MutMap()
      Host = host }

  let validateProject projectDir (ls: LangServiceState) = bundleWithCache ls projectDir |> snd

  let documentHighlight projectDir (docId: DocId) (targetPos: Pos) (ls: LangServiceState) =
    let resultOpt, errors = bundleWithCache ls projectDir

    match resultOpt with
    | None ->
        eprintfn "highlight: no bundle result: errors %d" (List.length errors)
        None

    | Some (expr, _tyCtx) ->
        let tokenOpt = findTokenAt ls docId targetPos

        match tokenOpt with
        | None ->
            eprintfn "highlight: token not found on position: docId=%s pos=%s" docId (posToString targetPos)
            None

        | Some (_token, tokenPos) ->
            // eprintfn "highlight: tokenPos=%A" tokenPos

            let symbols = collectSymbolsInExpr expr

            // Remove symbols occurred in other documents.
            symbols.RemoveAll(fun (_, _, loc) -> locToDoc loc <> docId)
            |> ignore

            let symbolIndex =
              symbols.FindIndex(fun (_, _, loc) -> locToPos loc = tokenPos)

            if symbolIndex < 0 then
              eprintfn "highlight: no symbol"
              None
            else
              let targetSymbol, _, _ = symbols.[symbolIndex]

              let reads = ResizeArray()
              let writes = ResizeArray()

              for symbol, defOrUse, loc in symbols do
                if symbol = targetSymbol then
                  let pos = locToPos loc

                  match defOrUse with
                  | Def -> writes.Add(pos)
                  | Use -> reads.Add(pos)

              let reads =
                resolveTokenRanges ls docId (List.ofSeq reads)

              let writes =
                resolveTokenRanges ls docId (List.ofSeq writes)

              Some((reads, writes))

  let hover projectDir (docId: DocId) (targetPos: Pos) (ls: LangServiceState) =
    let resultOpt, errors = bundleWithCache ls projectDir

    match resultOpt with
    | None ->
        eprintfn "hover: no bundle result: errors %d" (List.length errors)
        None

    | Some (expr, tyCtx) ->
        let tokenOpt = findTokenAt ls docId targetPos

        match tokenOpt with
        | None ->
            eprintfn "hover: token not found on position: docId=%s pos=%s" docId (posToString targetPos)
            None

        | Some (_token, tokenPos) ->
            let tokenLoc = locOfDocPos docId tokenPos

            // eprintfn "hover: %A, tokenLoc=%A" token tokenLoc

            match findTyInExpr ls expr tyCtx tokenLoc with
            | None -> None
            | Some ty -> Some(tyDisplayFn tyCtx ty)

  let definition projectDir (docId: DocId) (targetPos: Pos) (ls: LangServiceState) =
    let includeDecl = true
    let includeUse = false
    doCollectSymbolOccurrences "definition" projectDir docId targetPos includeDecl includeUse ls

  let references projectDir (docId: DocId) (targetPos: Pos) (includeDecl: bool) (ls: LangServiceState) =
    let includeUse = true
    doCollectSymbolOccurrences "references" projectDir docId targetPos includeDecl includeUse ls
