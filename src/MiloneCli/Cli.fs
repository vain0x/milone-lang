/// Front end of the compiler.
module rec MiloneLang.Cli

open MiloneLang.Util
open MiloneLang.SharedTypes
open MiloneLang.Syntax
open MiloneLang.SyntaxTokenize
open MiloneLang.SyntaxParse
open MiloneLang.ArityCheck
open MiloneLang.AstBundle
open MiloneLang.TySystem
open MiloneLang.AstToHir
open MiloneLang.AutoBoxing
open MiloneLang.NameRes
open MiloneLang.Typing
open MiloneLang.RecordRes
open MiloneLang.ClosureConversion
open MiloneLang.EtaExpansion
open MiloneLang.Hoist
open MiloneLang.TailRecOptimizing
open MiloneLang.Monomorphizing
open MiloneLang.MirGen
open MiloneLang.Cir
open MiloneLang.CirGen
open MiloneLang.CirDump

module C = MiloneStd.StdChar
module TMap = MiloneStd.StdMap
module TSet = MiloneStd.StdSet
module S = MiloneStd.StdString

module Hir = MiloneLang.Hir
module Tir = MiloneLang.Tir

let private currentVersion () = "0.3.0"

let private helpText () =
  """milone-lang v"""
  + currentVersion ()
  + """ <https://github.com/vain0x/milone-lang>

USAGE:
    milone <SUBCOMMAND> OPTIONS...

EXAMPLE
    milone compile ./MiloneLang

SUBCOMMANDS
    milone check <PROJECT-DIR>
        Checks a milone-lang project.

        Performs syntax validation and type checking
        but skips code generation.

        If error, exits with non-zero code
        after writing errors to standard output.

    milone compile <PROJECT-DIR>
        Compiles a milone-lang project to C.

        If success, writes generated C codes to STDOUT
        and exits with zero.

        If error, exits with non-zero code.
        Errors are written to STDOUT. (FIXME: use STDERR)

    milone header <PROJECT-DIR>
        Compiles to C only declarations.

OPTIONS
    -h, --help      Print help text.
    -V, --version   Print compiler version.

GLOBAL OPTIONS
    -v, --verbose   Enable verbose logging for debug
        --profile   Enable profile logging
    -q, --quiet     Disable logging"""

// -----------------------------------------------
// Interface (1)
// -----------------------------------------------

type private ProjectName = string

type private ProjectDir = string

type private ModuleName = string

[<NoEquality; NoComparison>]
type Verbosity =
  | Verbose
  | Profile of Profiler
  | Quiet

/// Abstraction layer of CLI program.
[<NoEquality; NoComparison>]
type CliHost =
  {
    /// Command line args.
    Args: string list

    /// Path to $HOME.
    Home: string

    /// Path to milone home (installation directory).
    MiloneHome: string

    /// Creates a profiler.
    ProfileInit: unit -> Profiler

    /// Prints a message to stderr for profiling.
    ProfileLog: string -> Profiler -> unit

    /// Reads all contents of a file as string.
    FileReadAllText: string -> string option

    /// Writes to text file.
    FileWriteAllText: string -> string -> unit

    /// Writes to standard output.
    WriteStdout: string -> unit }

// -----------------------------------------------
// Helpers
// -----------------------------------------------

let private charIsPathSep (c: char) = c = '/' || c = '\\'

let private pathStrTrimEndPathSep (s: string) = S.trimEndIf charIsPathSep s

// wants string.findLastIndex
/// Gets the final component splitting by path separators.
let private pathStrToFileName (s: string) =
  let rec go i =
    if i = 0 then
      s
    else if charIsPathSep s.[i - 1] then
      s |> S.slice i s.Length
    else
      go (i - 1)

  go s.Length

/// Gets the file name without extension.
let private pathStrToStem (s: string) =
  match s |> pathStrToFileName with
  | "."
  | ".." -> s

  | s ->
      match s |> S.findLastIndex "." with
      | Some i -> s |> S.slice 0 (i - 1)
      | None -> s

let private pathIsRelative (s: string) =
  (s |> S.startsWith "./")
  || (s |> S.startsWith "../")

// -----------------------------------------------
// MiloneCore resolution
// -----------------------------------------------

/// Generates decls for each MiloneCore module
/// whose name appears in the token stream.
let resolveMiloneCoreDeps tokens ast =
  let knownNames = [ "List"; "Option"; "String" ]

  let isKnownName moduleName =
    knownNames
    |> List.exists (fun name -> name = moduleName)

  let moduleMap =
    let rec go acc tokens =
      match tokens with
      | [] -> acc
      | (IdentToken moduleName, pos) :: (DotToken, _) :: tokens -> go ((moduleName, pos) :: acc) tokens
      | _ :: tokens -> go acc tokens

    let moduleNames = go [] tokens

    let add acc (moduleName, pos) =
      if (acc |> TMap.containsKey moduleName |> not)
         && isKnownName moduleName then
        acc |> TMap.add moduleName pos
      else
        acc

    moduleNames |> List.fold add (TMap.empty compare)

  let insertOpenDecls decls =
    moduleMap
    |> TMap.fold
         (fun decls moduleName pos ->
           AModuleSynonymDecl(
             Name(moduleName, pos),
             [ Name("MiloneCore", pos)
               Name(moduleName, pos) ],
             pos
           )
           :: decls)
         decls

  match ast with
  | AExprRoot decls -> AExprRoot(insertOpenDecls decls)
  | AModuleRoot (name, decls, pos) -> AModuleRoot(name, insertOpenDecls decls, pos)

// -----------------------------------------------
// Context
// -----------------------------------------------

type private ModuleSyntaxData = DocId * ARoot * (string * Pos) list

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type CompileCtx =
  { ProjectDir: string
    ProjectName: string

    /// project name -> project directory
    Projects: AssocMap<string, string>

    TokenizeHost: TokenizeHost
    FetchModule: ProjectName -> ProjectDir -> ModuleName -> ModuleSyntaxData option

    HeaderOnly: bool

    Verbosity: Verbosity
    Host: CliHost }

let compileCtxNew (host: CliHost) verbosity projectDir : CompileCtx =
  let projectDir = projectDir |> pathStrTrimEndPathSep
  let projectName = projectDir |> pathStrToStem

  let miloneHome =
    if host.MiloneHome <> "" then
      host.MiloneHome
    else
      host.Home + "/.milone"

  let projects =
    TMap.empty compare
    |> TMap.add "MiloneCore" (miloneHome + "/milone_libs/MiloneCore")
    |> TMap.add "MiloneStd" (miloneHome + "/milone_libs/MiloneStd")
    |> TMap.add projectName projectDir

  let readModuleFile (_: string) (projectDir: string) (moduleName: string) =
    let read (ext: string) =
      match host.FileReadAllText(projectDir + "/" + moduleName + ext) with
      | Some text -> Some(moduleName, text)
      | None -> None

    match read ".milone" with
    | (Some _) as it -> it
    | None -> read ".fs"

  let tokenizeHost = tokenizeHostNew ()

  let doParse (text: string) =
    let tokens = text |> tokenize tokenizeHost
    let errorTokens, tokens = tokens |> List.partition isErrorToken
    let ast, parseErrors = tokens |> parse

    let errors =
      List.append (tokenizeErrors errorTokens) parseErrors

    let ast =
      if errors |> List.isEmpty then
        resolveMiloneCoreDeps tokens ast
      else
        ast

    ast, errors

  let fetchModule (projectName: string) (projectDir: string) (moduleName: string) =
    match readModuleFile projectName projectDir moduleName with
    | None -> None
    | Some (docId, text) ->
        let ast, errors = doParse text
        Some(docId, ast, errors)

  { ProjectDir = projectDir
    ProjectName = projectName
    Projects = projects
    TokenizeHost = tokenizeHost
    FetchModule = fetchModule
    HeaderOnly = false
    Verbosity = verbosity
    Host = host }

let private compileCtxAddProjectReferences references (ctx: CompileCtx) =
  let projects =
    references
    |> List.fold
         (fun projects projectDir ->
           let projectDir = projectDir |> pathStrTrimEndPathSep
           let projectName = projectDir |> pathStrToStem

           if projects |> TMap.containsKey projectName then
             failwithf "Project name is duplicated: '%s'" projectName

           projects |> TMap.add projectName projectDir)
         ctx.Projects

  { ctx with Projects = projects }

// -----------------------------------------------
// Write output and logs
// -----------------------------------------------

let private writeLog (host: CliHost) verbosity msg =
  let profileLog = host.ProfileLog

  match verbosity with
  | Verbose ->
      // FIXME: to stderr
      printfn "// %s" msg

  | Profile profiler -> profiler |> profileLog msg

  | Quiet -> ()

let private syntaxHasError (syntax: SyntaxAnalysisResult) =
  let _, _, errors = syntax
  errors |> List.isEmpty |> not

let private syntaxErrorToString syntax =
  let _, _, errors = syntax

  errors
  |> listSort (fun (_, l) (_, r) -> locCompare l r)
  |> List.map (fun (msg, loc) -> "#error " + locToString loc + " " + msg + "\n")
  |> strConcat

let private tyCtxHasError (tyCtx: TyCtx) = tyCtx.Logs |> List.isEmpty |> not

let private nameResLogsToString logs =
  logs
  |> listSort (fun (_, l) (_, r) -> locCompare l r)
  |> List.map
       (fun (log, loc) ->
         "#error "
         + locToString loc
         + " "
         + Tir.nameResLogToString log
         + "\n")
  |> strConcat

let private semanticErrorToString (tyCtx: TyCtx) logs =
  let tyDisplayFn ty =
    let getTyName tySerial =
      tyCtx.Tys
      |> TMap.tryFind tySerial
      |> Option.map Tir.tyDefToName

    tyDisplay getTyName ty

  logs
  |> listSort (fun (_, l) (_, r) -> locCompare l r)
  |> List.map
       (fun (log, loc) ->
         "#error "
         + locToString loc
         + " "
         + Tir.logToString tyDisplayFn log
         + "\n")
  |> strConcat

// -----------------------------------------------
// Syntax/semantics data type conversion
// -----------------------------------------------

let private lowerTk (tk: Tir.Tk) : Hir.Tk =
  match tk with
  | Tir.IntTk intFlavor -> Hir.IntTk intFlavor
  | Tir.FloatTk floatFlavor -> Hir.FloatTk floatFlavor
  | Tir.BoolTk -> Hir.BoolTk
  | Tir.CharTk -> Hir.CharTk
  | Tir.StrTk -> Hir.StrTk
  | Tir.ObjTk -> Hir.ObjTk

  | Tir.FunTk -> Hir.FunTk
  | Tir.TupleTk -> Hir.TupleTk
  | Tir.OptionTk -> Hir.OptionTk
  | Tir.ListTk -> Hir.ListTk

  | Tir.VoidTk -> Hir.VoidTk
  | Tir.NativePtrTk isMut -> Hir.NativePtrTk isMut
  | Tir.NativeFunTk -> Hir.NativeFunTk
  | Tir.NativeTypeTk code -> Hir.NativeTypeTk code

  | Tir.MetaTk (serial, loc) -> Hir.MetaTk(serial, loc)
  | Tir.UnionTk serial -> Hir.UnionTk serial
  | Tir.RecordTk serial -> Hir.RecordTk serial

  | Tir.ErrorTk _
  | Tir.SynonymTk _ -> unreachable () // Resolved in Typing.

  | Tir.UnresolvedTk _
  | Tir.UnresolvedVarTk _ -> unreachable () // Resolved in NameRes.

let private lowerTy (ty: Tir.Ty) : Hir.Ty =
  let (Tir.Ty (tk, tyArgs)) = ty
  Hir.Ty(lowerTk tk, List.map lowerTy tyArgs)

let private lowerTyScheme (tyScheme: Tir.TyScheme) : Hir.TyScheme =
  let (Tir.TyScheme (fvs, ty)) = tyScheme
  Hir.TyScheme(fvs, lowerTy ty)

let private lowerVarSerial (Tir.VarSerial serial) = Hir.VarSerial serial
let private lowerFunSerial (Tir.FunSerial serial) = Hir.FunSerial serial
let private lowerVariantSerial (Tir.VariantSerial serial) = Hir.VariantSerial serial

let private lowerVarDef (def: Tir.VarDef) : Hir.VarDef =
  { Name = def.Name
    IsStatic = def.IsStatic
    Linkage = def.Linkage
    Ty = lowerTy def.Ty
    Loc = def.Loc }

let private lowerFunDef (def: Tir.FunDef) : Hir.FunDef =
  { Name = def.Name
    Arity = def.Arity
    Ty = lowerTyScheme def.Ty
    Abi = def.Abi
    Linkage = def.Linkage
    Loc = def.Loc }

let private lowerVariantDef (def: Tir.VariantDef) : Hir.VariantDef =
  { Name = def.Name
    UnionTySerial = def.UnionTySerial
    IsNewtype = def.IsNewtype
    HasPayload = def.HasPayload
    PayloadTy = lowerTy def.PayloadTy
    Loc = def.Loc }

let private lowerTyDef (def: Tir.TyDef) : Hir.TyDef =
  match def with
  | Tir.UnionTyDef (ident, variants, loc) -> Hir.UnionTyDef(ident, List.map lowerVariantSerial variants, loc)
  | Tir.RecordTyDef (ident, fields, loc) ->
      Hir.RecordTyDef(ident, List.map (fun (ident, ty, loc) -> ident, lowerTy ty, loc) fields, loc)

  | Tir.MetaTyDef _
  | Tir.UniversalTyDef _
  | Tir.SynonymTyDef _ -> unreachable () // Resolved in Typing.

let private lowerPrim (prim: Tir.HPrim) : Hir.HPrim =
  match prim with
  | Tir.HPrim.Not -> Hir.HPrim.Not
  | Tir.HPrim.Add -> Hir.HPrim.Add
  | Tir.HPrim.Sub -> Hir.HPrim.Sub
  | Tir.HPrim.Mul -> Hir.HPrim.Mul
  | Tir.HPrim.Div -> Hir.HPrim.Div
  | Tir.HPrim.Modulo -> Hir.HPrim.Modulo
  | Tir.HPrim.BitAnd -> Hir.HPrim.BitAnd
  | Tir.HPrim.BitOr -> Hir.HPrim.BitOr
  | Tir.HPrim.BitXor -> Hir.HPrim.BitXor
  | Tir.HPrim.LeftShift -> Hir.HPrim.LeftShift
  | Tir.HPrim.RightShift -> Hir.HPrim.RightShift
  | Tir.HPrim.Equal -> Hir.HPrim.Equal
  | Tir.HPrim.Less -> Hir.HPrim.Less
  | Tir.HPrim.Compare -> Hir.HPrim.Compare
  | Tir.HPrim.ToInt flavor -> Hir.HPrim.ToInt flavor
  | Tir.HPrim.ToFloat flavor -> Hir.HPrim.ToFloat flavor
  | Tir.HPrim.Char -> Hir.HPrim.Char
  | Tir.HPrim.String -> Hir.HPrim.String
  | Tir.HPrim.Box -> Hir.HPrim.Box
  | Tir.HPrim.Unbox -> Hir.HPrim.Unbox
  | Tir.HPrim.StrLength -> Hir.HPrim.StrLength
  | Tir.HPrim.OptionNone -> Hir.HPrim.OptionNone
  | Tir.HPrim.OptionSome -> Hir.HPrim.OptionSome
  | Tir.HPrim.Nil -> Hir.HPrim.Nil
  | Tir.HPrim.Cons -> Hir.HPrim.Cons
  | Tir.HPrim.Exit -> Hir.HPrim.Exit
  | Tir.HPrim.Assert -> Hir.HPrim.Assert
  | Tir.HPrim.Printfn -> Hir.HPrim.Printfn
  | Tir.HPrim.InRegion -> Hir.HPrim.InRegion
  | Tir.HPrim.NativeCast -> Hir.HPrim.NativeCast
  | Tir.HPrim.PtrRead -> Hir.HPrim.PtrRead
  | Tir.HPrim.PtrWrite -> Hir.HPrim.PtrWrite

  | Tir.HPrim.NativeFun
  | Tir.HPrim.NativeExpr
  | Tir.HPrim.NativeStmt
  | Tir.HPrim.NativeDecl
  | Tir.HPrim.SizeOfVal -> unreachable () // Resolved in Typing.

let private lowerPatKind (kind: Tir.HPatKind) : Hir.HPatKind =
  match kind with
  | Tir.HNilPN -> Hir.HNilPN
  | Tir.HConsPN -> Hir.HConsPN
  | Tir.HNonePN -> Hir.HNonePN
  | Tir.HSomeAppPN -> Hir.HSomeAppPN
  | Tir.HVariantAppPN serial -> Hir.HVariantAppPN(lowerVariantSerial serial)
  | Tir.HTuplePN -> Hir.HTuplePN
  | Tir.HAbortPN -> Hir.HAbortPN

  | Tir.HAppPN
  | Tir.HNavPN _ -> unreachable () // Resolved in NameRes.

  | Tir.HSomePN
  | Tir.HAscribePN -> unreachable () // Resolved in Typing.

  | Tir.HBoxPN -> unreachable () // Generated in AutoBoxing.

let private lowerExprKind (kind: Tir.HExprKind) : Hir.HExprKind =
  match kind with
  | Tir.HAbortEN -> Hir.HAbortEN
  | Tir.HMinusEN -> Hir.HMinusEN
  | Tir.HAppEN -> Hir.HAppEN
  | Tir.HIndexEN -> Hir.HIndexEN
  | Tir.HSliceEN -> Hir.HSliceEN
  | Tir.HCallNativeEN funName -> Hir.HCallNativeEN funName
  | Tir.HTupleEN -> Hir.HTupleEN
  | Tir.HNativeFunEN funSerial -> Hir.HNativeFunEN(lowerFunSerial funSerial)
  | Tir.HNativeExprEN code -> Hir.HNativeExprEN code
  | Tir.HNativeStmtEN code -> Hir.HNativeStmtEN code
  | Tir.HNativeDeclEN code -> Hir.HNativeDeclEN code
  | Tir.HSizeOfValEN -> Hir.HSizeOfValEN

  | Tir.HRangeEN -> unreachable () // Never generated.
  | Tir.HAscribeEN -> unreachable () // Resolved in Typing.

  | Tir.HCallProcEN
  | Tir.HCallClosureEN
  | Tir.HClosureEN -> unreachable () // Generated in EtaExpansion.

  | Tir.HCallTailRecEN -> unreachable () // Generated in TailRecOptimizing.

  | Tir.HRecordEN
  | Tir.HRecordItemEN _ -> unreachable () // Generated in RecordRes.

let private lowerPat (pat: Tir.HPat) : Hir.HPat =
  match pat with
  | Tir.HLitPat (lit, loc) -> Hir.HLitPat(lit, loc)
  | Tir.HDiscardPat (ty, loc) -> Hir.HDiscardPat(lowerTy ty, loc)
  | Tir.HVarPat (vis, varSerial, ty, loc) -> Hir.HVarPat(vis, lowerVarSerial varSerial, lowerTy ty, loc)
  | Tir.HVariantPat (variantSerial, ty, loc) -> Hir.HVariantPat(lowerVariantSerial variantSerial, lowerTy ty, loc)
  | Tir.HNodePat (kind, args, ty, loc) -> Hir.HNodePat(lowerPatKind kind, List.map lowerPat args, lowerTy ty, loc)
  | Tir.HAsPat (body, varSerial, loc) -> Hir.HAsPat(lowerPat body, lowerVarSerial varSerial, loc)
  | Tir.HOrPat (l, r, loc) -> Hir.HOrPat(lowerPat l, lowerPat r, loc)

let private lowerExpr (expr: Tir.HExpr) : Hir.HExpr =
  match expr with
  | Tir.HLitExpr (lit, loc) -> Hir.HLitExpr(lit, loc)
  | Tir.HVarExpr (varSerial, ty, loc) -> Hir.HVarExpr(lowerVarSerial varSerial, lowerTy ty, loc)
  | Tir.HFunExpr (funSerial, ty, loc) -> Hir.HFunExpr(lowerFunSerial funSerial, lowerTy ty, loc)
  | Tir.HVariantExpr (variantSerial, ty, loc) -> Hir.HVariantExpr(lowerVariantSerial variantSerial, lowerTy ty, loc)
  | Tir.HPrimExpr (prim, ty, loc) -> Hir.HPrimExpr(lowerPrim prim, lowerTy ty, loc)
  | Tir.HRecordExpr (exprOpt, fields, ty, loc) ->
      Hir.HRecordExpr(
        Option.map lowerExpr exprOpt,
        List.map (fun (ident, init, loc) -> ident, lowerExpr init, loc) fields,
        lowerTy ty,
        loc
      )
  | Tir.HMatchExpr (cond, arms, ty, loc) ->
      Hir.HMatchExpr(
        lowerExpr cond,
        List.map (fun (pat, guard, body) -> lowerPat pat, lowerExpr guard, lowerExpr body) arms,
        lowerTy ty,
        loc
      )
  | Tir.HNavExpr (l, r, ty, loc) -> Hir.HNavExpr(lowerExpr l, r, lowerTy ty, loc)
  | Tir.HNodeExpr (kind, args, ty, loc) -> Hir.HNodeExpr(lowerExprKind kind, List.map lowerExpr args, lowerTy ty, loc)
  | Tir.HBlockExpr (stmts, last) -> Hir.HBlockExpr(List.map lowerExpr stmts, lowerExpr last)
  | Tir.HLetValExpr (pat, init, next, ty, loc) ->
      Hir.HLetValExpr(lowerPat pat, lowerExpr init, lowerExpr next, lowerTy ty, loc)
  | Tir.HLetFunExpr _ ->
      (fun () ->
        let funSerial, isRec, vis, argPats, body, next, ty, loc =
          match expr with
          | Tir.HLetFunExpr (t0, t1, t2, t3, t4, t5, t6, t7) -> t0, t1, t2, t3, t4, t5, t6, t7
          | _ -> unreachable ()

        Hir.HLetFunExpr(
          lowerFunSerial funSerial,
          isRec,
          vis,
          List.map lowerPat argPats,
          lowerExpr body,
          lowerExpr next,
          lowerTy ty,
          loc
        ))
        ()

  | Tir.HTyDeclExpr _
  | Tir.HOpenExpr _
  | Tir.HModuleExpr _
  | Tir.HModuleSynonymExpr _ -> Hir.hxUnit (Tir.exprToLoc expr) // Consumed in NameRes.

let private lowerModules (modules: Tir.HProgram) : Hir.HProgram =
  modules
  |> List.map (fun (p, m, decls) -> p, m, List.map lowerExpr decls)

let private lowerTyCtx (tyCtx: Typing.TyCtx) : Hir.TyCtx =
  { Serial = tyCtx.Serial

    Vars =
      tyCtx.Vars
      |> TMap.stableMap (fun serial def -> lowerVarSerial serial, lowerVarDef def) Hir.varSerialCompare

    Funs =
      tyCtx.Funs
      |> TMap.stableMap (fun serial def -> lowerFunSerial serial, lowerFunDef def) Hir.funSerialCompare

    Variants =
      tyCtx.Variants
      |> TMap.stableMap (fun serial def -> lowerVariantSerial serial, lowerVariantDef def) Hir.variantSerialCompare

    MainFunOpt = tyCtx.MainFunOpt |> Option.map lowerFunSerial

    Tys =
      tyCtx.Tys
      |> TMap.map (fun _ def -> lowerTyDef def)

    TyLevels = tyCtx.TyLevels
    Level = 0
    TraitBounds = []
    Logs = [] }

// -----------------------------------------------
// Processes
// -----------------------------------------------

type private SyntaxAnalysisResult = Tir.HProgram * Tir.NameCtx * (string * Loc) list

let private isErrorToken token =
  match token with
  | ErrorToken _, _ -> true
  | _ -> false

let private tokenizeErrors errorTokens =
  errorTokens
  |> List.map
       (fun token ->
         match token with
         | ErrorToken error, pos -> tokenizeErrorToString error, pos
         | _ -> unreachable ())

/// Loads source codes from files, performs tokenization and SyntaxParse,
/// and transforms them into high-level intermediate representation (HIR).
let syntacticallyAnalyze (ctx: CompileCtx) : SyntaxAnalysisResult =
  let host = ctx.Host
  let v = ctx.Verbosity

  writeLog host v ("AstBundle project=" + ctx.ProjectName)

  let fetchModule (projectName: ProjectName) (moduleName: ModuleName) : ModuleSyntaxData option =
    let projectDir =
      match ctx.Projects |> TMap.tryFind projectName with
      | Some it -> it
      | None -> ctx.ProjectDir + "/../" + projectName

    ctx.FetchModule projectName projectDir moduleName

  bundleCompatible fetchModule ctx.ProjectName

[<NoEquality; NoComparison>]
type SemaAnalysisResult =
  | SemaAnalysisOk of Tir.HProgram * Typing.TyCtx
  | SemaAnalysisNameResError of (Tir.NameResLog * Loc) list
  | SemaAnalysisTypingError of Typing.TyCtx

/// Analyzes HIR to validate program and collect information.
let semanticallyAnalyze (host: CliHost) v (syntax: SyntaxAnalysisResult) : SemaAnalysisResult =
  let modules, nameCtx, syntaxErrors = syntax
  assert (syntaxErrors |> List.isEmpty)

  writeLog host v "NameRes"

  let modules, scopeCtx = nameRes (modules, nameCtx)

  if scopeCtx.Logs |> List.isEmpty |> not then
    SemaAnalysisNameResError scopeCtx.Logs
  else
    writeLog host v "Typing"

    let modules, tyCtx = infer (modules, scopeCtx, [])

    if tyCtx.Logs |> List.isEmpty |> not then
      SemaAnalysisTypingError tyCtx
    else
      writeLog host v "ArityCheck"
      let tyCtx = arityCheck (modules, tyCtx)

      if tyCtx.Logs |> List.isEmpty |> not then
        SemaAnalysisTypingError tyCtx
      else
        SemaAnalysisOk(modules, tyCtx)

/// Transforms HIR. The result can be converted to MIR.
let transformHir (host: CliHost) v (modules: Tir.HProgram, tyCtx: Typing.TyCtx) =
  writeLog host v "Lower"
  let modules = lowerModules modules
  let tyCtx = lowerTyCtx tyCtx

  let expr =
    let decls =
      (modules
       |> List.collect (fun (_, _, decls) -> decls))

    Hir.hxSemi decls noLoc

  writeLog host v "AutoBoxing"
  let expr, tyCtx = autoBox (expr, tyCtx)

  writeLog host v "RecordRes"
  let expr, tyCtx = recordRes (expr, tyCtx)

  writeLog host v "ClosureConversion"
  let expr, tyCtx = closureConversion (expr, tyCtx)

  writeLog host v "EtaExpansion"
  let expr, tyCtx = etaExpansion (expr, tyCtx)

  writeLog host v "Hoist"
  let decls, tyCtx = hoist (expr, tyCtx)

  writeLog host v "TailRecOptimizing"
  let decls, tyCtx = tailRecOptimize (decls, tyCtx)

  writeLog host v "Monomorphizing"
  monify (decls, tyCtx)

/// (module name, C code) list
type CodeGenResult = (string * string) list

/// Generates C language codes from transformed HIR,
/// using mid-level intermediate representation (MIR).
let codeGenHirViaMir (host: CliHost) v projectName headerOnly (decls, tyCtx) : CodeGenResult =
  writeLog host v "Mir"
  let stmts, mirCtx = mirify (decls, tyCtx)

  writeLog host v "CirGen"
  let modules = genCir (stmts, mirCtx)

  writeLog host v "CirDump"

  let output =
    if headerOnly then
      failwith "header command is unimplemented"

    modules
    |> List.map
         (fun (docId, cir) ->
           let fileName =
             if docId = projectName + ".Program"
                || docId = projectName + ".EntryPoint"
                || docId = projectName + "." + projectName then
               projectName + ".c"
             else
               S.replace "." "_" docId + ".c"

           fileName, cirDump cir)

  writeLog host v "Finish"
  output

let check (ctx: CompileCtx) : bool * string =
  let host = ctx.Host
  let v = ctx.Verbosity

  let syntax = syntacticallyAnalyze ctx

  if syntax |> syntaxHasError then
    false, syntaxErrorToString syntax
  else
    match semanticallyAnalyze host v syntax with
    | SemaAnalysisNameResError logs -> false, nameResLogsToString logs
    | SemaAnalysisTypingError tyCtx -> false, semanticErrorToString tyCtx tyCtx.Logs
    | SemaAnalysisOk _ -> true, ""

[<NoEquality; NoComparison>]
type CompileResult =
  | CompileOk of CodeGenResult
  | CompileError of string

let private compile (ctx: CompileCtx) : CompileResult =
  let host = ctx.Host
  let v = ctx.Verbosity

  let syntax = syntacticallyAnalyze ctx

  if syntax |> syntaxHasError then
    CompileError(syntaxErrorToString syntax)
  else
    match semanticallyAnalyze host v syntax with
    | SemaAnalysisNameResError logs -> CompileError(nameResLogsToString logs)
    | SemaAnalysisTypingError tyCtx -> CompileError(semanticErrorToString tyCtx tyCtx.Logs)

    | SemaAnalysisOk (modules, tyCtx) ->
        let decls, tyCtx = transformHir host v (modules, tyCtx)
        CompileOk(codeGenHirViaMir host v ctx.ProjectName ctx.HeaderOnly (decls, tyCtx))

// -----------------------------------------------
// Actions
// -----------------------------------------------

let cliParse (host: CliHost) v (projectDir: string) = todo ()
// let ctx = compileCtxNew host v projectDir

// let parseWithLogging moduleName contents =
//   writeLog
//     host
//     v
//     ("\n-------------\nSyntaxParse %s...\n--------------"
//      + moduleName)

//   let ast, errors =
//     contents |> tokenize ctx.TokenizeHost |> parse

//   if errors |> List.isEmpty |> not then
//     printfn "In %s" moduleName

//     errors
//     |> List.iter (fun (msg, pos) -> printfn "ERROR: %s %s" (posToString pos) msg)

//   match v with
//   | Verbose -> printfn "%s" (objToString ast)
//   | _ -> ()

//   ast, errors

// bundleProgram (ctx |> toBundleHost parseWithLogging) ctx.ProjectName
// |> ignore

// 0

let cliCheck (host: CliHost) verbosity projectDir =
  let ctx = compileCtxNew host verbosity projectDir

  let ok, output = check ctx
  let exitCode = if ok then 0 else 1

  printfn "%s" (output |> S.replace "#error " "" |> S.trimEnd)
  exitCode

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type CompileOptions =
  { ProjectDir: string
    TargetDir: string
    HeaderOnly: bool
    Verbosity: Verbosity }

let cliCompile (host: CliHost) (options: CompileOptions) =
  let ctx =
    compileCtxNew host options.Verbosity options.ProjectDir

  let ctx =
    { ctx with
        HeaderOnly = options.HeaderOnly }

  let result = compile ctx

  match result with
  | CompileOk files ->
      List.fold
        (fun () (name, contents) ->
          printfn "%s" name
          host.FileWriteAllText(options.TargetDir + "/" + name) contents)
        ()
        files

      0

  | CompileError output ->
      host.WriteStdout output
      1

// -----------------------------------------------
// Arg parsing
// -----------------------------------------------

/// Parses CLI args for a flag.
///
/// `picker state arg` should return `Some state` if arg is consumed. None otherwise.
///
/// Returns final state and args not consumed.
let private parseFlag picker state args =
  // acc: args not consumed in reversed order
  let rec go acc state args =
    match args with
    | []
    | "--" :: _ -> state, List.append (List.rev acc) args

    | arg :: args ->
        match picker state arg with
        | Some state -> go acc state args

        | None -> go (arg :: acc) state args

  go [] state args

/// Parses CLI args for an option with value.
let private parseOption isFlag args =
  // acc: args not consumed in reversed order
  let rec go acc args =
    match args with
    | []
    | [ _ ] -> None, List.append (List.rev acc) args

    | flag :: value :: args when isFlag flag -> Some value, List.append (List.rev acc) args

    | arg :: args -> go (arg :: acc) args

  go [] args

let private containsHelpFlag args =
  let ok, _ =
    parseFlag
      (fun _ arg ->
        match arg with
        | "-h"
        | "--help" -> Some true
        | _ -> None)
      false
      args

  ok

let private parseVerbosity (host: CliHost) args =
  parseFlag
    (fun (_: Verbosity) arg ->
      match arg with
      | "-v"
      | "--verbose" -> Some Verbose
      | "-q"
      | "--quiet" -> Some Quiet
      | "--profile" -> Some(Profile(host.ProfileInit()))
      | _ -> None)
    Quiet
    args

[<NoEquality; NoComparison>]
type private CliCmd =
  | HelpCmd
  | VersionCmd
  | CheckCmd
  | CompileCmd
  | HeaderCmd
  | ParseCmd
  | BadCmd of string

let private parseArgs args =
  let args = args |> List.skip 1

  match args with
  | []
  | "help" :: _ -> HelpCmd, []
  | _ when args |> containsHelpFlag -> HelpCmd, []

  | "version" :: _
  | "-V" :: _
  | "--version" :: _ -> VersionCmd, []

  // for backward
  | "-v" :: _
  | "-q" :: _
  | "--profile" :: _ -> CompileCmd, args

  | arg :: args ->
      match arg with
      | "check" -> CheckCmd, args

      | "build"
      | "compile" -> CompileCmd, args

      | "header" -> HeaderCmd, args

      // for debug
      | "parse" -> ParseCmd, args

      | _ -> BadCmd arg, []

// -----------------------------------------------
// Entrypoint
// -----------------------------------------------

let cli (host: CliHost) =
  match host.Args |> parseArgs with
  | HelpCmd, _ ->
      printfn "%s" (helpText ())
      0

  | VersionCmd, _ ->
      printfn "%s" (currentVersion ())
      0

  | CheckCmd, args ->
      let verbosity, args = parseVerbosity host args

      match args with
      | [ projectDir ] -> cliCheck host verbosity projectDir

      | [] ->
          printfn "ERROR: Expected project dir."
          1

      | arg :: _ ->
          printfn "ERROR: Unknown argument: '%s'." arg
          1

  | HeaderCmd, args ->
      let verbosity, args = parseVerbosity host args

      match args with
      | projectDir :: _ ->
          let options : CompileOptions =
            { ProjectDir = projectDir
              TargetDir = "."
              HeaderOnly = true
              Verbosity = verbosity }

          cliCompile host options

      | [] ->
          printfn "ERROR: Expected project dir."
          1

  | CompileCmd, args ->
      let verbosity, args = parseVerbosity host args

      let targetDir, args =
        parseOption (fun x -> x = "--target-dir") args

      match args with
      | projectDir :: _ ->
          let options : CompileOptions =
            { ProjectDir = projectDir
              TargetDir = Option.defaultValue "." targetDir
              HeaderOnly = false
              Verbosity = verbosity }

          cliCompile host options

      | [] ->
          printfn "ERROR: Expected project dir."
          1

  | ParseCmd, args ->
      let verbosity, args = parseVerbosity host args

      match args with
      | projectDir :: _ -> cliParse host verbosity projectDir

      | [] ->
          printfn "ERROR: Expected project dir."
          1

  | BadCmd subcommand, _ ->
      printfn "ERROR: Unknown subcommand '%s'." subcommand
      1
