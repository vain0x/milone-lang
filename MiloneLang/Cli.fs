/// Front end of the compiler.
module rec MiloneLang.Cli

open MiloneLang.Types
open MiloneLang.Records
open MiloneLang.Helpers
open MiloneLang.TySystem
open MiloneLang.Lexing
open MiloneLang.Parsing
open MiloneLang.AstToHir
open MiloneLang.AutoBoxing
open MiloneLang.Bundling
open MiloneLang.NameRes
open MiloneLang.Typing
open MiloneLang.MainHoist
open MiloneLang.TyElaborating
open MiloneLang.ClosureConversion
open MiloneLang.EtaExpansion
open MiloneLang.Hoist
open MiloneLang.TailRecOptimizing
open MiloneLang.Monomorphizing
open MiloneLang.Mir
open MiloneLang.KirGen
open MiloneLang.KirPropagate
open MiloneLang.KirToMir
open MiloneLang.KirDump
open MiloneLang.CIrGen
open MiloneLang.CPrinting

type Verbosity =
  | Verbose
  | Profile of Profiler
  | Quiet

let helpText = """USAGE: milone [OPTIONS] <project-dir>

EXAMPLE
    milone -q /path/to/foo

DESCRIPTION
    Compile the specified project
    and write compiled C-language code to standard output
    or compile error messages to standard error.

    Note that `Foo.fs` is the entry point of the project
    that is located at `/path/to/Foo`.

ARGS
    project-dir
        where the source files are located

OPTIONS
    -q              No debug logs
    -v              Verbose debug logs
       --profile    Print logs with time interval"""

let strTrimEnd (s: string) =
  let rec go i =
    if i = 0 || not (charIsSpace s.[i - 1]) then s |> strSlice 0 i else go (i - 1)

  go s.Length

let charIsPathSep (c: char) = c = '/' || c = '\\'

let pathStrTrimEndPathSep (s: string) =
  if s.Length >= 1 && charIsPathSep s.[s.Length - 1]
  then s |> strSlice 0 (s.Length - 1)
  else s

/// Gets the final component splitting by path separators.
let pathStrToFileName (s: string) =
  let rec go i =
    if i = 0 then s
    else if charIsPathSep s.[i - 1] then s |> strSlice i s.Length
    else go (i - 1)

  go s.Length

/// Gets the file name without extension.
let pathStrToStem (s: string) =
  match s |> pathStrToFileName with
  | "."
  | ".." -> s

  | s ->
      let rec go i =
        if i = 0 then s
        else if s.[i - 1] = '.' then s |> strSlice 0 (i - 1)
        else go (i - 1)

      go s.Length

// -----------------------------------------------
// Read module files
// -----------------------------------------------

let private readCoreFile host moduleName =
  let miloneHome = host |> cliHostGetMiloneHome
  let readFile = host |> cliHostGetFileReadAllText

  match readFile (miloneHome + "/libcore/" + moduleName + ".fs") with
  | Some it -> it
  | None ->
      printfn "Missing file: home=%s module=%s" miloneHome moduleName
      failwithf "File not found"

let private readModuleFile host projectDir moduleName =
  let readFile = host |> cliHostGetFileReadAllText

  readFile (projectDir + "/" + moduleName + ".fs")

// -----------------------------------------------
// Write output and logs
// -----------------------------------------------

let private writeLog host verbosity msg =
  let profileLog = host |> cliHostGetProfileLog

  match verbosity with
  | Verbose ->
      // FIXME: to stderr
      printfn "// %s" msg

  | Profile profiler -> profiler |> profileLog msg

  | Quiet -> ()

let syntaxHasError syntax =
  let _, _, errors = syntax
  errors |> List.isEmpty |> not

let printSyntaxErrors syntax =
  let _, _, errors = syntax

  errors
  |> listSort (fun (_, l) (_, r) -> locCmp l r)
  |> List.iter (fun (msg, loc) -> printfn "#error %s %s" (locToString loc) msg)

let tyCtxHasError tyCtx =
  tyCtx |> tyCtxGetLogs |> List.isEmpty |> not

let printLogs tyCtx logs =
  let tyDisplayFn ty =
    let getTyIdent tySerial =
      tyCtx
      |> tyCtxGetTys
      |> mapTryFind tySerial
      |> Option.map tyDefToIdent

    tyDisplay getTyIdent ty

  logs
  |> listSort (fun (_, l) (_, r) -> locCmp l r)
  |> List.iter (fun (log, loc) -> printfn "#error %s" (log |> logToString tyDisplayFn loc))

// -----------------------------------------------
// Processes
// -----------------------------------------------

/// Loads source codes from files, performs tokenization and parsing,
/// and transforms them into high-level intermediate representation (HIR).
let syntacticallyAnalyze host v (projectDir: string) =
  let projectDir = projectDir |> pathStrTrimEndPathSep
  let projectName = projectDir |> pathStrToStem

  writeLog host v ("Bundling project=" + projectName)

  let bundleHost: BundleHost =
    { FetchModule =
        fun p m ->
          // FIXME: unique id?
          let docId = m

          if p = "MiloneCore" then
            let ast, errors = readCoreFile host m |> tokenize |> parse
            Some(docId, ast, errors)
          else if p = projectName then
            match readModuleFile host projectDir m with
            | Some contents ->
                let ast, errors = contents |> tokenize |> parse
                Some(docId, ast, errors)

            | None -> None
          else
            None }

  match bundleProgram bundleHost projectName with
  | Some syntax -> syntax
  | None -> failwithf "No entrypoint module: %s" projectName

/// Analyzes HIR to validate program and collect information.
let semanticallyAnalyze host v (expr, nameCtx, errors) =
  writeLog host v "NameRes"
  let expr, scopeCtx = nameRes (expr, nameCtx)

  writeLog host v "Typing"
  infer (expr, scopeCtx, errors)

/// Transforms HIR. The result can be converted to KIR or MIR.
let transformHir host v (expr, tyCtx) =
  writeLog host v "MainHoist"
  let expr, tyCtx = hoistMain (expr, tyCtx)

  writeLog host v "AutoBoxing"
  let expr, tyCtx = autoBox (expr, tyCtx)

  writeLog host v "TyElaborating"
  let expr, tyCtx = tyElaborate (expr, tyCtx)

  writeLog host v "ClosureConversion"
  let expr, tyCtx = declosure (expr, tyCtx)

  writeLog host v "EtaExpansion"
  let expr, tyCtx = uneta (expr, tyCtx)

  writeLog host v "Hoist"
  let expr, tyCtx = hoist (expr, tyCtx)

  writeLog host v "TailRecOptimizing"
  let expr, tyCtx = tailRecOptimize (expr, tyCtx)

  writeLog host v "Monomorphizing"
  monify (expr, tyCtx)

/// Generates C language codes from transformed HIR,
/// using mid-level intermediate representation (MIR).
let codeGenHirViaMir host v (expr, tyCtx) =
  writeLog host v "Mir"
  let stmts, mirCtx = mirify (expr, tyCtx)

  if mirCtx |> mirCtxGetLogs |> List.isEmpty |> not then
    mirCtx |> mirCtxGetLogs |> printLogs tyCtx
    "", false
  else
    writeLog host v "CIrGen"
    let cir, success = gen (stmts, mirCtx)
    let output = cprint cir

    writeLog host v "Finish"
    output, success

/// EXPERIMENTAL.
let dumpHirAsKir host v (expr, tyCtx) =
  writeLog host v "KirGen"
  let kRoot, kirGenCtx = kirGen (expr, tyCtx)

  writeLog host v "KirPropagate"
  let kRoot, kirGenCtx = kirPropagate (kRoot, kirGenCtx)

  writeLog host v "KirDump"
  let result = kirDump "" "" (kRoot, kirGenCtx)

  writeLog host v "Finish"
  result, true

/// EXPERIMENTAL.
let codeGenHirViaKir host v (expr, tyCtx) =
  writeLog host v "KirGen"
  let kRoot, kirGenCtx = kirGen (expr, tyCtx)

  writeLog host v "KirPropagate"
  let kRoot, kirGenCtx = kirPropagate (kRoot, kirGenCtx)

  writeLog host v "KirToMir"
  let stmts, mirCtx = kirToMir (kRoot, kirGenCtx)

  writeLog host v "Cir generation"
  let cir, success = gen (stmts, mirCtx)
  let cOutput = cprint cir

  writeLog host v "Finish"
  cOutput, success

let compile host v projectDir: string * bool =
  let syntax = syntacticallyAnalyze host v projectDir
  if syntax |> syntaxHasError then
    printSyntaxErrors syntax
    "", false
  else
    let expr, tyCtx = semanticallyAnalyze host v syntax
    if tyCtx |> tyCtxHasError then
      tyCtx |> tyCtxGetLogs |> printLogs tyCtx
      "", false
    else
      let expr, tyCtx = transformHir host v (expr, tyCtx)
      codeGenHirViaMir host v (expr, tyCtx)

// -----------------------------------------------
// Actions
// -----------------------------------------------

let cliParse host verbosity (projectDir: string) =
  let v = verbosity
  let projectDir = projectDir |> pathStrTrimEndPathSep
  let projectName = projectDir |> pathStrToStem

  let parseWithLogging moduleName contents =
    writeLog
      host
      v
      ("\n-------------\nParsing %s...\n--------------"
       + moduleName)
    let ast, errors = contents |> tokenize |> parse

    if errors |> List.isEmpty |> not then
      printfn "In %s" moduleName

      errors
      |> List.iter (fun (msg, pos) -> printfn "ERROR: %s %s" (posToString pos) msg)

    match verbosity with
    | Verbose -> printfn "%s" (objToString ast)
    | _ -> ()

    ast, errors

  let bundleHost: BundleHost =
    { FetchModule =
        fun p m ->
          let docId = m

          if p = "MiloneCore" then
            let ast, errors = parseWithLogging m (readCoreFile host m)
            Some(docId, ast, errors)
          else if p = projectName then
            match readModuleFile host projectDir m with
            | Some contents ->
                let ast, errors = parseWithLogging m contents
                Some(docId, ast, errors)

            | None -> None
          else
            None }

  bundleProgram bundleHost projectName |> ignore
  0

let cliCompile host verbosity projectDir =
  let output, success = compile host verbosity projectDir
  let exitCode = if success then 0 else 1

  printfn "%s" (output |> strTrimEnd)
  exitCode

let cliKirDump host projectDirs =
  let v = Quiet
  printfn "// Common code.\n%s\n" (kirHeader ())

  projectDirs
  |> List.fold (fun code projectDir ->
       printfn "// -------------------------------\n// %s\n{\n" projectDir
       printfn "/*"

       let output, success =
         let syntax = syntacticallyAnalyze host v projectDir

         let expr, tyCtx = semanticallyAnalyze host v syntax

         if tyCtx |> tyCtxHasError then
           tyCtx |> tyCtxGetLogs |> printLogs tyCtx
           "", false
         else
           let expr, tyCtx = transformHir host v (expr, tyCtx)
           dumpHirAsKir host v (expr, tyCtx)

       let code =
         if success then
           printfn "*/"
           printfn "%s" (output |> strTrimEnd)
           code
         else
           printfn "\n%s\n*/" output
           1

       printfn "\n// exit = %d\n}\n" code
       code) 0

let cliCompileViaKir host projectDirs =
  let v = Quiet
  printfn "// Generated using KIR.\n"

  projectDirs
  |> List.fold (fun code projectDir ->
       printfn "// -------------------------------\n// %s\n" projectDir
       printfn "/*"

       let output, success =
         let syntax = syntacticallyAnalyze host v projectDir

         let expr, tyCtx = semanticallyAnalyze host v syntax

         if tyCtx |> tyCtxHasError then
           tyCtx |> tyCtxGetLogs |> printLogs tyCtx
           "", false
         else
           let expr, tyCtx = transformHir host v (expr, tyCtx)
           codeGenHirViaKir host v (expr, tyCtx)

       let code =
         if success then
           printfn "*/"
           printfn "%s" (output |> strTrimEnd)
           code
         else
           printfn "\n%s\n*/" output
           1

       printfn "\n// exit = %d\n" code
       code) 0

let cli (host: CliHost) =
  match host |> cliHostGetArgs with
  | [ "-v"; projectDir ] -> cliCompile host Verbose projectDir

  | [ "--profile"; projectDir ] ->
      let profile = Profile(cliHostGetProfileInit host ())

      cliCompile host profile projectDir

  | [ "-q"; projectDir ] -> cliCompile host Quiet projectDir

  // for debugging
  | [ "parse"; "-v"; projectDir ] -> cliParse host Verbose projectDir

  | [ "parse"; "-q"; projectDir ] -> cliParse host Quiet projectDir

  // experimental feature
  | "--kir-dump" :: projectDirs -> cliKirDump host projectDirs

  | "--kir-c" :: projectDirs -> cliCompileViaKir host projectDirs

  | _ ->
      // FIXME: to stderr
      printfn "%s" helpText
      1
