# Match Expressions

Match expressions perform *pattern matching* on a value for conditional branching based on structure of values.

## Instant Usage

```fsharp
let f (opt: int option): string =
    match opt with
    // `Some ...`: variant pattern and nested payload pattern.
    // `0`: literal pattern (nested pattern)
    | Some 0 -> "zero"

    // `when`: guard clause.
    | Some n when n >= 0 -> string n

    // `_`: Wildcard pattern.
    | Some _ -> "negative"

    // Tag pattern.
    // It's exhaustive: but exhaustivity check is unimplemented.
    | None -> "none"

assert (f (Some 0) = "zero")
assert (f (Some 1) = "1")
assert (f (Some (-1)) = "negative")
assert (f None = "none")
```

## Guide-level Explanation

A match expression consists of an condition expression and a number of clauses.
Each clause consists of a pattern and body expression.

```fsharp
    match condition with
    | pat1 -> body1
    | pat2 -> body2
    ...
    | patN -> bodyN
```

To evaluate a match expression, each pattern in clause is checked whether it does *match* the value of `condition` or not.
If some pattern matches, that clause is picked. Its body expression is evaluated as the result of `match` expression.

All body expressions must have same type.

### Syntax

```fsharp
    match condition with
    | pat1 ->
        body1

    | pat2 ->
        body2

    ...

    | patN ->
        bodyN
```

The `match` keyword and all pipes (`|`) must be aligned on same column.
Body expressions must be indented deeper than that column.

When both pattern and body expression are short, clause can be written in one line.

```fsharp
    | pat -> body
```

### Fundamental Patterns

- Wildcard pattern: `_`
    - This always matches.
- Variable patterns: `a` etc.
    - This always matches to condition.
    - The condition is assigned to the variable and it's available in body expression.
- AS patterns: `p as v`
    - This pattern matches when the inner pattern `p` matches the condition.
    - The value is assigned to the variable `v` and it's available in body expression.
- OR patterns: `p1 | p2`
    - This pattern matches when `p1` *or* `p2` matches the condition.
    - Currently, OR patterns can't bind variables.

### Type-specific Patterns

- Literal patterns: `1`, `'c'`, `"string"`, etc.
    - This pattern matches when the condition equals to the literal.
- Variant patterns: `None` etc.
    - This pattern matches when the condition equals to the variant.
- Variant patterns with payload: `Some p` etc.
    - This pattern matches when the condition is the same variant and the payload pattern `p` matches its payload value.
- Nil patterns: `[]`.
    - This pattern matches when the condition is nil (empty list).
- Cons patterns: `head :: tail`
    - This pattern matches when the condition is cons list (non-empty list) and the `head`/`tail` match its head/tail respectively.
- List patterns: `[ p1; p2; ...; pN ]`
    - This pattern matches when the condition is a list with same length; and for all i, i'th item pattern matches its i'th item.
- Tuple patterns: `p1, p2, ..., pN`
    - This pattern matches when the condition is a tuple with same number of items; and for all i, i'th item pattern matches its i'th item.

### Guarded Clauses

Clauses have optional `when` clause.

```fsharp
    | pat when guard -> body
```

Guarded clause is picked only if the `pat` matches the condition as well as the guard expression evaluated to true.

`guard` must have bool type.

## Advanced Topics

Match expression can be written in one line like this (not recommended).

```fsharp
match condition with Some _ -> true | None -> false
```

If multiple patterns match the condition, the first one of such clauses is picked.
If no pattern matches, the program exits with runtime error.
Non-exhaustive match expressions can be compile error in future version.

One exception about indentation of body expressions.
The body of last clause can be aligned to the same column as `match` keyword (not recommended).

A pattern denies redefining of variables: `match 2, 2 with x, x -> ()` is error since `x` appears twice.
