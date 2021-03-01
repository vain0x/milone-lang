# Modules

## Guide-level explanation

Each source file is a module.

Each file starts with a module header.
Currently `ProjectName` is same as directory name and `ModuleName` is same as file name (excluding extension).
(See also [Projects](projects.md).)

```fsharp
module rec ProjectName.ModuleName
```

Symbols defined in a module are separated from other modules.
To access symbols in other modules, there are several ways: module synonyms and `open` statements.

### Module synonyms

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

### Open statements

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

### Private symbols

`private` keyword in front of defined symbol hides it from other modules.

```fsharp
module P.A

// These types and functions can't be referenced from other modules.
type private InnerTy = | InnerTy of int
let private innerFun () = ()
```

## Advanced topics

- `module rec` is implemented, but non-recursive `module` isn't.

### Comparison with F#

In F#, each project has a project file (.fsproj). It describes:

- the ordered list of modules in the project
- and other projects that the project refers to.

/// (And bundled.)
///
/// ## Statements as dependency specification
///
/// 
/// and external project/package references.
///
/// In milone-lang, `open`/`module` statements work as dependency for now.
///
/// When a module X has a statement `open P.M`,
/// where P is project name and M is module name,
/// such module `P.M` is also a member of the project,
/// and `P.M` should be earlier than X in the project.
///
/// `module Y = P.M` (module synonym) has same effect too.
///
/// Where the project `P` come from, is not specified here.
/// Instead, this module just uses a function `FetchModule`,
/// provided by the caller, to load a module.
/// See `Cli.fs` for its implementation.
///
/// ## Dependency Resolution Algorithm
///
/// Dependency resolution is just a topological sort.
///
/// Starting from a module that is specified by the user,
/// recursively loads modules based on statements described above.
///
/// ## Example
///
/// Assume we want to compile this module.
///
/// ```fsharp
/// open MiloneLang.SyntaxParse
///
/// let main _ = 0
/// ```
///
/// Since this opens `MiloneLang.SyntaxParse`,
/// the bundler finds `SyntaxParse.fs` (some where),
/// load, tokenize, and parse.
///
/// Assume `SyntaxParse` has another open statement.
///
/// ```fsharp
/// // SyntaxParse.fs
/// open MiloneLang.SyntaxTokenize
///
/// let parse () = 0
/// ```
///
/// Bundler finds `SyntaxTokenize.fs` and parse.
///
/// ```fsharp
/// // SyntaxTokenize.fs
/// let tokenize () = 0
/// ```
///
/// Finally these modules are merged in the order.
///
/// ```fsharp
/// let tokenize () = 0 // from Lexing.fs
/// let parse () = 0 // from SyntaxParse.fs
/// let main _ = 0 // from entrypoint module
/// ```
