# MILONE-LANG

Self-hosting is **achieved** at [v0.1.0](https://github.com/vain0x/milone-lang/tree/v0.1.0).

## What

**Milone-lang** is a F#-subset programming language.

The goal is **[self-hosting](https://en.wikipedia.org/wiki/Self-hosting)**, i.e. to develop a milone-lang compiler that can compile the compiler itself.

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

- [notes.md](notes.md): notes on future works.

## Internals

See the comments in source files for details.

Most of types are defined in the module:

- [Types](MiloneLang/Types.fs)

and functions are in:

- [FSharpOnly](MiloneLang/FSharpOnly.fs)
- [Helpers](MiloneLang/Helpers.fs)

The following transformations are consist of the compilation in the order:

- [SyntaxTokenize](MiloneLang/SyntaxTokenize.fs)
- [SyntaxParse](MiloneLang/SyntaxParse.fs)
- [Bundling](MiloneLang/Bundling.fs)
    - Source codes concatenation
- [AstToHir](MiloneLang/AstToHir.fs)
    - From abstract syntax tree (AST) to high-level intermediate representation (HIR)
    - For data structure decoupling and desugaring
- [NameRes](MiloneLang/NameRes.fs) (Name resolution)
- [Typing](MiloneLang/Typing.fs) (Type inference)
- [MainHoist](MiloneLang/MainHoist.fs)
    - Resolve top-level bindings
- [TyElaboration](MiloneLang/TyElaborating.fs)
    - Convert records to tuples
- [ClosureConversion](MiloneLang/ClosureConversion.fs)
    - Resolve use of local variables in functions
- [EtaExpansion](MiloneLang/EtaExpansion.fs)
    - Resolve partial applications
- [Hoist](MiloneLang/Hoist.fs)
    - Just a preparation of monomorphization
- [Monomorphization](MiloneLang/Monomorphization.fs)
    - Resolve generic functions by code clone
- [Mir](MiloneLang/Mir.fs)
    - Resolve pattern matches
    - Convert to mid-level intermediate representation (MIR)
- [CIrGen](MiloneLang/CIrGen.fs)
    - Generate C code
- [CPrinting](MiloneLang/CPrinting.fs)
    - C code to string

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

- `features`: Testing of language features
- `functions`: Testing of primitives
- `errors`: Testing of compile errors
- `examples`: Complex codes
- `pendings`: Incomplete test cases
