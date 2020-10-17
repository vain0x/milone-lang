/// Entry point of the milone-lang compiler.
module rec MiloneLang.EntryPoint

open MiloneLang.Polyfills
open MiloneLang.Cli

let argCount (): int = (__nativeFun "arg_count" 1) ()

let argGet (i: int): string = (__nativeFun "arg_get" 1) i

let fileReadAllText (filePath: string): string =
  (__nativeFun "file_read_all_text" 1) filePath

let argList () =
  let rec go acc i =
    if i = 0 then acc else go (argGet (i - 1) :: acc) (i - 1)

  go [] (argCount ())

[<EntryPoint>]
let main _ =
  let args = argList ()
  cli fileReadAllText args
