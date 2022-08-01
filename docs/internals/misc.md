# Misc

## Edges

The following illustrates edge cases that F# allows but milone-lang doesn't.

### As Pattern Syntax

`as` patterns don't parse correctly.

```fs
    match [(1, 2); (3, 4)] with
    | _, _ as xs :: _ as ys ->
      match xs, ys with
      | (1, 2), [(1, 2); (3, 4)] ->
        ()
      | _ ->
        assert false
    | _ ->
      assert false
```

In F#, the two lines are same, but milone-lang doesn't parse the first line.

```fsharp
    |   _, _ as xs  :: _  as ys -> ...
    | ((_, _) as xs :: _) as ys -> ...
```

### Union Type Syntax without Pipes

Defining discriminated unions require `|` in front of all variants.

```fs
    // A is a discriminated union with single case in F#.
    type A = B
    // vs. type A = | B

    // T is synonym of A.
    type T = A
```

### Redundant Payload Patterns

Const variants can't have payload patterns.

```fs
    type A = | A

    match A with
    | A _ -> () // Notice the `_`.
```
