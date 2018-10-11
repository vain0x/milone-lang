module MiloneLang.Parsing.ParsingTests

open MiloneLang
open MiloneLang.Assets
open Xunit

let exprMap f = Parsing.exprMap f

let withUnit x = x, ()

let parseStr source: Expr<unit> list =
  source
  |> Lexing.tokenize
  |> Parsing.parse
  |> List.map (exprMap ignore)

let exprInt value =
  Expr.Int (value, ())

let exprStr value =
  Expr.String (value, ())

let exprRef ident =
  Expr.Ref (ident, ())

let exprCall callee args =
  Expr.Call (callee, List.map (exprMap ignore) args, ())

let exprFdd left right =
  Expr.Add (left,  right, ())

let exprLet name body =
  Expr.Let (name,  body, ())

let exprBlock exprs =
  Expr.Begin (List.map (exprMap ignore) exprs, ())

[<Fact>]
let parseMainEmpty () =
  let source = """let main () = 0"""
  let expected =
    [
      exprLet "main" (
        exprInt 0
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
        exprStr "Hello, world!"
      "printfn",
        Expr.Prim (PrimFun.Printfn, ())
      "x",
        exprRef "x"
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
        (exprFdd
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
          exprFdd
            (exprFdd (exprInt 4) (exprInt 2))
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
              exprFdd (exprInt 4) (exprInt 6)
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
          exprFdd
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
        exprFdd
          (exprFdd
            (exprInt 1)
            (exprFdd (exprInt 2) (exprInt 3)))
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
          exprCall (Expr.Prim (PrimFun.Printfn, ())) [exprStr "Hello, "]
          exprCall (Expr.Prim (PrimFun.Printfn, ())) [exprStr "World!"]
          exprInt 0
        ])
    ]
  source |> parseStr |> is expected
