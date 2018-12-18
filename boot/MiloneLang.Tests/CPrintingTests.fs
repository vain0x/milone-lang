module MiloneLang.CPrintingTests

open System
open System.IO
open MiloneLang.Assets
open MiloneLang.Program
open Xunit

let eol = """
"""

let testFile category case =
  async {
    let! source =
      IO.File.ReadAllTextAsync(
        IO.Path.Combine(testsDir.Value, category, case, case + ".milone")
      ) |> Async.AwaitTask
    let content =
      match toCir Verbosity.Silent source with
      | cir, [] ->
        CPrinting.cprintRun (fun acc -> CPrinting.cprintDecls acc cir)
      | _, errors ->
        errors |> List.map (fun (msg, (y, x)) -> sprintf "// %A %s%s" (y + 1, x + 1) msg eol) |> String.concat ""
    do!
      IO.File.WriteAllTextAsync(
        IO.Path.Combine(testsDir.Value, category, case, case + ".c"),
        content
      ) |> Async.AwaitTask
  }

let collectTestTargets () =
  seq {
    for category in IO.Directory.GetDirectories(testsDir.Value) do
      // features, examples, etc.
      let category = Path.GetFileName(category)
      let categoryDir = Path.Combine(testsDir.Value, category)
      for case in IO.Directory.GetDirectories(categoryDir) do
        let case = Path.GetFileName(case)
        yield [|category :> obj; case :> obj|]
  }

[<Theory>]
[<MemberData("collectTestTargets")>]
let integrationTests (category: string) (case: string) =
  testFile category case
