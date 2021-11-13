/// Module for LSP to talk directly to MiloneLang compiler.
module rec MiloneLspServer.Lsp

open MiloneShared.SharedTypes
open MiloneStd.StdMap
open MiloneStd.StdPath
open MiloneStd.StdSet
open MiloneSyntax.Syntax
open MiloneSyntax.Tir

module U = MiloneLspServer.Util // FIXME: don't depend

module C = MiloneStd.StdChar
module AstBundle = MiloneSyntax.AstBundle
module SyntaxApi = MiloneSyntax.SyntaxApi
module SyntaxTokenize = MiloneSyntax.SyntaxTokenize
module TySystem = MiloneSyntax.TySystem

type Range = Pos * Pos
type Location = DocId * Pos * Pos
type LError = string * Location

type private FilePath = string
type private DocVersion = int
type private Error = string * Loc

// Hide compiler-specific types from other modules.

[<NoEquality; NoComparison>]
type LToken = private LToken of Token * Pos

[<NoEquality; NoComparison>]
type LTokenList = private LTokenList of TokenizeFullResult

[<NoEquality; NoComparison>]
type LSyntaxData = private LSyntaxData of ModuleSyntaxData

// -----------------------------------------------
// Utils
// -----------------------------------------------

/// Folds single value to update a state.
///
/// Usage: `state |> up folder item1 |> up folder item2 |> ...`
let private up (folder: 'S -> 'T -> 'S) (item: 'T) (state: 'S) : 'S = folder state item

let private upList (folder: 'S -> 'T -> 'S) (items: 'T list) (state: 'S) : 'S = List.fold folder state items

// FIXME: avoid using generic compare
let private listUnique xs =
  xs |> TSet.ofList compare |> TSet.toList

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

module Multimap =
  let add key value map =
    map
    |> TMap.add
         key
         (value
          :: (map |> TMap.tryFind key |> Option.defaultValue []))

// -----------------------------------------------
// Syntax
// -----------------------------------------------

let private nameToIdent (Name (ident, _)) = ident
let private nameToPos (Name (_, pos)) = pos

let private pathToPos altPos path =
  match path |> List.tryLast with
  | Some name -> name |> nameToPos
  | None -> altPos

let private locOfDocPos (docId: DocId) (pos: Pos) : Loc =
  let y, x = pos
  Loc(docId, y, x)

let private locToDoc (loc: Loc) : DocId =
  let (Loc (docId, _, _)) = loc
  docId

let private locToPos (loc: Loc) : Pos =
  let (Loc (_, y, x)) = loc
  y, x

let private locToDocPos (loc: Loc) : DocId * Pos =
  let (Loc (docId, y, x)) = loc
  docId, (y, x)

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

let private resolveTokenRanges tokens posList : Range list =
  let posSet = TSet.ofList compare posList

  let rec go (posSet, ranges) tokens =
    match tokens with
    | [] -> ranges

    | [ (_, (y, _)) ] ->
      let p = y + 1, 0
      (p, p) :: ranges

    | (_, p1) :: (((_, p2) :: _) as tokens) ->
      let removed, posSet = posSet |> TSet.remove p1

      let rangeAcc =
        if removed then
          (p1, p2) :: ranges
        else
          ranges

      go (posSet, rangeAcc) tokens

  go (posSet, []) tokens

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

let private parseAllTokens projectName moduleName docId allTokens =
  let tokens =
    allTokens
    |> List.filter (fun (token, _) -> token |> isTrivia |> not)

  let kind =
    SyntaxApi.getModuleKind projectName moduleName

  let docId, _, ast, errors = SyntaxApi.parseModule docId kind tokens

  docId, allTokens, ast, errors

let private tyDisplayFn (tirCtx: TirCtx) ty =
  let getTyName tySerial =
    tirCtx.Tys
    |> TMap.tryFind tySerial
    |> Option.map tyDefToName

  TySystem.tyDisplay getTyName ty

// -----------------------------------------------
// Abstraction
// -----------------------------------------------

module LToken =
  let getPos (LToken (_, pos)) : Pos = pos

  /// FIXME: too specific
  let isModuleOrOpenKeyword (LToken (token, _)) =
    match token with
    | ModuleToken
    | OpenToken -> true
    | _ -> false

module LTokenList =
  let private host = tokenizeHostNew ()

  let empty = LTokenList []

  let tryLast (LTokenList tokens) =
    tokens |> List.tryLast |> Option.map LToken

  let tokenizeAll text =
    SyntaxTokenize.tokenizeAll host text |> LTokenList

  let findAt (pos: Pos) (LTokenList tokens) : LToken option =
    match findTokenAt tokens pos with
    | Some (token, pos) -> Some(LToken(token, pos))
    | None -> None

  let resolveRanges (posList: Pos list) (LTokenList tokens) : Range list = resolveTokenRanges tokens posList

  let filterByLine (y: int) (LTokenList tokens) : LToken list =
    tokens
    |> List.skipWhile (fun (_, pos) -> pos < (y, 0))
    |> List.takeWhile (fun (_, pos) -> pos < (y + 1, 0))
    |> List.map (fun (token, pos) -> LToken(token, pos))

module LSyntaxData =
  let parse projectName moduleName docId (LTokenList tokens) =
    parseAllTokens projectName moduleName docId tokens
    |> LSyntaxData

  let getDocId syntaxData =
    let (LSyntaxData (docId, _, _, _)) = syntaxData
    docId

  let getTokens syntaxData =
    let (LSyntaxData (_, tokens, _, _)) = syntaxData
    LTokenList tokens

// -----------------------------------------------
// Project-wise analysis
// -----------------------------------------------

/// Operations for project analysis.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ProjectAnalysisHost =
  { GetDocVersion: DocId -> DocVersion option
    Tokenize: DocId -> DocVersion * LTokenList
    Parse: DocId -> (DocVersion * LSyntaxData) option

    MiloneHome: FilePath
    ReadTextFile: string -> Future<string option>
    MiloneHomeModules: unit -> (ProjectName * ModuleName) list
    FindModulesInDir: ProjectDir -> (ProjectName * ModuleName) list }

/// State of project analysis.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ProjectAnalysis =
  private
    { NewTokenizeCache: TreeMap<DocId, LTokenList>
      NewParseResults: (DocVersion * LSyntaxData) list
      BundleCache: TreeMap<ProjectDir, BundleResult>
      Host: ProjectAnalysisHost }

let private emptyTokenizeCache: TreeMap<DocId, LTokenList> = TMap.empty compare

let private getVersion docId (pa: ProjectAnalysis) =
  pa.Host.GetDocVersion docId
  |> Option.defaultValue 0

let private tokenizeWithCache docId (pa: ProjectAnalysis) =
  match pa.NewTokenizeCache |> TMap.tryFind docId with
  | Some (LTokenList tokens) -> tokens, pa

  | None ->
    let tokens = pa.Host.Tokenize docId |> snd

    let pa =
      { pa with NewTokenizeCache = pa.NewTokenizeCache |> TMap.add docId tokens }

    let (LTokenList tokens) = tokens
    tokens, pa

let private parseWithCache docId (pa: ProjectAnalysis) = pa.Host.Parse docId |> Option.map snd

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type BundleResult =
  private
    { ProgramOpt: (TProgram * TirCtx) option
      Errors: Error list
      DocVersions: (DocId * DocVersion) list
      ParseResults: (DocVersion * LSyntaxData) list }

let private doBundle (pa: ProjectAnalysis) projectDir : BundleResult =
  let miloneHome = pa.Host.MiloneHome
  let projectDir = projectDir |> pathStrTrimEndPathSep
  let projectName = projectDir |> pathStrToStem

  let fetchModuleUsingCache _ (projectName: string) (moduleName: string) =
    let docId =
      AstBundle.computeDocId projectName moduleName

    match pa |> parseWithCache docId with
    | None -> Future.just None
    | Some (LSyntaxData syntaxData) -> Future.just (Some syntaxData)

  let syntaxCtx =
    let host: SyntaxApi.FetchModuleHost =
      { EntryProjectDir = projectDir
        EntryProjectName = projectName
        MiloneHome = miloneHome
        ReadTextFile = pa.Host.ReadTextFile
        WriteLog = fun _ -> () }

    SyntaxApi.newSyntaxCtx host
    |> SyntaxApi.SyntaxCtx.withFetchModule fetchModuleUsingCache

  let layers, result =
    SyntaxApi.performSyntaxAnalysis syntaxCtx

  let docVersions =
    layers
    |> List.collect (fun modules ->
      modules
      |> List.map (fun (docId, _, _, _) -> docId, getVersion docId pa))

  let parseResults =
    layers
    |> List.collect (fun modules ->
      modules
      |> List.map (fun ((docId, _, _, _) as syntaxData) ->
        let v = getVersion docId pa
        v, LSyntaxData syntaxData))

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

let private bundleWithCache (pa: ProjectAnalysis) projectDir : BundleResult * ProjectAnalysis =
  let docsAreAllFresh docVersions =
    docVersions
    |> List.forall (fun (docId, version) -> getVersion docId pa <= version)

  let cacheOpt =
    pa.BundleCache |> TMap.tryFind projectDir

  match cacheOpt with
  | Some result when docsAreAllFresh result.DocVersions ->
    // traceFn "bundle cache reused"
    result, pa

  | _ ->
    // match cacheOpt with
    // | Some _ -> eprintfn "bundle cache invalidated"
    // | _ -> eprintfn "bundle cache not found"

    let result = doBundle pa projectDir

    let pa =
      { pa with
          NewTokenizeCache =
            result.ParseResults
            |> List.fold
                 (fun map (_, syntaxData) ->
                   let (LSyntaxData (docId, tokens, _, _)) = syntaxData
                   map |> TMap.add docId (LTokenList tokens))
                 pa.NewTokenizeCache
          NewParseResults = List.append result.ParseResults pa.NewParseResults
          BundleCache = pa.BundleCache |> TMap.add projectDir result }

    result, pa

// -----------------------------------------------
// Find references
// -----------------------------------------------

/// Path of module names.
///
/// - File module: `[projectName; moduleName]`
/// - Inner module: `[projectName; moduleName; name1; name2; ...]`
/// - Module synonym: `[docId; name]`
type private ModulePath = string list

[<NoComparison>]
type Symbol =
  private
  | DiscardSymbol
  | PrimSymbol of TPrim
  | FieldSymbol of tySerial: TySerial * Ident
  | ValueSymbol of ValueSymbol
  | TySymbol of TySymbol
  | ModuleSymbol of ModulePath

[<NoEquality; NoComparison>]
type DefOrUse =
  | Def
  | Use

[<NoEquality; NoComparison>]
type private Loc2 =
  | At of Loc
  | PreviousIdent of Loc
  | NextIdent of Loc

// FIXME: name
type private SymbolOccurrence1 = Symbol * DefOrUse * Loc
type private SymbolOccurrence = Symbol * DefOrUse * Ty option * Loc2

let private lowerAExpr docId acc expr : SymbolOccurrence list =
  let onExpr acc expr = lowerAExpr docId acc expr
  let onExprOpt acc exprOpt = exprOpt |> Option.fold onExpr acc
  let onExprs acc exprs = exprs |> List.fold onExpr acc

  let isModuleSynonymLike (s: string) = s.Length = 1 && C.isUpper s.[0]
  let isModuleNameLike (s: string) = s.Length >= 1 && C.isUpper s.[0]
  let isModulePathLike path = path |> List.forall isModuleNameLike
  let toLoc (y, x) = At(Loc(docId, y, x))

  match expr with
  | AMissingExpr _
  | ALitExpr _
  | AIdentExpr _ -> acc

  | AListExpr (items, _) -> onExprs acc items

  | ARecordExpr (baseOpt, fields, _) ->
    acc
    |> up onExprOpt baseOpt
    |> up (List.fold (fun acc (_, init, _) -> onExpr acc init)) fields

  | AIfExpr (cond, body, alt, _) ->
    acc
    |> up onExpr cond
    |> up onExpr body
    |> up onExprOpt alt

  | AMatchExpr (cond, arms, _) ->
    acc
    |> up onExpr cond
    |> up
         (List.fold (fun acc arm ->
           let (AArm (_, guard, body, _)) = arm
           acc |> up onExprOpt guard |> up onExpr body))
         arms

  | AFunExpr (_, body, _) -> onExpr acc body

  | ANavExpr (l, _, _) ->
    match l with
    | AIdentExpr (Name (l, pos)) when l.Length = 1 && C.isUpper l.[0] ->
      (ModuleSymbol [ docId; l ], Use, None, toLoc pos)
      :: acc

    | ANavExpr (AIdentExpr p, m, _) ->
      let path = [ p; m ] |> List.map nameToIdent

      if isModulePathLike path then
        (ModuleSymbol path, Use, None, toLoc (nameToPos m))
        :: acc
      else
        acc

    | ANavExpr _ -> acc

    | _ -> onExpr acc l

  | AIndexExpr (l, r, _) -> onExprs acc [ l; r ]
  | AUnaryExpr (_, arg, _) -> onExpr acc arg
  | ABinaryExpr (_, l, r, _) -> onExprs acc [ l; r ]
  | ARangeExpr (l, r, _) -> onExprs acc [ l; r ]
  | ATupleExpr (items, _) -> onExprs acc items
  | AAscribeExpr (l, _, _) -> onExpr acc l

  | ASemiExpr (stmts, last, _) -> acc |> up onExprs stmts |> up onExpr last

  | ALetExpr (_, _, init, next, _) -> lowerAExpr docId (onExpr acc init) next

let private lowerADecl docId acc decl : SymbolOccurrence list =
  let onExpr acc expr = lowerAExpr docId acc expr
  let onDecl acc decl = lowerADecl docId acc decl
  let toLoc (y, x) = At(Loc(docId, y, x))

  match decl with
  | AExprDecl expr -> onExpr acc expr
  | ALetDecl (_, _, init, _) -> onExpr acc init

  | ATySynonymDecl _
  | AUnionTyDecl _
  | ARecordTyDecl _ -> acc

  | AOpenDecl (path, pos) ->
    let pos = path |> pathToPos pos

    (ModuleSymbol(path |> List.map nameToIdent), Use, None, toLoc pos)
    :: acc

  | AModuleSynonymDecl (Name (synonym, identPos), path, pos) ->
    let acc =
      (ModuleSymbol [ docId; synonym ], Def, None, toLoc identPos)
      :: acc

    let pos = path |> pathToPos pos

    (ModuleSymbol(path |> List.map nameToIdent), Use, None, toLoc pos)
    :: acc

  | AModuleDecl (_, _, _, decls, _) -> acc |> up (List.fold onDecl) decls

  | AAttrDecl (_, next, _) -> lowerADecl docId acc next

let private lowerARoot (docId: DocId) acc root : SymbolOccurrence list =
  let toLoc (y, x) = At(Loc(docId, y, x))
  let (ARoot (headOpt, decls)) = root

  let acc =
    match headOpt with
    | Some (path, pos) ->
      let pos = path |> pathToPos pos

      (ModuleSymbol(path |> List.map nameToIdent), Def, None, toLoc pos)
      :: acc

    | _ ->
      let path = docId.Split(".") |> Array.toList

      (ModuleSymbol path, Def, None, toLoc (0, 0))
      :: acc

  acc |> up (List.fold (lowerADecl docId)) decls

let private lowerTy acc ty : (Symbol * DefOrUse * Ty option * Loc2) list =
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

  acc |> up (List.fold lowerTy) tyArgs

let private lowerTPat acc pat : SymbolOccurrence list =
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
      | TAscribePN -> lowerTy acc ty
      | _ -> acc

    acc |> up (List.fold lowerTPat) pats

  | TAsPat (bodyPat, varSerial, loc) ->
    let acc =
      let ty = patToTy bodyPat

      (ValueSymbol(VarSymbol varSerial), Def, Some ty, At loc)
      :: acc

    lowerTPat acc bodyPat

  | TOrPat (l, r, _) -> acc |> up lowerTPat l |> up lowerTPat r

let private lowerTExpr acc expr =
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
    |> up lowerTExpr cond
    |> up
         (List.fold (fun acc (pat, guard, body) ->
           acc
           |> up lowerTPat pat
           |> up lowerTExpr guard
           |> up lowerTExpr body))
         arms

  | TRecordExpr (baseOpt, fields, ty, _) ->
    acc
    |> up (Option.fold lowerTExpr) baseOpt
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

           acc |> up lowerTExpr init))
         fields

  | TNavExpr (l, (r, loc), ty, _) ->
    let acc = acc |> up lowerTExpr l

    match exprToTy l with
    | Ty (RecordTk (tySerial, _), _) ->
      (FieldSymbol(tySerial, r), Use, Some ty, At loc)
      :: acc
    | _ -> acc

  | TNodeExpr (_, args, _, _) -> acc |> up (List.fold lowerTExpr) args

  | TBlockExpr (_, stmts, last) ->
    acc
    |> up (List.fold lowerTStmt) stmts
    |> up lowerTExpr last

let private lowerTStmt acc stmt =
  match stmt with
  | TExprStmt expr -> lowerTExpr acc expr

  | TLetValStmt (pat, init, _) -> acc |> up lowerTPat pat |> up lowerTExpr init

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
    |> up lowerTy (exprToTy body)
    |> up (List.fold lowerTPat) argPats
    |> up lowerTExpr body

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

  | TModuleStmt (_, stmts, _) -> acc |> up (List.fold lowerTStmt) stmts

  | TTyDeclStmt _
  | TOpenStmt _
  | TModuleSynonymStmt _ -> acc

let private lowerTModules acc modules =
  modules
  |> List.fold (fun acc (m: TModule) -> acc |> up (List.fold lowerTStmt) m.Stmts) acc

/// Resolve locations.
let private resolveLoc (symbols: SymbolOccurrence list) pa =
  symbols
  |> List.mapFold
       (fun (pa: ProjectAnalysis) item ->
         let tokenize loc pa =
           let (Loc (docId, y, x)) = loc
           let tokens, pa = tokenizeWithCache docId pa
           tokens, docId, (y, x), pa

         let symbol, defOrUse, tyOpt, loc = item

         let locOpt, pa =
           match loc with
           | At loc -> Some loc, pa

           | PreviousIdent loc ->
             let tokens, docId, pos, pa = tokenize loc pa
             lastIdentBefore tokens docId pos, pa

           | NextIdent loc ->
             let tokens, docId, pos, pa = tokenize loc pa
             firstIdentAfter tokens docId pos, pa

         match locOpt with
         | Some loc -> Some(symbol, defOrUse, tyOpt, loc), pa
         | None -> None, pa)
       pa
  |> fst
  |> List.choose id

let private findTyInStmt (pa: ProjectAnalysis) (modules: TProgram) (tokenLoc: Loc) =
  let symbols = lowerTModules [] modules

  resolveLoc symbols pa
  |> List.tryPick (fun (_, _, tyOpt, loc) ->
    match tyOpt with
    | Some ty when loc = tokenLoc -> Some ty
    | _ -> None)

let private collectSymbolsInExpr (pa: ProjectAnalysis) (modules: TProgram) =
  let parseModule (m: TModule) =
    let docId = m.DocId

    match pa |> parseWithCache docId with
    | Some (LSyntaxData (_, _, ast, _)) -> docId, ast
    | None -> failwith "must be parsed"

  []
  |> up
       (List.fold (fun acc m ->
         let docId, ast = parseModule m
         lowerARoot docId acc ast))
       modules
  |> up lowerTModules modules
  |> (fun acc -> resolveLoc acc pa)
  |> List.map (fun (symbol, defOrUse, _, loc) -> symbol, defOrUse, loc)

// Provides fundamental operations as building block of queries.
// FIXME: name?
module ProjectAnalysis1 =
  let tokenize (docId: DocId) (pa: ProjectAnalysis) : LTokenList * ProjectAnalysis =
    let tokens, pa = tokenizeWithCache docId pa
    LTokenList tokens, pa

  let collectSymbols (b: BundleResult) (pa: ProjectAnalysis) =
    match b.ProgramOpt with
    | None -> None
    | Some (modules, _) -> collectSymbolsInExpr pa modules |> Some

  let getTyName (b: BundleResult) (tokenLoc: Loc) (pa: ProjectAnalysis) =
    match b.ProgramOpt with
    | None -> None
    | Some (modules, tirCtx) ->
      match findTyInStmt pa modules tokenLoc with
      | None -> Some None
      | Some ty -> tyDisplayFn tirCtx ty |> Some |> Some

// -----------------------------------------------
// Lang service
// -----------------------------------------------

// FIXME: move these analysis process to other module decoupled with compiler.

let private doFindRefs hint projectDir docId targetPos pa =
  U.debugFn "doFindRefs %s" hint
  let tokens, pa = ProjectAnalysis1.tokenize docId pa
  let tokenOpt = tokens |> LTokenList.findAt targetPos

  match tokenOpt with
  | None ->
    U.debugFn "%s: token not found on position: docId=%s pos=%s" hint docId (posToString targetPos)
    None, pa

  | Some token ->
    let tokenLoc = locOfDocPos docId (LToken.getPos token)
    U.debugFn "%s: tokenLoc=%A" hint tokenLoc

    let bundleResult, pa = bundleWithCache pa projectDir

    match pa |> ProjectAnalysis1.collectSymbols bundleResult with
    | None ->
      U.debugFn "%s: no bundle result: errors %d" hint (List.length bundleResult.Errors)
      None, pa

    | Some symbols ->
      match symbols
            |> List.tryFind (fun (_, _, loc) -> loc = tokenLoc)
        with
      | None ->
        U.debugFn "%s: no symbol" hint
        None, pa

      | Some (targetSymbol, _, _) ->
        let result =
          symbols
          |> List.filter (fun (symbol, _, _) -> symbol = targetSymbol)

        Some result, pa

let private doFindDefsOrUses hint projectDir docId targetPos includeDef includeUse pa =
  match doFindRefs hint projectDir docId targetPos pa with
  | None, pa -> None, pa

  | Some symbols, pa ->
    let result, pa =
      symbols
      |> Seq.toList
      |> List.fold
           (fun map (_, defOrUse, loc) ->
             match defOrUse with
             | Def when not includeDef -> map
             | Use when not includeUse -> map

             | _ -> map |> Multimap.add (locToDoc loc) (locToPos loc))
           (TMap.empty compare)
      |> TMap.toList
      |> List.mapFold
           (fun pa (docId, posList) ->
             let tokens, pa = ProjectAnalysis1.tokenize docId pa

             let ranges =
               tokens |> LTokenList.resolveRanges posList

             (docId, ranges), pa)
           pa

    let result =
      result
      |> List.collect (fun (docId, ranges) -> ranges |> List.map (fun range -> docId, range))

    Some result, pa

module ProjectAnalysis =
  let create (host: ProjectAnalysisHost) : ProjectAnalysis =
    { NewTokenizeCache = emptyTokenizeCache
      NewParseResults = []
      BundleCache = TMap.empty compare
      Host = host }

  let withHost (host: ProjectAnalysisHost) pa : ProjectAnalysis = { pa with Host = host }

  let drain (pa: ProjectAnalysis) =
    pa.NewTokenizeCache,
    pa.NewParseResults,
    { pa with
        NewTokenizeCache = emptyTokenizeCache
        NewParseResults = [] }

  let validateProject projectDir (pa: ProjectAnalysis) : LError list * ProjectAnalysis =
    let result, pa = bundleWithCache pa projectDir

    let errorListList, pa =
      result.Errors
      |> List.fold
           (fun map (msg, loc) ->
             let docId, pos = locToDocPos loc
             map |> Multimap.add docId (msg, pos))
           (TMap.empty compare)
      |> TMap.toList
      |> List.mapFold
           (fun pa (docId, errorList) ->
             let tokens, pa = ProjectAnalysis1.tokenize docId pa

             // FIXME: parser reports error at EOF as y=-1. Fix up that here.
             let errorList =
               errorList
               |> List.map (fun (msg, pos) ->
                 let y, _ = pos

                 if y >= 0 then
                   msg, pos
                 else
                   match tokens |> LTokenList.tryLast with
                   | Some token ->
                     let y, _ = token |> LToken.getPos
                     msg, (y + 1, 0)

                   | _ -> msg, (0, 0))

             let posList = errorList |> List.map snd

             let rangeMap =
               tokens
               |> LTokenList.resolveRanges posList
               |> Seq.map (fun (l, r) -> l, r)
               |> Seq.toList
               |> TMap.ofList compare

             let locList =
               errorList
               |> List.map (fun (msg, pos) ->
                 match rangeMap |> TMap.tryFind pos with
                 | Some r -> msg, (docId, pos, r)
                 | None -> msg, (docId, pos, pos))

             locList, pa)
           pa

    List.collect id errorListList, pa

  let completion
    (projectDir: ProjectDir)
    (docId: DocId)
    (targetPos: Pos)
    (pa: ProjectAnalysis)
    : string list * ProjectAnalysis =
    let tokens, pa = ProjectAnalysis1.tokenize docId pa

    let inModuleLine =
      let y, _ = targetPos

      tokens
      |> LTokenList.filterByLine y
      |> List.exists LToken.isModuleOrOpenKeyword

    let result =
      if inModuleLine then
        let h = pa.Host

        List.append (h.MiloneHomeModules()) (h.FindModulesInDir projectDir)
        |> List.collect (fun (p, m) -> [ p; m ])
        |> listUnique
      else
        []

    result, pa

  /// `(defs, uses) option`
  let findRefs
    projectDir
    docId
    targetPos
    (pa: ProjectAnalysis)
    : ((DocId * Pos) list * (DocId * Pos) list) option * ProjectAnalysis =
    match doFindRefs "findRefs" projectDir docId targetPos pa with
    | Some symbols, pa ->
      let defs, uses =
        symbols
        |> List.fold
             (fun (defAcc, useAcc) (_, defOrUse, Loc (docId, y, x)) ->
               match defOrUse with
               | Def -> (docId, (y, x)) :: defAcc, useAcc
               | Use -> defAcc, (docId, (y, x)) :: useAcc)
             ([], [])

      Some(defs, uses), pa

    | None, pa -> None, pa

  /// `(reads, writes) option`
  let documentHighlight
    projectDir
    docId
    targetPos
    (pa: ProjectAnalysis)
    : (Range list * Range list) option * ProjectAnalysis =
    match doFindRefs "highlight" projectDir docId targetPos pa with
    | Some symbols, pa ->
      let reads, writes =
        symbols
        |> List.fold
             (fun (readAcc, writeAcc) (_, defOrUse, loc) ->
               if locToDoc loc = docId then
                 let pos = loc |> locToPos

                 match defOrUse with
                 | Def -> readAcc, pos :: writeAcc
                 | Use -> pos :: readAcc, writeAcc
               else
                 readAcc, writeAcc)
             ([], [])

      let tokens, pa = ProjectAnalysis1.tokenize docId pa

      let collect posList =
        tokens |> LTokenList.resolveRanges posList

      Some(collect reads, collect writes), pa

    | None, pa -> None, pa

  let hover projectDir (docId: DocId) (targetPos: Pos) (pa: ProjectAnalysis) : string option * ProjectAnalysis =
    let tokens, pa = ProjectAnalysis1.tokenize docId pa
    let tokenOpt = tokens |> LTokenList.findAt targetPos

    match tokenOpt with
    | None ->
      U.debugFn "hover: token not found on position: docId=%s pos=%s" docId (posToString targetPos)
      None, pa

    | Some token ->
      let tokenLoc = locOfDocPos docId (LToken.getPos token)
      // eprintfn "hover: %A, tokenLoc=%A" token tokenLoc

      let result, pa = bundleWithCache pa projectDir

      match ProjectAnalysis1.getTyName result tokenLoc pa with
      | None ->
        U.debugFn "hover: no bundle result: errors %d" (List.length result.Errors)
        None, pa

      | Some tyNameOpt -> tyNameOpt, pa

  let definition projectDir docId targetPos (pa: ProjectAnalysis) : (DocId * Range) list * ProjectAnalysis =
    let includeDef = true
    let includeUse = false

    let resultOpt, pa =
      doFindDefsOrUses "definition" projectDir docId targetPos includeDef includeUse pa

    Option.defaultValue [] resultOpt, pa

  let references
    projectDir
    docId
    targetPos
    (includeDef: bool)
    (pa: ProjectAnalysis)
    : (DocId * Range) list * ProjectAnalysis =
    let includeUse = true

    let resultOpt, pa =
      doFindDefsOrUses "references" projectDir docId targetPos includeDef includeUse pa

    Option.defaultValue [] resultOpt, pa
