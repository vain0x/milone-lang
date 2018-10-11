module MiloneLang.Assets

open System
open System.IO
open Xunit

let inline is<'T> (expected: 'T) (actual: 'T) =
  Assert.Equal(expected, actual)

let testsDir = lazy (
  let rec go (dir: string) =
    if IO.Path.GetFileName(dir) = "boot" then
      IO.Path.Combine(dir, "tests")
    else
      IO.Path.GetDirectoryName(dir) |> go
  go Environment.CurrentDirectory
)
