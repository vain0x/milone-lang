# milone-lang

`milone-lang` is an F#-subset programming language.

- [About](#about)
- [Install](#install)
- [Documentation](docs/refs/)
- [Examples](tests/examples)
- [Internals](internals.md)

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
