module rec CmdCat.Ffi

module Env = MiloneStd.StdEnv

let strAsPtr (s: string): __constptr<char> = __nativeFun ("str_as_ptr", s)

type Profiler = Profiler of voidptr

let profileInit (): Profiler =
  let state: voidptr = __nativeFun "milone_profile_init"
  Profiler state

let profileLog (msg: string) (Profiler state): unit =
  __nativeFun ("milone_profile_log", msg, state)

type Buffer = { Ptr: obj; Length: int }

/// buf: Buffer const *
let bufferRefNew (buf: obj): Buffer =
  let len: int = __nativeFun ("buffer_get_length", buf)

  { Ptr = buf; Length = len }

/// File descriptor.
type Fd = Fd of int

let stdoutFd = Fd 1

let fileOpenRead (path: string): Fd option =
  let fd: int = __nativeFun ("file_open_read", path)
  if fd >= 0 then Some(Fd fd) else None

let fileClose (Fd fd): bool =
  let stat: int = __nativeFun ("close", fd)
  stat = 0

let fileReadBytes (size: int) (Fd fd): Buffer option =
  let buf: obj =
    __nativeFun ("file_read_bytes", fd, size)

  if __nativeCast buf <> unativeint 0 then Some(bufferRefNew buf) else None

let fileWriteBytes (buf: Buffer) (Fd fd): bool =
  let writtenLen: int =
    __nativeFun ("file_write_bytes", fd, buf.Ptr)

  writtenLen >= 0

let getArgs (): string list = Env.commandLineArgs ()
