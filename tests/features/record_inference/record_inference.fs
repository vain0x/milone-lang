module rec record_inference.Program

// Type inference of records.

type IntWrapper = { Value: int }

type IntWrapperEx = { Value: int; Extra: int }

let letWithTypeAscriptionCase n =
  let w: IntWrapper = { Value = n }
  assert (w.Value = n)

let typeAscriptionExprCase (n: int) =
  assert (({ Value = n }: IntWrapper).Value = n)

let matchExprCase (n: int) =
  let t: IntWrapper =
    match n with
    | 5 -> { Value = 0 }
    | _ -> exit 1

  assert (t.Value = 0)

let main _ =
  letWithTypeAscriptionCase 2
  typeAscriptionExprCase 3
  matchExprCase 5

  0
