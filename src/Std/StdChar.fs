module rec Std.StdChar

/// Gets whether a char is in ASCII range.
let isAscii (c: char) : bool = uint c <= 0x7fu

// -----------------------------------------------
// Char class checks
// -----------------------------------------------

// These functions should be compatible with functions from <ctype.h> in the C language.
// See: https://en.cppreference.com/w/c/string/byte

let isControl (c: char) : bool = (uint c <= 31u) || c = '\x7f'

let isBlank (c: char) : bool = c = ' ' || c = '\t'

let isSpace (c: char) : bool =
  ('\t' <= c && c <= '\r')
  || c = ' '

let isPunctuation (c: char) : bool =
  let n = uint c

  (33u <= n && n <= 47u)
  || (58u <= n && n <= 64u)
  || (91u <= n && n <= 96u)
  || (123u <= n && n <= 126u)

let isDigit (c: char) : bool =
  '0' <= c && c <= '9'

let isHex (c: char) : bool =
  isDigit c
  || ('A' <= c && c <= 'F')
  || ('a' <= c && c <= 'f')

let isLower (c: char) : bool =
  'a' <= c && c <= 'z'

let isUpper (c: char) : bool =
  'A' <= c && c <= 'Z'

let isAlphabetic (c: char) : bool = isUpper c || isLower c

let isAlphanumeric (c: char) : bool = isDigit c || isAlphabetic c

let toUpper (c: char) : char =
  if isLower c then
    char(uint c - uint 'a' + uint 'A')
  else
    c

let toLower (c: char) : char =
  if isUpper c then
    char(uint c - uint 'A' + uint 'a')
  else
    c

// -----------------------------------------------
// Conversion
// -----------------------------------------------

let toUInt16 (c: char) : uint16 = uint16 c
let ofUInt16 (n : uint16) : char = char n

// -----------------------------------------------
// Other
// -----------------------------------------------

let evalDigit (c: char) : int =
  assert (isDigit c)
  int c - int '0'

let evalHex (c: char) : int =
  if isDigit c then
    int c - int '0'
  else if isLower c then
    assert (c <= 'f')
    int c - int 'a' + 10
  else
    assert (isUpper c && c <= 'F')
    int c - int 'A' + 10
