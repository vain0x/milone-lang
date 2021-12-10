module rec MiloneStd.StdAssoc

type Assoc<'K, 'T> = ('K * 'T) list

module Assoc =
  let tryFind keyCompare (key: 'K) (assoc: Assoc<'K, 'T>) : 'T option =
    let rec assocFindLoop assoc =
      match assoc with
      | [] -> None
      | (k, v) :: _ when keyCompare k key = 0 -> Some v
      | _ :: assoc -> assocFindLoop assoc

    assocFindLoop assoc
