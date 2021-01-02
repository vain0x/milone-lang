# bool type

`bool` is built-in type. Boolean literals are `true` and `false`.

bool type supports comparison operators in the order: `false < true`.

## `not` function

The `not` function flips a boolean value.

```fsharp
    assert (not false)
```

## Logical operators

Logical operators combine two conditions.

- `p && q`: both p and q are true
- `p || q`: either p or q is true

## If expression

`if` expression evaluates either of two expressions depending on a condition.

### Syntax

```fsharp
    // (1) When body or alt is long.
    if condition then
        body
    else
        alt

    // (2) When body and alt is short enough.
    if condition
    then body
    else alt

    // (3) When all subexpressions are short enough.
    if condition then body else alt
```

Else clause can be omitted:

```fsharp
    // (1')
    if condition then
        body

    // (2')
    if condition
    then body

    // (3').
    if condition then body
```

### Typing rule

The condition must have `bool` type. The two expressions must have same type. Else clause is omitted, the body must have `unit` type.

```fsharp
    condition: bool,
    body: unit
==>
    (if condition then body): unit
```

```fsharp
    condition: bool,
    body: T,
    alt: T
==>
    (if condition then body else alt): T
```

### Example

The function `collatz` halves an integer if even or multiplies by 3 and adds 1.

```fsharp
    let collatz (x: int): int =
        if x % 2 = 0 then
            x / 2
        else
            x * 3 + 1

    assert (collatz 4 = 2)   // 4 / 2
    assert (collatz 5 = 16)  // 5 * 3 + 1
```

## `assert`

The `assert` function states that "This condition must be true."

```fsharp
    assert (condition)
```

For example:

```fsharp
    assert (2 + 3 = 5)
```

If the condition evaluated to false, the program ends with runtime error.

## Derived forms

- `p && q` expands to `if p then q else false`. (Short-circuit occurs.)
- `p || q` expands to `if p then true else q`.
- `if cond then body else alt` expands to `match cond with true -> body | false -> alt`.

## Remarks

- Conditions for `if`, `&&`, `assert` etc. are must have `bool` type exactly. (No implicit conversion from int, string, etc. to bool. No truthy/falsy categories. This design choice is compatible with F#. Bad for short coding. Condition type error detects some kind of program error and improves type inference.)
- No conversion from bool to integer types is provided for now.

## Runtime representation

Currently, `bool` type from `<stdbool.h>` is used. That type is a macro, which expands to [`_Bool` type introduced from C99](https://en.cppreference.com/w/c/language/arithmetic_types#Boolean_type).
