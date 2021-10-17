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
  | T of Color * left: Node<'K, 'T> * key: 'K * value: 'T * right: Node<'K, 'T>

module private TreeNode =
  let private balanceL body =
    match body with
    | B, T (R, T (R, a, xk, xv, b), yk, yv, c), zk, zv, d -> R, T(B, a, xk, xv, b), yk, yv, T(B, c, zk, zv, d)
    | B, T (R, a, xk, xv, T (R, b, yk, yv, c)), zk, zv, d -> R, T(B, a, xk, xv, b), yk, yv, T(B, c, zk, zv, d)
    | _ -> body

  let private balanceR body =
    match body with
    | B, a, xk, xv, T (R, T (R, b, yk, yv, c), zk, zv, d) -> R, T(B, a, xk, xv, b), yk, yv, T(B, c, zk, zv, d)
    | B, a, xk, xv, T (R, b, yk, yv, T (R, c, zk, zv, d)) -> R, T(B, a, xk, xv, b), yk, yv, T(B, c, zk, zv, d)
    | _ -> body

  let findFromNode (keyCompare: 'K -> 'K -> int) key node : 'T option =
    let rec go node =
      match node with
      | E -> None

      | T (_, a, k, v, b) ->
        let c = keyCompare key k

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

  let insertNode (keyCompare: 'K -> 'K -> int) (newKey: 'K) (newValue: 'T) node : Node<'K, 'T> =
    let rec go node : Color * Node<'K, 'T> * 'K * 'T * Node<'K, 'T> =
      match node with
      | E -> R, E, newKey, newValue, E

      | T (color, l, k, v, r) ->
        let c = keyCompare newKey k

        if c < 0 then
          // key < k
          balanceL (color, T(go l), k, v, r)
        else if c > 0 then
          // k < key
          balanceR (color, l, k, v, T(go r))
        else
          // key = k
          color, l, newKey, newValue, r

    let _, yk, yv, a, b = go node
    T(B, yk, yv, a, b)

  let private setBlack node =
    match node with
    | E -> E
    | T (_, l, k, v, r) -> T(B, l, k, v, r)

  let private findMinItem node =
    let rec go node =
      match node with
      | E -> None

      | T (_, E, k, v, _) -> Some(k, v)

      | T (_, l, _, _, _) -> go l

    go node

  let removeNode (keyCompare: 'K -> 'K -> int) key node : 'T option * Node<'K, 'T> =
    let rec go node =
      match node with
      | E -> None, E

      | T (color, l, k, v, r) ->
        let c = keyCompare key k

        if c < 0 then
          // key < k
          let removed, l = go l
          removed, T(balanceL (color, l, k, v, r))
        else if c > 0 then
          // k < key
          let removed, r = go r
          removed, T(balanceR (color, l, k, v, r))
        else
          // key = k
          let rest =
            match l, r with
            | E, _ -> setBlack r
            | _ ->
              match findMinItem r with
              | None -> setBlack l
              | Some (rk, rv) ->
                let _, r = removeNode keyCompare rk r
                T(balanceR (color, l, rk, rv, r))

          Some v, rest

    go node

  let mapNode (f: 'K -> 'T -> 'U) (node: Node<'K, 'T>) : Node<'K, 'U> =
    let rec go node =
      match node with
      | E -> E

      | T (color, l, k, v, r) ->
        let l = go l
        let v = f k v
        let r = go r
        T(color, l, k, v, r)

    go node

  let foldNode (folder: 'S -> 'K -> 'T -> 'S) (state: 'S) (node: Node<'K, 'T>) : 'S =
    let rec go state node =
      match node with
      | E -> state

      | T (_, l, k, v, r) ->
        let state = go state l
        let state = folder state k v
        go state r

    go state node

  let mapFoldNode (folder: 'S -> 'K -> 'T -> 'U * 'S) (state: 'S) (node: Node<'K, 'T>) : Node<'K, 'U> * 'S =
    let rec go state node =
      match node with
      | E -> E, state

      | T (color, l, k, v, r) ->
        let l, state = go state l
        let v, state = folder state k v
        let r, state = go state r
        T(color, l, k, v, r), state

    go state node

// -----------------------------------------------
// Interface
// -----------------------------------------------

type TreeMap<'K, 'T> = TreeMap of Node<'K, 'T> * ('K -> 'K -> int)

module TMap =
  let empty (keyCompare: 'K -> 'K -> int) : TreeMap<'K, 'T> = TreeMap(E, keyCompare)

  let isEmpty (map: TreeMap<_, _>) : bool =
    let (TreeMap (node, _)) = map

    match node with
    | E -> true
    | _ -> false

  let tryFind (key: 'K) (map: TreeMap<'K, 'T>) : 'T option =
    let (TreeMap (node, keyCompare)) = map
    TreeNode.findFromNode keyCompare key node

  let containsKey (key: 'K) (map: TreeMap<'K, _>) : bool =
    let (TreeMap (node, keyCompare)) = map

    match TreeNode.findFromNode keyCompare key node with
    | Some _ -> true
    | None -> false

  let add (key: 'K) (value: 'T) (map: TreeMap<'K, 'T>) : TreeMap<'K, 'T> =
    let (TreeMap (node, keyCompare)) = map

    let node =
      TreeNode.insertNode keyCompare key value node

    TreeMap(node, keyCompare)

  let remove (key: 'K) (map: TreeMap<'K, 'T>) : 'T option * TreeMap<'K, 'T> =
    let (TreeMap (node, keyCompare)) = map
    let valueOpt, node = TreeNode.removeNode keyCompare key node
    valueOpt, TreeMap(node, keyCompare)

  let map (f: 'K -> 'T -> 'U) (map: TreeMap<'K, 'T>) : TreeMap<'K, 'U> =
    let (TreeMap (node, keyCompare)) = map
    let node = node |> TreeNode.mapNode f
    TreeMap(node, keyCompare)

  let fold (folder: 'S -> 'K -> 'T -> 'S) (state: 'S) (map: TreeMap<'K, 'T>) : 'S =
    let (TreeMap (node, keyCompare)) = map
    TreeNode.foldNode folder state node

  let mapFold (folder: 'S -> 'K -> 'T -> 'U * 'S) (state: 'S) (map: TreeMap<'K, 'T>) : TreeMap<'K, 'U> * 'S =
    let (TreeMap (node, keyCompare)) = map
    let node, state = TreeNode.mapFoldNode folder state node
    TreeMap(node, keyCompare), state

  let filter (pred: 'K -> 'T -> bool) (map: TreeMap<'K, 'T>) : TreeMap<'K, 'T> =
    let (TreeMap (node, keyCompare)) = map

    let node =
      node
      |> TreeNode.foldNode
           (fun node k v ->
             if pred k v then
               TreeNode.insertNode keyCompare k v node
             else
               node)
           E

    TreeMap(node, keyCompare)

  let ofList keyCompare (assoc: ('K * 'T) list) : TreeMap<'K, 'T> =
    let node =
      assoc
      |> List.fold (fun node (k, v) -> TreeNode.insertNode keyCompare k v node) E

    TreeMap(node, keyCompare)

  let toList (map: TreeMap<'K, 'T>) : ('K * 'T) list =
    map
    |> fold (fun acc key value -> (key, value) :: acc) []
    |> List.rev

  let toKeys (map: TreeMap<'K, 'T>) : 'K list = map |> toList |> List.map fst
