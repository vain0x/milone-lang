module rec native_code.Program

// Embedding arbitrary C codes.

let writeLine (msg: string): unit =
  __nativeDecl """
      // Embedded by __nativeDecl.
      #include <stdio.h>
  """

  __nativeStmt (
    """
      fprintf(stdout, "%s\n", str_to_c_str({0}));
    """,
    msg
  )

let freshId (): int =
  __nativeStmt """
    static int s_last;
  """

  __nativeExpr "++s_last"

let main _ =
  writeLine "HEY!"
  writeLine "YO!"
  writeLine (freshId () |> string)
  writeLine (freshId () |> string)
  0
