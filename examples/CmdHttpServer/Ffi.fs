module rec CmdHttpServer.Ffi

let strAsPtr (s: string): __constptr<char> = __nativeFun ("str_as_ptr", s)

type Profiler = Profiler of voidptr

let profileInit (): Profiler =
  let state: voidptr = __nativeFun "milone_profile_init"
  Profiler state

let profileLog (msg: string) (Profiler state): unit =
  __nativeFun ("milone_profile_log", msg, state)

let getArgs (): string list =
  let argc: int = __nativeFun "arg_count"

  let argv (i: int): string = __nativeFun ("arg_get", i)

  let rec go acc i =
    if i < argc then go (argv i :: acc) (i + 1) else List.rev acc

  go [] 0
