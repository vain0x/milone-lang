# Syntax

This page describes tokens and grammar.

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

    decimal_int_lit = '-'? digit+ suffix?

A hexadecimal integer literal consists of `0x`, 1+ hex digits and optional suffix.

    hex_int_lit = '0x' hex+ suffix?

A floating pointer number (float) literal consists of option minus sign, 1+ digits, optional fraction, optional exponent and optional suffix. Either fraction and exponent must exist (otherwise it's integer.)

    float_lit = '-'? digit+ ('.' digit+)? ([eE] [+-]? digit+)? suffix?

Let's make a group of these tokens for grammar.

    int_lit =
        decimal_int_lit
        | hex_int_lit

    number_lit =
        int_lit
        | float_lit

Remark: Number literals can't interleave `_`s for now. Hex floats are unsupported yet.

### Character Literal Tokens

Character literal token is basically single unicode character enclosed by ASCII single quotes `'`.

Control character, backslash and single quote can't appear between quotes.
Escape sequence can be used instead.

    verbatim_char = [^\x00-\x1f\x7f\\']

    escape = '\x' hex hex
           | '\n' | '\r' | '\t'
           | '\\' | `\'` | '\"'

    char_lit = "'" (escape | verbatim_char) "'"

Remark: `'\0'` isn't valid. Unicode escape sequence is unsupported yet.

### String Literal Tokens

Single-line string literal token is basically single line string enclosed by ASCII double quotes `"`.

Control characters, backslash and double quotes can't appear between quotes.
Escape sequences can be used.

    string_verbatim = [^\x00-\x1f\0x7f\\"]
    single_string_lit = '"' (escape | string_verbatim)* '"'

Raw string literal token is basically string enclosed by `"""`s.
CR (0x0d) and LF (0x0a), which are control characters, can also used between these quotes.
Unescaped double quotes can appear between these quotes, except for start and end of contents.
Escape sequences can't be used and therefore unescaped backslashes are available.

    raw_verbatim = [^\x00-\x09\x0b\x0c\x0e-\x1f\x7f]
    raw_string_lit = '"""' raw_verbatim+ '"""'

    string_lit =
        single_string_lit
        | raw_string_lit

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

Here is informal grammar of milone-lang source code.

### Categories of Syntax

Syntax elements are basically categorized to:

- types
- patterns
- expressions
- declarations

and others.

### Types

Type variable token is literally a type.

    var_ty = ty_var

Underscore (an identifier token) is a type to be inferred.

    infer_ty = '_'

Basically, identifier is a type.
It's optionally qualified by any number of qualifiers, separated by dot `.`.
It optionally has type argument list.
Type argument list is 1+ repetition of types, separated by comma `,` and enclosed by angle brackets `<` `>`.

    ty_arg_list = '<' ty (',' ty)* '>'
    app_ty = (ident '.')* ident ty_arg_list?

Parentheses wrap a type.

    paren_ty = '(' ty ')'

Those are called atomic types.

    atom_ty = var_ty | infer_ty | app_ty | paren_ty

Single identifier can be applied to a type in postfix notation, e.g. `_ list`.)
Note `suffix` in `suffix:ident` is a label of that part.

    suffix_ty =
        suffix_ty suffix:ident
        | atom_ty

Tuple types and function types have operator-like syntax.
Tuple type constructor `*` is non-associative N-arity operator.

    tuple_ty =
        suffix_ty ('*' ty)+
        | suffix_ty

Function type constructor `->` is right-associative binary operator.

    fun_ty =
        tuple_ty '->' fun_ty
        | tuple_ty

That's type.

    ty = fun_ty

### Patterns

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

Underscore is a discard pattern. (Also known as wildcard.)

    discard_pat = '_'

Unqualified identifier is a pattern.
It's either a variable pattern or a variant pattern, depending on whether it's defined as a variant or not.

    variant_pat = ident     (when it's defined as variant)
    ident_pat = ident       (otherwise)

Identifier that is preceded by an explicit visibility is also a variable pattern.

    vis = 'public' | 'private'
    vis_ident_pat = vis ident

Qualified identifier is a pattern.

    nav_pat = (ident '.')+ ident

Parentheses wrap a pattern.

    paren_pat = '(' pat ')'

List literal is a pattern.
It consists of any number of subpatterns, separated by semicolon `;` and enclosed by brackets `[` `].
Semicolons can be omit by putting subpatterns on the same column.

    list_pat = '[' (pat (';' pat)*)? ']'

Those are called atomic pattern.

    atom_pat =
        literal
        | ident_pat
        | discard_pat
        | variant_pat
        | vis_ident_pat
        | nav_pat
        | paren_pat
        | list_pat

Variant pattern followed by a payload pattern is a pattern.

    app_pat =
        atom_pat atom_pat
        | atom_pat

Cons (`::`) is a binary operator for patterns.

    cons_pat =
        app_pat '::' app_pat
        | app_pat

Type ascription pattern:

    ascribe_pat =
        cons_pat ':' ty
        | cons_pat

Tuple pattern is non-associative N-ary operator.

    tuple_pat =
        ascribe_pat (',' ascribe_pat)+
        | ascribe_pat

AS pattern (incompatible with F#):

    as_pat =
        tuple_pat ('as' tuple_pat)
        | tuple_pat

OR pattern:

    or_pat =
        as_pat ('|' as_pat)+
        | as_pat

That's pattern.

    pat = or_pat

### Expressions

Literals are expressions like patterns.

    lit_expr = lit

Identifier is an expression (except for `_`.)
It's optionally qualified.

    ident_expr = ident
    nav_expr = (ident '.')+ ident

Remark: Type argument list for expression is unsupported yet.

Parentheses wrap expressions, separated by semicolon `;`.
Semicolons can be omit by putting subexpressions on the same column.

    block = (expr ';')* expr
    paren_expr = '(' block ')'

List expression is basically same as list pattern but for expression.

    list_expr = '[' (expr (';' expr)*)? ']'

Record expression is 1+ list of fields, separated by semicolon `;`.
Semicolons can be omit by putting fields on the same column.
It optionally contains `with` clause.

    record_expr =
        '{' (expr 'with')?
            (ident '=' expr) (';' ident '=' expr)*
        '}'

There are also expressions that start with keyword.

If expression consists of a condition expression, then clause and optional else clause.
Subexpressions must be inside of the `if` keyword.
If `else` clause is another if expression, its layout is based on the first `if` keyword.

    if_expr = 'if' cond:expr 'then' body:block ('else' alt:(if_expr | block))?

Match expression consists of a condition expression and *arms*.
Arm starts with a pipe `|` except for the first one.
Subexpressions must be inside of the `match` keyword.

    arm = pat (when guard:expr)? '->' block

    match_expr =
        'match' cond:expr 'with'
        '|'? arm
        ('|' arm)*

Function expression (a.k.a. closure, lambda.)
Parameter patterns and body expression must be inside of the `fun` keyword.

    fun_expr = 'fun' pat+ -> block

Let expression have two form: let-val and let-fun.
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

Suffix expression is either field access, index access or slice.

    suffix_expr =
        suffix_expr '.' ident
        | suffix_expr '.' '[' expr ']'
        | suffix_expr '.' '[' expr '..' expr ']'
        | atom_expr

Remark: Dot-less index syntax is unsupported yet.

Putting two expressions form a function application expression.

    app_expr =
        app_expr suffix_expr
        | suffix_expr

Unary operators. It's distinct from infix notation by putting the operator in front of argument with no space between them.

    prefix_expr = ('-' | '&&') app_expr

Binary operators. Precedence from higher to lower:

| Name  | Operators                 | Associativity |
|:------|:--------------------------|:------|
| mul   | \* / %                    | Left  |
| add   | \+ -                      | Left  |
| cons  | ::                        | Right |
| xor   | ^^^                       | Left  |
| sigil | \< \> = \|> \|\|\| &&&    | Left  |
| and   | &&                        | Left  |
| or    | \|\|                      | Left  |

    binary_op = '*' | '/' | etc.

    binary_expr =
        binary_expr binary_op binary_expr
        | minus_expr

Tuple expression.

    tuple_expr =
        binary_expr (',' binary_expr)+
        | binary_expr

Type ascription expression.

    ascribe_expr =
        tuple_expr ':' ty
        | tuple_expr

That's expression.

    expr =
        atom_expr
        | suffix_expr
        | app_expr
        | minus_expr
        | binary_expr
        | tuple_expr
        | type_ascribe_expr

### Declarations

Expression is a declaration.

    expr_decl = expr

Let declarations are similar to let expressions but don't have `in` clause.

    let_val_decl = 'let' pat '=' init:expr

    let_fun_decl = 'let' 'rec'? vis? ident pat+ '=' body:expr

Type declarations have various forms.
Left-hand side is same in all forms.
Type declaration optionally has a type parameter list.

    ty_param_list = '<' ty_var (',' ty_var)* '>'

Synonym type declaration has a type in right-hand side.

    synonym_ty_decl =
        'type' vis? ident ty_param_list? '=' ty

Union type declaration has 1+ variants separated by pipe `|`, in right-hand side.
Initial pipe is optional except when it has single variant and the variant doesn't payload (i.e. `type U = V` is rejected.)
Each variant optionally has payload type.
Payload type is basically a tuple type.
Item types are optionally labelled.

    payload_ty = (ident ':')? ty ('*' (ident ':')? ty)*

    union_ty_decl =
        'type' vis? ident ty_param_list? '='
         '|'? ident ('of' payload_ty)?
        ('|'  ident ('of' payload_ty)?)*

Record type declaration has 1+ fields, separated by semicolon and enclosed by braces, in right-hand side.
Semicolons can be omit by putting fields on the same column.

    record_ty_decl =
        'type' vis? ident ty_param_list? '='
        '{' (ident ':' ty) (';' ident ':' ty)* '}'

Open declaration:

    open_decl = 'open' (ident '.')* ident

Module declaration have two forms.
Module synonyms declaration has module path in right-hand side.

    module_synonym_decl =
        'module' ident '=' (ident '.')* ident

Module declaration has 1+ declarations separated by semicolon `;` in right-hand side.
Semicolons can be omit by putting subdeclarations on the same column.
Subdeclarations must be inside of the `module` keyword.

    module_decl =
        'module' 'rec'? ident '='
            decl (';'+ decl)*

That's declaration.

    decl =
        expr_decl
        let_val_decl
        | let_fun_decl
        | synonym_ty_decl
        | union_ty_decl
        | record_ty_decl
        | open_decl
        | module_synonym_decl
        | module_decl

### Root

Root of parse tree optionally has module head and contains 1+ declarations separated by semicolon `;`.
Semicolons can be omit by putting declarations on the same column.
These declarations can be on the same column as module head.

    head = 'module' 'rec' ident '.' ident

    root =
        head?
        (decl (';'+ decl)*)?

----

## Notes

- TODO: explain more about indentation rule

Remark: Indentation rule isn't equivalent to F# lightweight syntax.
