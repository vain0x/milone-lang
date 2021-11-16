/// Extends prelude `Result` module.
module rec MiloneStd.StdResult

module Result =
  // Variant-wise functions:

  let isOk result =
    match result with
    | Ok _ -> true
    | _ -> false

  let isError result =
    match result with
    | Error _ -> true
    | _ -> false

  let asOk (result: Result<'T, _>) : 'T option =
    match result with
    | Ok value -> Some value
    | _ -> None

  let asError (result: Result<_, 'E>) : 'E option =
    match result with
    | Error e -> Some e
    | _ -> None

  // Mirror of Option functions:

  let defaultValue (alt: 'T) (result: Result<'T, 'E>) : 'T =
    match result with
    | Ok value -> value
    | Error _ -> alt

  let defaultWith (alt: 'E -> 'T) (result: Result<'T, 'E>) : 'T =
    match result with
    | Ok value -> value
    | Error e -> alt e

  let orElse (alt: Result<'T, 'E>) (result: Result<'T, 'E>) : Result<'T, 'E> =
    match result with
    | Ok value -> Ok value
    | Error _ -> alt

  let orElseWith (alt: 'E -> Result<'T, 'E>) (result: Result<'T, 'E>) : Result<'T, 'E> =
    match result with
    | Ok value -> Ok value
    | Error e -> alt e

  // Structural operations:

  let equals
    (okEquals: 'T -> 'T -> bool)
    (errorEquals: 'E -> 'E -> bool)
    (l: Result<'T, 'E>)
    (r: Result<'T, 'E>)
    : bool =
    match l, r with
    | Ok l, Ok r -> okEquals l r
    | Error l, Error r -> errorEquals l r
    | _ -> false

  /// Compares two results using given compare functions. Error is less than Ok.
  let compare
    (okCompare: 'T -> 'T -> int)
    (errorCompare: 'E -> 'E -> int)
    (l: Result<'T, 'E>)
    (r: Result<'T, 'E>)
    : int =
    match l, r with
    | Ok l, Ok r -> okCompare l r
    | Error l, Error r -> errorCompare l r
    | Error _, _ -> -1
    | _ -> 1

  let debug (okDebug: 'T -> string) (errorDebug: 'E -> string) (result: Result<'T, 'E>) : string =
    match result with
    | Ok value -> "Ok(" + okDebug value + ")"
    | Error e -> "Error(" + errorDebug e + ")"

module ResultList =
  /// Maps each item in a list to result value.
  /// Collects Ok payloads and Error payloads in separation.
  ///
  /// Analogue to `Option.choose`.
  let choose (chooser: 'T -> Result<'U, 'E>) (xs: 'T list) : 'U list * 'E list =
    let rec resultListChooseLoop valueAcc errorAcc xs =
      match xs with
      | [] -> List.rev valueAcc, List.rev errorAcc

      | x :: xs ->
        match chooser x with
        | Ok value -> resultListChooseLoop (value :: valueAcc) errorAcc xs
        | Error e -> resultListChooseLoop valueAcc (e :: errorAcc) xs

    resultListChooseLoop [] [] xs
