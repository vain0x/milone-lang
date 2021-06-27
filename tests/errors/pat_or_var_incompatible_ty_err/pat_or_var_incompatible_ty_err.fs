module rec pat_or_var_incompatible_ty_err.Program

type IntOrString =
  | Int of int
  | String of string

let main _ =
  match Int 2 with
  | Int x
  | String x ->
    let n : int = box x |> unbox
    assert (n = 2)

  assert false
  0
