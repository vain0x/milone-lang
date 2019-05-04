module MiloneLang.Parsing.ParsingTests

open MiloneLang
open MiloneLang.Assets
open MiloneLang.Helpers
open Xunit

let loc = (0, 0)

let parseStr source: HExpr =
  source
  |> Lexing.tokenize
  |> Parsing.parse
  |> exprMap id (fun _ -> loc)

let parseTyExprStr source: Ty =
  let ty, tokens =
    source
    |> Lexing.tokenize
    |> Parsing.parseTy -1
  if tokens <> [] then failwithf "Expected eof but %A" tokens
  ty

let parseStrAsPat source: HPat =
  let pat, tokens =
    source
    |> Lexing.tokenize
    |> Parsing.parsePat -1
  if tokens <> [] then failwithf "Expected eof but %A" tokens
  patMap id (fun _ -> loc) pat

let patInt value = HPat.Lit (Lit.Int value, loc)

let patNil = HPat.Nil (noTy, loc)

let patRef ident = HPat.Ref (ident, noSerial, noTy, loc)

let patCall callee args = HPat.Call (callee, args, noTy, loc)

let patTuple itemPats = HPat.Tuple (itemPats, noTy, loc)

let patCons l r = HPat.Cons (l, r, noTy, loc)

let exprInt value =
  HExpr.Lit (Lit.Int value, loc)

let exprStr value =
  HExpr.Lit (Lit.Str value, loc)

let exprRef ident =
  HExpr.Ref (ident, HValRef.Var noSerial, noArity, noTy, loc)

let exprList items =
  hxList items noTy loc

let exprNil =
  exprList []

let exprApp callee arg =
  HExpr.Op (Op.App, callee, arg, noTy, loc)

let exprOp op left right =
  HExpr.Op (op, left,  right, noTy, loc)

let exprCons l r =
  HExpr.Op (Op.Cons noTy, l, r, noTy, loc)

let exprAdd left right =
  HExpr.Op (Op.Add, left,  right, noTy, loc)

let exprSub left right =
  HExpr.Op (Op.Sub, left,  right, noTy, loc)

let exprLet ident body next =
  HExpr.Let (patRef ident, body, next, noTy, loc)

let exprLetMain body =
  HExpr.Let (patCall (patRef "main") [patUnit loc], body, hxUnit loc, noTy, loc)

let exprAndThen exprs =
  hxAndThen exprs loc

let exprCall callee args =
  let rec go callee args =
    match args with
    | [] ->
      callee
    | arg :: args ->
      go (exprApp callee arg) args
  go callee args

[<Fact>]
let parseMainEmpty () =
  let source = """let main () = 0"""
  let expected =
    exprLetMain (
      exprInt 0
    )
  source |> parseStr |> is expected

[<Fact>]
let parseMainModule () =
  let source = """module Program

let rec private helper () = 0

[<EntryPoint>]
let main _ =
  helper ()
"""
  source |> parseStr |> ignore // no exception

[<Fact>]
let parseSimpleExprs () =
  let table =
    [
      "()",
        hxUnit loc
      "1",
        exprInt 1
      "\"Hello, world!\"",
        exprStr "Hello, world!"
      "printfn",
        exprRef "printfn"
      "x",
        exprRef "x"
      "f 1",
        exprCall (exprRef "f") [exprInt 1]
    ]
  for fragment, expectedExpr in table do
    let source = sprintf "let main () =\n  %s" fragment
    let expected =
      exprLetMain expectedExpr
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
    exprLetMain (
      exprAndThen [
        exprAdd
          (exprAdd (exprInt 4) (exprInt 2))
          (exprInt 1)
        exprInt 2
      ])
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
    exprLetMain (
        exprLet "foo" (
          exprLet "goo" (exprInt 4) (
            exprAdd (exprInt 4) (exprInt 6)
          ))
          (exprInt 2)
        )
  source |> parseStr |> is expected

[<Fact>]
let parseBeginExpr () =
  let source = """let main () =
  f x
  + g y
  1
"""
  let expected =
    exprLetMain (
      exprAndThen [
        exprAdd
          (exprCall (exprRef "f") [exprRef "x"])
          (exprCall (exprRef "g") [exprRef "y"])
        exprInt 1
      ])
  source |> parseStr |> is expected

[<Fact>]
let parseParenExpr () =
  let source = """let main () =
  1 + (2 + 3) + 4
"""
  let expected =
    exprLetMain (
      exprAdd
        (exprAdd
          (exprInt 1)
          (exprAdd (exprInt 2) (exprInt 3)))
        (exprInt 4))
  source |> parseStr |> is expected

[<Fact>]
let parseSemicolonInLineOne () =
  let source = """let main () =
  printfn "Hello, " ; printfn "World!" ;
  0
"""
  let expected =
    exprLetMain (
      exprAndThen [
        exprCall
          (exprRef "printfn")
          [exprStr "Hello, "]
        exprCall
          (exprRef "printfn")
          [exprStr "World!"]
        exprInt 0
      ])
  source |> parseStr |> is expected

[<Fact>]
let parseAddSubExpr () =
  let source = """let main () =
  1 - 2 + 3 - 4
"""
  let expected =
    exprLetMain (
      exprSub
        (exprAdd
          (exprSub
            (exprInt 1)
            (exprInt 2))
          (exprInt 3))
        (exprInt 4))
  source |> parseStr |> is expected

[<Fact>]
let parseComparisonAndLogicExpr () =
  let source = """let main () =
  1 <= 2 && 2 < 3 || 3 > 2 && 2 >= 1
"""
  let expected =
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
            (exprInt 1))))
  source |> parseStr |> is expected

[<Fact>]
let parseExprListLiteral () =
  let source = """[
  f
    0
  x
]"""
  let expected =
    exprList [
      exprCall (exprRef "f") [exprInt 0]
      exprRef "x"
    ]
  source |> parseStr |> is expected

[<Fact>]
let parseExprCons () =
  let source = """
  0 :: 1 :: 2
  :: []
"""
  let expected =
    exprCons (exprInt 0)
      (exprCons (exprInt 1)
        (exprCons (exprInt 2) exprNil)
      )
  source |> parseStr |> is expected

[<Fact>]
let parseExprTyDefUnion () =
  let source = """
type Answer =
  | Yes of int
  | No
"""
  let tyDecl =
    TyDecl.Union ("Answer", [
      "Yes", noSerial, true, tyInt
      "No", noSerial, false, tyUnit
    ], (1, 5))
  let expected =
    HExpr.TyDef ("Answer", noSerial, tyDecl, loc)
  source |> parseStr |> is expected

[<Fact>]
let parseListTypeExprs () =
  let source = """int list list"""
  let expected = tyList (tyList tyInt)
  source |> parseTyExprStr |> is expected

[<Fact>]
let parseTupleTypeExprs () =
  let source = """string * char list * int"""
  let expected = tyTuple [tyStr; tyList tyChar; tyInt]
  source |> parseTyExprStr |> is expected

[<Fact>]
let parseFunTypeExprs () =
  let source = """unit -> (int -> bool) -> string"""
  let expected =
    tyFun
      tyUnit
      (tyFun (tyFun tyInt tyBool) tyStr)
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
  let expected = HPat.Anno (patRef "x", tyInt, loc)
  source |> parseStrAsPat |> is expected
