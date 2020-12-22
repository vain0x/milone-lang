# float types

(Float is implemented just to use with C FFI and not supported well for now.)

## `float` type

`float` is a built-in type to represent a real number approximately.

Float literals are written as `0.0`, `3.14`, `1e9`, `6.02e+23`. These literals have `float` type.

Float supports arithmetic operations (`(+)` etc.) and comparison operations (`(=)` etc.) as `int` does. For binary expressions of float type, both sides of operands must have `float` type, rather than `int`.

## Remarks

- `0` is zero of int and `0.0` is zero of float. Two values are incompatible.
- No implicit conversion between float types and integer types. (This design is bad for short coding, but improves type inference.)

## Runtime representation

- `float` in milone-lang is same as `double` in C.
