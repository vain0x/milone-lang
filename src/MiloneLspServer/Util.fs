module MiloneLspServer.Util

open System.Collections.Generic

// -----------------------------------------------
// Array
// -----------------------------------------------

let partition1 (f: 'T -> 'U option) (items: #seq<'T>) : 'U array * 'T array =
  let someItems = ResizeArray()
  let noneItems = ResizeArray()

  for item in items do
    match f item with
    | Some x -> someItems.Add(x)
    | None -> noneItems.Add(item)

  someItems.ToArray(), noneItems.ToArray()

let partition2 (f: 'T -> Result<'U, 'E>) (items: #seq<'T>) : 'U array * 'E array =
  let ok = ResizeArray()
  let error = ResizeArray()

  for item in items do
    match f item with
    | Ok x -> ok.Add(x)
    | Error e -> error.Add(e)

  ok.ToArray(), error.ToArray()

// -----------------------------------------------
// ResizeArray
// -----------------------------------------------

module ResizeArray =
  let assign (items: #seq<_>) (array: ResizeArray<_>) : unit =
    array.Clear()
    array.AddRange(items)

// -----------------------------------------------
// MutSet
// -----------------------------------------------

type MutSet<'T when 'T: equality> = HashSet<'T>

module MutSet =
  let empty<'T when 'T: equality> () : MutSet<'T> = MutSet()

  let isEmpty (set: MutSet<_>) : bool = set.Count = 0

  let length (set: MutSet<_>) : int = set.Count

  let contains item (set: MutSet<_>) : bool = set.Contains(item)

  let ofSeq (items: #seq<_>) : MutSet<_> = System.Linq.Enumerable.ToHashSet(items)

  let toSeq (set: MutSet<_>) : seq<_> = set :> seq<_>

  /// Returns true if newly inserted.
  let insert item (set: MutSet<_>) : bool = set.Add(item)

  /// Returns true if actually removed.
  let remove item (set: MutSet<_>) : bool = set.Remove(item)

  let toList (set: MutSet<_>) : _ list = Seq.toList set

// -----------------------------------------------
// MutMap
// -----------------------------------------------

type MutMap<'K, 'T> = Dictionary<'K, 'T>

module MutMap =
  let empty<'K, 'T when 'K: equality> () : MutMap<'K, 'T> = MutMap()

  let isEmpty (map: MutMap<_, _>) : bool = map.Count = 0

  let length (map: MutMap<_, _>) : int = map.Count

  let containsKey key (map: MutMap<_, _>) : bool = map.ContainsKey(key)

  let tryFind key (map: MutMap<_, _>) : _ option =
    match map.TryGetValue(key) with
    | true, value -> Some value
    | false, _ -> None

  let keys (map: MutMap<_, _>) : seq<_> = map.Keys :> seq<_>

  let values (map: MutMap<_, _>) : seq<_> = map.Values :> seq<_>

  let entries (map: MutMap<_, _>) : seq<_ * _> =
    seq { for KeyValue (key, value) in map -> key, value }

  let insert key value (map: MutMap<_, _>) =
    match map.TryGetValue(key) with
    | true, removed ->
      map.[key] <- value
      Some removed

    | false, _ ->
      map.Add(key, value)
      None

  let remove key (map: MutMap<_, _>) =
    match map.TryGetValue(key) with
    | true, removed ->
      map.Remove(key) |> ignore
      Some removed

    | false, _ -> None

// -----------------------------------------------
// MutMultimap
// -----------------------------------------------

type MutMultimap<'K, 'T when 'K: equality> = Dictionary<'K, ResizeArray<'T>>

module MutMultimap =
  let empty<'K, 'T when 'K: equality> () = MutMultimap<'K, 'T>()

  let insertKey key (multimap: MutMultimap<_, _>) =
    if multimap.ContainsKey(key) |> not then
      multimap.Add(key, ResizeArray())

  let insert key value (multimap: MutMultimap<_, _>) =
    match multimap.TryGetValue(key) with
    | true, values -> values.Add(value)

    | false, _ -> multimap.Add(key, ResizeArray([ value ]))

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
