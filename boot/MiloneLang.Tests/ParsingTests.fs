module MiloneLang.Parsing.ParsingTests

open MiloneLang
open MiloneLang.Assets
open MiloneLang.Helpers
open Xunit

let parseStr source: Expr<unit> list =
  source
  |> Lexing.tokenize
  |> Parsing.parse
  |> List.map (exprMap id ignore)

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
  patMap id ignore pat

let tyFun sTy tTy =
  Ty.Fun (sTy, tTy)

let tyList ty =
  Ty.List ty

let tyTuple itemTys =
  Ty.Tuple itemTys

let patInt value = Pat.Lit (Lit.Int value, ())

let patNil = Pat.Nil (noTy, ())

let patRef ident = Pat.Ref (ident, noSerial, noTy, ())

let patCall callee args = Pat.Call (callee, args, noTy, ())

let patTuple itemPats = Pat.Tuple (itemPats, noTy, ())

let patCons l r = Pat.Cons (l, r, noTy, ())

let exprInt value =
  Expr.Lit (Lit.Int value, ())

let exprStr value =
  Expr.Lit (Lit.Str value, ())

let exprRef ident =
  Expr.Ref (ident, noSerial, noTy, ())

let exprList items =
  Expr.List (items, noTy, ())

let exprNil =
  exprList []

let exprCall callee args =
  Expr.Call (callee, args, noTy, ())

let exprOp op left right =
  Expr.Op (op, left,  right, noTy, ())

let exprCons l r =
  Expr.Op (Op.Cons, l, r, noTy, ())

let exprAdd left right =
  Expr.Op (Op.Add, left,  right, noTy, ())

let exprSub left right =
  Expr.Op (Op.Sub, left,  right, noTy, ())

let exprLet ident body =
  Expr.Let (patRef ident, body, ())

let exprLetMain body =
  Expr.Let (patCall (patRef "main") [Pat.Unit ()], body, ())

let exprAndThen exprs =
  Expr.AndThen (exprs, noTy, ())

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

[<EntryPoint>]
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
        Expr.Ref ("printfn", noSerial, noTy, ())
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
          exprCall
            (Expr.Ref ("printfn", noSerial, noTy, ()))
            [exprStr "Hello, "]
          exprCall
            (Expr.Ref ("printfn", noSerial, noTy, ()))
            [exprStr "World!"]
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
let parseExprTyDefUnion () =
  let source = """
type Answer =
  | Yes of int
  | No
"""
  let tyDef =
    TyDef.Union ["Yes", noSerial, true, Ty.Int; "No", noSerial, false, Ty.Unit]
  let expected =
    [
      Expr.TyDef ("Answer", noSerial, tyDef, ())
    ]
  source |> parseStr |> is expected

[<Fact>]
let parseListTypeExprs () =
  let source = """int list list"""
  let expected = tyList (tyList Ty.Int)
  source |> parseTyExprStr |> is expected

[<Fact>]
let parseTupleTypeExprs () =
  let source = """string * char list * int"""
  let expected = tyTuple [Ty.Str; tyList Ty.Char; Ty.Int]
  source |> parseTyExprStr |> is expected

[<Fact>]
let parseFunTypeExprs () =
  let source = """unit -> (int -> bool) -> string"""
  let expected =
    tyFun
      Ty.Unit
      (tyFun (tyFun Ty.Int Ty.Bool) Ty.Str)
  source |> parseTyExprStr |> is expected

[<Fact>]
let parsePatTuple () =
  let source = """1, 2, (3, 4)"""
  let expected = patTuple [patInt 1; patInt 2; patTuple [patInt 3; patInt 4]]
  source |> parseStrAsPat |> is expected

[<Fact>]
let parsePatCons () =
  let source = """x :: y :: []"""
  let x = patRef "x"
  let y = patRef "y"
  let expected = patCons x (patCons y patNil)
  source |> parseStrAsPat |> is expected

[<Fact>]
let parsePatAnno () =
  let source = """x : int"""
  let expected = Pat.Anno (patRef "x", Ty.Int, ())
  source |> parseStrAsPat |> is expected
