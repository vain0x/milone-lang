/// Entry point of the milone-lang compiler.
module MiloneCli.Program

open MiloneCliCore.Cli
open MiloneCliCore.FSharpOnly
open MiloneSyntax.SyntaxApi
open MiloneTranslation.TranslationApi

[<EntryPoint>]
let main _ =
  cli (newSyntaxApi ()) (newTranslationApi ()) (dotnetCliHost ())
