module rec linear_err.Program

open Std.Linear

let private notDisposedError () =
  let _unused = Linear.acquire 0
  ()

let private useAfterDisposeError () =
  let df = Linear.acquire 0 // double-free
  let _ = Linear.dispose df
  let _ = Linear.dispose df
  ()

let private copyTwiceError () =
  let dupped = Linear.acquire 0
  let copy1 = dupped
  let copy2 = dupped
  let _ = Linear.dispose copy1
  let _ = Linear.dispose copy2
  ()

let private partiallyDisposed1 () =
  let part = Linear.acquire 0

  match 1 with
  | 1 -> () // not disposing part

  | _ ->
    let _ = Linear.dispose part
    ()

let private partiallyDisposed2 () =
  let part = Linear.acquire 0

  match 1 with
  | 1 ->
    let _ = Linear.dispose part
    ()

  | _ -> () // not disposing part

let private leakFromBranch () =
  match 1 with
  | 1 ->
    let branchLocal = Linear.acquire 0 // not disposed
    ()

  | _ -> ()

let private cannotCapture () =
  let escaping = Linear.acquire 0

  let f () =
    let _ = Linear.dispose escaping
    ()

  f ()
  f ()

let private cannotUseAsPattern () =
  let value = Linear.acquire 0
  let (first as second) = value
  let _ = Linear.dispose first
  let _ = Linear.dispose second
  0

let private linearOptionMustBeDisposed () =
  let _opt: Linear<int> option = None
  ()

let private linearPairPartiallyLeakedError () =
  let pair = Linear.acquire 2, Linear.acquire 3

  match pair with
  | l, _ ->
    let _ = Linear.dispose l
    ()

let private linearValueCannotBePartiallyAppliedError () =
  let f (l: Linear<int>) () = l

  let l = Linear.acquire 0
  let g = f l
  let l1 = g ()
  let l2 = g ()
  let _ = Linear.dispose l1
  let _ = Linear.dispose l2
  ()

// -----------------------------------------------
// LinearInt
// -----------------------------------------------

// Linear check should also work for linear unions.

type private LinearInt = LinearInt of Linear<int>
let private wrap (n: int) = LinearInt(Linear.acquire n)

let private notDisposedLinearUnionError () =
  let _unused = wrap 0
  ()

let private notDisposedWrappedUnionError () =
  let _unused = wrap 0
  ()

/// Non-linear generic union.
type private Identity<'T> = Identity of 'T

let private notDisposedLinearlyUsedGenericUnionError () =
  let _unused = Identity(Linear.acquire 0)
  ()

/// Linear generic union.
type private GenericLinear<'T> = GenericLinear of Linear<'T>

let private notDisposedGenericLinearError () =
  let _unused = GenericLinear(Linear.acquire 0)
  ()

// -----------------------------------------------

// Static variables can't be linear.
let private staticLinear = Linear.acquire 0

let private dup x = x, x

// Linear types can't be bound to type variable for now.
let private linearGenericError () =
  let x, y = dup (Linear.acquire 0)
  let _ = Linear.dispose x
  let _ = Linear.dispose y
  ()

// Record type can't be linear for now.
type private LinearRecord = { Linear: Linear<int> }

// Union type can't have other linear unions, especially they are forwardly referenced.
// (Must own Linear directly.)
type private OwnLinear = OwnLinear of ForwardLinearUnion
type private ForwardLinearUnion = FLU of Linear<int>

let main _ = 1
