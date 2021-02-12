# String type

`string` is a built-in type to represent a string (text).

## Guide-level explanation

String literals are written between two double-quotes (`"`), e.g. `"Hello, world!"`.

### `Length` property

Strings have `Length` property to get its length in bytes.

```fsharp
    assert ("hello".Length = 5)
```

About performance: O(1) time.

### Operations

Strings support concatenation operation (`(+)`) and comparison operations (`(=)` etc.) See also [Integer types](integer_types.md).

```fsharp
    assert ("!" + "?" = "!?")
```

About performance: concatenation likely copies the both strings and newly allocates a string on heap.

### Index operation

`s.[i]` extracts the `i`'th byte of string `s`.

```fsharp
    //       01234 (indices)
    assert ("Hello".[1] = 'e')
    //        ^
```

Index must have `int` type (rather than other integer types). Since `.[]` operation is also used for arrays in F#, type of operands are not inferred well. Write type ascription.

```fsharp
    let at (s: string) i = s.[i]
    //       ^^^^^^^^ Ascription for `s.[...]`
```

About performance and safety: indexing is O(1) time. Exceeding the boundary is undefined behavior for now.

### Subscript operation

`s.[l .. r]` is a substring from `l`'th byte to `r`'th byte, inclusive.

```fsharp
    //       01234 (indices)
    assert ("Hello".[1 .. 3] = "ell")
    //        ^ ^               ^ ^
```

About performance and safety: O(1) time and no allocation. Exceeding the boundary is runtime error for now.

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

(See also `struct String` in [milone.h](../../runtime/milone.h).)

Currently, string is a pair of a pointer (to `char`s) and length.
The pointer can't be null.
The length represents the number of bytes of string.

Span from `pointer` to `pointer + length` (exclusive) is an interval of either:

- a C string literal, or
- a buffer allocated by `calloc`.

A string spans from `pointer` to `pointer + length` (exclusive).

### Invariants

- Strings are encoded in UTF-8.
    - This is not guaranteed nor checked.
- Strings are immutable.
    - No operation is provided to modify contents of strings except for FFI.
    - This allows sharing of strings. With this property, the runtime can guarantee that subscript operation doesn't allocate.
- Buffer pointed by string must contain at least one null byte (`\x00`) after the end of string.
    - This property doesn't imply that strings are null-terminated.
        For example, `"hello".[0..1]` (= `"he"`) is unlikely null-terminated.
    - This property implies that the end of span is safe to dereference.
        - Runtime may check whether a string is null-terminated or not just by dereferencing `pointer + length`.
