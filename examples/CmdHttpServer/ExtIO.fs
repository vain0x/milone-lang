// IO and files

module rec CmdHttpServer.ExtIO

open CmdHttpServer.ExtBuffer

type File = __nativeType<``struct File``>

type ReadableFileStream = ReadableFileStream of File

module ReadableFileStream =
  let exists (filePath: string) (followLink: bool) : bool =
    __nativeFun ("milone_file_exists", filePath, followLink)

  let doOpen (filePath: string) : ReadableFileStream option =
    let file : File =
      __nativeFun ("milone_file_open", filePath, "r")

    if __nativeFun ("milone_file_is_null", file) then
      None
    else
      Some(ReadableFileStream file)

  let doClose (ReadableFileStream file) : unit = __nativeFun ("milone_file_close", file)

  // Returns read size in bytes.
  let doRead (dest: SpanMut) (ReadableFileStream file) : unativeint =
    __nativeFun ("milone_file_read", file, dest)

  let readAllText (filePath: string) : string option =
    match doOpen filePath with
    | None -> None
    | Some fp ->
        let itemSize = unativeint 1
        let chunkLen = unativeint 64

        let contents = Buffer.create (unativeint 1024) itemSize

        let chunk =
          Buffer.zeroCreate chunkLen itemSize
          |> Buffer.sliceMut (unativeint 0) chunkLen itemSize

        let rec go contents =
          let n = doRead chunk fp

          if n = unativeint 0 then
            contents
          else
            let chunk =
              chunk |> SpanMut.asConst |> Span.take n itemSize

            contents |> Buffer.append chunk itemSize |> go

        let contents = go contents |> Buffer.asString

        doClose fp
        Some contents

module Directory =
  let exists (path: string) (followLink: bool) : bool =
    __nativeFun ("milone_dir_exists", path, followLink)
