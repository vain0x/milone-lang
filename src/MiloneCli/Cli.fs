/// Front end of the compiler.
module rec MiloneCli.Cli

open MiloneShared.SharedTypes
open MiloneShared.Util
open MiloneSyntax.ArityCheck
open MiloneSyntax.AstBundle
open MiloneSyntax.AstToHir
open MiloneSyntax.NameRes
open MiloneSyntax.Syntax
open MiloneSyntax.SyntaxParse
open MiloneSyntax.SyntaxTokenize
open MiloneSyntax.Typing
open MiloneSyntax.TySystem
open MiloneTranslation.AutoBoxing
open MiloneTranslation.Cir
open MiloneTranslation.CirDump
open MiloneTranslation.CirGen
open MiloneTranslation.ClosureConversion
open MiloneTranslation.EtaExpansion
open MiloneTranslation.Hoist
open MiloneTranslation.MirGen
open MiloneTranslation.Monomorphizing
open MiloneTranslation.RecordRes
open MiloneTranslation.TailRecOptimizing

module C = MiloneStd.StdChar
module Hir = MiloneTranslation.Hir
module S = MiloneStd.StdString
module Tir = MiloneSyntax.Tir
module TMap = MiloneStd.StdMap
module TSet = MiloneStd.StdSet
module Typing = MiloneSyntax.Typing
module SyntaxApi = MiloneSyntax.SyntaxApi

let private currentVersion () = "0.3.0"

let private helpText () =
  """milone-lang v"""
  + currentVersion ()
  + """ <https://github.com/vain0x/milone-lang>

USAGE:
    milone <SUBCOMMAND> OPTIONS...

EXAMPLE
    milone compile src/MiloneCli

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

EXPERIMENTAL features
    milone build <PROJECT-DIR>
        Builds a milone-lang project to C & build.ninja
        so that you can make an executable with ninja easily.

        --target-dir <DIR>  Output directory.
                            (Defaults to target/<PROJECT-NAME>)

    milone run <PROJECT-DIR> [-- ARGS...]
        Runs a milone-lang project.
        (Requirements: gcc and ninja.)

        --target-dir <DIR>  Output/build directory.
                            (Defaults to target/<PROJECT-NAME>)

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

    WorkDir: string

    /// Path to $HOME.
    Home: string

    /// Path to milone home (installation directory).
    MiloneHome: string

    /// Creates a profiler.
    ProfileInit: unit -> Profiler

    /// Prints a message to stderr for profiling.
    ProfileLog: string -> Profiler -> unit

    /// Ensures directory exist.
    ///
    /// baseDir -> dir -> exist
    DirCreate: string -> string -> bool

    /// Reads all contents of a file as string.
    FileReadAllText: string -> string option

    /// Writes to text file.
    FileWriteAllText: string -> string -> unit

    /// Writes to standard output.
    WriteStdout: string -> unit

    /// Turns this process into a shell that runs specified command.
    ExecuteInto: string -> unit }

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
    | Some i -> s |> S.slice 0 i
    | None -> s

let private pathIsRelative (s: string) =
  (s |> S.startsWith "./")
  || (s |> S.startsWith "../")

// -----------------------------------------------
// Context
// -----------------------------------------------

type private ModuleSyntaxData = DocId * ARoot * (string * Pos) list

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type CompileCtx =
  { EntryProjectDir: string
    EntryProjectName: string

    SyntaxCtx: SyntaxApi.SyntaxCtx
    HeaderOnly: bool

    Verbosity: Verbosity
    Host: CliHost }

let compileCtxNew (host: CliHost) verbosity projectDir : CompileCtx =
  let projectDir = projectDir |> pathStrTrimEndPathSep
  let projectName = projectDir |> pathStrToStem

  let miloneHome =
    let getEnv name =
      match name with
      | "MILONE_HOME" when host.MiloneHome <> "" -> Some host.MiloneHome
      | "HOME" when host.Home <> "" -> Some host.Home
      | _ -> None

    SyntaxApi.getMiloneHomeFromEnv getEnv

  let syntaxCtx : SyntaxApi.SyntaxCtx =
    let host : SyntaxApi.SyntaxHost =
      { EntryProjectDir = projectDir
        EntryProjectName = projectName
        MiloneHome = miloneHome
        ReadTextFile = host.FileReadAllText
        WriteLog = writeLog host verbosity }

    SyntaxApi.syntaxCtxNew host

  { EntryProjectDir = projectDir
    EntryProjectName = projectName
    SyntaxCtx = syntaxCtx
    HeaderOnly = false
    Verbosity = verbosity
    Host = host }

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

let private lowerPrim (prim: Tir.TPrim) : Hir.HPrim =
  match prim with
  | Tir.TPrim.Not -> Hir.HPrim.Not
  | Tir.TPrim.Add -> Hir.HPrim.Add
  | Tir.TPrim.Sub -> Hir.HPrim.Sub
  | Tir.TPrim.Mul -> Hir.HPrim.Mul
  | Tir.TPrim.Div -> Hir.HPrim.Div
  | Tir.TPrim.Modulo -> Hir.HPrim.Modulo
  | Tir.TPrim.BitAnd -> Hir.HPrim.BitAnd
  | Tir.TPrim.BitOr -> Hir.HPrim.BitOr
  | Tir.TPrim.BitXor -> Hir.HPrim.BitXor
  | Tir.TPrim.LeftShift -> Hir.HPrim.LeftShift
  | Tir.TPrim.RightShift -> Hir.HPrim.RightShift
  | Tir.TPrim.Equal -> Hir.HPrim.Equal
  | Tir.TPrim.Less -> Hir.HPrim.Less
  | Tir.TPrim.Compare -> Hir.HPrim.Compare
  | Tir.TPrim.ToInt flavor -> Hir.HPrim.ToInt flavor
  | Tir.TPrim.ToFloat flavor -> Hir.HPrim.ToFloat flavor
  | Tir.TPrim.Char -> Hir.HPrim.Char
  | Tir.TPrim.String -> Hir.HPrim.String
  | Tir.TPrim.Box -> Hir.HPrim.Box
  | Tir.TPrim.Unbox -> Hir.HPrim.Unbox
  | Tir.TPrim.StrLength -> Hir.HPrim.StrLength
  | Tir.TPrim.OptionNone -> Hir.HPrim.OptionNone
  | Tir.TPrim.OptionSome -> Hir.HPrim.OptionSome
  | Tir.TPrim.Nil -> Hir.HPrim.Nil
  | Tir.TPrim.Cons -> Hir.HPrim.Cons
  | Tir.TPrim.Exit -> Hir.HPrim.Exit
  | Tir.TPrim.Assert -> Hir.HPrim.Assert
  | Tir.TPrim.Printfn -> Hir.HPrim.Printfn
  | Tir.TPrim.InRegion -> Hir.HPrim.InRegion
  | Tir.TPrim.NativeCast -> Hir.HPrim.NativeCast
  | Tir.TPrim.PtrRead -> Hir.HPrim.PtrRead
  | Tir.TPrim.PtrWrite -> Hir.HPrim.PtrWrite

  | Tir.TPrim.NativeFun
  | Tir.TPrim.NativeExpr
  | Tir.TPrim.NativeStmt
  | Tir.TPrim.NativeDecl
  | Tir.TPrim.SizeOfVal -> unreachable () // Resolved in Typing.

let private lowerPatKind (kind: Tir.TPatKind) : Hir.HPatKind =
  match kind with
  | Tir.TNilPN -> Hir.HNilPN
  | Tir.TConsPN -> Hir.HConsPN
  | Tir.TNonePN -> Hir.HNonePN
  | Tir.TSomeAppPN -> Hir.HSomeAppPN
  | Tir.TVariantAppPN serial -> Hir.HVariantAppPN(lowerVariantSerial serial)
  | Tir.TTuplePN -> Hir.HTuplePN
  | Tir.TAbortPN -> Hir.HAbortPN

  | Tir.TAppPN
  | Tir.TNavPN _ -> unreachable () // Resolved in NameRes.

  | Tir.TSomePN
  | Tir.TAscribePN -> unreachable () // Resolved in Typing.

let private lowerExprKind (kind: Tir.TExprKind) : Hir.HExprKind =
  match kind with
  | Tir.TAbortEN -> Hir.HAbortEN
  | Tir.TMinusEN -> Hir.HMinusEN
  | Tir.TAppEN -> Hir.HAppEN
  | Tir.TIndexEN -> Hir.HIndexEN
  | Tir.TSliceEN -> Hir.HSliceEN
  | Tir.TCallNativeEN funName -> Hir.HCallNativeEN funName
  | Tir.TTupleEN -> Hir.HTupleEN
  | Tir.TNativeFunEN funSerial -> Hir.HNativeFunEN(lowerFunSerial funSerial)
  | Tir.TNativeExprEN code -> Hir.HNativeExprEN code
  | Tir.TNativeStmtEN code -> Hir.HNativeStmtEN code
  | Tir.TNativeDeclEN code -> Hir.HNativeDeclEN code
  | Tir.TSizeOfValEN -> Hir.HSizeOfValEN

  | Tir.TAscribeEN -> unreachable () // Resolved in Typing.

let private lowerPat (pat: Tir.TPat) : Hir.HPat =
  match pat with
  | Tir.TLitPat (lit, loc) -> Hir.HLitPat(lit, loc)
  | Tir.TDiscardPat (ty, loc) -> Hir.HDiscardPat(lowerTy ty, loc)
  | Tir.TVarPat (vis, varSerial, ty, loc) -> Hir.HVarPat(vis, lowerVarSerial varSerial, lowerTy ty, loc)
  | Tir.TVariantPat (variantSerial, ty, loc) -> Hir.HVariantPat(lowerVariantSerial variantSerial, lowerTy ty, loc)
  | Tir.TNodePat (kind, args, ty, loc) -> Hir.HNodePat(lowerPatKind kind, List.map lowerPat args, lowerTy ty, loc)
  | Tir.TAsPat (body, varSerial, loc) -> Hir.HAsPat(lowerPat body, lowerVarSerial varSerial, loc)
  | Tir.TOrPat (l, r, loc) -> Hir.HOrPat(lowerPat l, lowerPat r, loc)

let private lowerExpr (expr: Tir.TExpr) : Hir.HExpr =
  match expr with
  | Tir.TLitExpr (lit, loc) -> Hir.HLitExpr(lit, loc)
  | Tir.TVarExpr (varSerial, ty, loc) -> Hir.HVarExpr(lowerVarSerial varSerial, lowerTy ty, loc)
  | Tir.TFunExpr (funSerial, ty, loc) -> Hir.HFunExpr(lowerFunSerial funSerial, lowerTy ty, loc)
  | Tir.TVariantExpr (variantSerial, ty, loc) -> Hir.HVariantExpr(lowerVariantSerial variantSerial, lowerTy ty, loc)
  | Tir.TPrimExpr (prim, ty, loc) -> Hir.HPrimExpr(lowerPrim prim, lowerTy ty, loc)
  | Tir.TRecordExpr (exprOpt, fields, ty, loc) ->
    Hir.HRecordExpr(
      Option.map lowerExpr exprOpt,
      List.map (fun (ident, init, loc) -> ident, lowerExpr init, loc) fields,
      lowerTy ty,
      loc
    )
  | Tir.TMatchExpr (cond, arms, ty, loc) ->
    Hir.HMatchExpr(
      lowerExpr cond,
      List.map (fun (pat, guard, body) -> lowerPat pat, lowerExpr guard, lowerExpr body) arms,
      lowerTy ty,
      loc
    )
  | Tir.TNavExpr (l, r, ty, loc) -> Hir.HNavExpr(lowerExpr l, r, lowerTy ty, loc)
  | Tir.TNodeExpr (kind, args, ty, loc) -> Hir.HNodeExpr(lowerExprKind kind, List.map lowerExpr args, lowerTy ty, loc)
  | Tir.TBlockExpr (stmts, last) -> Hir.HBlockExpr(List.map lowerExpr stmts, lowerExpr last)
  | Tir.TLetValExpr (pat, init, next, ty, loc) ->
    Hir.HLetValExpr(lowerPat pat, lowerExpr init, lowerExpr next, lowerTy ty, loc)
  | Tir.TLetFunExpr _ ->
    invoke
      (fun () ->
        let funSerial, isRec, vis, argPats, body, next, ty, loc =
          match expr with
          | Tir.TLetFunExpr (t0, t1, t2, t3, t4, t5, t6, t7) -> t0, t1, t2, t3, t4, t5, t6, t7
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

  | Tir.TTyDeclExpr _
  | Tir.TOpenExpr _
  | Tir.TModuleExpr _
  | Tir.TModuleSynonymExpr _ -> Hir.hxUnit (Tir.exprToLoc expr) // Consumed in NameRes.

let private lowerModules (modules: Tir.TProgram) : Hir.HProgram =
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
      |> TMap.map (fun _ def -> lowerTyDef def) }

// -----------------------------------------------
// Processes
// -----------------------------------------------

/// Transforms HIR. The result can be converted to MIR.
let transformHir (host: CliHost) v (modules: Tir.TProgram, tyCtx: Typing.TyCtx) =
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
  match SyntaxApi.performSyntaxAnalysis ctx.SyntaxCtx with
  | SyntaxApi.SyntaxAnalysisOk _ -> true, ""
  | SyntaxApi.SyntaxAnalysisError (errors, _) -> false, SyntaxApi.syntaxErrorsToString errors

[<NoEquality; NoComparison>]
type CompileResult =
  | CompileOk of CodeGenResult
  | CompileError of string

let private compile (ctx: CompileCtx) : CompileResult =
  let host = ctx.Host
  let v = ctx.Verbosity

  match SyntaxApi.performSyntaxAnalysis ctx.SyntaxCtx with
  | SyntaxApi.SyntaxAnalysisError (errors, _) -> CompileError(SyntaxApi.syntaxErrorsToString errors)

  | SyntaxApi.SyntaxAnalysisOk (modules, tyCtx) ->
    let decls, tyCtx = transformHir host v (modules, tyCtx)
    CompileOk(codeGenHirViaMir host v ctx.EntryProjectName ctx.HeaderOnly (decls, tyCtx))

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

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type BuildOptions =
  { ProjectDir: string
    TargetDir: string
    Verbosity: Verbosity }

let private cliBuild (host: CliHost) (options: BuildOptions) =
  let miloneHome = host.MiloneHome
  let projectDir = options.ProjectDir
  let targetDir = options.TargetDir
  let ninjaFile = targetDir + "/build.ninja"

  let build =
    let rules =
      """
rule false
  description = false $out
  command = false

rule cc
  description = cc $in
  command = $${CC:-gcc} -std=c11 -O1 -g -c $include_flag $in -o $out

rule link
  description = link $out
  command = $${CC:-gcc} $in -o $out"""

    []
    |> cons "# Generated by 'milone build'.\n"
    |> cons "builddir = "
    |> cons targetDir
    |> cons "\n"
    |> cons "include_flag = -I"
    |> cons miloneHome
    |> cons "/runtime\n"
    |> cons rules
    |> cons "\n\n"

  let ctx =
    compileCtxNew host options.Verbosity projectDir

  let exeFile =
    targetDir + "/" + ctx.EntryProjectName + ".exe"

  let ok = host.DirCreate host.WorkDir targetDir

  if not ok then
    printfn "error: Couldn't create target dir: %s." targetDir
    exit 1

  match compile ctx with
  | CompileError output ->
    host.WriteStdout output

    let build =
      build
      |> cons "build "
      |> cons exeFile
      |> cons ": false\ndefault "
      |> cons exeFile
      |> cons "\n"

    host.FileWriteAllText ninjaFile (build |> List.rev |> S.concat "")
    1

  | CompileOk files ->
    let miloneObj = miloneHome + "/runtime/milone.o"
    let miloneHeader = miloneHome + "/runtime/milone.h"

    let cFile name = [ targetDir; "/"; name ] |> S.concat ""

    let objFile name =
      [ targetDir
        "/"
        pathStrToStem name
        ".o" ]
      |> S.concat ""

    let build =
      List.fold
        (fun build (name, contents) ->
          host.FileWriteAllText(targetDir + "/" + name) contents

          build
          |> cons "build "
          |> cons (objFile name)
          |> cons ": cc "
          |> cons (cFile name)
          |> cons " | "
          |> cons miloneHeader
          |> cons "\n\n")
        build
        files

    let build =
      build
      |> cons "build "
      |> cons exeFile
      |> cons ": link "
      |> cons miloneObj
      |> cons " "
      |> cons (
        files
        |> List.map (fun (name, _) -> objFile name)
        |> S.concat " "
      )
      |> cons "\n"

    host.FileWriteAllText ninjaFile (build |> List.rev |> S.concat "")
    0

let private cliRun (host: CliHost) (options: BuildOptions) (restArgs: string list) =
  let projectDir = options.ProjectDir
  let targetDir = options.TargetDir
  let ninjaFile = targetDir + "/build.ninja"

  let exeFile =
    let ctx =
      compileCtxNew host options.Verbosity projectDir

    targetDir + "/" + ctx.EntryProjectName + ".exe"

  // FIXME: Escape correctly.
  let restArgs =
    let escape (s: string) =
      s
      |> S.replace "\\" "/"
      |> S.replace "$" "\\$"
      |> S.replace "'" "\\'"
      |> S.replace "\"" "\\\""
      |> S.replace " " "\\ "

    restArgs |> List.map escape |> S.concat " "

  let exitCode = cliBuild host options

  if exitCode <> 0 then
    exitCode
  else
    host.ExecuteInto(
      "ninja -f '"
      + ninjaFile
      + "' 1>&2 && '"
      + exeFile
      + "' "
      + restArgs
    )

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

let private defaultTargetDir projectDir =
  let projectName =
    projectDir
    |> pathStrTrimEndPathSep
    |> pathStrToFileName

  "target/" + projectName

[<NoEquality; NoComparison>]
type private CliCmd =
  | HelpCmd
  | VersionCmd
  | CheckCmd
  | CompileCmd
  | BuildCmd
  | HeaderCmd
  | ParseCmd
  | RunCmd
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
    | "build" -> BuildCmd, args
    | "check" -> CheckCmd, args
    | "compile" -> CompileCmd, args
    | "run" -> RunCmd, args

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
          TargetDir = Option.defaultValue (defaultTargetDir projectDir) targetDir
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

  | BuildCmd, args ->
    let verbosity, args = parseVerbosity host args

    let targetDir, args =
      parseOption (fun x -> x = "--target-dir") args

    match args with
    | projectDir :: _ ->
      let options : BuildOptions =
        { ProjectDir = projectDir
          TargetDir = Option.defaultValue (defaultTargetDir projectDir) targetDir
          Verbosity = verbosity }

      cliBuild host options

    | [] ->
      printfn "ERROR: Expected project dir."
      1

  | RunCmd, args ->
    let verbosity, args = parseVerbosity host args

    let targetDir, args =
      parseOption (fun x -> x = "--target-dir") args

    let restArgs =
      args
      |> List.skipWhile (fun x -> x <> "--")
      |> listSkip 1

    match args with
    | projectDir :: _ ->
      let options : BuildOptions =
        { ProjectDir = projectDir
          TargetDir = Option.defaultValue (defaultTargetDir projectDir) targetDir
          Verbosity = verbosity }

      cliRun host options restArgs

    | [] ->
      printfn "ERROR: Expected project dir."
      1

  | BadCmd subcommand, _ ->
    printfn "ERROR: Unknown subcommand '%s'." subcommand
    1
