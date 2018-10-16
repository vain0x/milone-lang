module MiloneLang.CPrintingTests

open System
open System.IO
open MiloneLang.Assets
open Xunit

let testFile fileName =
  async {
    let! source =
      IO.File.ReadAllTextAsync(
        IO.Path.Combine(testsDir.Value, "src", fileName + ".milone")
      ) |> Async.AwaitTask
    let content =
      let cir = Program.toCir source
      CPrinting.cprintRun (fun acc -> CPrinting.cprintDecls acc cir)
    do!
      IO.File.WriteAllTextAsync(
        IO.Path.Combine(testsDir.Value, "c", fileName + ".c"),
        content
      ) |> Async.AwaitTask
  }

let collectTestTargets () =
  seq {
    let files = IO.Directory.GetFiles(Path.Combine(testsDir.Value, "src"), "*.milone")
    for file in files do
      let name = IO.Path.GetFileNameWithoutExtension(file)
      yield [|name :> obj|]
  }

[<Theory>]
[<MemberData("collectTestTargets")>]
let integrationTests (name: string) =
  testFile name
