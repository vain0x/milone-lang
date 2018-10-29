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

let parseTyExprStr source: Ty =
  let ty, tokens =
    source
    |> Lexing.tokenize
    |> Parsing.parseTy -1
  if tokens <> [] then failwithf "Expected eof but %A" tokens
  ty

let parseStrAsPat source: Pat<unit> =
  let pat, tokens =
    source
    |> Lexing.tokenize
    |> Parsing.parsePat -1
  if tokens <> [] then failwithf "Expected eof but %A" tokens
  patMap ignore pat

let tyFun sTy tTy =
  Ty.Fun (sTy, tTy)

let patNil = Pat.Nil ()

let patCons l r = Pat.Cons (l, r, ())

let exprInt value =
  Expr.Int (value, ())

let exprStr value =
  Expr.Str (value, ())

let exprRef ident =
  Expr.Ref (ident, 0, ())

let exprList items =
  Expr.List (items, ())

let exprNil =
  exprList []

let exprCall callee args =
  Expr.Call (callee, List.map (exprMap ignore) args, ())

let exprOp op left right =
  Expr.Op (op, left,  right, ())

let exprCons l r =
  Expr.Op (Op.Cons, l, r, ())

let exprAdd left right =
  Expr.Op (Op.Add, left,  right, ())

let exprSub left right =
  Expr.Op (Op.Sub, left,  right, ())

let exprLet name body =
  Expr.Let ([Pat.Ident (name, 0, ())], body, ())

let exprLetMain body =
  Expr.Let ([Pat.Ident ("main", 0, ()); Pat.Unit ()], body, ())

let exprAndThen exprs =
  Expr.AndThen (List.map (exprMap ignore) exprs, ())

[<Fact>]
let parseMainEmpty () =
  let source = """let main () = 0"""
  let expected =
    [
      exprLetMain (
        exprInt 0
      )
    ]
  source |> parseStr |> is expected

[<Fact>]
let parseMainModule () =
  let source = """module Program

let rec private helper () = 0

let main _ =
  helper ()
"""
  source |> parseStr |> List.length |> is 2

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
      [exprLetMain expectedExpr]
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
      exprLetMain
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
      exprLetMain (
        exprAndThen [
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
      exprLetMain (
        exprAndThen [
          exprLet "foo" (
            exprAndThen [
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
      exprLetMain (
        exprAndThen [
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
      exprLetMain (
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
      exprLetMain (
        exprAndThen [
          exprCall (Expr.Prim (PrimFun.Printfn, ())) [exprStr "Hello, "]
          exprCall (Expr.Prim (PrimFun.Printfn, ())) [exprStr "World!"]
          exprInt 0
        ])
    ]
  source |> parseStr |> is expected

[<Fact>]
let parseAddSubExpr () =
  let source = """let main () =
  1 - 2 + 3 - 4
"""
  let expected =
    [
      exprLetMain (
        exprSub
          (exprAdd
            (exprSub
              (exprInt 1)
              (exprInt 2))
            (exprInt 3))
          (exprInt 4)
      )
    ]
  source |> parseStr |> is expected

[<Fact>]
let parseComparisonAndLogicExpr () =
  let source = """let main () =
  1 <= 2 && 2 < 3 || 3 > 2 && 2 >= 1
"""
  let expected =
    [
      exprLetMain (
        exprOp Op.Or
          (exprOp Op.And
            (exprOp Op.Le
              (exprInt 1)
              (exprInt 2))
            (exprOp Op.Lt
              (exprInt 2)
              (exprInt 3)))
          (exprOp Op.And
            (exprOp Op.Gt
              (exprInt 3)
              (exprInt 2))
            (exprOp Op.Ge
              (exprInt 2)
              (exprInt 1)))
      )
    ]
  source |> parseStr |> is expected

[<Fact>]
let parseExprListLiteral () =
  let source = """[
  f
    0
  x
]"""
  let expected =
    [
      exprList [
        exprCall (exprRef "f") [exprInt 0]
        exprRef "x"
      ]]
  source |> parseStr |> is expected

[<Fact>]
let parseExprCons () =
  let source = """
  0 :: 1 :: 2
  :: []
"""
  let expected =
    [
      exprCons (exprInt 0)
        (exprCons (exprInt 1)
          (exprCons (exprInt 2) exprNil)
        )]
  source |> parseStr |> is expected

[<Fact>]
let parseFunTypeExprs () =
  let source = """unit -> (int -> bool) -> string"""
  let expected =
    tyFun
      Ty.Unit
      (tyFun (tyFun Ty.Int Ty.Bool) Ty.Str)
  source |> parseTyExprStr |> is expected

[<Fact>]
let parsePatCons () =
  let source = """x :: y :: []"""
  let x = Pat.Ident ("x", 0, ())
  let y = Pat.Ident ("y", 0, ())
  let expected = patCons x (patCons y patNil)
  source |> parseStrAsPat |> is expected

[<Fact>]
let parsePatAnno () =
  let source = """x : int"""
  let expected =
    Pat.Anno (Pat.Ident ("x", 0, ()), Ty.Int, ())
  source |> parseStrAsPat |> is expected
