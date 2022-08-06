# The Milone Language

The *Milone* language is an F#-subset programming language. This is all-in-one repository.

```fsharp
let rec factorial n =
  if n = 0 then
    1
  else
    n * factorial (n - 1)

printfn "5! = %d" (factorial 5) //=> 120
```

## Table of Contents

- [#About](#about)
- [#Install](#install)
    - ~~With package manager~~ (yet)
    - [#From sources on Linux](#install-from-sources-on-linux)
    - [#From binary package on Windows](#install-from-binary-package-on-windows)
- [#How it works](#how-it-works)
- Documentation
    - Language -> [docs/refs](docs/refs)
    - CLI -> [docs/cli.md](docs/cli.md)
- Examples
    - [tests/examples](tests/examples)
    - Compiler itself -> [src/MiloneCliCore/Cli.fs](src/MiloneCliCore/Cli.fs)
- Libraries
    - Built-in library -> [src/MiloneCore](src/MiloneCore)
    - Standard library -> [src/Std](src/Std)
- Tools
    - VSCode extension -> [vscode_ext](vscode_ext)
- Internals -> [docs/internals](docs/internals)

## About

*History*:
The author started this project in 2018 just for fun. Initial goal was making a compiler that can compile itself (that is, **[self-hosting](https://en.wikipedia.org/wiki/Self-hosting)**). It was achieved at [v0.1.0](https://github.com/vain0x/milone-lang/tree/v0.1.0) in 2019.

*Status*: Currently this project is being developed for v1.0 release.

*Disclaimer*:
This is a hobby project. Don't use in production.

## Install

### Install from Sources on Linux

Prerequisites:

- Ubuntu 20.04 (or similar)
- Install [.NET SDK 6](https://dotnet.microsoft.com/download/dotnet/6.0)
- Install GNU make 4.2.1
- Install GCC 9.4.0

Do:

```sh
# Download
git clone 'https://github.com/vain0x/milone-lang' --filter=blob:none

# Build and install.
cd milone-lang
make install
```

- To uninstall, do `make uninstall`.

### Install from Binary Package on Windows

Prerequisites:

- Windows 10
- Install [Visual Studio 2022 Build Tools](https://visualstudio.microsoft.com/ja/downloads/?q=build+tools#build-tools-for-visual-studio-2022)

Instructions:

- Download a binary package from [GitHub Releases](https://github.com/vain0x/milone-lang/releases)
- Unarchive it
- Follow instructions written in [INSTALL.md](src/MyBuildTool/assets/INSTALL.md)

See [docs/binary_package.md](docs/binary_package.md) for more details.

## How It Works

Currently the target language is C. That is, the milone-lang compiler reads a source code and translates to a C code. For example, assume the following code is given.

```fsharp
let main _ =
  let rec factorial x =
    if x = 0 then 1 else x * factorial (x - 1)
  factorial 5 - 120 // exit code
```

The compiler emits a C code that is equivalent to the following:

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

The diagram below illustrates how it does self-hosting.

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

## Contribute

Issues and pull requests are welcome.
Feel free to ask in [discussions](https://github.com/vain0x/milone-lang/discussions/4), twitter or something.

## License

Milone-lang tools (compiler and LSP server) are distributed under either:

- the Apache 2.0 license, or
- the MIT license.

Others including documentation, examples, standard libraries, runtime code, scripts, tests, etc. are distributed under [CC0-1.0](https://creativecommons.org/publicdomain/zero/1.0/).
