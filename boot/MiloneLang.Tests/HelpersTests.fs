module MiloneLang.HelpersTests

open MiloneLang
open MiloneLang.Assets
open MiloneLang.Helpers
open Xunit

[<Fact>]
let analyzeFormatTests () =
  analyzeFormat "Brave 100%%"
  |> is (Ty.Fun (Ty.Str, Ty.Unit))

  analyzeFormat "Hello, %s!"
  |> is (Ty.Fun (Ty.Str, Ty.Fun (Ty.Str, Ty.Unit)))

  analyzeFormat "Welcome to %s. Entry price is %c%d!"
  |> is (Ty.Fun (Ty.Str, Ty.Fun (Ty.Str, Ty.Fun (Ty.Char, Ty.Fun (Ty.Int, Ty.Unit)))))
