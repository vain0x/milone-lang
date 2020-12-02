module rec CmdCat.Ffi

let strAsPtr (s: string): __constptr<char> = __nativeFun ("str_as_ptr", s)

type Profiler = Profiler of obj

let profileInit (): Profiler =
  let state: obj = __nativeFun "milone_profile_init"
  Profiler state

let profileLog (msg: string) (Profiler state): unit =
  __nativeFun ("milone_profile_log", msg, state)

type Buffer = { Ptr: __voidconstptr; Length: int }

/// buf: Buffer *
let bufferRefNew (buf: __voidconstptr): Buffer =
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
  let buf: __voidconstptr =
    __nativeFun ("file_read_bytes", fd, size)

  if unativeint buf <> unativeint 0 then Some(bufferRefNew buf) else None

let fileWriteBytes (buf: Buffer) (Fd fd): bool =
  let writtenLen: int =
    __nativeFun ("file_write_bytes", fd, buf.Ptr)

  writtenLen >= 0

let getArgs (): string list =
  let argc: int = __nativeFun "arg_count"

  let argv (i: int): string = __nativeFun ("arg_get", i)

  let rec go acc i =
    if i < argc then go (argv i :: acc) (i + 1) else List.rev acc

  go [] 0
