module MiloneLang.CPrintingTests

open System
open System.IO
open MiloneLang.Assets
open MiloneLang.Program
open Xunit

let testFile category case =
  async {
    let! source =
      IO.File.ReadAllTextAsync(
        IO.Path.Combine(testsDir.Value, category, case, case + ".milone")
      ) |> Async.AwaitTask
    let content =
      let cir = toCir Verbosity.Silent source
      CPrinting.cprintRun (fun acc -> CPrinting.cprintDecls acc cir)
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
