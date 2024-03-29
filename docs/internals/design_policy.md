# Design Policy

Policy to design the milone-lang language. Policy might vary in future.

## Motivation

Explore programming language design that isn't popular.

## Language Extensions

- milone-lang should be a subset of F# as possible
- Some amount of language extensions are necessary
- Well-formed (= valid in syntax) milone-lang code shall be valid F# code
- Language extensions should be building blocks of abstractions
- Language extensions should be used only in libraries, not application-wide
- Identifiers for language extensions should start with `__`

For quotes:

> - *NOTICE(lang-ext)*: This feature is "language extension", i.e. not compatible with F#. Identifiers that start with `__` are for extensions.

## Feature Covering

- How much the milone-lang covers the F# features
- Basically, "functional" features are supported
- These features aren't planned to support
    - Mutation:
        - `mutable`, assignment, byref, outref
        - Loops
    - Class-based object-oriented:
        - Classes, interfaces, abstract members
        - Inheritance, flexible types (`#seq`)
    - .NET-compatible:
        - Base class library (BCL), NuGet
        - Delegates, events, namespaces, `struct` tuples
        - Exceptions
        - Reflections
    - Meta programming:
        - Code quotations (`<@ @>`)
        - Custom operators (`let (++) ...`)
        - User-defined computation expressions
        - Type providers
    - Others:
        - `do`, `function`
        - `extern` declarations
        - Inline functions
        - Overloaded methods
        - Preprocessor
        - Statically resolved type parameters (SRTP, `^T`)
        - Units of measure
        - Verbose syntax
- Not determined:
    - Active patterns (`let (A|B) ...`)
    - Anonymous records
    - Constraints (`when 'T : ...`, Map type)
    - `inref`
    - `seq`
    - `use`
    - Non-recursive modules
    - Signature files
- Planned to support:
    - `enum`
    - Index notation without dot

### Lvalue

(This section is a kind of sketch of idea.)
(See also "pointer types" in the language documentation.)

Occurrence of "lvalue" in the milone-lang is restricted to `&&x`.

Expressions in C are categorized to lvalues and rvalues.
A variable reference is an lvalue.
Compound expressions such as `x[i].y` can also be an lvalue.

Lvalue expressions are context-sensitive.
Assigning a subexpression to a temporary does change its meaning.

For example, the two statements have different semantics:

```c
    f(&x[i].y);
// vs.
    struct S z = x[i];
    f(&z.y);
```

Compiler needs to track context of expressions to avoid such invalid conversion.

Compound lvalue expressions don't match the concept of the milone-lang as a language based on values.

Another argument is that dereference operator `*` in C doesn't always dereference.
For example, the expression `&((*p).x)` contains `*` yet doesn't read anything from memory.
It's equivalent to `p + offsetof(struct S, x)`, which derives a pointer to field `x` from a pointer to struct `p`.

## Language Characteristics

### Abstraction

This language should provide a way to make an abstract over code that can cause undefined behavior (UB).

Any language that implements FFI can cause UB inevitably.
Key point is that there's a way to wrap UB-causing code with a UB-free abstraction.
One of examples is `Vector` module, a UB-free abstraction over dynamic arrays using memory allocation and pointers.

This characteristic is important for learning and developer experience.
It's difficult for the programmer to notice occasion of UB since program doesn't report errors, goes silently and sometimes seems to work well.
That makes the language more difficult to learn.

Abstraction is also a good tool to design code.
That is, there's a way to wrap invariant-breaking code with a invariant-preserving abstraction.

### Ease of Learning

This language should be easy to learn.

This implies the language attempts to be less powerful.
Features that are powerful yet difficult to learn aren't going to be a part of the language.

## Runtime Characteristics

Policy about a program generated by the milone-lang and other tools.

### Cross Platform

Compiled program should be cross-platform at some level: Linux and Windows.

- Linux is an important platform: server applications and docker containers. Note the author uses Ubuntu Desktop environment for development.
- Windows is so huge platform that shouldn't be ignored.

### Single Binary

Compiled program should be a "single binary" executable.
Reasons:

- Single binary is optimal for end-users; no need to worry about runtime dependencies (ignoring libc).
- There could be a room for a new language to habit as use of micro online services ("lambda functions").
- There are already good languages in the other area.

### Start-up Performance

Compiled program should start instantly. Performance overhead shouldn't be large in comparison to the cost of a process creation by OS.

- Slow to start program tends to be complex: do a bunch of thing in a batch or run as a server.
- Reasons in the "Single Binary" section are applicable to this.
