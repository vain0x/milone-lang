/// Provides immutable map (associative array) data structure
/// based on red-black tree.
///
/// Requires comparison of keys.
module rec MiloneStd.StdMap

// -----------------------------------------------
// Nodes
// -----------------------------------------------

[<NoEquality; NoComparison>]
type Color =
  | R
  | B

[<NoEquality; NoComparison>]
type Node<'K, 'T> =
  | E
  | T of Color * left: Node<'K, 'T> * pair: ('K * 'T) * right: Node<'K, 'T>

// keyCompare kv = compare theKey (fst (unbox kv))
let private doTryFind (keyCompare: 'K -> 'K -> int) key node : ('K * 'T) option =
  let rec go node =
    match node with
    | E -> None

    | T (_, a, ((k, _) as kv), b) ->
      let c = keyCompare key k

      if c < 0 then
        // key < k
        go a
      else if c > 0 then
        // k < key
        go b
      else
        // key = k
        Some kv

  go node

let private balanceL body =
  match body with
  | B, T (R, T (R, a, x, b), y, c), z, d -> R, T(B, a, x, b), y, T(B, c, z, d)
  | B, T (R, a, x, T (R, b, y, c)), z, d -> R, T(B, a, x, b), y, T(B, c, z, d)
  | _ -> body

let private balanceR body =
  match body with
  | B, a, x, T (R, T (R, b, y, c), z, d) -> R, T(B, a, x, b), y, T(B, c, z, d)
  | B, a, x, T (R, b, y, T (R, c, z, d)) -> R, T(B, a, x, b), y, T(B, c, z, d)
  | _ -> body

// keyCompare kv = compare (fst (unbox newKv)) (fst (unbox kv))
let private doInsert (keyCompare: 'K -> 'K -> int) (newKv: 'K * 'T) node : Node<'K, 'T> =
  let newKey, _ = newKv

  let rec go node =
    match node with
    | E -> R, E, newKv, E

    | T (color, l, ((k, _) as kv), r) ->
      let c = keyCompare newKey k

      if c < 0 then
        // key < k
        balanceL (color, T(go l), kv, r)
      else if c > 0 then
        // k < key
        balanceR (color, l, kv, T(go r))
      else
        // key = k
        color, l, newKv, r

  let _, y, a, b = go node
  T(B, y, a, b)

let private setBlack node =
  match node with
  | E -> E
  | T (_, l, kv, r) -> T(B, l, kv, r)

let private findMinItem node =
  let rec go node =
    match node with
    | E -> None

    | T (_, E, kv, _) -> Some kv

    | T (_, l, _, _) -> go l

  go node

// keyCompare kv = compare theKey k
// keyCompareTo l r = compare (fst l) (fst r)
let private doRemove (keyCompare: 'K -> 'K -> int) key node : ('K * 'T) option * Node<'K, 'T> =
  let rec go node =
    match node with
    | E -> None, E

    | T (color, l, ((k, _) as kv), r) ->
      let c = keyCompare key k

      if c < 0 then
        // key < k
        let removed, l = go l
        removed, T(balanceL (color, l, kv, r))
      else if c > 0 then
        // k < key
        let removed, r = go r
        removed, T(balanceR (color, l, kv, r))
      else
        // key = k
        let rest =
          match l, r with
          | E, _ -> setBlack r
          | _ ->
            match findMinItem r with
            | None -> setBlack l
            | Some ((rk, _) as rkv) ->
              let _, r = doRemove keyCompare rk r
              T(balanceR (color, l, rkv, r))

        Some kv, rest

  go node

// f: kv -> kv
let private doMap f node =
  let rec go node =
    match node with
    | E -> E

    | T (color, l, kv, r) ->
      let l = go l
      let kv = f kv
      let r = go r
      T(color, l, kv, r)

  go node

// folder: state kv -> state
let private doFold folder state node =
  let rec go state node =
    match node with
    | E -> state

    | T (_, l, kv, r) ->
      let state = go state l
      let state = folder state kv
      go state r

  go state node

// folder: state kv -> kv * state
let private doMapFold folder state node =
  let rec go state node =
    match node with
    | E -> E, state

    | T (color, l, kv, r) ->
      let l, state = go state l
      let kv, state = folder state kv
      let r, state = go state r
      T(color, l, kv, r), state

  go state node

// -----------------------------------------------
// Interface
// -----------------------------------------------

type TreeMap<'K, 'T> = TreeMap of Node<'K, 'T> * ('K -> 'K -> int)

let empty (keyCompare: 'K -> 'K -> int) : TreeMap<'K, 'T> = TreeMap(E, keyCompare)

let isEmpty (map: TreeMap<_, _>) : bool =
  let (TreeMap (node, _)) = map

  match node with
  | E -> true
  | _ -> false

let tryFind (key: 'K) (map: TreeMap<'K, 'T>) : 'T option =
  let (TreeMap (node, keyCompare)) = map

  let kvOpt = doTryFind keyCompare key node

  match kvOpt with
  | Some (_, v) -> Some v
  | None -> None

let containsKey (key: 'K) (map: TreeMap<'K, _>) : bool =
  match tryFind key map with
  | Some _ -> true
  | None -> false

let add (key: 'K) (value: 'T) (map: TreeMap<'K, 'T>) : TreeMap<'K, 'T> =
  let (TreeMap (node, keyCompare)) = map

  let node = doInsert keyCompare (key, value) node

  TreeMap(node, keyCompare)

let remove (key: 'K) (map: TreeMap<'K, 'T>) : 'T option * TreeMap<'K, 'T> =
  let (TreeMap (node, keyCompare)) = map

  let kvOpt, node = doRemove keyCompare key node

  let valueOpt =
    match kvOpt with
    | Some (_, v) -> Some v
    | None -> None

  valueOpt, TreeMap(node, keyCompare)

let map (f: 'K -> 'T -> 'U) (map: TreeMap<'K, 'T>) : TreeMap<'K, 'U> =
  let (TreeMap (node, keyCompare)) = map

  let node = node |> doMap (fun (k, v) -> k, f k v)

  TreeMap(node, keyCompare)

/// Maps both keys and values. Keys must preserve their relative ordering (unchecked).
let stableMap (f: 'K -> 'T -> 'H * 'U) (otherKeyCompare: 'H -> 'H -> int) (map: TreeMap<'K, 'T>) : TreeMap<'H, 'U> =
  let (TreeMap (node, keyCompare)) = map

  let node = node |> doMap (fun (k, v) -> f k v)

  TreeMap(node, otherKeyCompare)

let fold (folder: 'S -> 'K -> 'T -> 'S) (state: 'S) (map: TreeMap<'K, 'T>) : 'S =
  let (TreeMap (node, keyCompare)) = map

  doFold (fun state (k, v) -> folder state k v) state node

let mapFold (folder: 'S -> 'K -> 'T -> 'U * 'S) (state: 'S) (map: TreeMap<'K, 'T>) : TreeMap<'K, 'U> * 'S =
  let (TreeMap (node, keyCompare)) = map

  let node, state =
    doMapFold
      (fun state kv ->
        let k, v = kv
        let v, state = folder state k v
        (k, v), state)
      state
      node

  TreeMap(node, keyCompare), state

let filter (pred: 'K -> 'T -> bool) (map: TreeMap<'K, 'T>) : TreeMap<'K, 'T> =
  let (TreeMap (_, keyCompare)) = map

  map
  |> fold (fun acc k v -> if pred k v then (k, v) :: acc else acc) []
  |> ofList keyCompare

let ofList keyCompare (assoc: ('K * 'T) list) : TreeMap<'K, 'T> =
  let node =
    assoc
    |> List.fold (fun node kv -> doInsert keyCompare kv node) E

  TreeMap(node, keyCompare)

let toList (map: TreeMap<'K, 'T>) : ('K * 'T) list =
  map
  |> fold (fun acc key value -> (key, value) :: acc) []
  |> List.rev

let toKeys (map: TreeMap<'K, 'T>) : 'K list = List.map fst (toList map)
