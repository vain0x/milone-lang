module rec union_equal.Program

open MiloneStd.Equal

// No payload.
type private MyBool =
  | MyTrue
  | MyFalse

let private testMyBool () =
  let t = MyTrue
  assert (t = MyTrue)
  assert (t <> MyFalse)

  let f = MyFalse
  assert (t <> f)
  assert (f = MyFalse)

// Contains a value-carrying variant, whose payload is comparable by default.
type private MyIntOption =
  | MySome of int
  | MyNone

let private testMyInt () =
  let s = MySome 2
  assert (s = MySome 2)
  assert (s <> MySome 3)
  assert (s <> MyNone)

  let n = MyNone
  assert (s <> n)
  assert (n = MyNone)

// Value-carrying variant with custom-type payload.
type private MyValue =
  | MyUnit
  | MyInt of int
  | MyString of string

type private MyResult =
  | MyOk of MyValue
  | MyErr of msg: string

let private testMyResult () =
  let ok2 = MyOk(MyInt 2)
  assert (ok2 = MyOk(MyInt 2))
  assert (ok2 <> MyOk(MyInt 3))
  assert (ok2 <> MyOk MyUnit)
  assert (ok2 <> MyErr "")

  let hello = MyOk(MyString "hello")
  assert (hello = MyOk(MyString "hello"))
  assert (hello <> ok2)
  assert (hello <> MyErr "hello")

// Generic and recursive one.
type private MyNode<'T> = MyNode of 'T * MyNode<'T> list

let private testMyNode () =
  let v =
    MyNode(5, [ MyNode(2, []); MyNode(3, []) ])

  assert (v = v)
  assert (v <> MyNode(5, []))

let main _ =
  testMyBool ()
  testMyInt ()
  testMyResult ()
  testMyNode ()
  0
