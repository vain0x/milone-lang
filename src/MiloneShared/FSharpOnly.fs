/// Defines milone-lang primitives for F#.
[<AutoOpen>]
module FSharpOnly

// -----------------------------------------------
// C FFI
// -----------------------------------------------

/// C-ABI function pointer type: `T (*)(params...)` in C.
///
/// P is `()` or `P1 * P2 * ...`.
[<AbstractClass; Sealed>]
type FunPtr<'P, 'T> =
  override _.ToString() =
    failwith "FunPtr type is not available in F#"

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

    module Ptr =
      /// `T const *` in C.
      [<AbstractClass; Sealed>]
      type InPtr<'T> =
        override _.ToString() = "InPtr is not available in F#"

        static member op_Implicit(_: InPtr<'T>) : int = 0
        static member op_Implicit(_: InPtr<'T>) : unativeint = unativeint 0

      /// `void const *` in C.
      type VoidInPtr = voidptr

      /// Non-readable `T *` in C.
      [<AbstractClass; Sealed>]
      type OutPtr<'T> =
        override _.ToString() = "OutPtr is not available in F#"

        static member op_Implicit(_: InPtr<'T>) : int = 0
        static member op_Implicit(_: InPtr<'T>) : unativeint = unativeint 0

  module Region =
    module Region =
      let run (f: unit -> int) : int = f ()
