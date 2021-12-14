module rec native_code.Program

// Embedding arbitrary C codes.

let writeLine (msg: string) : unit =
  __nativeDecl
    """
      // Embedded by __nativeDecl.
      #include <stdio.h>
  """

  __nativeStmt (
    """
      fprintf(stdout, "%s\n", str_to_c_str({0}));
    """,
    msg
  )

let freshId () : int =
  __nativeStmt
    """
    static int s_last;
  """

  __nativeExpr "++s_last"

let private nativeExprWithPlaceholder () =
  let s = "hello"
  let n: int = __nativeExpr ("{0}.len", s)
  assert (n = 5)

let private nativeStmtWithTyPlaceholder () =
  // (_: T) is type placeholder. Embed type name.
  let alignOf (_: nativeptr<'T>) : unativeint =
    __nativeStmt ("typedef {0} T;", (_: 'T))
    __nativeExpr "_Alignof(T)"

  assert (alignOf (__nativeCast 0n: nativeptr<char>) = 1un)
  assert (alignOf (__nativeCast 0n: nativeptr<int>) = 4un)
  assert (alignOf (__nativeCast 0n: nativeptr<int -> unit>) = 8un)

let main _ =
  writeLine "HEY!"
  writeLine "YO!"
  writeLine (freshId () |> string)
  writeLine (freshId () |> string)
  nativeExprWithPlaceholder ()
  nativeStmtWithTyPlaceholder ()
  0
