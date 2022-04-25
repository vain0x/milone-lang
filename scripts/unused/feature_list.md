## Features

Not all of F# features are supported. Features for functional-style programming are selected to write a compiler easily.

- Compile a CLI application (no libraries)
- Expressions
    - Literals: `42`, `3.14`, `"string"`, `"""raw string"""`
    - Operations: `a + b`, `s.[i]`, `h :: t`, `(x, y)`, etc.
    - Function calls: `f x y` and `y |> f x`
    - Function definitions: `let f x y = ..` and `fun x y -> ..`
    - Pattern matching
- Functions
    - Mutual recursion
    - Local variable capturing
    - Partial applications
    - Function objects
- Types
    - Polymorphic type inference
        - Only top-level functions are generalized
    - Primitive types: int, float, string, tuples, lists, functions, etc.
    - Discriminated unions
    - Records (non-generic ones only)
- IO
    - `printfn` (`%s`, `%d`, `%f` only)
