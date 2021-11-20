/// Module for LSP to talk directly to MiloneLang compiler.
module rec MiloneLspServer.Lsp

open MiloneShared.SharedTypes
open MiloneShared.UtilParallel
open MiloneStd.StdMap
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

  // FIXME: too specific

  let asIdent (LToken (token, _)) =
    match token with
    | IdentToken name -> Some name
    | _ -> None

  let isDot (LToken (token, _)) =
    match token with
    | DotToken -> true
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

module BundleResult =
  let getErrors (b: BundleResult) = b.Errors

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

let private bundleWithCache (pa: ProjectAnalysis) : BundleResult * ProjectAnalysis =
  let docsAreAllFresh docVersions =
    docVersions
    |> List.forall (fun (docId, version) -> getVersion docId pa <= version)

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

module Symbol =
  let name (b: BundleResult) (symbol: Symbol) =
    match b.ProgramOpt with
    | Some (modules, tirCtx) ->
      match symbol with
      | DiscardSymbol _
      | PrimSymbol _ -> None // not implemented, completion need filter out

      | FieldSymbol _ -> None

      | ValueSymbol (VarSymbol varSerial) ->
        (match tirCtx.Vars |> TMap.tryFind varSerial with
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
         | MetaTySymbol _
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
// FIXME: name?
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

  let bundle (pa: ProjectAnalysis) : BundleResult * ProjectAnalysis = bundleWithCache pa

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
