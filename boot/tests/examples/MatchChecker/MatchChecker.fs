/// Algorithm to check covering of match expressions.
///
/// ## References
///
/// - "Pattern matching covering check used in the Swift compiler"
///   <https://qiita.com/ukitaka/items/7345e74116e11eb10f33> (written in Japanese)
/// - "A generic algorithm for checking exhaustivity of pattern matching"
///   <https://infoscience.epfl.ch/record/225497> (written in English)
module rec MatchChecker

// -----------------------------------------------
// Polyfills
// -----------------------------------------------

// Basic auxillary functions.

let id x = x

let ignore _ = ()

let fst (x, _) = x

let cons head tail = head :: tail

let listIsEmpty xs =
  match xs with
  | [] ->
    true
  | _ ->
    false

let listRev xs =
  let rec go acc xs =
    match xs with
    | [] ->
      acc
    | x :: xs ->
      go (x :: acc) xs
  go [] xs

let listMap f xs =
  let rec go acc xs =
    match xs with
    | [] ->
      listRev acc
    | x :: xs ->
      go (f x :: acc) xs
  go [] xs

let listMapWithIndex f xs =
  let rec go acc i xs =
    match xs with
    | [] ->
      listRev acc
    | x :: xs ->
      go (f i x :: acc) (i + 1) xs
  go [] 0 xs

let listForAll p xs =
  let rec go xs =
    match xs with
    | [] ->
      true
    | x :: xs ->
      p x && go xs
  go xs

// USAGE: items |> listFold (fun oldState item -> newState) initialState
let listFold folder state xs =
  let rec go state xs =
    match xs with
    | [] ->
      state
    | x :: xs ->
      go (folder state x) xs
  go state xs

let strConcat xs =
  let rec go (xs: string list) =
    match xs with
    | [] ->
      ""
    | x :: xs ->
      x + go xs
  go xs

let failwith msg =
  printfn "ERROR %s" msg
  exit 1

// -----------------------------------------------
// Types
// -----------------------------------------------

[<RequireQualifiedAccess>]
type Ty =
  /// Example of open type.
  /// We assume the number of integers is infinite (rather than 2^N) here.
  | Int

  /// Example of product type.
  | Tuple
    of Ty list

  /// Example of recursive sum type.
  | List
    of Ty

// -----------------------------------------------
// Patterns
// -----------------------------------------------

[<RequireQualifiedAccess>]
type Pat =
  /// `_`
  | Discard

  /// E.g. `1`.
  | IntLit
    of int

  /// `x, y, ...`
  | TupleLit
    of Pat list

  /// `[]`
  | Nil

  /// `head :: tail`
  | Cons
    of Pat * Pat

// -----------------------------------------------
// Spaces
// -----------------------------------------------

/// Set of value that patterns cover or types allow.
[<RequireQualifiedAccess>]
type Space =
  /// Space of wildcard patterns or open types.
  | Full

  /// Space identified by int.
  | Variant
    of int * Space

  /// Reference of space, identified by int.
  /// Used for recursive spaces. Never empty.
  | Ref
    of int * (unit -> Space)

  | Union
    of Space list

let spaceFull =
  Space.Full

let spaceRef serial thunk =
  Space.Ref (serial, thunk)

let spaceEmpty =
  Space.Union []

let spaceVariant variant =
  Space.Variant variant

/// Sum of spaces. These spaces are disjoint.
let spaceSum variants =
  variants |> listMap spaceVariant |> spaceUnion

/// Union of spaces.
/// FIXME: Merge spaces of the same variants/refs.
let spaceUnion spaces =
  let rec go spaces acc =
    match spaces with
    | _ when false ->
      failwith "NEVER: suppress warning"

    | [] ->
      acc

    | Space.Union subspaces :: spaces ->
      acc |> go subspaces |> go spaces

    | space :: spaces when space |> spaceIsEmpty ->
      acc |> go spaces

    | space :: spaces ->
      (space :: acc) |> go spaces

  match go spaces [] with
  | [space] ->
    space

  | spaces ->
    Space.Union spaces

/// Gets if the space is empty.
let rec spaceIsEmpty space =
  let result =
    match space with
    | Space.Ref _
    | Space.Full ->
      false

    | Space.Variant (_, subspace) ->
      subspace |> spaceIsEmpty

    | Space.Union spaces ->
      spaces |> listForAll spaceIsEmpty

    | _ ->
      failwith "NEVER: suppress warning"

  result

/// Excludes the second space from the first space.
/// Similar to difference of set.
let rec spaceExclude first second =
  match first, second with
  // Full space excludes anything because wildcard patterns match anything.
  | _, Space.Full
  | Space.Union [], _ ->
    spaceEmpty

  // No exclusion if the second is empty.
  | _, Space.Union [] ->
    first

  // Matching variant reduces the payload space.
  | Space.Variant (tag, firstSpace), Space.Variant (secondTag, secondSpace)
    when tag = secondTag ->
    let subspace = spaceExclude firstSpace secondSpace
    spaceVariant (tag, subspace)

  // Non-matching variants do nothing because disjoint.
  | Space.Variant _, Space.Variant _ ->
    first

  // `first - (x + y)` = `(first - x) - y`
  | _, Space.Union seconds ->
    seconds |> listFold spaceExclude first

  // `(x + y) - second` = (x - second) + (y - second)`.
  // Too inefficient but okay for real patterns and types.
  | Space.Union firsts, _ ->
    firsts |> listMap (fun first -> spaceExclude first second) |> spaceUnion

  // `x - x = {}` even if x is infinite.
  | Space.Ref (firstRef, _), Space.Ref (secondRef, _)
    when firstRef = secondRef ->
    spaceEmpty

  // Expand the ref space to calculate the result.
  // This doesn't run into an infinite loop
  // because the second (space of patterns) is finite.
  | Space.Ref (_, thunk), _ ->
    spaceExclude (thunk ()) second

  | _, Space.Ref (_, thunk) ->
    // Never happens because patterns don't generate ref spaces
    // at least in milone-lang... not true perhaps in Scala?
    assert false
    spaceExclude first (thunk ())

/// Gets if the `other` is subspace of the `cover`.
let spaceCovers other cover =
  spaceExclude other cover |> spaceIsEmpty

let spaceToString space =
  let rec go space acc =
    match space with
    | Space.Full ->
      acc |> cons "full"

    | Space.Ref (refId, _) ->
      acc |> cons "ref#" |> cons (string refId)

    | Space.Variant (variantId, subspace) ->
      acc |> cons "var#" |> cons (string variantId) |> cons " (" |> go subspace |> cons ")"

    | Space.Union [] ->
      acc |> cons "empty"

    | Space.Union (subspace :: subspaces) ->
      let acc = acc |> cons "+(" |> go subspace
      subspaces
      |> listFold (fun acc space -> acc |> cons ", " |> go space) acc
      |> cons ")"

    | _ ->
      failwith "NEVER: suppress warning"

  [] |> go space |> listRev |> strConcat

// -----------------------------------------------
// Space generation
// -----------------------------------------------

let NilId = 0
let ConsId = 1
let ConsHeadId = 0
let ConsTailId = 1
let ListRefId = -1

/// Generates the space of a type.
/// The result can be infinite (e.g. lists).
let tyToSpace ty =
  let rec go ty =
    match ty with
    | Ty.Int ->
      spaceFull

    | Ty.Tuple [] ->
      // No need to split into cases.
      spaceFull

    | Ty.Tuple itemTys ->
      // The space of tuple is the *sum* of item types.
      // These spaces are separated. Use indexes as identifiers.
      itemTys |> listMapWithIndex (fun i itemTy -> i, go itemTy) |> spaceSum

    | Ty.List itemTy ->
      let itemSpace = go itemTy

      // Space of the list type is recursive.
      // The function reifies it step by step.
      let rec thunk () =
        // Space of the content of `cons`, i.e. ('a * 'a list).
        let consSpace =
          spaceSum
            [
              ConsHeadId, itemSpace
              ConsTailId, spaceRef ListRefId thunk
            ]
        spaceSum
          [
            NilId, spaceFull
            ConsId, consSpace
          ]

      spaceRef ListRefId thunk

    | _ ->
      failwith "NEVER"

  go ty

/// Generates the space of a pattern.
let patToSpace pat =
  let rec go pat =
    match pat with
    | Pat.Discard ->
      spaceFull

    | Pat.IntLit _ ->
      spaceEmpty

    | Pat.TupleLit [] ->
      // Any value of unit type matches with the pattern.
      spaceFull

    | Pat.TupleLit itemPats ->
      itemPats |> listMapWithIndex (fun i itemPat -> i, go itemPat) |> spaceSum

    | Pat.Nil ->
      spaceSum
        [
          NilId, spaceFull
        ]

    | Pat.Cons (headPat, tailPat) ->
      let consSpace =
        spaceSum
          [
            ConsHeadId, go headPat
            ConsTailId, go tailPat
          ]
      spaceSum
        [
          ConsId, consSpace
        ]

    | _ ->
      failwith "NEVER"

  go pat

let patsToSpace pats =
  pats |> listMap patToSpace |> spaceUnion

// -----------------------------------------------
// Testing
// -----------------------------------------------

type Covering =
  | Covering
  | Open

let main _ =
  assert (spaceEmpty |> spaceIsEmpty)

  // `_ :: _`
  let anyConsPat = Pat.Cons (Pat.Discard, Pat.Discard)

  let testCases =
    [
      "unit with ()",
        Ty.Tuple [],
        [Pat.TupleLit []],
        Covering

      "int with literal pats",
        Ty.Int,
        [Pat.IntLit 1],
        Open

      "int with _",
        Ty.Int,
        [Pat.Discard],
        Covering

      "int with 1|_",
        Ty.Int,
        [Pat.IntLit 1; Pat.Discard],
        Covering

      "int * unit with _, ()",
        Ty.Tuple [Ty.Int; Ty.Tuple []],
        [Pat.TupleLit [Pat.Discard; Pat.TupleLit []]],
        Covering

      "int list with []",
        Ty.List Ty.Int,
        [Pat.Nil],
        Open

      "int list with _::_",
        Ty.List Ty.Int,
        [anyConsPat],
        Open

      "int list with [] | _::_",
        Ty.List Ty.Int,
        [Pat.Nil; anyConsPat],
        Covering

      "int list with [] | [_] | _::_::_",
        Ty.List Ty.Int,
        [
          Pat.Nil
          Pat.Cons (Pat.Discard, Pat.Nil)
          Pat.Cons (Pat.Discard, anyConsPat)
        ],
        Covering

      "int list list with [] | [[]] | [_::_] | _::_::_",
        Ty.List (Ty.List Ty.Int),
        [
          Pat.Nil
          Pat.Cons (Pat.Nil, Pat.Nil)
          Pat.Cons (anyConsPat, Pat.Discard)
          Pat.Cons (Pat.Discard, anyConsPat)
        ],
        Covering

      "int list * int list with [], [] | [], _::_ | _::_, [] | _::_, _::_",
        Ty.Tuple [Ty.List Ty.Int; Ty.List Ty.Int],
        [
          Pat.TupleLit [Pat.Nil; Pat.Nil]
          Pat.TupleLit [anyConsPat; Pat.Nil]
          Pat.TupleLit [Pat.Nil; anyConsPat]
          Pat.TupleLit [anyConsPat; anyConsPat]
        ],
        Covering
    ]

  let ok =
    testCases |> listMap (fun (name, ty, pats, covering) ->
      // The pattern matching is covering if
      // that the space of patterns covers that of the type.
      let tySpace = ty |> tyToSpace
      let patSpace = pats |> patsToSpace
      let actual = if patSpace |> spaceCovers tySpace then Covering else Open

      let ok, msg =
        match covering, actual with
        | Covering, Covering
        | Open, Open ->
          true, "OK"

        | Covering, Open ->
          false, "NG. Expected covering but open"

        | _ ->
          false, "NG. Expected open but covering"

      printfn "%s: %s" name msg

      if not ok then
        // Print for debugging.
        printfn "  ty: %s" (tySpace |> spaceToString)
        printfn "  pats: %s" (patSpace |> spaceToString)

      ok
    )
    |> listForAll id

  let exitCode = if ok then 0 else 1
  exitCode
