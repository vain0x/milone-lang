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

let private partiallyDisposed1 () =
  let part = __acquire 0

  match 1 with
  | 1 -> () // not disposing part

  | _ ->
    let _ = __dispose part
    ()

let private partiallyDisposed2 () =
  let part = __acquire 0

  match 1 with
  | 1 ->
    let _ = __dispose part
    ()

  | _ -> () // not disposing part

let private leakFromBranch () =
  match 1 with
  | 1 ->
    let branchLocal = __acquire 0 // not disposed
    ()

  | _ -> ()

let private cannotCapture () =
  let escaping = __acquire 0

  let f () =
    let _ = __dispose escaping
    ()

  f ()
  f ()

let private cannotUseAsPattern () =
  let value = __acquire 0
  let (first as second) = value
  let _ = __dispose first
  let _ = __dispose second
  0

// -----------------------------------------------
// Wrapped
// -----------------------------------------------

// Linear check should also work for linear unions.

type private Wrapped = Wrapped of __linear<int>
let private wrap (n: int) = Wrapped(__acquire n)

let private notDisposedWrappedUnionError () =
  let unused = wrap 0
  ()

// -----------------------------------------------

// Static variables can't be linear.
let private staticLinear = __acquire 0

let private dup x = x, x

// Linear types can't be bound to type variable for now.
let private linearGenericError () =
  let x, y = dup (__acquire 0)
  let _ = __dispose x
  let _ = __dispose y
  ()

// Record type can't be linear for now.
type private LinearRecord = { Linear: __linear<int> }

// Union type can't have other linear unions.
// (Cannot own linear values indirectly.)
type private OwnLinear = OwnLinear of Wrapped

// Generic union can't be linear for now.
type private GenericLinear<'T> = GL of __linear<'T>

let main _ = 1
