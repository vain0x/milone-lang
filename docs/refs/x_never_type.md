# Extension: Never Type

The `never` type is a special type for particular situations.

## Guide-level Explanation

This is a typical usage of `never`:

```fsharp
    // There exists a function findThing : () -> A option.
    // We know it must return (Some x) here for some reason.

    let found : A =
        match findThing () with
        | Some it -> it
        | None -> unreachable ()
    //            ^^^^^^^^^^^^^^
```

The type of `unreachable ()` is `never`.
Never-typed arms are ignored to compute the type of match expressions.

### Never-returning Functions

`never` is usually used as a result type of a function that **never** returns.
There are several reasons:

- **exit**: Function that exits the thread or the process, which doesn't return
- **stop**: Function that enters into unconditionally infinite loop, which doesn't return

## Advanced Topics

### Motivation

`never` is an appropriate way to represent never-returning function.

Note that [generic return type pattern](#generic-return-type-pattern) written below works also in milone-lang but not good in several reasons:

- Monomorphization unnecessarily duplicates generic-return functions
- Ownership restriction rejects generic-return functions to make its return type an owned type
- Doesn't represent never-returning actually

Another benefit is the compiler can emit [`_Noreturn`][_Noreturn] attribute on never-returning functions.

[_Noreturn]: https://en.cppreference.com/w/c/language/_Noreturn

### Typing Rules

**Expression Statements**:

```
    Γ |- e1: never,
    Γ |- e2: T
==>
    Γ |- (e1; e2): T
```

- (Informally) Non-last expressions in block can be `never`.

**Let-init**:

```
    meta type A is fresh,
    Γ |- init: never,
    Γ |- (let pat = (_: A) in next): T
==>
    Γ |- (let pat = init in next): T
```

- During type-checking of a let-val expression,
    if init type is `never`,
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
    if type of an arm is `never`,
    apply this rule:
    - Don't unify the type of arm (`never`) to the target type of the match expression.

### Generic Return Type Pattern

F# doesn't have `never` as a built-in type.
Instead, never-returning functions have signatures with generic type parameter in return position.

For example, signature of `failwith` is:

```fsharp
    fun failwith<'T> : string -> 'T
```

Expression `failwith "message"` can have any type.
All rules of `never` above are virtually applied.

The signature doesn't necessarily imply that the function never returns.
There exists a non-never function of the same signature (`fun _ -> unbox (box 0)`.)

### Runtime Representation

- Runtime representation of `never` is same as `unit` (`char` in C)
- `never` as function return type compiles to `void` in C instead

### Remarks

- There exists no value of `never` type
- `never` is just a unit-like type except for the rules above
- No structural subtyping. `never` doesn't work like the bottom type
- The type of `assert false` is `unit` since type check doesn't depend on values

## See Also

There exist other languages that have built-in `never` type.

- TypeScript: [TypeScript Handbook - Basic Types #never](https://www.typescriptlang.org/docs/handbook/basic-types.html#never)
- Rust: [Never type - The Rust Reference](https://doc.rust-lang.org/reference/types/never.html)
