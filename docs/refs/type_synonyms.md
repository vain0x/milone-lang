# Type Synonyms

*Type synonym* is a kind of user-defined types.

## Instant usage

```fsharp
// Define type.
type RowIndex = int

let getRowText (row: RowIndex) (text: string) : string =
    //               ^ Use as a type
    "<row'th line in t>"
```

## Guide-level explanation

Type declaration like below defines a type synonym.

```fsharp
type TypeName = UnderlyingType
```

Example:

```fsharp
type RowIndex = int
```

`RowIndex` is a type name.
It's the same type as `int` written in the right-hand side.
That type is called *underlying type*.

### Type check

Type synonym is *same* as the underlying type.
These types are interchangable.

```fsharp
let intValue : int = 1

// This assigns an int value to a vaiable of RowIndex type, which is okay.
let rowIndex : RowIndex = intValue
```

### Typical usage

Type synonym is useful when a type (say, `int`) is used for multiple purposes.
Name of type synonym adds information for the reader of code.

```fsharp
type RowIndex = int
type ColumnIndex = int
```

### Generics

Type synonyms can be parameterized over types. (Same as other nominal types.)
Such types are called *generic synonym types*.

Example:

```fsharp
type EqualFun<'T> = ('T * 'T) -> int

let equalTwo (equals: EqualFun<int>) x1 x2 y1 y2 =
    equals x1 y1 && equals x2 y2
```

## Advanced topics

### Naming

Type synonyms are also known as type abbreviations in F#, type aliases in Rust. `typedef` in C.

### Cyclic type synonyms

Cyclic definitions are forbidden.

```fsharp
// NG: Recursive.
type Maybe<'T> = Maybe<'T> option

// NG: Mutually recursive.
type A = B
type B = A
```

Directly self-recursive type synonym is also forbidden.
In F#, it's parsed as a declaration of a discriminated union type.

```fsharp
// This is rejected in milone-lang.
type X = X

// In F#, the above declaration is equivalent to:
type X =
    | X
```

### Elimination of type synonyms

Type synonyms are all substituted to underlying types after type check.
