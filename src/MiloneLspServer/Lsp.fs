/// Module for LSP to talk directly to MiloneLang compiler.
module rec MiloneLspServer.Lsp

open MiloneLspServer.Util
open MiloneShared.SharedTypes
open MiloneStd.StdPath
open MiloneSyntax
open MiloneSyntax.Syntax
open MiloneSyntax.Tir

module SharedTypes = MiloneShared.SharedTypes
module TMap = MiloneStd.StdMap
module SyntaxApi = MiloneSyntax.SyntaxApi

type Range = Pos * Pos

// -----------------------------------------------
// Host
// -----------------------------------------------

type private DocVersion = int

type private FilePath = string

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
// Utils
// -----------------------------------------------

let private pathStrTrimEndPathSep (s: string) : string =
  s
  |> Path.ofString
  |> Path.trimEndSep
  |> Path.toString

let private pathStrToStem (s: string) : string =
  s
  |> Path.ofString
  |> Path.fileStem
  |> Path.toString

let private pathStrToFileName (s: string) : string =
  s
  |> Path.ofString
  |> Path.basename
  |> Path.toString

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

let private parseWithCache (ls: LangServiceState) docId kind =
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
    let tokens =
      tokenizeWithCache ls docId
      |> List.filter (fun (token, _) -> token |> isTrivia |> not)

    // Parse.
    let _, ast, errors =
      SyntaxApi.parseModuleWith docId kind tokens

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
    |> Option.map tyDefToName

  TySystem.tyDisplay getTyName ty

let private doBundle (ls: LangServiceState) projectDir =
  let miloneHome = ls.Host.MiloneHome
  let projectDir = projectDir |> pathStrTrimEndPathSep
  let projectName = projectDir |> pathStrToStem

  let syntaxCtx: SyntaxApi.SyntaxCtx =
    let host: SyntaxApi.SyntaxHost =
      { EntryProjectDir = projectDir
        EntryProjectName = projectName
        Projects = [] // FIXME: read manifest
        MiloneHome = miloneHome
        ReadTextFile = File.readFile
        WriteLog = fun _ -> () }

    SyntaxApi.syntaxCtxNew host

  let docVersions = MutMap()

  let fetchModuleUsingCache defaultFetchModule (projectName: string) (moduleName: string) =
    match ls.Host.Docs.FindDocId projectName moduleName with
    | None -> defaultFetchModule projectName moduleName

    | Some docId ->
      docVersions
      |> MutMap.insert docId (ls.Host.Docs.GetVersion docId)
      |> ignore

      let kind =
        SyntaxApi.getModuleKind projectName moduleName

      parseWithCache ls docId kind
      |> Some
      |> Future.just

  let syntaxCtx =
    { syntaxCtx with
        FetchModule = fetchModuleUsingCache syntaxCtx.FetchModule }

  match SyntaxApi.performSyntaxAnalysis syntaxCtx with
  | SyntaxApi.SyntaxAnalysisOk (modules, tyCtx) -> Some(modules, tyCtx), [], docVersions

  | SyntaxApi.SyntaxAnalysisError (errors, tyCtxOpt) ->
    let tirOpt =
      tyCtxOpt |> Option.map (fun it -> [], it)

    tirOpt, errors, docVersions

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

type private TokenizeFullResult = (Token * Pos) list

type private ParseResult = ARoot * (string * Pos) list

type private BundleResult = (TProgram * Typing.TyCtx) option * (string * Loc) list * MutMap<DocId, DocVersion>

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
    OnPrim: TPrim * Ty * Loc -> unit }

let private dfsPat (visitor: Visitor) pat =
  match pat with
  | TLitPat _ -> ()
  | TDiscardPat (ty, loc) -> visitor.OnDiscardPat(ty, loc)
  | TVarPat (_, varSerial, ty, loc) -> visitor.OnVar(varSerial, Def, ty, loc)
  | TVariantPat (variantSerial, ty, loc) -> visitor.OnVariant(variantSerial, ty, loc)

  | TNodePat (_, pats, _, _) ->
    for pat in pats do
      dfsPat visitor pat

  | TAsPat (bodyPat, varSerial, loc) ->
    let ty = patToTy bodyPat
    visitor.OnVar(varSerial, Def, ty, loc)
    dfsPat visitor bodyPat

  | TOrPat (l, r, _) ->
    dfsPat visitor l
    dfsPat visitor r

let private dfsExpr (visitor: Visitor) expr =
  match expr with
  | TLitExpr _ -> ()
  | TVarExpr (varSerial, ty, loc) -> visitor.OnVar(varSerial, Use, ty, loc)
  | TFunExpr (funSerial, ty, loc) -> visitor.OnFun(funSerial, Some ty, loc)
  | TVariantExpr (variantSerial, ty, loc) -> visitor.OnVariant(variantSerial, ty, loc)
  | TPrimExpr (prim, ty, loc) -> visitor.OnPrim(prim, ty, loc)

  | TMatchExpr (cond, arms, _, _) ->
    dfsExpr visitor cond

    for pat, guard, expr in arms do
      dfsPat visitor pat
      dfsExpr visitor guard
      dfsExpr visitor expr

  | TRecordExpr (baseOpt, fields, _, _) ->
    baseOpt |> Option.iter (dfsExpr visitor)

    for _, field, _ in fields do
      dfsExpr visitor field

  | TNavExpr (expr, _, _, _) -> dfsExpr visitor expr

  | TNodeExpr (_, exprs, _, _) ->
    for expr in exprs do
      dfsExpr visitor expr

  | TBlockExpr (_, stmts, expr) ->
    for stmt in stmts do
      dfsStmt visitor stmt

    dfsExpr visitor expr

let private dfsStmt (visitor: Visitor) stmt =
  let onPat pat = dfsPat visitor pat
  let onExpr expr = dfsExpr visitor expr
  let onStmt stmt = dfsStmt visitor stmt

  match stmt with
  | TExprStmt expr -> onExpr expr

  | TLetValStmt (pat, init, _) ->
    onPat pat
    onExpr init

  | TLetFunStmt (_, _, _, args, body, _) ->
    for arg in args do
      onPat arg

    onExpr body

  | TModuleStmt (_, body, _) ->
    for stmt in body do
      onStmt stmt

  | TTyDeclStmt _
  | TOpenStmt _
  | TModuleSynonymStmt _ -> ()

let private findTyInStmt (ls: LangServiceState) (stmt: TStmt) (tyCtx: Typing.TyCtx) (tokenLoc: Loc) =
  let mutable contentOpt = None

  let onVisit tyOpt loc =
    // eprintfn "hover: loc=%A tyOpt=%A" loc (tyOpt |> Option.map (tyDisplayFn tyCtx))
    if loc = tokenLoc then
      contentOpt <- tyOpt

  let visitor: Visitor =
    { OnDiscardPat = fun (ty, loc) -> onVisit (Some ty) loc
      OnVar = fun (_, _, ty, loc) -> onVisit (Some ty) loc
      OnFun = fun (_, tyOpt, loc) -> onVisit tyOpt loc
      OnVariant = fun (_, ty, loc) -> onVisit (Some ty) loc
      OnPrim = fun (_, ty, loc) -> onVisit (Some ty) loc }

  dfsStmt visitor stmt
  contentOpt

[<NoComparison>]
type private Symbol =
  | DiscardSymbol
  | PrimSymbol of TPrim
  | ValueSymbol of ValueSymbol
  | TySymbol of TySymbol

let private collectSymbolsInExpr (modules: TProgram) =
  let mutable symbols = ResizeArray()

  let onVisit symbol defOrUse loc = symbols.Add((symbol, defOrUse, loc))

  let visitor: Visitor =
    { OnDiscardPat = fun (_, loc) -> onVisit DiscardSymbol Def loc
      OnVar = fun (varSerial, defOrUse, _, loc) -> onVisit (ValueSymbol(VarSymbol varSerial)) defOrUse loc
      OnFun = fun (funSerial, _, loc) -> onVisit (ValueSymbol(FunSymbol funSerial)) Use loc
      OnVariant = fun (variantSerial, _, loc) -> onVisit (ValueSymbol(VariantSymbol variantSerial)) Use loc
      OnPrim = fun (prim, _, loc) -> onVisit (PrimSymbol prim) Use loc }

  for _, _, decls in modules do
    for stmt in decls do
      dfsStmt visitor stmt

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

  | Some (modules, _tyCtx) ->
    let tokenOpt = findTokenAt ls docId targetPos

    match tokenOpt with
    | None ->
      eprintfn "%s: token not found on position: docId=%s pos=%s" hint docId (posToString targetPos)
      []

    | Some (_token, tokenPos) ->
      // eprintfn "%s: tokenPos=%A" hint tokenPos

      let tokenLoc = locOfDocPos docId tokenPos

      let symbols = collectSymbolsInExpr modules

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

    | Some (modules, tyCtx) ->
      let tokenOpt = findTokenAt ls docId targetPos

      match tokenOpt with
      | None ->
        eprintfn "hover: token not found on position: docId=%s pos=%s" docId (posToString targetPos)
        None

      | Some (_token, tokenPos) ->
        let tokenLoc = locOfDocPos docId tokenPos

        // eprintfn "hover: %A, tokenLoc=%A" token tokenLoc

        match modules
              |> List.tryPick
                   (fun (_, _, decls) ->
                     decls
                     |> List.tryPick (fun stmt -> findTyInStmt ls stmt tyCtx tokenLoc)) with
        | None -> None
        | Some ty -> Some(tyDisplayFn tyCtx ty)

  let definition projectDir (docId: DocId) (targetPos: Pos) (ls: LangServiceState) =
    let includeDecl = true
    let includeUse = false
    doCollectSymbolOccurrences "definition" projectDir docId targetPos includeDecl includeUse ls

  let references projectDir (docId: DocId) (targetPos: Pos) (includeDecl: bool) (ls: LangServiceState) =
    let includeUse = true
    doCollectSymbolOccurrences "references" projectDir docId targetPos includeDecl includeUse ls
