# Development Environment

This explains how to set up an environment to develop the milone-lang compiler.

Remark: Scripts are written for `bash` because I use a Ubuntu desktop.

### Prerequisites

See also the "install" section in [README](../../README.md) in the root.

- Install Git 2.30.0
- Install GNU make
- Install [ninja 1.10.2](https://github.com/ninja-build/ninja) (build tool)
    with `scripts/install-ninja`

Reasons:

- `git` command is used in tests to generate diff.
- `make` command is used to incremental building and wrapper of ninja.
- `ninja` command is used for incremental building and testing.

### Build

```sh
make
```

See also [Makefile](../../Makefile) in the root.

### Dev: Testing

```
    tests/*/X/X.fs
        ↓ compile with milone-lang compiler
    tests/*/X/X.c       → snapshot test
        ↓ compile with C compiler
    tests/*/X/X.exe
        ↓ execute
    tests/*/X/X.output  → integration test
```

The `tests` directory contains projects for testing. Testing consist of two phases.

First, snapshot testing: each test project (at `tests/*/X`) is compiled with milone-lang compiler to C file. C files are committed to Git and you can assume they are verified before commit. OK if unchanged. Otherwise, the project proceeds to the next phase to verify the modified output.

Second, integration testing: each test project is compiled with GCC and executed. The standard output and exit code is written to `tests/*/X/X.generated.output`. The expected result is stored in `tests/*/X/X.output`, which is committed. OK if the two files are same. Otherwise, something wrong. Debug it.

In addition, self compilation is also a kind of testing. The milone-lang compiler (on .NET) compiles the compiler itself (obtaining first C code) and the output compiler also compiles the compiler itself (obtaining second C code). OK if the generated two C codes are same, and the generated compiler passes the all tests described above.

In tests, there are some categories of test cases:

- `features`: Tests for language features
- `primitives`: Tests for primitive operators, functions, and types
- `examples`: (should be) meaningful codes
- `edges`: Tests for exotic cases
- `errors`: Tests of compile errors
- `pendings`: Test cases pointing out flaw of the compiler

### Notes on Formatting Code

TODO: explain more

Check current fantomas version used in [ionide-vscode-fsharp](https://github.com/ionide/ionide-vscode-fsharp/blob/master/RELEASE_NOTES.md).
See also [FsAutoComplete/RELEASE_NOTES.md](https://github.com/fsharp/FsAutoComplete/blob/master/RELEASE_NOTES.md).

Install [fantomas](https://github.com/fsprojects/fantomas).

```sh
# Restore fantomas. (See also `.config/dotnet-tools.json`.)
dotnet tool restore

# Execute for each F# file. Since fantomas crashes on error, avoid using --recursive mode.
find -type f \
    -name '*.fs' \
    -not \( \
        -path '*/bin/Debug/*' \
        -or -path '*/bin/Release/*' \
        -or -path '*/obj/Debug/*' \
        -or -path '*/obj/Release/*' \) | \
    xargs -I{} -P4 dotnet fantomas {}

# Execute for each milone file. Use temporary file since fantomas doesn't allow non-F# file extensions.
find -type f -name '*.milone' | \
    xargs -I{} -P4 sh -c 'cp -f {} {}_.fs; dotnet fantomas {}_.fs; if test $? -eq 0; then cat {}_.fs >{}; fi; rm -f {}_.fs'
```

- See also [F# code formatting guidelines | Microsoft Docs](https://docs.microsoft.com/en-us/dotnet/fsharp/style-guide/formatting#formatting-expressions).

----

## Less Interesting

### Deployment - Tag and Pack

- Make sure the develop branch is working
- Update version number written in source
- Merge to the main branch

```sh
# Make Git tag.
git tag v0.0.0
git push --tags

# Create package.
make pack
```

- Make a release in GitHub
    - Add the package to the release
    - Build a package on Windows and add it to the release
