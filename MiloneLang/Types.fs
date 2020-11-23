/// Defines the types used in multiple modules.
module rec MiloneLang.Types

open MiloneLang.TreeMap

// -----------------------------------------------
// Collections
// -----------------------------------------------

type AssocMap<'K, 'V> = TreeMap<'K, 'V>

type AssocSet<'K> = TreeMap<'K, unit>

/// Tree to generate a string for debugging.
[<NoEquality; NoComparison>]
type DumpTree = DumpTree of heading: string * body: DumpTree list * next: DumpTree list
