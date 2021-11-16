/// Defines milone-lang primitives for F#.
[<AutoOpen>]
module FSharpOnly

module E = MiloneStd.StdError

let __inRegion (f: unit -> int) : int = f ()

let __dump value = E.__dump value
let __trace msg = E.__trace msg
let __context info action = E.__context info action
let unreachable (info: obj) = E.unreachable info
let todo (info: obj) = E.todo info

// -----------------------------------------------
// C FFI
// -----------------------------------------------

/// `T const *` in C.
[<AbstractClass; Sealed>]
type __constptr<'T> =
  override _.ToString() = "__constptr is not available in F#"

  static member op_Implicit(_: __constptr<'T>) : int = 0
  static member op_Implicit(_: __constptr<'T>) : unativeint = unativeint 0

/// C-ABI function pointer type: `T (*)(params...)` in C.
///
/// P is `()` or `P1 * P2 * ...`.
[<AbstractClass; Sealed>]
type __nativeFun<'P, 'T> =
  override _.ToString() =
    failwith "__nativeFun type is not available in F#"

// Calls a C function, which should be linked statically.
let __nativeFun _ =
  failwith "__nativeFun is not available in F#"

// Casts a pointer, unchecked.
let __nativeCast _ =
  failwith "__nativeCast is not available in F#"

/// Accesses to `ptr[i]` to read a value.
let __ptrRead (_ptr: __constptr<'a>) (_index: int) : 'a =
  failwith "__ptrRead is not available in F#"

/// Writes a value to `ptr[i]`.
let __ptrWrite (_ptr: nativeptr<'a>) (_index: int) (_value: 'a) : unit =
  failwith "__ptrWrite is not available in F#"
