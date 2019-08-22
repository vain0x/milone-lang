module rec MiloneLang.Program

open MiloneLang.Polyfills
open MiloneLang.Lexing

let fileReadAllText (fileName: string): string =
  (__nativeFun "file_read_all_text" 1) fileName

let tokenKindToString kind =
  match kind with
  | TokenKind.Error ->
    "Error"
  | TokenKind.Ident ->
    "Ident"
  | TokenKind.IntLit ->
    "IntLit"
  | TokenKind.CharLit ->
    "CharLit"
  | TokenKind.StrLit ->
    "StrLit"
  | TokenKind.Op ->
    "Op"
  | TokenKind.Pun ->
    "Pun"

let tokenToString token =
  match token with
  | Token.Bool true ->
    "true"
  | Token.Bool false ->
    "false"
  | Token.Int value ->
    string value
  | Token.Char _ ->
    // FIXME: escape and print
    "'?'"
  | Token.Str _ ->
    // FIXME: escape and print
    "\"..\""
  | Token.Ident ident ->
    ident
  | Token.Do ->
    "do"
  | Token.Let ->
    "let"
  | Token.Rec ->
    "rec"
  | Token.If ->
    "if"
  | Token.Then ->
    "then"
  | Token.Else ->
    "else"
  | Token.Match ->
    "match"
  | Token.With ->
    "with"
  | Token.As ->
    "as"
  | Token.When ->
    "when"
  | Token.ParenL ->
    "("
  | Token.ParenR ->
    ")"
  | Token.BracketL ->
    "["
  | Token.BracketR ->
    "]"
  | Token.Colon ->
    ":"
  | Token.Dot ->
    "."
  | Token.Range ->
    ".."
  | Token.Pipe ->
    "|"
  | Token.Arrow ->
    "->"
  | Token.Punct value ->
    value
  | Token.Private ->
    "private"
  | Token.Internal ->
    "internal"
  | Token.Public ->
    "public"
  | Token.Module ->
    "module"
  | Token.Namespace ->
    "namespace"
  | Token.Open ->
    "open"
  | Token.Type ->
    "type"
  | Token.Of ->
    "of"
  | Token.Fun ->
    "fun"
  | Token.In ->
    "in"

let rec listIter f xs =
  match xs with
  | [] ->
    ()

  | x :: xs ->
    f x
    listIter f xs

[<EntryPoint>]
let main _ =
  // let source = "let main _ =\n  0"
  let source = fileReadAllText "MiloneLang/Lexing.fs"

  // let _, tokens = source |> scanRoot
  // tokens |> listIter (fun (kind, l, r) -> printfn "%d..%d %s" l r (tokenKindToString kind))

  source |> tokenize |> listIter (fun (token, (y, x)) -> printfn "%s (%d, %d)" (tokenToString token) y x)
  0
