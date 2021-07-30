module rec CmdHttpServer.Ffi

module Env = MiloneStd.StdEnv

let strAsPtr (s: string) : __constptr<char> = __nativeFun ("str_as_ptr", s)

type Profiler = Profiler of voidptr

let profileInit () : Profiler =
  let state: voidptr = __nativeFun "milone_profile_init"
  Profiler state

let profileLog (msg: string) (Profiler state) : unit =
  __nativeFun ("milone_profile_log", msg, state)

let getArgs () : string list = Env.commandLineArgs ()
