module rec Std.StdChar

/// Subtracts char codes.
let subtract (l: char) (r: char) : char = char (byte l - byte r)

/// Gets whether a char is in ASCII range.
let isAscii (c: char) : bool = byte c <= 0x7fuy

// -----------------------------------------------
// Char class checks
// -----------------------------------------------

// These functions should be compatible with functions from <ctype.h> in the C language.
// See: https://en.cppreference.com/w/c/string/byte

let isControl (c: char) : bool = (byte c <= 31uy) || c = '\x7f'

let isBlank (c: char) : bool = c = ' ' || c = '\t'

let isSpace (c: char) : bool =
  (byte '\t' <= byte c && byte c <= byte '\r')
  || c = ' '

let isPunctuation (c: char) : bool =
  let n = byte c

  (33uy <= n && n <= 47uy)
  || (58uy <= n && n <= 64uy)
  || (91uy <= n && n <= 96uy)
  || (123uy <= n && n <= 126uy)

let isDigit (c: char) : bool =
  byte '0' <= byte c && byte c <= byte '9'

let isHex (c: char) : bool =
  isDigit c
  || (byte 'A' <= byte c && byte c <= byte 'F')
  || (byte 'a' <= byte c && byte c <= byte 'f')

let isLower (c: char) : bool =
  byte 'a' <= byte c && byte c <= byte 'z'

let isUpper (c: char) : bool =
  byte 'A' <= byte c && byte c <= byte 'Z'

let isAlphabetic (c: char) : bool = isUpper c || isLower c

let isAlphanumeric (c: char) : bool = isDigit c || isAlphabetic c

let toUpper (c: char) : char =
  if isLower c then
    subtract c 'a' + 'A'
  else
    c

let toLower (c: char) : char =
  if isUpper c then
    subtract c 'A' + 'a'
  else
    c

// -----------------------------------------------
// Other
// -----------------------------------------------

let evalDigit (c: char) : int =
  assert (isDigit c)
  int (byte c - byte '0')

let evalHex (c: char) : int =
  if isDigit c then
    int (byte c - byte '0')
  else if isLower c then
    assert (byte c <= byte 'f')
    int (byte c - byte 'a') + 10
  else
    assert (isUpper c && byte c <= byte 'F')
    int (byte c - byte 'A') + 10
