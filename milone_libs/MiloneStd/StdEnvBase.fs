module rec MiloneStd.StdEnvBase

open System

let __argCount () : int = Environment.GetCommandLineArgs().Length

let __argGet (index: int) : string =
  Environment.GetCommandLineArgs().[index]
