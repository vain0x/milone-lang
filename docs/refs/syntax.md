# Syntax

## Tokens

Category of tokens:

- Number literal tokens
    - Decimal integer tokens (`42`)
        - with suffix (`65u`)
    - Hex integer tokens (`0xca10cafe`)
        - with suffix (`0x80000000u`)
    - Float tokens (`3.14`)
        - exponential (`1e-9`)
- Character literal tokens (`'a'`)
    - escaped (`'\x0a'`)
- String literal tokens
    - single line (`"hey"`)
    - raw (`"""..."""`)
- Identifiers (`foo`)
    - Keywords (`let`)
    - Reserved F# keywords (`abstract`)
    - Reserved OCaml keywords (`asr`)
    - Reserved words (`atomic`)
- Type variables (`'T`)
- Punctuation
    - Operator (`+`)
    - Brackets (`(`)

### Number Literal Tokens

A digit is one of ASCII digit letters.

    digit = [0-9]

A hex digit is one of ASCII digits and ASCII alphabets in the A-F range.

    hex = [0-9A-Fa-f]

A suffix is one or more repetition of ASCII alphabets.

    suffix = [A-Za-z]+

A decimal integer literal consists of optional minus sign, 1+ digits and optional suffix.

    decimal_int = '-'? digit+ suffix?

A hexadecimal integer literal consists of `0x`, 1+ hex digits and optional suffix.

    hex_int = '0x' hex+ suffix?

A floating pointer number (float) literal consists of option minus sign, 1+ digits, optional fraction, optional exponent and optional suffix. Either fraction and exponent must exist (otherwise it's integer.)

    float = '-'? digit+ ('.' digit+)? ([eE] [+-]? digit+)? suffix?

Remark: Number literals can't interleave `_`s for now. Hex floats are unsupported yet.

### Character Literal Tokens

Character literal token is basically single unicode character enclosed by ASCII single quotes `'`.

Control character, backslash and single quote can't appear between quotes.
Escape sequence can be used instead.

    verbatim_char = [^\x00-\x1f\x7f\\']

    escape = '\x' hex hex
           | '\n' | '\r' | '\t'
           | '\\' | `\'` | '\"'

    char_literal = "'" (escape | verbatim_char) "'"

Remark: `'\0'` isn't valid. Unicode escape sequence is unsupported yet.

### String Literal Tokens

Single-line string literal token is basically single line string enclosed by ASCII double quotes `"`.

Control characters, backslash and double quotes can't appear between quotes.
Escape sequences can be used.

    string_verbatim = [^\x00-\x1f\0x7f\\"]
    string_literal = '"' (escape | string_verbatim)* '"'

Raw string literal token is basically string enclosed by `"""`s.
CR (0x0d) and LF (0x0a), which are control characters, can also used between these quotes.
Unescaped double quotes can appear between these quotes, except for start and end of contents.
Escape sequences can't be used and therefore unescaped backslashes are available.

    raw_verbatim = [^\x00-\x09\x0b\x0c\x0e-\x1f\x7f]
    raw_string_literal = '"""' raw_verbatim+ '"""'

Remark: String interpolation (`$""`) are unsupported yet.

Identifiers and strings must not appear consecutively without spaces or newlines. (unchecked yet.)

### Identifiers

Identifiers consist of ASCII digits, ASCII alphabets and ASCII underscore `_`.
Identifier can't start with a digit.

    w0 = [A-Fa-f_]
    w1 = [0-9A-Fa-f_]

    ident = w0 w1*

### Keywords

Keywords are lexically identifiers but can't be used as symbols.

See Syntax.fs for comprehensive list of keywords.

TODO: make an index for keywords and usage like this: [Keyword Reference - F# | Microsoft Docs](https://docs.microsoft.com/en-us/dotnet/fsharp/language-reference/keyword-reference)

### Type variables

Type variable is an identifier that is prefixed by a single quote.
Currently type variable must be single alphabet.

    ty_var = "'" [A-Za-z]

### Punctuations

Punctuations are operators and others.

Non-operator punctuations can appear consecutively. For example, `,,` are two comma tokens. Operators don't. `++` is single operator token event hough such operator doesn't exist. This is for compatibility with F#, where custom operators are supported.

TODO: make an index for punctuation and usage like this: [Symbol and Operator Reference - F# | Microsoft Docs](https://docs.microsoft.com/en-us/dotnet/fsharp/language-reference/symbol-and-operator-reference/)

## Grammar

TODO: write grammar
