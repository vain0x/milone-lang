# TODO

List of tasks. Because this is just a note for the author, it's not easy to understand what comments means. Feel free to ask with GitHub issues for details.

### Re-think features

It has too many features just for self-hosting.

### Inline functions

Implement function inlining to implement generic functions.

### Hindley-Milner type inference

- Generalize type of variable after definition analysis.
- Instantiate type scheme of function that is referenced in an expression.
- Inline generic functions to call-site.

### Recursive modules/functions

Support `let rec` and `module rec`.

To implement `module rec`, iterate over the body and find `let` expressions to collect name of functions defined in the module.

### Record types

Support record definitions, field access expressions and `with` update expressions.

It's unnecessary because we have tuples as replacement, however, painful.

```
type R = { X: int, .. }

X.Foo

{ X with Foo = 1 }
```

### Generic equality/string/etc.

Automatically generate these functions for each type.

- `string`
- `=`

### Module system

`module`

No plan for nested module supports.

### IO primitives

To compile multiple-file projects, we need some IO primitives.

Because it's verbose to implement classes such as `File` from .NET standard library, I have a plan to use non-F# primitives.

```fsharp
    _ioStdinReadToEnd: unit -> string
    _ioFileReadAllText: string -> string
    _ioFileWriteAllText: string -> string -> unit
```

### Multiple-file Project

We don't use `fsproj`. Plan:

- Compiler reads a source code from the standard input
- Parse it and find `open` statements that match `open D.X`, where `D` is the working directory name.
- We assume that there exists a file with name `X.milone` for each `open D.X`. Read the file to parse. And find `open` statements, and do things recursively.

### Low Priority

These features are unnecessary because we have replacement.

- sprintf, printf, failwithf
    - Generic `string` function is enough.
- Map
    - We can replace them with associative lists
- Bugs about arity calculation

### Not Supported

There are no plan to implement these features unnecessary for self-hosting.

- Mutability
- Classes, etc.
- .NET Standard Library
- Computation expressions
- Exceptions
- etc.
