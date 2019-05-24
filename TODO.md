# TODO

List of tasks. Because this is just a note for the author, it's not easy to understand what comments means. Feel free to ask with GitHub issues for details.

### Re-think features

It has too many features just for self-hosting.

### Type synonyms

```fsharp
type FooId = int
```

### Recursive unions

Recursive unions should be allowed for expression types.

```fsharp
type Expr =
    | Int of int
    | Add of Expr * Expr
```

### Recursive modules/functions

Support `let rec` and `module rec`.

To implement `module rec`, iterate over the body and find `let` expressions to collect name of functions defined in the module.

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

### Low Priority

These features are unnecessary because we have replacement.

- sprintf, printf, failwithf
    - Generic `string` function is enough.
- Set/Map
    - We can replace them with associative lists
- Record types
- Bugs about arity calculation

### Not Supported

There are no plan to implement these features unnecessary for self-hosting.

- Mutability
- Classes, etc.
- .NET Standard Library
- Computation expressions
- Exceptions
- etc.
