module rec CmdHttpServer.EntryPoint

open CmdHttpServer.Ffi
open CmdHttpServer.ExtIO

module S = MiloneStd.StdString

// -----------------------------------------------
// HTTP Types
// -----------------------------------------------

type HttpError =
  | BadRequestError
  | NotFoundError
  | NotImplementedError
  | FoundError of location: string

type HttpResult =
  | Ok of okContent: string * okContentType: string
  | Error of status: HttpError * message: string

// -----------------------------------------------
// App
// -----------------------------------------------

let serverName = "httpd"

let serverVersion = "0.1.0"

let private doHandle (methodName: string) (pathname: string): HttpResult =
  let contentType () =
    let ext =
      match S.findLastIndex "." pathname with
      | Some i when i >= 1 -> S.skip i pathname
      | _ -> ""

    match ext with
    | ".css" -> "text/css; charset=utf-8"
    | ".html" -> "text/html; charset=utf-8"
    | ".js"
    | ".mjs" -> "text/javascript; charset=utf-8"

    | ".jpeg"
    | ".jpg" -> "image/jpeg"
    | ".png" -> "image/png"
    | ".woff" -> "font/woff"

    | ".json" -> "application/json; charset=utf-8"
    | _ -> "text/plain; charset=utf-8"

  match methodName with
  | "GET" ->
      if pathname |> S.contains ".." then
        Error(BadRequestError, "Path may not include '..'.")
      else
        let followLink = false

        if ReadableFileStream.exists pathname followLink then
          match ReadableFileStream.readAllText pathname with
          | Some contents -> Ok(contents, contentType ())
          | None -> Error(NotFoundError, "File cannot read.")
        else if Directory.exists pathname followLink
                && ReadableFileStream.exists (pathname + "/index.html") followLink then
          Error(FoundError "index.html", "Redirect.")
        else
          Error(NotFoundError, "File not found.")

  | _ -> Error(NotImplementedError, "Method not implemented.")

// -----------------------------------------------
// Runtime
// -----------------------------------------------

let handler
  (methodName: string)
  (pathname: string)
  (date: string)
  (distDir: string)
  (protocolMinorVersion: int)
  (writeString: string -> unit)
  (writeTrace: string -> unit)
  : unit =
  let writeCommonHeaders (statusText: string) =
    writeString (
      "HTTP/1."
      + string protocolMinorVersion
      + " "
      + statusText
      + "\r\n"
    )

    writeString ("Date: " + date + "\r\n")

    writeString (
      "Server: "
      + serverName
      + "/"
      + serverVersion
      + "\r\n"
    )

    writeString "Connection: close\r\n"

  let writeBody (content: string) (contentType: string): unit =
    writeString (
      "Content-Length: "
      + string content.Length
      + "\r\n"
    )

    writeString ("Content-Type: " + contentType + "\r\n\r\n")

    if methodName <> "HEAD" then
      writeString content

  let res =
    doHandle methodName (distDir + "/" + pathname)

  let statusText =
    match res with
    | Ok (content, contentType) ->
        let statusText = "200 OK"
        writeCommonHeaders statusText
        writeBody content contentType
        statusText

    | Error (err, _) ->
        let statusText, headers =
          match err with
          | FoundError location -> "302 Found", [ "Location", location ]
          | BadRequestError -> "400 Bad Request", []
          | NotFoundError -> "404 Not Found", []
          | NotImplementedError -> "501 Not Implemented", []

        writeCommonHeaders statusText

        let rec go headers =
          match headers with
          | [] -> ()
          | (header, text) :: headers ->
              writeString (header + ": " + text + "\r\n")
              go headers

        go headers

        writeBody "" "text/plain; charset=utf-8"
        statusText

  // Access log.
  writeTrace (
    "["
    + methodName
    + "] "
    + pathname
    + " - "
    + statusText
  )

let main _ =
  // Never return.
  __nativeFun ("do_serve", __nativeFun handler)

  0
