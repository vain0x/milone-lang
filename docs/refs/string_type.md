# String type

`string` is a built-in type to represent a string (text).

## Guide-level explanation

String literals are written between two double-quotes (`"`), e.g. `"Hello, world!"`.

### Invariants

In milone-lang, strings are assumed to be encoded in UTF-8. (Not guaranteed nor checked, though.)

Strings are immutable. No operation is provided to modify contents of strings (except for FFI).

### `Length` property

Strings have `Length` property to get length in bytes. (O(1) time.)

```fsharp
    assert ("hello".Length = 5)
```

### Operations

Strings support "add" operation (`(+)`) for concatenation and comparison operations (`(=)` etc.) See also [Integer Types](./integer_types.md) for details.

```fsharp
    assert ("!" + "?" = "!?")
```

About performance: the operation likely copies the both strings and newly allocates a string on heap.

### Index operation

`s.[i]` extracts the `i`'th byte of string `s`. (O(1) time. Exceeding the boundary is undefined behavior for now.)

```fsharp
    //       01234 (indices)
    assert ("Hello".[1] = 'e')
    //        ^
```

Index must have `int` type (rather than other integer type). Since `.[ ]` operation is also used for arrays in F#, type of operands are not inferred well. Write type annotation.

```fsharp
    let at (s: string) i = s.[i]
    //       ^^^^^^^^ Annotation for `s.[...]`
```

### Subscript operation

`s.[l .. r]` is a substring from `l`'th byte to `r`'th byte, inclusive.

```fsharp
    //       01234 (indices)
    assert ("Hello".[1 .. 3] = "ell")
    //        ^ ^               ^ ^
```

About performance: if resulting substring is suffix of the string or empty, the operation is guaranteed to be O(1) time. Otherwise, the substring likely gets copied and newly allocated on heap.

Exceeding the boundary is runtime error for now.

### Conversion from numbers

`string` function converts a value of integer or float type to string. (The result format is unspecified for now.)

```fsharp
    assert (string 42 = "42")
```

### Escape sequences

In quotes, backslashes *escape* other characters.

- `\x00`: null byte
- `\t`: tab space
- `\r`: CR
- `\n`: LF (newline)
- `\'`: the character `'`
- `\"`: the character `"`
- `\\`: the character `\`

## Advanced topics

### Runtime representation

(See also `struct String` in [milone.h](../../runtime/milone.h).

Currently, string is a pair of pointer and length.

The pointer points to start or middle of either:

- C string literal, or
- buffer allocated by `calloc` and terminated by null byte.

The length represents the number of bytes of string.

A string object spans from `pointer` to `pointer + length` (exclusive).

The span doesn't include the trailing null byte of string literal or last byte of allocated buffer. String itself is not guaranteed to be null-terminated, but it's not undefined behavior to pass it in a function that expects null-terminated string, e.g. `strtol`.

Since strings are immutable, the buffer pointed by some string object should not be mutated. At least mutation is not observable.
