module MiloneLang.Parsing.ParsingTests

open MiloneLang
open MiloneLang.Assets
open Xunit

let locO = (0, 0)

let parseStr source: Expr<unit> list =
  source
  |> Lexing.tokenize
  |> Parsing.parse
  |> List.map (Parsing.exprMap ignore)

let exprInt value =
  Expr.Int ((), value)

let exprRef ident =
  Expr.Ref ((), ident)

let exprCall f args =
  Expr.Call ((), f, args)

let exprAdd left right =
  Expr.Add ((), left, right)

let exprLet name body =
  Expr.Let ((), name, body)

let exprBlock exprs =
  Expr.Begin ((), exprs)

[<Fact>]
let parseMainEmpty () =
  let source = """let main () = 0"""
  let expected =
    [
      exprLet "main" (
        Expr.Int ((), 0)
      )
    ]
  source |> parseStr |> is expected

[<Fact>]
let parseSimpleExprs () =
  let table =
    [
      "()",
        Expr.Unit ()
      "1",
        exprInt 1
      "\"Hello, world!\"",
        Expr.String ((), "Hello, world!")
      "printfn",
        Expr.Prim ((), PrimFun.Printfn)
      "x",
        Expr.Ref ((), "x")
      "f 1",
        exprCall (exprRef "f") [exprInt 1]
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
            (exprRef "f")
            [
              exprInt 1
              exprInt 2
              exprInt 3
            ])
          (exprInt 4))
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
        exprBlock [
          exprAdd
            (exprAdd (exprInt 4) (exprInt 2))
            (exprInt 1)
          exprInt 2
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
        exprBlock [
          exprLet "foo" (
            exprBlock [
              exprLet "goo" (exprInt 4)
              exprAdd (exprInt 4) (exprInt 6)
            ])
          exprInt 2
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
        exprBlock [
          exprAdd
            (exprCall (exprRef "f") [exprRef "x"])
            (exprCall (exprRef "g") [exprRef "y"])
          exprInt 1
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
            (exprInt 1)
            (exprAdd (exprInt 2) (exprInt 3)))
          (exprInt 4)
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
        exprBlock [
          exprCall (Expr.Prim ((), PrimFun.Printfn)) [Expr.String ((), "Hello, ")]
          exprCall (Expr.Prim ((), PrimFun.Printfn)) [Expr.String ((), "World!")]
          exprInt 0
        ])
    ]
  source |> parseStr |> is expected
