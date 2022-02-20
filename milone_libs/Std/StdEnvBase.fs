module rec Std.StdEnvBase

open System

let internal getArgCount () : int = Environment.GetCommandLineArgs().Length

let internal getArg (index: int) : string =
  Environment.GetCommandLineArgs().[index]
