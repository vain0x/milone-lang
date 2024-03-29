# Integer Types

## Guide-level Explanation

`int` is a built-in type to represent a integer (in a limited set).

Integer literals are written as `0`, `1`, `42`, etc. Their type is `int`.

### Arithmetic Operations

- `-x`: minus
    - *Known issue*: Due to incorrect parsing of unary operators, you should wrap it with parens, e.g. `(-1)`.
- `x + y`: addition
- `x - y`: subtraction
- `x * y`: multiplication
- `x / y`: division
- `x % y`: modulo

### Bitwise Operations

- `~~~x`: bit-wise not
- `x &&& y`: bit-wise and
- `x ||| y`: bit-wise or
- `x ^^^ y`: bit-wise xor
- `x <<< n`: left shift
- `x >>> n`: right shift

### Comparison Operations

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

## Advanced Topics

### Other Integer Types

| name          | signedness    | width     | suffix | alias |
|:--------------|--------------:|----------:|:-------|:------|
| int8          | signed        | 8 bits    | y      | sbyte |
| int16         | signed        | 16 bits   | s      | - |
| int32         | signed        | 32 bits   | -      | int |
| int64         | signed        | 64 bits   | L      | - |
| nativeint     | signed        | 1 word    | n      | - |
| uint8         | unsigned      | 8 bits    | uy     | byte |
| uint16        | unsigned      | 16 bits   | us     | - |
| uint32        | unsigned      | 32 bits   | u      | uint |
| uint64        | unsigned      | 64 bits   | UL     | - |
| unativeint    | unsigned      | 1 word    | un     | - |

`1 word` means a size of pointer: 64 bits on 64-bit platform, 32 bits on 32-bit platform, and so on.

Integer literal needs to have *suffix* to specify their type (except for int).

```fsharp
    let b = 127uy       // uy for Unsigned bYte
    let s = 65535us     // us for Unsigned Short
    let n = 100100100100100100L // L for Long
```

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
    n: I
==>
    (~~~n): I
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

### Byte Literals

A character literal with suffix `B` represents a byte value.

```fsharp
    assert (`'a'B` = 97uy)
```

### Runtime Representation

N-bit integer types in milone-lang map to corresponding fixed integer types[^1] in C; e.g. `int` → `int32_t`.

`nativeint` is `intptr_t` and `unativeint` is `uintptr_t`.

[^1]: [Fixed width integer types](https://en.cppreference.com/w/c/types/integer).
