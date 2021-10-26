/// # Manifest
///
/// Provides functions for manifest file (also known as project file).
///
/// E.g. .fsproj (F#), Cargo.toml (Rust/cargo), package.json (Node.js)
module rec MiloneSyntax.Manifest

open MiloneStd.StdPath
open MiloneShared.SharedTypes
open MiloneSyntax.Syntax

module S = MiloneStd.StdString

type private Projects = (ProjectName * ProjectDir * Loc) list

type ManifestData =
  { Projects: Projects
    Libs: (string * Loc) list
    Errors: (string * Loc) list }

let private emptyManifest: ManifestData =
  { Projects = []
    Libs = []
    Errors = [] }

let private getManifestPath (projectDir: ProjectDir) : string = projectDir + "/milone_manifest"

let private splitByWhitespace (s: string) : string list =
  let rec go acc s =
    match s |> S.findIndex " " with
    | None when s = "" -> acc
    | None -> s :: acc

    | Some i ->
      let part = S.truncate i s
      go (part :: acc) (s |> S.skip (i + 1) |> S.trim)

  s |> S.trim |> go [] |> List.rev

let private parseManifest (docId: DocId) (s: string) : ManifestData =
  s
  |> S.toLines
  |> List.mapi (fun i line -> i, line)
  |> List.fold
       (fun (m: ManifestData) (row, line) ->
         let loc = Loc(docId, row, 0)
         let skip () = m

         let warn msg =
           { m with Errors = (msg, loc) :: m.Errors }

         let push name dir =
           { m with Projects = (name, dir, loc) :: m.Projects }

         let addLib name = { m with Libs = (name, loc) :: m.Libs }

         match splitByWhitespace line with
         | [] -> skip ()
         | w :: _ when w |> S.startsWith "#" -> skip ()

         | [ "project"; dir ] ->
           let name =
             Path.basename (Path dir) |> Path.toString

           if name = "" || dir = "" then
             warn "Project name/path can't be empty."
           else if name |> S.startsWith "Milone" then
             warn "Project name can't start with 'Milone'."
           else
             push name dir

         | [ "lib"; name ] -> addLib name

         | _ -> warn "Invalid statement.")
       emptyManifest

let readManifestFile (readTextFileFun: ReadTextFileFun) (projectDir: ProjectDir) : Future<ManifestData> =
  let manifestFile = getManifestPath projectDir
  let docId: DocId = manifestFile

  readTextFileFun manifestFile
  |> Future.map (fun manifestOpt ->
    match manifestOpt with
    | Some manifest -> parseManifest docId manifest
    | None -> emptyManifest)
