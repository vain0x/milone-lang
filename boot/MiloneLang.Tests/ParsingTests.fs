module MiloneLang.Parsing.ParsingTests

open MiloneLang
open Xunit

let inline is<'T> (expected: 'T) (actual: 'T) =
  Assert.Equal(expected, actual)

let parseString source =
  source |> Lexing.lex |> Parsing.parse

let funDecl ident body =
  Stmt.FunDecl (ident, body)

let exprCall f args =
  Expr.Call (f, args)

let exprAdd left right =
  Expr.Add (left, right)

[<Fact>]
let parseMainEmpty () =
  let source = "let main () = 0"
  let expected =
    [
      funDecl "main" (
        Expr.Int 0
      )
    ]
  parseString source |> is expected

[<Fact>]
let parseBeginExpr () =
  let source = """let main () =
  f x
  + g y
  1
"""
  let expected =
    [
      funDecl "main" (
        Expr.Begin [
          exprAdd
            (exprCall (Expr.Ref "f") [Expr.Ref "x"])
            (exprCall (Expr.Ref "g") [Expr.Ref "y"])
          Expr.Int 1
        ]
      )
    ]
  parseString source |> is expected

[<Fact>]
let parseParenExpr () =
  let source = """let main () =
  1 + (2 + 3) + 4
"""
  let expected =
    [
      funDecl "main" (
        exprAdd
          (exprAdd
            (Expr.Int 1)
            (exprAdd (Expr.Int 2) (Expr.Int 3)))
          (Expr.Int 4)
      )
    ]
  parseString source |> is expected
