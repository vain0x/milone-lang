# Option type

Option is a container for some value which can be missing.

## Instant usage

```fsharp
    // Creation.
    let none = None
    let some = Some 42

    // Decomposition.
    match some with
    | None -> assert false
    | Some x -> assert (x = 42)
```

## Guide-level explanation

`T option` or `option<T>` is an option type for type `T`.
For example, `int option` is an option of int value.

### As error handling

Option is useful when a function can fail to produce its result.
A typical example is `List.tryHead` function in the List module.
It tries to extract the first item from a list.
However, it isn't always possible since list can be empty.
For such case, `tryHead` returns a value wrapped with an option.

```fsharp
    let tryHead (xs: string list): string option =
        match xs with
        | [] -> None
        | x :: _ -> Some x

    let _ = tryHead []
    //=> None
    
    let _ = tryHead [ "x"; "y" ]
    //=> Some "x"
```

### As optional data

Option is also useful when a value is missing at first and is filled later.

```fsharp
type MyConfig =
    { FileName: string option }

let defaultConfig: MyConfig = { FileName = None }

let parseArgs args (config: MyConfig) =
    match args with
    | fileName :: _ -> { config with FileName = Some fileName }
    | _ -> config

let doSomething args (config: MyConfig) =
    let fileName =
        match config.FileName with
        | None -> "default.txt" // Use default value (or error?)
        | Some it -> it
    ...
```

In the example, config object is instantiated with options unspecified.
In `parseArgs` function, it is filled if the value is specified in argument list.
In `doSomething`, the option is unwrapped to use.
It can still be None.
You need to consider what to do in the case: falling back to a default value, raising an error, or something.

### Helper functions

Once you are familiar with option types, pattern matching on option might look too verbose.
Use Option module for built-in helper functions.

```fsharp
    config.FileName |> Option.defaultValue "default.txt"
```

### Combination with List

List module also provides several utilities related to options. Check these:

- List.tryPick
- List.choose

## Advanced topics

### As discriminated union

Option is just a generic discriminated union.

```fsharp
type option<'T> =
    | None
    | Some of 'T
```

### Runtime representation

(Unlikely stabilized.
Ideally the runtime representation should depend on the content type.
For example, if the content type has illegal bit pattern such as discriminated union with invalid discriminant, it might be reused for None instead of additional boolean flag.)

A pair of boolean flag and content.
The flag indicates whether it's None or Some.
The content part is only valid when it's Some.

```fsharp
// int option
struct IntOption {
    bool some;
    int value;
};
```

### Comparison to F#

In F#, there are two kinds of option-like types: `option` and `voption`.
The difference is runtime representation: `option` is a reference type, which is pointer-sized and the content is likely put on heap.
On the other hand, `voption` is a value type, which holds the content by-value along with a boolean flag.

`voption` is introduced later.
Most of functions support only `option`.
