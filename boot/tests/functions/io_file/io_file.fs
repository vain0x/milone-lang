let fileReadAllText (fileName: string): string =
  (__nativeFun "file_read_all_text" 1) fileName

let fileWriteAllText (fileName: string) (content: string): unit =
  (__nativeFun "file_write_all_text" 2) fileName content

let main _ =
  let content = fileReadAllText "boot/tests/functions/io_file/input.txt"
  assert (content = "hello\n")

  let content = content + "world\n"
  fileWriteAllText "boot/tests/functions/io_file/output.txt" content

  0
