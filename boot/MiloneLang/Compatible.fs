/// ## Compatibility layer
///
/// Because milone-lang doesn't implement `Map` correctly,
/// we need to use different map functions between milone-lang and F#.
[<AutoOpen>]
module rec MiloneLang.Compatible

type AssocMap<'K, 'V> = (int * ('K * 'V) list) list * ('K -> int) * ('K -> 'K -> int)
