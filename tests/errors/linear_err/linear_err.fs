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

let private linearOptionMustBeDisposed () =
  let _opt: __linear<int> option = None

// -----------------------------------------------
// LinearInt
// -----------------------------------------------

// Linear check should also work for linear unions.

type private LinearInt = LinearInt of __linear<int>
let private wrap (n: int) = LinearInt(__acquire n)

let private notDisposedLinearUnionError () =
  let _unused = wrap 0
  ()

let private notDisposedWrappedUnionError () =
  let _unused = wrap 0
  ()

/// Non-linear generic union.
type private Identity<'T> = Identity of 'T

let private notDisposedLinearlyUsedGenericUnionError () =
  let _unused = Identity(__acquire 0)
  ()

/// Linear generic union.
type private GenericLinear<'T> = GenericLinear of __linear<'T>

let private notDisposedGenericLinearError () =
  let _unused = GenericLinear(__acquire 0)
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
type private OwnLinear = OwnLinear of LinearInt

let main _ = 1
