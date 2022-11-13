# Extension: Never Type

The `never` type is a special type for a particular situation.

## Guide-level Explanation

This is a typical usage of never type:

```fsharp
    // There exists a function findThing : () -> A option.
    // We know it must return (Some x) here for some reason.

    let found : A =
        match findThing () with
        | Some it -> it
        | None -> unreachable ()
```

The type of the expression `unreachable ()` is `never`.
`never` is an exception of the rule that the all arms of a match needs to have the same type.

### Never-returning Functions

`never` type is usually used as a result type of a function that returns **never**.
There are several reasons such situation happens:

- **exit**: Function that exits the thread or the process, which doesn't return to the caller
- **stop**: Function that enters into unconditionally infinite loop, which that doesn't return

## Advanced Topics

### Typing Rules

**Let-init**:

```
    meta type A is fresh,
    Γ |- init: never,
    Γ |- (let pat = (_: A) in next): T
==>
    Γ |- (let pat = init in next): T
```

- During type-checking of a `let-ini` expression,
    if the type of init is `never`,
    apply this rule:
    - Generate a fresh meta type A.
    - Perform type-checking `pat : A` rather than `pat : never`.

**Match**:

```
    Γ |- cond: T,
    ((pat: T), Γ) |- arm: never,
    Γ |- (match cond with rest...): U
==>
    Γ |- (match cond with | pat -> arm | rest...): U
```

- Durning type-checking of a match expression,
    if the type of an arm body is `never`,
    apply this rule:
    - Don't unify the type of arm (`never`) to the target type of the match expression.

**The `main` Function**:

- The body of the `main` function is allowed to be `never`.

### Generic Result Type Pattern

OCaml and F# don't have `never` type as a built-in type.
Instead, never-returning functions in the languages have some form of signatures that the result type is an unconditionally generic type parameter.

For example, there exists `failwith` function that always raises an exception, never-returning.
Its signature is:

```fsharp
    fun failwith<'T> : string -> 'T
```

That reads "this function takes a string and returns something of type 'T," and the type `'T` is arbitrary.
The signature implies that `failwith` never returns because there doesn't exist such a function that returns something of whatever type the caller demand.

### Motivation

In milone-lang, never-returning functions can be just a generic function as above.
However it doesn't work well with:

- monomorphization that duplicates generic functions, and
- ownership restriction that rejects generic function parameters to be bound to owned types.

## See Also

There exist other languages that have built-in `never` type.

- TypeScript: [TypeScript Handbook - Basic Types #never](https://www.typescriptlang.org/docs/handbook/basic-types.html#never)
- Rust: [Never type - The Rust Reference](https://doc.rust-lang.org/reference/types/never.html)
