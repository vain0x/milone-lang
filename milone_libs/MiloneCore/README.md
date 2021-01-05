# MiloneCore

**MiloneCore** is one of standard library of milone-lang
for modules that are included in "prelude" of F# such as `List`,
which you can use without writing `open` statements.

This is a subset of such F# libraries.
Provided functions should have compatible behavior with F#.
Some functions are unimplemented yet.

## About partial functions

Partial functions, which could throw exceptions on error such as `List.head`,
are unavailable because milone-lang doesn't support exceptions that you can catch.
