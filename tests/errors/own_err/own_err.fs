module rec own_err.Program

open Std.Own

let private notDisposedError () =
  let _unused = Own.acquire 0
  ()

let private useAfterDisposeError () =
  let df = Own.acquire 0 // double-free
  let _ = Own.release df
  let _ = Own.release df
  ()

let private copyTwiceError () =
  let dupped = Own.acquire 0
  let copy1 = dupped
  let copy2 = dupped
  let _ = Own.release copy1
  let _ = Own.release copy2
  ()

let private partiallyDisposed1 () =
  let part = Own.acquire 0

  match 1 with
  | 1 -> () // not disposing part

  | _ ->
    let _ = Own.release part
    ()

let private partiallyDisposed2 () =
  let part = Own.acquire 0

  match 1 with
  | 1 ->
    let _ = Own.release part
    ()

  | _ -> () // not disposing part

let private leakFromBranch () =
  match 1 with
  | 1 ->
    let branchLocal = Own.acquire 0 // not disposed
    ()

  | _ -> ()

let private cannotCapture () =
  let escaping = Own.acquire 0

  let f () =
    let _ = Own.release escaping
    ()

  f ()
  f ()

let private cannotUseAsPattern () =
  let value = Own.acquire 0
  let (first as second) = value
  let _ = Own.release first
  let _ = Own.release second
  0

let private ownedOptionMustBeDisposed () =
  let _opt: Own<int> option = None
  ()

let private ownedPairPartiallyLeakedError () =
  let pair = Own.acquire 2, Own.acquire 3

  match pair with
  | l, _ ->
    let _ = Own.release l
    ()

let private ownedValueCannotBePartiallyAppliedError () =
  let f (l: Own<int>) () = l

  let l = Own.acquire 0
  let g = f l
  let l1 = g ()
  let l2 = g ()
  let _ = Own.release l1
  let _ = Own.release l2
  ()

// -----------------------------------------------
// OwnInt
// -----------------------------------------------

// Ownership check should also work for owned unions.

type private OwnInt = OwnInt of Own<int>
let private wrap (n: int) = OwnInt(Own.acquire n)

let private ownedUnionLeakError () =
  let _unused = wrap 0
  ()

/// Non-owned generic union.
type private Identity<'T> = Identity of 'T

let private genericUnionOfOwnedTypeLeakError () =
  let _unused = Identity(Own.acquire 0)
  ()

/// Owned generic union.
type private MyOwn<'T> = MyOwn of Own<'T>

let private ownedGenericUnionLeakError () =
  let _unused = MyOwn(Own.acquire 0)
  ()

// -----------------------------------------------

// Static variables can't be owned types.
let private ownedStaticVar = Own.acquire 0

let private dup x = x, x

// Owned types can't be bound to type variable for now.
let private genericFunOwnedTyArgError () =
  let x, y = dup (Own.acquire 0)
  let _ = Own.release x
  let _ = Own.release y
  ()

// Record types can't be owned types for now.
type private OwnRecord = { OwnField: Own<int> }

// Union type can't have other owned unions, especially they are forwardly referenced.
// (Must own the Own type directly.)
type private OwnForwardUnion = OwnForwardUnion of ForwardUnion
type private ForwardUnion = FU of Own<int>

let main _ = 1
