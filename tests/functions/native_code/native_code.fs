module rec native_code.Program

// Embedding arbitrary C codes.

let writeLine (msg: string): unit =
  __nativeDecl """
      // Embedded by __nativeDecl.
      #include <stdio.h>

      static int s_write_count;

      void write_line(struct String s) {
          fprintf(stdout, "%s\n", s.str);
      }
  """

  __nativeStmt """
      s_write_count++;
  """

  __nativeFun ("write_line", msg)

let getWriteCount (): int = __nativeExpr "s_write_count"

let main _ =
  writeLine "HEY!"
  writeLine "YO!"
  writeLine (getWriteCount () |> string)
  0
