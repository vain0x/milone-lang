# The Milone Language

The Milone language is an F#-subset programming language. This is all-in-one repository.

```fsharp
let rec factorial n =
  if n = 0 then
    1
  else
    n * factorial (n - 1)

printfn "5! = %d" (factorial 5)
```

```
5! = 120
```

---

## Table of Contents

- [#About](#about)
- [#Install](#install)
    - ~~With package manager~~ (yet)
    - [#From sources on Linux](#install-from-sources-on-linux)
    - [#From binary package on Windows](#install-from-binary-package-on-windows)
- ~~Getting Started~~ (yet)
- References:
    - Language -> [docs/refs](docs/refs)
    - CLI -> [docs/cli.md](docs/cli.md)
- Reading:
    - [C as Backend](docs/articles/c_as_backend.md)
    - Examples -> [tests/examples](tests/examples)
    - Internals -> [docs/internals](docs/internals)
- Implementation:
    - Compiler -> [src/MiloneCli/Cli.fs](src/MiloneCli/Cli.fs)
    - LSP Server -> [src/MiloneLspServer/Program.fs](src/MiloneLspServer/Program.fs)
    - Built-In Library -> [src/MiloneCore](src/MiloneCore)
    - Standard Library -> [src/Std](src/Std)
    - VSCode Extension -> [vscode_ext](vscode_ext)

## About

**History**:
The author started this project in 2018 just for fun. Initial goal was making a compiler that can compile itself (that is, **[self-hosting](https://en.wikipedia.org/wiki/Self-hosting)**). It was achieved at [v0.1.0](https://github.com/vain0x/milone-lang/tree/v0.1.0) in 2019.

**Status**: Currently this project is being developed for v1.0 release.

**Disclaimer**: This is a hobby project. Don't use in production.

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

## Contribute

Issues and pull requests are welcome.
Feel free to ask in [discussions](https://github.com/vain0x/milone-lang/discussions/4), twitter or something.

## License

Milone-lang tools (compiler and LSP server) are distributed under either:

- the Apache 2.0 license, or
- the MIT license.

Others including documentation, examples, standard libraries, runtime code, scripts, tests, etc. are distributed under [CC0-1.0](https://creativecommons.org/publicdomain/zero/1.0/).
