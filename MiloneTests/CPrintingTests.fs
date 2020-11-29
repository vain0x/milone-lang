module MiloneLang.CPrintingTests

open System
open System.IO
open MiloneLang.Assets
open MiloneLang.Cli
open MiloneLang.Program
open Xunit

let private testFile category case =
  async {
    let dirPath =
      IO.Path.Combine(testsDir.Value, category, case)

    let host =
      let miloneHome = IO.Path.Combine(testsDir.Value, "..")
      dotnetCliHost [] miloneHome

    let _ok, content =
      compile (compileCtxNew host Quiet dirPath)

    do! IO.File.WriteAllTextAsync(IO.Path.Combine(testsDir.Value, category, case, case + ".c"), content)
        |> Async.AwaitTask
  }

let private collectTestTargets () =
  seq {
    for category in IO.Directory.GetDirectories(testsDir.Value) do
      // features, examples, etc.
      let category = Path.GetFileName(category)
      let categoryDir = Path.Combine(testsDir.Value, category)
      for case in IO.Directory.GetDirectories(categoryDir) do
        let case = Path.GetFileName(case)
        yield [| category :> obj; case :> obj |]
  }

[<Theory>]
[<MemberData("collectTestTargets")>]
let integrationTests (category: string) (case: string) = testFile category case
