# TODO

List of tasks. Because this is just a note for the author, it's not easy to understand what comments means. Feel free to ask with GitHub issues for details.

### Re-think features

It has too many features just for self-hosting.

### Generic equality/string/etc.

Automatically generate these functions for each type.

- `string`
- `=`

### Library functions

assert, failwith, List.map, String.concat, etc.

### Format strings

printfn, eprintfn, failwithf, etc.

### Small things

- option type
- type variables (`'a`) in type expressions
- str.Substring
- str.Contains
- bump memory allocator instead of malloc

### Low Priority

These features are unnecessary because we have replacement.

- sprintf, printf, failwithf
    - Generic `string` function is enough.
- Set/Map
    - We can replace them with associative lists
- Record types
- Bugs about arity calculation
- Bugs about interaction between module-rec and let-polymorphism

## Not Supported

There are no plan to implement these features unnecessary for self-hosting.

- Mutability
- Classes, etc.
- .NET Standard Library
- Computation expressions
- Exceptions
- etc.

The following shows edge cases that F# allows but milone-lang doesn't.

### As pattern syntax

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

### Union type syntax without pipes

Defining discriminated unions require `|` in front of all variants.

```fs
    // A is a discriminated union with single case in F#.
    type A = B
    // vs. type A = | B

    // T is synonym of A.
    type T = A
```

### Redundant payload patterns

Const variants can't have payload patterns.

```fs
    type A = | A

    match A with
    | A _ -> () // Notice the `_`.
```
