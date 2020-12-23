# Discriminated Union Types

Discriminated union type (DU) is a kind of user-defined types.

## Instant usage

```fsharp
// Define type and variants.
type Customer =
    | Guest
    | Member of id: int

// Create value.
let john = Member 1

// Decompose value.
match john with
| Guest -> assert false
| Member id -> assert (id = 1)
```

## Basic usage

### Constant variants

Type declaration defines a discriminated union type. Discriminated union consists of any number of variants, separated by `|`s.

```fsharp
type TypeName =
    | Variant1
    | Variant2
    | ...
```

Example:

```fsharp
type CustomerKind =
    | Guest
    | Member
```

`CustomerKind` is type name. `Guest` and `Member` are *variants*. `Guest` and `Member` are constant values of `CustomerKind` type.

```fsharp
    // `Guest` is a value. You can assign it to a variable.
    let kind = Guest
```

On the contrary, a value of `CustomerKind` is either `Guest` or `Member`. That's all. This is similar to `bool` type.

When a function takes a parameter of `CustomerKind` type, there only exists two possibilities: the parameter is `Guest` or `Member`. To compute something depending on the parameter, use match expression to handle every possibility.

```fsharp
    let isGuest (kind: CustomerKind): bool =
        match kind with
        | Guest -> true
        | Member -> false

    assert (isGuest Guest)
    assert (not (isGuest Member))
```

### Value-carrying variants

Variants can have some fields.

```fsharp
type TypeName =
    | ValueCarryingVariant1 of field1: Type1 * field2: Type2 * ...
    // and other variants...
```

Example:

```fsharp
type Customer =
    | Guest
    | Member of memberId: int * memberName: string
```

`Member` has fields called `memberId` and `memberName`. To create a value of `Member`, feed these values.

```fsharp
    let john = Member (1, "John Doe")
```

To handle the case of value-carrying variants, variant in arm can take some "parameter".

```fsharp
    let greetMessage (customer: Customer): string =
        match kind with
        | Guest -> "Hello!"
        | Member (id, name) ->
            "Hi, " + name  + "!"

    assert (greetMessage Guest = "Hello!")

    let john = Member (1, "John Doe")
    assert (greetMessage john = "Hi, John Doe!")
```

## Notes on name of parts

- "discriminated union type" is also known as "algebraic data type (ADT)", "custom type", "enum" (enumeration), "sum type", "tagged union type", "variant", etc. in other communities.
- "variant" is also known as "case", "constructor", etc.

In the milone-lang implementation and documentation, I use terms as below:

```fsharp
    | Member of id: int * name: string
//    ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
//    Member *variant*

    | Member of id: int * name: string
//    ^^^^^^
//    *Tag* of Member variant

    | Member of id: int * name: string
//              ^^^^^^^^^^^^^^^^^^^^^^
//              *Payload* of Member variant

    | Member of id: int * name: string
//              ^^^^^^^
//              First *field* of Member variant
```

"Payload" is same as "field list", but "field list" sounds it relates to record types. I prefer to use "payload" for discriminated unions.

If a variant is declared without `of` clause, its payload is empty. Its payload type if `unit`. It has no fields.

Each variant is associated with an integer. The value is called *discriminant* of the variant.

## Runtime representation

(The runtime representation of discriminated union types is unlikely stabilized. FFI codes shouldn't rely on the layout.)

Currently, discriminated union type is converted to a struct. It consists of a pair of tag and payload. Tag is an enum of discriminants. Payload is (an anonymous union of) pointer to payload type.

Example:

```fsharp
type Customer =
    | Guest
    | Member of memberId: int * memberName: string
```

```c
enum CustomerTag {
    Guest,
    Member,
};

// int * string
struct IntStringPair {
    int t0;
    struct String t1;
};

struct Customer {
    enum CustomerTag tag_;
    union {
        struct IntStringPair const *member_;
    };
};
```
