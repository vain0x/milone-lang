module rec union_generic.Program

type private MyOption<'T> =
  | MyNone
  | MySome of 'T

let private isNone (opt: MyOption<'A>) : bool =
  match opt with
  | MyNone -> true
  | MySome _ -> false

let private unwrap (opt: MyOption<'T>) : 'T =
  match opt with
  | MySome it -> it

  | MyNone ->
    assert false
    exit 1

let private testBasicUsage () =
  // Unit-like variant.
  let none: MyOption<_> = MyNone

  assert (isNone none)

  // Value-carrying variant.
  let some: MyOption<_> = MySome 42

  assert (isNone some |> not)
  assert (unwrap some = 42)

let private testAnotherInstance () =
  let stringNone: MyOption<string> = MyNone

  assert (isNone stringNone)

  let stringSome: MyOption<string> = MySome "hey"

  assert (isNone stringSome |> not)
  assert (unwrap stringSome = "hey")

let main _ =
  testBasicUsage ()
  testAnotherInstance ()
  0
