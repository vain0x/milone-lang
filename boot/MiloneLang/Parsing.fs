module rec MiloneLang.Parsing

open System
open System.Text.RegularExpressions
open MiloneLang

let parseError message (_, syns) =
  let near = syns |> List.truncate 6
  failwithf "Parse error %s near %A" message near

let (|LeadExpr|_|) token =
  match token with
  | Token.Int _
  | Token.Ident _
  | Token.Punct "(" -> Some ()
  | _ -> None

/// atom = unit / int / string / prim
let rec parseAtom syns =
  match syns with
  | Syn.Unit :: syns ->
    Some Expr.Unit, syns
  | Syn.Int value :: syns ->
    Some (Expr.Int value), syns
  | Syn.String value :: syns ->
    Some (Expr.String value), syns
  | Syn.Ident "emit_out" :: syns ->
    Some (Expr.Prim PrimFun.EmitOut), syns
  | Syn.Ident value :: syns ->
    Some (Expr.Ref value), syns
  | syns ->
    None, syns

/// call = atom ( atom )*
let parseCall syns =
  let rec go acc syns =
    match parseAtom syns with
    | Some atom, syns ->
      go (atom :: acc) syns
    | None, syns ->
      match List.rev acc with
      | [] -> failwith "invalid syns"
      | [atom] ->
        atom, syns
      | atom :: args ->
        Expr.Call (atom, args), syns
  go [] syns

/// add = call ( '+' call )*
let parseAdd syns =
  let rec go syns =
    match syns with
    | acc, Syn.Op "+" :: syns ->
      let it, syns = parseCall syns
      Expr.Add (acc, it), syns
    | t -> t
  parseCall syns |> go

/// begin = add ( ';' add )*
let parseBegin syns: Expr =
  let rec go acc syns =
    match acc, syns with
    | [expr], [] ->
      expr
    | acc, [] ->
      acc |> List.rev |> Expr.Begin
    | acc, Syn.Op ";" :: syns ->
      let expr, syns = parseAdd syns
      go (expr :: acc) syns
    | _, syns ->
      failwithf "Expected ';' but: %A" syns
  let expr, syns = parseAdd syns
  go [expr] syns

let parseExpr = parseBegin

let parseLet acc syns =
  match syns with
  | [] ->
    List.rev acc
  // let f arg ... = ...
  | Syn.Let
    (
      Syn.Ident ident :: (_ :: _ as args),
      body
    ) :: syns ->
    let body = parseExpr body
    let s = Stmt.FunDecl (ident, body)
    parseLet (s :: acc) syns
  | _ ->
    failwithf "unimpl %A" syns

let parse (syn: Syn list): Stmt list =
  parseLet [] syn
