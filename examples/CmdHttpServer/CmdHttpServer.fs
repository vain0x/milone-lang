module rec CmdHttpServer.EntryPoint

open CmdHttpServer.Ffi
open CmdHttpServer.ExtIO

module S = MiloneStd.StdString

// FIXME: Return other status code if error.
let handler (methodName: string) (pathname: string): string =
  match methodName with
  | "GET" ->
      if pathname |> S.contains ".." then
        "ERROR: File path with .. is rejected.\n"
      else
        let path = "." + pathname
        let followLink = false

        if ReadableFileStream.exists path followLink |> not then
          "ERROR: File not found.\n"
        else
          match ReadableFileStream.readAllText path with
          | Some contents -> contents
          | None -> "ERROR: File cannot read.\n"

  | _ ->
      "ERROR: Method not implemented: "
      + methodName
      + ".\n"

let main _ =
  __nativeFun ("do_serve", __nativeFun handler)
