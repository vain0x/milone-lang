module rec union_rec.Program

/// Infinite sequence of integer.
/// Example of indirectly recursive discriminated union type.
type LazyList =
  | Nil
  | Cons of int * (unit -> LazyList)

let main _ =
  let cons tail head = LazyList.Cons(head, tail)

  let lazyListPrint n xs =
    let rec go n xs =
      if n > 0 then
        match xs with
        | LazyList.Nil -> ()
        | LazyList.Cons (head, tail) ->
            printfn "%d" head
            go (n - 1) (tail ())

    go n xs

  let fact =
    let rec makeTail n prev () =
      let head = n * prev
      head |> cons (makeTail (n + 1) head)

    makeTail 1 1 ()

  lazyListPrint 5 fact

  0
