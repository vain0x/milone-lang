# Glossary

(*Warning*: too long, you don't need to read. Use as a kind of dictionary.*)

(*Legend: Word, full spelling if abbreviation is set, and meaning in the repository. In alphabetical order.*)

- alt (alternative):
    1. Default value to replace None with.
    2. Expression in `else` clause.
- arg (argument):
    - Value to pass in when calling function at runtime.
    - Expression to be applied to a function (`a` in `f a` in the view of syntax.)
    - Warning: Currently "arg" is also used for parameters but it should be rephrased.
- closure:
    - Specific runtime representation of function object that might capture some state. That is, pair of an opaque pointer (`obj`) and a function pointer.
    - Warning: Currently "closure" is also used for syntax `fun _ -> ....` but it should be rephrased.
- cond (condition):
    - Expression in a particular part of if/match syntax.
        - `if cond then ...`
        - `match cond with ...`
- decl (declaration):
    - Kind of syntax that appears in module directly.
    - In milone-lang, declarations don't appear inside statements or expressions.
- def (definition)
    - Data of entities such as variables and types.
- deref (dereference)
    - Operation to read or write to location pointed by a pointer; `*p` in C.
- env (environment)
    - Mapping from name to thing in a delimited context.
    - Field of a function object. Parameter of an underlying function of function object.
- expr (expression):
    - Kind of syntax that represents a value.
- fun (function)
- fun expression
    - Syntax that looks like `fun ... -> ...`.
- gen (generation)
    - Note: Avoid using `gen` for generic or generalize.
- ident (identifier)
    - Kind of token. Name of thing.
    - Note: Ident doesn't include `.`s in contrast to name, path or nav.
- infer type:
    - Name of `_` type, which is a placeholder of a type to be inferred.
- init (initialization)
- let-val
    - Syntax that looks like `let x = ...` (no parameters in left-hand side) in contrast to let-fun.
- let-fun
    - Syntax that looks like `let f x = ...` (some parameters in left-hand side) in contrast to let-val.
- lit (literal)
    - Kind of token and expression that represent a specific value.
- NameRes (name resolution)
    - Particular pass
- ns (namespace)
    - (In NameRes) Set of symbols as children of other symbol.
- NsOwner (namespace owner)
    - (In NameRes) Reference of a symbol that owns a namespace.
- op (operator)
    - Note: Avoid using "op" for operation that is unrelated to operator.
- opt (optional)
    - Note: Variable name `xOpt` indicates its type is `T option`.
- param (parameter)
    - Note: `params` is a keyword. Use `paramList` or something instead.
- symbol
    - Token that denotes to a defined entity (such as variables and types.)
    - Value to identify a defined entity such as ID.
- qual (qualifier)
    - Non-last segment in a path of name.
- ref (reference)
- semi (semicolon)
- std (standard)
- stmt (statement)
    - Note: I feel this spelling awful but it's commonly used.
- ty (type)
- univ (universal)
    - Universally quantified type variable, e.g. `'A`.

### Policy

- Ubiquitous abbreviations such as "info" are also used.
- I believe abbreviations should be
    - only for frequently-used words,
    - much shorter than full spelling,
    - prefix of full spelling if possible,
    - able to pronounce,
    - used consistently.
