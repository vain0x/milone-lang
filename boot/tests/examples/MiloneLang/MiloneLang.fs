module rec MiloneLang.Program

open MiloneLang.Polyfills
open MiloneLang.Lexing
open MiloneLang.Types
open MiloneLang.Self

let fileReadAllText (fileName: string): string =
  (__nativeFun "file_read_all_text" 1) fileName

[<EntryPoint>]
let main _ =
  doSelf fileReadAllText
