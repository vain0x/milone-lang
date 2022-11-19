# Prefer Signed Indexes

This page describes why the language use signed integer types for indexes.

## Index-like Values

List of index-like values that are considered in the page is:

- index of strings or arrays
- size (in bytes)
- count
- length
- capacity

## What

Use `int` in milone-lang or `int32_t` in C by default for these types.

## Why `int`

The main reason is compatibility with F# that uses `int`.

Examples: `i` in `s.[i]` is int. `sizeof<'T>` is int.

Known downsides:

- Bloat of bound checks (`assert (i >= 0)`)
- Unintentional wrapping (no warning on `UINT32_MAX + 1`)

## Why Not `size_t`

C standard library uses `size_t` (basically `unativeint` in the milone-lang) for index-like types.
`size_t` is too large for most of cases and wastes memory when stored in objects.

Note file and blobs tend to be larger than the max value of int (2GB.)

## Why Not `uint`



----
----

## Appendix: Boundary Check Trick

When `len >= 0` is assumed, `0 <= i && i < len` can be replaced with `uint i < uint len`.
That works faster for lack of `&&`.

## Appendix: Tips on C Integer Types

**int**:

The `int` type in C (`CInt`) isn't equivalent to `int` in the milone-lang.
`CInt`, which is defined in the specification in a subtle way, is equivalent to `int32_t` in most of cases.
In rare situations, it's equivalent to `int16_t` or `int64_t`.

**size_t**:

The `size_t` type is an unsigned integer type.
Commonly either `uint32_t` or `uint64_t`.

## Appendix: Tips on Arithmetic Operations

This is a guide for using integer types in C.

`int` -> `int32_t` is okay to be implicit.

```c
int n;
int32_t m = n;
```

When `int` -> `int32_t` cast and then an operation is done, flip it.
Cast to `int32_t` first and then operate in case `int` is smaller than `int32_t`.

```c
int n;
int32_t m = (int32_t)n + 1;
```

`int32_t` -> unsigned types (e.g. `uint32_t`, `size_t`) cast should be explicit.
Be sure the signed value is non-negative.

```c
int32_t n;
assert (n >= 0);
uint32_t u = (uint32_t)n;
size_t z = (size_t)n;
```

Prefer cast-then-operate over operate-then-cast in order to avoid C compiler warning.
Detect overflow before operation if necessary.

```c
uint32_t n1, n2;

// Cast and then add.
size_t z = (size_t)n1 + (size_t)n2;

// Verify (n1 + n2 < 2^31).
assert(n1 < (1U << 31) - n2);
int32_t sum = n1 + n2;

// Verify (n1 * n2 < 2^31).
assert (n2 == 0 || n1 < (1U << 31) / n2);
int32_t prod = n1 * n2;
```

Right shift depends on signedness.
(Other bit-wise operations don't depend on signedness.)

```c
// 0b1000'0000
uint8_t n = 1 << 7;

assert ((n >> 7) == 1);
assert (((int8_t)n >> 7) == -1);
```

Overflow of signed values causes undefined behavior in C.
(Unsigned wraps.)

```c
// ❌ BAD: Undefined behavior.
int32_t n = 0x7fff'ffff;
n++;
```

```c
// OK.
int32_t m = 0x7fff'ffff;
assert((uint32_t)m + 1 == 0x8000'0000U);
```
