/// Extends `List` module.
module rec MiloneStd.StdList

module SB = MiloneStd.StdStringBase

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
