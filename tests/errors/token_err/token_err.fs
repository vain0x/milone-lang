// Tokenization errors.

// undefined operator
2&&&-3

// reserved word (F# keyword)
class

// reserved word (OCaml keyword)
sig

// reserved word (F# reserved word)
trait

// invalid characters outside of comments/quotes
こんにちは〜！

// unimplemented: int with suffix
1L

// unknown number suffix
9mm

// unknown escape sequence in char literal
'\m'

// unknown escape sequence in string literal
"\+"

// unimplemented: hex escape
"\x7f"

// invalid hex escape
"\x--"

// Note 'unclosed... is tokenized as type variable ('T).
'+unclosed char literal

"unclosed string literal

"""unclosed raw string literal
