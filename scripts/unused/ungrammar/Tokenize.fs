module Ungrammar.Tokenize

type Pos = int

[<RequireQualifiedAccess>]
type TokenKind =
  | Token of string
  | Node of string
  | LeftParen
  | RightParen
  | Colon
  | Equal
  | Pipe
  | Question
  | Star

type Token = TokenKind * Pos

[<RequireQualifiedAccess>]
type TokenizeError =
  | Eof
  | UnclosedToken
  | InvalidEscape
  | InvalidChar

module private S =
  let occursAt index (substr: string) (s: string) =
    index + substr.Length <= s.Length
    && s.[index..index + substr.Length - 1] = substr

  let findIndex (index: int) (substr: string) (s: string) =
    let i = s.IndexOf(substr, index)
    if i >= 0 then Some i else None

let private isEscapable c =
  match c with
  | '\\'
  | '\'' -> true
  | _ -> false

let private isSpace c =
  match c with
  | ' '
  | '\t'
  | '\r'
  | '\n' -> true
  | _ -> false

let private isDigit (c: char) = '0' <= c && c <= '9'

let private isIdent (c: char) =
  c = '_'
  || ('0' <= c && c <= '9')
  || ('A' <= c && c <= 'Z')
  || ('a' <= c && c <= 'z')

let private skipSpace (text: string) (index: int) : int =
  let rec go (i: int) =
    if i < text.Length && isSpace text.[i] then
      go (i + 1)
    else
      i

  go index

let private skipComment (text: string) (index: int) : int =
  if text |> S.occursAt index "//" then
    match text |> S.findIndex index "\n" with
    | Some i -> i + 1
    | None -> text.Length
  else
    index

let private advance (text: string) (index: int) : Result<Token * int, TokenizeError> =
  let at (i: int) =
    if i < text.Length then
      text.[i]
    else
      '\x00'

  let pun1 kind = Ok((kind, index), index + 1)

  match at index with
  | '\x00' -> Error TokenizeError.Eof
  | '(' -> pun1 TokenKind.LeftParen
  | ')' -> pun1 TokenKind.RightParen
  | ':' -> pun1 TokenKind.Colon
  | '=' -> pun1 TokenKind.Equal
  | '*' -> pun1 TokenKind.Star
  | '|' -> pun1 TokenKind.Pipe
  | '?' -> pun1 TokenKind.Question

  | '\'' ->
    let rec go acc (i: int) =
      match at i with
      | '\x00' -> Error TokenizeError.UnclosedToken

      | '\\' when isEscapable (at (i + 1)) -> go (at (i + 1) :: acc) (i + 2)

      | '\\' -> Error TokenizeError.InvalidEscape
      | '\'' -> Ok(acc, i + 1)
      | c -> go (c :: acc) (i + 1)

    match go [] (index + 1) with
    | Ok (acc, endIndex) ->
      let token =
        acc
        |> List.rev
        |> List.map string
        |> String.concat ""

      Ok((TokenKind.Token token, index), endIndex)

    | Error e -> Error e

  | c when isIdent c && not (isDigit c) ->
    let rec go (i: int) =
      if isIdent (at i) then go (i + 1) else i

    let endIndex = go (index + 1)
    assert (index < endIndex)
    let node = text.[index..endIndex - 1]
    Ok((TokenKind.Node node, index), endIndex)

  | _ -> Error TokenizeError.InvalidChar

let tokenize (text: string) : Result<Token list, TokenizeError * Pos> =
  let rec go acc i =
    if i >= text.Length then
      acc |> List.rev |> Ok
    else
      let j = skipSpace text i
      let j = skipComment text j

      if i <> j then
        go acc j
      else
        match advance text i with
        | Ok (token, nextIndex) -> go (token :: acc) nextIndex
        | Error e -> Error(e, i)

  go [] 0
