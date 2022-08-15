# ARCHITECTURE

(*What is ARCHITECTURE.md?* See [this article: ARCHITECTURE.md](https://matklad.github.io/2021/02/06/ARCHITECTURE.md.html).)

## Bird's Eye Overview

Compiler does *parse* a program and then *codegen*.

    [ milone-lang code ]
        |
        | OK?
        +--------→ [ error ]
        ↓
    [  IR  ]
        |
        | codegen
        ↓
    [ C code ]

## Code Map

Projects:

- lib: MiloneShared: Shared types, functions and utilities
- lib: MiloneSyntax: Syntax analysis and semantic check
- lib: MiloneTranslation: Code generation actual logic
- app: MiloneCli: CLI client
- app: MiloneLspServer: LSP server implementation (F#)

Diagram of project dependencies:

         Shared
            ^
          /   \
         /     \
    Syntax   Translation
     ^  ^       ^
     |   \     /
     |    \   /
     |      v
     |   CLI tool
     |
  LSP server

Note that Translation isn't depended by Syntax and LSP server.
That illustrates modification of Translation doesn't affect the interface of language.

### Intermediate representations

- Abstract Syntax Tree (AST)
    - AST is well-known. IR for syntax.
- Name resolution intermediate representation (NIR)
    - Functional-style IR for semantic check. Symbols are strings.
- Typed intermediate representation (TIR)
    - Functional-style IR for semantic check. Symbols are internal IDs.
- High-level intermediate representation (HIR)
    - Functional-style IR for transformation and codegen.
- Mid-level intermediate representation (MIR)
    - Imperative-style IR for C code generation.
- C intermediate representation (CIR)
    - IR similar to AST of C language.

Diagram of data flow.

    Files (*.fs, *.milone)
      ↓ tokenize & parse
     AST
    　↓
     NIR
      ↓  -- name resolution
     TIR -- type check etc.
      |
      ~  -- boundary
      ↓  -- lower
     HIR
      ↓  -- closure conversion etc.
     MIR
      ↓
     CIR
      ↓
    Files (*.c)

### Language-Specific Files

- FSharpOnly and Program.fs are F# only part.

## Cross-Cutting Concerns

*WIP*
