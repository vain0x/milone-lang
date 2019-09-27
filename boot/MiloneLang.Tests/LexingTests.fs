module MiloneLang.Lexing.LexingTests

open MiloneLang
open MiloneLang.Assets
open MiloneLang.Helpers
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
      Token.Eq
      Token.Int 0
    ]
  source
  |> Lexing.tokenize |> listMap fst
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
      Token.Eq
      Token.Int 1
      Token.Minus
      Token.Int 1
    ]
  source
  |> Lexing.tokenize |> listMap fst
  |> is expected

[<Fact>]
let tokenizeCharLiteral () =
  let unwrapChar (token, _) =
    match token with
    | Token.Char value ->
      value
    | _ ->
      failwithf "Expected char token but %A" token
  let source = """'a' '\'' '\n' '\x00'"""
  let expected = ['a'; '\''; '\n'; '\x00']
  source
  |> Lexing.tokenize
  |> listMap unwrapChar
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
      Token.Eq,
        (1, 12)
      Token.Ident "f",
        (2, 2)
      Token.Int 1,
        (2, 4)
    ]
  source |> Lexing.tokenize |> is expected
