module MiloneLspServer.Util

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
  | Info = 5
  | Debug = 7 // LOG_DEBUG
  | Trace = 8

let private logLevelEnv: string =
  let env =
    System.Environment.GetEnvironmentVariable("MILONE_LSP_SERVER_LOG_LEVEL")

  if not (isNull env) then
    eprintf "%s" $"debug: $MILONE_LSP_SERVER_LOG_LEVEL='{env}'\n"

  env

let private maxLevel: LogLevel =
  match logLevelEnv with
  | "debug" -> LogLevel.Debug
  | "trace" -> LogLevel.Trace
  | _ -> LogLevel.Warn

let private printLog (label: string) (level: LogLevel) fmt =
  Printf.kprintf
    (fun msg ->
      if level <= maxLevel then
        eprintf "%s" $"{label}: {msg}\n")
    fmt

let errorFn fmt = printLog "error" LogLevel.Error fmt
let warnFn fmt = printLog "warn" LogLevel.Warn fmt
let infoFn fmt = printLog "info" LogLevel.Info fmt
let debugFn fmt = printLog "debug" LogLevel.Debug fmt
let traceFn fmt = printLog "trace" LogLevel.Trace fmt
