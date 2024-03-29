module rec Std.StdIter

type private NextFun<'S, 'T> = 'S -> ('T * 'S) option

// The implementation of the Iter type.
//
// If generic nominal type were implemented,
// iterator (enumerator in .NET) would be defined as:
//    Iter<'T> = Iter of unit -> ('T * Iter<'T>) option
//
// The recursion of type can be avoided by
// splitting the function and the state that changes during iteration.
// That is:
//    Iter<'T> = (forall 'S => 'S -> ('T * 'S) option)
//
// `forall` is not supported (no plan to support).
// 'S is just replaced by obj here.

/// Iterator, abstraction of iteration.
///
/// Also known as "enumerator" in .NET.
/// Iterator is stateless and different than IEnumerator.
type Iter<'T> = NextFun<obj, 'T> * obj

module Iter =
  let next (xs: Iter<'T>) : ('T * Iter<'T>) option =
    let nextFun, state = xs

    match nextFun state with
    | None -> None
    | Some (item, state) ->
      let xs: Iter<'T> = nextFun, state
      Some(item, xs)

  /// Extended `scan`.
  let private scanEx (f: 'S -> 'T -> Iter<'U> * 'S) (state: 'S) (xs: Iter<'T>) : Iter<'U> =
    let innerNextFun, innerState = xs

    let pack (subIterOpt: Iter<'U> option) (innerState: obj) (state: 'S) = box (subIterOpt, innerState, state)
    let unpack (outerState: obj) : Iter<'U> option * obj * 'S = unbox outerState

    let rec scanExLoop
      (ysOpt: Iter<'U> option)
      (innerState: obj)
      (state: 'S)
      : ('U * (Iter<'U> option * obj * 'S)) option =
      match ysOpt with
      | Some ys ->
        match next ys with
        | None -> scanExLoop None innerState state
        | Some (y, ys) -> Some(y, (Some ys, innerState, state))

      | None ->
        match innerNextFun innerState with
        | None -> None

        | Some (x, innerState) ->
          let ys, state = f state x
          scanExLoop (Some ys) innerState state

    let nextFun outerState : ('U * obj) option =
      let ysOpt, innerState, state = unpack outerState

      match scanExLoop ysOpt innerState state with
      | None -> None
      | Some (y, (ysOpt, innerState, state)) -> Some(y, pack ysOpt innerState state)

    nextFun, pack None innerState state

  let map (f: 'T -> 'U) (xs: Iter<'T>) : Iter<'U> =
    let innerNextFun, state = xs

    let nextFun (state: obj) : ('U * obj) option =
      match innerNextFun state with
      | None -> None
      | Some (x, state) -> Some(f x, state)

    nextFun, state

  // ---------------------------------------------
  // Constructor
  // ---------------------------------------------

  let empty () : Iter<'T> =
    let nextFun (_: obj) : ('T * obj) option = None
    nextFun, box ()

  let singleton (item: 'T) : Iter<'T> =
    let nextFun (state: obj) : ('T * obj) option =
      if unbox state = 0 then
        Some(item, box 1)
      else
        None

    nextFun, box 0

  let range (start: int) (endIndex: int) : Iter<int> =
    let nextFun state =
      let i = unbox state

      if i < endIndex then
        Some(i, box (i + 1))
      else
        None

    nextFun, box start

  let ofOption (opt: 'T option) : Iter<'T> =
    match opt with
    | Some item -> singleton item
    | None -> empty ()

  let ofList (xs: 'T list) : Iter<'T> =
    let nextFun (state: obj) : ('T * obj) option =
      match unbox state with
      | [] -> None
      | x :: xs -> Some(x, box xs)

    nextFun, box xs

  let init (count: int) (initializer: int -> 'T) : Iter<'T> = range 0 count |> map initializer

  let replicate (count: int) (item: 'T) : Iter<'T> = range 0 count |> map (fun _ -> item)

  let unfold (unfolder: 'S -> ('T * 'S) option) (state: 'S) : Iter<'T> =
    let nextFun (state: obj) : ('T * obj) option =
      match unfolder (unbox state) with
      | None -> None
      | Some (item, state) -> Some(item, box state)

    nextFun, box state

  // ---------------------------------------------
  // Transformer
  // ---------------------------------------------

  let choose (f: 'T -> 'U option) (xs: Iter<'T>) : Iter<'U> =
    let innerNextFun, state = xs

    let rec nextFun (state: obj) : ('U * obj) option =
      match innerNextFun state with
      | None -> None

      | Some (x, innerState) ->
        match f x with
        | None -> nextFun innerState
        | Some y -> Some(y, innerState)

    nextFun, state

  let collect (f: 'T -> Iter<'U>) (xs: Iter<'T>) : Iter<'U> =
    scanEx (fun () (x: 'T) -> f x, ()) () xs

  let scan (folder: 'S -> 'T -> 'S) (state: 'S) (xs: Iter<'T>) : Iter<'S> =
    scanEx
      (fun state x ->
        let state = folder state x
        singleton state, state)
      state
      xs

  let filter (pred: 'T -> bool) (xs: Iter<'T>) : Iter<'T> =
    xs
    |> choose (fun x -> if pred x then Some x else None)

  let mapi (f: int -> 'T -> 'U) (xs: Iter<'T>) : Iter<'U> =
    scanEx (fun (i: int) (x: 'T) -> singleton (f i x), i + 1) 0 xs

  let indexed (xs: Iter<'T>) : Iter<int * 'T> =
    scanEx (fun (i: int) (x: 'T) -> singleton (i, x), i + 1) 0 xs

  let append (first: Iter<'T>) (second: Iter<'T>) : Iter<'T> =
    scanEx
      (fun () (i: int) ->
        match i with
        | 0 -> first, ()
        | _ -> second, ())
      ()
      (range 0 2)

  // ---------------------------------------------
  // Consumer
  // ---------------------------------------------

  let isEmpty (xs: Iter<_>) : bool = Option.isNone (next xs)

  // wants Result<'S, 'A>, use 'S option * 'A option instead
  /// Runs an iterator updating a state.
  ///
  /// `folder state item` computes the next state `Ok s`
  /// or returns `Err a` to break from the iteration.
  let private foldEx (folder: 'S -> 'T -> 'S option * 'A option) (complete: 'S -> 'A) (state: 'S) (xs: Iter<'T>) : 'A =
    let nextFun, iterState = xs

    let rec foldExLoop (state: 'S) (iterState: obj) : 'A =
      match nextFun iterState with
      | None -> complete state

      | Some (item, iterState) ->
        match folder state item with
        | Some state, None -> foldExLoop state iterState
        | None, Some result -> result
        | _ ->
          assert false
          exit 1

    foldExLoop state iterState

  let fold (folder: 'S -> 'T -> 'S) (state: 'S) (xs: Iter<'T>) : 'S =
    foldEx (fun state item -> Some(folder state item), None) id state xs

  let forall (pred: 'T -> bool) (xs: Iter<'T>) : bool =
    foldEx
      (fun _ x ->
        if pred x then
          Some(), None // Ok ()
        else
          None, Some false) // Err false
      (fun () -> true)
      ()
      xs

  let exists (pred: 'T -> bool) (xs: Iter<'T>) : bool =
    foldEx
      (fun _ x ->
        if pred x then
          None, Some true // Err true
        else
          Some(), None) // Ok ()
      (fun () -> false)
      ()
      xs

  let tryPick (picker: 'T -> 'U option) (xs: Iter<'T>) : 'U option =
    match next (choose picker xs) with
    | Some (it, _) -> Some it
    | _ -> None

  let toList (xs: Iter<'T>) : 'T list =
    xs |> fold (fun xs x -> x :: xs) [] |> List.rev
