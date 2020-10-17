/// Defines milone-lang primitives for F#.
[<AutoOpen>]
module rec MiloneLang.Compatible

type AssocMap<'K, 'V> = (int * ('K * 'V) list) list * ('K -> int) * ('K -> 'K -> int)

type AssocSet<'K> = AssocMap<'K, unit>

let objToString (value: _) = string (value :> obj)
