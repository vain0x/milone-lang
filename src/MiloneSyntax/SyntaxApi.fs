/// # SyntaxApi
///
/// Exposed API of the project.
module rec MiloneSyntax.SyntaxApi

open MiloneShared.SharedTypes
open MiloneShared.UtilParallel
open MiloneShared.Util
open Std.StdError
open Std.StdMap
open MiloneSyntax.Syntax
open MiloneSyntaxTypes.SyntaxTypes
open MiloneSyntaxTypes.SyntaxApiTypes

module ArityCheck = MiloneSyntax.ArityCheck
module OwnershipCheck = MiloneSyntax.OwnershipCheck
module NameRes = MiloneSyntax.NameRes
module Manifest = MiloneSyntax.Manifest
module NirGen = MiloneSyntax.NirGen
module S = Std.StdString
module SyntaxParse = MiloneSyntax.SyntaxParse
module SyntaxTokenize = MiloneSyntax.SyntaxTokenize
module SyntaxTreeGen = MiloneSyntax.SyntaxTreeGen
module Tir = MiloneSyntax.Tir
module Typing = MiloneSyntax.Typing
module TySystem = MiloneSyntax.TySystem
module TirTypes = MiloneSyntaxTypes.TirTypes

/// `.fs` or `.milone`.
type private SourceExt = string

/// File extension. Starts with `.`.
type private FileExt = string

type private FileExistsFun = string -> bool

let private changeExt (ext: FileExt) (path: string) : string =
  assert (ext |> S.startsWith "." && ext <> ".")

  let dirname, basename =
    match path |> S.cutLast "/" with
    | dirname, basename, true -> dirname + "/", basename
    | s, _, _ -> "", s

  let stem =
    let s = basename

    match s |> S.findIndex "." with
    | Some i when 0 < i && i < s.Length -> S.truncate i s
    | _ -> s

  dirname + stem + ext

// -----------------------------------------------
// Std library
// -----------------------------------------------

let private getStdLibNames () = [ "MiloneCore"; "Std" ]

let private computeStdLibProjectDir (miloneHome: MiloneHome) (projectName: ProjectName) : ProjectDir =
  miloneHome + "/src/" + projectName

let getStdLibProjects (miloneHome: MiloneHome) : (ProjectName * ProjectDir) list =
  getStdLibNames ()
  |> List.map (fun name -> name, computeStdLibProjectDir miloneHome name)

// -----------------------------------------------
// Prelude resolution
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type ModuleKind =
  | MiloneCore
  | Regular

let getModuleKind projectName (_: ModuleName) =
  match projectName with
  | "MiloneCore" -> ModuleKind.MiloneCore
  | _ -> ModuleKind.Regular

let private preludeFuns = [ "ignore"; "id"; "fst"; "snd" ]
let private optionIdents = [ "option"; "None"; "Some" ]
let private resultIdents = [ "Result"; "Ok"; "Error" ]

let private knownModules =
  [ "List"
    "Option"
    "Prelude"
    "Result"
    "String" ]

let private isPreludeFun funName =
  preludeFuns
  |> List.exists (fun name -> name = funName)

let private isOptionIdent ident =
  optionIdents |> List.exists (fun x -> x = ident)

let private isResultIdent ident =
  resultIdents |> List.exists (fun x -> x = ident)

let private isKnownModule moduleName =
  knownModules
  |> List.exists (fun name -> name = moduleName)

/// Generates decls for each MiloneCore module
/// whose name appears in the token stream.
let private resolveMiloneCoreDeps kind tokens ast =
  let analyze tokens =
    let rec go preludeOpt optionOpt resultOpt acc tokens =
      match tokens with
      | [] -> preludeOpt, optionOpt, resultOpt, acc

      | (IdentToken name, pos) :: tokens when Option.isNone preludeOpt && isPreludeFun name ->
        go (Some pos) optionOpt resultOpt acc tokens

      | (IdentToken name, pos) :: tokens when Option.isNone optionOpt && isOptionIdent name ->
        go preludeOpt (Some pos) resultOpt acc tokens

      | (IdentToken name, pos) :: tokens when Option.isNone resultOpt && isResultIdent name ->
        go preludeOpt optionOpt (Some pos) acc tokens

      | (IdentToken moduleName, pos) :: (DotToken, _) :: tokens ->
        go preludeOpt optionOpt resultOpt ((moduleName, pos) :: acc) tokens

      | _ :: tokens -> go preludeOpt optionOpt resultOpt acc tokens

    let preludeOpt, optionOpt, resultOpt, moduleNames = go None None None [] tokens

    let add acc (moduleName, pos) =
      if (acc |> TMap.containsKey moduleName |> not)
         && isKnownModule moduleName then
        acc |> TMap.add moduleName pos
      else
        acc

    let moduleMap =
      moduleNames |> List.fold add (TMap.empty compare)

    preludeOpt, optionOpt, resultOpt, moduleMap

  let insertOpenDecls decls =
    let preludeOpt, optionOpt, resultOpt, moduleMap = analyze tokens

    let decls =
      moduleMap
      |> TMap.fold
           (fun decls moduleName pos ->
             AModuleSynonymDecl(
               pos,
               Name(moduleName, pos),
               pos,
               [ Name("MiloneCore", pos)
                 Name(moduleName, pos) ]
             )
             :: decls)
           decls

    let decls =
      match preludeOpt with
      | Some pos ->
        AOpenDecl(
          pos,
          [ Name("MiloneCore", pos)
            Name("Prelude", pos) ]
        )
        :: decls
      | None -> decls

    let decls =
      match optionOpt with
      | Some pos ->
        AOpenDecl(
          pos,
          [ Name("MiloneCore", pos)
            Name("Option", pos) ]
        )
        :: decls
      | None -> decls

    match resultOpt with
    | Some pos ->
      AOpenDecl(
        pos,
        [ Name("MiloneCore", pos)
          Name("Result", pos) ]
      )
      :: decls
    | None -> decls

  let updateAst ast =
    let (ARoot (headOpt, decls)) = ast
    ARoot(headOpt, insertOpenDecls decls)

  match kind with
  | ModuleKind.MiloneCore -> ast
  | _ -> updateAst ast

// -----------------------------------------------
// Misc
// -----------------------------------------------

let getMiloneHomeFromEnv (getMiloneHomeEnv: unit -> string option) (getHomeEnv: unit -> string option) : MiloneHome =
  match getMiloneHomeEnv () with
  | Some miloneHome ->
    assert (miloneHome <> "")
    miloneHome

  | None ->
    match getHomeEnv () with
    | Some home -> home + "/.local/share/milone"
    | None -> failwith "$MILONE_HOME and $HOME are missing."

/// Computes preferred filename of source file.
let chooseSourceExt (fileExists: FileExistsFun) filename =
  let fs = changeExt ".fs" filename

  if fileExists filename || not (fileExists fs) then
    filename
  else
    fs

// #readSourceFile
let readSourceFile (readTextFile: ReadTextFileFun) filename : Future<string option> =
  readTextFile filename
  |> Future.andThen (fun result ->
    match result with
    | (Some _) as it -> Future.just it
    | None -> readTextFile (changeExt ".fs" filename))

let parseModule (docId: DocId) (kind: ModuleKind) (tokens: TokenizeResult) : ModuleSyntaxData =
  let errorTokens, tokens = tokens |> List.partition isErrorToken

  let ast, parseErrors = tokens |> SyntaxParse.parse

  let errors =
    List.append (tokenizeErrors errorTokens) parseErrors

  let ast =
    if errors |> List.isEmpty then
      resolveMiloneCoreDeps kind tokens ast
    else
      ast

  docId, tokens, ast, errors

let parse1 host beingCore sourceCode : ARoot * ModuleSyntaxError list =
  let kind =
    if beingCore then
      ModuleKind.MiloneCore
    else
      ModuleKind.Regular

  let tokens = SyntaxTokenize.tokenize host sourceCode
  let errorTokens, tokens = tokens |> List.partition isErrorToken

  let ast, parseErrors = SyntaxParse.parse tokens

  let errors =
    List.append (tokenizeErrors errorTokens) parseErrors

  let ast =
    if errors |> List.isEmpty then
      resolveMiloneCoreDeps kind tokens ast
    else
      ast

  ast, errors

// -----------------------------------------------
// Error processing
// -----------------------------------------------

type private SyntaxError = string * Loc

let private isErrorToken token =
  match token with
  | ErrorToken _, _ -> true
  | _ -> false

let private tokenizeErrors errorTokens =
  errorTokens
  |> List.map (fun token ->
    match token with
    | ErrorToken error, pos -> tokenizeErrorToString error, pos
    | _ -> unreachable ())

let private collectNameResErrors logs : SyntaxError list option =
  if List.isEmpty logs then
    None
  else
    logs
    |> List.map (fun (log, loc) -> Tir.nameResLogToString log, loc)
    |> Some

let private collectTypingErrors (tirCtx: TirTypes.TirCtx) : SyntaxError list option =
  let logs = tirCtx.Logs

  if List.isEmpty logs then
    None
  else
    let tyDisplayFn ty =
      let getTyName tySerial =
        tirCtx.Tys
        |> TMap.tryFind tySerial
        |> Option.map Tir.tyDefToName

      TySystem.tyDisplay getTyName ty

    logs
    |> List.map (fun (log, loc) -> Tir.logToString tyDisplayFn log, loc)
    |> Some

let syntaxErrorsToString (errors: SyntaxError list) : string =
  errors
  |> listSort (fun (_, l) (_, r) -> Loc.compare l r)
  |> List.map (fun (msg, loc) -> "#error " + Loc.toString loc + " " + msg + "\n")
  |> S.concat ""

// -----------------------------------------------
// Analysis
// -----------------------------------------------

/// Creates an NIR and collects errors
/// by loading source files and processing.
let performSyntaxAnalysis (writeLog: WriteLogFun) (layers: SyntaxLayers) : SyntaxAnalysisResult =
  writeLog "NirGen"

  let nirLayers =
    layers
    |> __parallelMap (fun modules ->
      modules
      |> __parallelMap (fun (m: ModuleSyntaxData2) ->
        let nir, logs =
          NirGen.genNir m.ProjectName m.ModuleName m.DocId m.Ast

        m.DocId, nir, logs))

  let errors =
    nirLayers
    |> List.collect (
      List.collect (fun (_, _, logs) ->
        logs
        |> List.map (fun (log, loc) -> NirGen.nirGenLogToString log, loc))
    )

  if errors |> List.isEmpty |> not then
    SyntaxAnalysisError(errors, None)
  else
    writeLog "NameRes"

    let modules, nameResResult =
      let modules: NModuleRoot list list =
        nirLayers
        |> List.map (fun layer ->
          layer
          |> List.map (fun (docId, (root: NRoot), _) -> docId, root))

      NameRes.nameRes modules

    match collectNameResErrors nameResResult.Logs with
    | Some errors -> SyntaxAnalysisError(errors, None)

    | None ->
      writeLog "Typing"
      let modules, tirCtx = Typing.infer (modules, nameResResult)

      writeLog "ArityCheck"
      let tirCtx = ArityCheck.arityCheck (modules, tirCtx)

      writeLog "OwnershipCheck"

      let modules, tirCtx =
        OwnershipCheck.ownershipCheck (modules, tirCtx)

      match collectTypingErrors tirCtx with
      | Some errors -> SyntaxAnalysisError(errors, Some tirCtx)
      | None -> SyntaxAnalysisOk(modules, tirCtx)

// -----------------------------------------------
// Dump
// -----------------------------------------------

let dumpSyntax (text: string) : string * ModuleSyntaxError list =
  let host = tokenizeHostNew ()
  let tokens = SyntaxTokenize.tokenizeAll host text

  let ast, errors =
    SyntaxTokenize.tokenize host text
    |> SyntaxParse.parse

  let tree = SyntaxTreeGen.dumpTree tokens ast
  tree, errors

// -----------------------------------------------
// Interface
// -----------------------------------------------

let newSyntaxApi () : SyntaxApi =
  let host = tokenizeHostNew ()

  { GetMiloneHomeFromEnv = getMiloneHomeFromEnv
    GetStdLibProjects = getStdLibProjects
    ReadSourceFile = readSourceFile
    ParseManifest = fun docId text -> Manifest.parseManifest docId text
    Parse = fun beingCore sourceCode -> parse1 host beingCore sourceCode
    FindDependentModules = findDependentModules
    SyntaxErrorsToString = syntaxErrorsToString
    PerformSyntaxAnalysis = fun writeLog layers -> performSyntaxAnalysis writeLog layers
    GenSyntaxTree = SyntaxTreeGen.genSyntaxTree
    DumpSyntax = dumpSyntax }
