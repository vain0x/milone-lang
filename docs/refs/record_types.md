# Record types

Record type is one of user-defined types. It represents some specific group of values.

## Instant usage

```fsharp
// Declare Person record type.
// (Nominal, immutable. Allocation is decided by compiler.)
type Person =
    { Name: string
      Age: int }

// Create a record.
// (Type annotations is required.)
let john: Person =
    { Name = "John Doe"
      Age = 18 }

// Read a field of record.
// (Record type must be annotated somewhere above.)
assert (john.Name = "John Doe")

// Update a record.
let agedJohn =
    { john with
        Age = john.Age + 1 }

assert (agedJohn.Age = 19)
```

## Guide-level explanation

### Record type declaration

Type declaration defines a record type. Record consists of any number of fields. Each field has name and type.

```fsharp
type Person =
    { Name: string
      Age: int }
```

In the example, `Person` is name of record type. `Name` and `Age` are fields of the Person record type.

### Record creation

A value of Person type is a exhaustive mapping from fields to values. Record expression `{ .. }` creates a record from specified assignment.

```fsharp
    { FieldName1 = fieldInitializer1
      FieldName2 = fieldInitializer2
      ... }
```

```fsharp
let john: Person =
    { Name = "John Doe"
      Age = 18 }
```

Field names must be aligned on the same column and indented deeper than `{`. While record expression doesn't specify its type, **the record type must be inferred** [^1].

[^1]: The limitation is same as require-qualified-access records in F#, but milone-lang compiler is less clever to infer record types. You always need type annotation for record expression.

In record creation (without `with` clause described later), every field must have initializer.

```fsharp
    let namelessOne: Person =
        { Age = 20 }
//      ^ ERROR: Value of Name is unspecified.
```

On the contrary, redundant field is error.

```fsharp
    let nonPerson: Person =
        { Name = "Tanaka Taro"
          Age = 20
          From = "Japan" }
//        ^ ERROR: Person doesn't have From field.
```

### Field access

Field is accessible with dot notation like this.

```fsharp
    assert (john.Name = "John Doe")
```

### Record update

Sometimes you want to create a record, whose value is almost same as existing one. Optional `with` clause in record expression specifies a "base" record to fill values of unspecified fields. This is called *immutable update* of record.

```fsharp
// This is same as { Age = john.Age + 1; Name = joh.Name }.
let agedJohn =
    { john with
        Age = john.Age + 1 }

assert (agedJohn.Name = "John Doe")
assert (agedJohn.Age = 19)
```

## Detailed explanation

### Type inference of records

Current implementation of type inference is subtle on records.

Currently, the record expression must have record type explicitly. To avoid type error, write type annotation around record expressions like this:

```fsharp
    // Record expression itself has type annotation.
    { ... }: RecordType

    // Type of base record expression is explicitly annotated.
    let baseExpr: RecordType = { ... }
    let newExpr = { baseExpr with ... }

    // Assign record expression to variable with type annotation.
    let x: RecordType = { ... }

    // Pass record expression in a parameter with type annotation.
    // The function must be defined before the record expression.
    let f (x: RecordType) = ...
    f { ... }
```

Similarly, left-hand side of field expression (before `.`) also needs type annotation.

## Remarks

- Records are all immutable. No operation is provided to mutate field value after record creation.
- Unlike F#, fields can't be qualified. (`{ Person.Name = "" }`)

## Runtime representation

(Runtime representation of record types are unlikely stabilized. Compiler may put some of records on heap for performance optimization. I want to introduce an attribute to specify runtime layout, such as `#[repr(C)]` in Rust.)

Record types are converted to C structs.

```c
struct Person {
    struct String Name;
    int Age;
};
```
