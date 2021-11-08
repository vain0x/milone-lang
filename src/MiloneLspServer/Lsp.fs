/// Module for LSP to talk directly to MiloneLang compiler.
module rec MiloneLspServer.Lsp

open MiloneLspServer.Util
open MiloneShared.SharedTypes
open MiloneStd.StdMap
open MiloneStd.StdPath
open MiloneSyntax
open MiloneSyntax.Syntax
open MiloneSyntax.Tir

module C = MiloneStd.StdChar
module SharedTypes = MiloneShared.SharedTypes
module SyntaxApi = MiloneSyntax.SyntaxApi
module Tir = MiloneSyntax.Tir

type Range = Pos * Pos

// -----------------------------------------------
// Host
// -----------------------------------------------

type private DocVersion = int

type private FilePath = string

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type LangServiceHost =
  { GetDocVersion: DocId -> DocVersion option
    Tokenize: DocId -> DocVersion * TokenizeFullResult
    Parse: DocId -> (DocVersion * ModuleSyntaxData) option

    MiloneHome: FilePath
    MiloneHomeModules: unit -> (ProjectName * ModuleName) list
    FindModulesInDir: ProjectDir -> (ProjectName * ModuleName) list }

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

let private getVersion docId (ls: LangServiceState) =
  ls.Host.GetDocVersion docId
  |> Option.defaultValue 0

// FIXME: avoid doing tokenization repeatedly
let private tokenizeWithCache docId (ls: LangServiceState) = ls.Host.Tokenize docId |> snd

let private parseWithCache docId (ls: LangServiceState) = ls.Host.Parse docId |> Option.map snd

// -----------------------------------------------
// Semantic analysis
// -----------------------------------------------

let private tyDisplayFn (tirCtx: TirCtx) ty =
  let getTyName tySerial =
    tirCtx.Tys
    |> TMap.tryFind tySerial
    |> Option.map tyDefToName

  TySystem.tyDisplay getTyName ty

let private doBundle (ls: LangServiceState) projectDir : BundleResult =
  let miloneHome = ls.Host.MiloneHome
  let projectDir = projectDir |> pathStrTrimEndPathSep
  let projectName = projectDir |> pathStrToStem

  let fetchModuleUsingCache _ (projectName: string) (moduleName: string) =
    let docId =
      AstBundle.computeDocId projectName moduleName

    ls |> parseWithCache docId |> Future.just

  let syntaxCtx =
    let host: SyntaxApi.FetchModuleHost =
      { EntryProjectDir = projectDir
        EntryProjectName = projectName
        MiloneHome = miloneHome
        ReadTextFile = File.readFile
        WriteLog = fun _ -> () }

    SyntaxApi.newSyntaxCtx host
    |> SyntaxApi.SyntaxCtx.withFetchModule fetchModuleUsingCache

  let layers, result =
    SyntaxApi.performSyntaxAnalysis syntaxCtx

  let docVersions =
    layers
    |> List.collect (fun modules ->
      modules
      |> List.map (fun (docId, _, _, _) -> docId, getVersion docId ls))

  let parseResults =
    layers
    |> List.collect (fun modules ->
      modules
      |> List.map (fun ((docId, _, _, _) as syntaxData) ->
        let v = getVersion docId ls
        v, syntaxData))

  match result with
  | SyntaxApi.SyntaxAnalysisOk (modules, tirCtx) ->
    { ProgramOpt = Some(modules, tirCtx)
      Errors = []
      DocVersions = docVersions
      ParseResults = parseResults }

  | SyntaxApi.SyntaxAnalysisError (errors, tirCtxOpt) ->
    { ProgramOpt =
        match tirCtxOpt with
        | Some tirCtx -> Some([], tirCtx)
        | None -> None

      Errors = errors
      DocVersions = docVersions
      ParseResults = parseResults }

let private bundleWithCache (ls: LangServiceState) projectDir : BundleResult * LangServiceState =
  let docsAreAllFresh docVersions =
    docVersions
    |> List.forall (fun (docId, version) -> getVersion docId ls <= version)

  let cacheOpt =
    ls.BundleCache |> TMap.tryFind projectDir

  match cacheOpt with
  | Some result when docsAreAllFresh result.DocVersions ->
    // traceFn "bundle cache reused"
    result, ls

  | _ ->
    // match cacheOpt with
    // | Some _ -> eprintfn "bundle cache invalidated"
    // | _ -> eprintfn "bundle cache not found"

    let result = doBundle ls projectDir

    let ls =
      { ls with
          NewParseResults = List.append result.ParseResults ls.NewParseResults
          BundleCache = ls.BundleCache |> TMap.add projectDir result }

    result, ls

// -----------------------------------------------
// State
// -----------------------------------------------

type private Error = string * Loc
type private ParseResult = ARoot * (string * Pos) list

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type BundleResult =
  { ProgramOpt: (TProgram * TirCtx) option
    Errors: Error list
    DocVersions: (DocId * DocVersion) list
    ParseResults: (DocVersion * ModuleSyntaxData) list }

// FIXME: private repr
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type LangServiceState =
  { NewParseResults: (DocVersion * ModuleSyntaxData) list
    BundleCache: TreeMap<ProjectDir, BundleResult>
    Host: LangServiceHost }

let private isTrivia token =
  match token with
  | BlankToken
  | NewlinesToken
  | CommentToken -> true

  | _ -> false

let private findTokenAt (ls: LangServiceState) (docId: DocId) (targetPos: Pos) =
  let tokens = tokenizeWithCache docId ls

  let rec go tokens =
    match tokens with
    | []
    | [ _ ] -> None

    | (token, p1) :: (((_, p2) :: _) as tokens) ->
      if not (isTrivia token)
         && token <> DotToken
         && p1 <= targetPos
         && targetPos <= p2 then
        Some(token, p1)
      else if p1 > targetPos then
        None
      else
        go tokens

  go tokens

let private resolveTokenRanges (ls: LangServiceState) docId (posList: Pos list) =
  let tokens = tokenizeWithCache docId ls

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

let parseFullTokens projectName moduleName docId (allTokens: TokenizeFullResult) : ModuleSyntaxData =
  let tokens =
    allTokens
    |> List.filter (fun (token, _) -> token |> isTrivia |> not)

  let kind =
    SyntaxApi.getModuleKind projectName moduleName

  let docId, _, ast, errors = SyntaxApi.parseModule docId kind tokens

  docId, allTokens, ast, errors

[<NoEquality; NoComparison>]
type private DefOrUse =
  | Def
  | Use

/// Path of module names.
///
/// - File module: `[projectName; moduleName]`
/// - Inner module: `[projectName; moduleName; name1; name2; ...]`
/// - Module synonym: `[docId; name]`
type private ModulePath = string list

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private Visitor =
  { OnDiscardPat: Ty * Loc -> unit
    OnVar: VarSerial * DefOrUse * Ty * Loc -> unit
    OnFun: FunSerial * DefOrUse * Ty option * Loc -> unit
    OnVariant: VariantSerial * DefOrUse * Ty * Loc -> unit
    OnPrim: TPrim * Ty * Loc -> unit
    OnField: TySerial * Ident * DefOrUse * Ty * Loc -> unit
    OnTy: TySymbol * DefOrUse * Loc -> unit
    OnModule: ModulePath * DefOrUse * Loc -> unit

    // Context
    GetTokens: DocId -> TokenizeFullResult }

let private lastIdentBefore getTokens loc =
  let (Loc (docId, py, px)) = loc

  getTokens docId
  |> List.skipWhile (fun (_, (y, x)) -> (y, x) < (py, 0))
  |> List.takeWhile (fun (_, (y, x)) -> (y, x) <= (py, px))
  |> List.rev
  |> List.tryPick (fun (token, (y, x)) ->
    match token with
    | IdentToken _ -> Some(Loc(docId, y, x))
    | _ -> None)

let private firstIdentAfter getTokens loc =
  let (Loc (docId, py, px)) = loc

  getTokens docId
  |> List.tryPick (fun (token, (y, x)) ->
    match token with
    | IdentToken _ when (py, px) < (y, x) -> Some(Loc(docId, y, x))
    | _ -> None)

let private nameToIdent (Name (ident, _)) = ident
let private nameToPos (Name (_, pos)) = pos

let private pathToPos altPos path =
  match path |> List.tryLast with
  | Some name -> name |> nameToPos
  | None -> altPos

let private dfsAExpr (visitor: Visitor) docId expr : unit =
  let onExpr expr = dfsAExpr visitor docId expr
  let onExprOpt exprOpt = exprOpt |> Option.iter onExpr
  let onExprs exprs = exprs |> List.iter onExpr

  let toLoc (y, x) = Loc(docId, y, x)

  match expr with
  | AMissingExpr _
  | ALitExpr _
  | AIdentExpr _ -> ()
  | AListExpr (items, _) -> onExprs items

  | ARecordExpr (baseOpt, fields, _) ->
    onExprOpt baseOpt

    for _, init, _ in fields do
      onExpr init

  | AIfExpr (cond, body, alt, _) ->
    onExpr cond
    onExpr body
    onExprOpt alt

  | AMatchExpr (cond, arms, _) ->
    onExpr cond

    for AArm (_, guard, body, _) in arms do
      onExprOpt guard
      onExpr body

  | AFunExpr (_, body, _) -> onExpr body

  | ANavExpr (l, _, _) ->
    match l with
    | AIdentExpr (Name (l, pos)) when l.Length = 1 && C.isUpper l.[0] -> visitor.OnModule([ docId; l ], Use, toLoc pos)

    | ANavExpr (AIdentExpr p, m, _) ->
      let path = [ p; m ] |> List.map nameToIdent

      if path
         |> List.forall (fun name -> name.Length >= 1 && C.isUpper name.[0]) then
        visitor.OnModule(path, Use, toLoc (nameToPos m))

    | ANavExpr _ -> ()
    | _ -> onExpr l

  | AIndexExpr (l, r, _) -> onExprs [ l; r ]
  | AUnaryExpr (_, arg, _) -> onExpr arg
  | ABinaryExpr (_, l, r, _) -> onExprs [ l; r ]
  | ARangeExpr (l, r, _) -> onExprs [ l; r ]
  | ATupleExpr (items, _) -> onExprs items
  | AAscribeExpr (l, _, _) -> onExpr l

  | ASemiExpr (stmts, last, _) ->
    onExprs stmts
    onExpr last

  | ALetExpr (_, _, init, next, _) -> onExprs [ init; next ]

let private dfsADecl (visitor: Visitor) docId decl =
  let onExpr expr = dfsAExpr visitor docId expr
  let toLoc (y, x) = Loc(docId, y, x)

  match decl with
  | AExprDecl expr -> onExpr expr
  | ALetDecl (_, _, init, _) -> onExpr init

  | ATySynonymDecl _
  | AUnionTyDecl _
  | ARecordTyDecl _ -> ()

  | AOpenDecl (path, pos) ->
    let pos = path |> pathToPos pos
    visitor.OnModule(path |> List.map nameToIdent, Use, toLoc pos)

  | AModuleSynonymDecl (Name (synonym, identPos), path, pos) ->
    visitor.OnModule([ docId; synonym ], Def, toLoc identPos)

    let pos = path |> pathToPos pos
    visitor.OnModule(path |> List.map nameToIdent, Use, toLoc pos)

  | AModuleDecl (_, _, _, decls, _) ->
    for decl in decls do
      dfsADecl visitor docId decl

  | AAttrDecl (_, next, _) -> dfsADecl visitor docId next

let private dfsARoot (visitor: Visitor) (docId: DocId) root =
  let toLoc (y, x) = Loc(docId, y, x)
  let (ARoot (headOpt, decls)) = root

  match headOpt with
  | Some (path, pos) ->
    let pos = path |> pathToPos pos
    visitor.OnModule(path |> List.map nameToIdent, Def, toLoc pos)

  | _ ->
    let path = docId.Split(".") |> Array.toList
    visitor.OnModule(path, Def, Loc(docId, 0, 0))

  for decl in decls do
    dfsADecl visitor docId decl

let private dfsTy (visitor: Visitor) ty : unit =
  let (Ty (tk, tyArgs)) = ty

  match tk with
  | UnionTk (tySerial, Some loc) -> visitor.OnTy(UnionTySymbol tySerial, Use, loc)
  | RecordTk (tySerial, Some loc) -> visitor.OnTy(RecordTySymbol tySerial, Use, loc)
  | _ -> ()

  for ty in tyArgs do
    dfsTy visitor ty

let private dfsPat (visitor: Visitor) pat =
  match pat with
  | TLitPat _ -> ()
  | TDiscardPat (ty, loc) -> visitor.OnDiscardPat(ty, loc)

  | TVarPat (_, varSerial, ty, loc) -> visitor.OnVar(varSerial, Def, ty, loc)
  | TVariantPat (variantSerial, ty, loc) -> visitor.OnVariant(variantSerial, Use, ty, loc)

  | TNodePat (kind, pats, ty, loc) ->
    match kind with
    | TVariantAppPN variantSerial -> visitor.OnVariant(variantSerial, Use, ty, loc)
    | TNavPN _ -> ()
    | TAscribePN -> dfsTy visitor ty
    | _ -> ()

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
  | TFunExpr (funSerial, ty, loc) -> visitor.OnFun(funSerial, Use, Some ty, loc)
  | TVariantExpr (variantSerial, ty, loc) -> visitor.OnVariant(variantSerial, Use, ty, loc)
  | TPrimExpr (prim, ty, loc) -> visitor.OnPrim(prim, ty, loc)

  | TMatchExpr (cond, arms, _, _) ->
    dfsExpr visitor cond

    for pat, guard, expr in arms do
      dfsPat visitor pat
      dfsExpr visitor guard
      dfsExpr visitor expr

  | TRecordExpr (baseOpt, fields, ty, _) ->
    baseOpt |> Option.iter (dfsExpr visitor)

    for ident, init, loc in fields do
      match ty with
      | Ty (RecordTk (tySerial, _), _) ->
        // before '='
        match lastIdentBefore visitor.GetTokens loc with
        | Some loc -> visitor.OnField(tySerial, ident, Use, ty, loc)
        | _ -> ()
      | _ -> ()

      dfsExpr visitor init

  | TNavExpr (l, (r, loc), ty, _) ->
    dfsExpr visitor l

    match exprToTy l with
    | Ty (RecordTk (tySerial, _), _) -> visitor.OnField(tySerial, r, Use, ty, loc)
    | _ -> ()

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

  | TLetFunStmt (callee, _, _, args, body, loc) ->
    let tyFunN argTys resultTy : Ty =
      argTys
      |> List.fold (fun funTy argTy -> tyFun argTy funTy) resultTy

    // after 'let'
    match firstIdentAfter visitor.GetTokens loc with
    | Some loc ->
      let funTy =
        let argTys = args |> List.map patToTy
        let resultTy = body |> exprToTy
        tyFunN argTys resultTy

      visitor.OnFun(callee, Def, Some funTy, loc)

    | None -> ()

    // HACK: Visit type as if let-fun has result-type ascription. Typing removes result type ascription.
    dfsTy visitor (exprToTy body)

    for arg in args do
      onPat arg

    onExpr body

  | TTyDeclStmt (tySerial, _, tyArgs, tyDecl, tyDeclLoc) ->
    match tyDecl with
    | TySynonymDecl _ -> ()

    | UnionTyDecl (_, variants, _) ->
      // after 'type'
      match firstIdentAfter visitor.GetTokens tyDeclLoc with
      | Some loc -> visitor.OnTy(UnionTySymbol tySerial, Def, loc)
      | _ -> ()

      for _, variantSerial, hasPayload, payloadTy, identLoc in variants do
        let ty =
          let tyArgs =
            tyArgs
            |> List.map (fun tySerial -> tyMeta tySerial tyDeclLoc)

          if hasPayload then
            tyFun payloadTy (tyUnion tySerial tyArgs identLoc)
          else
            tyUnit

        visitor.OnVariant(variantSerial, Def, ty, identLoc)

    | RecordTyDecl (_, fields, _, _) ->
      // after 'type'
      match firstIdentAfter visitor.GetTokens tyDeclLoc with
      | Some loc -> visitor.OnTy(RecordTySymbol tySerial, Def, loc)
      | _ -> ()

      for ident, ty, loc in fields do
        // before ':'
        match lastIdentBefore visitor.GetTokens loc with
        | Some loc -> visitor.OnField(tySerial, ident, Def, ty, loc)
        | _ -> ()

  | TModuleStmt (_, body, _) ->
    for stmt in body do
      onStmt stmt

  | TTyDeclStmt _
  | TOpenStmt _
  | TModuleSynonymStmt _ -> ()

let private findTyInStmt (ls: LangServiceState) (stmt: TStmt) (tirCtx: TirCtx) (tokenLoc: Loc) =
  let mutable contentOpt = None

  let onVisit tyOpt loc =
    // eprintfn "hover: loc=%A tyOpt=%A" loc (tyOpt |> Option.map (tyDisplayFn tirCtx))
    if loc = tokenLoc then
      contentOpt <- tyOpt

  let visitor: Visitor =
    { OnDiscardPat = fun (ty, loc) -> onVisit (Some ty) loc
      OnVar = fun (_, _, ty, loc) -> onVisit (Some ty) loc
      OnFun = fun (_, _, tyOpt, loc) -> onVisit tyOpt loc
      OnVariant = fun (_, _, ty, loc) -> onVisit (Some ty) loc
      OnPrim = fun (_, ty, loc) -> onVisit (Some ty) loc
      OnField = fun (_, _, _, ty, loc) -> onVisit (Some ty) loc
      OnTy = fun _ -> ()
      OnModule = fun _ -> ()

      GetTokens = fun docId -> tokenizeWithCache docId ls }

  dfsStmt visitor stmt
  contentOpt

[<NoComparison>]
type private Symbol =
  | DiscardSymbol
  | PrimSymbol of TPrim
  | FieldSymbol of tySerial: TySerial * Ident
  | ValueSymbol of ValueSymbol
  | TySymbol of TySymbol
  | ModuleSymbol of ModulePath

let private collectSymbolsInExpr (ls: LangServiceState) (modules: TProgram) =
  let symbols = ResizeArray()
  let onVisit symbol defOrUse loc = symbols.Add((symbol, defOrUse, loc))

  let visitor: Visitor =
    { OnDiscardPat = fun (_, loc) -> onVisit DiscardSymbol Def loc
      OnVar = fun (varSerial, defOrUse, _, loc) -> onVisit (ValueSymbol(VarSymbol varSerial)) defOrUse loc
      OnFun = fun (funSerial, defOrUse, _, loc) -> onVisit (ValueSymbol(FunSymbol funSerial)) defOrUse loc
      OnVariant =
        fun (variantSerial, defOrUse, _, loc) -> onVisit (ValueSymbol(VariantSymbol variantSerial)) defOrUse loc
      OnPrim = fun (prim, _, loc) -> onVisit (PrimSymbol prim) Use loc
      OnField = fun (tySerial, ident, defOrUse, _, loc) -> onVisit (FieldSymbol(tySerial, ident)) defOrUse loc
      OnTy = fun (tySymbol, defOrUse, loc) -> onVisit (TySymbol tySymbol) defOrUse loc
      OnModule = fun (path, defOrUse, loc) -> onVisit (ModuleSymbol path) defOrUse loc

      GetTokens = fun docId -> ls |> tokenizeWithCache docId }

  for m in modules do
    let docId = m.DocId

    match ls |> parseWithCache docId with
    | Some syntaxData ->
      let _, _, ast, _ = syntaxData

      dfsARoot visitor docId ast

    | None -> failwith "must be parsed"

  for m in modules do
    for stmt in m.Stmts do
      dfsStmt visitor stmt

  symbols

let private doFindRefs hint projectDir docId targetPos ls =
  debugFn "doFindRefs %s" hint
  let result, ls = bundleWithCache ls projectDir

  match result.ProgramOpt with
  | None ->
    debugFn "%s: no bundle result: errors %d" hint (List.length result.Errors)
    None, ls

  | Some (modules, _) ->
    let tokenOpt = findTokenAt ls docId targetPos

    match tokenOpt with
    | None ->
      debugFn "%s: token not found on position: docId=%s pos=%s" hint docId (posToString targetPos)
      None, ls

    | Some (_token, tokenPos) ->
      debugFn "%s: tokenPos=%A" hint tokenPos
      let tokenLoc = locOfDocPos docId tokenPos

      let symbols = collectSymbolsInExpr ls modules

      debugFn
        "%s: tokenLoc=%A symbols(%s)"
        hint
        tokenLoc
        (symbols
         |> Seq.map (sprintf "%A")
         |> Seq.toList
         |> String.concat "; ")

      let symbolIndex =
        symbols.FindIndex(fun (_, _, loc) -> loc = tokenLoc)

      if symbolIndex < 0 then
        debugFn "%s: no symbol" hint
        None, ls
      else
        let targetSymbol, _, _ = symbols.[symbolIndex]

        let result =
          symbols
          |> Seq.filter (fun (symbol, _, _) -> symbol = targetSymbol)

        Some result, ls

let private doFindDefsOrUses hint projectDir docId targetPos includeDef includeUse ls =
  match doFindRefs hint projectDir docId targetPos ls with
  | None, ls -> None, ls

  | Some symbols, ls ->
    let map = MutMultimap.empty ()

    for _, defOrUse, loc in symbols do
      match defOrUse with
      | Def when not includeDef -> ()
      | Use when not includeUse -> ()
      | _ ->
        map
        |> MutMultimap.insert (locToDoc loc) (locToPos loc)

    let result =
      [ for KeyValue (docId, posList) in map do
          for range in resolveTokenRanges ls docId (List.ofSeq posList) do
            docId, range ]

    Some result, ls

module LangService =
  let create (host: LangServiceHost) : LangServiceState =
    { NewParseResults = []
      BundleCache = TMap.empty compare
      Host = host }

  let validateProject projectDir (ls: LangServiceState) : Error list * LangServiceState =
    let result, ls = bundleWithCache ls projectDir
    result.Errors, ls

  let completion
    (projectDir: ProjectDir)
    (docId: DocId)
    (targetPos: Pos)
    (ls: LangServiceState)
    : string list * LangServiceState =
    let tokens = tokenizeWithCache docId ls

    let inModuleLine =
      let y, _ = targetPos

      tokens
      |> Seq.skipWhile (fun (_, pos) -> pos < (y, 0))
      |> Seq.takeWhile (fun (_, pos) -> pos < (y + 1, 0))
      |> Seq.exists (fun (token, _) ->
        match token with
        | ModuleToken
        | OpenToken -> true
        | _ -> false)

    let result =
      if inModuleLine then
        let h = ls.Host

        List.append (h.MiloneHomeModules()) (h.FindModulesInDir projectDir)
        |> List.collect (fun (p, m) -> [ p; m ])
        |> MutSet.ofSeq
        |> MutSet.toList
      else
        []

    result, ls

  /// `(defs, uses) option`
  let findRefs
    projectDir
    docId
    targetPos
    (ls: LangServiceState)
    : ((DocId * Pos) list * (DocId * Pos) list) option * LangServiceState =
    match doFindRefs "findRefs" projectDir docId targetPos ls with
    | Some symbols, ls ->
      let defs = ResizeArray()
      let uses = ResizeArray()

      for _, defOrUse, Loc (docId, y, x) in symbols do
        match defOrUse with
        | Def -> defs.Add(docId, (y, x))
        | Use -> uses.Add(docId, (y, x))

      Some(Seq.toList defs, Seq.toList uses), ls

    | None, ls -> None, ls

  /// `(reads, writes) option`
  let documentHighlight
    projectDir
    docId
    targetPos
    (ls: LangServiceState)
    : (Range list * Range list) option * LangServiceState =
    match doFindRefs "highlight" projectDir docId targetPos ls with
    | Some symbols, ls ->
      let reads = ResizeArray()
      let writes = ResizeArray()

      for _, defOrUse, loc in symbols do
        if locToDoc loc = docId then
          let pos = loc |> locToPos

          match defOrUse with
          | Def -> writes.Add(pos)
          | Use -> reads.Add(pos)

      let collect (posArray: ResizeArray<Pos>) =
        resolveTokenRanges ls docId (List.ofSeq posArray)
        |> Seq.toList

      Some(collect reads, collect writes), ls

    | None, ls -> None, ls

  let hover projectDir (docId: DocId) (targetPos: Pos) (ls: LangServiceState) : string option * LangServiceState =
    let result, ls = bundleWithCache ls projectDir

    match result.ProgramOpt with
    | None ->
      debugFn "hover: no bundle result: errors %d" (List.length result.Errors)
      None, ls

    | Some (modules, tirCtx) ->
      let tokenOpt = findTokenAt ls docId targetPos

      match tokenOpt with
      | None ->
        debugFn "hover: token not found on position: docId=%s pos=%s" docId (posToString targetPos)
        None, ls

      | Some (_token, tokenPos) ->
        let tokenLoc = locOfDocPos docId tokenPos

        // eprintfn "hover: %A, tokenLoc=%A" token tokenLoc

        match modules
              |> List.tryPick (fun m ->
                m.Stmts
                |> List.tryPick (fun stmt -> findTyInStmt ls stmt tirCtx tokenLoc))
          with
        | None -> None, ls
        | Some ty -> Some(tyDisplayFn tirCtx ty), ls

  let definition projectDir docId targetPos (ls: LangServiceState) : (DocId * Range) list * LangServiceState =
    let includeDef = true
    let includeUse = false

    let resultOpt, ls =
      doFindDefsOrUses "definition" projectDir docId targetPos includeDef includeUse ls

    Option.defaultValue [] resultOpt, ls

  let references
    projectDir
    docId
    targetPos
    (includeDef: bool)
    (ls: LangServiceState)
    : (DocId * Range) list * LangServiceState =
    let includeUse = true

    let resultOpt, ls =
      doFindDefsOrUses "references" projectDir docId targetPos includeDef includeUse ls

    Option.defaultValue [] resultOpt, ls
