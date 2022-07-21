/// Extends `Option`.
module rec Std.StdOption

module Option =
  // Structural operations:

  let equals (itemEquals: 'T -> 'T -> bool) (l: 'T option) (r: 'T option) : bool =
    match l, r with
    | Some l, Some r -> itemEquals l r
    | None, None -> true
    | _ -> false

  /// Compares two options using given compare function. None is less than Some.
  let compare (itemCompare: 'T -> 'T -> int) (l: 'T option) (r: 'T option) : int =
    match l, r with
    | Some l, Some r -> itemCompare l r
    | None, None -> 0
    | None, _ -> -1
    | _ -> 1

  let debug (itemDebug: 'T -> string) (opt: 'T option) : string =
    match opt with
    | Some value -> "Some(" + itemDebug value + ")"
    | None -> "None"
