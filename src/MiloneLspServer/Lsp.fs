/// Module for LSP to talk directly to MiloneLang compiler.
module rec MiloneLspServer.Lsp

open MiloneLspServer.LspUtil
open MiloneShared.SharedTypes
open MiloneShared.UtilParallel
open MiloneShared.UtilSymbol
open MiloneSyntax.Syntax
open MiloneSyntax.Tir
open MiloneSyntax.SyntaxApiTypes
open MiloneSyntax.SyntaxTypes
open MiloneSyntax.TirTypes
open Std.StdMap
open Std.StdSet

module C = Std.StdChar
module S = Std.StdString
module AstBundle = MiloneLspServer.AstBundle
module Manifest = MiloneSyntax.Manifest
module SyntaxApi = MiloneSyntax.SyntaxApi
module SyntaxTokenize = MiloneSyntax.SyntaxTokenize
module SyntaxTreeGen = MiloneSyntax.SyntaxTreeGen
module NameRes = MiloneSyntax.NameRes
module TySystem = MiloneSyntax.TySystem

// Hide compiler-specific types from other modules.

[<NoEquality; NoComparison>]
type LToken = private LToken of Token * Pos

// result of tokenization
type LTokenList = TokenizeFullResult

// result of parse
// (this includes Text, FullTokens and SyntaxTree unlike SyntaxData)
// (this is superset of ModuleSyntaxData)
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type LSyntax =
  { DocId: DocId

    // from ModuleSyntaxData
    ProjectName: ProjectName
    ModuleName: ModuleName
    UnmodifiedAst: ARoot

    Text: SourceCode
    LineBuffer: LineBuffer
    FullTokens: TokenizeFullResult
    Ast: ARoot
    SyntaxTree: SyntaxTree
    Errors: ModuleSyntaxError list }

type LSyntaxData = LSyntax

/// Identifier of a document.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private Doc =
  { DocId: DocId

    /// `[ ProjectName; ModuleName ]`
    ModulePath: string list }

// -----------------------------------------------
// Utils
// -----------------------------------------------

// Usage:
//  state |> up folder item1 |> up folder tem2 |> ...
/// Folds single value to update a state.
let private up (folder: 'S -> 'T -> 'S) (item: 'T) (state: 'S) : 'S = folder state item

let private upOpt (folder: 'S -> 'T -> 'S) (itemOpt: 'T option) (state: 'S) : 'S = Option.fold folder state itemOpt

let private upList (folder: 'S -> 'T -> 'S) (items: 'T list) (state: 'S) : 'S = List.fold folder state items

module Multimap =
  let ofList itemCompare entries =
    List.fold (fun map (key, value) -> add key value map) (TMap.empty itemCompare) entries

  let find key map =
    map |> TMap.tryFind key |> Option.defaultValue []

  let add key value map =
    map
    |> TMap.add
         key
         (value
          :: (map |> TMap.tryFind key |> Option.defaultValue []))

module T3 =
  let compare c0 c1 c2 l r =
    let l0, l1, l2 = l
    let r0, r1, r2 = r

    match c0 l0 r0 with
    | 0 ->
      match c1 l1 r1 with
      | 0 -> c2 l2 r2
      | c -> c
    | c -> c

// -----------------------------------------------
// Syntax
// -----------------------------------------------

let private nameToIdent (Name (ident, _)) = ident
let private nameToPos (Name (_, pos)) = pos

let private pathToPos altPos path =
  match path |> List.tryLast with
  | Some name -> name |> nameToPos
  | None -> altPos

let private isTrivia token =
  match token with
  | BlankToken
  | NewlinesToken
  | CommentToken -> true

  | _ -> false

// #findTokenAt
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

// #findTokenAt
let private findTokensAt tokens (targetPos: Pos) =
  let rec go tokens =
    match tokens with
    | []
    | [ _ ] -> []

    | (token, p1) :: (((_, p2) :: _) as tokens) ->
      if not (isTrivia token)
         && p1 <= targetPos
         && targetPos <= p2 then
        (token, p1) :: go tokens
      else if p1 > targetPos then
        []
      else
        go tokens

  go tokens

let private resolveTokenRanges tokens posList : Range list =
  let posSet = TSet.ofList compare posList

  let put p1 p2 posSet rangeAcc =
    let removed, posSet = posSet |> TSet.remove p1

    let rangeAcc =
      if removed then
        (p1, p2) :: rangeAcc
      else
        rangeAcc

    posSet, rangeAcc

  let rec go (posSet, rangeAcc) tokens =
    match tokens with
    | [] -> rangeAcc

    | [ (_, (y, _)) ] ->
      let _, rangeAcc =
        let p = y + 1, 0
        put p p posSet rangeAcc

      rangeAcc

    | (_, p1) :: (((_, p2) :: _) as tokens) ->
      let acc = put p1 p2 posSet rangeAcc
      go acc tokens

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

  let m =
    SyntaxApi.parseModule docId projectName moduleName tokens

  { m with Tokens = allTokens }

let private makeDoc1 (m: ModuleSyntaxData) : Doc =
  { DocId = m.DocId
    ModulePath = [ m.ProjectName; m.ModuleName ] }

let private makeDoc (s: LSyntax) : Doc =
  { DocId = s.DocId
    ModulePath = [ s.ProjectName; s.ModuleName ] }

// -----------------------------------------------
// Abstraction
// -----------------------------------------------

module LToken =
  let getPos (LToken (_, pos)) : Pos = pos

  // poorly designed:

  let asIdent (LToken (token, _)) =
    match token with
    | IdentToken name -> Some name
    | _ -> None

  let isDot (LToken (token, _)) =
    match token with
    | DotToken -> true
    | _ -> false

  let isEqual (LToken (token, _)) =
    match token with
    | EqualToken -> true
    | _ -> false

  let isOpen (LToken (token, _)) =
    match token with
    | OpenToken -> true
    | _ -> false

  let isModule (LToken (token, _)) =
    match token with
    | ModuleToken -> true
    | _ -> false

  let isModuleOrOpenKeyword (LToken (token, _)) =
    match token with
    | ModuleToken
    | OpenToken -> true
    | _ -> false

  let isBindingKeyword (LToken (token, _)) =
    match token with
    | LetToken
    | TypeToken
    | ModuleToken -> true
    | _ -> false

module LTokenList =
  let private host = tokenizeHostNew ()

  let empty: LTokenList = []

  let tryLast (tokens: LTokenList) =
    tokens |> List.tryLast |> Option.map LToken

  let tokenizeAll text: LTokenList =
    SyntaxTokenize.tokenizeAll host text

  let findAt (pos: Pos) (tokens: LTokenList) : LToken option =
    match findTokenAt tokens pos with
    | Some (token, pos) -> Some(LToken(token, pos))
    | None -> None

  let findAdjacent (pos: Pos) (tokens: LTokenList) : LToken list =
    findTokensAt tokens pos |> List.map LToken

  let resolveRanges (posList: Pos list) (tokens: LTokenList) : Range list = resolveTokenRanges tokens posList

  let toList (tokens: LTokenList) = tokens |> List.map LToken

  let filterByLine (y: int) (tokens: LTokenList) : LToken list =
    tokens
    |> List.skipWhile (fun (_, pos) -> pos < (y, 0))
    |> List.takeWhile (fun (_, pos) -> pos < (y + 1, 0))
    |> List.map (fun (token, pos) -> LToken(token, pos))

module LSyntaxData =
  let getDocId (s: LSyntax) = s.DocId

  let getTokens (s: LSyntax) = s.FullTokens

  let findModuleDefs (s: LSyntax) : string list =
    lowerARoot (makeDoc s) [] s.Ast
    |> List.choose (fun (symbol, defOrUse, _) ->
      match symbol, defOrUse with
      | DModuleSymbol ([ name ]), Def -> Some name
      | _ -> None)

  let findModuleSynonyms (s: LSyntax) : (string * ModulePath * Loc) list =
    lowerARoot (makeDoc s) [] s.Ast
    |> List.choose (fun (symbol, _, loc2) ->
      match symbol, resolveLoc2 s.DocId s.FullTokens loc2 with
      | DModuleSynonymDef (synonym, modulePath), Some loc -> Some(synonym, modulePath, loc)
      | _ -> None)

module internal LSyntax =
  let private host = tokenizeHostNew ()

  let ofModuleSyntaxData text (m: ModuleSyntaxData) : LSyntax =
    { DocId = m.DocId
      ProjectName = m.ProjectName
      ModuleName = m.ModuleName
      UnmodifiedAst = m.UnmodifiedAst
      Text = text
      LineBuffer = LineBuffer.compute text
      FullTokens = m.Tokens
      Ast = m.Ast
      SyntaxTree = SyntaxTreeGen.genSyntaxTree m.Tokens m.UnmodifiedAst
      Errors = m.Errors }

  let toModuleSyntaxData (s: LSyntax) : ModuleSyntaxData =
    { DocId = s.DocId
      ProjectName = s.ProjectName
      ModuleName = s.ModuleName
      Tokens = s.FullTokens
      Ast = s.Ast
      UnmodifiedAst = s.UnmodifiedAst
      Errors = s.Errors }

  let parse projectName moduleName docId (text: SourceCode) : LSyntax =
    let fullTokens = SyntaxTokenize.tokenizeAll host text

    let m =
      parseAllTokens projectName moduleName docId fullTokens

    let syntax: LSyntax =
      { DocId = docId
        ProjectName = m.ProjectName
        ModuleName = m.ModuleName
        UnmodifiedAst = m.UnmodifiedAst
        Text = text
        LineBuffer = LineBuffer.compute text
        FullTokens = fullTokens
        Ast = m.Ast
        SyntaxTree = SyntaxTreeGen.genSyntaxTree fullTokens m.UnmodifiedAst
        Errors = m.Errors }

    syntax

module BundleResult =
  let getErrors (b: BundleResult) = b.Errors

// -----------------------------------------------
// Project-wise analysis
// -----------------------------------------------

/// Operations for project analysis.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ProjectAnalysisHost =
  { ComputeDocId: ProjectName * ModuleName * DocId -> DocId
    GetCoreDocId: ModuleName -> DocId
    GetDocEntry: DocId -> DocVersion * SourceCode
    GetDocSyntax: DocId -> (DocVersion * LSyntaxData) option

    MiloneHome: FilePath
    ReadTextFile: string -> Future<string option> }

/// State of project analysis.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ProjectAnalysis =
  private
    { ProjectDir: ProjectDir
      ProjectName: ProjectName
      EntryDoc: DocId * ProjectName * ModuleName
      Db: SyntaxApi.SyntaxAnalysisDb
      BundleCache: BundleResult option
      TirSymbolsCache: SymbolOccurrence list option
      Host: ProjectAnalysisHost }

let private getVersion docId (pa: ProjectAnalysis) = pa.Host.GetDocEntry docId |> fst

// returns [] if missing
let private getTokenizeResult docId (pa: ProjectAnalysis) : LTokenList =
  match pa.Host.GetDocSyntax docId with
  | Some(_, syntax) -> syntax.FullTokens
  | _ -> []

let private getParseResult docId (pa: ProjectAnalysis) : LSyntax option =
  pa.Host.GetDocSyntax docId |> Option.map snd

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type BundleResult =
  private
    { Program: TProgram
      TirCtxOpt: TirCtx option
      Errors: (string * Loc) list
      DocVersions: (DocId * DocVersion) list
      ParseResults: (DocVersion * LSyntaxData) list }

let private bundleWithCache (pa: ProjectAnalysis) : BundleResult * ProjectAnalysis =
  let docsAreAllFresh docVersions =
    docVersions
    |> List.forall (fun (docId, version) -> getVersion docId pa = version)

  let cacheOpt = pa.BundleCache

  match cacheOpt with
  | Some result when docsAreAllFresh result.DocVersions ->
    // traceFn "bundle cache reused"
    result, pa

  | _ ->
    // match cacheOpt with
    // | Some _ -> eprintfn "bundle cache invalidated"
    // | _ -> eprintfn "bundle cache not found"

    let writeLog: string -> unit = ignore

    let fetchModuleUsingCache (r: AstBundle.FetchModuleParams) : Future<ModuleSyntaxData option> =
      let docId =
        pa.Host.ComputeDocId(r.ProjectName, r.ModuleName, r.Origin)

      match pa |> getParseResult docId with
      | None -> Future.just None
      | Some s -> Future.just (Some (LSyntax.toModuleSyntaxData s))

    let layers, bundleErrors =
      AstBundle.bundle fetchModuleUsingCache pa.EntryDoc

    let oldDocs =
      match cacheOpt with
      | Some cache -> cache.DocVersions
      | None -> []

    let newDocMap =
      layers |> List.collect (fun modules -> modules |> List.map (fun (s: ModuleSyntaxData, _) -> s.DocId))
      |> List.map (fun docId -> docId, getVersion docId pa)
      |> TMap.ofList Symbol.compare

    let invalidatedDocIds =
      oldDocs
      |> List.filter (fun (docId, u) ->
        match newDocMap |> TMap.tryFind docId with
        | Some v -> u <> v
        | _ -> true
      )
      |> List.map fst

    let result, modules, tirCtxOpt, db =
      if bundleErrors |> List.isEmpty |> not then
        Error bundleErrors, [], None, pa.Db
      else
        let layers2 =
          layers
          |> List.map (fun modules -> modules |> List.map (fun (_, m) -> m))

        let isExecutableDoc (_: DocId) = false

        SyntaxApi.performSyntaxAnalysisWithCache pa.Db writeLog isExecutableDoc layers2 invalidatedDocIds

    let docVersions =
      layers
      |> List.collect (fun modules ->
        modules
        |> List.map (fun (_, (m: ModuleSyntaxData2)) -> m.DocId, getVersion m.DocId pa))

    let parseResults =
      layers
      |> List.collect (fun modules ->
        modules
        |> List.map (fun ((m: ModuleSyntaxData), (_: ModuleSyntaxData2)) ->
          let v, text = pa.Host.GetDocEntry m.DocId
          v, LSyntax.ofModuleSyntaxData text m))

    let result : BundleResult =
      let errors =
        match result with
        | Ok () -> []
        | Error it -> it

      { Program = modules
        TirCtxOpt = tirCtxOpt
        Errors = errors
        DocVersions = docVersions
        ParseResults = parseResults }

    // let result = doBundle pa

    let pa =
      { pa with
          Db = db
          BundleCache = Some result
          TirSymbolsCache = None }

    result, pa

// -----------------------------------------------
// Find references
// -----------------------------------------------

[<NoEquality; NoComparison>]
type DefOrUse =
  | Def
  | Use

[<NoEquality; NoComparison>]
type private Loc2 =
  | At of Loc
  | PreviousIdent of Loc
  | NextIdent of Loc

/// Path of module names.
///
/// - File module: `[projectName; moduleName]`
/// - Inner module: `[projectName; moduleName; name1; name2; ...]`
/// - Module synonym: `[docId; name]`
type private ModulePath = string list

/// Symbol collected by lowering AST.
[<NoComparison>]
type DSymbol =
  | DFunSymbol of string
  | DVariantSymbol of Ident * unionIdent: Ident * defDoc: DocId
  | DFieldSymbol of Ident * recordIdent: Ident * defDoc: DocId
  | DTySymbol of string
  | DModuleSymbol of ModulePath
  | DOpenUse of ModulePath
  | DModuleSynonymDef of synonym: string * ModulePath

type private DSymbolOccurrence = DSymbol * DefOrUse * Loc2

[<NoComparison>]
type private ValueSymbol =
  | VarSymbol of varSerial: VarSerial
  | FunSymbol of funSerial: FunSerial
  | VariantSymbol of variantSerial: VariantSerial

[<NoComparison>]
type private TySymbol =
  | UnivTySymbol of univTySerial: TySerial
  | SynonymTySymbol of synonymTySerial: TySerial
  | UnionTySymbol of unionTySerial: TySerial
  | RecordTySymbol of recordTySerial: TySerial

[<NoComparison>]
type Symbol =
  private
  | DiscardSymbol
  | PrimSymbol of TPrim
  | FieldSymbol of tySerial: TySerial * Ident
  | ValueSymbol of ValueSymbol
  | TySymbol of TySymbol
  | ModuleSymbol of ModulePath
  // (this is not a symbol though)
  | RecordOccurrence

type private SymbolOccurrence = Symbol * DefOrUse * Ty option * Loc2

let private lowerATy (doc: Doc) acc ty : DSymbolOccurrence list =
  let onTy acc ty = lowerATy doc acc ty
  let onTys acc tys = tys |> List.fold onTy acc

  match ty with
  | AMissingTy _
  | AVarTy _ -> acc

  | AAppTy (_, None, _) -> acc

  | AAppTy (_, Some (Name (name, pos)), tyArgList) ->
    let acc =
      (DTySymbol name, Use, At(Loc.ofDocPos doc.DocId pos))
      :: acc

    let tyArgs =
      match tyArgList with
      | Some (_, tyArgs, _) -> tyArgs
      | None -> []

    onTys acc tyArgs

  | AParenTy (_, bodyTy, _) -> onTy acc bodyTy
  | ASuffixTy (bodyTy, _) -> onTy acc bodyTy
  | ATupleTy (itemTys, _) -> itemTys |> List.fold onTy acc
  | AFunTy (l, _, r) -> acc |> up onTy l |> up onTy r

let private lowerAPat (doc: Doc) acc pat : DSymbolOccurrence list =
  let onTy acc ty = lowerATy doc acc ty
  let onPat acc pat = lowerAPat doc acc pat
  let onPats acc pats = pats |> List.fold onPat acc
  let toLoc (y, x) = At(Loc(doc.DocId, y, x))

  match pat with
  | AMissingPat _
  | ALitPat _
  | AIdentPat _ -> acc

  | AParenPat (_, bodyPat, _) -> lowerAPat doc acc bodyPat
  | AListPat (_, itemPats, _) -> acc |> up onPats itemPats
  | ANavPat (l, _, _) -> acc |> up onPat l

  | AAppPat (l, _, r)
  | AConsPat (l, _, r) -> acc |> up onPat l |> up onPat r

  | ATuplePat (_, itemPats, _) -> acc |> up onPats itemPats
  | AAsPat (bodyPat, _, _) -> acc |> up onPat bodyPat
  | AAscribePat (l, _, r) -> acc |> up onPat l |> up onTy r
  | AOrPat (l, _, r) -> acc |> up onPat l |> up onPat r

let private lowerALetContents (doc: Doc) acc contents =
  let onTy acc ty = lowerATy doc acc ty
  let onPat acc pat = lowerAPat doc acc pat
  let onPats acc pats = pats |> List.fold onPat acc
  let onExpr acc expr = lowerAExpr doc acc expr
  let toLoc (y, x) = At(Loc(doc.DocId, y, x))

  match contents with
  | ALetContents.LetFun (_, _, name, argPats, resultTyOpt, _, body) ->
    let (Name (name, pos)) = name
    let acc = (DFunSymbol name, Def, toLoc pos) :: acc

    let acc =
      acc |> upOpt onTy (resultTyOpt |> Option.map snd)

    acc |> up onPats argPats |> up onExpr body

  | ALetContents.LetVal (_, pat, _, init) -> acc |> up onPat pat |> up onExpr init

let private lowerAExpr (doc: Doc) acc expr : DSymbolOccurrence list =
  let onTy acc ty = lowerATy doc acc ty
  let onPat acc pat = lowerAPat doc acc pat
  let onExpr acc expr = lowerAExpr doc acc expr
  let onExprOpt acc exprOpt = exprOpt |> Option.fold onExpr acc
  let onExprs acc exprs = exprs |> List.fold onExpr acc

  let isModuleSynonymLike (s: string) = s.Length = 1 && C.isUpper s.[0]
  let isModuleNameLike (s: string) = s.Length >= 1 && C.isUpper s.[0]
  let isModulePathLike path = path |> List.forall isModuleNameLike
  let toLoc (y, x) = At(Loc(doc.DocId, y, x))

  match expr with
  | AMissingExpr _
  | ALitExpr _
  | AIdentExpr _ -> acc

  | AParenExpr (_, body, _) -> lowerAExpr doc acc body
  | AListExpr (_, items, _) -> onExprs acc items

  | ARecordExpr (_, baseOpt, fields, _) ->
    acc
    |> up onExprOpt (baseOpt |> Option.map fst)
    |> up (List.fold (fun acc (_, _, init) -> onExpr acc init)) fields

  | AIfExpr (_, cond, _, body, alt) ->
    acc
    |> up onExpr cond
    |> up onExpr body
    |> up onExprOpt (alt |> Option.map snd)

  | AMatchExpr (_, cond, _, arms) ->
    acc
    |> up onExpr cond
    |> up
         (List.fold (fun acc arm ->
           let (_, pat, guard, _, body) = arm

           acc
           |> up onPat pat
           |> up onExprOpt (guard |> Option.map snd)
           |> up onExpr body))
         arms

  | AFunExpr (pos, argPats, _, body) ->
    ((DFunSymbol "<fun>", Def, toLoc pos) :: acc)
    |> upList onPat argPats
    |> up onExpr body

  | ANavExpr (l, _, _) ->
    match l with
    | AIdentExpr (Name (l, pos), None) when l.Length = 1 && C.isUpper l.[0] ->
      (DModuleSymbol(List.append doc.ModulePath [ l ]), Use, toLoc pos)
      :: acc

    | ANavExpr (AIdentExpr (p, None), _, Some m) ->
      let path = [ p; m ] |> List.map nameToIdent

      if isModulePathLike path then
        (DModuleSymbol path, Use, toLoc (nameToPos m))
        :: acc
      else
        acc

    | ANavExpr _ -> acc

    | _ -> onExpr acc l

  | AIndexExpr (l, _, _, r, _) -> onExprs acc [ l; r ]
  | AUnaryExpr (_, _, arg) -> onExpr acc arg
  | ABinaryExpr (_, l, _, r) -> onExprs acc [ l; r ]
  | ARangeExpr (l, _, r) -> onExprs acc [ l; r ]
  | ATupleExpr (_, items, _) -> onExprs acc items

  | AAscribeExpr (l, _, r) -> acc |> up onExpr l |> up onTy r
  | ASemiExpr (stmts, last, _) -> acc |> up onExprs stmts |> up onExpr last

  | ALetExpr (_, contents, nextOpt) ->
    let acc = lowerALetContents doc acc contents

    match nextOpt with
    | Some next -> lowerAExpr doc acc next
    | None -> acc

let private lowerADecl (doc: Doc) acc decl : DSymbolOccurrence list =
  let onTy acc ty = lowerATy doc acc ty
  let onPat acc pat = lowerAPat doc acc pat
  let onExpr acc expr = lowerAExpr doc acc expr
  let onDecl acc decl = lowerADecl doc acc decl
  let docId = doc.DocId
  let toLoc (y, x) = At(Loc(docId, y, x))

  match decl with
  | AExprDecl expr -> onExpr acc expr

  | ALetDecl (_, contents) -> lowerALetContents doc acc contents

  | ATySynonymDecl (_, _, name, _, _, _) ->
    let (Name (name, pos)) = name
    (DTySymbol name, Def, toLoc pos) :: acc

  | AUnionTyDecl (_, _, name, _, _, variants) ->
    let (Name (unionIdent, pos)) = name

    let acc =
      variants
      |> List.fold
           (fun acc (_, name, _) ->
             let (Name (ident, pos)) = name

             (DVariantSymbol(ident, unionIdent, docId), Def, toLoc pos)
             :: acc)
           acc

    (DTySymbol unionIdent, Def, toLoc pos) :: acc

  | ARecordTyDecl (_, _, name, _, _, _, fields, _) ->
    let (Name (recordIdent, pos)) = name

    let acc =
      fields
      |> List.fold
           (fun acc (name, _, _) ->
             let (Name (ident, pos)) = name

             (DFieldSymbol(ident, recordIdent, docId), Def, toLoc pos)
             :: acc)
           acc

    (DTySymbol recordIdent, Def, toLoc pos) :: acc

  | AOpenDecl (pos, path) ->
    let pos = path |> pathToPos pos

    (DOpenUse(path |> List.map nameToIdent), Use, toLoc pos)
    :: (DModuleSymbol(path |> List.map nameToIdent), Use, toLoc pos)
       :: acc

  | AModuleSynonymDecl (pos, Name (synonym, identPos), _, path) ->
    let acc =
      (DModuleSymbol(List.append doc.ModulePath [ synonym ]), Def, toLoc identPos)
      :: acc

    let pos = path |> pathToPos pos
    let path = path |> List.map nameToIdent

    (DModuleSynonymDef(synonym, path), Use, toLoc pos)
    :: (DModuleSymbol path, Use, toLoc pos) :: acc

  | AModuleDecl (_, _, _, Name (name, pos), _, decls) ->
    let acc =
      (DModuleSymbol [ name ], Def, toLoc pos) :: acc

    acc |> up (List.fold onDecl) decls

  | AAttrDecl (_, _, _, next) -> lowerADecl doc acc next

let private lowerARoot (doc: Doc) acc root : DSymbolOccurrence list =
  let toLoc (y, x) = At(Loc(doc.DocId, y, x))
  let (ARoot (headOpt, decls)) = root

  let pos: Pos =
    match headOpt with
    | Some (pos, _) -> pos
    | _ -> 0, 0

  let acc =
    (DModuleSymbol doc.ModulePath, Def, toLoc pos)
    :: acc

  acc |> up (List.fold (lowerADecl doc)) decls

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

  | TRecordExpr (baseOpt, fields, ty, loc) ->
    let acc = (RecordOccurrence, Def, Some ty, At loc) :: acc

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
      :: (RecordOccurrence, Use, Some ty, At loc)
      :: acc
    | _ -> acc

  | TNodeExpr (_, args, _, _) -> acc |> up (List.fold lowerTExpr) args

  | TBlockExpr (stmts, last) ->
    acc
    |> up (List.fold lowerTStmt) stmts
    |> up lowerTExpr last

let private lowerTStmt acc stmt =
  match stmt with
  | TExprStmt expr -> lowerTExpr acc expr

  | TLetValStmt (pat, init, _) -> acc |> up lowerTPat pat |> up lowerTExpr init

  | TLetFunStmt f ->
    let callee, argPats, body, loc = f.FunSerial, f.Params, f.Body, f.Loc

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

    acc
    |> up (List.fold lowerTPat) argPats
    |> up lowerTExpr body

  | TBlockStmt (_, stmts) -> acc |> up (List.fold lowerTStmt) stmts

let private lowerTModules acc modules =
  modules
  |> List.fold (fun acc (m: TModule) -> acc |> up (List.fold lowerTStmt) m.Stmts) acc

let private resolveLoc2 docId tokens (loc: Loc2) =
  match loc with
  | At loc -> Some loc

  | PreviousIdent (Loc (_, y, x)) -> lastIdentBefore tokens docId (y, x)

  | NextIdent (Loc (_, y, x)) -> firstIdentAfter tokens docId (y, x)

/// Resolve locations.
let private resolveLoc (symbols: SymbolOccurrence list) pa =
  symbols
  |> List.choose
       (fun item ->
         let symbol, defOrUse, tyOpt, loc2 = item

         let locOpt =
           match loc2 with
           | At loc -> Some loc

           | PreviousIdent (Loc (docId, y, x)) ->
             let tokens = getTokenizeResult docId pa
             lastIdentBefore tokens docId (y, x)

           | NextIdent (Loc (docId, y, x)) ->
             let tokens = getTokenizeResult docId pa
             firstIdentAfter tokens docId (y, x)

         match locOpt with
         | Some loc -> Some(symbol, defOrUse, tyOpt, loc)
         | None -> None)

let private paGetTirSymbolsWithCache (pa: ProjectAnalysis) =
  match pa.BundleCache, pa.TirSymbolsCache with
  | _, Some it -> Some it, pa

  | Some b, _ ->
    let symbols = lowerTModules [] b.Program
    let pa = { pa with TirSymbolsCache = Some symbols }
    Some symbols, pa

  | _ -> None, pa

let private collectSymbolsInExpr (pa: ProjectAnalysis) (modules: TProgram) (tirCtx: TirCtx) =
  let parseModule (m: TModule) =
    let docId = m.DocId

    match pa |> getParseResult docId with
    | Some s -> LSyntax.toModuleSyntaxData s
    | None -> failwith "must be parsed"

  let variantNameMap =
    tirCtx.Variants
    |> TMap.fold
         (fun acc variantSerial (variantDef: VariantDef) ->
           let tySerial = variantDef.UnionTySerial
           let name = variantDef.Name
           let loc = variantDef.Loc
           let docId, _ = Loc.toDocPos loc

           acc
           |> TMap.add (name, tySerial, docId) (VariantSymbol variantSerial))
         (TMap.empty (T3.compare compare compare Symbol.compare))

  let fieldNameMap =
    tirCtx.Tys
    |> TMap.fold
         (fun acc tySerial tyDef ->
           match tyDef with
           | RecordTyDef (_, _, fields, _, loc) ->
             let docId, _ = Loc.toDocPos loc

             fields
             |> List.fold
                  (fun acc (ident, _, _) ->
                    acc
                    |> TMap.add (ident, tySerial, docId) (FieldSymbol(tySerial, ident)))
                  acc

           | _ -> acc)
         (TMap.empty (T3.compare compare compare Symbol.compare))

  let tyNameToDefs =
    tirCtx.Tys
    |> TMap.toList
    |> List.choose (fun (tySerial, tyDef) ->
      let name = tyDefToName tyDef

      let tySymbolOpt =
        match tyDef with
        | SynonymTyDef _ -> SynonymTySymbol tySerial |> Some
        | RecordTyDef _ -> RecordTySymbol tySerial |> Some
        | UnionTyDef _ -> UnionTySymbol tySerial |> Some
        | _ -> None

      match tySymbolOpt with
      | Some tySymbol -> Some(name, tySymbol)
      | None -> None)
    |> Multimap.ofList compare

  let findTyByName name =
    match tyNameToDefs |> Multimap.find name with
    | [ tySerial ] -> Some tySerial
    | _ -> None

  let docSymbols =
    modules
    |> List.fold
         (fun acc m ->
           let m = parseModule m
           lowerARoot (makeDoc1 m) acc m.Ast)
         []

  let tySymbols =
    docSymbols
    |> List.choose (fun (symbol, defOrUse, loc) ->
      match symbol, defOrUse with
      | DVariantSymbol (ident, unionIdent, defDoc), Def ->
        match findTyByName unionIdent with
        | Some (UnionTySymbol tySerial) ->
          match
            variantNameMap
            |> TMap.tryFind (ident, tySerial, defDoc)
            with
          | Some variantSymbol ->
            let tyOpt = None // FIXME: Compute type
            Some(ValueSymbol variantSymbol, Def, tyOpt, loc)

          | None -> None
        | _ -> None

      | DFieldSymbol (ident, recordIdent, defDoc), Def ->
        match findTyByName recordIdent with
        | Some (RecordTySymbol tySerial) ->
          match
            fieldNameMap
            |> TMap.tryFind (ident, tySerial, defDoc)
            with
          | Some fieldSymbol ->
            let tyOpt = None // FIXME: Compute type
            Some(fieldSymbol, Def, tyOpt, loc)

          | None -> None
        | _ -> None

      | DTySymbol name, _ ->
        match findTyByName name with
        | Some tySymbol -> Some(TySymbol tySymbol, defOrUse, None, loc)
        | _ -> None
      | _ -> None)

  let moduleSymbols =
    docSymbols
    |> List.choose (fun (symbol, defOrUse, loc) ->
      match symbol with
      | DModuleSymbol path -> Some(ModuleSymbol path, defOrUse, None, loc)
      | _ -> None)

  List.append tySymbols moduleSymbols
  |> up lowerTModules modules
  |> (fun acc -> resolveLoc acc pa)
  |> List.map (fun (symbol, defOrUse, _, loc) -> symbol, defOrUse, loc)

module Symbol =
  let name (b: BundleResult) (symbol: Symbol) =
    let modules = b.Program

    match b.TirCtxOpt with
    | Some tirCtx ->
      match symbol with
      | DiscardSymbol
      | PrimSymbol _ -> None // not implemented, completion need filter out

      | FieldSymbol _ -> None

      | ValueSymbol (VarSymbol varSerial) ->
        (match tirCtx.StaticVars |> TMap.tryFind varSerial with
         | Some t -> Some t
         | None ->
           modules
           |> List.tryPick (fun (m: TModule) -> m.Vars |> TMap.tryFind varSerial))
        |> Option.map (fun (t: VarDef) -> t.Name)

      | ValueSymbol (FunSymbol funSerial) ->
        tirCtx.Funs
        |> TMap.tryFind funSerial
        |> Option.map (fun (d: FunDef) -> d.Name)

      | ValueSymbol (VariantSymbol variantSerial) ->
        tirCtx.Variants
        |> TMap.tryFind variantSerial
        |> Option.map (fun (d: VariantDef) -> d.Name)

      | TySymbol tySymbol ->
        (match tySymbol with
         | UnivTySymbol _
         | SynonymTySymbol _ -> None
         | UnionTySymbol tySerial -> Some tySerial
         | RecordTySymbol tySerial -> Some tySerial)
        |> Option.bind (fun tySerial -> tirCtx.Tys |> TMap.tryFind tySerial)
        |> Option.bind (fun (d: TyDef) ->
          match d with
          | UnionTyDef (name, _, _, _) -> Some name
          | RecordTyDef (name, _, _, _, _) -> Some name
          | _ -> None)

      | ModuleSymbol _ // unimplemented
      | RecordOccurrence -> None
    | None -> None

// Provides fundamental operations as building block of queries.
module ProjectAnalysis1 =
  let create
    (entryDoc: DocId * ProjectName * ModuleName)
    (projectDir: ProjectDir)
    (projectName: ProjectName)
    (host: ProjectAnalysisHost)
    : ProjectAnalysis =
    { ProjectDir = projectDir
      ProjectName = projectName
      EntryDoc = entryDoc
      Db = SyntaxApi.SyntaxAnalysisDb.empty ()
      BundleCache = None
      TirSymbolsCache = None
      Host = host }

  let withHost (host: ProjectAnalysisHost) pa : ProjectAnalysis = { pa with Host = host }

  let getTokens (docId: DocId) (pa: ProjectAnalysis) : LTokenList = getTokenizeResult docId pa

  let getSyntax (docId: DocId) (pa: ProjectAnalysis) : LSyntaxData option = getParseResult docId pa

  let bundle (pa: ProjectAnalysis) : BundleResult * ProjectAnalysis = bundleWithCache pa

  let documentSymbols (s: LSyntaxData) (_pa: ProjectAnalysis) =
    lowerARoot (makeDoc s) [] s.Ast
    |> List.choose (fun (symbol, defOrUse, loc2) ->
      match defOrUse, resolveLoc2 s.DocId s.FullTokens loc2 with
      | Def, Some loc -> Some(symbol, defOrUse, loc)
      | _ -> None)

  // collect symbols from AST
  let collectSymbols (b: BundleResult) (pa: ProjectAnalysis) =
    match b.TirCtxOpt with
    | None -> None
    | Some tirCtx -> collectSymbolsInExpr pa b.Program tirCtx |> Some

  let getTyName (tokenLoc: Loc) (pa: ProjectAnalysis) =
    let symbolsOpt, pa = paGetTirSymbolsWithCache pa
    let symbols = Option.defaultValue [] symbolsOpt

    let resultOpt =
      resolveLoc symbols pa
      |> List.tryPick (fun (_, _, tyOpt, loc) ->
        match tyOpt with
        | Some ty when Loc.equals loc tokenLoc -> Some ty
        | _ -> None)
      |> Option.map TySystem.tyDisplay
      |> Some

    resultOpt, pa

// -----------------------------------------------
// Completion
// -----------------------------------------------

// Rough, incomplete implementation of completion feature.
module internal ProjectAnalysisCompletion =
  open MiloneLspServer.Util

  // #CompletionItemKind
  module private Kind =
    [<Literal>]
    let Text = 1

    [<Literal>]
    let Method = 2

    [<Literal>]
    let Function = 3

    [<Literal>]
    let Constructor = 4

    [<Literal>]
    let Field = 5

    [<Literal>]
    let Variable = 6

    [<Literal>]
    let Class = 7

    [<Literal>]
    let Interface = 8

    [<Literal>]
    let Module = 9

    [<Literal>]
    let Property = 10

    [<Literal>]
    let Unit = 11

    [<Literal>]
    let Value = 12

    [<Literal>]
    let Enum = 13

    [<Literal>]
    let Keyword = 14

    [<Literal>]
    let Snippet = 15

    [<Literal>]
    let Color = 16

    [<Literal>]
    let File = 17

    [<Literal>]
    let Reference = 18

    [<Literal>]
    let Folder = 19

    [<Literal>]
    let EnumMember = 20

    [<Literal>]
    let Constant = 21

    [<Literal>]
    let Struct = 22

    [<Literal>]
    let Event = 23

    [<Literal>]
    let Operator = 24

    [<Literal>]
    let TypeParameter = 25

  module private Range =
    let isTouched (pos: Pos) (range: Range) =
      let s, t = range
      Pos.compare s pos <= 0 && Pos.compare pos t <= 0

    let start ((s, _): Range) = s
    let endPos ((_, t): Range) = t

  module private SyntaxElement =
    let kind element =
      match element with
      | SyntaxToken (kind, _)
      | SyntaxNode (kind, _, _) -> kind

    let range element =
      match element with
      | SyntaxToken (_, range)
      | SyntaxNode (_, range, _) -> range

    let children element =
      match element with
      | SyntaxToken _ -> []
      | SyntaxNode (_, _, children) -> children

    let endPos element = element |> range |> Range.endPos

  let private isPatLike kind =
    match kind with
    | SyntaxKind.LiteralPat
    | SyntaxKind.WildcardPat
    | SyntaxKind.VarPat
    | SyntaxKind.PathPat
    | SyntaxKind.ParenPat
    | SyntaxKind.ListPat
    | SyntaxKind.WrapPat
    | SyntaxKind.ConsPat
    | SyntaxKind.AscribePat
    | SyntaxKind.TuplePat
    | SyntaxKind.AsPat
    | SyntaxKind.OrPat -> true
    | _ -> false

  let private findVarsInPat pat =
    let rec patRec acc pat =
      let acc =
        SyntaxElement.children pat |> List.fold patRec acc

      match SyntaxElement.kind pat with
      | SyntaxKind.VarPat
      | SyntaxKind.AsPat ->
        match pat
              |> SyntaxElement.children
              |> List.tryFind (fun node ->
                match SyntaxElement.kind node with
                | SyntaxKind.Ident -> true
                | _ -> false)
          with
        | Some it -> it :: acc
        | None -> acc

      | _ -> acc

    patRec [] pat

  let resolveUnqualifiedAsValue docId text ancestors qualIdent (targetPos: Pos) (pa: ProjectAnalysis) =
    let asIdent text node =
      match node with
      | SyntaxToken (SyntaxKind.Ident, identRange) -> Some(LineBuffer.stringBetween identRange text)
      | _ -> None

    let asModulePath node =
      match node with
      | SyntaxNode (SyntaxKind.ModulePath, _, children) -> Some children
      | _ -> None

    // finds all fields of record type declarations that are found
    // by going through open declarations transitively
    let collectFields (pa: ProjectAnalysis) =
      // checks if a node is record type declaration and if so, finds all field identifiers
      // if it's open or module synonym declaration, enqueues the opened module to be processed
      // otherwise just returns an empty list
      let foldOnNode text state node =
        let acc, docAcc, doneSet = state

        match SyntaxElement.kind node with
        | SyntaxKind.RecordTyDecl ->
          let fields =
            SyntaxElement.children node
            |> List.collect (fun node ->
              match SyntaxElement.kind node with
              | SyntaxKind.FieldDecl ->
                node
                |> SyntaxElement.children
                |> List.choose (asIdent text)
              | _ -> [])

          fields :: acc, docAcc, doneSet

        | SyntaxKind.ModuleSynonymDecl
        | SyntaxKind.OpenDecl ->
          match
            SyntaxElement.children node
            |> List.tryPick asModulePath
            |> Option.map (List.choose (asIdent text))
            with
          | Some [ p; m ] ->
            let docAcc, doneSet =
              let docId = pa.Host.ComputeDocId(p, m, docId)

              if doneSet |> TSet.contains docId |> not then
                docId :: docAcc, TSet.add docId doneSet
              else
                docAcc, doneSet

            acc, docAcc, doneSet

          | _ -> state
        | _ -> state

      let rec onDocRec acc docAcc doneSet =
        match docAcc with
        | [] -> acc

        | docId :: docAcc ->
          match getParseResult docId pa with
          | Some syntax ->
            let (SyntaxTree root) = syntax.SyntaxTree

            let acc, docAcc, doneSet =
              SyntaxElement.children root
              |> List.fold (foldOnNode syntax.LineBuffer) (acc, docAcc, doneSet)

            onDocRec acc docAcc doneSet

          | None -> onDocRec acc docAcc doneSet

      let acc =
        let docAcc = [ docId ]

        let doneSet =
          TSet.empty Symbol.compare |> TSet.add docId

        onDocRec [] docAcc doneSet

      acc
      |> List.rev
      |> List.collect id
      |> List.map (fun fieldIdent -> Kind.Field, fieldIdent)

    // finds all variables in a pattern
    let rec patRec acc pat =
      let acc =
        SyntaxElement.children pat |> List.fold patRec acc

      match SyntaxElement.kind pat with
      | SyntaxKind.VarPat
      | SyntaxKind.AsPat ->
        match pat
              |> SyntaxElement.children
              |> List.tryFind (fun node ->
                match SyntaxElement.kind node with
                | SyntaxKind.Ident -> true
                | _ -> false)
          with
        | Some ident -> ident :: acc
        | None -> acc

      | _ -> acc

    // checks if `nsIdent` is a name of variable
    let isVar =
      ancestors
      |> List.exists (fun ancestor ->
        ancestor
        |> SyntaxElement.children
        |> List.exists (fun node ->
          match SyntaxElement.kind node with
          | SyntaxKind.FunExpr
          | SyntaxKind.LetValExpr
          | SyntaxKind.LetFunExpr
          | SyntaxKind.LetValDecl
          | SyntaxKind.LetFunDecl ->
            SyntaxElement.children node
            |> List.exists (fun node ->
              isPatLike (SyntaxElement.kind node)
              && (patRec [] node
                  |> List.exists (fun ident ->
                    match asIdent text ident with
                    | Some ident -> ident = qualIdent
                    | None -> false)))

          | _ -> false))

    if isVar then
      List.append (collectFields pa) [ Kind.Property, "Length" ]
    else
      debugFn "not a variable: %s" qualIdent
      []

  // finds the sibling nodes before the dot and ancestral nodes.
  let private findQuals (tree: SyntaxTree) targetPos =
    let isPathLike kind =
      match kind with
      | SyntaxKind.NameTy
      | SyntaxKind.PathPat
      | SyntaxKind.PathExpr -> true
      | _ -> false

    let rec findRec pos ancestors node =
      let parentOpt = List.tryHead ancestors

      match node, parentOpt with
      // Cursor is at `.<|>` and parent is path
      | SyntaxToken (SyntaxKind.Dot, range), Some (SyntaxNode (parentKind, _, children)) when
        Pos.compare (Range.endPos range) pos = 0
        && isPathLike parentKind
        ->
        // siblings before position
        let left =
          children
          |> List.filter (fun child -> Pos.compare (SyntaxElement.endPos child) pos <= 0)

        (left, ancestors) |> Some

      | SyntaxToken _, _ -> None

      | SyntaxNode (_, range, children), _ ->
        if Range.isTouched pos range then
          children
          |> List.tryPick (fun child -> findRec pos (node :: ancestors) child)
        else
          None

    let (SyntaxTree root) = tree
    findRec targetPos [] root

  let private lastIdent text nodes =
    let asIdent node =
      match node with
      | SyntaxToken (SyntaxKind.Ident, identRange) -> Some(LineBuffer.stringBetween identRange text, Range.start identRange)
      | _ -> None

    let pickLast nodes =
      nodes |> List.rev |> List.tryPick asIdent

    nodes
    |> List.rev
    |> List.tryPick (fun node ->
      match node with
      | SyntaxNode (SyntaxKind.NameExpr, _, children) -> pickLast children
      | _ -> asIdent node)

  let resolveAsNs docId text ancestors (nsIdent: string) (targetPos: Pos) (pa: ProjectAnalysis) =
    debugFn "resolveAsNs nsIdent='%s'" nsIdent

    let asIdent text node =
      match node with
      | SyntaxToken (SyntaxKind.Ident, identRange) -> Some(LineBuffer.stringBetween identRange text)
      | _ -> None

    let asModulePath node =
      match node with
      | SyntaxNode (SyntaxKind.ModulePath, _, children) -> Some children
      | _ -> None

    let isDecl node =
      match node with
      | SyntaxNode (kind, _, _) ->
        match kind with
        | SyntaxKind.LetValDecl
        | SyntaxKind.LetFunDecl
        | SyntaxKind.TySynonymDecl
        | SyntaxKind.UnionTyDecl
        | SyntaxKind.RecordTyDecl
        | SyntaxKind.ModuleDecl
        | SyntaxKind.ModuleSynonymDecl -> true

        | _ -> false
      | _ -> false

    let findToplevelDecls docId (pa: ProjectAnalysis) =
      match getParseResult docId pa with
      | Some syntax ->
        let (SyntaxTree root) = syntax.SyntaxTree

        root
        |> SyntaxElement.children
        |> List.choose (fun node ->
          if isDecl node then
            Some(syntax, node)
          else
            None)

      | None ->
        warnFn "doc not parsed %s" (Symbol.toString docId)
        []

    // assume node is UnionTyDecl
    let collectVariants text (node: SyntaxElement) =
      node
      |> SyntaxElement.children
      |> List.choose (fun node ->
        match node with
        | SyntaxNode (SyntaxKind.VariantDecl, _, children) ->
          children
          |> List.tryPick (asIdent text)
          |> Option.map (fun name -> Kind.EnumMember, name)

        | _ -> None)

    // assumes node is the declaration that is exposed to the namespace
    let collectFromDecl text (node: SyntaxElement) =
      let children = SyntaxElement.children node

      match SyntaxElement.kind node with
      | SyntaxKind.LetValDecl ->
        match children
              |> List.tryFind (fun node -> isPatLike (SyntaxElement.kind node))
          with
        | Some pat ->
          let rec patRec acc pat =
            let acc =
              SyntaxElement.children pat |> List.fold patRec acc

            match SyntaxElement.kind pat with
            | SyntaxKind.VarPat
            | SyntaxKind.AsPat ->
              match
                pat |> SyntaxElement.children
                |> List.tryPick (asIdent text)
                with
              | Some name -> (Kind.Value, name) :: acc
              | None -> acc

            | _ -> acc

          patRec [] pat

        | None -> []

      | SyntaxKind.LetFunDecl
      | SyntaxKind.TySynonymDecl
      | SyntaxKind.RecordTyDecl
      | SyntaxKind.ModuleDecl ->
        let kind =
          match SyntaxElement.kind node with
          | SyntaxKind.LetFunDecl -> Kind.Function
          | SyntaxKind.ModuleDecl -> Kind.Module
          | _ -> Kind.Class

        node
        |> SyntaxElement.children
        |> List.tryPick (asIdent text)
        |> Option.map (fun name -> kind, name)
        |> Option.toList

      | SyntaxKind.UnionTyDecl ->
        let nameOpt =
          children
          |> List.tryPick (asIdent text)
          |> Option.map (fun name -> Kind.Enum, name)

        let variants = collectVariants text node

        List.append (Option.toList nameOpt) variants

      | _ -> []

    // checks if node has the specified name and collects items for completion
    let collectContents text (node: SyntaxElement) =
      match node with
      | SyntaxNode (SyntaxKind.UnionTyDecl, _, children) ->
        let ok =
          match children |> List.tryPick (asIdent text) with
          | Some ident -> ident = nsIdent
          | None -> false

        if ok then
          collectVariants text node
        else
          []

      | SyntaxNode (SyntaxKind.ModuleDecl, _, children) ->
        let ok =
          match children |> List.tryPick (asIdent text) with
          | Some ident -> ident = nsIdent
          | None -> false

        if ok then
          children |> List.collect (collectFromDecl text)
        else
          []

      | _ -> []

    let rec collectViaOpenDecls docId text node (pa: ProjectAnalysis) =
      match node with
      | SyntaxNode (SyntaxKind.ModuleSynonymDecl, _, children) ->
        let ok =
          match children |> List.tryPick (asIdent text) with
          | Some ident -> ident = nsIdent
          | None -> false

        if ok then
          match
            children |> List.tryPick asModulePath
            |> Option.map (List.choose (asIdent text))
            with
          | Some [ p; m ] ->
            let docId: DocId = pa.Host.ComputeDocId(p, m, docId)

            findToplevelDecls docId pa
            |> List.collect (fun (syntax, decl) -> collectFromDecl syntax.LineBuffer decl)

          | _ -> []
        else
          []

      | SyntaxNode (SyntaxKind.OpenDecl, _, children) ->
        match
          children |> List.tryPick asModulePath
          |> Option.map (List.choose (asIdent text))
          with
        | Some [ p; m ] ->
          let docId = pa.Host.ComputeDocId(p, m, docId)

          findToplevelDecls docId pa
          |> List.collect (fun ((syntax: LSyntax), decl) -> collectContents syntax.LineBuffer decl)

        | _ -> []

      | _ -> collectContents text node

    let resolveUnqualifiedAsNs docId (targetPos: Pos) (pa: ProjectAnalysis) =
      ancestors
      |> List.collect (fun ancestor ->
        let isBeforeTarget node =
          Pos.compare (SyntaxElement.endPos node) targetPos
          <= 0

        ancestor
        |> SyntaxElement.children
        |> List.collect (fun child ->
          if isBeforeTarget child then
            collectViaOpenDecls docId text child pa
          else
            []))

    let resolvePrelude () =
      if SyntaxApi.isKnownModule nsIdent then
        let docId: DocId = pa.Host.GetCoreDocId nsIdent

        findToplevelDecls docId pa
        |> List.collect (fun (syntax, decl) -> collectFromDecl syntax.LineBuffer decl)
      else
        []

    List.append (resolveUnqualifiedAsNs docId targetPos pa) (resolvePrelude ())

  let tryNsCompletion (docId: DocId) (targetPos: Pos) pa : (int * string) list option * ProjectAnalysis =
    let syntaxOpt = getParseResult docId pa

    match syntaxOpt with
    | Some syntax ->
      let text = syntax.LineBuffer
      let tree = syntax.SyntaxTree

      match findQuals tree targetPos with
      | None ->
        // debugFn "no quals"
        None, pa

      | Some (quals, ancestors) ->
        // debugFn "quals=%A" quals

        match lastIdent text quals with
        | None ->
          // debugFn "no ident"
          None, pa

        | Some (qualIdent, qualPos) ->
          // ignore non-last qualifiers for now

          // ensure depended files are parsed
          let pa =
            if pa.BundleCache |> Option.isNone then
              ProjectAnalysis1.bundle pa |> snd
            else
              pa

          match resolveAsNs docId text ancestors qualIdent qualPos pa with
          | [] ->
            // debugFn "no members in %s" qualIdent

            match resolveUnqualifiedAsValue docId text ancestors qualIdent qualPos pa with
            | [] -> None, pa

            | items -> Some items, pa

          | items -> Some items, pa

    | None ->
      // debugFn "no syntax2"
      None, pa

  let private findAncestorsAt (targetPos: Pos) (tree: SyntaxTree) =
    let rec findRec ancestors node =
      match node with
      | SyntaxToken (_, range) when Range.isTouched targetPos range -> [ancestors]

      | SyntaxToken _ -> []

      | SyntaxNode (_, range, children) ->
        if Range.isTouched targetPos range then
          children
          |> List.collect (findRec (node :: ancestors))
        else
          []

    let (SyntaxTree root) = tree
    findRec [] root

  /// Attempts generate completion items in record expressions.
  let tryRecordCompletion (docId: DocId) (targetPos: Pos) pa : (int * string) list option * ProjectAnalysis =
    let tryFindParentRecordExprNode tree : Range option =
      findAncestorsAt targetPos tree
      |> List.tryPick (fun ancestors ->
        ancestors
        |> List.tryFind (fun node ->
          match SyntaxElement.kind node with
          | SyntaxKind.RecordExpr -> true
          | _ -> false))
      |> Option.map SyntaxElement.range

    // performs syntactic analysis and checks if whether record completion is applicable.
    let tryDetectRecordRange pa =
      let syntaxOpt = getParseResult docId pa

      match syntaxOpt with
      | Some syntax ->
        let tree = syntax.SyntaxTree
        let recordRangeOpt = tryFindParentRecordExprNode tree
        recordRangeOpt, pa

      | None -> None, pa

    let computeTypeInfo pa =
      let bundleResult, pa = ProjectAnalysis1.bundle pa
      let symbolsOpt, pa = paGetTirSymbolsWithCache pa

      let tysAndSymbolsOpt =
        match bundleResult.TirCtxOpt, symbolsOpt with
        | Some tirCtx, Some symbols -> Some(tirCtx.Tys, symbols)
        | _ -> None

      tysAndSymbolsOpt, pa

    let findRecordTySerialFromRange recordRange symbols =
      let toLoc loc2 =
        match loc2 with
        | At loc -> loc
        | PreviousIdent loc -> loc
        | NextIdent loc -> loc

      symbols
      |> List.tryPick (fun (symbol, _, tyOpt, loc2) ->
        let loc = toLoc loc2

        match symbol, tyOpt with
        | RecordOccurrence, Some(Ty(RecordTk(tySerial, _), _)) when Symbol.equals docId (Loc.docId loc) ->
          let _, pos = Loc.toDocPos loc

          if Range.isTouched pos recordRange then
            Some tySerial
          else
            None

        | FieldSymbol(tySerial, ident), _ when Symbol.equals docId (Loc.docId loc) ->
          let _, pos = Loc.toDocPos loc

          if Range.isTouched pos recordRange then
            Some tySerial
          else
            None
        | _ -> None)

    let findFieldsOfRecordTy tys tySerialOpt =
      match tySerialOpt with
      | Some tySerial ->
        match tys |> TMap.tryFind tySerial with
        | Some(RecordTyDef(_, _, fields, _, _)) -> fields |> List.map (fun (ident, _, _) -> ident) |> Some

        | _ -> None
      | _ -> None

    let newFieldItem (ident: string) = Kind.Field, ident

    match tryDetectRecordRange pa with
    | Some recordRange, pa ->
      match computeTypeInfo pa with
      | Some(tys, symbols), pa ->
        let tySerialOpt = findRecordTySerialFromRange recordRange symbols
        let fieldsOpt = findFieldsOfRecordTy tys tySerialOpt
        let itemsOpt = Option.map (List.map newFieldItem) fieldsOpt
        itemsOpt, pa

      | None, pa -> None, pa
    | None, pa -> None, pa
