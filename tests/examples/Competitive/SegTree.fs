// Provides owned segment tree.
module rec Competitive.SegTree

open Std.Vector

// Implementation is a port of:
//    https://github.com/vain0x/procon/blob/cf0e49e5/rust/src/procon/seg_tree.rs (2018-09-30)

// -----------------------------------------------
// Interval
// -----------------------------------------------

/// Range of indexes. (End is exclusive.)
type private Interval = int * int

module private Interval =
  let disjoint (l: Interval) (r: Interval) =
    let ll, lr = l
    let rl, rr = r
    lr <= rl || rr <= ll

  let covers (l: Interval) (r: Interval) =
    let ll, lr = l
    let rl, rr = r
    ll <= rl && rr <= lr

// -----------------------------------------------
// SegTree
// -----------------------------------------------

/// Owned segment tree.
type SegTree<'T> =
  private | SegTree of
    // Count of items.
    len: int *
    // Number of leaf nodes.
    width: int *
    // List of nodes.
    //
    // First (width-1) nodes are inner nodes.
    // Rest width nodes are leaf node.
    //
    // Every inner node (at ni) has exactly two children:
    //    left: nodes.[2 * ni + 1]
    //    right: nodes.[2 * ni + 2]
    // and its value is append of children.
    nodes: Vector<'T> *
    // Identity value of the append operation.
    empty: 'T *
    // Combine two value. This must be associative.
    append: ('T -> 'T -> 'T)

module SegTree =
  /// Creates a segment tree that is filled with the specified value.
  let replicate (len: int) (item: 'T) (empty: 'T) (append: 'T -> 'T -> 'T) : SegTree<'T> =
    // Compute width. (Next power of two.)
    let w =
      let rec go w = if w < len then go (w * 2) else w
      go 1

    assert (w >= len)

    let nodes = Vector.replicate (2 * w - 1) empty

    // Set leaves.
    let nodes =
      let rec go nodes ei =
        if ei < len then
          let nodes = Vector.forceSet (w - 1 + ei) item nodes
          go nodes (ei + 1)
        else
          nodes

      go nodes 0

    // Compute inner nodes.
    let nodes =
      let rec go nodes ni =
        if ni >= 1 then
          let ni = ni - 1
          let l, nodes = Vector.forceGet (2 * ni + 1) nodes
          let r, nodes = Vector.forceGet (2 * ni + 2) nodes
          go (Vector.forceSet ni (append l r) nodes) ni
        else
          nodes

      go nodes (w - 1)

    SegTree(len, w, nodes, empty, append)

  let dispose (tree: SegTree<'T>) : unit =
    let (SegTree (_, _, nodes, _, _)) = tree
    Vector.dispose nodes

  let length (tree: SegTree<'T>) =
    let (SegTree (len, width, nodes, empty, append)) = tree
    len, SegTree(len, width, nodes, empty, append)

  let set (ei: int) (item: 'T) (tree: SegTree<'T>) =
    let (SegTree (len, width, nodes, empty, append)) = tree

    assert (uint ei < uint len)
    let ni = width - 1 + ei
    let nodes = Vector.forceSet ni item nodes

    // Re-compute ancestors.
    let nodes =
      let rec go nodes ni =
        if ni >= 1 then
          let ni = (ni - 1) / 2
          let l, nodes = Vector.forceGet (2 * ni + 1) nodes
          let r, nodes = Vector.forceGet (2 * ni + 2) nodes
          go (Vector.forceSet ni (append l r) nodes) ni
        else
          nodes

      go nodes ni

    SegTree(len, width, nodes, empty, append)

  // Computes the sum of the append operation
  // from all items in the range (ql-qr, exclusive).
  let sum (ql: int) (qr: int) (tree: SegTree<'T>) : 'T * SegTree<'T> =
    let (SegTree (len, width, nodes, empty, append)) = tree

    // Range of query.
    let q: Interval = ql, qr
    // Range of element indexes.
    let e: Interval = 0, len

    if Interval.disjoint q e then
      empty, SegTree(len, width, nodes, empty, append)
    else
      let rec go nodes ni q e =
        if Interval.disjoint q e then
          empty, nodes
        else if Interval.covers q e then
          Vector.forceGet ni nodes
        else
          let el, er = e
          let m = (el + er) / 2

          // Recursively resolve the query for children.
          let l, nodes = go nodes (2 * ni + 1) q (el, m)
          let r, nodes = go nodes (2 * ni + 2) q (m, er)
          append l r, nodes

      let sum, nodes =
        // Range of leaf node indexes.
        let leaves: Interval = 0, width

        go nodes 0 q leaves

      sum, SegTree(len, width, nodes, empty, append)

// -----------------------------------------------
// Testing
// -----------------------------------------------

let segTreeTest () =
  let inf = 1000000
  let intMin (l: int) r = if r < l then r else l

  let tree = SegTree.replicate 10 10 inf intMin

  let sum, tree = SegTree.sum 0 10 tree
  assert (sum = 10)
  let sum, tree = SegTree.sum 10 10 tree
  assert (sum = inf)

  let tree = SegTree.set 5 5 tree
  let sum, tree = SegTree.sum 0 5 tree
  assert (sum = 10)
  let sum, tree = SegTree.sum 5 6 tree
  assert (sum = 5)
  let sum, tree = SegTree.sum 6 10 tree
  assert (sum = 10)
  let sum, tree = SegTree.sum 4 8 tree
  assert (sum = 5)
  let sum, tree = SegTree.sum 0 10 tree
  assert (sum = 5)

  let tree = SegTree.set 3 3 tree
  let sum, tree = SegTree.sum 0 3 tree
  assert (sum = 10)
  let sum, tree = SegTree.sum 3 5 tree
  assert (sum = 3)
  let sum, tree = SegTree.sum 5 10 tree
  assert (sum = 5)
  let sum, tree = SegTree.sum 0 10 tree
  assert (sum = 3)

  SegTree.dispose tree
