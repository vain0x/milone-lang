open System
open System.IO
open System.Net.Http

let private helpText () = """DownloadText <URL> -o <OUTPUT>"""

let private cli (url: string) output =
  let url =
    try
      Uri(url)
    with
    | _ -> failwith "ERROR: URL can't parse."

  async {
    use client = new HttpClient()
    let! stream = client.GetStreamAsync(url) |> Async.AwaitTask
    use writer = File.OpenWrite(output)
    do! stream.CopyToAsync(writer) |> Async.AwaitTask
  }
  |> Async.RunSynchronously

match (Environment.GetCommandLineArgs()).[2..]
      |> Array.toList
  with
| []
| "-h" :: _
| "--help" :: _ -> printfn "%s" (helpText ())

| url :: args ->
  let output =
    match args with
    | "-o" :: output :: _ -> output
    | _ ->
      eprintfn "-o missing"
      exit 1

  cli url output
