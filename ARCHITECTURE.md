# ARCHITECTURE

(*What is ARCHITECTURE.md?* See [this article: ARCHITECTURE.md](https://matklad.github.io/2021/02/06/ARCHITECTURE.md.html).)

## Code map

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

### Data structures

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

    FileSystem (*.milone)
      | tokenize & parse
      v
     AST
      |
      v
     TIR -- type checking etc.
      |
      ~  -- Syntax / Transform boundary
      |
      v
     HIR -- closure conversion etc.
      ↓
     MIR
      ↓
     CIR
      ↓
    FileSystem (*.c)     

### Others

- FSharpOnly and Program.fs is F# only part.
- MiloneOnly is milone-lang only part.
