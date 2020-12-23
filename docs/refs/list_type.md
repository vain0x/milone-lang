# List type

List is a container of multiple values in order.

All items of single list must have same type. For item type `T`, the type of list is written as `T list` or `list<T>`. For example, `int list` is the list type of int values.

## List literals

Lists are written as `[ x; y; z ]` or in multiline:

```fsharp
    [
        x
        y
        z
    ]
```

Example: `[]`, `[ 2 ]`, `[ 2; 3; 5; 7 ]`.

Empty list `[]` is called *nil*.

## Cons operator

Cons operator (`(::)`) prepends an item to a list: `x :: xs`.

Example:

```fsharp
    let xs = [ 3; 5 ]
    let ys = 2 :: xs
    // ys is [ 2; 3; 5 ]
```

## Pattern matching

A list value is either *nil* (empty) or *cons* (non-empty).

```fsharp
    let first (xs: string list) =
        match xs with
        | [] -> ""
        | head :: tail -> head

    assert (first [] = "")
    assert (first [ "john" ; "jane" ] = "john")
```

List literal can be used as a pattern.

```fsharp
    | [ first; second ] -> ...
```

## Runtime representation

Currently, list types are represented by intrusive linked list structure like this:

```c
// int list ==> struct IntList const *
struct IntList {
    int head;
    struct IntList const *tail;
};
```

Especially, `[]` is `NULL`. Each cons object is allocated on heap.
