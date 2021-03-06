# Integer types

## Guide-level explanation

`int` is a built-in type to represent a integer (in a limited set).

Integer literals are written as `0`, `1`, `42`, etc. Their type is `int`.

### Arithmetic operations

- `-x`: minus
    - *Known issue*: Due to incorrect parsing of unary operators, you should wrap it with parens, e.g. `(-1)`.
- `x + y`: addition
- `x - y`: subtraction
- `x * y`: multiplication
- `x / y`: division
- `x % y`: modulo

### Bit operations

- `x &&& y`: bit-wise and
- `x ||| y`: bit-wise or
- `x ^^^ y`: bit-wise xor
- `x <<< n`: left shift
- `x >>> n`: right shift

### Comparison operations

- `x = y`: x equals to y (Don't confuse with `==`.)
- `x <> y`: x does NOT equal to y
- `x < y`: x is less than y
- `x <= y`: x is less than or equal to y
- `x > y`: x is greater than y
- `x >= y`: x is greater than or equal to y
- `compare x y`: gets a negative number if `x < y`, zero if `x = y`, positive if `x > y`

### Conversion

`int` type supports conversion from/to float and string.

When string-to-int conversion failed, the program ends with runtime error.

### Remarks

- Overflow of signed integer is undefined behavior. (This behavior is derived from C language.)

## Advanced topics

### Integer types other than `int`

| name          | signedness    | width     | alias |
|:--------------|--------------:|----------:|:------|
| int8          | signed        | 8 bits    | sbyte |
| int16         | signed        | 16 bits   | - |
| int32         | signed        | 32 bits   | int |
| int64         | signed        | 64 bits   | - |
| nativeint     | signed        | 1 word    | - |
| uint8         | unsigned      | 8 bits    | byte |
| uint16        | unsigned      | 16 bits   | - |
| uint32        | unsigned      | 32 bits   | uint |
| uint64        | unsigned      | 64 bits   | - |
| unativeint    | unsigned      | 1 word    | - |

`1 word` means a size of pointer: 64 bits on 64-bit platform, 32 bits on 32-bit platform, and so on.

There are built-in functions with same name as every integer type to convert an integer to that type.

```fsharp
    let n: int64 = int64 4
    //             ^^^^^ Conversion to int64.

    let m: unativeint = unativeint 8
    //                  ^^^^^^^^^^ Conversion to unativeint.
```

All integer types support arithmetic operations (`(+)` etc.), bit operations (`(&&&)` etc.), and comparison operations (`(=)` etc.) as `int` does.
Both side of operands must have same type, except for right-hand side of shifts.

Typing rules:

```fsharp
    I: signed integer type,
    n: I
==>
    (-n): I
```

```fsharp
    I: integer type,
    l: I,
    r: I
==>
    (l + r): I,
    (l * r): I,
    (l &&& r): I, etc.
```

```fsharp
    I: integer type,
    l: I,
    r: int
==>
    (l <<< r): I,
    (l >>> r): I
```

### Runtime representation

Currently, `int` in milone-lang is same as `int` in C.
For other types, fixed integer types[^1] in C language are used.
`nativeint` is `intptr_t`, `unativeint` is `uintptr_t`.

[^1]: [Fixed width integer types](https://en.cppreference.com/w/c/types/integer).
