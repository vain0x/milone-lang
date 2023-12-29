# Changelog

> [Keep a Changelog](https://keepachangelog.com/)

## [Unreleased]

[Unreleased]: https://github.com/vain0x/milone-lang/compare/v0.6.0...develop

### CLI Tools

- (*Windows*) `milone` command now generates VS2022 project files to build C code.

### LSP Server

- Parse results are now memoized
- Some refactoring

### Internal Changes

Compiler:

- Type synonym expansions is now faster
- Preparations for workspaces:
    - Multiple `main` functions are now allowed
    - (*Windows*) MSBuild backend supports multi-projects

Others:

- Use `--allsig` options in F# projects (to reduce compilation time)
- Add `scripts/prof` and `docs/internals/profiling.md`
- Fix build/pack scripts

## [v0.6.0] - 2023-02-15

[v0.6.0]: https://github.com/vain0x/milone-lang/releases/tag/v0.6.0

### Documentation

- Clarify limitation of `__nativeDecl` arguments
- Add explanation of generic nominal types
- Add type synonyms page

### Language Features

- Support generic records
- Fix type check bugs
- Fix unicode string literals broken
- Add `never` type
- Add primitives:
    - Add byte literals (`'a'B` syntax)
    - Add bitwise negation operator (`~~~`)
- Improve for native interop (still incomplete):
    - Add `FunPtr<P, T>` (from `Std.Ptr`), type of function pointers (replacing experimental `__nativeFun` type)
    - Add `FunPtr.invoke` primitive (from `Std.Ptr`) to invoke a function pointer
    - Add Ptr-of operator (`&&`) to obtain pointers of named functions (replacing experimental `__nativeFun funName` syntax)
    - Add `Opaque` types
    - Add `Export` attribute on functions (to preserve the function name to link time)
- Improve manifest:
    - Add directives to specify output binary type in manifest
        - `binary shared` (`*.so`, `*.dll`)
        - `binary staticlib` (`*.a`, `*.lib`)
    - Add `subsystem windows` directive (only on Windows)

### Standard Libraries

- Add `Std.CStr`, `Std.CMemory` modules for native interop
- Add `Std.StringBuffer` module
- Remake `Std.File`

### CLI Tool

- Add `milone parse` subcommand
- Fix `milone run .` that didn't work

### LSP Server

- Support `prepareRename` request (the editor can now reject at invalid position)
- Support `completion` of static namespace members and record fields
- Fix `diagnostics` are too frequently updated
- Fix the server tries to continue after out of memory
- Fix the server didn't do almost anything if type errors present

### VSCode Extension

- Add `Show Syntax Tree` command
- Support double-backticks (\`\`) as brackets

### Build Chain

- Change default install directories (to match match XDG):
    - `$HOME/.local/bin` (rather than `$HOME/bin`)
    - `$HOME/.local/share` (rather than `$HOME/.milone`)

### Internal Changes

Compiler:

- Change project structure to revert separation of types and implementation projects (lack of benefits)
- Transfer module load process to clients (CLI tool and LSP server)
- Improve separate compilation by generating label names per function
- Add SyntaxTree generation
- Allow `DocId` representation to vary in clients
    - Compiler still uses `P.M` module paths. LSP server now uses absolute file paths to avoid conflict.
- Change `exit` to a regular function in Prelude

Standard Libraries:

- Add `Std/FormatBase.milone` as wrapper of `sprintf`-like code
    - (It isn't a public interface of Std but no way to express such privacy)

Nursery:

- Add LibPoda

## [v0.5.0] - 2022-07-21

[v0.5.0]: https://github.com/vain0x/milone-lang/releases/tag/v0.5.0

### Documentation

- Rewrite README
- Update ARCHITECTURE
- Add Glossary
- Add documentation for:
    - Syntax
    - Name resolution (incomplete)
    - Arity check
    - AST bundle
- Add design policy
- Add developer notes

### Language Features

- Improve syntax:
    - Support hex escape in quotes
    - Support integer suffix
    - Parse `fun` expressions in arguments better
    - More strict syntax for `<` token (space-sensitive)
    - Fix precedence of binary operators for compatibility with F#
    - Unreserve some of keywords as [unreserved in F# 4.1](https://github.com/fsharp/fslang-design/blob/96ad0254c156473372ab089ac36f5dd54a783ada/FSharp-4.1/FS-1016-unreserve-keywords.md)
- Improve type checks:
    - Fix lots of incorrect type checks
    - No longer nested functions are generic
    - No longer type variables are unified with particular types (unlike `_` types are)
    - Resolve trait bounds before generalization as possible
    - Support equality for built-in types: list, option, tuple and discriminated union
        - (Note `open Std.Equal` is required to enable this feature.)
    - `unit` is comparable now
    - `char` is now convertible only from/to 8-bit integers to avoid incompatibility with F# (**EDIT**: Reverted in 0.6.0)
    - `option` is defined as a discriminated union now (which is still built-in type, almost non-functional change)
    - `Result` is a new built-in type (which is also defined as a discriminated union)
- Improve transformation:
    - Small generic unions can now be unboxed
- Improve code generation:
    - Use `int32_t` type from C for `int` type
        - Same for `uint`
    - Top-level expressions are generated in C file of that module (rather than collected into single module)
    - Fix an issue of `__nativeType` containing spaces
    - Emit a directive to include `<milone.h>` (rather than `"milone.h"`) to search system directories
    - Emit `__nativeDecl` in more suitable order
    - Emit verbose, context-preserving symbol names for more stable compilation outputs
    - Inline `if` statement in use-site of `assert`
    - Change name of Cons struct to `FooCons` (rather than `FooList`)
    - Change style of pointer-type to `T *` (rather than `T*`)
    - Generate `typedef` for function pointer types to fix invalid code generation issues
- Support **ownership** for better expressiveness
    - Add `Own` module
        - `Own<'T>` type
        - `acquire`, `release` primitives
    - Support ownership check
    - Add several standard libraries built on top of it
- Support more **pointer** types and primitives
    - Add  `OutPtr<'T>` and `VoidInPtr<'T>` types
    - Change `__constptr<'T>` to `InPtr<'T>`
    - Add ptr-of (`&&`) operator
    - Add `Ptr` module
        - `select`, `read`, `write`
        - `nullPtr`, `invalid`
        - `cast`, `asIn`, `asNative`
        - `distance`
- Improve primitives:
    - Fix an issue that `string : bool -> string` didn't work at all
    - `string` now works for tuples and unions (result is unstable)
    - Add `__discriminant`
    - Add `sizeof<'T>`, remove `__sizeOfVal` primitive in favor of this
    - Rename `inRegion` to `Region.run`
    - `__nativeExpr` etc. can now embed some expressions and types
- Support provisional manifest files (`milone_manifest`)

### Runtime Library

- Reduce headers included in `milone.h`
- Heaps are now stored in thread-local variables (rather than static)
- Rename most of functions
- Prefer `uint32_t` for size/length/capacity (over `int`) (**EDIT**: Reverted in 0.6.0)

### Standard Libraries

- Rename to `Std` (from `MiloneStd`)
- Add modules:
    - `StdAssoc`
    - `StdError`
    - `StdIter`
    - `StdJson`
    - `StdList`
    - `StdLoop`
    - `StdMultimap`
    - `StdNativeInterop`
    - `StdOption`
    - `StdPair`
    - `StdResult`
    - `StdTesting`
    - `Own`
    - `Ptr`
    - `Region`
    - `IO`, `File`, `Path`, `OsString`
    - `Vector`, `ByteVector`, `Block`, `Box`, `HashMap`
    - `StringBuffer`
- Add functions:
    - `Option.fold`
    - `List.takeWhile`
    - `StdChar`
        - `evalDigit`, `evalHex`
    - `StdString`
        - `cut`, `cutLast`
        - `format`
        - `toLower`, `toUpper`
        - `lowerFirst`, `upperFirst`
        - `split`, `splitAt`
        - `stripStart`, `stripEnd`
        - `parseHexAsUInt64`, `uint64ToHex`
        - `StringExt`
            - `asPtr`, etc.
- Change `StdMap.TreeMap` to a generic union (from a synonym)
- Fix an issue that `StdString.cutLine` and `toLines` aren't binary-safe

### CLI Tool

- Add `milone eval` subcommand
- `milone` now defines `NDEBUG` macro on release build as convention of C compilation
- Outputs of runtime library are now written in the target directory (rather than source directory of runtime library)

### LSP Server

- Support find references for more kinds of symbols: variants, fields, types and modules
- Support `textDocument/documentSymbol`
- Support `textDocument/completion`
    - module names in open/module declarations
    - local values
- Support `textDocument/codeAction`
    - "Generate module head"
    - "Generate module synonym"
    - "Generate open"
- Support `textDocument/formatting` (by spawning `fantomas`, an F# formatter)
- Improve ranges of diagnostics
- Improve error handling, report failed requests
- Detect projects created after starting a server
- Fix an issue that sever doesn't work on Windows due to Windows-style pathnames

### VSCode Extension

- Rewrite syntax definition for better highlights
- Run LSP server with limited heap size to workaround out-of-memory issue

### Build Chain

- Migrate to .NET 6 (from .NET 5)
- No longer require `busybox`
- Installation script for Linux now requires `curl` and automatically downloads `ninja` binary

### Internal Changes

Compiler:

- Change directory structure
    - Source files are in `src` directory, including scripts and runtime library
    - Projects for types and functions are separated for less dependencies
- No longer support `MiloneOnly` modules
- `DocId`s are interned as Symbol
- Passes run per module as possible
- Move works about type check from name resolution to the Typing module
- Redesign name resolution, introduce IR for name resolution (NIR)
- Map of non-static variables are split into modules
- HIR no longer has visibility of symbols and `rec` modifiers
- Rewrite monomorphization algorithm for more efficiency
- Change parameter order
    - `S -> T -> S` for fold
    - `S -> T -> T * S` for map-fold
- Remove intermediate type information from MIR expressions

LSP server:

- Use fixed-sized intermediate buffer for simplicity
- Rewrite concurrent part for better cancellation supports
- Decouple from .NET and side-effect functions for tests and porting to milone-lang
- Add tests a bit

Nursery:

- `nursery/CmdLspServer` project has started (not working though)
- `nursery/ExDyLib` as experiment of interop with Rust

Suspended works:

- Fixing type check of recursive functions (difficult)
- Compiling pattern matching in better way (difficult)
- Designing SSA-style IR (difficult)
- Serializing (caching) compilation results (Writing in JSON makes too large outputs. It needs to switch to an appropriate binary format.)
- Adding `clone` primitive for lower memory usage peak (less priority)
- Improving test scripts (less priority)

## [v0.4.0] - 2021-10-08

[v0.4.0]: https://github.com/vain0x/milone-lang/releases/tag/v0.4.0

- Added two subcommands `build` and `run` to use milone programs more easily.
- Implemented generic discriminated union types.
- Fixed many issues about typing etc.
- Updated many things.

## [v0.3.0] - 2021-03-14

[v0.3.0]: https://github.com/vain0x/milone-lang/releases/tag/v0.3.0

- Added optimization to unwrap newtype variants.
- Improved mechanism of projects and modules.
- Fixed the issue that generated code was not C11-compliant.

## [v0.2.0] - 2021-02-12

[v0.2.0]: https://github.com/vain0x/milone-lang/releases/tag/v0.2.0

- Improved error reporting, compiler's stability and performance.

## [v0.1.1] - 2020-10-21

[v0.1.1]: https://github.com/vain0x/milone-lang/releases/tag/v0.1.1

Fixed a bug that name resolution was too slow. Self compilation now spends \~10sec.
This is the first time that pre-compiled compiler binary (for x86_64 linux) is published.

## [v0.1.0] - 2019-10-06

[v0.1.0]: https://github.com/vain0x/milone-lang/releases/tag/v0.1.0

This is the first version of the milone-lang project.
The initial milestone, self-hosting, was reached at the version.

### v0.0.0 - 2018-08-31

Started the project.
