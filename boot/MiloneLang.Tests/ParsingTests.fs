module MiloneLang.Parsing.ParsingTests

open MiloneLang
open Xunit

let inline is<'T> (expected: 'T) (actual: 'T) =
  Assert.Equal(expected, actual)

let parseStr source =
  source |> Lexing.tokenize |> Parsing.parse

let exprCall f args =
  Expr.Call (f, args)

let exprAdd left right =
  Expr.Add (left, right)

let exprLet name body =
  Expr.Let (name, body)

[<Fact>]
let parseMainEmpty () =
  let source = """let main () = 0"""
  let expected =
    [
      exprLet "main" (
        Expr.Int 0
      )
    ]
  source |> parseStr |> is expected

[<Fact>]
let parseSimpleExprs () =
  let table =
    [
      "()",
        Expr.Unit
      "1",
        Expr.Int 1
      "\"Hello, world!\"",
        Expr.String "Hello, world!"
      "printfn",
        Expr.Prim PrimFun.Printfn
      "x",
        Expr.Ref "x"
      "f 1",
        exprCall (Expr.Ref "f") [Expr.Int 1]
    ]
  for fragment, expectedExpr in table do
    let source = sprintf "let main () =\n  %s" fragment
    let expected =
      [exprLet "main" expectedExpr]
    source |> parseStr |> is expected

[<Fact>]
let parseOperatorOnGroundDoesNotClearBox () =
  let source = """
let main () =
  f 1 2
    3
  + 4
"""
  let expected =
    [
      exprLet "main"
        (exprAdd
          (exprCall
            (Expr.Ref "f")
            [
              Expr.Int 1
              Expr.Int 2
              Expr.Int 3
            ])
          (Expr.Int 4))
    ]
  source |> parseStr |> is expected

[<Fact>]
let parseParensRelaxLayout () =
  let source = """let main () =
  (
        4
  + 2)
      + 1
  2
"""
  let expected =
    [
      exprLet "main" (
        Expr.Begin [
          exprAdd
            (exprAdd (Expr.Int 4) (Expr.Int 2))
            (Expr.Int 1)
          Expr.Int 2
        ])
    ]
  source |> parseStr |> is expected

[<Fact>]
let parseIndentLayoutTest () =
  let source = """let main () =
  let foo =
    let goo = 4
    4
      + 6
  2
"""
  let expected =
    [
      exprLet "main" (
        Expr.Begin [
          exprLet "foo" (
            Expr.Begin [
              exprLet "goo" (Expr.Int 4)
              exprAdd (Expr.Int 4) (Expr.Int 6)
            ])
          Expr.Int 2
        ])
    ]
  source |> parseStr |> is expected

[<Fact>]
let parseBeginExpr () =
  let source = """let main () =
  f x
  + g y
  1
"""
  let expected =
    [
      exprLet "main" (
        Expr.Begin [
          exprAdd
            (exprCall (Expr.Ref "f") [Expr.Ref "x"])
            (exprCall (Expr.Ref "g") [Expr.Ref "y"])
          Expr.Int 1
        ]
      )
    ]
  source |> parseStr |> is expected

[<Fact>]
let parseParenExpr () =
  let source = """let main () =
  1 + (2 + 3) + 4
"""
  let expected =
    [
      exprLet "main" (
        exprAdd
          (exprAdd
            (Expr.Int 1)
            (exprAdd (Expr.Int 2) (Expr.Int 3)))
          (Expr.Int 4)
      )
    ]
  source |> parseStr |> is expected

[<Fact>]
let parseSemicolonInLineOne () =
  let source = """let main () =
  printfn "Hello, " ; printfn "World!" ;
  0
"""
  let expected =
    [
      exprLet "main" (
        Expr.Begin [
          exprCall (Expr.Prim PrimFun.Printfn) [Expr.String "Hello, "]
          exprCall (Expr.Prim PrimFun.Printfn) [Expr.String "World!"]
          Expr.Int 0
        ])
    ]
  source |> parseStr |> is expected
