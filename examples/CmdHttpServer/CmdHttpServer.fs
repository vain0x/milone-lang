module rec CmdHttpServer.EntryPoint

open CmdHttpServer.Ffi

let handler (methodName: string) (pathname: string): string =
  "I have received a request with methodName='"
  + methodName
  + "', pathname='"
  + pathname
  + "'.\n"

let main _ =
  __nativeFun ("do_serve", __nativeFun handler)
