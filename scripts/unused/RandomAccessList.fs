/// # RandomAccessList
///
/// Provides a data structure "skew binary random access list",
/// as replacement of ResizeArray.
///
/// ## See also
///
/// - ["Purely Functional Data Structures" by Chris Okasaki](https://www.cambridge.org/jp/academic/subjects/computer-science/programming-languages-and-applied-logic/purely-functional-data-structures?format=PB)
///     - or [its Japanese translation](https://asciidwango.jp/post/160831986220/%E7%B4%94%E7%B2%8B%E9%96%A2%E6%95%B0%E5%9E%8B%E3%83%87%E3%83%BC%E3%82%BF%E6%A7%8B%E9%80%A0).
module rec MiloneLang.RandomAccessList

type RawNode =
  | Leaf of value: obj
  | Node of value: obj * left: RawNode * right: RawNode

// (len, (weight, node) list, None)
type RandomAccessList<'T> = int * (int * RawNode) list * 'T option

let empty (): RandomAccessList<_> = 0, [], None

let length (ral: RandomAccessList<_>): int =
  let len, _, _ = ral
  len

let add value (ral: RandomAccessList<_>): RandomAccessList<_> =
  let len, ts, none = ral
  let _typeUnifier () = [ Some value; none ] |> ignore

  let value = box value

  let ts =
    match ts with
    | (w1, t1) :: (w2, t2) :: rest ->
        if w1 = w2
        then (1 + w1 + w2, Node(value, t1, t2)) :: rest
        else (1, Leaf value) :: ts

    | _ -> (1, Leaf value) :: ts

  len + 1, ts, none

// I don't need this for now.
// let pop (ral: RandomAccessList<_>): _ option * RandomAccessList<_> =
//   let len, ts, none = ral

//   match ts with
//   | [] -> None, ral

//   | (w, Leaf x) :: ts ->
//       assert (w = 1)

//       let head = unbox x
//       let _typeUnifier () = [ Some head; none ] |> ignore

//       Some head, (len - 1, ts, none)

//   | (w, Node (x, t1, t2)) :: ts ->
//       let head = unbox x
//       let _typeUnifier () = [ Some head; none ] |> ignore

//       let ts = (w / 2, t1) :: (w / 2, t2) :: ts
//       Some head, (len - 1, ts, none)

/// Gets i'th item.
let item (index: int) (ral: RandomAccessList<_>): _ =
  let len, ts, none = ral
  assert (index < len)

  let rec go2 w i t =
    match t with
    | Leaf x ->
        assert (w = 1)
        unbox x

    | Node (x, t1, t2) ->
        if i = 0 then unbox x
        else if i <= w / 2 then go2 (w / 2) (i - 1) t1
        else go2 (w / 2) (i - 1 - w / 2) t2

  let rec go1 i ts =
    match ts with
    | [] -> failwith "NEVER: Out of range."
    | (w, t) :: ts -> if i < w then go2 w i t else go1 (i - w) ts

  let value = go1 (len - 1 - index) ts
  let _typeUnifier () = [ Some value; none ] |> ignore

  value

/// Replaces i'th item immutably.
let withItem (index: int) value (ral: RandomAccessList<_>): RandomAccessList<_> =
  let len, ts, none = ral
  assert (index < len)

  let _typeUnifier () = [ Some value; none ] |> ignore

  let value = box value

  let rec go2 w i t =
    match t with
    | Leaf _ -> Leaf value

    | Node (x, t1, t2) ->
        if i <= w / 2
        then Node(x, go2 (w / 2) (i - 1) t1, t2)
        else Node(x, t1, go2 (w / 2) (i - 1 - w / 2) t2)

  let rec go1 i ts =
    match ts with
    | [] -> failwith "NEVER: Out of range."

    | (w, t) :: ts -> if i < w then (w, go2 w i t) :: ts else (w, t) :: go1 (i - w) ts

  let ts = go1 (len - 1 - index) ts
  len, ts, none

/// Iterates over items in order to compute some state. Equivalent to `List.fold`.
let fold folder state (ral: RandomAccessList<_>) =
  let _, ts, none = ral

  let _typeUnifier () =
    match none with
    | None -> ()
    | Some x -> folder state x |> ignore

  let rec go2 state t =
    match t with
    | Leaf x -> folder state (unbox x)

    | Node (x, t1, t2) ->
        let state = go2 state t2
        let state = go2 state t1
        folder state (unbox x)

  let rec go1 state ts =
    match ts with
    | [] -> state

    | (_, t) :: ts ->
        // No need to be tail-recursive because ts is short: O(log N).
        let state = go1 state ts
        go2 state t

  go1 state ts

let map f (ral: RandomAccessList<_>) =
  let len, ts, none = ral

  let none =
    match none with
    | None -> None
    | Some x -> Some(f x)

  let g x = box (f (unbox x))

  let rec go2 t =
    match t with
    | Leaf x -> Leaf(g x)

    | Node (x, t1, t2) ->
        let t2 = go2 t2
        let t1 = go2 t1
        Node(g x, t1, t2)

  let rec go1 ts =
    match ts with
    | [] -> []

    | (w, t) :: ts ->
        let ts = go1 ts
        (w, go2 t) :: ts

  let ts = go1 ts
  len, ts, none

let ofList (xs: _ list): RandomAccessList<_> =
  List.fold (fun ral x -> add x ral) (empty ()) xs

let toList (ral: RandomAccessList<_>): _ list =
  ral |> fold (fun acc x -> x :: acc) [] |> List.rev
