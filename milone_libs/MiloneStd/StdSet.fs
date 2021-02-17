/// Tree-based set data structure. See StdMap for details.
module rec MiloneStd.StdSet

module M = MiloneStd.StdMap

type TreeSet<'T> = M.TreeMap<'T, unit>

let empty (compare: 'T -> 'T -> int): TreeSet<'T> = M.empty compare

let isEmpty (set: TreeSet<_>): bool = M.isEmpty set

let contains (item: 'T) (set: TreeSet<'T>): bool = M.containsKey item set

let add (item: 'T) (set: TreeSet<'T>): TreeSet<'T> = M.add item () set

let remove (item: 'T) (set: TreeSet<'T>): bool * TreeSet<'T> =
  let itemOpt, set = M.remove item set

  let ok =
    match itemOpt with
    | Some () -> true
    | None -> false

  ok, set

let fold (folder: 'S -> 'T -> 'S) (state: 'S) (set: TreeSet<'T>): 'S =
  M.fold (fun state item () -> folder state item) state set

let ofList (compare: 'T -> 'T -> int) (xs: 'T list): TreeSet<'T> =
  M.ofList compare (List.map (fun item -> item, ()) xs)

let toList (set: TreeSet<'T>): 'T list = M.toKeys set
