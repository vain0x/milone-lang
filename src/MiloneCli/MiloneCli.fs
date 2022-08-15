/// Entry point of the milone-lang compiler.
module MiloneCli.Program

open MiloneCli.Cli
open MiloneCli.FSharpOnly
open MiloneSyntax.SyntaxApi
open MiloneTranslation.TranslationApi

[<EntryPoint>]
let main _ =
  cli (newSyntaxApi ()) (newTranslationApi ()) (dotnetCliHost ())
