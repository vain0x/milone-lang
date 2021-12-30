# Glossary

(*Warning*: too long, you don't need to read. Use as a kind of dictionary.*)

(*Legend: Word, full spelling if abbreviation is set, and meaning in the repository. In alphabetical order.*)

- alt (alternative):
    1. Default value to replace None with.
    2. An expression in `else` clause.
- arg (argument):
    - Value to pass in when calling function.
    - `a` in use-site `f a`; in contrast to parameter x in def-site `let f x`.
    - Warning: Currently "arg" is also used for parameters but it should be rephrased.
- closure:
    - Specific runtime representation of function object that might capture some state. That is, pair of an opaque pointer (`obj`) and a function pointer.
    - Warning: Currently "closure" is also used for syntax `fun _ -> ....` but it should be rephrased.
- cond (condition):
    - Expression in some part of if/match syntax.
        - `if cond then ...`
        - `match cond with ...`
- decl (declaration):
    - Kind of syntax that appears in module directly.
    - In milone-lang, declarations don't appear inside statements or expressions.
- deref (dereference)
    - Operation `*p` in C.
- div (division)
- env (environment)
    - Mapping from name to thing in a delimited context.
- expr (expression):
    - A kind of syntax. Evaluating an expression results in a value.
- fun (function)
- gen (generation)
    - Note: avoid using `gen` for generic/generalize.
- ident (identifier)
    - A kind of token. Name of something.
    - Note ident doesn't include `.`s in contrast to name, path or nav.
- infer type:
    - Name of `_` type, which is a placeholder of some type to be inferred.
- init (initialize)
- lit (literal)
    - A kind of token and expression that represent a specific value.
- mul (multiplication)
- op (operator)
    - Note: avoid using "op" for operation that is unrelated to operator.
- opt (optional)
    - Note: Variable name `xOpt` indicates `option<T>` type.
- param (parameter)
    - Note that `params` is keyword in F#. Use `paramList` or something.
- qual (qualifier)
    - Non-last segment of path of name.
- ref (reference)
- semi (semicolon)
- sub (subtraction)
- std (standard)
- stmt (statement)
    - Note that I feel this spelling awful but it's commonly used.
- ty (type)

### Policy

- Ubiquitous abbreviations such as "info" are also used.
- I believe abbreviations should be
    - only for frequently-used words,
    - much shorter than full spelling,
    - prefix of full spelling if possible,
    - able to pronounce,
    - used consistently.
