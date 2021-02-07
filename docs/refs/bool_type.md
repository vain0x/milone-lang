# Bool type

`bool` is a built-in type to represent a truth value.

## Guide-level explanation

Boolean literals are `true` and `false`.

The `bool` type supports comparison operations in the order: `false < true`. See [Integer types](integer_types.md#Operations) for details.

### `not` function

The `not` function flips a boolean value.

```fsharp
    assert (not false)
```

### Logical operators

Logical operators combine two conditions.

- `p && q`: both p and q are true
- `p || q`: either p or q is true

### If expression

`if` expression evaluates either of two expressions depending on a condition.

Syntax:

```fsharp
    // (1) When body or alt is long.
    if condition then
        body
    else
        alt

    // (2) When body and alt are short enough.
    if condition
    then body
    else alt

    // (3) When all subexpressions are short enough.
    if condition then body else alt
```

Else clause can be omitted (and `else ()` is used):

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

Example: the function `collatz` halves an integer if even or multiplies by 3 and adds 1.

```fsharp
    let collatz (x: int): int =
        if x % 2 = 0 then
            x / 2
        else
            x * 3 + 1

    assert (collatz 4 = 2)   // 4 / 2
    assert (collatz 5 = 16)  // 5 * 3 + 1
```

### `assert` function

The `assert` function states that "This condition must be true."

```fsharp
    assert condition
```

For example:

```fsharp
    assert (2 + 3 = 5)
```

If the condition evaluated to false, the program ends with runtime error.

### Remarks

- Conditions for `if`, `&&`, `assert` etc. must have `bool` type.
    - No implicit conversion from int, string, etc. to bool.
    - No truthy/falsy categorization.
    - This design choice is compatible with F#. It improves type inference.

## Advanced topics

### Typing rule

The condition must have `bool` type.
The two expressions must have same type.
If `else` clause is omitted, body must have `unit` type.

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

### Derived forms

- `p && q` expands to `if p then q else false`. (Short-circuit occurs.)
- `p || q` expands to `if p then true else q`.
- `if cond then body else alt` expands to `match cond with true -> body | false -> alt`.

### Runtime representation

Currently, `bool` in milone-lang is same as `bool` from `<stdbool.h>`, which is a macro of `_Bool`.
See [`_Bool` type introduced from C99](https://en.cppreference.com/w/c/language/arithmetic_types#Boolean_type).
