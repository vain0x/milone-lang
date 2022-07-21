# Result type

Result is a container type for value that might be failed with error.

## Instant usage

```fsharp
    // Creation.
    let error = Error "Something wrong"
    let ok = Ok 42

    // Decomposition.
    match ok with
    | Ok n -> assert (n = 42)
    | Error _ -> assert false

    // Pipeline.
    result |> Result.bind fallibleFun |> Result.map pureFun
```

## Guide-level explanation

`Result<T, E>` is a result type whose value type is `T` and error type is `E`.

A computation that can abort with an error returns a value of result type.

*WIP: add intuitive example where there are two kind of non-logical failure*

### Difference from option type

Result is similar to [option type](option_type.md).

Prefer Result over option when reason of failure is concerned.

### Difference from exceptions

Milone-lang doesn't support exceptions.

### Remarks

- Use assertion or "abort with message" for logical or non-recoverable error.
- One might attempt to write perfectly precise error type, which might be unnecessary.

## Advanced topics

### Wording

- A function is *fallible* when its result type is `Result`.

### Runtime representation

Result is a generic discriminated union type.

- See definition in `Std.Result`
- See details in [discriminated union types#Runtime representation](discriminated_union_types.md#Runtime-representation)

### History of name

Name of `Result` type starts with uppercase unlike `option`.

- Option type originates in OCaml language (and its ancestors) where type name should start with lowercase.
- Result type is introduced in [F# 4.1](https://devblogs.microsoft.com/dotnet/announcing-f-4-1-and-the-visual-f-tools-for-visual-studio-2017-2/)in 2017-02. At that time, OCaml didn't have result type.
- After that, `result` type (lowercase) is added to [OCaml 4.08](https://ocaml.org/releases/4.08.0.html) in 2019-06.
