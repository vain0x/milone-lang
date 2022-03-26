module rec fun_generic.Program

// Function defined with let expression is generalized automatically.

type private HPat =
  | HNodePat of HPat list
  | HOrPat

/// Converts a pattern in disjunctive normal form.
/// E.g. `A, [B | C]` → `(A | [B]), (A | [C])`
let patNormalize pat =
  match pat with
  | HNodePat argPats ->
    [ argPats ]
    |> List.map (fun itemPats -> HNodePat itemPats)

  | _ -> exit 1

let main _ =
  let _ = patNormalize (HNodePat [])

  0
