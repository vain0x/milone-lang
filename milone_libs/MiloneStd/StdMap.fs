/// Provides immutable map (associative array) data structure
/// based on red-black tree.
///
/// Requires comparison of keys.
module rec MiloneStd.StdMap

// -----------------------------------------------
// Nodes
// -----------------------------------------------

[<NoEquality; NoComparison>]
type TreeMapColor =
  | R
  | B

[<NoEquality; NoComparison>]
type TreeMapRawNode =
  | E
  | T of TreeMapColor * left: TreeMapRawNode * keyValuePair: obj * right: TreeMapRawNode

// keyCompare kv = compare theKey (fst (unbox kv))
let private doTryFind (keyCompare: obj -> int) node: obj option =
  let rec go node =
    match node with
    | E -> None

    | T (_, a, kv, b) ->
        let c = keyCompare kv

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

let private balance body =
  match body with
  | B, T (R, T (R, a, x, b), y, c), z, d -> R, T(B, a, x, b), y, T(B, c, z, d)
  | B, T (R, a, x, T (R, b, y, c)), z, d -> R, T(B, a, x, b), y, T(B, c, z, d)
  | B, a, x, T (R, T (R, b, y, c), z, d) -> R, T(B, a, x, b), y, T(B, c, z, d)
  | B, a, x, T (R, b, y, T (R, c, z, d)) -> R, T(B, a, x, b), y, T(B, c, z, d)
  | _ -> body

// keyCompare kv = compare (fst (unbox newKv)) (fst (unbox kv))
let private doInsert (keyCompare: obj -> int) (newKv: obj) node =
  let rec go node =
    match node with
    | E -> R, E, newKv, E

    | T (color, l, kv, r) ->
        let c = keyCompare kv

        if c < 0 then
          // key < k
          balance (color, T(go l), kv, r)
        else if c > 0 then
          // k < key
          balance (color, l, kv, T(go r))
        else
          // key = k
          balance (color, l, newKv, r)

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
let private doRemove (keyCompare: obj -> int) (keyCompareTo: obj -> obj -> int) node: obj option * _ =
  let rec go keyCompare node =
    match node with
    | E -> None, E

    | T (color, l, kv, r) ->
        let c = keyCompare kv

        if c < 0 then
          // key < k
          let removed, l = go keyCompare l
          removed, T(balance (color, l, kv, r))
        else if c > 0 then
          // k < key
          let removed, r = go keyCompare r
          removed, T(balance (color, l, kv, r))
        else
          // key = k
          let rest =
            match l, r with
            | E, _ -> setBlack r
            | _, E -> setBlack l
            | _ ->
                match findMinItem r with
                | None -> failwith ""
                | Some rkv ->
                    let _, r = go (keyCompareTo rkv) r
                    T(balance (color, l, rkv, r))

          Some kv, rest

  go keyCompare node

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

// -----------------------------------------------
// Interface
// -----------------------------------------------

// Third item is always None. This is just for "phantom" type parameter 'T.
type TreeMap<'K, 'T> = TreeMapRawNode * ('K -> 'K -> int) * ('T option)

let empty (keyCompare: 'K -> 'K -> int): TreeMap<'K, 'T> = E, keyCompare, None

let isEmpty (map: TreeMap<_, _>): bool =
  let node, _, _ = map

  match node with
  | E -> true
  | _ -> false

let tryFind (key: 'K) (map: TreeMap<'K, 'T>): 'T option =
  let node, keyCompare, _ = map

  let kvOpt =
    node
    |> doTryFind (fun kv -> keyCompare key (fst (unbox kv: 'K * 'T)))

  match kvOpt with
  | Some kv -> Some(snd (unbox kv: 'K * 'T))
  | None -> None

let add (key: 'K) (value: 'T) (map: TreeMap<'K, 'T>): TreeMap<'K, 'T> =
  let node, keyCompare, none = map

  let node =
    doInsert (fun kv -> keyCompare key (fst (unbox kv: 'K * 'T))) (box (key, value)) node

  node, keyCompare, none

let remove (key: 'K) (map: TreeMap<'K, 'T>): 'T option * TreeMap<'K, 'T> =
  let node, keyCompare, none = map

  let kvOpt, node =
    doRemove
      (fun kv -> keyCompare key (fst (unbox kv: 'K * 'T)))
      (fun l r -> keyCompare (fst (unbox l: 'K * 'T)) (fst (unbox r: 'K * 'T)))
      node

  let valueOpt =
    match kvOpt with
    | Some kv -> Some(snd (unbox kv: 'K * 'T))
    | None -> None

  valueOpt, (node, keyCompare, none)

let map (f: 'K -> 'T -> 'U) (map: TreeMap<'K, 'T>): TreeMap<'K, 'U> =
  let node, keyCompare, _ = map

  let node =
    node
    |> doMap
         (fun kv ->
           let k, v = unbox kv
           let v = f k v
           box (k, v))

  node, keyCompare, None

let fold (folder: 'S -> 'K -> 'T -> 'S) (state: 'S) (map: TreeMap<'K, 'T>): 'S =
  let node, keyCompare, _ = map

  doFold
    (fun state kv ->
      let k, v = unbox kv
      folder state k v)
    state
    node

let filter (pred: 'K -> 'T -> bool) (map: TreeMap<'K, 'T>): TreeMap<'K, 'T> =
  let _, keyCompare, _ = map

  map
  |> fold (fun acc k v -> if pred k v then (k, v) :: acc else acc) []
  |> ofList keyCompare

let ofList keyCompare (assoc: ('K * 'T) list): TreeMap<'K, 'T> =
  let node =
    assoc
    |> List.fold (fun node kv -> doInsert (fun r -> keyCompare (fst kv) (fst (unbox r: 'K * 'T))) (box kv) node) E

  node, keyCompare, None

let toList (map: TreeMap<'K, 'T>): ('K * 'T) list =
  map
  |> fold (fun acc key value -> (key, value) :: acc) []
  |> List.rev
