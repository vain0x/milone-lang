# MILONE-LANG

[![Build Status](https://travis-ci.org/vain0x/milone-lang.svg?branch=master)](https://travis-ci.org/vain0x/milone-lang)

*Work in Progress*

## What

This is a compiler of programming language, code name **milone-lang**, which is currently a subset of F# .

The goal is **[self-hosting](https://en.wikipedia.org/wiki/Self-hosting)**, i.e. to make a milone-lang compiler that can compile milone-lang compiler itself.

This project is my study. Don't use in production.

[Milone-lang Code Example](./boot/tests/src/factorial.milone)

## How

The compiler is written in F# and works on .NET Core for now. It emits C language source code. Use GCC for an executable.

For self-hosting, I avoid the use of complex mechanism in compiler source code, such as lex/yacc tools.

### How: Stages

- Lexing
    - From source code to list of tokens
    - With hand-written tokenizer
- Parsing (syntax analysis)
    - From token list to abstract syntax tree
    - With hand-written [recursive descent parser](https://en.wikipedia.org/wiki/Recursive_descent_parser)
    - Indent-based semicolon insertion is applied on this stage.
- Typing (type checking)
    - Collect type info for each expression
    - Simple unification-based type inference
- CIrGen: C language IR generation.
    - From AST and type info to IR
    - IR is a C AST-ish tree.
- CPrinting:
    - From IR to C language source code

## See Also

This project is inspired with [rui314/9cc\: A Small C Compiler](https://github.com/rui314/9cc).
