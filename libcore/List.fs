/// Provides functions about lists for milone-lang.
///
/// This is almost compatible with the `List` module in F#.
module rec MiloneCore.List

// For failwith.
open MiloneCore.Polyfills

// Make sure every function is tail-recursive.
// Inner functions have verbose name for readability of output code.

let isEmpty (xs: _ list): bool =
  match xs with
  | [] -> true

  | _ -> false

let length (xs: _ list): int =
  let rec listLengthLoop len xs =
    match xs with
    | [] -> len

    | _ :: xs -> listLengthLoop (len + 1) xs

  listLengthLoop 0 xs

let rev (xs: _ list): _ list =
  let rec listRevLoop acc xs =
    match xs with
    | [] -> acc

    | x :: xs -> listRevLoop (x :: acc) xs

  listRevLoop [] xs

let map (f: _ -> _) (xs: _ list): _ list =
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

let filter (pred: _ -> bool) (xs: _ list): _ list =
  let rec listFilterLoop acc xs =
    match xs with
    | [] -> rev acc

    | x :: xs ->
        let acc = if pred x then x :: acc else acc
        listFilterLoop acc xs

  listFilterLoop [] xs

let choose (f: _ -> _ option) (xs: _ list): _ list =
  let rec listChooseLoop acc xs =
    match xs with
    | [] -> rev acc

    | x :: xs ->
        match f x with
        | Some y -> listChooseLoop (y :: acc) xs
        | None -> listChooseLoop acc xs

  listChooseLoop [] xs

let collect (f: _ -> _ list) (xs: _ list): _ list =
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

let skip (count: int) (xs: _ list): _ list =
  let rec listSkipLoop count xs =
    match xs with
    | [] -> []

    | _ when count <= 0 -> xs

    | _ :: xs -> listSkipLoop (count - 1) xs

  listSkipLoop count xs

let truncate (count: int) (xs: _ list): _ list =
  let rec listTruncateLoop acc count xs =
    match xs with
    | [] -> rev acc

    | _ when count <= 0 -> rev acc

    | x :: xs -> listTruncateLoop (x :: acc) (count - 1) xs

  listTruncateLoop [] count xs

let append (xs: _ list) (ys: _ list): _ list =
  let rec listAppendLoop acc xs =
    match xs with
    | [] -> acc

    | x :: xs -> listAppendLoop (x :: acc) xs

  listAppendLoop ys (rev xs)

/// USAGE: `items |> List.fold (fun state item -> nextState) initialState`
let fold (folder: _ -> _ -> _) state (xs: _ list) =
  let rec listFoldLoop state xs =
    match xs with
    | [] -> state

    | x :: xs -> listFoldLoop (folder state x) xs

  listFoldLoop state xs

let reduce (reducer: _ -> _ -> _) (xs: _ list) =
  match xs with
  | [] -> failwith "List.reduce: Empty list."

  | x :: xs -> fold reducer x xs

let forall (pred: _ -> bool) (xs: _ list): bool =
  let rec listForAllLoop xs =
    match xs with
    | [] -> true

    | x :: xs -> pred x && listForAllLoop xs

  listForAllLoop xs

let exists (pred: _ -> bool) (xs: _ list): bool =
  let rec listExistsLoop xs =
    match xs with
    | [] -> false

    | x :: xs -> pred x || listExistsLoop xs

  listExistsLoop xs

let iter (f: _ -> unit) (xs: _ list): unit =
  match xs with
  | [] -> ()

  | x :: xs ->
      f x
      iter f xs

let last (xs: _ list) =
  let rec listLastLoop xs =
    match xs with
    | [] -> failwith "List.last: Empty list."

    | [ x ] -> x

    | _ :: xs -> listLastLoop xs

  listLastLoop xs

/// Gets the i'th item if exists.
///
/// Avoid using this as possible.
/// This causes runtime error if out of range.
/// Spends O(N) time at worst.
let item (i: int) (xs: _ list) =
  match skip i xs with
  | x :: _ -> x
  | _ -> failwith "listItem: out of range"

let tryFind (pred: _ -> bool) (xs: _ list): _ option =
  let rec listTryFindLoop xs =
    match xs with
    | [] -> None

    | x :: _ when pred x -> Some x

    | _ :: xs -> listTryFindLoop xs

  listTryFindLoop xs

let tryPick (f: _ -> _ option) (xs: _ list): _ option =
  let rec listTryPickLoop xs =
    match xs with
    | [] -> None

    | x :: xs ->
        match f x with
        | Some x -> Some x
        | None -> listTryPickLoop xs

  listTryPickLoop xs
