# Syntax

This page describes tokens and grammar.

## Tokens

Category of tokens:

- Number literal tokens
    - Decimal integer tokens (`42`)
        - With suffix (`65u`)
    - Hex integer tokens (`0xca10cafe`)
        - With suffix (`0x80000000u`)
    - Float tokens (`3.14`)
        - With exponential (`1e-9`)
- Character literal tokens (`'a'`)
    - Escaped (`'\x0a'`)
    - Byte (`'a'B`)
- String literal tokens
    - Single-line (`"hey"`)
    - Raw (`"""..."""`)
- Identifiers (`foo`)
    - Keywords (`let`)
    - Reserved F# keywords (`abstract`)
    - Reserved OCaml keywords (`asr`)
    - Reserved words (`break`)
- Type variables (`'T`)
- Punctuation
    - Operator (`+`)
    - Brackets (`(`)

### Number Literal Tokens

A digit is one of ASCII digit letters.

    digit = [0-9]

A hex digit is one of ASCII digits and ASCII hex alphabets (A-F and a-f).

    hex = [0-9A-Fa-f]

A suffix is one or more repetition of ASCII alphabets.

    suffix = [A-Za-z]+

A decimal integer literal consists of optional minus sign, 1+ digits and optional suffix.

    decimal_int_lit = '-'? digit+ suffix?

A hexadecimal integer literal consists of `0x`, 1+ hex digits and optional suffix.

    hex_int_lit = '0x' hex+ suffix?

A floating point number (float) literal consists of optional minus sign, 1+ digits, optional fraction, optional exponent and optional suffix. Either fraction or exponent part must exist (otherwise it's an integer literal.)

    float_lit = '-'? digit+ ('.' digit+)? ([eE] [+-]? digit+)? suffix?

`int_lit` is a group of these integer tokens.
`number_lit` is a group of integer and float literal tokens.
These groups are used in grammar definition later.

    int_lit =
        decimal_int_lit
        | hex_int_lit

    number_lit =
        int_lit
        | float_lit

### Character Literal Tokens

A character literal token is basically single ASCII character enclosed by ASCII single quotes `'`.

`verbatim_char` is a character that can appear inside quotes, which is any ASCII character except for control characters, backslash and single quote.
Note control characters include newlines.

`escape` is a so-called escape sequence to represent an non-verbatim character.
It starts with a backslash and an ASCII alphabet follows.

    verbatim_char = [^\x00-\x1f\x7f\\']

    escape = '\x' hex hex
           | '\n' | '\r' | '\t'
           | '\\' | `\'` | '\"'

    char_lit = "'" (escape | verbatim_char) "'"

Remark: `'\0'` isn't valid.

Character literal may by followed by `B` without any blank.

### String Literal Tokens

A single-line string literal token is basically single-line string enclosed by ASCII double quotes `"`.

`single_verbatim` is a character that can appear inside of quotes, which is any character except for control characters, backslash and double quote.

`escape`, defined above, can also appear inside quotes.

    single_verbatim = [^\x00-\x1f\0x7f\\"]
    single_string_lit = '"' (escape | single_verbatim)* '"'

Raw string literal token is basically string enclosed by `"""`s.
CR (U+000D) and LF (U+000A), which are control characters, can also appear inside quotes.
Unescaped double quotes can appear middle of quotes, except for start and end of contents.
Escape sequences can't be used. Unescaped backslashes are available.

    raw_verbatim = [^\x00-\x09\x0b\x0c\x0e-\x1f\x7f]
    raw_string_lit = '"""' raw_verbatim* '"""'

    string_lit =
        single_string_lit
        | raw_string_lit

Remark: String interpolation (`$""`) isn't supported yet.

Identifiers and strings mustn't appear consecutively with no spaces or newlines. (unchecked yet.)

### Identifiers

An identifier consists of ASCII digits, ASCII alphabets and ASCII underscore `_` except it can't start with a digit.

    w0 = [A-Fa-f_]
    w1 = [0-9A-Fa-f_]

    ident = w0 w1*

### Keywords

Keywords are lexically same as identifiers but can't be used as symbols.

See Syntax.fs for comprehensive list of keywords.

TODO: make an index for keywords and usage like this: [Keyword Reference - F# | Microsoft Docs](https://docs.microsoft.com/en-us/dotnet/fsharp/language-reference/keyword-reference)

### Type variables

A type variable consists of a single quote and single ASCII alphabet.

    ty_var = "'" [A-Za-z]

### Punctuations

Punctuations are operators, brackets and others.

Non-operator punctuations can appear consecutively.
For example, `,,` is two comma tokens.
Operators don't.
`++` is single operator token even though such operator doesn't exist.
This is for compatibility with F#, where custom operators are supported.

TODO: make an index for punctuation and usage like this: [Symbol and Operator Reference - F# | Microsoft Docs](https://docs.microsoft.com/en-us/dotnet/fsharp/language-reference/symbol-and-operator-reference/)

## Grammar

Here is informal grammar of the milone-lang source code.

### Categories of Syntax

Syntax elements are basically categorized to:

- types
- patterns
- expressions
- declarations

and others.

### Types

A type as an element of syntax is defined recursively as follows.

A type variable token is literally a type.

    var_ty = ty_var

An underscore identifier token is a type.

    infer_ty = '_'

An identifier is a type.
It's optionally qualified by any number of qualifiers, separated by dot `.`.
It optionally has type argument list.
Type argument list is 1+ repetition of types, separated by comma `,` and enclosed by angle brackets `<` `>`.
Starting bracket `<` must appear consecutively after the previous token.

    ty_arg_list = '<' ty (',' ty)* '>'
    app_ty = (ident '.')* ident ty_arg_list?

A pair of parentheses that wraps a type is also a type.

    paren_ty = '(' ty ')'

Then, these types are called atomic types.

    atom_ty = var_ty | infer_ty | app_ty | paren_ty

A single identifier can be applied to a type in postfix notation, e.g. `_ list`.
That identifier is called a *suffix*.

    suffix_ty =
        suffix_ty suffix:ident
        | atom_ty

A tuple type is a list of types separated by 1+ `*` operators.
It's non-associative, N-ary operator.

    tuple_ty =
        suffix_ty ('*' ty)+
        | suffix_ty

A function type consists of source type, an `->` operator and destination type in right-associative infix notation.

    fun_ty =
        src:tuple_ty '->' dest:fun_ty
        | tuple_ty

That's type.

    ty = fun_ty

### Patterns

Next, pattern is defined in the same way as type.

Literals are patterns.

    unit_lit = '(' ')'
    bool_lit = 'false' | 'true'

    lit =
        number_lit
        | unit_lit
        | bool_lit
        | char_lit
        | string_lit

    lit_pat = lit

An underscore token is a discard pattern. (Also known as wildcard.)

    discard_pat = '_'

An unqualified identifier is a pattern.
It's either a variable pattern or a variant pattern, depending on whether it's defined as a variant or not.

    variant_pat = ident     (if defined as variant)
    ident_pat = ident       (otherwise)

An identifier that is preceded by an explicit visibility is also a variable pattern.
In this case the identifier mustn't be underscore nor defined as a variant.

    vis = 'public' | 'private'
    vis_ident_pat = vis ident

A qualified identifier is a pattern.

    nav_pat = (ident '.')+ ident

A pair of parentheses that wraps a pattern is also a pattern.

    paren_pat = '(' pat ')'

A list literal is a pattern.
It consists of any number of item patterns, separated by semicolon `;` and enclosed by brackets `[` `]`.
Semicolons can be omit by putting item patterns on the same column.

    list_pat = '[' (pat (';' pat)*)? ']'

These are called atomic pattern.

    atom_pat =
        literal
        | ident_pat
        | discard_pat
        | variant_pat
        | vis_ident_pat
        | nav_pat
        | paren_pat
        | list_pat

A variant pattern consists of a variant pattern that is followed by a payload pattern.

    app_pat =
        variant_pat atom_pat
        | atom_pat

A cons pattern consists of head pattern, `::`, and tail pattern in right-associated infix notation.

    cons_pat =
        head:app_pat '::' tail:cons_pat
        | app_pat

A type ascription pattern consists of a pattern followed by `:` and a type.

    ascribe_pat =
        cons_pat ':' ty
        | cons_pat

A tuple pattern consists of 2+ patterns separated by `,` in non-associative N-ary infix operation.

    tuple_pat =
        ascribe_pat (',' ascribe_pat)+
        | ascribe_pat

An `as` pattern consists of a pattern, `as` keyword and an identifier.
This grammar is less flexible than F#.

    as_pat =
        tuple_pat 'as' ident
        | tuple_pat

An `or` pattern (also known as disjunction) consists of 2+ patterns separated by '|' in non-associative N-ary infix notation.

    or_pat =
        as_pat ('|' as_pat)+
        | as_pat

That's pattern.

    pat = or_pat

### Expressions

Literals are expressions like patterns.

    lit_expr = lit

An identifier is an expression (except for `_`.)
It's optionally qualified.
It optionally has a type argument list, which must appear consecutively without spaces.

    ident_expr = ident ty_arg_list?
    nav_expr = (ident '.')+ ident

Parentheses wrap expressions, separated by semicolon `;`.
Semicolons can be omit by putting subexpressions on the same column.

    block = (expr ';')* expr
    paren_expr = '(' block ')'

A list expression is basically same as a list pattern but for expression.

    list_expr = '[' (expr (';' expr)*)? ']'

A record expression consists of 1+ list of fields, separated by semicolon `;` and enclosed by braces `{` `}`.
Semicolons can be omit by putting fields on the same column.
It optionally has `with` clause.

    record_expr =
        '{' (expr 'with')?
            (ident '=' expr) (';' ident '=' expr)*
        '}'

There are also expressions that start with keyword.

An `if` expression consists of `if` keyword, a condition expression, then clause and an optional else clause.
Subexpressions must be inside of the `if` keyword.
If `else` clause is another `if` expression, its layout is based on the first `if` keyword.

    if_expr = 'if' cond:expr 'then' body:block ('else' alt:(if_expr | block))?

A match expression consists of `match` keyword, a condition expression and 1+ *arms*.
An arm starts with a pipe `|` except for the first one and contains a pattern, optional guard expression and a body expression.
Subexpressions must be inside of the `match` keyword.

    arm = pat (when guard:expr)? '->' body:block

    match_expr =
        'match' cond:expr 'with'
        '|'? arm
        ('|' arm)*

A function expression (a.k.a. closure or lambda) consists of a `fun` keyword, 1+ list of parameter patterns, `->` and a body expression.
Parameter patterns and the body must be inside of the `fun` keyword.

    fun_expr = 'fun' pat+ -> block

Let expressions have two categories: let-val and let-fun.
`in` keyword can be omit by putting `next` on the same column as the `let` keyword.

    let_val_expr = 'let' pat '=' init:block 'in' next:block

    let_fun_expr = 'let' 'rec'? vis? ident pat+ '=' body:block 'in' next:block

Those are called atomic expressions.

    atom_expr =
        lit_expr
        | ident_expr
        | nav_expr
        | paren_expr
        | list_expr
        | record_expr
        | if_expr
        | match_expr
        | fun_expr
        | let_val_expr
        | let_fun_expr

A suffix expression is either a field access, an index access or a slice operation.

    suffix_expr =
        suffix_expr '.' ident
        | suffix_expr '.' '[' expr ']'
        | suffix_expr '.' '[' expr '..' expr ']'
        | atom_expr

Remark: Dot-less index syntax isn't supported yet.

A functional application expression is just two expressions separated by 1+ spaces.
Argument expression must be inside of the callee expression.

    app_expr =
        callee:app_expr arg:suffix_expr
        | suffix_expr

A prefix expression consists of a operator and an argument expression.
Operator and expression must appear consecutively without spaces so that the operator is distinct from a binary operator.

    prefix_expr = ('-' | '&&' | '~~~') app_expr

A binary operator consists of two expressions separated by an operator.
Precedence from higher to lower:

| Name  | Operators                 | Associativity |
|:------|:--------------------------|:------|
| mul   | \* / %                    | Left  |
| add   | \+ -                      | Left  |
| cons  | ::                        | Right |
| xor   | ^^^                       | Left  |
| sigil | \< \> = \|> \|\|\| &&&    | Left  |
| and   | &&                        | Left  |
| or    | \|\|                      | Left  |

Note the sigil layer also contains `<= >= <> <<< >>>`.

    binary_op = '*' | '/' | etc.

    binary_expr =
        binary_expr binary_op binary_expr
        | prefix_expr

A tuple expression consists of 2+ expressions separated by `,`.

    tuple_expr =
        binary_expr (',' binary_expr)+
        | binary_expr

A type ascription expression consists of an expression followed by a type.

    ascribe_expr =
        tuple_expr ':' ty
        | tuple_expr

That's expression.

    expr = ascribe_expr

### Declarations

An expression is a declaration.

    expr_decl = expr

Let declarations are similar to let expressions but don't have `in` clause.

    let_val_decl = 'let' pat '=' init:block

    let_fun_decl = 'let' 'rec'? vis? ident pat+ '=' body:block

Type declarations have various forms.
Left-hand side is same in all forms.

A type declaration optionally has a type parameter list.
The angle bracket must appear consecutively after the identifier without spaces.

    xxx_ty_decl = 'type' vis? ident ty_param_list? '=' ...
    ty_param_list = '<' ty_var (',' ty_var)* '>'

A type synonym declaration takes a type in right-hand side.

    ty_synonym_decl =
        'type' vis? ident ty_param_list? '=' ty

A discriminated union type declaration takes 1+ variants separated by pipe `|` in right-hand side.
Initial pipe is optional except it looks like `type U = | V`.
Each variant optionally has a payload type.
A payload type is basically a tuple type but each item type can optionally have a label.

    payload_ty = (ident ':')? ty ('*' (ident ':')? ty)*

    union_ty_decl =
        'type' vis? ident ty_param_list? '='
        vis?
         '|'? ident ('of' payload_ty)?
        ('|'  ident ('of' payload_ty)?)*

A record type declaration has 1+ fields separated by semicolon and enclosed by braces in right-hand side.
Semicolons can be omit by putting fields on the same column.

    record_ty_decl =
        'type' vis? ident ty_param_list? '='
        vis?
        '{' (ident ':' ty) (';' ident ':' ty)* '}'

An open declaration:

    open_decl = 'open' (ident '.')* ident

Module declarations have two forms.
A module synonym declaration has module path in right-hand side.

    module_synonym_decl =
        'module' ident '=' (ident '.')* ident

A (non-synonym) module declaration has 1+ declarations separated by semicolon `;` in right-hand side.
Semicolons can be omit by putting subdeclarations on the same column.
Subdeclarations must be inside of the `module` keyword.

    module_decl =
        'module' 'rec'? ident '='
            decl (';'+ decl)*

That's declaration.

    decl =
        expr_decl
        | let_val_decl
        | let_fun_decl
        | ty_synonym_decl
        | union_ty_decl
        | record_ty_decl
        | open_decl
        | module_synonym_decl
        | module_decl

### Root

Root of parse tree optionally has module head and contains 1+ declarations separated by semicolon `;`.
Semicolons can be omit by putting declarations on the same column.

    head = 'module' 'rec' ident '.' ident

    root = head? (decl (';'+ decl)*)?

----

## Notes

- TODO: explain more about indentation rule

Remark: Indentation rule isn't equivalent to F# lightweight syntax.
