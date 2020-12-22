# Char Type

`char` is built-in type.

Char literals are written between two single-quotes (`'`), e.g. `'a'`. Escape sequence works same as string literals. See also [String Type](./string_type.md).

## Remarks

- Single `char` value can't represent all "character" in the world. Learn about Unicode for details.
- `char` value is typically used to represent a UTF-8 code unit in milone-lang, but it's not guaranteed.

## Runtime representation

(F#'s `char` type is 2-byte to represent UTF-16 code unit.)

`char` is represented by `char` in C language. Some integer with implementation-specific size and signedness.
