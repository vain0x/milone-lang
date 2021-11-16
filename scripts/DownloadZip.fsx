open System
open System.Net.Http
open System.IO.Compression

let private helpText () = """DownloadZip <URL> -o <OUTPUT-DIR>"""

let private cli (url: string) outputDir =
  let url =
    try
      Uri(url)
    with
    | _ -> failwith "ERROR: URL can't parse."

  async {
    use client = new HttpClient()
    client.DefaultRequestHeaders.Accept.Add(Headers.MediaTypeWithQualityHeaderValue("application/zip"))

    let! stream = client.GetStreamAsync(url) |> Async.AwaitTask
    use zip = new ZipArchive(stream)
    zip.ExtractToDirectory(outputDir)
  }
  |> Async.RunSynchronously

match (Environment.GetCommandLineArgs()).[2..]
      |> Array.toList with
| []
| "-h" :: _
| "--help" :: _ -> printfn "%s" (helpText ())

| url :: args ->
  let outputDir =
    match args with
    | "-o" :: outputDir :: _ -> outputDir
    | _ ->
      eprintfn "-o missing"
      exit 1

  cli url outputDir
