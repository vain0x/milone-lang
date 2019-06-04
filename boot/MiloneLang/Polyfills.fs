/// Define primitives in milone-lang.

[<AutoOpen>]
module MiloneLang.Polyfills

/// Useful operator to build a list.
let ( *- ) tail head = head :: tail
