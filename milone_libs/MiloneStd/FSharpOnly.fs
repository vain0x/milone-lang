/// Provides functions, whose implementations use .NET features and work only in F#.
/// Public interface of this module should be compatible with file://./MiloneOnly.milone .
[<AutoOpen>]
module rec MiloneStd.FSharpOnly

open System

// -----------------------------------------------
// StrEnv
// -----------------------------------------------

let __argCount () : int = Environment.GetCommandLineArgs().Length

let __argGet (index: int) : string =
  Environment.GetCommandLineArgs().[index]
