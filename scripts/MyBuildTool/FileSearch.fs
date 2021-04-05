module rec MyBuildTool.FileSearch

open System
open System.IO

// let private stripPrefix (prefix: string) (s: string) =
//   if s.StartsWith(prefix) then s.[prefix.Length..s.Length - 1] else s

[<Literal>]
let private RecLimit = 5

let private isIncluded (filePath: string) =
  let fileName = Path.GetFileName(filePath)

  match fileName with
  | "bin"
  | "obj"
  | "node_modules"
  | "target" -> false
  | _ ->
      not (fileName.StartsWith("."))
      && not (fileName.Contains("~"))

let private relativeTo (baseDir: string) (file: string) : string = Path.GetRelativePath(baseDir, file)

let private oneOf<'T when 'T: equality> (candidates: 'T list) (value: 'T) = candidates |> List.exists ((=) value)

let private join (t: string) (s: string) = Path.Combine(s, t)
let private basename (s: string) = Path.GetFileName(s)
let private dirname (s: string) = Path.GetDirectoryName(s)
let private ext (s: string) = Path.GetExtension(s)

let private searchFiles pred (rootDir: string) =
  let rec go depth dir =
    seq {
      if depth >= 6 then
        eprintfn "warn: due to recursion limit, '%s' skipped." (Path.GetRelativePath(rootDir, dir))
      else if isIncluded dir then
        for entry in Directory.GetDirectories(dir) do
          yield! go (depth + 1) entry

        for entry in Directory.GetFiles(dir) do
          if pred entry then entry
    }

  go 0 rootDir

let descendantDirs maxDepth (dir: string) : seq<string> =
  seq {
    if maxDepth >= 1 && isIncluded dir then
      yield dir

      for subdir in Directory.EnumerateDirectories(dir) do
        yield! descendantDirs (maxDepth - 1) subdir
  }

let private sourceFiles solutionDir projectDir =
  [ for file in Directory.EnumerateFiles(projectDir) do
      if file |> ext |> oneOf [ ".fs"; ".milone" ] then
        yield file |> relativeTo solutionDir ]

let allFsProjects (solutionDir: string) =
  [ for dir in descendantDirs RecLimit solutionDir do
      let projectFile = dir |> join $"{basename dir}.fsproj"

      if File.Exists(projectFile) then
        yield relativeTo solutionDir projectFile, sourceFiles solutionDir dir ]

let allTestProjects (solutionDir: string) =
  let rel = relativeTo solutionDir

  [ for categoryDir in Directory.EnumerateDirectories(solutionDir + "/tests") do
      if isIncluded categoryDir then
        for projectDir in Directory.EnumerateDirectories(categoryDir) do
          if isIncluded projectDir then
            yield rel categoryDir, rel projectDir, basename projectDir, sourceFiles solutionDir projectDir ]
