module MiloneLspServer.Util

open MiloneShared.UtilParallel

// -----------------------------------------------
// IO
// -----------------------------------------------

module File =
  open System.IO

  let tryReadFile (filePath: string) =
    try
      if File.Exists(filePath) then
        System.IO.File.ReadAllText(filePath) |> Some
      else
        None
    with
    | _ -> None

  let readTextFile (filePath: string) : Future<string option> =
    try
      if System.IO.File.Exists(filePath) then
        System.IO.File.ReadAllTextAsync(filePath)
        |> Future.ofTask
        |> Future.map Some
      else
        Future.just None
    with
    | _ -> Future.just None

// -----------------------------------------------
// MD5
// -----------------------------------------------

module Md5Helper =
  let private hasher =
    new System.Threading.ThreadLocal<System.Security.Cryptography.MD5>(fun () ->
      System.Security.Cryptography.MD5.Create())

  let private encoding = System.Text.Encoding.UTF8

  let ofString (s: string) : byte array =
    hasher.Value.ComputeHash(encoding.GetBytes(s))

  let equals (l: byte array) (r: byte array) : bool =
    System.Linq.Enumerable.SequenceEqual(l, r)

// -----------------------------------------------
// Logging
// -----------------------------------------------

type private LogLevel =
  | Error = 3
  | Warn = 4
  | Debug = 7 // LOG_DEBUG
  | Trace = 8

let private currentLogLevel: LogLevel =
  match System.Environment.GetEnvironmentVariable("MILONE_LSP_SERVER_LOG_LEVEL") with
  | "debug" -> LogLevel.Debug
  | "trace" -> LogLevel.Trace
  | _ -> LogLevel.Warn

let private printLog name (level: LogLevel) =
  fun fmt ->
    Printf.kprintf
      (fun msg ->
        if level <= currentLogLevel then
          eprintf "%s: %s" name (msg + "\n")
        else
          ())
      fmt

let errorFn fmt = printLog "error" LogLevel.Error fmt
let warnFn fmt = printLog "warn" LogLevel.Warn fmt
let infoFn fmt = printLog "info" LogLevel.Debug fmt // no such level
let debugFn fmt = printLog "debug" LogLevel.Debug fmt
let traceFn fmt = printLog "trace" LogLevel.Trace fmt
