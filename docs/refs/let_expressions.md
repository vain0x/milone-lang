# Let Expressions

## Guide-level explanation

### Variable definition

Let expression defines a variable like this:

```fsharp
    let name = initializer
    next
```

Example:

```fsharp
    let sum = 2 + 3
    assert (sum = 5)
```

When `initializer` expression is multiline, indent like this:

```fsharp
    let name =
        initializer
    next
```

Example:

```fsharp
    let sum =
        2
        + 3
        + 5

    assert (sum = 2 + 3 + 5)
```

### About indentation

`next` expression must be indented on the same column as `let` keyword.

```fsharp
//  let keyword is indented by 4 spaces here
//  v
    let x = 2
    assert (x = 2)
//  ^
//  and then next expression must be indented exactly 4 spaces
```

`initializer` expression must be indented deeper than `let`.

```fsharp
//  let keyword is indented by 4 spaces here
//  v
    let sum =
        2 + 3
//      ^ initializer expression must be indented more than 4 spaces
//        (so that it is distinct from next expression)

    assert (sum = 5)
```

### Type ascription

The type of variable is same as the type of `initializer` expression. If you want to make it explicit, write a type ascription like this:

```fsharp
    let sum: int = 2 + 3
    //     ^^^^^
    //     This states the type of sum is int explicitly.
    assert (sum = 5)
```

Compiler reports a type error if the ascription is wrong.

**Remark**: Type ascription doesn't change the value of expression. Type ascription is not *type casting*.

### Function definition

Let expression also defines a function like this:

```fsharp
    let name (p1: P1Type) (p2: P2Type): ResultType =
        body
    next
```

Example:

```fsharp
    let squareSum (x: int) (y: int): int =
        x * x + y * y

    // 3 * 3 + 4 * 4 = 9 + 16 = 25
    assert (squareSum 3 4 = 25)
```

These type ascriptions are recommended for readability, but optional:

```fsharp
    let squareSum x y = x * x + y * y
    assert (squareSum 3 4 = 25)
```

### Recursive functions

Recursive let expression defines a recursive function.

```fsharp
    let rec name param1 param2 ... = body
    next
```

Example:

```fsharp
    // Calculates the sum of integers from 0 to n (inclusive).
    let rec sum n =
        if n <= 0 then
            0
        else
            n + sum (n - 1)

    assert (sum 0 = 0)
    assert (sum 1 = 1 + 0)
    assert (sum 2 = 2 + 1 + 0)
    assert (sum 3 = 3 + 2 + 1 + 0)
```

### Polymorphic functions

Function defined by `let-fun` is polymorphic as possible.

```fsharp
    // Whatever the type of x is, `id x` should pass type checking.
    // So the type of `id` is T -> T for any type T.
    let id x = x

    assert (id 1 = 1)
    //      ^^ id: int -> int here

    assert (id "two" = "two")
    //      ^^ id: string -> string here
```

(TODO: Explain more. If you want to learn by yourself, search for Hindley-Milner type inference.)

## Advanced topics

### Generic syntax of let expressions

Let expression has several variants of syntax.

```fsharp
    // let-val expression
    let pattern = initializer
    next

    // let-fun expression
    let name param1 param2 ... = body
    next

    // let-rec expression
    let rec name param1 param2 ... = body
    next
```

`let-val` expression just expands to match expression:

```fsharp
    let pattern = initializer
    next
// ==>
    match initializer with
    | pattern -> next
```

The difference between `let-fun` and `let-rec` is only at name resolution.

```fsharp
    // With rec:
    // This denotes to the function itself.
    //             v
    let rec f () = f ()

    // Without rec:
    let f () = f ()
    //         ^
    // This denotes to the function defined above, not itself.
```
