module MiloneLang.Lexing.LexingTests

open MiloneLang
open Xunit

let inline is<'T> (expected: 'T) (actual: 'T) =
  Assert.Equal(expected, actual)

[<Fact>]
let tokenizeMainEmpty () =
  let source = """let main () = 0"""
  let expected =
    [
      Token.Ident "let"
      Token.Ident "main"
      Token.Unit
      Token.Punct "="
      Token.Int 0
    ]
  source
  |> Lexing.tokenize |> List.unzip |> fst
  |> is expected

[<Fact>]
let tokenizeComplex () =
  let source = """
let main () =
  f 1
"""
  let expected =
    [
      Token.Ident "let",
        (1, 0)
      Token.Ident "main",
        (1, 4)
      Token.Unit,
        (1, 9)
      Token.Punct "=",
        (1, 12)
      Token.Ident "f",
        (2, 2)
      Token.Int 1,
        (2, 4)
    ]
  source |> Lexing.tokenize |> is expected
