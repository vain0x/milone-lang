/// Provides functions about lists for milone-lang.
///
/// This is a subset of `List` module in F#.
/// Some functions are not unimplemented yet,
/// however, existing functions have compatible with F#.
///
/// Partial functions, which could throw exceptions, are unavailable intentionally.
module rec MiloneCore.List

open MiloneCore.Option

// Make sure every function is tail-recursive.
// Inner functions have verbose name for readability of output code.

let isEmpty (xs: _ list) : bool =
  match xs with
  | [] -> true

  | _ -> false

let length (xs: _ list) : int =
  let rec listLengthLoop len xs =
    match xs with
    | [] -> len

    | _ :: xs -> listLengthLoop (len + 1) xs

  listLengthLoop 0 xs

let rev (xs: _ list) : _ list =
  let rec listRevLoop acc xs =
    match xs with
    | [] -> acc

    | x :: xs -> listRevLoop (x :: acc) xs

  listRevLoop [] xs

let map (f: _ -> _) (xs: _ list) : _ list =
  let rec listMapLoop acc xs =
    match xs with
    | [] -> rev acc

    | x :: xs -> listMapLoop (f x :: acc) xs

  listMapLoop [] xs

let mapi (f: int -> _ -> _) (xs: _ list) =
  let rec listMapWithIndexLoop acc i xs =
    match xs with
    | [] -> rev acc

    | x :: xs -> listMapWithIndexLoop (f i x :: acc) (i + 1) xs

  listMapWithIndexLoop [] 0 xs

let filter (pred: _ -> bool) (xs: _ list) : _ list =
  let rec listFilterLoop acc xs =
    match xs with
    | [] -> rev acc

    | x :: xs ->
      let acc = if pred x then x :: acc else acc
      listFilterLoop acc xs

  listFilterLoop [] xs

let takeWhile (pred: _ -> bool) (xs: _ list) : _ list =
  let rec listTakeWhileLoop acc xs =
    match xs with
    | x :: tail when pred x -> listTakeWhileLoop (x :: acc) tail
    | _ -> rev acc

  listTakeWhileLoop [] xs

let skipWhile (pred: _ -> bool) (xs: _ list) : _ list =
  let rec listSkipWhileLoop xs =
    match xs with
    | [] -> []

    | x :: tail ->
      if pred x then
        listSkipWhileLoop tail
      else
        xs

  listSkipWhileLoop xs

let choose (f: _ -> _ option) (xs: _ list) : _ list =
  let rec listChooseLoop acc xs =
    match xs with
    | [] -> rev acc

    | x :: xs ->
      match f x with
      | Some y -> listChooseLoop (y :: acc) xs
      | None -> listChooseLoop acc xs

  listChooseLoop [] xs

let collect (f: _ -> _ list) (xs: _ list) : _ list =
  let rec listCollectInnerLoop acc ys =
    match ys with
    | [] -> acc

    | y :: ys -> listCollectInnerLoop (y :: acc) ys

  let rec listCollectOuterLoop acc xs =
    match xs with
    | [] -> rev acc

    | x :: xs ->
      let acc = listCollectInnerLoop acc (f x)
      listCollectOuterLoop acc xs

  listCollectOuterLoop [] xs

let truncate (count: int) (xs: _ list) : _ list =
  let rec listTruncateLoop acc count xs =
    match xs with
    | [] -> rev acc

    | _ when count <= 0 -> rev acc

    | x :: xs -> listTruncateLoop (x :: acc) (count - 1) xs

  listTruncateLoop [] count xs

let append (xs: _ list) (ys: _ list) : _ list =
  let rec listAppendLoop acc xs =
    match xs with
    | [] -> acc

    | x :: xs -> listAppendLoop (x :: acc) xs

  listAppendLoop ys (rev xs)

// Usage:
//  items |> List.fold (fun state item -> nextState) initialState
let fold (folder: _ -> _ -> _) state (xs: _ list) =
  let rec listFoldLoop state xs =
    match xs with
    | [] -> state

    | x :: xs -> listFoldLoop (folder state x) xs

  listFoldLoop state xs

// Usage:
//  let mappedList, finalState =
//    items |> List.mapFold (fun state item -> mappedItem, nextState) initialState
/// Does `map` and `fold` on a list at the same time.
let mapFold (folder: 'S -> 'T -> 'U * 'S) (state: 'S) (xs: 'T list) : 'U list * 'S =
  let rec listMapFoldLoop state acc xs =
    match xs with
    | [] -> rev acc, state

    | x :: xs ->
      let y, state = folder state x
      listMapFoldLoop state (y :: acc) xs

  listMapFoldLoop state [] xs

let forall (pred: _ -> bool) (xs: _ list) : bool =
  let rec listForAllLoop xs =
    match xs with
    | [] -> true

    | x :: xs -> pred x && listForAllLoop xs

  listForAllLoop xs

let exists (pred: _ -> bool) (xs: _ list) : bool =
  let rec listExistsLoop xs =
    match xs with
    | [] -> false

    | x :: xs -> pred x || listExistsLoop xs

  listExistsLoop xs

let iter (f: _ -> unit) (xs: _ list) : unit =
  match xs with
  | [] -> ()

  | x :: xs ->
    f x
    iter f xs

let tryHead (xs: _ list) : _ option =
  match xs with
  | x :: _ -> Some x
  | _ -> None

let tryLast (xs: _ list) : _ option =
  match xs with
  | [] -> None
  | x :: xs ->
    let rec listTryLastLoop xs =
      match xs with
      | [] -> x
      | [ x ] -> x
      | _ :: xs -> listTryLastLoop xs

    Some(listTryLastLoop xs)

/// Gets the i'th item if exists.
///
/// Spends O(N) time at worst. Avoid using this as possible.
let tryItem (i: int) (xs: _ list) : _ option =
  let rec listTryItemLoop (i: int) xs =
    match xs with
    | [] -> None
    | x :: _ when i = 0 -> Some x
    | _ :: xs -> listTryItemLoop (i - 1) xs

  if i >= 0 then
    listTryItemLoop i xs
  else
    None

let tryFind (pred: _ -> bool) (xs: _ list) : _ option =
  let rec listTryFindLoop xs =
    match xs with
    | [] -> None

    | x :: _ when pred x -> Some x

    | _ :: xs -> listTryFindLoop xs

  listTryFindLoop xs

let tryFindIndex (pred: _ -> bool) (xs: _ list) : int option =
  let rec listTryFindIndexLoop i xs =
    match xs with
    | [] -> None

    | x :: _ when pred x -> Some i

    | _ :: xs -> listTryFindIndexLoop (i + 1) xs

  listTryFindIndexLoop 0 xs

let tryPick (f: _ -> _ option) (xs: _ list) : _ option =
  let rec listTryPickLoop xs =
    match xs with
    | [] -> None

    | x :: xs ->
      match f x with
      | Some x -> Some x
      | None -> listTryPickLoop xs

  listTryPickLoop xs

/// Splits a list into a pair `(trueItems, falseItems)`, where:
///
/// - `trueItems` consists of items that return `true` for the predicate,
/// - `falseItems` is the other items, which return `false` for the predicate.
///
/// Ordering is preserved.
let partition (pred: _ -> bool) (xs: _ list) : _ list * _ list =
  let rec listPartitionLoop trueAcc falseAcc xs =
    match xs with
    | [] -> rev trueAcc, rev falseAcc

    | x :: xs ->
      if pred x then
        listPartitionLoop (x :: trueAcc) falseAcc xs
      else
        listPartitionLoop trueAcc (x :: falseAcc) xs

  listPartitionLoop [] [] xs

let unzip (xs: ('T * 'U) list) : 'T list * 'U list =
  let rec listUnzipLoop lAcc rAcc xs =
    match xs with
    | [] -> rev lAcc, rev rAcc
    | (l, r) :: xs -> listUnzipLoop (l :: lAcc) (r :: rAcc) xs

  listUnzipLoop [] [] xs

/// Creates a list with specified length. i'th element is filled by `f i`.
/// That is, `[ f 0; f 1; ...; f (len - 1) ]`.
let init (len: int) (f: int -> _) : _ list =
  assert (len >= 0)

  let rec listInitLoop acc i =
    if i = len then
      rev acc
    else
      listInitLoop (f i :: acc) (i + 1)

  listInitLoop [] 0

/// Creates a list with specified length. Every element is `item`.
/// That is, `[ item; item; ...; item ]`.
let replicate (len: int) item : _ list =
  assert (len >= 0)

  let rec listReplicateLoop acc i =
    if i = len then
      acc
    else
      listReplicateLoop (item :: acc) (i + 1)

  listReplicateLoop [] 0
