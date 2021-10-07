/// # Loop
///
/// ## Description
///
/// `Loop` is an interface of an iteration over collection.
///
/// ## Comparison to sequences
///
/// `Loop` is similar to `seq` in F# and "iterable" in other languages.
///
/// - Pros: `Loop` runs fast enough but `seq` doesn't in current milone-lang
/// - Cons: Less flexible than `seq`.

module rec MiloneStd.StdLoop

module S = MiloneStd.StdString

/// Function type to compute a step of iteration.
///
/// Result boolean means whether the iteration is running gracefully.
/// `false` result indicates break.
///
/// `'S`: State of iteration.
/// `'T`: Item of collection.
type private Folder<'S, 'T> = 'S -> 'T -> bool * 'S

/// Abstraction of iteration.
type private Loop<'S, 'T> = Folder<'S, 'T> -> 'S -> bool * 'S

/// Runs a loop to fold items.
let fold (folder: Folder<'S, 'T>) (state: 'S) (xs: Loop<'S, 'T>) : 'S = xs folder state |> snd

// -----------------------------------------------
// Creation
// -----------------------------------------------

let empty () : Loop<'S, 'T> =
  fun (folder: Folder<_, _>) state -> true, state

/// Generates integers such that `start <= i && i < endIndex`.
let range (start: int) (endIndex: int) : Loop<'S, int> =
  fun folder state ->
    let rec loopRangeLoop (i: int) state =
      if i >= endIndex then
        true, state
      else
        let ok, state = folder state i

        if ok then
          loopRangeLoop (i + 1) state
        else
          false, state

    loopRangeLoop start state

let init (len: int) (f: int -> 'T) : Loop<'S, 'T> =
  assert (len >= 0)

  fun folder state ->
    let rec loopInitLoop i acc =
      if i = len then
        true, acc
      else
        let ok, state = folder state (f i)

        if ok then
          loopInitLoop (i + 1) state
        else
          false, state

    loopInitLoop 0 state

let replicate (len: int) (item: 'T) : Loop<'S, 'T> =
  assert (len >= 0)

  fun folder state ->
    let rec loopReplicateLoop (len: int) state =
      if len = 0 then
        true, state
      else
        let ok, state = folder state item

        if ok then
          loopReplicateLoop (len - 1) state
        else
          false, state

    loopReplicateLoop len state

// -----------------------------------------------
// Transformation
// -----------------------------------------------

let map (f: 'T -> 'U) (xs: Loop<'S, 'T>) : Loop<'S, 'U> =
  fun folder state -> xs (fun state item -> folder state (f item)) state

let filter (pred: 'T -> bool) (xs: Loop<'S, 'T>) : Loop<'S, 'T> =
  fun folder state ->
    xs
      (fun state item ->
        if pred item then
          folder state item
        else
          true, state)
      state

let collect (f: 'T -> Loop<'S, 'U>) (xs: Loop<'S, 'T>) : Loop<'S, 'U> =
  fun folder state -> xs (fun state item -> (f item) folder state) state

// -----------------------------------------------
// Combination
// -----------------------------------------------

let append (xs: Loop<'S, 'T>) (ys: Loop<'S, 'T>) : Loop<'S, 'T> =
  fun folder state ->
    let ok, state = xs folder state

    if ok then
      ys folder state
    else
      false, state

// -----------------------------------------------
// List
// -----------------------------------------------

let ofList (xs: 'T list) : Loop<'S, 'T> =
  fun folder state ->
    let rec loopOfList state xs =
      match xs with
      | x :: xs ->
        let ok, state = folder state x

        if ok then
          loopOfList state xs
        else
          false, state

      | [] -> true, state

    loopOfList state xs

let toList (xs: Loop<_, 'T>) : 'T list =
  xs (fun xs x -> true, x :: xs) []
  |> snd
  |> List.rev

// -----------------------------------------------
// Collector
// -----------------------------------------------

let isEmpty (xs: Loop<_, _>) : bool = forall (fun _ -> false) xs

let length (xs: Loop<int, _>) : int =
  xs (fun len _ -> true, len + 1) 0 |> snd

let forall (pred: 'T -> bool) (xs: Loop<_, 'T>) : bool = xs (fun _ x -> pred x, ()) () |> fst

let exists (pred: 'T -> bool) (xs: Loop<_, 'T>) : bool =
  xs (fun _ x -> not (pred x), ()) () |> fst |> not

let concatString (sep: string) (xs: Loop<_, string>) : string = xs |> toList |> S.concat sep

// let zip (xs1: Loop<_, 'T1>) (xs2: Loop<'T1 list * 'S, 'T2>) : Loop<'S, 'T1 * 'T2> =
//   let xs1 : 'T1 list = xs1 |> toList

//   fun (folder: Folder<'S, 'T1 * 'T2>) (state: 'S) ->
//     let ok, (_, state) =
//       xs2
//         (fun (xs1: 'T1 list, state: 'S) (x2: 'T2) ->
//           match xs1 with
//           | [] -> false, ([], state)

//           | x1 :: xs1 ->
//             let ok, state = folder state (x1, x2)

//             if ok then
//               true, (xs1, state)
//             else
//               false, ([], state))
//         (xs1, state)

//     ok, state
