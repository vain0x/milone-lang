# Extension: Own Type

The `Own` type is a container of single value that holds ownership.

- *NOTICE(lang-ext)*: This feature is "language extension", i.e. not compatible with F#. Identifiers that start with `__` are for extensions.
- *NOTICE(experimental)*: This feature can be modified or removed in future.

## Instant Usage

```fsharp
    open Std.Own

    // Acquires a resource (allocate/connect/etc.)
    let acquireThing () : Own<A> =
        Own.acquire (malloc ())

    // Disposes a resource. (free/disconnect/etc.)
    let disposeThing (resource: Own<A>) : unit =
        let handle = Own.release resource
        free handle
```

## Guide-level Explanation

The `Std.Own` module provides several primitives for this feature.

```fsharp
    module Std.Own =
        type Own<'T>
        fun acquire<'T> : 'T -> Own<'T>
        fun release<'T> : Own<'T> -> 'T
        // etc.
```

`Own<T>` is an owned type.

The type itself is really simple.
Primitive `Own.acquire` function wraps a value in an Own value.
Primitive `Own.release` function unwraps an Own value.

The key point is a feature called *ownership check*. Compiler ensures that values of owned type are used *linearly*, i.e. exactly once.
Ownership check reports a compile error when it detects the violation of ownership rule, that is, a value of owned type is unused or used more than once.

Ownership check is useful for values that can't be copied or shared.

### Case Study: File Handle Management

This is a story about ownership and file system API.

Consider a file handle, which is obtained by opening a file to operate on it.
The handle must be passed in an API to close the file.
By wrapping the handle in an owned type, ownership check ensures that all file handles are closed.

Let a module provide an API for file system manipulation, which consists of a FileHandle type and functions to operate on files:

```fsharp
// Sketch of File module:

/// Owned file handle.
type FileHandle = FileHandle of Own<...>

/// Opens a file.
let openFile (filename: string) : FileHandle = ...

/// Closes a file.
let closeFile (handle: FileHandle) : unit = ...

/// Reads a line from file.
let readLine (file: FileHandle) : string * FileHandle = ...
```

There are there functions.
They can be classified to three kinds:

- *Constructor*: Function to acquire FileHandle
    - `openFile`
- *Transformer*: Function to use FileHandle
    - `readLine`
- *Destructor*: Function to dispose FileHandle
    - `closeFile`

The constructor function (`openFile`) returns a FileHandle.
And it does't take `FileHandle`s as parameter.
Since other functions take a FileHandle as parameter, program can't call them before `openFile`.
It's natural that a program needs to call `openFile` first to operate on a file.

```fsharp
    let h: FileHandle = openFile "/path/to/file.txt"
```

The transformer function (`readLine`) takes a file handle and also returns it back (or another one).
It can be called repeatedly by using returned file handles.

```fsharp
    let l1, h = readLine h
    let l2, h = readLine h
    let l3, h = readLine h
```

The destructor function (`closeFile`) takes a file handle but doesn't return it.
The function signature reflects the fact that closed file handle is no longer available.

```fsharp
    closeFile h
    // File handle h is no longer available.
```

However the file handle is still held by the variable `h`.
It might be used after `closeFile`.
Ownership check protects the file handle from abusing.

```fsharp
    closeFile h
    let _ = readLine h
    //               ^ Error!
```

## Owned Types and Non-owned Types

Types are classified to owned types and others (non-owned types) automatically.

`Own<T>` is literally an owned type.

*Non-owned types*: Basic types (such as `int` and `string`) are non-owned.
Function types are non-owned no matter whether owned types appear in its signature. For example, `Own<int> -> unit` is non-owned.

Compound types (lists, tuples, unions and records) are owned types when it contains other owned types in it.
For example:

- *list*: `Own<int> list` is an owned type
- *tuple*: `Own<int> * int` is an owned type
- *union*:
    - `type U = | V of Own<int> ` is an owned type
    - `type U = | V of Own<int> | W` is also an owned type. Note that `W` is a value of owned type despite it contains no values of owned type in it.
- *record*: (can't be an owned type for now)

## Owned Types and Conditional Branching

Ownership check is especially complicated on branching.

`match` expressions must use variables of owned type consistently in branches.
That is, a variable of owned type must be used either in *all* branches or *none* of them.
Otherwise, it becomes unclear that a variable of owned type is disposed or not, depending on which branch is picked.

```fsharp
    // The program is incorrect:

    let r: Own<unit> = Own.acquire ()

    match flip () with
    | A ->
        Own.release r

    | B ->
        ()
    //  ^ ERROR! This branch must use `r`.
```

`if` expressions go same.

## Immaturity and Future Extensions

There are some restrictions due to maturity of language and implementation.

- Union types can't be an owned type in some situation.
- Record types can't be owned types. In other words, field types can't be owned types.
- Generic function can't bind type variables to owned types.
    - Note that type variables of generic types can be owned types; e.g. `option<Own<int>>`.
- Variables of owned type can't be used in local functions.

## Advanced Topics

### Runtime Representation

Runtime Representation of `Own<T>` is same as `T`.
`acquire` and `dispose` are noop at runtime.

### Prior Arts

- [linear types · Wiki · Glasgow Haskell Compiler / GHC · GitLab](https://gitlab.haskell.org/ghc/ghc/-/wikis/linear-types): Linear types (academic name of "owned types" here) in Haskell as compiler extension
- [What is Ownership? - The Rust Programming Language](https://doc.rust-lang.org/book/ch04-01-what-is-ownership.html): "Ownership" in the Rust language shares the motivation although it's different than that in the milone-lang.
