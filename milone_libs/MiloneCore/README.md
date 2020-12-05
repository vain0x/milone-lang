# MiloneCore

**MiloneCore** is one of standard library of milone-lang.

This is a subset of `FSharp.Core`. Some functions are still unimplemented, though.
Provided functions should have compatible behavior with F#.

### About partial functions

Partial functions, which could throw exceptions on error such as `List.head`,
are unavailable because milone-lang doesn't support exceptions that you can catch.

"Just abort program on runtime error" is an option,
but I don't think standard library should do that.
