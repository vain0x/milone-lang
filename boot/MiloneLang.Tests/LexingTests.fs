module MiloneLang.Lexing.LexingTests

open MiloneLang
open Xunit

let inline is<'T> (expected: 'T) (actual: 'T) =
  Assert.Equal(expected, actual)

let synLet pat terms = Syn.Let (pat, Syn.Expr terms)

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
  emit_out 1
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
      Token.Ident "emit_out",
        (2, 2)
      Token.Int 1,
        (2, 11)
    ]
  source |> Lexing.tokenize |> is expected

[<Fact>]
let lexMainEmpty () =
  let source = """let main () = 0"""
  let expected =
    [
      synLet [Syn.Ident "main"; Syn.Unit] [
        Syn.Term [
          Syn.Int 0
        ]
      ]
    ]
  source |> Lexing.lex |> is expected

[<Fact>]
let lexEmit1 () =
  let source = """
let main () =
  emit_out 1
"""
  let expected =
    [
      synLet [Syn.Ident "main"; Syn.Unit] [
        Syn.Term [
          Syn.Ident "emit_out"
          Syn.Int 1
        ]
      ]
    ]
  source |> Lexing.lex |> is expected

[<Fact>]
let lexComplex () =
  let source = """
let main () =
  f 1 2
    3
  + 4
"""
  let expected =
    [
      synLet [Syn.Ident "main"; Syn.Unit] [
        Syn.Term [
          Syn.Ident "f"
          Syn.Int 1
          Syn.Int 2
          Syn.Int 3
          Syn.Op "+"
          Syn.Int 4
        ]
      ]
    ]
  source |> Lexing.lex |> is expected

[<Fact>]
let lexTests () =
  let source = """let main () =
  let foo =
    let goo = 4
    4
      + 6
  2
"""
  let expected =
    [
      synLet [Syn.Ident "main"; Syn.Unit] [
        synLet [Syn.Ident "foo"] [
          synLet [Syn.Ident "goo"] [
            Syn.Term [
              Syn.Int 4
            ]
          ]
          Syn.Term [
            Syn.Int 4
            Syn.Op "+"
            Syn.Int 6
          ]
        ]
        Syn.Term [
          Syn.Int 2
        ]
      ]
    ]
  source |> Lexing.lex |> is expected

[<Fact>]
let lexBeginExprTests () =
  let source = """let main () =
  f x
  + g y
  1
"""
  let expected =
    [
      synLet [Syn.Ident "main"; Syn.Unit] [
        Syn.Term [
          Syn.Ident "f"
          Syn.Ident "x"
          Syn.Op "+"
          Syn.Ident "g"
          Syn.Ident "y"
        ]
        Syn.Term [
          Syn.Int 1
        ]
      ]
    ]
  source |> Lexing.lex |> is expected
