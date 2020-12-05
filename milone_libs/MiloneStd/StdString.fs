module rec MiloneStd.StdString

open MiloneStd.StdChar

/// Ensures `minValue <= value <= maxValue`.
let private intClamp (minValue: int) (maxValue: int) (value: int) =
  if value < minValue then minValue
  else if maxValue < value then maxValue
  else value

let isEmpty (str: string): bool = str.Length = 0

let tryItem (index: int) (str: string): char option =
  if 0 <= index && index <= str.Length then Some str.[index] else None

// -----------------------------------------------
// Search
// -----------------------------------------------

/// Gets if a substring occurs at the specified index in string.
///
/// Start index is strict.
let private occursAt (start: int) (substr: string) (s: string): bool =
  let rec occursAtLoop i =
    (i = substr.Length)
    || (s.[start + i] = substr.[i] && occursAtLoop (i + 1))

  (0 <= start && start + substr.Length <= s.Length)
  && occursAtLoop 0

let startsWith (prefix: string) (s: string): bool = occursAt 0 prefix s

let endsWith (suffix: string) (s: string): bool =
  occursAt (s.Length - suffix.Length) suffix s

/// Finds first index of string where a substring occurs.
let findIndex (substr: string) (s: string): int option =
  // Upper bound of the index that could satisfy the predicate.
  let r = s.Length - substr.Length + 1

  let rec stringFindIndexLoop i =
    if i >= r then None
    else if occursAt i substr s then Some i
    else stringFindIndexLoop (i + 1)

  stringFindIndexLoop 0

/// Finds last index of string where a substring occurs.
let findLastIndex (substr: string) (s: string): int option =
  let rec stringFindLastIndexLoop r =
    if r <= 0 then None
    else if occursAt (r - 1) substr s then Some(r - 1)
    else stringFindLastIndexLoop (r - 1)

  // Upper bound of the index that could satisfy the predicate.
  let r = s.Length - substr.Length + 1

  stringFindLastIndexLoop r

/// Gets a substring occurs in a string.
let contains (substr: string) (s: string): bool =
  match findIndex substr s with
  | Some _ -> true
  | None -> false

// -----------------------------------------------
// Slices
// -----------------------------------------------

/// Gets a prefix of string with specified length.
///
/// Analogue to `List.truncate`.
///
/// This functions is tolerant about exceeding the boundary.
/// If `prefixLen < 0`, returns `""`.
/// If `prefixLen > s.Length`, returns s itself.
let truncate (prefixLen: int) (s: string): string =
  if prefixLen <= 0 then ""
  else if prefixLen >= s.Length then s
  else s.[0..prefixLen - 1]

/// Removes a prefix of string by specified length.
///
/// Analogue to `List.skip`.
///
/// This functions is tolerant about exceeding the boundary.
/// If `prefixLen < 0`, returns `s` itself.
/// If `prefixLen > s.Length`, returns `""`.
let skip (prefixLen: int) (s: string): string =
  if prefixLen <= 0 then s
  else if prefixLen >= s.Length then ""
  else s.[prefixLen..s.Length - 1]

/// Gets a contiguous substring in specified range. End index is exclusive.
///
/// Unlike `s.[..]`, this function is tolerant about exceeding the boundary.
/// If `start < 0`, use 0 as start index instead.
/// If `end > s.Length`, use `s.Length` as end index instead.
let slice (start: int) (endIndex: int) (s: string): string =
  let start = start |> intClamp 0 s.Length
  let endIndex = endIndex |> intClamp start s.Length
  if start < endIndex then s.[start..endIndex - 1] else ""

// -----------------------------------------------
// Trim
// -----------------------------------------------

/// Removes leading and trailing chars that satisfy predicate.
let trimIf (isTrimmed: char -> bool) (s: string) =
  let l =
    let rec stringTrimIfLoop1 (l: int) =
      if l < s.Length && isTrimmed s.[l] then stringTrimIfLoop1 (l + 1) else l

    stringTrimIfLoop1 0

  let r =
    let rec stringTrimIfLoop2 (r: int) =
      if r > l && isTrimmed s.[r - 1] then stringTrimIfLoop2 (r - 1) else r

    stringTrimIfLoop2 s.Length

  if l < r then s.[l..r - 1] else ""

/// Removes leading chars that satisfy predicate.
let trimStartIf (isTrimmed: char -> bool) (s: string) =
  let l =
    let rec stringTrimStartIfLoop (l: int) =
      if l < s.Length && isTrimmed s.[l] then stringTrimStartIfLoop (l + 1) else l

    stringTrimStartIfLoop 0

  if l < s.Length then s.[l..s.Length - 1] else ""

/// Removes trailing chars that satisfy predicate.
let trimEndIf (isTrimmed: char -> bool) (s: string) =
  let r =
    let rec stringTrimEndIfLoop (r: int) =
      if r > 0 && isTrimmed s.[r - 1] then stringTrimEndIfLoop (r - 1) else r

    stringTrimEndIfLoop s.Length

  if r > 0 then s.[0..r - 1] else ""

/// Removes leading and trailing spaces.
let trim (s: string) = s |> trimIf isSpace

/// Removes leading spaces.
let trimStart (s: string) = s |> trimStartIf isSpace

/// Removes trailing spaces.
let trimEnd (s: string) = s |> trimEndIf isSpace

// -----------------------------------------------
// Split
// -----------------------------------------------

let private findNewline (start: int) (s: string) =
  let i = start
  if i < s.Length
     && (s.[i] <> '\x00' && s.[i] <> '\r' && s.[i] <> '\n') then
    findNewline (i + 1) s
  else
    i

/// Scans a line of string. Line ends with a `\r`, `\n`, or `\x00`.
///
/// Returns `(lineContents, newlineOpt, rest)`, where:
///
/// `lineContents` is the contents of the line.
/// Empty if string starts with newline or is empty.
///
/// `newlineOpt` is "\n" or "\r\n" (or perhaps "\r"), which is actually found.
///
/// `rest` is the string after the newline.
/// Empty if it ends with the newline or no newline found.
let scanLine (s: string): string * string option * string =
  let m = findNewline 0 s
  let lineContents = if m > 0 then s.[0..m - 1] else ""

  if m = s.Length then
    lineContents, None, ""
  else
    let sepLen =
      if (m + 1) < s.Length
         && s.[m] = '\r'
         && s.[m + 1] = '\n' then
        2
      else
        assert (s.[m] = '\x00' || s.[m] = '\r' || s.[m] = '\n')
        1

    let r = m + sepLen
    let sep = s.[m..r - 1]

    let rest =
      if r < s.Length then s.[r..s.Length - 1] else ""

    lineContents, Some sep, rest

/// Splits a string to lines.
let toLines (s: string): string list =
  // l: Start index of current line.
  let rec stringToLinesLoop (l: int) acc =
    let r = findNewline l s

    let acc =
      (if l < r then s.[l..r - 1] else "") :: acc

    if r = s.Length then
      acc
    else if (r + 1) < s.Length
            && s.[r] = '\r'
            && s.[r + 1] = '\n' then
      stringToLinesLoop (r + 2) acc
    else
      assert (s.[r] = '\r' || s.[r] = '\n')
      stringToLinesLoop (r + 1) acc

  [] |> stringToLinesLoop 0 |> List.rev

// -----------------------------------------------
// Compose
// -----------------------------------------------

/// Same as `String.concat` but takes a list, rather than #seq (which is unimplemented in milone-lang).
let concat (sep: string) (xs: string list): string = __stringJoin sep xs
