# Tokenize

Tokenize is a pass to split source code into a list of tokens as preparation of parsing.

See also [syntax](../refs/syntax.md) and [char type](../refs/char_type.md).

## Motivation

This pass takes over some portion of complexity of parsing.

- Parser wants to use token position (row/column indexes) for the indent-sensitive syntax.
    Token stream pre-computes position so that parser can just retrieve it.
- Parser wants to look ahead.
    Spaces, newlines and comments are obstacles in the view of lookahead.
    Token stream without these tokens are easier to lookahead.

## Input

Input is source code that is typically loaded from single source file.

## Output

Output is *token stream*, a list of token data.
Token data consists of kind, text and position.

There are two variants of tokenize functions:

- one to remove all trivia tokens, which is for parsing,
- one to preserve all tokens, which is useful for LSP analysis.

## Example

```fsharp
let main _ =
  0
```

Token stream is:

| Y:X   | Token     | Text  |
|------:|:-------   |:----- |
|   0:0 | Let       | let   |
|   0:4 | Ident     | main  |
|   0:9 | Ident     | _     |
|  0:11 | Equal     | =     |
|   1:2 | IntLit    | 0     |

## Remarks

### Variables of Position

Row number is denoted by `y`. Column number by `x`.

### Reliability

This pass should *never fail* even when the input is completely invalid.
Tokenization is called by LSP server, when the user is editing code.
The pass should produce a result as possible so that subsequent passes can do something useful.

This pass should also be always fast for the same reason.
