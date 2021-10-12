# ARCHITECTURE

(*What is ARCHITECTURE.md?* See [this article: ARCHITECTURE.md](https://matklad.github.io/2021/02/06/ARCHITECTURE.md.html).)

## Bird's Eye Overview

Compiler does *parse* a program and then *transform*.

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

- MiloneShared: Shared types and utils
- MiloneSyntax: Syntax analysis and type checking
- MiloneTransform: Code generation
- MiloneCli: CLI app
- MiloneLspServer: LSP server implementation (F#)

Diagram of project dependencies:

        Shared
            ^
          /   \
         /     \
    Syntax   Transform
     ^  ^       ^
     |   \     /
     |    \   /
     |     Cli
    LSP

Note that Transform is not depended by Syntax and LSP server.
That illustrates modification of Transform doesn't affect interface of the language.

### Intermediate representations

- Abstract Syntax Tree (AST)
- Typed intermediate representation (TIR)
    - Functional-style IR. For checking.
- High-level intermediate representation (HIR)
    - Functional-style IR. For transformation.
- Mid-level intermediate representation (MIR)
    - For C code generation.
    - Imperative-style IR.
- C intermediate representation (CIR)
    - Similar to AST of C language.

Diagram of data flow.

    Files (*.fs, *.milone)
      | tokenize & parse
      v
     AST
      ↓
     TIR -- type checking etc.
      |
      ~  -- boundary
      ↓
     HIR -- closure conversion etc.
      ↓
     MIR
      ↓
     CIR
      ↓
    Files (*.c)     

### Language-Specific Files

- FSharpOnly and Program.fs are F# only part.
- MiloneOnly and `*.milone` are milone-lang only part.

## Cross-Cutting Concerns

*WIP*
