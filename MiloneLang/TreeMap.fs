/// Provides immutable map (associative array) data structure
/// based on red-black tree.
///
/// Requires comparison of keys.
module rec MiloneLang.TreeMap

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

let private doTryFind (keyCmp: 'K -> 'K -> int) (key: 'K) node: 'T option =
  let rec go node =
    match node with
    | E -> None

    | T (_, a, kv, b) ->
        let k, v = unbox kv: 'K * 'T
        let c = keyCmp key k

        if c < 0 then
          // key < k
          go a
        else if c > 0 then
          // k < key
          go b
        else
          // key = k
          Some v

  go node

let private balance body =
  match body with
  | B, T (R, T (R, a, x, b), y, c), z, d -> R, T(B, a, x, b), y, T(B, c, z, d)
  | B, T (R, a, x, T (R, b, y, c)), z, d -> R, T(B, a, x, b), y, T(B, c, z, d)
  | B, a, x, T (R, T (R, b, y, c), z, d) -> R, T(B, a, x, b), y, T(B, c, z, d)
  | B, a, x, T (R, b, y, T (R, c, z, d)) -> R, T(B, a, x, b), y, T(B, c, z, d)
  | _ -> body

let private doInsert (keyCmp: 'K -> 'K -> int) (key: 'K) (value: 'T) node =
  let newKv = box (key, value)

  let rec go node =
    match node with
    | E -> R, E, newKv, E

    | T (color, l, kv, r) ->
        let k, _ = unbox kv: 'K * 'T
        let c = keyCmp key k

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

let private doRemove (keyCmp: 'K -> 'K -> int) (key: 'K) node: 'T option * _ =
  let rec go key node =
    match node with
    | E -> None, E

    | T (color, l, kv, r) ->
        let k, v = unbox kv: 'K * 'T
        let c = keyCmp key k

        if c < 0 then
          // key < k
          let removed, l = go key l
          removed, T(balance (color, l, kv, r))
        else if c > 0 then
          // k < key
          let removed, r = go key r
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
                    let rk, rv = unbox rkv: 'K * 'T
                    let _, r = go rk r
                    T(balance (color, l, rkv, r))

          Some v, rest

  go key node

let private doMap f node =
  let rec go node =
    match node with
    | E -> E

    | T (color, l, kv, r) ->
        let l = go l

        let k, v = unbox kv

        let v = f k v

        let r = go r

        T(color, l, box (k, v), r)

  go node

let private doFold folder state node =
  let rec go state node =
    match node with
    | E -> state

    | T (_, l, kv, r) ->
        let state = go state l

        let state =
          let k, v = unbox kv
          folder state k v

        go state r

  go state node

// -----------------------------------------------
// Interface
// -----------------------------------------------

// Third item is always None. This is just for "phantom" type parameter 'T.
type TreeMap<'K, 'T> = TreeMapRawNode * ('K -> 'K -> int) * ('T option)

let empty (keyCmp: 'K -> 'K -> int): TreeMap<'K, 'T> = E, keyCmp, None

let isEmpty (map: TreeMap<_, _>): bool =
  let node, _, _ = map

  match node with
  | E -> true
  | _ -> false

let tryFind key (map: TreeMap<'K, 'T>): 'T option =
  let node, keyCmp, _ = map
  node |> doTryFind keyCmp key

let add (key: 'K) (value: 'T) (map: TreeMap<'K, 'T>): TreeMap<'K, 'T> =
  let node, keyCmp, none = map

  let node = doInsert keyCmp key value node

  node, keyCmp, none

let remove (key: 'K) (map: TreeMap<'K, 'T>): 'T option * TreeMap<'K, 'T> =
  let node, keyCmp, none = map

  let valueOpt, node = doRemove keyCmp key node

  valueOpt, (node, keyCmp, none)

let map (f: 'K -> 'T -> 'U) (map: TreeMap<'K, 'T>): TreeMap<'K, 'U> =
  let node, keyCmp, _ = map
  let node = doMap f node
  node, keyCmp, None

let fold (folder: 'S -> 'K -> 'T -> 'S) (state: 'S) (map: TreeMap<'K, 'T>): 'S =
  let node, keyCmp, _ = map

  doFold folder state node

let filter (pred: 'K -> 'T -> bool) (map: TreeMap<'K, 'T>): TreeMap<'K, 'T> =
  let _, keyCmp, _ = map

  map
  |> fold (fun acc k v -> if pred k v then (k, v) :: acc else acc) []
  |> ofList keyCmp

let ofList (keyCmp: 'K -> 'K -> int) (assoc: ('K * 'T) list): TreeMap<'K, 'T> =
  let node =
    assoc
    |> List.fold (fun node (key, value) -> doInsert keyCmp key value node) E

  node, keyCmp, None

let toList (map: TreeMap<'K, 'T>): ('K * 'T) list =
  map
  |> fold (fun acc key value -> (key, value) :: acc) []
  |> List.rev
