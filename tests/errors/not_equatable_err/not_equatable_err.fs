module rec not_equatable_err.Program

// Some of types can't provide equality.

let private f: unit -> int = fun () -> 0

let private testObj () = assert (box 0 = box 0)

let private testFun () = assert (f = f)

let private testTupleWithObj () = assert ((box 0, 0) = (box 0, 0))

type private UnionWithFun = UF of (unit -> int)

let private testUnionContainingFun () = assert (UF f = UF f)

type private GU<'T> = GU of 'T

let private testGenericUnion () = assert (GU f = GU f)

type private MyNode<'T> = MyNode of 'T * MyNode<'T> list

let private testRecursiveGenericUnion () = assert (MyNode(f, []) = MyNode(f, []))

type private RecordWithFun = { F: unit -> int }

let private testRecordWithFun () =
  let r: RecordWithFun = { F = f }
  assert (r = r)

let main _ =
  testObj ()
  testFun ()
  testTupleWithObj ()
  testUnionContainingFun ()
  testRecursiveGenericUnion ()
  testGenericUnion ()
  testRecordWithFun ()
  1
