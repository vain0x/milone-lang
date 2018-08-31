module rec MiloneLang.Parsing

open System
open System.Text.RegularExpressions
open MiloneLang

let lex (source: string): list<Token> =
  let regex =
    [
      """[ \t\r\n]+"""
      """[+;(){}]"""
      """[0-9a-zA-Z_]+"""
    ]
    |> String.concat "|"
    |> Regex

  let rec go acc index (m: Match) =
    if m.Success && m.Index = index && m.Length > 0 then
      let s = m.Value
      let c = m.Value.[0]
      let token =
        if Char.IsWhiteSpace(c) then
          None
        else if Char.IsDigit(c) then
          s |> int |> Token.Int |> Some
        else if Char.IsLetter(c) || c = '_' then
          s |> Token.Ident |> Some
        else
          Token.Punct s |> Some
      let acc =
        match token with
        | Some token -> token :: acc
        | None -> acc
      let index = m.Index + m.Length
      if index >= source.Length then
        acc |> List.rev
      else
        let m = m.NextMatch()
        go acc index m
    else
      let near =
        source.Substring(
          Math.Min(source.Length - 1, index),
          Math.Max(0, Math.Min(source.Length - index, 8))
        )
      failwithf "Unknown token at %d near %s" index near
  go [] 0 (regex.Match(source))

let parseError message (_, tokens) =
  let near = tokens |> List.truncate 6
  failwithf "Parse error %s near %A" message near

/// atom = int / prim
let rec parseAtom =
  function
  | Token.Int value :: tokens ->
    Expr.Int value, tokens
  | Token.Ident "emit_out" :: tokens ->
    Expr.Prim PrimFun.EmitOut, tokens
  | tokens ->
    parseError "atom" ((), tokens)

/// call = atom ('(' arg ')')?
let parseCall tokens =
  match parseAtom tokens with
  | first, Token.Punct "(" :: tokens ->
    match parseExpr tokens with
    | arg, Token.Punct ")" :: tokens ->
      Expr.Call (first, [arg]), tokens
    | t ->
      parseError "missing args )" t
  | t -> t

/// add = call ( '+' call )* / atom
let parseAdd tokens: Expr * list<Token> =
  let rec go =
    function
    | acc, Token.Punct "+" :: tokens ->
      let it, tokens = parseCall tokens
      Expr.Add(acc, it), tokens
    | t -> t
  parseCall tokens |> go

let parseExpr tokens =
  parseAdd tokens

let parse (tokens: list<Token>): Stmt =
  match tokens with
  | Token.Ident "fun"
    :: Token.Ident "main"
    :: Token.Punct "(" :: Token.Punct ")"
    :: Token.Punct "{" :: tokens ->
    match parseAdd tokens with
    | body, Token.Punct "}" :: tokens ->
      if tokens <> [] then
        failwithf "Unknown tokens: %A" tokens
      Stmt.FunDecl ("main", body)
    | t ->
      parseError "expected } to close fun body" t
  | t ->
    parseError "not starting with main fun decl" ((), t)
