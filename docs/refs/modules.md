# Modules

## Guide-level Explanation

Each source file is a module.

Each file starts with a module header.
Currently `ProjectName` is same as directory name and `ModuleName` is same as file name (excluding extension).
(See also [Projects](projects.md).)

```fsharp
module rec ProjectName.ModuleName
```

Symbols defined in a module are separated from other modules.
To access symbols in other modules, there are several ways: module synonyms and `open` statements.

### Module Synonyms

A module statement defines a module synonym.

```fsharp
module A = P.M
```

`A` is module synonym that denotes to other module `P.M`.

For example:

```fsharp
// P/A.milone
module P.A

let f () = ()
```

```fsharp
// P/B.milone
module P.B

module A = P.A

// Now you can use `f` defined in `A`.
let g () = A.f ()
```

### Open Declarations

After `open` statement, all symbols defined in specified module are visible in the current module.

```fsharp
// P/A.milone
module P.A

let f () = ()
```

```fsharp
// P/B.milone
module P.B

open P.A

let g () = f () // f is defined in `P.A`
```

### Private Symbols

`private` keyword in front of defined symbol hides it from other modules.

```fsharp
module P.A

// These types and functions can't be referenced from other modules.
type private InnerTy = | InnerTy of int
let private innerFun () = ()
```

## Advanced Topics

- `module rec` is implemented, but non-recursive `module` isn't.

### Comparison with F#

In F#, each project has a project file (.fsproj). It describes:

- the ordered list of modules in the project
- and other projects that the project refers to.
