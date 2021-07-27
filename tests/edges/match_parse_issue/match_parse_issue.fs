module rec match_parse_issue.Program

// Regression test: the parser used to run into infinite loop with the following code
// (without the assertion in MiloneSyntax.SyntaxParse.parsePatApp).

let main _ =
  match None with
  | None -
  | _ -> ()

  0
