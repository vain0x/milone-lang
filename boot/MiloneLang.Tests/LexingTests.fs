module MiloneLang.Lexing.LexingTests

open MiloneLang
open MiloneLang.Assets
open MiloneLang.Types
open Xunit

[<Fact>]
let tokenizeMainEmpty () =
  let source = """let main () = 0"""
  let expected =
    [
      Token.Let
      Token.Ident "main"
      Token.ParenL
      Token.ParenR
      Token.Punct "="
      Token.Int 0
    ]
  source
  |> Lexing.tokenize |> List.map fst
  |> is expected

[<Fact>]
let tokenizeLineComment () =
  let source = """
/// Entry point.
let main _ =
  1 // After expression
    - 1
// EOF"""
  let expected =
    [
      Token.Let
      Token.Ident "main"
      Token.Ident "_"
      Token.Punct "="
      Token.Int 1
      Token.Punct "-"
      Token.Int 1
    ]
  source
  |> Lexing.tokenize |> List.map fst
  |> is expected

[<Fact>]
let tokenizeOps () =
  let unwrapPunct token =
    match token with
    | Token.Punct op -> Some op
    | _ -> None
  let source = """+ - <- :,-,:"""
  let expected = ["+"; "-"; "<-"; ":,-,:"]
  source
  |> Lexing.tokenize
  |> List.unzip
  |> fst
  |> List.choose unwrapPunct
  |> is expected

[<Fact>]
let tokenizeCharLiteral () =
  let unwrapChar (token, _) =
    match token with
    | Token.Char value ->
      value
    | _ ->
      failwithf "Expected char token but %A" token
  let source = """'a' '\'' '\n' '\u0000'"""
  let expected = ['a'; '\''; '\n'; '\u0000']
  source
  |> Lexing.tokenize
  |> List.map unwrapChar
  |> is expected

[<Fact>]
let tokenizeStrLiteral () =
  let source = "\"HELLO!\\n\\\"NEW\\\"\\nWORLD!\""
  let expected = [Token.Str "HELLO!\n\"NEW\"\nWORLD!", (0, 0)]
  source
  |> Lexing.tokenize
  |> is expected

[<Fact>]
let tokenizeComplex () =
  let source = """
let main () =
  f 1
"""
  let expected =
    [
      Token.Let,
        (1, 0)
      Token.Ident "main",
        (1, 4)
      Token.ParenL,
        (1, 9)
      Token.ParenR,
        (1, 10)
      Token.Punct "=",
        (1, 12)
      Token.Ident "f",
        (2, 2)
      Token.Int 1,
        (2, 4)
    ]
  source |> Lexing.tokenize |> is expected
