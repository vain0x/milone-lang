module rec union_no_equal_err.Program

type private MyNode<'T> = MyNode of 'T * MyNode<'T> list

let main _ =
  let f = fun () -> 42
  let n = MyNode(f, [])

  // MyNode<int -> int> is not equatable
  // since function type isn't equatable.
  assert (n = MyNode(f, []))

  0
