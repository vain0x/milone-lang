/// # Loop
///
/// ## Description
///
/// `Loop` is an interface of an iteration over collection.
///
/// ## Comparison to sequences
///
/// `Loop` is similar to `seq` in F# but not the same.
///
/// `Loop<'S, 'T>` carries the type of internal state `'S` in its type.
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
/// `'S`: Internal state of iteration.
/// `'T`: Item of collection.
type private Folder<'S, 'T> = 'S -> 'T -> bool * 'S

/// Abstraction of iteration.
///
/// `'S`: Internal state of iteration.
/// `'T`: Item of collection.
type Loop<'S, 'T> = Folder<'S, Folder<'S, 'T>>

module Loop =
  /// Runs a loop to fold items.
  let fold (folder: 'S -> 'T -> 'S) (state: 'S) (xs: Loop<'S, 'T>) : 'S =
    xs state (fun state item -> true, folder state item)
    |> snd

  // -----------------------------------------------
  // Creation
  // -----------------------------------------------

  let empty () : Loop<_, 'T> =
    fun state (folder: Folder<_, _>) -> true, state

  let singleton (x: 'T) : Loop<_, 'T> = fun state folder -> folder state x

  /// Generates integers such that `start <= i && i < endIndex`.
  let range (start: int) (endIndex: int) : Loop<_, int> =
    fun state folder ->
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

  let init (len: int) (f: int -> 'T) : Loop<_, 'T> =
    assert (len >= 0)

    fun state folder ->
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

  let replicate (len: int) (item: 'T) : Loop<_, 'T> =
    assert (len >= 0)

    fun state folder ->
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

  let ofOption (opt: 'T option) : Loop<_, 'T> =
    match opt with
    | None -> empty ()
    | Some x -> singleton x

  let ofList (xs: 'T list) : Loop<'S, 'T> =
    fun state folder ->
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

  // -----------------------------------------------
  // Transformation
  // -----------------------------------------------

  let map (f: 'T -> 'U) (xs: Loop<'S, 'T>) : Loop<'S, 'U> =
    fun state folder -> xs state (fun state item -> folder state (f item))

  let filter (pred: 'T -> bool) (xs: Loop<'S, 'T>) : Loop<'S, 'T> =
    fun state folder ->
      xs state (fun state item ->
        if pred item then
          folder state item
        else
          true, state)

  let collect (f: 'T -> Loop<'S, 'U>) (xs: Loop<'S, 'T>) : Loop<'S, 'U> =
    fun state folder -> xs state (fun state item -> (f item) state folder)

  let append (xs: Loop<'S, 'T>) (ys: Loop<'S, 'T>) : Loop<'S, 'T> =
    fun state folder ->
      let ok, state = xs state folder

      if ok then
        ys state folder
      else
        false, state

  // -----------------------------------------------
  // Consumer
  // -----------------------------------------------

  let isEmpty (xs: Loop<_, _>) : bool = forall (fun _ -> false) xs

  let length (xs: Loop<int, _>) : int =
    xs 0 (fun len _ -> true, len + 1) |> snd

  let forall (pred: 'T -> bool) (xs: Loop<_, 'T>) : bool = xs () (fun _ x -> pred x, ()) |> fst

  let exists (pred: 'T -> bool) (xs: Loop<_, 'T>) : bool =
    xs () (fun _ x -> not (pred x), ()) |> fst |> not

  let toList (xs: Loop<_, 'T>) : 'T list =
    xs [] (fun xs x -> true, x :: xs)
    |> snd
    |> List.rev

  let concatString (sep: string) (xs: Loop<_, string>) : string = xs |> toList |> S.concat sep
