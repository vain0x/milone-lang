# Tuple type

Tuple types are anonymous data structure to carry multiple values as single value.

Tuple types are written as `T1 * T2 * ...`, where Ti is the type of i'th item.

Tuple values are created by separating expressions by commas (`,`).

2-tuple:

```fsharp
    // Create tuple.
    let pair: int * string = 2, "three"

    // Decompose tuple.
    let x, y = pair

    assert (x = 2)
    assert (y = "three")
```

3-tuple:

```fsharp
    // Create 3-tuple.
    let triple: int * float * string =
        2, 3.14, "seven"

    // Decompose tuple.
    let x, y, z = triple

    assert (x = 2)
    assert (y = 3.14)
    assert (z = "seven")
```

And so on.

## Runtime representation

(The runtime representation of tuples is unlikely stabilized. For example, compiler may allocate large tuples on heap for performance in future.)

Currently, tuple types are converted to generated C struct. Struct tag is uniquely computed from item type names.

```c
// int * string
struct IntStringPair {
    int t0;
    struct String t1;
};
```
