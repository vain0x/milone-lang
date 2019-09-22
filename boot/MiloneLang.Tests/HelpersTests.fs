module MiloneLang.HelpersTests

open MiloneLang.Assets
open MiloneLang.Helpers
open Xunit

[<Fact>]
let analyzeFormatTests () =
  analyzeFormat "Brave 100%%"
  |> is (tyFun tyStr tyUnit)

  analyzeFormat "Hello, %s!"
  |> is (tyFun tyStr (tyFun tyStr tyUnit))

  analyzeFormat "Welcome to %s. Entry price is %c%d!"
  |> is (tyFun tyStr (tyFun tyStr (tyFun tyChar (tyFun tyInt tyUnit))))
