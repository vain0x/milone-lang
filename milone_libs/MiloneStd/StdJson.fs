/// Provides JSON parser and dumper.

// Non-goals:
//    - Optimization
//    - Streaming
//    - Error recovery
//    - Multiple error reporting
//    - Non-standard JSON

// Thanks: pdjson is referred to implement this.
// <https://github.com/skeeto/pdjson/blob/67108d883061043e55d0fb13961ac1b6fc8a485c/pdjson.c>
// (Unlike pdjson, this module does trust input is valid utf-8.)

module rec MiloneStd.StdJson

open MiloneStd.StdError

module C = MiloneStd.StdChar
module S = MiloneStd.StdString
module JB = MiloneStd.StdJsonBase

let private cons x y = x :: y

// -----------------------------------------------
// Public types
// -----------------------------------------------

type JsonValue =
  | JNull
  | JString of stringValue: string
  | JNumber of numberValue: float
  | JBoolean of boolValue: bool
  | JArray of items: JsonValue list
  | JObject of entries: (string * JsonValue) list

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type JsonErrorKind =
  | ExpectedKey
  | ExpectedValue
  | ExpectedColon
  | ExpectedCommaOrRightBracket
  | ExpectedCommaOrRightBrace
  | UnterminatedString
  | UnescapedControlChar
  | InvalidEscapeSequence

[<NoEquality; NoComparison>]
type JsonParseResult =
  | ParseOk of JsonValue * endIndex: int
  | ParseErr of index: int * JsonErrorKind

// -----------------------------------------------
// String
// -----------------------------------------------

let private at i s =
  S.tryItem i s |> Option.defaultValue '\x00'

// #charNeedsEscaping
// bytes invalid as UTF-8 also need escaping
let private charNeedsEscaping (c: char) =
  c = '"'
  || c = '\\'
  || (byte c <= 0x78uy && byte c < 0x20uy)

// -----------------------------------------------
// Unicode
// -----------------------------------------------

let private evalUnicode (s: string) : string option =
  let rec allHex i =
    i = s.Length || (C.isHex s.[i] && allHex (i + 1))

  if s.Length < 4 || not (allHex 0) then
    // printfn "warn: \\u is not followed by four hex digits '%s'" s
    None
  else
    let codePoint =
      let rec go (n: int) i =
        if i = 4 then
          n
        else
          let shift = 12 - i * 4
          let n = n ||| ((C.evalHex s.[i]) <<< shift)
          go n (i + 1)

      go 0 0

    JB.encodeUtf8 codePoint

// -----------------------------------------------
// Escape sequence
// -----------------------------------------------

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private VerbatimSep =
  | Eof
  | Control
  | Quote
  | Backslash

let private readVerbatim (i: int) text =
  let rec go i =
    match at i text with
    | '"' -> i, VerbatimSep.Quote
    | '\\' -> i, VerbatimSep.Backslash

    | '\x00' when i >= text.Length -> i, VerbatimSep.Eof

    // #charNeedsEscaping
    | c when byte c <= 0x7fuy && byte c < 0x20uy -> i, VerbatimSep.Control

    | _ -> go (i + 1)

  go i

let private readEscape (i: int) (text: string) =
  assert (at i text = '\\')

  let ok i (s: string) =
    if i <= text.Length then
      Some(i, s)
    else
      None

  match at (i + 1) text with
  | 't' -> ok (i + 2) "\t"
  | 'r' -> ok (i + 2) "\r"
  | 'n' -> ok (i + 2) "\n"

  | 'b' -> ok (i + 2) "\x08" // backspace
  | 'f' -> ok (i + 2) "\x0c" // formfeed

  | '\\'
  | '/'
  | '\''
  | '"' -> ok (i + 2) text.[i + 1..i + 1]

  | 'u' ->
    let hex = text |> S.slice (i + 2) (i + 6)

    match evalUnicode hex with
    | Some s -> ok (i + 6) s
    | None -> None

  | _ -> None

// -----------------------------------------------
// Parse
// -----------------------------------------------

let private skipSpaces (i: int) (text: string) =
  match at i text with
  | ' ' when
    i + 4 <= text.Length
    && text.[i + 1] = ' '
    && text.[i + 2] = ' '
    && text.[i + 3] = ' '
    ->
    skipSpaces (i + 4) text

  | ' '
  | '\t'
  | '\r'
  | '\n' -> skipSpaces (i + 1) text

  | _ -> i

let private parseString (i: int) (text: string) =
  let rec go acc (i: int) =
    assert (i <= text.Length)

    let endIndex, sep = readVerbatim i text

    let acc =
      if i < endIndex then
        (text |> S.slice i endIndex) :: acc
      else
        acc

    let i = endIndex

    match sep with
    | VerbatimSep.Eof -> ParseErr(i, JsonErrorKind.UnterminatedString)
    | VerbatimSep.Control -> ParseErr(i, JsonErrorKind.UnescapedControlChar)

    | VerbatimSep.Quote ->
      let value =
        acc |> List.rev |> S.concat "" |> JString

      assert (at i text = '"')
      ParseOk(value, i + 1)

    | VerbatimSep.Backslash ->
      match readEscape i text with
      | Some (i, s) -> go (s :: acc) i
      | None -> ParseErr(i, JsonErrorKind.InvalidEscapeSequence)

  assert (at i text = '"')
  go [] (i + 1)

let private scanDigits (i: int) (text: string) =
  let rec go i =
    if C.isDigit (at i text) then
      go (i + 1)
    else
      i

  go i

let private parseNumber (i: int) (text: string) =
  let start = i

  let i = if at i text = '-' then i + 1 else i

  let i = scanDigits i text

  let i =
    if at i text = '.' then
      scanDigits (i + 1) text
    else
      i

  let i =
    match at i text with
    | 'e'
    | 'E' ->
      let i =
        match at (i + 1) text with
        | '-'
        | '+' -> i + 2
        | _ -> i + 1

      scanDigits i text

    | _ -> i

  let value =
    text |> S.slice start i |> float |> JNumber

  value, i

let parseArray (i: int) (text: string) =
  let rec go acc i =
    let i = skipSpaces i text

    match parseValue i text with
    | ParseOk (item, i) ->
      let i = skipSpaces i text
      let acc = item :: acc

      match at i text with
      | ',' -> go acc (i + 1)

      | ']' ->
        let value = JArray(List.rev acc)
        ParseOk(value, i + 1)

      | _ -> ParseErr(i, JsonErrorKind.ExpectedCommaOrRightBracket)

    | err -> err

  assert (text.[i] = '[')
  let i = skipSpaces (i + 1) text

  match at i text with
  | ']' -> ParseOk(JArray [], i + 1)
  | _ -> go [] i

let parseObject i (text: string) =
  let rec go acc i =
    let i = skipSpaces i text

    match at i text with
    | '"' ->
      match parseString i text with
      | ParseOk (JString key, i) ->
        let i = skipSpaces i text

        match at i text with
        | ':' ->
          let i = skipSpaces (i + 1) text

          match parseValue i text with
          | ParseOk (value, i) ->
            let i = skipSpaces i text
            let acc = (key, value) :: acc

            match at i text with
            | ',' -> go acc (i + 1)

            | '}' ->
              let value = JObject(List.rev acc)
              ParseOk(value, i + 1)

            | _ -> ParseErr(i, JsonErrorKind.ExpectedCommaOrRightBrace)

          | _ -> ParseErr(i, JsonErrorKind.ExpectedValue)

        | _ -> ParseErr(i, JsonErrorKind.ExpectedColon)

      | ParseOk _ -> unreachable () // parseString should return JString

      | err -> err

    | _ -> ParseErr(i, JsonErrorKind.ExpectedKey)

  assert (text.[i] = '{')
  let i = skipSpaces (i + 1) text

  match at i text with
  | '}' -> ParseOk(JObject [], i + 1)
  | _ -> go [] i

let private parseValue (i: int) (text: string) : JsonParseResult =
  let ok endIndex value =
    if endIndex <= text.Length then
      ParseOk(value, endIndex)
    else
      ParseErr(i, JsonErrorKind.ExpectedValue)

  match at i text with
  | '[' -> parseArray i text
  | '{' -> parseObject i text

  | '"' -> parseString i text

  | '-'
  | '.'
  | '0'
  | '1'
  | '2'
  | '3'
  | '4'
  | '5'
  | '6'
  | '7'
  | '8'
  | '9' -> parseNumber i text |> ParseOk

  | 'f' -> ok (i + 5) (JBoolean false)
  | 't' -> ok (i + 4) (JBoolean true)
  | 'n' -> ok (i + 4) JNull

  | _ -> ParseErr(i, JsonErrorKind.ExpectedValue)

// -----------------------------------------------
// Dump
// -----------------------------------------------

let private writeVerbatim i (text: string) =
  if i < text.Length then
    let c = text.[i]

    if charNeedsEscaping c then
      i, false
    else
      writeVerbatim (i + 1) text
  else
    i, true

let private writeEscape acc c =
  match c with
  | '"' -> acc |> cons "\\\""
  | '\\' -> acc |> cons "\\\\"

  | '\r' -> acc |> cons "\\r"
  | '\n' -> acc |> cons "\\n"
  | '\t' -> acc |> cons "\\t"
  | '\x08' -> acc |> cons "\\b" // backspace
  | '\x0c' -> acc |> cons "\\f" // formfeed

  | _ ->
    assert (charNeedsEscaping c)

    acc
    |> cons "\\u"
    |> cons (S.uint64ToHex 4 (uint64 (byte c)))

let private writeString acc (text: string) =
  let rec go acc i =
    let endIndex, eof = writeVerbatim i text

    let acc =
      if i < endIndex then
        acc |> cons (text |> S.slice i endIndex)
      else
        acc

    let i = endIndex

    if eof then
      acc
    else
      let c =
        assert (i < text.Length)
        text.[i]

      let acc = writeEscape acc c
      go acc (i + 1)

  go (acc |> cons "\"") 0 |> cons "\""

let private writeNumber acc (n: float) = acc |> cons (JB.jsonNumberToString n)

let private writeArray acc items =
  let rec go acc first items =
    match items with
    | [] -> acc

    | item :: items ->
      let acc = if first then acc else acc |> cons ","
      let acc = writeValue acc item
      go acc false items

  go (acc |> cons "[") true items |> cons "]"

let private writeObject acc entries =
  let rec go acc first entries =
    match entries with
    | [] -> acc

    | (key, value) :: entries ->
      let acc = if first then acc else acc |> cons ","
      let acc = writeString acc key |> cons ":"
      let acc = writeValue acc value
      go acc false entries

  go (acc |> cons "{") true entries |> cons "}"

let private writeValue acc value : string list =
  match value with
  | JString value -> writeString acc value
  | JNumber value -> writeNumber acc value

  | JBoolean true -> "true" :: acc
  | JBoolean false -> "false" :: acc
  | JNull -> "null" :: acc

  | JArray items -> writeArray acc items
  | JObject entries -> writeObject acc entries

// -----------------------------------------------
// Interface
// -----------------------------------------------

module Json =
  /// Parses a JSON document.
  let parse (text: string) : JsonValue option =
    let i = skipSpaces 0 text

    match parseValue i text with
    | ParseOk (value, i) when skipSpaces i text = text.Length -> Some value
    | _ -> None

  /// Parses a JSON value that appears in some part of text.
  let parsePartial (l: int) (r: int) (text: string) : JsonParseResult =
    let text = text |> S.truncate r
    let i = skipSpaces l text
    parseValue i text

  let dump (value: JsonValue) : string =
    writeValue [] value |> List.rev |> S.concat ""
