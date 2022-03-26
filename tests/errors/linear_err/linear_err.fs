module rec linear_err.Program

let private notDisposedError () =
  let _unused = __acquire 0
  ()

let private useAfterDisposeError () =
  let df = __acquire 0 // double-free
  let _ = __dispose df
  let _ = __dispose df
  ()

let private copyTwiceError () =
  let dupped = __acquire 0
  let copy1 = dupped
  let copy2 = dupped
  let _ = __dispose copy1
  let _ = __dispose copy2
  ()

let private partiallyDisposed () =
  let part = __acquire 0

  match 2 with
  | 1 -> () // not disposed
  | _ -> __dispose part

type private Wrapped = Wrapped of __linear<int>
let private wrap (n: int) = Wrapped(__acquire n)

let private notDisposedWrappedUnionError () =
  let unused = wrap 0
  ()

let private dup x = x, x

// Linear types can't be bound to type variable for now.
let private linearGenericError () =
  let x, y = dup (__acquire 0)
  let _ = __dispose x
  let _ = __dispose y
  ()

let main _ = 1
