module rec native_code.Program

// Embedding arbitrary C codes.
// See also x_native_code.md in docs.

open Std.Ptr

__nativeDecl
  """
    // Embedded by __nativeDecl on toplevel.
  """

let private writeLine (msg: string) : unit =
  __nativeDecl
    """
      // Embedded by __nativeDecl in function.
      #include <stdio.h>
    """

  __nativeStmt (
    """
      fprintf(stdout, "%s\n", string_to_c_str({0}));
    """,
    msg
  )

let private freshId () : int =
  __nativeStmt
    """
    static int s_last;
  """

  __nativeExpr "++s_last"

let private nativeExprWithPlaceholder () =
  let s = "hello"
  let n: int = __nativeExpr ("{0}.len", s)
  assert (n = 5)

// (__type: T) is type placeholder. Embed type name.
let private alignOf (_: nativeptr<'T>) : unativeint =
  __nativeStmt ("typedef {0} T;", (__type: 'T))
  __nativeExpr "_Alignof(T)"

let private nativeStmtWithTyPlaceholder () =
  assert (alignOf (Ptr.nullPtr: nativeptr<char>) = 1un)
  assert (alignOf (Ptr.nullPtr: nativeptr<int>) = 4un)
  assert (alignOf (Ptr.nullPtr: nativeptr<int -> unit>) = 8un)

type private R = { X: int }

let private getX (r: nativeptr<R>) : int = (Ptr.read r).X

__nativeDecl (
  """
    int32_t {1}({0} *r);

    int32_t getX({0} *r) {
      return {1}(r);
    }
  """,
  (__type: R),
  &&getX
)

let main _ =
  writeLine "HEY!"
  writeLine "YO!"
  writeLine (freshId () |> string)
  writeLine (freshId () |> string)
  nativeExprWithPlaceholder ()
  nativeStmtWithTyPlaceholder ()
  0
