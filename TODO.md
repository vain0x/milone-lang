# TODO

List of tasks. Because this is just a note for the author, it's not easy to understand what comments means. Feel free to ask with GitHub issues for details.

### Re-think features

It has too many features just for self-hosting.

### Generic equality/string/etc.

Automatically generate these functions for each type.

- `string`
- `=`

### IO primitives

To compile multiple-file projects, we need some IO primitives.

Because it's verbose to implement classes such as `File` from .NET standard library, I have a plan to use non-F# primitives.

```fsharp
    _ioStdinReadToEnd: unit -> string
    _ioFileReadAllText: string -> string
    _ioFileWriteAllText: string -> string -> unit
```

### Library functions

assert, failwith, List.map, String.concat, etc.

### Format strings

printfn, eprintfn, failwithf, etc.

### Small things

- option type
- type variables (`'a`) in type expressions
- str.Substring
- str.Contains
- multiline string
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

### Not Supported

There are no plan to implement these features unnecessary for self-hosting.

- Mutability
- Classes, etc.
- .NET Standard Library
- Computation expressions
- Exceptions
- etc.
