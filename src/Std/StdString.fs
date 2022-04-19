/// # StdString
///
/// Provides functions to manipulate string.
///
/// See also: <https://github.com/fsharp/fslang-design/blob/e50f1bcd5f9824e287a9e70d03b37f07d170d25f/RFCs/FS-1033-extend-string-module.md>
module rec Std.StdString

module B = Std.StdStringBase
module C = Std.StdChar

/// Ensures `minValue <= value <= maxValue`.
let private intClamp (minValue: int) (maxValue: int) (value: int) =
  if value < minValue then minValue
  else if maxValue < value then maxValue
  else value

/// Gets whether a string is empty, i.e. length is zero.
///
/// O(1) time.
let isEmpty (s: string) : bool = s.Length = 0

/// Gets a byte in string at specified index.
///
/// O(1) time.
let tryItem (index: int) (s: string) : char option =
  if 0 <= index && index < s.Length then
    Some s.[index]
  else
    None

// -----------------------------------------------
// Search
// -----------------------------------------------

/// Gets whether a substring occurs at the specified index in string.
///
/// O(N) time.
let private occursAt (start: int) (substr: string) (s: string) : bool =
  let rec occursAtLoop i =
    (i = substr.Length)
    || (s.[start + i] = substr.[i] && occursAtLoop (i + 1))

  (0 <= start && start + substr.Length <= s.Length)
  && occursAtLoop 0

/// Gets whether a string starts with specified substring.
///
/// O(|P|) time, P: prefix.
let startsWith (prefix: string) (s: string) : bool = occursAt 0 prefix s

/// Gets whether a string ends with specified substring.
///
/// O(|S|) time, S: suffix.
let endsWith (suffix: string) (s: string) : bool =
  occursAt (s.Length - suffix.Length) suffix s

/// Finds first index of string where a substring occurs.
///
/// O(NM) time, N: length of substring, M: length of total string.
let findIndex (substr: string) (s: string) : int option =
  // Upper bound of the index that could satisfy the predicate.
  let r = s.Length - substr.Length + 1

  let rec stringFindIndexLoop i =
    if i >= r then None
    else if occursAt i substr s then Some i
    else stringFindIndexLoop (i + 1)

  stringFindIndexLoop 0

/// Finds last index of string where a substring occurs.
///
/// O(NM) time, N: length of substring, M: length of total string.
let findLastIndex (substr: string) (s: string) : int option =
  let rec stringFindLastIndexLoop r =
    if r <= 0 then
      None
    else if occursAt (r - 1) substr s then
      Some(r - 1)
    else
      stringFindLastIndexLoop (r - 1)

  // Upper bound of the index that could satisfy the predicate.
  let r = s.Length - substr.Length + 1

  stringFindLastIndexLoop r

/// Gets whether a substring occurs in a string.
///
/// O(NM) time, N: length of substring, M: length of total string.
let contains (substr: string) (s: string) : bool =
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
/// This function is tolerant about exceeding the boundary.
/// If `prefixLen < 0`, returns `""`.
/// If `prefixLen > s.Length`, returns s itself.
let truncate (prefixLen: int) (s: string) : string =
  if prefixLen <= 0 then ""
  else if prefixLen >= s.Length then s
  else s.[0..prefixLen - 1]

/// Removes a prefix of string by specified length.
///
/// Analogue to `List.skip`.
///
/// This function is tolerant about exceeding the boundary.
/// If `prefixLen < 0`, returns `s` itself.
/// If `prefixLen > s.Length`, returns `""`.
let skip (prefixLen: int) (s: string) : string =
  if prefixLen <= 0 then s
  else if prefixLen >= s.Length then ""
  else s.[prefixLen..s.Length - 1]

/// Gets a contiguous substring in specified range. End index is exclusive.
///
/// Unlike `s.[..]`, this function is tolerant about exceeding the boundary.
/// If `start < 0`, use 0 as start index instead.
/// If `end > s.Length`, use `s.Length` as end index instead.
///
/// O(1) time.
let slice (start: int) (endIndex: int) (s: string) : string =
  let start = start |> intClamp 0 s.Length
  let endIndex = endIndex |> intClamp start s.Length

  if start < endIndex then
    s.[start..endIndex - 1]
  else
    ""

/// Splits a string into two parts at the specified index.
///
/// Index is tolerant.
/// If `i < 0`, use `0`. If `i > s.Length`, use length.
let splitAt (i: int) (s: string) : string * string =
  if i <= 0 then "", s
  else if s.Length <= i then s, ""
  else s.[0..i - 1], s.[i..s.Length - 1]

// -----------------------------------------------
// Trim
// -----------------------------------------------

/// Removes leading and trailing chars that satisfy predicate.
let trimIf (isTrimmed: char -> bool) (s: string) =
  let l =
    let rec stringTrimIfLoop1 (l: int) =
      if l < s.Length && isTrimmed s.[l] then
        stringTrimIfLoop1 (l + 1)
      else
        l

    stringTrimIfLoop1 0

  let r =
    let rec stringTrimIfLoop2 (r: int) =
      if r > l && isTrimmed s.[r - 1] then
        stringTrimIfLoop2 (r - 1)
      else
        r

    stringTrimIfLoop2 s.Length

  if l < r then s.[l..r - 1] else ""

/// Removes leading chars that satisfy predicate.
let trimStartIf (isTrimmed: char -> bool) (s: string) =
  let l =
    let rec stringTrimStartIfLoop (l: int) =
      if l < s.Length && isTrimmed s.[l] then
        stringTrimStartIfLoop (l + 1)
      else
        l

    stringTrimStartIfLoop 0

  if l < s.Length then
    s.[l..s.Length - 1]
  else
    ""

/// Removes trailing chars that satisfy predicate.
let trimEndIf (isTrimmed: char -> bool) (s: string) =
  let r =
    let rec stringTrimEndIfLoop (r: int) =
      if r > 0 && isTrimmed s.[r - 1] then
        stringTrimEndIfLoop (r - 1)
      else
        r

    stringTrimEndIfLoop s.Length

  if r > 0 then s.[0..r - 1] else ""

/// Removes leading and trailing spaces.
let trim (s: string) = s |> trimIf C.isSpace

/// Removes leading spaces.
let trimStart (s: string) = s |> trimStartIf C.isSpace

/// Removes trailing spaces.
let trimEnd (s: string) = s |> trimEndIf C.isSpace

// -----------------------------------------------
// Replace
// -----------------------------------------------

/// Replaces all occurrences of substring with other string.
///
/// If pattern is empty string, just returns `s` itself.
let replace (pattern: string) (target: string) (s: string) =
  let rec replaceLoop acc (i: int) =
    match findIndex pattern (skip i s) with
    | None -> (skip i s) :: acc
    | Some n -> replaceLoop ((s |> skip i |> truncate n) :: acc) (i + n + pattern.Length)

  if pattern.Length = 0 then
    s
  else
    replaceLoop [] 0 |> List.rev |> concat target

// unicode is not supported
let private transformByBytes (f: char -> char) (s: string) : string =
  let rec stringTransformLoop (s: string) =
    if s.Length = 1 then
      string (f s.[0])
    else
      let m = s.Length / 2

      stringTransformLoop s.[0..m - 1]
      + stringTransformLoop s.[m..s.Length - 1]

  if s = "" then
    ""
  else
    stringTransformLoop s

let toLower (s: string) : string = transformByBytes C.toLower s
let toUpper (s: string) : string = transformByBytes C.toUpper s

/// Changes first letter to lowercase (if ASCII uppercase).
let lowerFirst (s: string) : string =
  if s.Length >= 1 && C.isUpper s.[0] then
    string (C.toLower s.[0]) + s.[1..s.Length - 1]
  else
    s

/// Changes first letter to uppercase (if ASCII lowercase).
let upperFirst (s: string) : string =
  if s.Length >= 1 && C.isLower s.[0] then
    string (C.toUpper s.[0]) + s.[1..s.Length - 1]
  else
    s

// -----------------------------------------------
// Split
// -----------------------------------------------

/// Splits a string into two part by separator.
/// Returns `(first, second, ok)`.
///
/// The first occurrence of separator is picked.
let cut (sep: string) (s: string) : string * string * bool =
  match findIndex sep s with
  | None -> s, "", false
  | Some i -> s.[0..i - 1], s.[i + sep.Length..s.Length - 1], true

/// Splits a string into two part by separator.
/// Returns `(first, second, ok)`.
///
/// The *last* occurrence of separator is picked.
let cutLast (sep: string) (s: string) : string * string * bool =
  match findLastIndex sep s with
  | None -> s, "", false
  | Some i -> s.[0..i - 1], s.[i + sep.Length..s.Length - 1], true

/// Splits a string by separator.
///
/// ## Edges
///
/// - `split "," "foo"` is `[ "foo" ]` (not separated)
/// - `split "," ""` is `[ "" ]` too
/// - `split "," "foo,"` is `[ "foo"; "" ]` (trailing separator)
/// - `split "" "foo"` is *unimplemented* (empty separator)
let split (sep: string) (s: string) : string list =
  assert (sep.Length <> 0) // should split at every character boundary

  let rec go acc s =
    let part, s, ok = cut sep s
    let acc = part :: acc
    if ok then go acc s else acc

  go [] s |> List.rev

// Variant of cut.
/// Removes a substring if string starts with it.
/// Returns `(string, ok)`.
let stripStart (prefix: string) (s: string) : string * bool =
  if startsWith prefix s then
    s.[prefix.Length..s.Length - 1], true
  else
    s, false

/// Removes a substring if string ends with it.
/// Returns `(string, ok)`.
let stripEnd (suffix: string) (s: string) : string * bool =
  if endsWith suffix s then
    s.[0..s.Length - suffix.Length - 1], true
  else
    s, false

/// Finds first index of newline. Returns total length if missing.
let private findNewline (start: int) (s: string) =
  let i = start

  if i < s.Length && (s.[i] <> '\r' && s.[i] <> '\n') then
    findNewline (i + 1) s
  else
    i

/// Splits a string into first line and rest.
/// Line ends with a `\r\n`, `\n`, or end of string.
///
/// Returns `(lineContents, rest, newlineOpt)`, where:
///
/// - `lineContents` is the contents of the line.
///     Empty if string starts with newline or is empty.
/// - `rest` is the string after the newline.
///     Empty if it ends with the newline. Otherwise no newline found.
/// - `newlineOpt` is "\n" or "\r\n" (or perhaps "\r"), which is actually found.
let cutLine (s: string) : string * string * string option =
  let m = findNewline 0 s
  let lineContents = if m > 0 then s.[0..m - 1] else ""

  if m = s.Length then
    lineContents, "", None
  else
    let sepLen =
      if (m + 1) < s.Length
         && s.[m] = '\r'
         && s.[m + 1] = '\n' then
        2
      else
        assert (m = s.Length || s.[m] = '\r' || s.[m] = '\n')
        1

    let r = m + sepLen
    let sep = s.[m..r - 1]

    let rest =
      if r < s.Length then
        s.[r..s.Length - 1]
      else
        ""

    lineContents, rest, Some sep

/// Splits a string to lines.
let toLines (s: string) : string list =
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
// Concatenation
// -----------------------------------------------

/// Concatenates a list of strings
/// by inserting a separator between every two items.
///
/// This function is almost same as `String.concat` in F#
/// but takes a list rather than seq, which is unimplemented in milone-lang.
let concat (sep: string) (xs: string list) : string = B.concat sep xs

// -----------------------------------------------
// Formatting
// -----------------------------------------------

let parseHexAsUInt64 (s: string) : uint64 option =
  let rec go acc (i: int) =
    if i = s.Length then
      Some acc
    else if C.isHex s.[i] then
      let d = uint64 (C.evalHex s.[i])

      let overflow =
        let m = uint64 (int64 (-1))
        acc <= (m - uint64 d) / uint64 16

      if overflow then
        go (acc * uint64 16 + d) (i + 1)
      else
        None
    else
      None

  if s.Length <> 0 then
    go (uint64 0) 0
  else
    None

let uint64ToHex (len: int) (value: uint64) =
  assert (len >= 0)

  let rec go acc len (n: uint64) =
    if n = uint64 0 && len <= 0 then
      acc
    else
      let d = int (n % uint64 16)
      let acc = "0123456789abcdef".[d..d] + acc
      let len = if len >= 1 then len - 1 else 0
      let n = n / uint64 16
      go acc len n

  if value = uint64 0 && len = 0 then
    "0"
  else
    go "" len value

// bad implementation
let format (s: string) (args: string list) =
  args
  |> List.fold
       (fun (i, s) arg ->
         let s = s |> replace ("{" + string i + "}") arg
         i + 1, s)
       (0, s)
  |> snd
