/// Defines milone-lang primitives for F#.
[<AutoOpen>]
module FSharpOnly


// -----------------------------------------------
// C FFI
// -----------------------------------------------

/// `T const *` in C.
[<AbstractClass; Sealed>]
type __inptr<'T> =
  override _.ToString() = "__inptr is not available in F#"

  static member op_Implicit(_: __inptr<'T>) : int = 0
  static member op_Implicit(_: __inptr<'T>) : unativeint = unativeint 0

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

module Std =
  module Ptr =
    /// Derives a pointer to its component.
    let select (_ptr: _) = failwith "Ptr.select not available"

    /// Reads a value from a pointer.
    let read (_ptr: _) = failwith "Ptr.read not available"

    /// Writes a value into a pointer.
    let write (_ptr: nativeptr<'T>) (_: 'T) : unit = failwith "Ptr.write not available"

  module Region =
    module Region =
      let run (f: unit -> int) : int = f ()
