module rec union_with_ty_args.Program

type MyInt = Value of int

let main _ =
  let _: MyInt<_> = Value 0
  0
