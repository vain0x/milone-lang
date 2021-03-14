# milone-lang

`milone-lang` is an F#-subset programming language.

- [About](#about)
- [Install](#install)
- [Documentation](docs/refs/)
- [Examples](tests/examples)

## About

*History*:
The initial goal of the project was **[self-hosting](https://en.wikipedia.org/wiki/Self-hosting)**.
That is, I just wanted to write a compiler that can compile the compiler itself.
I achieved the goal at [v0.1.0](https://github.com/vain0x/milone-lang/tree/v0.1.0).

*Current*:
I'm working toward initial release.

*Remarks*:
This is a hobby project.
Don't use in production.
Issues and pull requests are welcome.
Feel free to ask anything in [discussions](https://github.com/vain0x/milone-lang/discussions/4) or something.

## Install

- ~~With package manager~~ (yet)
- [From binary](#install-from-binary)
- [From sources](#install-from-sources)

### Install from binary

Download pre-release binary packages from [Releases](https://github.com/vain0x/milone-lang/releases).

### Install from sources (Linux)

Prerequisites:

- Ubuntu 18.04 (or similar platform)
- Install [.NET SDK 5](https://dotnet.microsoft.com/download/dotnet/5.0)
- Install some C11-compliant C compiler, typically either:
    - GCC 7, or
    - Clang 6

Do:

```sh
# Download the source code.
git clone 'https://github.com/vain0x/milone-lang' --filter=blob:none

# Build and install.
cd milone-lang
scripts/install
```

- To uninstall, do `scripts/uninstall`.

### Install from sources (Windows)

Prerequisites:

- Windows 10
- Intall Git for Windows
- Install [.NET SDK 5](https://dotnet.microsoft.com/download/dotnet/5.0)
- Install Visual Studio 2019 with "Desktop development with C++" enabled
- Put MSBuild.exe in PATH

Do with Git Bash:

```sh
# Download the source code.
git clone 'https://github.com/vain0x/milone-lang' --filter=blob:none

# Build.
scripts/build-milone-windows

# Put executable to some directory as you want.
mkdir -p $USERPROFILE/bin
cp 'scripts/milone-lang-win10-msvc/target/64-Release-bin/milone.exe' $USERPROFILE/bin

# Copy libraries to '.milone' in user directory.
mkdir -p $USERPROFILE/.milone
cp milone_libs $USERPROFILE/.milone
```

## How to build a test project

TODO: Write in docs and include in test chain.

These commands build [tests/examples/hello_world](tests/examples/hello_world) project.

```sh
# Compile to C code.
milone compile tests/examples/hello_world >hello.c

# Build C code with C compiler.
# You need to specify include directory (-I)
# and compile runtime code.
gcc -std=c11 \
    -I$HOME/.milone/runtime \
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

*The actual output is available at [factorial.c](tests/examples/factorial/factorial.c).*

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
    - Literals: `42`, `3.14`, `"str"`, `"""raw str"""`
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
    - Primitive types: int, float, string, tuples, lists, functions, etc.
    - Discriminated unions (non-generic ones only)
    - Records (non-generic ones only)
- IO
    - `printfn` (`%s`, `%d`, `%f` only)

See also:

- [the docs/refs directory](docs/refs/) for detailed explanation
- [the tests/examples directory](tests/examples) for working codes
- [the examples directory](examples) for more practical codes

## Architecture

See comments written at the top of each file.

Utilities:

- [Util](MiloneLang/Util.fs)
    - Utility functions for string, list etc.

Domains (types and functions):

- [Syntax](MiloneLang/Syntax.fs)
    - Tokens, abstract syntax tree (AST), source location information etc.
- [Hir](MiloneLang/Hir.fs):
    - Functional-style intermediate representation
- [Mir](MiloneLang/Mir.fs):
    - Imperative-style intermediate representation
- [Cir](MiloneLang/Cir.fs)
    - AST of the C code to be pretty printed

Program analysis:

- [SyntaxTokenize](MiloneLang/SyntaxTokenize.fs) (milone-lang source code -> Token list)
- [SyntaxParse](MiloneLang/SyntaxParse.fs) (Token list -> AST)
- [AstToHir](MiloneLang/AstToHir.fs) (AST -> HIR)
- [AstBundle](MiloneLang/AstBundle.fs) (\*files\* -> HIR)
    - Loads source files of project and concatenates them into single HIR program
- [NameRes](MiloneLang/NameRes.fs) (Name resolution) (HIR)
- [Typing](MiloneLang/Typing.fs) (Type inference) (HIR)

Transformations:

- [MainHoist](MiloneLang/MainHoist.fs) (HIR)
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
    - .NET entrypoint
- [MiloneLang.milone](MiloneLang/MiloneLang.milone)
    - milone-lang entrypoint

Language-specific parts:

- [FSharpOnly](MiloneLang/FSharpOnly.fs)
- [MiloneOnly](MiloneLang/MiloneOnly.milone)

## Development

Scripts are written for `bash` because I use a Ubuntu desktop for development.

### Dev: Prerequisites

See the "install from sources" section above.

For incremental building and testing, `ninja` command is also used.

`git` command is used in tests to generate diff.

- Install Git 2.30.0
- Install [ninja 1.10.2](https://github.com/ninja-build/ninja) (build tool)
    with `scripts/install-ninja`

### Dev: Build

```sh
# If you have make:
make

# Otherwise:
scripts/build-ninja-gen
bin/ninja
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

- [TODO list](https://github.com/vain0x/milone-lang/projects/1)
- [notes.md](notes.md): Notes on future works.
- [milone_libs](milone_libs): Standard library for milone-lang.
    - [MiloneCore](milone_libs/MiloneCore): Core library that is a subset of F# with compatible behavior.
    - [MiloneStd](milone_libs/MiloneStd): Standard library for milone-lang, not compatible with F#.
- [nursery](nursery): Experimental projects written in milone-lang
