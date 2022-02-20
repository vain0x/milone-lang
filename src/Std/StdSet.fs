/// Tree-based set data structure. See StdMap for details.
module rec Std.StdSet

open Std.StdMap

type TreeSet<'T> = TreeMap<'T, unit>

module TSet =
  let empty (compare: 'T -> 'T -> int) : TreeSet<'T> = TMap.empty compare

  let isEmpty (set: TreeSet<_>) : bool = TMap.isEmpty set

  let contains (item: 'T) (set: TreeSet<'T>) : bool = TMap.containsKey item set

  let add (item: 'T) (set: TreeSet<'T>) : TreeSet<'T> = TMap.add item () set

  let remove (item: 'T) (set: TreeSet<'T>) : bool * TreeSet<'T> =
    let unitOpt, set = TMap.remove item set

    let isRemoved =
      match unitOpt with
      | Some () -> true
      | None -> false

    isRemoved, set

  let fold (folder: 'S -> 'T -> 'S) (state: 'S) (set: TreeSet<'T>) : 'S =
    TMap.fold (fun state item () -> folder state item) state set

  let ofList (compare: 'T -> 'T -> int) (xs: 'T list) : TreeSet<'T> =
    TMap.ofList compare (List.map (fun item -> item, ()) xs)

  let toList (set: TreeSet<'T>) : 'T list = TMap.toKeys set
