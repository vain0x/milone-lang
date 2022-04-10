# Design Policy

Policy when to design the milone-lang language. Policy might vary in future.

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
