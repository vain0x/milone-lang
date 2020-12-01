/// Defines milone-lang primitives for F#.
[<AutoOpen>]
module FSharpOnly

let objToString (value: _) = string (value :> obj)

let inRegion (f: unit -> int): int = f ()

let strJoin (sep: string) (xs: string list): string = System.String.Join(sep, xs)

// -----------------------------------------------
// C FFI
// -----------------------------------------------

// `T const *` in C.
[<AbstractClass; Sealed>]
type constptr<'T> =
  override _.ToString() = "constptr is not available in F#"

  static member op_Implicit(_: constptr<'T>): int = 0
  static member op_Implicit(_: constptr<'T>): unativeint = unativeint 0

// `void const *` in C.
[<AbstractClass; Sealed>]
type voidconstptr =
  override _.ToString() = "voidconstptr is not available in F#"

  static member op_Implicit(_: voidconstptr): int = 0
  static member op_Implicit(_: voidconstptr): unativeint = unativeint 0

// Calls a C function, which should be linked statically.
let __nativeFun _ =
  failwith "__nativeFun is not available in F#"

// Casts a pointer, unchecked.
let __nativeCast _ =
  failwith "__nativeCast is not available in F#"

// -----------------------------------------------
// Profiler
// -----------------------------------------------

[<NoEquality; NoComparison>]
type Profiler = Profiler of System.Diagnostics.Stopwatch * int64 ref

let private getAllocatedBytes (): int64 =
  System.GC.GetAllocatedBytesForCurrentThread()

let profileInit (): Profiler =
  let bytesRef = getAllocatedBytes () |> ref
  Profiler(System.Diagnostics.Stopwatch.StartNew(), bytesRef)

let profileLog (msg: string) (Profiler (stopwatch, bytesRef)): unit =
  let millis = int stopwatch.ElapsedMilliseconds
  let sec = millis / 1000
  let millis = millis % 1000

  let totalBytes = getAllocatedBytes ()

  let bytes =
    (totalBytes - (!bytesRef)) |> int |> max 0

  let kilo = bytes / 1000
  let bytes = bytes % 1000
  let mega = kilo / 1000
  let kilo = kilo % 1000

  eprintfn "profile: time=%4d.%03d mem=%5d,%03d,%03d\n%s" sec millis mega kilo bytes msg

  stopwatch.Restart()
  bytesRef := totalBytes
