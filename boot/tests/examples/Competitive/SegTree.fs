/// Immutable segment tree based on AVL tree
///
/// Replacement of ResizeArray.
module rec Competitive.SegTree

open Competitive.Helpers

// -----------------------------------------------
// Intervals
// -----------------------------------------------

type Interval = int * int

let intervalIsDisjoint (first: Interval) (second: Interval) =
  let xl, xr = first
  let yl, yr = second
  xr <= yl || yr <= xl

let intervalCovers (first: Interval) (second: Interval) =
  let xl, xr = first
  let yl, yr = second
  xl <= yl && yr <= xr

// -----------------------------------------------
// Traits
// -----------------------------------------------

type SegItemTypeTag =
  | SegItemTypeTag

let segItemTypeToAppend (append, _, _, (_: SegItemTypeTag)) = append

let segItemTypeToEmptyNode (_, emptyNode, _, (_: SegItemTypeTag)) = emptyNode

let segItemTypeToNoChildren (_, _, noChildren, (_: SegItemTypeTag)): obj = noChildren

let segItemTypeToEmptyItem itemTy =
  itemTy |> segItemTypeToEmptyNode |> segNodeToItem

let segItemTypeNew emptyItem append =
  let emptyNode = segNodeNewEmpty emptyItem

  // Type unification.
  assert ([append emptyItem emptyItem; emptyItem] |> listIsEmpty |> not)

  let itemTy = append, emptyNode, box (emptyNode, emptyNode), SegItemTypeTag
  assert ([itemTy |> segItemTypeToAppend; append] |> listIsEmpty |> not)

  itemTy

// -----------------------------------------------
// Nodes
// -----------------------------------------------

type SegNodeTag =
  | SegNodeTag

let segNodeNewEmpty emptyItem =
  emptyItem, 0, (-1), unitObj, SegNodeTag

let segNodeNewLeaf itemTy item =
  let noChildren = itemTy |> segItemTypeToNoChildren
  item, 1, 0, noChildren, SegNodeTag

let segNodeNew itemTy left right =
  let doNew () =
    let leftItem, leftLen, leftHeight, _, (_: SegNodeTag) = left
    let rightItem, rightLen, rightHeight, _, (_: SegNodeTag) = right
    assert (leftLen >= 1 && rightLen >= 1)

    let item = (itemTy |> segItemTypeToAppend) leftItem rightItem
    let len = leftLen + rightLen
    let height = 1 + intMax leftHeight rightHeight
    item, len, height, box (left, right), SegNodeTag

  match left |> segNodeToLength, right |> segNodeToLength with
  | 0, 0 ->
    itemTy |> segItemTypeToEmptyNode

  | 0, _ ->
    right

  | _, 0 ->
    left

  // | 1, 1 ->
  //   doNew ()

  // | 1, _ ->
  //   let item, _, _, _, (_: SegNodeTag) = left
  //   right |> segNodeInsert itemTy 0 item

  // | _, 1 ->
  //   let item, _, _, _, (_: SegNodeTag) = right
  //   left |> segNodeInsert itemTy (len - 1) item

  | _ ->
    doNew ()

let segNodeToItem node =
  let item, _, _, _, (_: SegNodeTag) = node
  item

let segNodeToLength node =
  let _, len, _, _, (_: SegNodeTag) = node
  len

let segNodeToHeight node =
  let _, _, height, _, (_: SegNodeTag) = node
  height

let segNodeToChildren node =
  let _, (len: int), (_: int), (children: obj), (_: SegNodeTag) = node
  assert (len >= 2)

  let left, right = unbox children

  // HACK: Unify the item type of children.
  assert ([node; left; right] |> listIsEmpty |> not)

  left, right

let segNodeIsEmpty node =
  segNodeToLength node = 0

let segNodeWithLeft itemTy newLeft node =
  assert (segNodeToLength node >= 1)
  let _, right = node |> segNodeToChildren
  segNodeNew itemTy newLeft right

let segNodeWithRight itemTy newRight node =
  assert (segNodeToLength node >= 1)
  let left, _ = node |> segNodeToChildren
  segNodeNew itemTy left newRight

let segNodeMakeBalanced itemTy node =
  // from:
  //       T
  //      / \
  //     L   R
  //        / \
  //       X   Y
  // to:
  //        [R]
  //        / \
  //      [T]  Y
  //      / \
  //     L   X
  let rotateLeft node =
    if (node |> segNodeToLength) < 2 then
      node
    else

    let _, right = node |> segNodeToChildren
    if (right |> segNodeToLength) < 2 then
      node
    else

    let x, _ = right |> segNodeToChildren
    let u = node |> segNodeWithRight itemTy x
    let t = right |> segNodeWithLeft itemTy u
    t

  // from:
  //         T
  //        / \
  //       L   R
  //      / \
  //     X   Y
  // to:
  //      [L]
  //      / \
  //     X  [T]
  //        / \
  //       Y   R
  let rotateRight node =
    if (node |> segNodeToLength) < 2 then
      node
    else

    let left, _ = node |> segNodeToChildren
    if (left |> segNodeToLength) < 2 then
      node
    else

    let _, y = left |> segNodeToChildren
    let u = node |> segNodeWithLeft itemTy y
    let t = left |> segNodeWithRight itemTy u
    t

  let doubleLeft node =
    if (node |> segNodeToLength) < 2 then
      node
    else

    let _, right = node |> segNodeToChildren
    node |> segNodeWithRight itemTy (right |> rotateRight) |> rotateLeft

  let doubleRight node =
    if (node |> segNodeToLength) < 2 then
      node
    else

    let left, _ = node |> segNodeToChildren
    node |> segNodeWithLeft itemTy (left |> rotateLeft) |> rotateRight

  let toBalance node =
    if (node |> segNodeToLength) < 2 then
      0
    else
      let left, right = node |> segNodeToChildren
      segNodeToHeight right - segNodeToHeight left

  let selfBalance = node |> toBalance
  if (-1) <= selfBalance && selfBalance <= 1 then
    node
  else

  if (node |> segNodeToLength) < 2 then
    node
  else

  let left, right = node |> segNodeToChildren
  if selfBalance >= 2 then
    if (right |> toBalance) < 0 then
      node |> doubleLeft
    else
      node |> rotateLeft
  else
    if (left |> toBalance) > 0 then
      node |> doubleRight
    else
      node |> rotateRight

// -----------------------------------------------
// Trees
// -----------------------------------------------

type SegTreeTag =
  | SegTreeTag

let segTreeNew itemTy =
  let emptyNode = itemTy |> segItemTypeToEmptyNode
  itemTy, emptyNode, SegTreeTag

let segTreeToRoot self =
  let _, node, (_: SegTreeTag) = self
  node

let segTreeToLength self =
  self |> segTreeToRoot |> segNodeToLength

let segTreeToHeight self =
  self |> segTreeToRoot |> segNodeToHeight

let segTreeIsEmpty self =
  self |> segTreeToRoot |> segNodeIsEmpty

/// Gets an item at the index.
/// Error if out of range.
let segTreeGet index self =
  let rec go index node =
    let item, len, _, _, (_: SegNodeTag) = node
    if index < 0 || index >= len then
      printfn "ERROR: segNodeGet out of range (index = %d, len = %d)" index len
      exit 1

    assert (len <> 0)
    if len = 1 then
      item
    else

    let left, right = node |> segNodeToChildren
    let leftLen = segNodeToLength left
    if index < leftLen then
      go index left
    else
      go (index - leftLen) right

  self |> segTreeToRoot |> go index

/// Gets the sum of items at the index.
/// The end index is exclusive.
let segTreeSum (ql: int) (qr: int) self =
  let itemTy, root, (_: SegTreeTag) = self

  let rec go (e: Interval) (q: Interval) node =
    if intervalIsDisjoint q e then
      itemTy |> segItemTypeToEmptyItem
    else if intervalCovers q e then
      node |> segNodeToItem
    else
      assert (node |> segNodeIsEmpty |> not)
      let leftNode, rightNode = node |> segNodeToChildren

      let el, er = e
      let m = el + (leftNode |> segNodeToLength)

      let vl = leftNode |> go (el, m) q
      let vr = rightNode |> go (m, er) q
      (itemTy |> segItemTypeToAppend) vl vr

  let len = root |> segNodeToLength
  let q = ql, qr

  if intervalIsDisjoint q (0, len) then
    itemTy |> segItemTypeToEmptyItem
  else

  let e = 0, len
  root |> go e q

/// Replaces an item at the index.
/// Error if out of range.
let segTreeSet index newItem self =
  let itemTy, root, (_: SegTreeTag) = self

  let rec go index node =
    let _, len, height, children, (_: SegNodeTag) = node
    if index < 0 || index >= len then
      printfn "ERROR: segNodeSet out of range (index = %d, len = %d)" index len
      exit 1

    assert (len <> 0)
    if len = 1 then
      newItem, len, height, children, SegNodeTag
    else

    let left, right = node |> segNodeToChildren
    let leftLen = segNodeToLength left
    if index < leftLen then
      node |> segNodeWithLeft itemTy (left |> go index)
    else
      node |> segNodeWithRight itemTy (right |> go (index - leftLen))

  let root = root |> go index
  itemTy, root, SegTreeTag

/// Inserts an item at the index.
let segTreeInsert index newItem self =
  let itemTy, root, (_: SegTreeTag) = self

  let rec go index node =
    let oldItem, len, _, _, (_: SegNodeTag) = node
    assert (index <= len)

    if len = 0 then
      segNodeNewLeaf itemTy newItem
    else if len = 1 then
      let oldLeaf = segNodeNewLeaf itemTy oldItem
      let newLeaf = segNodeNewLeaf itemTy newItem
      let left, right =
        if index = 0 then
          newLeaf, oldLeaf
        else
          assert (index = 1)
          oldLeaf, newLeaf
      segNodeNew itemTy left right
    else
      let left, right = node |> segNodeToChildren

      let leftLen = segNodeToLength left
      let rightLen = segNodeToLength right
      assert (leftLen + rightLen = len)

      let left, right =
        if index < leftLen then
          let left = left |> go index
          assert (segNodeToLength left = leftLen + 1)
          left, right
        else
          let right = right |> go (index - leftLen)
          assert (segNodeToLength right = rightLen + 1)
          left, right

      segNodeNew itemTy left right |> segNodeMakeBalanced itemTy

  let root = root |> go index
  itemTy, root, SegTreeTag

/// Removes an item at the index.
let segTreeRemove index self =
  let itemTy, root, (_: SegTreeTag) = self

  let rec go index node =
    let _, len, _, _, (_: SegNodeTag) = node
    assert (index < len)

    assert (len <> 0)
    if len = 1 then
      itemTy |> segItemTypeToEmptyNode
    else
      let left, right = node |> segNodeToChildren

      let leftLen = segNodeToLength left
      let rightLen = segNodeToLength right
      assert (leftLen + rightLen = len)

      let node =
        if index < leftLen then
          if leftLen < 2 then
            right
          else
            node |> segNodeWithLeft itemTy (left |> go index)
        else
          if rightLen < 2 then
            left
          else
            node |> segNodeWithRight itemTy (right |> go (index - leftLen))

      node |> segNodeMakeBalanced itemTy

  let root = root |> go index
  itemTy, root, SegTreeTag

/// Inserts an item to the bottom.
let segTreePush value self =
  let index = self |> segTreeToLength
  self |> segTreeInsert index value

/// Removes the last item.
let segTreePop self =
  let index = (self |> segTreeToLength) - 1
  self |> segTreeRemove index

/// Creates a segment tree from the list.
let segTreeOfList itemTy xs =
  let rec go t xs =
    match xs with
    | [] ->
      t

    | x :: xs ->
      go (t |> segTreePush x) xs

  go (segTreeNew itemTy) xs

/// Creates a list from the segment tree.
let segTreeToList v =
  let len = v |> segTreeToLength

  let rec go acc i =
    if i = len then
      listRev acc
    else
      let x = v |> segTreeGet i
      go (x :: acc) (i + 1)

  go [] 0

// -----------------------------------------------
// Testing
// -----------------------------------------------

let segTreeTest unit =
  let intAdd (x: int) (y: int) = x + y
  let segItemTypeInt = segItemTypeNew 0 intAdd

  let strAdd (x: string) (y: string) = x + y
  let segItemTypeStr = segItemTypeNew "" strAdd

  let testPushPop () =
    let v = segTreeNew segItemTypeInt |> segTreePush 1 |> segTreePush 2
    assert (v |> segTreeToList |> listEq intEq [1; 2])

    let v = v |> segTreePush 3
    assert (v |> segTreeToList |> listEq intEq [1; 2; 3])

    let v = v |> segTreePop
    assert (v |> segTreeToList |> listEq intEq [1; 2])

    let v = v |> segTreePop
    assert (v |> segTreeToList |> listEq intEq [1])

    let v = v |> segTreePop
    assert (v |> segTreeToList |> listEq intEq [])

  testPushPop ()

  let testSet () =
    let v = segTreeOfList segItemTypeInt [1; 2; 3] |> segTreeSet 1 22
    assert (v |> segTreeToList |> listEq intEq [1; 22; 3])

    let v = v |> segTreeSet 0 11 |> segTreeSet 2 33
    assert (v |> segTreeToList |> listEq intEq [11; 22; 33])

  testSet ()

  let testSum () =
    let v = segTreeOfList segItemTypeInt [3; 1; 4; 1; 5; 9]
    assert (v |> segTreeSum 0 6 = 3 + 1 + 4 + 1 + 5 + 9)
    assert (v |> segTreeSum 2 4 = 4 + 1)

  testSum ()

  let testSumMore () =
    let xs = [3; 1; 4; 1; 5; 9]
    let v = segTreeOfList segItemTypeInt xs
    let n = xs |> listLength
    let rec go l r =
      if r = n then
        if l < n then
          go (l + 1) (l + 1)
      else
        let expected =
          let rec sum (acc: int) i xs =
            if i = r then
              acc
            else
              match xs with
              | x :: xs ->
                let acc = if i < l then acc else acc + x
                sum acc (i + 1) xs
              | _ ->
                failwith "NEVER"
          sum 0 0 xs
        let actual = v |> segTreeSum l r
        assert (actual = expected)
        go l (r + 1)
    go 0 0

  testSumMore ()

  let testBalance () =
    let v = segTreeOfList segItemTypeInt (listReplicate 1 1000)
    assert (segTreeToHeight v < 100)

  testBalance ()

  let testPolymorphic () =
    let v = segTreeNew segItemTypeStr |> segTreePush "a" |> segTreePush "b"
    assert (v |> segTreeToList |> listEq strEq ["a"; "b"])

  testPolymorphic ()

  unit
