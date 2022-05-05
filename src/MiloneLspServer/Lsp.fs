/// Module for LSP to talk directly to MiloneLang compiler.
module rec MiloneLspServer.Lsp

open MiloneLspServer.LspUtil
open MiloneShared.SharedTypes
open MiloneShared.UtilParallel
open MiloneShared.UtilSymbol
open MiloneSyntax.Syntax
open MiloneSyntax.Tir
open MiloneSyntaxTypes.SyntaxApiTypes
open MiloneSyntaxTypes.SyntaxTypes
open MiloneSyntaxTypes.TirTypes
open Std.StdMap
open Std.StdSet

module C = Std.StdChar
module S = Std.StdString
module AstBundle = MiloneSyntax.AstBundle
module SyntaxApi = MiloneSyntax.SyntaxApi
module SyntaxTokenize = MiloneSyntax.SyntaxTokenize
module TySystem = MiloneSyntax.TySystem

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

  let empty = LTokenList []

  let tryLast (LTokenList tokens) =
    tokens |> List.tryLast |> Option.map LToken

  let tokenizeAll text =
    SyntaxTokenize.tokenizeAll host text |> LTokenList

  let findAt (pos: Pos) (LTokenList tokens) : LToken option =
    match findTokenAt tokens pos with
    | Some (token, pos) -> Some(LToken(token, pos))
    | None -> None

  let findAdjacent (pos: Pos) (LTokenList tokens) : LToken list =
    findTokensAt tokens pos |> List.map LToken

  let resolveRanges (posList: Pos list) (LTokenList tokens) : Range list = resolveTokenRanges tokens posList

  let toList (LTokenList tokens) = tokens |> List.map LToken

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

  let findModuleDefs (s: LSyntaxData) : string list =
    let (LSyntaxData (docId, _, ast, _)) = s

    lowerARoot docId [] ast
    |> List.choose (fun (symbol, defOrUse, _) ->
      match symbol, defOrUse with
      | DModuleSymbol ([ name ]), Def -> Some name
      | _ -> None)

  let findModuleSynonyms (s: LSyntaxData) : (string * ModulePath * Loc) list =
    let (LSyntaxData (docId, tokens, ast, _)) = s

    lowerARoot docId [] ast
    |> List.choose (fun (symbol, _, loc2) ->
      match symbol, resolveLoc2 docId tokens loc2 with
      | DModuleSynonymDef (synonym, modulePath), Some loc -> Some(synonym, modulePath, loc)
      | _ -> None)

module BundleResult =
  let getErrors (b: BundleResult) = b.Errors

// -----------------------------------------------
// Project-wise analysis
// -----------------------------------------------

/// Operations for project analysis.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ProjectAnalysisHost =
  { GetDocVersion: DocId -> DocVersion
    Tokenize: DocId -> DocVersion * LTokenList
    Parse: DocId -> (DocVersion * LSyntaxData) option

    MiloneHome: FilePath
    ReadTextFile: string -> Future<string option> }

/// State of project analysis.
[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ProjectAnalysis =
  private
    { ProjectDir: ProjectDir
      ProjectName: ProjectName
      NewTokenizeCache: TreeMap<DocId, LTokenList>
      NewParseResults: (DocVersion * LSyntaxData) list
      BundleCache: BundleResult option
      Host: ProjectAnalysisHost }

let private emptyTokenizeCache: TreeMap<DocId, LTokenList> = TMap.empty Symbol.compare

let private getVersion docId (pa: ProjectAnalysis) = pa.Host.GetDocVersion docId

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
      Errors: (string * Loc) list
      DocVersions: (DocId * DocVersion) list
      ParseResults: (DocVersion * LSyntaxData) list }

let private doBundle (pa: ProjectAnalysis) : BundleResult =
  let projectDir = pa.ProjectDir
  let projectName = pa.ProjectName
  let miloneHome = pa.Host.MiloneHome

  let fetchModuleUsingCache _ (projectName: string) (moduleName: string) =
    let docId =
      AstBundle.computeDocId projectName moduleName

    match pa |> parseWithCache docId with
    | None -> Future.just None
    | Some (LSyntaxData syntaxData) -> Future.just (Some syntaxData)

  let syntaxCtx =
    let host: FetchModuleHost =
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
  | SyntaxAnalysisOk (modules, tirCtx) ->
    { ProgramOpt = Some(modules, tirCtx)
      Errors = []
      DocVersions = docVersions
      ParseResults = parseResults }

  | SyntaxAnalysisError (errors, tirCtxOpt) ->
    { ProgramOpt =
        match tirCtxOpt with
        | Some tirCtx -> Some([], tirCtx)
        | None -> None

      Errors = errors
      DocVersions = docVersions
      ParseResults = parseResults }

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

    let result = doBundle pa

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
          BundleCache = Some result }

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

type private SymbolOccurrence = Symbol * DefOrUse * Ty option * Loc2

let private lowerATy docId acc ty : DSymbolOccurrence list =
  let onTy acc ty = lowerATy docId acc ty
  let onTys acc tys = tys |> List.fold onTy acc

  match ty with
  | AMissingTy _
  | AVarTy _ -> acc

  | AAppTy (_, Name (name, pos), tyArgs, _) ->
    let acc =
      (DTySymbol name, Use, At(Loc.ofDocPos docId pos))
      :: acc

    onTys acc tyArgs

  | ASuffixTy (bodyTy, _) -> onTy acc bodyTy
  | ATupleTy (itemTys, _) -> itemTys |> List.fold onTy acc
  | AFunTy (l, r, _) -> acc |> up onTy l |> up onTy r

let private lowerAPat docId acc pat : DSymbolOccurrence list =
  let onTy acc ty = lowerATy docId acc ty
  let onPat acc pat = lowerAPat docId acc pat
  let onPats acc pats = pats |> List.fold onPat acc
  let toLoc (y, x) = At(Loc(docId, y, x))

  match pat with
  | AMissingPat _
  | ALitPat _
  | AIdentPat _ -> acc

  | AListPat (itemPats, _) -> acc |> up onPats itemPats
  | ANavPat (l, _, _) -> acc |> up onPat l

  | AAppPat (l, r, _)
  | AConsPat (l, r, _) -> acc |> up onPat l |> up onPat r

  | ATuplePat (itemPats, _) -> acc |> up onPats itemPats
  | AAsPat (bodyPat, _, _) -> acc |> up onPat bodyPat
  | AAscribePat (l, r, _) -> acc |> up onPat l |> up onTy r
  | AOrPat (l, r, _) -> acc |> up onPat l |> up onPat r

let private lowerALetContents docId acc contents =
  let onTy acc ty = lowerATy docId acc ty
  let onPat acc pat = lowerAPat docId acc pat
  let onPats acc pats = pats |> List.fold onPat acc
  let onExpr acc expr = lowerAExpr docId acc expr
  let toLoc (y, x) = At(Loc(docId, y, x))

  match contents with
  | ALetContents.LetFun (_, _, name, argPats, resultTyOpt, body) ->
    let (Name (name, pos)) = name
    let acc = (DFunSymbol name, Def, toLoc pos) :: acc

    let acc =
      acc |> upOpt onTy (resultTyOpt |> Option.map fst)

    acc |> up onPats argPats |> up onExpr body

  | ALetContents.LetVal (_, pat, init) -> acc |> up onPat pat |> up onExpr init

let private lowerAExpr docId acc expr : DSymbolOccurrence list =
  let onTy acc ty = lowerATy docId acc ty
  let onPat acc pat = lowerAPat docId acc pat
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

  | AFunExpr (argPats, body, pos) ->
    ((DFunSymbol "<fun>", Def, toLoc pos) :: acc)
    |> upList onPat argPats
    |> up onExpr body

  | ANavExpr (l, _, _) ->
    match l with
    | AIdentExpr (Name (l, pos), []) when l.Length = 1 && C.isUpper l.[0] ->
      (DModuleSymbol [ Symbol.toString docId
                       l ],
       Use,
       toLoc pos)
      :: acc

    | ANavExpr (AIdentExpr (p, []), m, _) ->
      let path = [ p; m ] |> List.map nameToIdent

      if isModulePathLike path then
        (DModuleSymbol path, Use, toLoc (nameToPos m))
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

  | AAscribeExpr (l, r, _) -> acc |> up onExpr l |> up onTy r
  | ASemiExpr (stmts, last, _) -> acc |> up onExprs stmts |> up onExpr last

  | ALetExpr (contents, next, _) ->
    let acc = lowerALetContents docId acc contents
    lowerAExpr docId acc next

let private lowerADecl docId acc decl : DSymbolOccurrence list =
  let onTy acc ty = lowerATy docId acc ty
  let onPat acc pat = lowerAPat docId acc pat
  let onExpr acc expr = lowerAExpr docId acc expr
  let onDecl acc decl = lowerADecl docId acc decl
  let toLoc (y, x) = At(Loc(docId, y, x))

  match decl with
  | AExprDecl expr -> onExpr acc expr

  | ALetDecl (contents, _) -> lowerALetContents docId acc contents

  | ATySynonymDecl (_, name, _, _, _) ->
    let (Name (name, pos)) = name
    (DTySymbol name, Def, toLoc pos) :: acc

  | AUnionTyDecl (_, name, _, variants, _) ->
    let (Name (unionIdent, pos)) = name

    let acc =
      variants
      |> List.fold
           (fun acc (AVariant (name, _, _)) ->
             let (Name (ident, pos)) = name

             (DVariantSymbol(ident, unionIdent, docId), Def, toLoc pos)
             :: acc)
           acc

    (DTySymbol unionIdent, Def, toLoc pos) :: acc

  | ARecordTyDecl (_, name, _, fields, _) ->
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

  | AOpenDecl (path, pos) ->
    let pos = path |> pathToPos pos

    (DOpenUse(path |> List.map nameToIdent), Use, toLoc pos)
    :: (DModuleSymbol(path |> List.map nameToIdent), Use, toLoc pos)
       :: acc

  | AModuleSynonymDecl (Name (synonym, identPos), path, pos) ->
    let acc =
      (DModuleSymbol [ Symbol.toString docId
                       synonym ],
       Def,
       toLoc identPos)
      :: acc

    let pos = path |> pathToPos pos
    let path = path |> List.map nameToIdent

    (DModuleSynonymDef(synonym, path), Use, toLoc pos)
    :: (DModuleSymbol path, Use, toLoc pos) :: acc

  | AModuleDecl (_, _, Name (name, pos), decls, _) ->
    let acc =
      (DModuleSymbol [ name ], Def, toLoc pos) :: acc

    acc |> up (List.fold onDecl) decls

  | AAttrDecl (_, next, _) -> lowerADecl docId acc next

let private lowerARoot (docId: DocId) acc root : DSymbolOccurrence list =
  let toLoc (y, x) = At(Loc(docId, y, x))
  let (ARoot (headOpt, decls)) = root

  let pos: Pos =
    match headOpt with
    | Some (_, pos) -> pos
    | _ -> 0, 0

  let acc =
    // #abusingDocId
    let path = Symbol.toString docId |> S.split "."
    (DModuleSymbol path, Def, toLoc pos) :: acc

  acc |> up (List.fold (lowerADecl docId)) decls

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

  | TBlockExpr (stmts, last) ->
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
  |> List.mapFold
       (fun (pa: ProjectAnalysis) item ->
         let symbol, defOrUse, tyOpt, loc2 = item

         let locOpt, pa =
           match loc2 with
           | At loc -> Some loc, pa

           | PreviousIdent (Loc (docId, y, x)) ->
             let tokens, pa = tokenizeWithCache docId pa
             lastIdentBefore tokens docId (y, x), pa

           | NextIdent (Loc (docId, y, x)) ->
             let tokens, pa = tokenizeWithCache docId pa
             firstIdentAfter tokens docId (y, x), pa

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
    | Some ty when Loc.equals loc tokenLoc -> Some ty
    | _ -> None)

let private collectSymbolsInExpr (pa: ProjectAnalysis) (modules: TProgram) (tirCtx: TirCtx) =
  let parseModule (m: TModule) =
    let docId = m.DocId

    match pa |> parseWithCache docId with
    | Some (LSyntaxData (_, _, ast, _)) -> docId, ast
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
           let docId, ast = parseModule m
           lowerARoot docId acc ast)
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
    match b.ProgramOpt with
    | Some (modules, tirCtx) ->
      match symbol with
      | DiscardSymbol _
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

      | ModuleSymbol (_) -> None // unimplemented
    | None -> None

// Provides fundamental operations as building block of queries.
module ProjectAnalysis1 =
  let create (projectDir: ProjectDir) (projectName: ProjectName) (host: ProjectAnalysisHost) : ProjectAnalysis =
    { ProjectDir = projectDir
      ProjectName = projectName
      NewTokenizeCache = emptyTokenizeCache
      NewParseResults = []
      BundleCache = None
      Host = host }

  let withHost (host: ProjectAnalysisHost) pa : ProjectAnalysis = { pa with Host = host }

  let drain (pa: ProjectAnalysis) =
    pa.NewTokenizeCache,
    pa.NewParseResults,
    { pa with
        NewTokenizeCache = emptyTokenizeCache
        NewParseResults = [] }

  let tokenize (docId: DocId) (pa: ProjectAnalysis) : LTokenList * ProjectAnalysis =
    let tokens, pa = tokenizeWithCache docId pa
    LTokenList tokens, pa

  let parse (docId: DocId) (pa: ProjectAnalysis) : LSyntaxData option * ProjectAnalysis = parseWithCache docId pa, pa

  let bundle (pa: ProjectAnalysis) : BundleResult * ProjectAnalysis = bundleWithCache pa

  let documentSymbols (syntax: LSyntaxData) (_pa: ProjectAnalysis) =
    let (LSyntaxData (docId, tokens, ast, _)) = syntax

    lowerARoot docId [] ast
    |> List.choose (fun (symbol, defOrUse, loc2) ->
      match defOrUse, resolveLoc2 docId tokens loc2 with
      | Def, Some loc -> Some(symbol, defOrUse, loc)
      | _ -> None)

  let collectSymbols (b: BundleResult) (pa: ProjectAnalysis) =
    match b.ProgramOpt with
    | None -> None
    | Some (modules, tirCtx) -> collectSymbolsInExpr pa modules tirCtx |> Some

  let getTyName (b: BundleResult) (tokenLoc: Loc) (pa: ProjectAnalysis) =
    match b.ProgramOpt with
    | None -> None
    | Some (modules, tirCtx) ->
      match findTyInStmt pa modules tokenLoc with
      | None -> Some None
      | Some ty -> tyDisplayFn tirCtx ty |> Some |> Some
