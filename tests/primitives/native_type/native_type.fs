module rec native_type.Program

// __nativeType<``ANY C TYPE``> is expanded to `ANY C TYPE` in C.
// See also x_native_code.md in docs.

type FILE = __nativeType<FILE>

let strAsPtr (s: string) : __inptr<char> = __nativeFun ("str_as_ptr", s)

let fopen (filename: string) (mode: string) : nativeptr<FILE> =
  __nativeFun ("fopen", strAsPtr filename, strAsPtr mode)

let fclose (fp: nativeptr<FILE>) : int = __nativeFun ("fclose", fp)

let main _ =
  let fp = fopen "LICENSE" "r"
  assert (fp <> __nullptr)

  let stat = fclose fp
  assert (stat = 0)
  0
