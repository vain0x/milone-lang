[<AutoOpen>]
module CmdHttpServer.FSharpOnly

open System.IO

let __fileExists (_filePath: string) (_followLink: bool): bool = failwith "unimplemented"

let __fileReadAllText (_filePath: string): string option = failwith "unimplemented"
