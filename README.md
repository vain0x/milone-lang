# milone-lang

`milone-lang` is an F#-subset programming language.

- [#About](#about)
- [#Install](#install)
    - ~~With package manager~~ (yet)
    - From binary -> [install_from_binary.md](install_from_binary.md)
    - [#From sources on Linux](#install-from-sources-on-linux)
    - [#From sources on Windows](#install-from-sources-on-windows)
- [#How it works](#how-it-works)
- Documentation -> [docs/refs](docs/refs)
- Examples -> [examples](examples)
- Internals -> [internals.md](internals.md)

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

### Install from sources on Linux

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

### Install from sources on Windows

Prerequisites:

- Windows 10
- Install [Git for Windows](https://gitforwindows.org/)
- Install [.NET SDK 5](https://dotnet.microsoft.com/download/dotnet/5.0)
- Install [Visual Studio 2019](https://visualstudio.microsoft.com/ja/downloads/) with "Desktop development with C++" option

Do with Git Bash:

```sh
# Download the source code.
git clone 'https://github.com/vain0x/milone-lang' --filter=blob:none
cd milone-lang

# ---- BUILD ----

# Build milone-lang compiler to C code.
mkdir -p target/gen2
MILONE_HOME=$PWD dotnet run -p MiloneLang --target-dir target/gen2 -- compile MiloneLang

# HACK: MSVC seems to not handle minimum int literal. Replace them with hex notation.
sed -i 's/-2147483648/0x80000000/' target/gen2/MiloneLang.c

# Build for executable.
# Remark: MSBuild.exe is not in PATH by default.
#         If you don't know what to do about this,
#         just open the solution with Visual Studio to build instead.
MSBuild.exe 'scripts/milone-lang-win10-msvc/milone-lang-win10-msvc.sln' '-p:Configuration=Release;Platform=x64'

# ---- INSTALL ----

# Copy the generated executable to some directory as you want.
mkdir -p $USERPROFILE/bin
cp 'scripts/milone-lang-win10-msvc/target/64-Release-bin/milone.exe' $USERPROFILE/bin

# Create '.milone' directory in user directory.
# Copy libraries to it.
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

## License

Milone-lang tools (compiler and LSP server) are distributed under either:

- the Apache 2.0 license, or
- the MIT license.

Others including documentation, examples, libraries, runtime code, scripts, tests, etc. are distributed under CC0-1.0.
