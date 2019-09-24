module rec MiloneLang.Self

open MiloneLang.Types
open MiloneLang.Helpers
open MiloneLang.Lexing
open MiloneLang.Parsing

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

let doSelf (fileReadAllText: string -> string) =
  let source = fileReadAllText "MiloneLang/Lexing.fs"

  let tokens = source |> tokenize

  tokens |> listIter (fun (token, (y, x)) -> printfn "%s (%d, %d)" (tokenToString token) y x)

  let _, errors = tokens |> parse
  errors |> listIter (fun (msg, (y, x)) -> printfn "ERROR %s (%d:%d)" msg (y + 1) (x + 1))

  0
