module rec CmdHttpServer.EntryPoint

open CmdHttpServer.Ffi

let main _ = __nativeFun "do_serve"
