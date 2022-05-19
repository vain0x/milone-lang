# Changelog

> [Keep a Changelog](https://keepachangelog.com/)

## [Unreleased]

[Unreleased]: https://github.com/vain0x/milone-lang/v0.4.0...develop

https://github.com/vain0x/milone-lang/commits/develop?after=689350a9d82133b68350a91c806303dab408630a+839&branch=develop&qualified_name=refs%2Fheads%2Fdevelop

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
    - Add  `__outptr<'T>` and `__voidinptr<'T>` types
    - Change `__constptr` to `__inptr`
    - Add ptr-of (`&&`) operator
    - Add `Ptr` module
        - `select`, `read`, `write`
        - `nullPtr`, `invalid`
        - `cast`, `asIn`, `asNative`
        - `distance`
- Improve primitives:
    - Fix an issue that `string : bool -> string` didn't work at all
    - Add `__discriminant`
    - Add `sizeof<'T>`, remove `__sizeOfVal` primitive in favor of this
    - Rename `inRegion` to `Region.run`
    - `__nativeExpr` etc. can now embed some expressions and types
- Support provisional manifest files (`milone_manifest`)

### Runtime Library

- Reduce headers included in `milone.h`
- Heaps are now stored in thread-local variables (rather than static)
- Rename most of functions
- Prefer `uint32_t` for size/length/capacity (over `int`)

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
    - `Vector`, `ByteVector`, `Block`
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
- change parameter order
    - `S -> T -> S` for fold
    - `S -> T -> T * S` for map-fold
- remove intermediate type information from MIR expressions

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
