module MiloneLsp.JsonRpcReaderForStdIn

/// Provides two functions for JSON RPC node to read data from stream.
/// (Not compliant with JSON-RPC, indeed.)
let jsonRpcReaderForStdIn () =
  let utf8 = System.Text.Encoding.UTF8
  let input = System.Console.OpenStandardInput()
  let reader = new System.IO.BinaryReader(input)

  let mutable buf = Array.zeroCreate 0x4000
  let mutable bufLen = 0
  let mutable closed = false

  let readBuffer () =
    if not closed then
      let len =
        reader.BaseStream.Read(buf, bufLen, buf.Length - bufLen)

      // eprintfn "read: %d (%d -> %d)" len bufLen (bufLen + len)
      if len <> 0 then
        bufLen <- bufLen + len
      else
        closed <- true

  let shrink len =
    // eprintfn "consume: %d (%d -> %d)" len bufLen (bufLen - len)
    System.Array.Copy(buf, len, buf, 0, bufLen - len)
    bufLen <- bufLen - len

  let rec readLine () =
    // eprintfn "readLine"
    if closed then
      None
    else
      let i =
        System.Array.FindIndex(buf, 0, bufLen, System.Predicate((=) (byte '\n')))

      if i >= 0 then
        let line =
          let len =
            if i >= 1 && buf.[i - 1] = byte '\r' then
              i - 1
            else
              i

          utf8.GetString(buf, 0, len)

        shrink (i + 1)
        Some line
      else
        readBuffer ()
        readLine ()

  let rec readBytes len =
    // eprintfn "readBytes %d" len
    if len > buf.Length / 2 then
      System.Array.Resize(&buf, len * 2)

    if bufLen >= len then
      let data = buf.[0..len]
      shrink len
      Some data

    else if closed then
      None

    else
      readBuffer ()
      readBytes len

  readLine, readBytes
