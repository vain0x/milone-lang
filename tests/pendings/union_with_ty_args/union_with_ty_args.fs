module rec union_with_ty_args.Program

type MyInt = Value of int

let main _ =
  // This causes assertion violation at NameRes.fs:686 `assert (List.isEmpty tys)`.
  // let _ : MyInt<_> = Value 0
  0
