# MILONE-LANG

Self-hosting the initial goal was **achieved** at [v0.1.0](https://github.com/vain0x/milone-lang/tree/v0.1.0). Currently working for initial release.

## What

**Milone-lang** is a F#-subset programming language. The goal ~is~ was **[self-hosting](https://en.wikipedia.org/wiki/Self-hosting)**, i.e. to develop a milone-lang compiler that can compile the compiler itself.

This is a hobby project. Don't use in production. Pull requests and issues are welcome.

## (No) Getting Started

No releases available yet. To try, see the Development section below.

## How It Works

Currently the target language is C. That is, the milone-lang compiler reads a source code and translates to a C code. For example, assume the following code is given.

```fsharp
let main _ =
  let rec factorial x =
    if x = 0 then 1 else x * factorial (x - 1)
  factorial 5 - 120 // exit code
```

Then the output is a C code that looks like the following.

```c
int factorial(int x) {
    if (x == 0) {
        return 1;
    } else {
        return x * factorial(x - 1);
    }
}

int main() {
    return factorial(5) - 120;
}
```

*The actual output is available at [factorial.c](./tests/examples/factorial/factorial.c).*

The diagram below illustrates how it does self-host finally.

```
    <milone-lang compiler>.fs
        |                | Compile with F# compiler
        |                v
        | Compile with <milone-lang compiler>.exe
        v                           ^ an executable on .NET runtime
    <milone-lang compiler>.c
        | Compile with C compiler
        v
    <milone-lang compiler>.exe
                 ^ a native executable
```

## Features

Not all of F# features are supported. Features for functional-style programming are selected to write a compiler easily.

- Compile a CLI application (no libraries)
- Expressions
    - Literals: `1`, `"str"`, etc.
    - Operations: `+`, `::`, etc.
    - Function calls: `f x y` and `y |> f x`
    - Function definitions: `let f x y = ..` and `fun x y -> ..`
    - Pattern matching
- Functions
    - Mutually recursion
    - Local variable capturing
    - Partial applications
    - Function objects
- Types
    - Polymorphic type inference
    - Primitive types: `int`, `string`, tuples, lists, functions, etc.
    - Discriminated unions (non-generic ones only)
    - Records (non-generic, non-recursive ones only)
- IO
    - `printfn` with `%s`, `%d`
    - Some file IOs

See [the tests/examples directory](./tests/examples) for working codes.

## Internals

See comments written at the top of each file to describe what it is.

Most of types and functions are defined in:

- [Util](MiloneLang/Util.fs)
    - Just a set of utility functions for string, list, map etc.
- [Syntax](MiloneLang/Syntax.fs)
    - Tokens, abstract syntax tree (AST), source location information etc.
- [Hir](MiloneLang/Hir.fs):
    - Functional-style intermediate representation
- [Mir](MiloneLang/Mir.fs):
    - Imperative-style intermediate representation
- [Cir](MiloneLang/Cir.fs)
    - AST of the C language for pretty-printing
- [FSharpOnly](MiloneLang/FSharpOnly.fs)

Program analysis and transformations are written in:

- [SyntaxTokenize](MiloneLang/SyntaxTokenize.fs) (milone-lang source code -> Token list)
- [SyntaxParse](MiloneLang/SyntaxParse.fs) (Token list -> AST)
- [AstToHir](MiloneLang/AstToHir.fs) (AST -> HIR)
- [Bundling](MiloneLang/Bundling.fs) (\*files\* -> HIR)
    - Loads source files of project and concatenates them into single HIR program
- [NameRes](MiloneLang/NameRes.fs) (Name resolution)
- [Typing](MiloneLang/Typing.fs) (Type inference)
- [MainHoist](MiloneLang/MainHoist.fs)
    - Resolves top-level bindings
- [AutoBoxing](MiloneLang/AutoBoxing.fs)
    - Resolves recursive nominal types
- [RecordRes](MiloneLang/RecordRes.fs)
    - Resolves use of field names
- [ClosureConversion](MiloneLang/ClosureConversion.fs)
    - Resolves non-closed functions
- [EtaExpansion](MiloneLang/EtaExpansion.fs)
    - Resolves partial applications and function references
- [Hoist](MiloneLang/Hoist.fs)
    - Just a preparation of monomorphization
- [Monomorphization](MiloneLang/Monomorphization.fs)
    - Resolves use of generic functions by code cloning
- [TailRecOptimizing](MiloneLang/TailRecOptimizing.fs)
    - Marks tail-recursive calls to be optimized
- [MirGen](MiloneLang/MirGen.fs) (HIR -> MIR)
    - Resolves pattern matches
- [CirGen](MiloneLang/CirGen.fs) (MIR -> CIR)
- [CirDump](MiloneLang/CirDump.fs) (CIR -> C source code)

Entrypoints:

- [Cli.fs](MiloneLang/Cli.fs)
    - CLI application logic shared by F# and milone-lang
- [Program.fs](MiloneLang/Program.fs)
    - Provides `main` function for .NET
- [MiloneLang.fs](MiloneLang/MiloneLang.fs)
    - Provides `main` function for milone-lang

## Development

Scripts are written for `bash` because I use a Ubuntu desktop for development. These scripts might work on Windows Subsystem Linux or macOS (not tried).

### Dev: Prerequisites

- Install .NET Core SDK [3.1 LTS](https://dotnet.microsoft.com/download/dotnet-core/3.1)
- Install [F#](http://ionide.io/#requirements) 4.1 tools

### Dev: Testing

The `tests` directory contains files for testing.

`dotnet test` performs unit testing. All `tests/*/X/X.fs` files are compiled to matching `tests/*/X/X.c`. The outputs have verified before commit, so it's OK if none of them changed. If an output is changed, you need to perform integration testing to verify.

`./test` performs integration testing. Each `tests/*/X/X.fs` file is compiled to an executable using GCC and executed. It is verified by matching the stdout and exit code with `tests/*/X/X.out`.

`./test-self` performs self-compile checking. The milone-lang compiler (on .NET) compiles the compiler itself (obtaining first C code) and the output compiler also compiles the compiler itself (obtaining second C code). It's okay if the generated two C codes are same.

There are some categories of testing files:

- `features`: Test cases of language features
- `functions`: Test cases of primitives
- `examples`: Complex codes
- `pendings`: Incomplete test cases
- `edges`: Exotic test cases
- `errors`: Test cases of compile errors

### Dev: See also

- [TODO list](https://github.com/vain0x/milone-lang/projects/1): TODO list. Feel free to clarify by opening an issue.
- [notes.md](notes.md): Notes on future works.
- [milone_libs](./milone_libs): Standard library for milone-lang.
    - [MiloneCore](./milone_libs/MiloneCore): Core library that is a subset of F# with compatible behavior.
    - [MiloneStd](./milone_libs/MiloneStd): Standard library for milone-lang, not compatible with F#.
