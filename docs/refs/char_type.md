# Char type

`char` is a built-in type to represent a component of strings.

## Guide-level explanation

Char literals are written between two single-quotes (`'`), e.g. `'a'`.

### Escape sequences

Escape sequences work same as string literals. See also [String type](string_type.md).

### Conversion

`char` function converts an 8-bit integer to `char` type.

```fsharp
    assert (char 65uy = 'A')
```

Char value can be converted to 8-bit integer types. See [Int types#Conversion](integer_types.md#Conversion) for details.

```fsharp
    assert (byte 'A' = 65uy)
```

### Remarks

- Single `char` value can't represent all "character" in the world. Learn about Unicode for details.
- `char` value is typically used to represent a UTF-8 code unit in milone-lang, but it's not guaranteed.
- `char` doesn't support comparison operators (`<` etc.) to avoid incompatibility with F#.

## Advanced topics

### Runtime representation

(F#'s `char` type is 2-byte to represent UTF-16 code unit.)

Currently, `char` in milone-lang is same as `char` in C language.

Notice `char` can signed *or* unsigned, depending on implementation.
Even when `char` is signed, it's different type from `signed char`.
See [Types](https://en.cppreference.com/w/c/language/type).

The difference makes some of operations work incompatibly.

```fsharp
    assert (char (-1) = char 0xffff) // F#

    // If char->uint conversion were allowed:
    assert (uint (char (-1)) <> 0xff) // F#
    assert (uint (char (-1)) = 0xff) // milone-lang

    // If char comparison is allowed:
    assert (char (-1) >= char 0) // F#
    assert (char (-1) < char 0) // milone-lang
```
