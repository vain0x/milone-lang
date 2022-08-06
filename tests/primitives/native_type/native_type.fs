module rec native_type.Program

// - __nativeType<``ANY C TYPE``> is expanded to `ANY C TYPE` in C.
// - Opaque types are compiled to incomplete struct types in C.
// See also x_native_code.md in docs.

open Std.Ptr

type FILE = __nativeType<FILE>

[<Opaque>]
type OpaqueStruct = private | OS

let strAsPtr (s: string) : InPtr<char> = __nativeFun ("string_as_ptr", s)

let fopen (filename: string) (mode: string) : nativeptr<FILE> =
  __nativeFun ("fopen", strAsPtr filename, strAsPtr mode)

let fclose (fp: nativeptr<FILE>) : int = __nativeFun ("fclose", fp)

let private testOpaqueStruct () =
  let opt: option<nativeptr<OpaqueStruct>> = Some Ptr.nullPtr
  ()

let main _ =
  let fp = fopen "LICENSE" "r"
  assert (fp <> Ptr.nullPtr)

  let stat = fclose fp
  assert (stat = 0)
  0
