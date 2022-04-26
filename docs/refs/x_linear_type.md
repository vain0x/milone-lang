# Extensions: Linear type

Linear type is a container of single value that must be used linearly.

- *NOTICE(lang-ext)*: This feature is "language extension", i.e. not compatible with F#. Identifiers that start with `__` are for extensions.
- *NOTICE(experimental)*: This feature can be modified or removed in future.

## Instant usage

```fsharp
    open Std.Linear

    // Acquires a resource (allocate/connect/etc.)
    let acquireThing () : Linear<A> =
        Linear.acquire (malloc ())

    // Disposes a resource. (free/disconnect/etc.)
    let disposeThing (resource: Linear<A>) : unit =
        let handle = Linear.dispose resource
        free handle
```

## Guide-level explanation

The `Std.Linear` module provides several primitives for this feature.

```fsharp
    module Std.Linear =
        type Linear<'T>
        fun acquire<'T> : 'T -> Linear<'T>
        fun dispose<'T> : Linear<'T> -> 'T
        // etc.
```

`Linear<T>` is a linear type.

The type itself is really simple.
Primitive `Linear.acquire` function wraps a value in a linear.
Primitive `Linear.dispose` function unwraps a linear value.

The key point is a feature called *linearity check*. Compiler ensures that values of linear type are used *linearly*, i.e. exactly once.
Linearity check reports a compile error when it detects the violation of linearly, that is, a value of linear type is unused or used more than once.

Linearity check is useful for values that can't be copied or shared.

### Case study: file handle management

This is a story about linearity and file system API.

Consider a file handle, which is obtained by opening a file to operate on it.
The handle must be passed in an API to close the file.
By wrapping the handle in a linear type, linearity check ensures that all file handles are closed.

Let a module provide an API for file system manipulation, which consists of a FileHandle type and functions to operate on files:

```fsharp
// Sketch of File module:

/// Linear file handle.
type FileHandle = FileHandle of Linear<...>

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
Linearity check protects the file handle from abusing.

```fsharp
    closeFile h
    let _ = readLine h
    //               ^ Error!
```

## Linear types and non-linear types

Types are classified to linear types and others (non-linear types) automatically.

`Linear<T>` is literally linear type.

*Non-linear types*: Basic types (such as `int` and `string`) are non-linear.
Function types are non-linear no matter whether linear types appear in its signature. For example, `Linear<int> -> unit` is non-linear.

Compound types (lists, tuples, unions and records) are linear when it contains other linear types in it.
For example:

- *list*: `Linear<int> list` is linear
- *tuple*: `Linear<int> * int` is linear
- *union*:
    - `type U = | V of Linear<int> ` is linear
    - `type U = | V of Linear<int> | W` is also linear. Note that `W` is linear value despite it contains no linear values in it.
- *record*: (never linear for now)

## Linear types and branching

Linearity check is especially complicated on branching.

`match` expressions must use linear variables consistently in branches.
That is, a variable of linear type must be used either in *all* branches or *none* of them.
Otherwise, it becomes unclear that a linear variable is disposed or not, depending on which branch is picked.

```fsharp
    // The program is incorrect:

    let r: LinearType = Linear.acquire ()

    match flip () with
    | A ->
        Linear.dispose r

    | B ->
        ()
    //  ^ ERROR! This branch must use `r`.
```

`if` expressions go same.

## Immaturity and future extensions

There are some restrictions due to maturity of language and implementation.

- Union types can't be linear in some situation.
- Record types can't be linear. In other words, field types can't be linear.
- Generic function can't bind type variables to linear types.
    - Note that type variables of generic types can be linear; e.g. `option<Linear<int>>`.
- Linear variables can't be used in local functions.

## Advanced topics

### Runtime representation

Runtime representation of `Linear<T>` is same as `T`.
`acquire` and `dispose` are noop at runtime.

### Prior art

- [linear types · Wiki · Glasgow Haskell Compiler / GHC · GitLab](https://gitlab.haskell.org/ghc/ghc/-/wikis/linear-types): Linear types in Haskell as compiler extension
- [What is Ownership? - The Rust Programming Language](https://doc.rust-lang.org/book/ch04-01-what-is-ownership.html): "Ownership" in the Rust language. Ownership shares the motivation but is different than linear types.
