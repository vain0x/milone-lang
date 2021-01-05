# List type

List is a container of multiple values in order.

## Instant usage

```fsharp
    // Create a list.
    let nil = []
    let xyz = [ x; y; z ]
    let wxyz = w :: xyz

    // Multiline list literal.
    let numbers =
        [
            1
            2
        ]

    // Decompose a list.
    match xyz with
    | [] -> assert false
    | head :: tail -> assert (head = x)

    match xyz with
    | [ a; b; c ] -> assert (a = x && b = y && c = z)
    | _ -> assert false
```

## Guide-level explanation

`T list` or `list<T>` is a list type for values of type `T`.
For example, `int list` is the list type of int values.

### List literals

Lists are written as `[ x; y; z ]` or in multiline:

```fsharp
    [
        x
        y
        z
    ]
```

Examples: `[]`, `[ 1 ]`, `[ 1; 2; 3; 4 ]`.

Empty list `[]` is called *nil*.

### Cons operator

Cons operator (`(::)`) prepends an item to a list: `x :: xs`.

For example:

```fsharp
    let xs = [ 1; 2 ]
    let ys = 0 :: xs
    // ys is [ 0; 1; 2 ]
```

### Pattern matching

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

## Advanced topics

### Runtime representation

Currently, list types are represented by intrusive linked list structure like this:

```c
// int list ==> struct IntList const *
struct IntList {
    int head;
    struct IntList const *tail;
};
```

Especially, `[]` is `NULL`.

Cons objects are allocated on heap.
