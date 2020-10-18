module MiloneLsp.LspLangService

open MiloneLang.Types

// ---------------------------------------------
// Document store
// ---------------------------------------------

type TokenizeResult = (Token * Loc) list

type ParseResult = AExpr * (string * Loc) list

type DocData =
  { Uri: string
    Version: int
    Text: string
    mutable TokenizeResultOpt: TokenizeResult option
    mutable ParseResultOpt: ParseResult option }

let docs =
  System.Collections.Generic.Dictionary<string, DocData>()

let findDoc (uri: string): DocData option =
  match docs.TryGetValue(uri) with
  | true, docData -> Some docData
  | false, _ -> None

let openDoc (uri: string) (version: int) (text: string) =
  let docData: DocData =
    { Uri = uri
      Version = version
      Text = text
      TokenizeResultOpt = None
      ParseResultOpt = None }

  eprintfn "INFO: Document opened uri:'%s' v:%d len:%d" uri version text.Length
  docs.Add(uri, docData)

let changeDoc (uri: string) (version: int) (text: string): unit =
  match findDoc uri with
  | Some _ ->
      let docData =
        { Uri = uri
          Version = version
          Text = text
          TokenizeResultOpt = None
          ParseResultOpt = None }

      eprintfn "INFO: Document changed uri:'%s' v:%d len:%d" uri version text.Length
      docs.[uri] <- docData

  | None -> openDoc uri version text

let closeDoc (uri: string): unit =
  eprintfn "INFO: Document closed uri:'%s'" uri
  docs.Remove(uri) |> ignore

// ---------------------------------------------
// Analysis
// ---------------------------------------------

let tokenizeWithCaching (docData: DocData): TokenizeResult =
  match docData.TokenizeResultOpt with
  | Some it -> it

  | None ->
      let result = MiloneLang.Lexing.tokenize docData.Text
      docData.TokenizeResultOpt <- Some result
      result

let parseWithCaching (docData: DocData): ParseResult =
  match docData.ParseResultOpt with
  | Some it -> it

  | None ->
      let tokens = tokenizeWithCaching docData
      let result = MiloneLang.Parsing.parse tokens
      docData.ParseResultOpt <- Some result
      result

let validateDoc (uri: string): (string * Loc) list =
  match findDoc uri with
  | Some docData ->
      let _, errors = parseWithCaching docData
      errors

  | None -> []
