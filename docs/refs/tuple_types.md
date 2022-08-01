# Tuple Types

Tuple is an anonymous data structure to carry multiple values as single value.

### Guide-level Explanation

Tuple types are written as `T1 * T2 * ...`, where Ti is the type of i'th item.
For example, `int * string` is a pair of int and a string.

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

## Advanced Topics

### Runtime Representation

(The runtime representation of tuples is unlikely stabilized.)

Currently, tuple types are converted to generated C structs. Struct tag is uniquely computed from item types.

```c
// int * string
struct IntStringPair {
    int t0;
    struct String t1;
};
```
