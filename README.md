# MILONE-LANG

**Milone-lang** is a F#-subset programming language.

The initial goal was **[self-hosting](https://en.wikipedia.org/wiki/Self-hosting)**, i.e. to develop a milone-lang compiler that can compile the compiler itself. It was achieved at [v0.1.0](https://github.com/vain0x/milone-lang/tree/v0.1.0).

Currently, working toward initial release (v0.2.0).

This is a hobby project. Don't use in production. Pull requests and issues etc. are welcome.

## Index

- [Install](#install)
- [Documentation](./docs/refs/)
- [Examples](./tests/examples)

## Install

(Installation from binary or via package manager is not available yet.)

### Install from sources

Prerequisites:

- Ubuntu 18.04 (or similar platform)
- Install [.NET SDK 5.0.101](https://dotnet.microsoft.com/download/dotnet/5.0)
- Install GCC 7.5.0 (Note: This is old, current latest version is 10.)

Do:

```sh
# Download the source codes. (Or `git clone 'https://github.com/vain0x/milone-lang'`.)
curl -L 'https://github.com/vain0x/milone-lang/archive/master.zip' | \
    busybox unzip -q - && \
    mv milone-lang-master milone-lang

# Build and install.
cd milone-lang
./install
```

- Feel free to ask anything in [discussion](https://github.com/vain0x/milone-lang/discussions/4).
- To uninstall, run `scripts/uninstall`.

### Other platforms (Windows/macOS)

Installation script is not available yet.

So you need run commands by hand.
See [./install](./install) for details.
(The milone-lang compiler should work on these platforms since .NET and C language are cross-platform.
The milone-lang compiler emits C11-compliant codes and the [runtime codes](runtime/milone.c) are C11-compliant.)

## How to build a test project

TODO: Write in docs and include in test chain.

These commands build [tests/examples/hello_world](./tests/examples/hello_world) project.

```sh
# Compile to C.
milone compile tests/examples/hello_world >hello.c

# Build C. You need to specify runtime directory and link runtime codes.
gcc -std=c11 \
    -O2 \
    -I $HOME/.milone/runtime \
    $HOME/.milone/runtime/milone.c \
    hello.c \
    -o hello

# Execute.
./hello
```

## Install VSCode Extension

See [./vscode_ext](./vscode_ext)

----

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

See also:

- [the tests/examples directory](./tests/examples) for working codes
- [the docs/refs directory](./docs/refs/) for detailed references

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

See the "install from sources" section above.

For incremental building and testing, `ninja` command is also used.
`git` command is used in tests to generate diff.

- Install Git 2.30.0
- Install [ninja 1.10.2](https://github.com/ninja-build/ninja) (build tool)

### Dev: Build

Generate a build script for ninja and then run ninja command.

```sh
./build-ninja-gen && ninja
```

### Dev: Testing

```
    tests/*/X/X.fs
        ↓ compile with milone-lang compiler
    tests/*/X/X.c       → snapshot test
        ↓ compile with C compiler
    tests/*/X/X.exe
        ↓ execute
    tests/*/X/X.out     → integration test
```

The `tests` directory contains projects for testing. Testing consist of two phases.

First, snapshot testing: each test project (at `tests/*/X`) is compiled with milone-lang compiler to C file. C files are committed to Git and you can assume they are verified before commit. OK if unchanged. Otherwise, the project proceeds to the next phase to verify the modified output.

Second, integration testing: each test project is compiled with GCC and executed. The standard output and exit code is written to `tests/*/X/X.generated.out`. The expected result is stored in `tests/*/X/X.out`, which is committed. OK if the two files are same. Otherwise, something wrong. Debug it.

In addition, self compilation is also a kind of testing. The milone-lang compiler (on .NET) compiles the compiler itself (obtaining first C code) and the output compiler also compiles the compiler itself (obtaining second C code). OK if the generated two C codes are same, and the generated compiler passes the all tests described above.

In tests, there are some categories of test cases:

- `features`: Tests for language features
- `primitives`: Tests for primitive operators, functions, and types
- `examples`: (should be) meaningful codes
- `edges`: Tests for exotic cases
- `errors`: Tests of compile errors
- `pendings`: Test cases pointing out flaw of the compiler

### Dev: See also

- [TODO list](https://github.com/vain0x/milone-lang/projects/1): TODO list. Feel free to clarify by opening an issue.
- [notes.md](notes.md): Notes on future works.
- [milone_libs](./milone_libs): Standard library for milone-lang.
    - [MiloneCore](./milone_libs/MiloneCore): Core library that is a subset of F# with compatible behavior.
    - [MiloneStd](./milone_libs/MiloneStd): Standard library for milone-lang, not compatible with F#.
