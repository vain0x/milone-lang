# MILONE-LANG

[![Build Status](https://travis-ci.org/vain0x/milone-lang.svg?branch=master)](https://travis-ci.org/vain0x/milone-lang)

## What

This is a compiler of programming language, code-name **milone-lang**, which is currently a subset of F#.

The goal is **[self-hosting](https://en.wikipedia.org/wiki/Self-hosting)**, i.e. to make a milone-lang compiler that can compile milone-lang compiler itself.

This project is my study. Don't use in production. Pull requests and issues are welcome.

## Example

I show an example to illustrate what the milone-lang compiler does. It reads a source code like this.

```fs
let main _ =
  let rec factorial x =
    if x = 0 then 1 else x * factorial (x - 1)
  factorial 5 - 120
```

The compiler converts the code to a C language code like the following.

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

After that you will use GCC to compile it to a binary.

Note that the actual output, [factorial.c](./boot/tests/examples/factorial/factorial.c), is not such a beautiful code.

## Project Status

The compiler can compile a single-file CLI application for now.

- Indent-aware parsing
- Basic type inference
- Expressions
    - Literals: `1`, `"str"`, etc.
    - Basic operators: `+`, `::`, etc.
    - Function applications: `f x y` and `y |> f x`
    - Pattern matching
- Functions
    - Local variable capturing
    - Partial applications
    - Function objects
- Types
    - Basic built-in types: `int`, `string`, tuples, lists, functions, etc.
    - Discriminated unions (non-recursive and non-generic)
- IO
    - `printfn` with `%s`, `%d`

See [boot/tests/examples directory](./boot/tests/examples) for non-trivial, working codes.

## How

The compiler is written in F# and works on .NET Core for now. As described above, it emits C language source code. Use GCC for an executable.

For self-hosting, I avoid the use of complex mechanism in compiler source code, such as lex/yacc tools and computation expressions.

### How: Stages

- Lexing (lexical analysis)
    - The input is a source code and the output is a list of tokens.
    - Tokenizer is hand-written.
- Parsing (syntax analysis)
    - Input: a list of tokens. Output: abstract syntax tree (AST).
    - Parser is hand-written, [recursive descent parser](https://en.wikipedia.org/wiki/Recursive_descent_parser).
    - Indent-based semicolon insertion is applied on this stage.
- Typing (type checking)
    - From/to AST
    - Simple unification-based type inference
    - Collect symbol info and types of expression
- FunTrans
    - From/to AST
    - Convert function definitions and applications
    - See [lambda lifting](https://en.wikipedia.org/wiki/Lambda_lifting)
- Monomorphization
    - From/to AST
    - Resolve generics by cloning generic definitions for each combination of type parameters
    - See [Monomorphizing.fs](boot/MiloneLang/Monomorphizing.fs) for details.
- MIR
    - From AST to mid-level intermediate representation (MIR)
    - Convert expressions to imperative statements
    - Pattern matching is broken down to a list of `if`/`goto`s.
- CIR
    - From MIR to CIR
    - Generate `struct`s, etc.
- CPrinting
    - From CIR to C language source code

## Development

### Dev: Prerequisites

- Install .NET Core CLI Tools 2.1
- Install [F# 4.1](http://ionide.io/#requirements)

### Dev: Tasks

[task](./boot/task) provides a set of testing scripts.

- It is written for `bash` because I'm using Ubuntu desktop for development. It might work on Windows Subsystem Linux.

To execute integration tests, run `./task integ-all`.

### Dev: Testing

The `tests` directory contains files for testing.

`dotnet test` performs unit testing. All `tests/*/X/X.fs` files are compiled to matching `tests/*/X/X.c`. The outputs have verified before commit, so it's OK if none of them changed. If an output is changed, you need to perform integration testing to verify.

`./task integ-all` performs integration testing. Each `tests/*/X/X.fs` file is compiled to an executable using GCC and executed. It is verified by matching the stdout and exit code with `tests/*/X/X.out`.

There are some categories of testing files:

- `features`: Language feature testing
- `functions`: Primitives testing
- `errors`: Compile error testing
- `examples`: Complex, meaningful codes
- `pendings`: Incomplete test cases
