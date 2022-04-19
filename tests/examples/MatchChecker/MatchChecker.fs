/// Algorithm to check covering of match expressions.
///
/// ## References
///
/// - "Pattern matching covering check used in the Swift compiler"
///   <https://qiita.com/ukitaka/items/7345e74116e11eb10f33> (written in Japanese)
/// - "A generic algorithm for checking exhaustivity of pattern matching"
///   <https://infoscience.epfl.ch/record/225497> (written in English)
module rec MatchChecker.Program

// -----------------------------------------------
// Polyfills
// -----------------------------------------------

// Basic auxillary functions.

let failwith msg =
  printfn "ERROR %s" msg
  exit 1

let cons head tail = head :: tail

let listIsEmpty xs =
  match xs with
  | [] -> true
  | _ -> false

let listRev xs =
  let rec go acc xs =
    match xs with
    | [] -> acc
    | x :: xs -> go (x :: acc) xs

  go [] xs

let listMap f xs =
  let rec go acc xs =
    match xs with
    | [] -> listRev acc
    | x :: xs -> go (f x :: acc) xs

  go [] xs

let listMapWithIndex f xs =
  let rec go acc i xs =
    match xs with
    | [] -> listRev acc
    | x :: xs -> go (f i x :: acc) (i + 1) xs

  go [] 0 xs

let listForAll p xs =
  let rec go xs =
    match xs with
    | [] -> true
    | x :: xs -> p x && go xs

  go xs

let listExists p xs =
  // xs |> listForAll (fun x -> p x |> not) |> not
  let rec go xs =
    match xs with
    | [] -> false
    | x :: xs -> p x || go xs

  go xs

// USAGE: items |> listFold (fun oldState item -> newState) initialState
let listFold folder state xs =
  let rec go state xs =
    match xs with
    | [] -> state
    | x :: xs -> go (folder state x) xs

  go state xs

let listZip xs ys =
  let rec go acc xs ys =
    match xs, ys with
    | [], _
    | _, [] -> listRev acc
    | x :: xs, y :: ys -> go ((x, y) :: acc) xs ys

  go [] xs ys

let stringConcat xs =
  let rec go (xs: string list) =
    match xs with
    | [] -> ""
    | x :: xs -> x + go xs

  go xs

// -----------------------------------------------
// Types
// -----------------------------------------------

[<RequireQualifiedAccess>]
type Ty =
  /// Example of open type.
  /// We assume the number of integers is infinite (rather than 2^N) here.
  | Int

  /// Example of product type.
  | Tuple of Ty list

  /// Example of recursive sum type.
  | List of Ty

// -----------------------------------------------
// Patterns
// -----------------------------------------------

[<RequireQualifiedAccess>]
type Pat =
  /// `_`
  | Discard

  /// E.g. `1`.
  | IntLit of int

  /// E.g. `_, _, _`.
  | TupleLit of Pat list

  /// `[]`
  | Nil

  /// `head :: tail`
  | Cons of Pat * Pat

// -----------------------------------------------
// Spaces
// -----------------------------------------------

/// Set of value that patterns cover or types allow.
[<RequireQualifiedAccess>]
type Space =
  /// Space of wildcard patterns or open types.
  | Full

  /// Space of a constructor, e.g. `Nil(())`, `Cons(head, tail)`.
  | Ctor of tag: string * items: Space list

  /// Space of a constructor before decomposition.
  /// Can be decomposed into a space by using `thunk`.
  /// Used to represent a recursive space. Never empty.
  | Ref of tag: string * thunk: (unit -> Space)

  | Union of Space list

let spaceFull = Space.Full

let spaceCtor tag items = Space.Ctor(tag, items)

let spaceRef tag thunk = Space.Ref(tag, thunk)

let spaceEmpty = Space.Union []

/// Union of spaces.
let spaceUnion spaces =
  let rec go spaces acc =
    match spaces with
    | [] -> listRev acc

    | Space.Union subspaces :: spaces -> acc |> go subspaces |> go spaces

    | space :: spaces when space |> spaceIsEmpty -> acc |> go spaces

    | space :: spaces -> (space :: acc) |> go spaces

    | _ -> failwith "NEVER: suppress warning"

  match go spaces [] with
  | [ space ] -> space

  | spaces -> Space.Union spaces

/// Gets if the space is empty.
let rec spaceIsEmpty space =
  let result =
    match space with
    | Space.Ctor (_, spaces) -> spaces |> listExists spaceIsEmpty

    | Space.Union spaces -> spaces |> listForAll spaceIsEmpty

    | _ -> false

  result

let spaceDecompose space =
  match space with
  | Space.Ref (_, thunk) ->
    let space = thunk ()
    assert (space |> spaceIsEmpty |> not)
    space

  | _ ->
    assert false
    space

/// Gets if the two spaces are disjoint, i.e., the intersection is empty.
// let spaceIsDisjoint first second =
//   let rec go (first, second) =
//     match first, second with
//     | Space.Ctor (tag, firsts), Space.Ctor (secondTag, seconds)
//       when tag = secondTag ->
//       listZip firsts seconds |> listExists go

//     | Space.Ctor _, Space.Ctor _->
//       true

//     | _, Space.Union seconds ->
//       seconds |> listForAll (fun second -> go (first, second))

//     | Space.Union firsts, _ ->
//       firsts |> listForAll (fun first -> go (first, second))

//     | Space.Ref (tag, _), Space.Ref (secondTag, _)
//       when tag = secondTag ->
//       false

//     | Space.Ref _, _ ->
//       go (spaceExpand first) second

//     | _, Space.Ref _ ->
//       go first (spaceExpand second)

//     | _ ->
//       assert false
//       false

//   go (first, second)

/// Excludes the second space from the first space.
/// Similar to difference of sets.
let rec spaceExclude first second =
  match first, second with
  | Space.Union [], _ -> spaceEmpty

  | _, Space.Union [] -> first

  // Full space excludes anything because wildcard patterns match anything.
  | _, Space.Full -> spaceEmpty

  | Space.Full, Space.Ctor _ -> spaceFull

  // Matching constructor reduces the space of items.
  | Space.Ctor (tag, firsts), Space.Ctor (secondTag, seconds) when tag = secondTag ->
    // `(s, t) - (u, v) = {} if s <= u and t <= v`.
    let dominant =
      listZip firsts seconds
      |> listForAll (fun (first, second) -> second |> spaceCovers first)

    if dominant then
      spaceEmpty
    else

      // add disjoint case here!

      // `(s, t) - (u, v) = (s - u, t) + (s, t - v)`.
      // For example, the space of bool^2 excluded by the `false, true` pattern
      // is "the left is not false, or the right is not true."
      firsts
      |> listMapWithIndex (fun i _ ->
        listZip firsts seconds
        |> listMapWithIndex (fun j (first, second) ->
          if i = j then
            spaceExclude first second
          else
            first)
        |> spaceCtor tag)
      |> spaceUnion

  // Non-matching constructors do nothing because disjoint.
  | Space.Ctor _, Space.Ctor _ -> first

  // `first - (x + y)` = `(first - x) - y`
  | _, Space.Union seconds -> seconds |> listFold spaceExclude first

  // `(x + y) - second` = (x - second) + (y - second)`.
  // Too inefficient but okay for small, hand-written patterns and types.
  | Space.Union firsts, _ ->
    firsts
    |> listMap (fun first -> spaceExclude first second)
    |> spaceUnion

  // `x - x = {}` even if x is infinite.
  | Space.Ref (tag, _), Space.Ref (secondTag, _) when tag = secondTag -> spaceEmpty

  // Decompose the ref space to calculate the result.
  // This doesn't run into an infinite loop
  // because the second (space of patterns) is finite.
  | Space.Ref _, _ -> spaceExclude (spaceDecompose first) second

  | _, Space.Ref _ ->
    // Never happens because patterns don't generate ref spaces
    // at least in milone-lang... not true perhaps in Scala?
    assert false
    spaceExclude first (spaceDecompose second)

/// Gets if the `other` is subspace of the `cover`.
let spaceCovers other cover =
  spaceExclude other cover |> spaceIsEmpty

let spaceToString space =
  let rec go space acc =
    match space with
    | Space.Full -> acc |> cons "full"

    | Space.Ctor (tag, []) -> acc |> cons tag

    | Space.Ctor (tag, item :: items) ->
      let acc = acc |> cons tag |> cons "(" |> go item

      items
      |> listFold (fun acc space -> acc |> cons ", " |> go space) acc
      |> cons ")"

    | Space.Ref (tag, _) -> acc |> cons tag

    | Space.Union [] -> acc |> cons "empty"

    | Space.Union (subspace :: subspaces) ->
      let acc = acc |> cons "+(" |> go subspace

      subspaces
      |> listFold (fun acc space -> acc |> cons ", " |> go space) acc
      |> cons ")"

    | _ -> failwith "NEVER: suppress warning"

  [] |> go space |> listRev |> stringConcat

// -----------------------------------------------
// Space generation
// -----------------------------------------------

/// Generates the space of a type.
let tyToSpace ty =
  let rec go ty =
    match ty with
    | Ty.Int -> spaceFull

    | Ty.Tuple itemTys -> itemTys |> listMap go |> spaceCtor "tuple"

    | Ty.List itemTy ->
      let itemSpace = go itemTy

      // Space of the list type is recursive.
      // The function reifies it step by step.
      let rec thunk () =
        spaceUnion [ spaceCtor "nil" []
                     spaceCtor "cons" [ itemSpace; spaceRef "list" thunk ] ]

      spaceRef "list" thunk

  go ty

/// Generates the space of a pattern.
let patToSpace pat =
  let rec go pat =
    match pat with
    | Pat.Discard -> spaceFull

    | Pat.IntLit _ -> spaceEmpty

    | Pat.TupleLit itemPats -> itemPats |> listMap go |> spaceCtor "tuple"

    | Pat.Nil -> spaceCtor "nil" []

    | Pat.Cons (headPat, tailPat) -> spaceCtor "cons" [ go headPat; go tailPat ]

    | _ -> failwith "NEVER: suppress warning"

  go pat

let patsToSpace pats =
  pats |> listMap patToSpace |> spaceUnion

// -----------------------------------------------
// Testing
// -----------------------------------------------

type Covering =
  | Covering
  | Open

let testSpaceIsEmpty () =
  assert (spaceEmpty |> spaceIsEmpty)

  assert (spaceUnion [ spaceEmpty
                       spaceUnion [ spaceEmpty ] ]
          |> spaceIsEmpty)

  assert (spaceFull |> spaceIsEmpty |> not)

  assert (spaceRef "ref" (fun () -> spaceFull)
          |> spaceIsEmpty
          |> not)

  assert (spaceUnion [ spaceEmpty; spaceFull ]
          |> spaceIsEmpty
          |> not)

  assert (spaceCtor "tuple" [] |> spaceIsEmpty |> not)

  assert (spaceCtor "tuple" [ spaceFull; spaceEmpty; spaceFull ]
          |> spaceIsEmpty)

  assert (tyToSpace (Ty.List Ty.Int) |> spaceIsEmpty |> not)

  assert (tyToSpace (Ty.List(Ty.Tuple []))
          |> spaceIsEmpty
          |> not)

let testSpaceToString () =
  let cases =
    [ "empty", spaceEmpty
      "full", spaceFull
      "nil", spaceCtor "nil" []
      "tuple(empty, full)", spaceCtor "tuple" [ spaceEmpty; spaceFull ]
      "full", tyToSpace Ty.Int
      "+(nil, cons(full, list))", tyToSpace (Ty.List Ty.Int) |> spaceDecompose
      "cons(full, nil)", patToSpace (Pat.Cons(Pat.Discard, Pat.Nil)) ]

  let ok =
    cases
    |> listMap (fun (expected, space) ->
      let actual = space |> spaceToString

      if actual = expected then
        true
      else
        printfn "%s: NG (%s)" expected actual
        false)
    |> listForAll id

  assert ok

let main _ =
  testSpaceIsEmpty ()
  testSpaceToString ()

  // `_ :: _`
  let anyConsPat = Pat.Cons(Pat.Discard, Pat.Discard)

  let testCases =
    [ "unit with ()", Ty.Tuple [], [ Pat.TupleLit [] ], Covering

      "int with literal pats", Ty.Int, [ Pat.IntLit 1 ], Open

      "int with _", Ty.Int, [ Pat.Discard ], Covering

      "int with 1|_", Ty.Int, [ Pat.IntLit 1; Pat.Discard ], Covering

      "int * unit with _, ()",
      Ty.Tuple [ Ty.Int; Ty.Tuple [] ],
      [ Pat.TupleLit [ Pat.Discard
                       Pat.TupleLit [] ] ],
      Covering

      "int * int with 1, _ | _, 1",
      Ty.Tuple [ Ty.Int; Ty.Int ],
      [ Pat.TupleLit [ Pat.IntLit 1
                       Pat.Discard ]
        Pat.TupleLit [ Pat.Discard
                       Pat.IntLit 1 ] ],
      Open

      "int list with []", Ty.List Ty.Int, [ Pat.Nil ], Open

      "int list with _::_", Ty.List Ty.Int, [ anyConsPat ], Open

      "int list with [] | _::_", Ty.List Ty.Int, [ Pat.Nil; anyConsPat ], Covering

      "int list with [] | [_] | _::_::_",
      Ty.List Ty.Int,
      [ Pat.Nil
        Pat.Cons(Pat.Discard, Pat.Nil)
        Pat.Cons(Pat.Discard, anyConsPat) ],
      Covering

      "int list list with [] | [[]] | [_::_] | _::_::_",
      Ty.List(Ty.List Ty.Int),
      [ Pat.Nil
        Pat.Cons(Pat.Nil, Pat.Nil)
        Pat.Cons(anyConsPat, Pat.Discard)
        Pat.Cons(Pat.Discard, anyConsPat) ],
      Covering

      "int list * int list with [], [] | [], _::_ | _::_, [] | _::_, _::_",
      Ty.Tuple [ Ty.List Ty.Int
                 Ty.List Ty.Int ],
      [ Pat.TupleLit [ Pat.Nil; Pat.Nil ]
        Pat.TupleLit [ anyConsPat; Pat.Nil ]
        Pat.TupleLit [ Pat.Nil; anyConsPat ]
        Pat.TupleLit [ anyConsPat; anyConsPat ] ],
      Covering ]

  let ok =
    testCases
    |> listMap (fun (name, ty, pats, covering) ->
      // The pattern matching is covering if
      // that the space of patterns covers that of the type.
      let tySpace = ty |> tyToSpace
      let patSpace = pats |> patsToSpace

      let actual =
        if patSpace |> spaceCovers tySpace then
          Covering
        else
          Open

      let ok, msg =
        match covering, actual with
        | Covering, Covering
        | Open, Open -> true, "OK"

        | Covering, Open -> false, "NG. Expected covering but open"

        | _ -> false, "NG. Expected open but covering"

      printfn "%s: %s" name msg

      if not ok then
        // Print for debugging.
        printfn "  ty: %s" (tySpace |> spaceToString)
        printfn "  pats: %s" (patSpace |> spaceToString)

      ok)
    |> listForAll id

  let exitCode = if ok then 0 else 1
  exitCode
