# Char type

`char` is a built-in type to represent a component of strings.

## Guide-level explanation

Char literals are written between two single-quotes (`'`), e.g. `'a'`.

### Escape sequences

Escape sequences work same as string literals. See also [String type](string_type.md).

### Conversion

`char` function converts an integer to `char` type. (Signedness and precision are unspecified.)

```fsharp
    assert (char 65 = 'A')
```

Char value can be converted to integer types. See [Int types#Conversion](integer_types.md#Conversion) for details.

```fsharp
    assert (int 'A' = 65)
```

### Remarks

- Single `char` value can't represent all "character" in the world. Learn about Unicode for details.
- `char` value is typically used to represent a UTF-8 code unit in milone-lang, but it's not guaranteed.

## Advanced topics

### Runtime representation

(F#'s `char` type is 2-byte to represent UTF-16 code unit.)

Currently, `char` in milone-lang is same as `char` in C language.

Notice `char` can signed *or* unsigned, depending on implementation.
Even when `char` is signed, it's different type from `signed char`.
See [Types](https://en.cppreference.com/w/c/language/type).
