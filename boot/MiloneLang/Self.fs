module rec MiloneLang.Self

open MiloneLang.Types
open MiloneLang.Helpers
open MiloneLang.Lexing
open MiloneLang.Parsing

let litToString lit =
  match lit with
  | Lit.Bool true ->
    "true"

  | Lit.Bool false ->
    "false"

  | Lit.Int value ->
    string value

  | Lit.Char value ->
    "char " + string (int value) // FIXME: escape

  | Lit.Str _ ->
    "\"...\"" // FIXME: escape

let tokenToString token =
  match token with
  | Token.Error ->
    "Error"

  | Token.Bool false ->
    "false"

  | Token.Bool true ->
    "true"

  | Token.Int value ->
    string value

  | Token.Char _  ->
    "'?'" // FIXME: escape

  | Token.Str _ ->
    "\"?\"" // FIXME: escape

  | Token.Ident ident ->
    "\"" + ident + "\""

  | Token.ParenL ->
    "("

  | Token.ParenR ->
    ")"

  | Token.BracketL ->
    "["

  | Token.BracketR ->
    "]"

  | Token.Amp ->
    "&"

  | Token.AmpAmp ->
    "&&"

  | Token.Arrow ->
    "->"

  | Token.Colon ->
    ":"

  | Token.ColonColon ->
    "::"

  | Token.Comma ->
    ","

  | Token.Dot ->
    "."

  | Token.DotDot ->
    ".."

  | Token.Eq ->
    "="

  | Token.Gt ->
    ">"

  | Token.GtEq ->
    ">="

  | Token.Lt ->
    "<"

  | Token.LtEq ->
    "<="

  | Token.LtGt ->
    "<>"

  | Token.Minus ->
    "-"

  | Token.Percent ->
    "%"

  | Token.Pipe ->
    "|"

  | Token.PipeGt ->
    "|>"

  | Token.PipePipe ->
    "||"

  | Token.Plus ->
    "+"

  | Token.Semi ->
    ";"

  | Token.Star ->
    "*"

  | Token.Slash ->
    "/"

  | Token.As ->
    "as"

  | Token.Do ->
    "do"

  | Token.Else ->
    "else"

  | Token.Fun ->
    "fun"

  | Token.If ->
    "if"

  | Token.In ->
    "in"

  | Token.Internal ->
    "internal"

  | Token.Let ->
    "let"

  | Token.Match ->
    "match"

  | Token.Module ->
    "module"

  | Token.Namespace ->
    "namespace"

  | Token.Of ->
    "of"

  | Token.Open ->
    "open"

  | Token.Private ->
    "private"

  | Token.Public ->
    "public"

  | Token.Rec ->
    "rec"

  | Token.Then ->
    "then"

  | Token.Type ->
    "type"

  | Token.When ->
    "when"

  | Token.With ->
    "with"

let atDump ty =
  match ty with
  | ATy.Missing loc ->
    dumpTreeFromError "missing" loc

  | ATy.Ident (ident, _) ->
    dumpTreeNewLeaf ident

  | ATy.Suffix (lTy, ident, _) ->
    dumpTreeNew ident [atDump lTy]

  | ATy.Tuple (itemTys, _) ->
    dumpTreeNew "tuple" (listMap atDump itemTys)

  | ATy.Fun (sTy, tTy, _) ->
    dumpTreeNew "fun" ([sTy; tTy] |> listMap atDump)

let apDump (pat: APat) =
  match pat with
  | APat.Missing loc ->
    dumpTreeFromError "missing" loc

  | APat.Lit (lit, _) ->
    lit |> litToString |> dumpTreeNewLeaf

  | APat.Ident (ident, _) ->
    dumpTreeNewLeaf ident

  | APat.ListLit (pats, _) ->
    dumpTreeNew "list" (pats |> listMap apDump)

  | APat.Nav (l, r, loc) ->
    dumpTreeNew ("." + r) [apDump l]

  | APat.Call (calleePat, argPats, _) ->
    dumpTreeNew "call" (
      apDump calleePat
      :: (argPats |> listMap apDump)
    )

  | APat.Cons (head, tail, _) ->
    dumpTreeNew "cons" [apDump head] |> dumpTreeAttachNext (apDump tail)

  | APat.TupleLit (pats, _) ->
    dumpTreeNew "tuple" (pats |> listMap apDump)

  | APat.As (pat, ident, _) ->
    dumpTreeNew ("as " + ident) [apDump pat]

  | APat.Anno (pat, ty, _) ->
    dumpTreeNew "anno" [apDump pat; atDump ty]

  | APat.Or (l, r, _) ->
    dumpTreeNew "or" [apDump l] |> dumpTreeAttachNext (apDump r)

  | APat.Fun (callee, args, loc) ->
    dumpTreeNew "fun" (
      dumpTreeNewLeaf callee
      :: (args |> listMap apDump)
    )

let axDump (expr: AExpr) =
  match expr with
  | AExpr.Missing loc ->
    dumpTreeFromError "missing" loc

  | AExpr.Lit (lit, _) ->
    dumpTreeNewLeaf (litToString lit)

  | AExpr.Ident (ident, _) ->
    dumpTreeNewLeaf ident

  | AExpr.ListLit (items, _) ->
    dumpTreeNew "list" (items |> listMap axDump)

  | AExpr.If (cond, body, alt, _) ->
    dumpTreeNew "if" [
      axDump cond
      axDump body
      axDump alt
    ]

  | AExpr.Match (target, arms, _) ->
    dumpTreeNew "match" [axDump target] // FIXME: arms

  | AExpr.Fun (pats, body, _) ->
    dumpTreeNew "fun" (pats |> listMap apDump)
    |> dumpTreeAttachNext (axDump body)

  | AExpr.Nav (l, r, _) ->
    dumpTreeNew ("." + r) [axDump l]

  | AExpr.Index (l, r, _) ->
    dumpTreeNew "index" [axDump l]

  | AExpr.Uni (UniOp.Neg, arg, _) ->
    dumpTreeNew "-" [axDump arg]

  | AExpr.Bin (_, l, r, _) ->
    dumpTreeNew "bin" [axDump l; axDump r] // FIXME: binOp to string

  | AExpr.Range (items, _) ->
    dumpTreeNew "range" (items |> listMap axDump)

  | AExpr.TupleLit (items, _) ->
    dumpTreeNew "tuple" (items |> listMap axDump)

  | AExpr.Anno (body, ty, _) ->
    dumpTreeNew "anno" [axDump body; atDump ty]

  | AExpr.Semi (exprs, _) ->
    dumpTreeNew "semi" (exprs |> listMap axDump)

  | AExpr.Let (pat, body, next, _) ->
    dumpTreeNew "let" [apDump pat; axDump body]
    |> dumpTreeAttachNext (axDump next)

  | AExpr.TySynonym (ident, ty, _) ->
    dumpTreeNewLeaf "FIXME: TBD"

  | AExpr.TyUnion (ident, variants, _) ->
    dumpTreeNewLeaf "FIXME: TBD"

  | AExpr.Open (path, _) ->
    dumpTreeNewLeaf "FIXME: TBD"

let doSelf (fileReadAllText: string -> string) =
  let source = fileReadAllText "MiloneLang/Lexing.fs"

  let tokens = source |> tokenize

  tokens |> listIter (fun (token, (y, x)) -> printfn "%s (%d, %d)" (tokenToString token) y x)

  let ast, errors = tokens |> parse
  printfn "AST:"
  printfn "%s" (ast |> axDump |> dumpTreeToString)

  errors |> listIter (fun (msg, (y, x)) -> printfn "ERROR %s (%d:%d)" msg (y + 1) (x + 1))

  0
