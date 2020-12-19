module rec MiloneStd.StdChar

/// Subtracts char codes.
let subtract (l: char) (r: char): char = char (int l - int r)

/// Gets whether a char is in ASCII range, i.e. `0x00 <= c <= 0x7f`.
let isAscii (c: char): bool = '\x00' <= c && c <= char 127

// -----------------------------------------------
// Char class checks
// -----------------------------------------------

// These functions should be compatible with functions from <ctype.h> in the C language.
// See: https://en.cppreference.com/w/c/string/byte

let isControl (c: char): bool =
  let n = int c
  (0 <= n && n <= 31) || n = 127

let isBlank (c: char): bool = c = ' ' || c = '\t'

let isSpace (c: char): bool = ('\t' <= c && c <= '\r') || c = ' '

let isPunctuation (c: char): bool =
  let n = int c
  (33 <= n && n <= 47)
  || (58 <= n && n <= 64)
  || (91 <= n && n <= 96)
  || (123 <= n && n <= 126)

let isDigit (c: char): bool = '0' <= c && c <= '9'

let isHex (c: char): bool =
  isDigit c
  || ('A' <= c && c <= 'F')
  || ('a' <= c && c <= 'f')

let isUpper (c: char): bool = 'A' <= c && c <= 'Z'

let isLower (c: char): bool = 'a' <= c && c <= 'z'

let isAlphabetic (c: char): bool = isUpper c || isLower c

let isAlphanumeric (c: char): bool = isDigit c || isAlphabetic c

let toUpper (c: char): char =
  if isLower c then subtract c 'a' + 'A' else c

let toLower (c: char): char =
  if isUpper c then subtract c 'A' + 'a' else c
