# Tuple type

Tuple types are anonymous data structure to carry multiple values as single value.

Type of tuple is written as `T1 * T2 * ...`, where Ti is the type of i'th item.

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
