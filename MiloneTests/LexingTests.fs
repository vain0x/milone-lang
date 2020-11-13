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
    [ LetToken
      IdentToken "main"
      LeftParenToken
      RightParenToken
      EqToken
      IntToken 0 ]

  source
  |> Lexing.tokenize
  |> List.map fst
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
    [ LetToken
      IdentToken "main"
      IdentToken "_"
      EqToken
      IntToken 1
      MinusToken
      IntToken 1 ]

  source
  |> Lexing.tokenize
  |> List.map fst
  |> is expected

[<Fact>]
let tokenizeCharLiteral () =
  let unwrapChar (token, _) =
    match token with
    | CharToken value -> value
    | _ -> failwithf "Expected char token but %A" token

  let source = """'a' '\'' '\n' '\x00'"""
  let expected = [ 'a'; '\''; '\n'; '\x00' ]
  source
  |> Lexing.tokenize
  |> List.map unwrapChar
  |> is expected

[<Fact>]
let tokenizeStrLiteral () =
  let source = "\"HELLO!\\n\\\"NEW\\\"\\nWORLD!\""

  let expected =
    [ StrToken "HELLO!\n\"NEW\"\nWORLD!", (0, 0) ]

  source |> Lexing.tokenize |> is expected

[<Fact>]
let tokenizeTyVarIdent () =
  let source =
    """type option<'T> = Some of 'T | None"""

  let expected = [ "T", (0, 12); "T", (0, 26) ]

  source
  |> Lexing.tokenize
  |> List.choose (fun (token, pos) ->
       match token with
       | TyVarToken text -> Some(text, pos)
       | _ -> None)
  |> is expected

[<Fact>]
let tokenizeComplex () =
  let source = """
let main () =
  f 1
"""

  let expected =
    [ LetToken, (1, 0)
      IdentToken "main", (1, 4)
      LeftParenToken, (1, 9)
      RightParenToken, (1, 10)
      EqToken, (1, 12)
      IdentToken "f", (2, 2)
      IntToken 1, (2, 4) ]

  source |> Lexing.tokenize |> is expected
