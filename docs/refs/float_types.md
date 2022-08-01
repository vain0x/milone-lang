# Float Types

(Float is implemented just to use with FFI and not supported well for now.)

## Guide-level Explanation

`float` is a built-in type to represent a real number approximately.

Float literals are written as `0.0`, `3.14`, `1e9`, `6.02e+23`.
These literals have `float` type.

Float supports arithmetic operations (`(+)` etc.) and comparison operations (`(=)` etc.) as `int` does.
See [Integer types](integer_types.md#Operations) for details.
For binary expressions of float type, both sides of operands must have `float` type, rather than `int`.

### Conversion

The `float` type and integer types are convertible with built-in functions.

```fsharp
    assert (float 2 = 2.0)
    assert (int 3.14 = 3)
```

### Remarks

- `0` is zero of int and `0.0` is zero of float. Two values are incompatible.
- No implicit conversion between float types and integer types. This improves type inference.

## Advanced Topics

### Runtime Representation

Currently, `float` in milone-lang is same as `double` in C.
