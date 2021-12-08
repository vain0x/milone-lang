/// Extends `List` module.
module rec MiloneStd.StdList

module SB = MiloneStd.StdStringBase

module List =
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
