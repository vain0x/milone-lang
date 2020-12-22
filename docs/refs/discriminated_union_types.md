# Discriminated Union Types

Discriminated union type (DU) is a kind of user-defined types.

Note on naming: "discriminated union type" is also known as "algebraic data type (ADT)", "custom type", "enum" (enumeration), "sum type", "tagged union type", "variant", etc. in other communities.

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
