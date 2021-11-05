module rec Ungrammar.Parse

open Ungrammar.Tokenize

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type Rule =
  | Labeled of label: string * Rule
  | Token of name: string
  | Node of name: string
  | Seq of Rule list
  | Alt of Rule list
  | Opt of Rule
  | Rep of Rule

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type Grammar = { Rules: Map<string, Rule> }

[<RequireQualifiedAccess; NoEquality; NoComparison>]
type private ParseCtx =
  { Text: string
    Tokens: Token list
    Rules: Map<string, Rule>
    Errors: (string * Pos) list }

type Error = string * Pos

let private atEof (px: ParseCtx) = List.isEmpty px.Tokens

let private isOkay (px: ParseCtx) = List.isEmpty px.Errors

let private addError msg (px: ParseCtx) =
  let pos =
    match px.Tokens with
    | (_, pos) :: _ -> pos
    | _ -> px.Text.Length

  { px with Errors = (msg, pos) :: px.Errors }

let private peek (px: ParseCtx) =
  match px.Tokens with
  | token :: _ -> Some token
  | _ -> None

let private peek2 (px: ParseCtx) =
  match px.Tokens with
  | [ token ] -> Some(token, None)
  | t1 :: t2 :: _ -> Some(t1, Some t2)
  | _ -> None

let private bump (px: ParseCtx) =
  match px.Tokens with
  | _ :: tokens -> { px with Tokens = tokens }
  | _ -> px

let private expect kind hint (px: ParseCtx) =
  match px.Tokens with
  | (token, _) :: _ when token = kind -> bump px
  | _ -> px |> addError ("Expected " + hint) |> bump

let private parseAtomRule px =
  match peek2 px with
  | Some ((TokenKind.Node _, _), Some (TokenKind.Equal, _)) -> None, px
  | Some ((TokenKind.Node _, _), Some (TokenKind.Colon, _)) -> None, px

  | Some ((TokenKind.Token name, _), _) -> Some(Rule.Token name), bump px
  | Some ((TokenKind.Node name, _), _) -> Some(Rule.Node name), bump px

  | Some ((TokenKind.LeftParen, _), _) ->
    let px = bump px
    let ruleOpt, px = parseRule px
    let px = px |> expect TokenKind.RightParen ")"
    ruleOpt, px

  | _ -> None, px

let private parseOptRule px =
  match parseAtomRule px with
  | Some head, px ->
    match peek px with
    | Some (TokenKind.Question, _) -> head |> Rule.Opt |> Some, bump px
    | Some (TokenKind.Star, _) -> head |> Rule.Rep |> Some, bump px
    | _ -> Some head, px

  | t -> t

let private parseLabeledRule px =
  match peek2 px with
  | Some ((TokenKind.Node label, _), Some (TokenKind.Colon, _)) ->
    let px = px |> bump |> bump

    match parseOptRule px with
    | Some rule, px -> Some(Rule.Labeled(label, rule)), px
    | t -> t

  | _ -> parseOptRule px

let private parseSeqRule px =
  match parseLabeledRule px with
  | Some head, px ->
    let rec go prev acc px =
      match parseLabeledRule px with
      | Some rule, px -> go rule (prev :: acc) px
      | None, px -> prev, acc, px

    match go head [] px with
    | it, [], px -> it |> Some, px
    | last, acc, px -> last :: acc |> List.rev |> Rule.Seq |> Some, px

  | t -> t

let private parseAlt px =
  match parseSeqRule px with
  | Some head, px ->
    let rec go prev acc px =
      match peek px with
      | Some (TokenKind.Pipe, _) ->
        let px = bump px

        match parseSeqRule px with
        | Some rule, px -> go rule (prev :: acc) px
        | None, px -> prev, acc, addError "Expected rule" px

      | _ -> prev, acc, px

    match go head [] px with
    | it, [], px -> it |> Some, px
    | last, acc, px -> last :: acc |> List.rev |> Rule.Alt |> Some, px

  | t -> t

let private parseRule px : Rule option * ParseCtx = parseAlt px

let private parseNode px =
  match peek px with
  | Some (TokenKind.Node name, pos) ->
    let px = px |> bump |> expect TokenKind.Equal "="
    let ruleOpt, px = parseRule px

    match ruleOpt with
    | _ when px.Rules |> Map.containsKey name -> { px with Errors = ("Already defined.", pos) :: px.Errors }
    | Some rule -> { px with Rules = px.Rules |> Map.add name rule }
    | None ->
      assert (isOkay px |> not)
      px

  | _ ->
    let rec go px =
      match peek2 px with
      | None
      | Some ((TokenKind.Node _, _), Some (TokenKind.Equal, _)) -> px
      | _ -> bump px

    px |> addError "Expected node" |> go

let private parseRoot px =
  let rec go px =
    if atEof px then
      px
    else
      parseNode px |> go

  go px

let parse (text: string) (tokens: Token list) : Grammar * Error list =
  let px: ParseCtx =
    { Text = text
      Tokens = tokens
      Rules = Map.empty
      Errors = [] }

  let px = parseRoot px

  { Rules = px.Rules }, px.Errors
