/// Algorithm to check covering of match expressions.
module rec MatchChecker

// -----------------------------------------------
// Polyfills
// -----------------------------------------------

let id x = x

let ignore _ = ()

let fst (x, _) = x

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
  | Int
  | Tuple
    of Ty list
  | List
    of Ty

// -----------------------------------------------
// Patterns
// -----------------------------------------------

[<RequireQualifiedAccess>]
type Pat =
  /// `_`
  | Discard

  | IntLit
    of int

  | TupleLit
    of Pat list

  | Nil
  | Cons
    of Pat * Pat

// -----------------------------------------------
// Space
// -----------------------------------------------

/// Set of value that patterns cover or types allow.
[<RequireQualifiedAccess>]
type Space =
  /// Space of wildcard patterns or open types.
  | Full

  /// Space identified by int.
  | Variant
    of int * Space

  /// Reference of space. Used for recursive spaces. Never empty.
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

let spaceUnit =
  spaceFull

let spaceVariant variant =
  Space.Variant variant

let spaceSum variants =
  variants |> listMap spaceVariant |> spaceUnion

/// Union of spaces.
/// FIXME: merge variants
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

  // printfn "%s is %s" (space |> spaceToString) (if result then "empty" else "NOT empty")
  result

let rec spaceExclude first second =
  match first, second with
  | _, Space.Full
  | Space.Union [], _ ->
    // printfn "%s - %s = %s (empty)" (first |> spaceToString) (second |> spaceToString) (spaceEmpty |> spaceToString)
    spaceEmpty

  | _, Space.Union [] ->
    // printfn "%s - %s = %s (first)" (first |> spaceToString) (second |> spaceToString) (first |> spaceToString)
    first

  | Space.Variant (tag, firstSpace), Space.Variant (secondTag, secondSpace)
    when tag = secondTag ->
    let subspace = spaceExclude firstSpace secondSpace
    spaceVariant (tag, subspace)

  | Space.Variant _, Space.Variant _ ->
    first

  | _, Space.Union seconds ->
    seconds |> listFold spaceExclude first

  | Space.Union firsts, _ ->
    firsts |> listMap (fun first -> spaceExclude first second) |> spaceUnion

  | Space.Ref (firstRef, _), Space.Ref (secondRef, _)
    when firstRef = secondRef ->
    spaceEmpty

  | Space.Ref (_, thunk), _ ->
    spaceExclude (thunk ()) second

  | _, Space.Ref (_, thunk) ->
    // Never happens because patterns don't generate ref spaces
    // at least in milone-lang... not true perhaps in Scala?
    assert false
    spaceExclude first (thunk ())

let spaceCovers other cover =
  // printfn "%s covers %s?" (cover |> spaceToString) (other |> spaceToString)
  let excluded = spaceExclude other cover
  // printfn "%s - %s = %s" (other |> spaceToString) (cover |> spaceToString) (excluded |> spaceToString)
  excluded |> spaceIsEmpty

let spaceToString space =
  let cons head tail = head :: tail

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
let ConsRefId = -1

let tyToSpace ty =
  let rec go ty =
    match ty with
    | Ty.Int ->
      spaceFull

    | Ty.Tuple [] ->
      spaceUnit

    | Ty.Tuple itemTys ->
      itemTys |> listMapWithIndex (fun i itemTy -> i, go itemTy) |> spaceSum

    | Ty.List itemTy ->
      let itemSpace = go itemTy
      let rec thunk () =
        let consSpace =
          spaceSum
            [
              ConsHeadId, itemSpace
              ConsTailId, spaceRef ConsRefId thunk
            ]
        spaceSum
          [
            NilId, spaceUnit
            ConsId, consSpace
          ]
      spaceRef ConsRefId thunk

    | _ ->
      failwith "NEVER"

  go ty

let patToSpace pat =
  let rec go pat =
    match pat with
    | Pat.Discard ->
      spaceFull

    | Pat.IntLit _ ->
      // We assume any number of int patterns can't cover the space.
      spaceEmpty

    | Pat.TupleLit [] ->
      spaceUnit

    | Pat.TupleLit itemPats ->
      itemPats |> listMapWithIndex (fun i itemPat -> i, go itemPat) |> spaceSum

    | Pat.Nil ->
      spaceSum [NilId, spaceUnit]

    | Pat.Cons (headPat, tailPat) ->
      let consSpace =
        spaceSum
          [
            ConsHeadId, go headPat
            ConsTailId, go tailPat
          ]
      spaceSum [ConsId, consSpace]

    | _ ->
      failwith "NEVER"

  go pat

let patsToSpace pats =
  pats |> listMap patToSpace |> spaceUnion

type Covering =
  | Covering
  | Open

let coveringToString covering =
  match covering with
  | Covering -> "Covering"
  | Open -> "open"

let main _ =
  assert (spaceEmpty |> spaceIsEmpty)

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
      printfn "  ty: %s" (tySpace |> spaceToString)
      printfn "  pats: %s" (patSpace |> spaceToString)
      ok
    )
    |> listForAll id

  let exitCode = if ok then 0 else 1
  exitCode
