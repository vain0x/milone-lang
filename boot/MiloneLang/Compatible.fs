/// ## Compatibility layer
///
/// Because milone-lang doesn't implement `Map` correctly,
/// we need to use different map functions between milone-lang and F#.
[<AutoOpen>]
module rec MiloneLang.Compatible

// -----------------------------------------------
// Map
// -----------------------------------------------

let mapEmpty _ =
  Map.empty

let mapAdd key value map =
  Map.add key value map

let mapTryFind key map =
  Map.tryFind key map

let mapFold folder state map =
  Map.fold folder state map

let mapMap mapper map =
  Map.map mapper map

let mapToList map =
  Map.toList map

let mapOfList _ pairs =
  Map.ofList pairs
