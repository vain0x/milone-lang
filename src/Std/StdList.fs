/// Extends `List` module.
module rec Std.StdList

module SB = Std.StdStringBase

module List =
  /// Removes initial `count` items.
  ///
  /// Count is tolerant. When `count` is negative or exceeds length, returns `[]` unlike `List.skip`.
  let drop (count: int) (xs: 'T list) : 'T list =
    let rec listDropLoop count xs =
      match xs with
      | [] -> []
      | _ when count <= 0 -> xs
      | _ :: xs -> listDropLoop (count - 1) xs

    listDropLoop count xs

  /// Pairs two items in same position from two lists.
  ///
  /// If two lists have different length, some elements have no pair.
  /// These items are returns as second and third result.
  ///
  /// To check two list has same length, do:
  ///
  /// ```fsharp
  ///   match List.zipEx xs ys with
  ///   | it, [], [] -> Some it
  ///   | _ -> None
  /// ```
  let zipEx (xs: 'T list) (ys: 'U list) : ('T * 'U) list * 'T list * 'U list =
    let rec listZipLoop acc xs ys =
      match xs, ys with
      | _, []
      | [], _ -> List.rev acc, xs, ys

      | x :: xs, y :: ys -> listZipLoop ((x, y) :: acc) xs ys

    listZipLoop [] xs ys

  let private doSort (unique: bool) itemCompare xs =
    let rec appendRev acc xs =
      match xs with
      | [] -> acc
      | x :: xs -> appendRev (x :: acc) xs

    // Induction of xs, ys while maintaining invariant:
    // `merge (xs, xn) (ys, yn) = (zs, zn), d` where
    // `zs.[0..zn - 1]` is the merge of `xs.[0..xn - 1]` and `ys.[0..yn - 1]`,
    // and `d` is the number of duplicated items.
    let rec merge (zs, zn) d (xs, xn) (ys, yn) =
      let noXs () = (appendRev ys zs, zn + yn), d
      let noYs () = (appendRev xs zs, zn + xn), d

      match xs, ys with
      | _ when xn = 0 -> noXs ()
      | [], _ -> noXs ()

      | _ when yn = 0 -> noYs ()
      | _, [] -> noYs ()

      | x :: xs1, y :: ys1 ->
        let c = itemCompare x y

        if c > 0 then
          merge (y :: zs, zn + 1) d (xs, xn) (ys1, yn - 1)
        else if c = 0 && unique then
          merge (zs, zn) (d + 1) (xs, xn) (ys1, yn - 1)
        else
          merge (x :: zs, zn + 1) d (xs1, xn - 1) (ys, yn)

    // `sortLoop (xs, xn) = (zs, zn), xs1, d` where
    // `zs.[0..xn - 1]` is the sort of `xs.[0..xn - 1]`,
    // `xs1 = xs.[xn..]`,
    // and `d` is the number of duplicated items.
    let rec sortLoop (xs, n) =
      if n <= 1 then
        (xs, n), drop n xs, 0
      else
        let m = n / 2
        let (xs, xn), xs1, d1 = sortLoop (xs, m)
        let (ys, yn), ys1, d2 = sortLoop (xs1, n - m)
        let (zs, zn), d3 = merge ([], 0) 0 (xs, xn) (ys, yn)
        (zs, zn), ys1, d1 + d2 + d3

    let xn = List.length xs
    let (zs, zn), ws, d = sortLoop (xs, xn)
    assert (zn + d = xn)
    assert (ws |> List.isEmpty)
    List.truncate zn zs

  /// Sorts a list.
  let sortWith (itemCompare: 'T -> 'T -> int) (xs: 'T list) : 'T list = doSort false itemCompare xs

  /// Sorts a list and removes all duplicated items.
  let sortUniqueWith (itemCompare: 'T -> 'T -> int) (xs: 'T list) : 'T list = doSort true itemCompare xs

  // Structural operations:

  let equals (itemEquals: 'T -> 'T -> bool) (ls: 'T list) (rs: 'T list) : bool =
    let rec listEqualsLoop ls rs =
      match ls, rs with
      | [], [] -> true

      | [], _
      | _, [] -> false

      | l :: ls, r :: rs -> itemEquals l r && listEqualsLoop ls rs

    listEqualsLoop ls rs

  let compare (itemCompare: 'T -> 'T -> int) (ls: 'T list) (rs: 'T list) : int =
    let rec listCompareLoop ls rs =
      match ls, rs with
      | [], [] -> 0
      | [], _ -> -1
      | _, [] -> 1

      | l :: ls, r :: rs ->
        let c = itemCompare l r

        if c <> 0 then
          c
        else
          listCompareLoop ls rs

    listCompareLoop ls rs

  let debug (itemDebug: 'T -> string) (xs: 'T list) : string =
    match xs with
    | [] -> "[]"

    | _ ->
      let xs =
        xs |> List.map itemDebug |> SB.concat "; "

      [ "["; xs; "]" ] |> SB.concat " "
