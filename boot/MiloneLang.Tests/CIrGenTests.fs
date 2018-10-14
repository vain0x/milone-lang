module MiloneLang.CIrGen.CIrGenTests

open MiloneLang
open MiloneLang.Assets
open Xunit

let locO = 0, 0

[<Fact>]
let boolLiterals () =
  let expr = Expr.Ref ("true", 0, (Ty.Bool, locO))
  let expr, acc, _ = CIrGen.genExpr [] emptyCtx expr
  (expr, acc) |> is (CExpr.Int 1, [])
