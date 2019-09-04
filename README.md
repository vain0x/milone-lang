# MILONE-LANG

[![Build Status](https://travis-ci.org/vain0x/milone-lang.svg?branch=master)](https://travis-ci.org/vain0x/milone-lang)

## What

**Milone-lang** is a F#-subset programming language.

The goal is **[self-hosting](https://en.wikipedia.org/wiki/Self-hosting)**., i.e. to make a milone-lang compiler that can compile milone-lang compiler itself.

This is a hobby project. Don't use in production. Pull requests and issues are welcome.

## (No) Getting Started

No releases available due to quality. To use, see the Development section.

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

*The actual output is available at [factorial.c](./boot/tests/examples/factorial/factorial.c).*

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

## Project Status

Most (~70%) of features required for self-hosting have been implemented. For example, the compiler can tokenize the tokenizer itself.

See [the self branch](https://github.com/vain0x/milone-lang/tree/self/boot/tests/examples/MiloneLang) for the progress of self-hosting.

## Features

Not all of F# features are supported. Features for functional-style programming are selected to write a compiler easily.

- Compile a CLI application (no libraries)
- Expressions
    - Literals: `1`, `"str"`, etc.
    - Operations: `+`, `::`, etc.
    - Function applications: `f x y` and `y |> f x`
    - Function abstractions: `let f x y = ..` and `fun x y -> ..`
    - Pattern matching
- Functions
    - Mutually recursion
    - Local variable capturing
    - Partial applications
    - Function objects
- Types
    - Type inference based on Hindley-Milner algorithm
    - Primitive types: `int`, `char`, `string`, tuples, lists, functions
    - Discriminated unions (non-generic ones only)
- IO
    - `printfn` with `%s`, `%d`
    - Some file IOs

See [the boot/tests/examples directory](./boot/tests/examples) for working codes.

## Internals

See the comments in source files for details. Most of types are defined in the module:

- [Types](boot/MiloneLang/Types.fs)

Functions are defined in:

- [Polyfills](boot/MiloneLang/Polyfill.fs)
    - Abstraction layer to reduce the gap of F# and milone-lang
- [Helpers](boot/MiloneLang/Helpers.fs)

The following transformations are consist of the compilation in the order:

- [Lexing](boot/MiloneLang/Lexing.fs) (Tokenization)
- [Parsing](boot/MiloneLang/Parsing.fs)
- [Bundling](boot/MiloneLang/Bundling.fs)
    - Source codes concatenation
- [AstToHir](boot/MiloneLang/AstToHir.fs)
    - From abstract syntax tree (AST) to high-level intermediate representation (HIR)
    - For data structure decoupling and desugaring
- [NameRes](boot/MiloneLang/NameRes.fs) (Name resolution)
- [Typing](boot/MiloneLang/Typing.fs) (Type inference)
- [FunTrans](boot/MiloneLang/FunTrans.fs) (Function transformations)
    - Main hoisting:
        - Resolve top-level bindings
    - Declosure (closure conversion):
        - Resolve use of local variables in functions
    - Uneta:
        - Resolve partial applications
- [Hoist](boot/MiloneLang/Hoist.fs)
    - Just a preparation of monomorphization
- [Monomorphization](boot/MiloneLang/Monomorphization.fs)
    - Resolve generic functions by code clone
- [Mir](boot/MiloneLang/Mir.fs)
    - Resolve pattern matches
    - Convert to mid-level intermediate representation (MIR)
- [CIrGen](boot/MiloneLang/CIrGen.fs)
    - Generate C code
- [CPrinting](boot/MiloneLang/CPrinting.fs)
    - C code to string

## Development

### Dev: Prerequisites

- Install .NET Core SDK [2.1 LTS](https://dotnet.microsoft.com/download/dotnet-core/2.1)
- Install [F#](http://ionide.io/#requirements) 4.1 tools

### Dev: Tasks

[task](./boot/task) provides a set of testing scripts. Run in the `boot` directory.

- It's written for `bash` because I'm using a Ubuntu desktop for development. It might work on Windows Subsystem Linux or macOs (not tried).

To execute integration tests, run `./task integ-all`.

### Dev: Testing

The `tests` directory contains files for testing.

`dotnet test` performs unit testing. All `tests/*/X/X.fs` files are compiled to matching `tests/*/X/X.c`. The outputs have verified before commit, so it's OK if none of them changed. If an output is changed, you need to perform integration testing to verify.

`./task integ-all` performs integration testing. Each `tests/*/X/X.fs` file is compiled to an executable using GCC and executed. It is verified by matching the stdout and exit code with `tests/*/X/X.out`.

There are some categories of testing files:

- `features`: Testing of language features
- `functions`: Testing of primitives
- `errors`: Testing of compile errors
- `examples`: Complex codes
- `pendings`: Incomplete test cases
