# milone-lang

`milone-lang` is an F#-subset programming language.

- [#About](#about)
- [#Install](#install)
    - ~~With package manager~~ (yet)
    - [#From sources on Linux](#install-from-sources-on-linux)
    - [#From sources on Windows](#install-from-sources-on-windows)
- [#How it works](#how-it-works)
- Documentation
    - Language -> [docs/refs](docs/refs)
    - CLI -> [docs/cli.md](docs/cli.md)
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
- Install GNU make
- Install GCC 7.5.0
- Install `busybox`, which is likely pre-installed, by:
    `apt install -y busybox-static`

Do:

```sh
# Download the source code.
git clone 'https://github.com/vain0x/milone-lang' --filter=blob:none

# Build and install.
cd milone-lang
make install
```

- To uninstall, do `make uninstall`.

### Install from binary package on Windows

Prerequisites:

- Windows 10
- Install `MSBuild.exe` in some way:
    - install Visual Studio 2019 with "Desktop development with C++" option, *OR*
    - install [Visual Studio 2019 Build Tools](https://visualstudio.microsoft.com/ja/downloads/?q=build+tools#build-tools-for-visual-studio-2019).

Instructions:

- Download a binary package from [GitHub Releases](https://github.com/vain0x/milone-lang/releases)
- Unarchive it somewhere
- Follow instructions written in [INSTALL.md](scripts/MyBuildTool/assets/INSTALL.md)

See also [docs/binary_package.md](docs/binary_package.md).

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

Others including documentation, examples, libraries, runtime code, scripts, tests, etc. are distributed under [CC0-1.0](https://creativecommons.org/publicdomain/zero/1.0/).
