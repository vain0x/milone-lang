module rec MiloneStd.StdMultimap

open MiloneStd.StdMap

/// Mapping from key to a list of value.
type Multimap<'K, 'T> = TreeMap<'K, 'T list>

module Multimap =
  /// Finds all values in mapping.
  let find (key: 'K) (multimap: Multimap<'K, 'T>) : 'T list =
    match multimap |> TMap.tryFind key with
    | Some it -> it
    | None -> []

  /// Inserts an item in addition to current items.
  let add (key: 'K) (item: 'T) (multimap: Multimap<'K, 'T>) : Multimap<'K, 'T> =
    let items = multimap |> find key
    TMap.add key (item :: items) multimap

  /// Creates a multimap from a list of key-value pairs.
  let ofList (keyCompare: 'K -> 'K -> int) (entries: ('K * 'T) list) : Multimap<'K, 'T> =
    entries
    |> List.fold (fun map (key, value) -> add key value map) (TMap.empty keyCompare)
