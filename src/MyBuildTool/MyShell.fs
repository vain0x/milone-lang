/// Provides `io` workflow.
module internal MyBuildTool.MyShell

open System
open System.Diagnostics
open System.IO

/// Ensures a directory exists.
let internal makeDir (dir: string) : unit =
  Directory.CreateDirectory(dir) |> ignore

/// Reads from a text file.
let internal readFile file : string option =
  try
    File.ReadAllText(file) |> Some
  with
  | :? FileNotFoundException
  | :? DirectoryNotFoundException -> None

/// Reads from a text file to be compared to an expected result.
let internal readToDiff (file: string) =
  try
    if File.Exists(file) then
      File.ReadAllText(file)
    else
      $"{file} doesn't exist"
  with _ ->
    $"{file} couldn't be read."

let internal writeFile file (contents: string) : unit = File.WriteAllText(file, contents)

/// Writes a text file if changed.
let internal writeTo (contents: string) (output: string) =
  let same =
    try
      File.Exists(output) && File.ReadAllText(output) = contents
    with _ ->
      false

  if not same then
    File.WriteAllText(output, contents)

let internal copyFile src dest : unit = File.Copy(src, dest, true)

/// Copies multiple files to a directory.
let internal copyFilesTo (srcFiles: string list) (destDir: string) : unit =
  for src in srcFiles do
    let destFile = Path.Combine(destDir, Path.GetFileName(src))

    File.Copy(src, destFile, true)

/// Gets whether the specified pathname is accepted by the filter.
let internal applyFilter (filter: string list) (pathname: string) =
  filter
  |> List.exists (fun (p: string) ->
    if p.StartsWith("*.") then
      let ext = p.[1..]
      Path.GetExtension(pathname) = ext
    else
      Path.GetFileName(pathname) = p)

/// Gets a list of files in a directory, filtering.
let internal getFilesWithFilter filter (dir: string) : string array =
  let files =
    try
      Directory.GetFiles(dir)
    with :? DirectoryNotFoundException ->
      [||]

  files |> Array.filter (applyFilter filter)

/// Copies a directory shallowly. Only files passing the filter are copied.
let internal copyDirWithFilter (filter: string list) (srcDir: string) (destDir: string) : unit =
  makeDir destDir

  for src in getFilesWithFilter filter srcDir do
    let destFile = Path.Combine(destDir, Path.GetFileName(src))

    File.Copy(src, destFile, true)

let internal removeFile file : unit =
  try
    File.Delete(file)
  with :? DirectoryNotFoundException ->
    ()

let internal removeDir dir : unit =
  try
    Directory.Delete(dir, true)
  with :? DirectoryNotFoundException ->
    ()

let internal removeFilesWithFilter (filter: string list) (dir: string) : unit =
  for file in getFilesWithFilter filter dir do
    removeFile file

let internal runWithEnv command (args: string list) env workDirOpt : unit =
  let startInfo = ProcessStartInfo(command)

  for arg in args do
    startInfo.ArgumentList.Add(arg)

  for key, value in env do
    startInfo.Environment.Add(key, value)

  match workDirOpt with
  | Some workDir -> startInfo.WorkingDirectory <- workDir
  | None -> ()

  let p = Process.Start(startInfo)
  p.WaitForExit()

  if p.ExitCode <> 0 then
    eprintfn "ERROR: '%s' %A exited with %d." command args p.ExitCode
    exit 1

let internal run command (args: string list) : unit = runWithEnv command args [] None

let internal runToOut command (args: string list) : string =
  let startInfo = ProcessStartInfo(command)

  for arg in args do
    startInfo.ArgumentList.Add(arg)

  startInfo.RedirectStandardOutput <- true
  startInfo.UseShellExecute <- false

  let p = Process.Start(startInfo)
  p.WaitForExit()

  let output = p.StandardOutput.ReadToEnd()

  if p.ExitCode <> 0 then
    printfn "%s\nERROR: '%s' %A exited with %d." output command args p.ExitCode
    exit 1

  output

// -----------------------------------------------
// Action
// -----------------------------------------------

type internal Action =
  // Fundamental actions:
  | Do of label: string * k: (unit -> unit)
  | Block of label: string * Action list

  // Basic actions:
  | Echo of msg: string
  | Run of exe: string * args: string list * env: (string * string) list * workDir: string option
  | RunWith of exe: string * args: string list * k: (string -> unit)

  // File operations:
  | ReadBytesWith of binaryFile: string * k: (byte[] -> unit)
  | CopyFile of src: string * dest: string
  | CopyFiles of srcFiles: string list * dest: string
  | CopyDirWithFilter of src: string * dest: string * filter: string list
  | MakeDir of string
  | RemoveFile of file: string
  | RemoveFilesWithFilter of dir: string * filter: string list
  | RemoveDir of dir: string

[<Sealed; NoEquality; NoComparison>]
type internal IOBuilder(label: string) =
  member _.Delay(f: unit -> Action list) = f

  member _.Run(f) = Block(label, f ())

  member _.Zero() : Action list = []
  member _.Yield(x: Action) : Action list = [ x ]
  member _.Bind(x: Action list, f: unit -> Action list) : Action list = List.append x (f ())
  member _.Combine(x: Action, y: unit -> Action list) : Action list = x :: (y ())
  member _.Combine(x: Action list, y: unit -> Action list) : Action list = List.append x (y ())

let internal io label = IOBuilder(label)

// -----------------------------------------------
// Dump
// -----------------------------------------------

let internal dumpAction a =
  let mutable indent = ""

  let rec go a =
    match a with
    | Block(label, actions) ->
      let parentIndent = indent
      indent <- indent + "  "

      eprintfn "%s%s {" parentIndent label

      for a in actions do
        go a

      eprintfn "%s}" parentIndent

      indent <- parentIndent

    | Do(label, _) -> eprintfn "%sDo(%s)" indent label

    | CopyDirWithFilter(src, dest, filter) ->
      eprintfn "%sCopyDirWithFilter(%A, %s)" indent (getFilesWithFilter filter src) dest

    | RemoveFilesWithFilter(dir, filter) ->
      eprintfn "%sRemoveFilesWithFilter(%A)" indent (getFilesWithFilter filter dir)

    | _ -> eprintfn "%s%A" indent a

  go a

// -----------------------------------------------
// Perform
// -----------------------------------------------

let private Trace = true

let internal performAction a =
  let rec go a =
    if Trace then
      match a with
      | Block _
      | Echo _ -> ()
      | _ -> dumpAction a

    match a with
    | Block(label, actions) ->
      try
        if Trace then
          eprintfn "begin %s" label

        for a in actions do
          go a

        if Trace then
          eprintfn "end %s" label
      with _ ->
        eprintfn "Failed in %s" label
        reraise ()

    | CopyFile(src, dest) -> copyFile src dest
    | CopyFiles(srcFiles, dest) -> copyFilesTo srcFiles dest
    | CopyDirWithFilter(src, dest, filter) -> copyDirWithFilter filter src dest
    | MakeDir dir -> makeDir dir
    | Run(exe, args, env, workDir) -> runWithEnv exe args env workDir
    | RunWith(exe, args, k) -> k (runToOut exe args)
    | RemoveFile file -> removeFile file
    | RemoveFilesWithFilter(dir, filter) -> removeFilesWithFilter filter dir
    | RemoveDir dir -> removeDir dir
    | Echo msg -> printfn "%s" msg
    | Do(_, k) -> k ()

    | ReadBytesWith(file, k) ->
      let contents =
        try
          File.ReadAllBytes(file)
        with
        | :? FileNotFoundException
        | :? DirectoryNotFoundException -> [||]

      k contents

  go a
