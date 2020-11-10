module MiloneLang.Assets

open System
open System.IO
open Xunit

let inline is<'T> (expected: 'T) (actual: 'T) = Assert.Equal(expected, actual)

let testsDir =
  lazy
    (
     let rec go (dir: string) =
       if File.Exists(Path.Combine(dir, "milone_lang.sln"))
       then Path.Combine(dir, "boot/tests")
       else Path.GetDirectoryName(dir) |> go

     go Environment.CurrentDirectory)
