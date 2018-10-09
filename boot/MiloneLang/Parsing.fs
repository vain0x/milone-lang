module rec MiloneLang.Parsing

open System
open System.Text.RegularExpressions
open MiloneLang

let parseError message (_, syns) =
  let near = syns |> List.truncate 6
  failwithf "Parse error %s near %A" message near

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
  | Syn.Ident "printfn" :: syns ->
    Some (Expr.Prim PrimFun.Printfn), syns
  | Syn.Ident value :: syns ->
    Some (Expr.Ref value), syns
  | Syn.Expr terms :: syns ->
    Some (parseTerms terms), syns
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
  let rec go acc syns =
    match syns with
    | [] ->
      acc
    | Syn.Op "+" :: syns ->
      let second, syns = parseCall syns
      let acc = Expr.Add (acc, second)
      go acc syns
    | _ ->
      failwithf "Expected '+' but %A" syns
  let first, syns = parseCall syns
  go first syns

let parseTerm term =
  match term with
  | Syn.Let _ ->
    failwithf "unimpl let-in"
  | Syn.Term syns ->
    parseAdd syns
  | _ ->
    failwithf "Expected term but %A" term

let parseTerms terms: Expr =
  match terms |> List.map parseTerm with
  | [term] ->
    term
  | terms ->
    Expr.Begin terms

let parseLet acc syns =
  match syns with
  | [] ->
    List.rev acc
  // let f arg ... = ...
  | Syn.Let
    (
      Syn.Ident ident :: (_ :: _ as args),
      Syn.Expr body
    ) :: syns ->
    let body = parseTerms body
    let s = Stmt.FunDecl (ident, body)
    parseLet (s :: acc) syns
  | _ ->
    failwithf "unimpl %A" syns

let parse (syn: Syn list): Stmt list =
  parseLet [] syn
