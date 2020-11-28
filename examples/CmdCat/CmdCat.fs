module rec CmdCat.Program

open CmdCat.Ffi

// -----------------------------------------------
// Util
// -----------------------------------------------

let ignore _ = ()

let failwith msg =
  printfn "ERROR: %s" msg
  exit 1

let guard f cond = if not cond then f ()

let unwrapOrElse f opt =
  match opt with
  | Some it -> it
  | None -> f ()

// -----------------------------------------------
// Application logic
// -----------------------------------------------

/// Reads a file and writes its contents to STDOUT.
let doCatFile profiler path =
  // profileLog ("OPEN: " + path) profiler

  let fd =
    fileOpenRead path
    |> unwrapOrElse (fun () -> failwith ("open: '" + path + "'"))

  let rec go () =
    // profileLog "READ" profiler

    let buf =
      fileReadBytes 1000 fd
      |> unwrapOrElse (fun () -> failwith ("read: '" + path + "'"))

    if buf.Length > 0 then
      fileWriteBytes buf stdoutFd
      |> guard (fun () -> failwith "write to STDOUT")

      go ()

  go ()

  fileClose fd
  |> guard (fun () -> failwith ("close: '" + path + "'"))

// profileLog "CLOSED" profiler

let main _ =
  let args = getArgs ()

  (args |> List.isEmpty |> not)
  |> guard (fun () -> failwith "file not specified")

  let profiler = profileInit ()
  // profileLog "START" profiler

  args
  |> List.iter (fun arg -> doCatFile profiler arg)

  // profileLog "FINISH" profiler
  0
