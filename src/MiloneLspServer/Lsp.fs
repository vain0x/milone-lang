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

/// Folds single value to update a state.
///
/// Usage: `state |> up folder item1 |> up folder item2 |> ...`
let private up (folder: 'S -> 'T -> 'S) (item: 'T) (state: 'S) : 'S = folder state item

let private upList (folder: 'S -> 'T -> 'S) (items: 'T list) (state: 'S) : 'S = List.fold folder state items

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

let private tokenizeWithCache docId (ls: LangServiceState) =
  match ls.NewTokenizeCache |> TMap.tryFind docId with
  | Some it -> it, ls

  | None ->
    let tokens = ls.Host.Tokenize docId |> snd

    let ls =
      { ls with NewTokenizeCache = ls.NewTokenizeCache |> TMap.add docId tokens }

    tokens, ls

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
          NewTokenizeCache =
            result.ParseResults
            |> List.fold (fun map (_, (docId, tokens, _, _)) -> map |> TMap.add docId tokens) ls.NewTokenizeCache
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
  { NewTokenizeCache: TreeMap<DocId, TokenizeFullResult>
    NewParseResults: (DocVersion * ModuleSyntaxData) list
    BundleCache: TreeMap<ProjectDir, BundleResult>
    Host: LangServiceHost }

let private isTrivia token =
  match token with
  | BlankToken
  | NewlinesToken
  | CommentToken -> true

  | _ -> false

let private findTokenAt tokens (targetPos: Pos) =
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

let private resolveTokenRanges tokens (posList: Pos list) =
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

let private lastIdentBefore tokens docId pos =
  let py, px = pos

  tokens
  |> List.skipWhile (fun (_, (y, x)) -> (y, x) < (py, 0))
  |> List.takeWhile (fun (_, (y, x)) -> (y, x) <= (py, px))
  |> List.rev
  |> List.tryPick (fun (token, (y, x)) ->
    match token with
    | IdentToken _ -> Some(Loc(docId, y, x))
    | _ -> None)

let private firstIdentAfter tokens docId pos =
  let py, px = pos

  tokens
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

type private Loc2 =
  | At of Loc
  | PreviousIdent of Loc
  | NextIdent of Loc

let private dfsTy acc ty : (Symbol * DefOrUse * Ty option * Loc2) list =
  let (Ty (tk, tyArgs)) = ty

  let acc =
    match tk with
    | UnionTk (tySerial, Some loc) ->
      (TySymbol(UnionTySymbol tySerial), Use, None, At loc)
      :: acc
    | RecordTk (tySerial, Some loc) ->
      (TySymbol(RecordTySymbol tySerial), Use, None, At loc)
      :: acc
    | _ -> acc

  acc |> up (List.fold dfsTy) tyArgs

let private dfsPat acc pat : (Symbol * DefOrUse * Ty option * Loc2) list =
  match pat with
  | TLitPat _ -> acc

  | TDiscardPat (ty, loc) -> (DiscardSymbol, Use, Some ty, At loc) :: acc

  | TVarPat (_, varSerial, ty, loc) ->
    (ValueSymbol(VarSymbol varSerial), Def, Some ty, At loc)
    :: acc
  | TVariantPat (variantSerial, ty, loc) ->
    (ValueSymbol(VariantSymbol variantSerial), Use, Some ty, At loc)
    :: acc

  | TNodePat (kind, pats, ty, loc) ->
    let acc =
      match kind with
      | TVariantAppPN variantSerial ->
        (ValueSymbol(VariantSymbol variantSerial), Use, Some ty, At loc)
        :: acc
      | TAscribePN -> dfsTy acc ty
      | _ -> acc

    acc |> up (List.fold dfsPat) pats

  | TAsPat (bodyPat, varSerial, loc) ->
    let acc =
      let ty = patToTy bodyPat

      (ValueSymbol(VarSymbol varSerial), Def, Some ty, At loc)
      :: acc

    dfsPat acc bodyPat

  | TOrPat (l, r, _) -> acc |> up dfsPat l |> up dfsPat r

let private dfsExpr acc expr =
  match expr with
  | TLitExpr _ -> acc

  | TVarExpr (varSerial, ty, loc) ->
    (ValueSymbol(VarSymbol varSerial), Use, Some ty, At loc)
    :: acc
  | TFunExpr (funSerial, ty, loc) ->
    (ValueSymbol(FunSymbol funSerial), Use, Some ty, At loc)
    :: acc
  | TVariantExpr (variantSerial, ty, loc) ->
    (ValueSymbol(VariantSymbol variantSerial), Use, Some ty, At loc)
    :: acc
  | TPrimExpr (prim, ty, loc) -> (PrimSymbol prim, Use, Some ty, At loc) :: acc

  | TMatchExpr (cond, arms, _, _) ->
    acc
    |> up dfsExpr cond
    |> up
         (List.fold (fun acc (pat, guard, body) ->
           acc
           |> up dfsPat pat
           |> up dfsExpr guard
           |> up dfsExpr body))
         arms

  | TRecordExpr (baseOpt, fields, ty, _) ->
    acc
    |> up (Option.fold dfsExpr) baseOpt
    |> up
         (List.fold (fun acc (ident, init, loc) ->
           let acc =
             match ty with
             | Ty (RecordTk (tySerial, _), _) ->
               // before '='
               let loc = PreviousIdent loc

               (FieldSymbol(tySerial, ident), Use, Some ty, loc)
               :: acc
             | _ -> acc

           acc |> up dfsExpr init))
         fields

  | TNavExpr (l, (r, loc), ty, _) ->
    let acc = acc |> up dfsExpr l

    match exprToTy l with
    | Ty (RecordTk (tySerial, _), _) ->
      (FieldSymbol(tySerial, r), Use, Some ty, At loc)
      :: acc
    | _ -> acc

  | TNodeExpr (_, args, _, _) -> acc |> up (List.fold dfsExpr) args

  | TBlockExpr (_, stmts, last) ->
    acc
    |> up (List.fold dfsStmt) stmts
    |> up dfsExpr last

let private dfsStmt acc stmt =
  match stmt with
  | TExprStmt expr -> dfsExpr acc expr

  | TLetValStmt (pat, init, _) -> acc |> up dfsPat pat |> up dfsExpr init

  | TLetFunStmt (callee, _, _, argPats, body, loc) ->
    let tyFunN argTys resultTy : Ty =
      argTys
      |> List.fold (fun funTy argTy -> tyFun argTy funTy) resultTy

    let acc =
      let funTy =
        let argTys = argPats |> List.map patToTy
        let resultTy = body |> exprToTy
        tyFunN argTys resultTy

      // after 'let'
      let loc = NextIdent loc

      (ValueSymbol(FunSymbol callee), Def, Some funTy, loc)
      :: acc

    // HACK: Visit type as if let-fun has result-type ascription. Typing removes result type ascription.
    acc
    |> up dfsTy (exprToTy body)
    |> up (List.fold dfsPat) argPats
    |> up dfsExpr body

  | TTyDeclStmt (tySerial, _, tyArgs, tyDecl, tyDeclLoc) ->
    match tyDecl with
    | TySynonymDecl _ -> acc

    | UnionTyDecl (_, variants, _) ->
      let acc =
        // after 'type'
        let loc = NextIdent tyDeclLoc

        (TySymbol(UnionTySymbol tySerial), Def, None, loc)
        :: acc

      acc
      |> up
           (List.fold (fun acc v ->
             let _, variantSerial, hasPayload, payloadTy, identLoc = v

             let ty =
               let tyArgs =
                 tyArgs
                 |> List.map (fun tySerial -> tyMeta tySerial tyDeclLoc)

               if hasPayload then
                 tyFun payloadTy (tyUnion tySerial tyArgs identLoc)
               else
                 tyUnit

             (ValueSymbol(VariantSymbol variantSerial), Def, Some ty, At identLoc)
             :: acc))
           variants

    | RecordTyDecl (_, fields, _, _) ->
      let acc =
        // after 'type'
        let loc = NextIdent tyDeclLoc

        (TySymbol(RecordTySymbol tySerial), Def, None, loc)
        :: acc

      acc
      |> up
           (List.fold (fun acc (ident, ty, loc) ->
             // before ':'
             let loc = PreviousIdent loc

             (FieldSymbol(tySerial, ident), Def, Some ty, loc)
             :: acc))
           fields

  | TModuleStmt (_, stmts, _) -> acc |> up (List.fold dfsStmt) stmts

  | TTyDeclStmt _
  | TOpenStmt _
  | TModuleSynonymStmt _ -> acc

let private foldTir modules ls =
  let symbols =
    modules
    |> List.fold (fun acc (m: TModule) -> acc |> up (List.fold dfsStmt) m.Stmts) []
    |> List.rev

  // Resolve locations.
  symbols
  |> List.mapFold
       (fun (ls: LangServiceState) item ->
         let tokenize loc ls =
           let (Loc (docId, y, x)) = loc
           let tokens, ls = tokenizeWithCache docId ls
           tokens, docId, (y, x), ls

         let symbol, defOrUse, tyOpt, loc = item

         let locOpt, ls =
           match loc with
           | At loc -> Some loc, ls

           | PreviousIdent loc ->
             let tokens, docId, pos, ls = tokenize loc ls
             lastIdentBefore tokens docId pos, ls

           | NextIdent loc ->
             let tokens, docId, pos, ls = tokenize loc ls
             firstIdentAfter tokens docId pos, ls

         match locOpt with
         | Some loc -> Some(symbol, defOrUse, tyOpt, loc), ls
         | None -> None, ls)
       ls
  |> fst
  |> List.choose id

let private findTyInStmt (ls: LangServiceState) (modules: TProgram) (tokenLoc: Loc) =
  foldTir modules ls
  |> List.tryPick (fun (_, _, tyOpt, loc) ->
    match tyOpt with
    | Some ty when loc = tokenLoc -> Some ty
    | _ -> None)

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

      GetTokens = fun docId -> ls |> tokenizeWithCache docId |> fst }

  for m in modules do
    let docId = m.DocId

    match ls |> parseWithCache docId with
    | Some syntaxData ->
      let _, _, ast, _ = syntaxData

      dfsARoot visitor docId ast

    | None -> failwith "must be parsed"

  foldTir modules ls
  |> List.iter (fun (symbol, defOrUse, _, loc) -> symbols.Add((symbol, defOrUse, loc)))

  symbols

let private doFindRefs hint projectDir docId targetPos ls =
  debugFn "doFindRefs %s" hint
  let result, ls = bundleWithCache ls projectDir

  match result.ProgramOpt with
  | None ->
    debugFn "%s: no bundle result: errors %d" hint (List.length result.Errors)
    None, ls

  | Some (modules, _) ->
    let tokens, ls = tokenizeWithCache docId ls
    let tokenOpt = findTokenAt tokens targetPos

    match tokenOpt with
    | None ->
      debugFn "%s: token not found on position: docId=%s pos=%s" hint docId (posToString targetPos)
      None, ls

    | Some (_token, tokenPos) ->
      debugFn "%s: tokenPos=%A" hint tokenPos
      let tokenLoc = locOfDocPos docId tokenPos

      let symbols = collectSymbolsInExpr ls modules

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
          let tokens, _ = tokenizeWithCache docId ls

          for range in resolveTokenRanges tokens (List.ofSeq posList) do
            docId, range ]

    Some result, ls

module LangService =
  let create (host: LangServiceHost) : LangServiceState =
    { NewTokenizeCache = TMap.empty compare
      NewParseResults = []
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
    let tokens, ls = tokenizeWithCache docId ls

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

      let tokens, ls = tokenizeWithCache docId ls

      let collect (posArray: ResizeArray<Pos>) =
        resolveTokenRanges tokens (List.ofSeq posArray)
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
      let tokens, ls = tokenizeWithCache docId ls
      let tokenOpt = findTokenAt tokens targetPos

      match tokenOpt with
      | None ->
        debugFn "hover: token not found on position: docId=%s pos=%s" docId (posToString targetPos)
        None, ls

      | Some (_token, tokenPos) ->
        let tokenLoc = locOfDocPos docId tokenPos

        // eprintfn "hover: %A, tokenLoc=%A" token tokenLoc

        match findTyInStmt ls modules tokenLoc with
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
