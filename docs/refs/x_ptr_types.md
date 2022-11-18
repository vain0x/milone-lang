# Extension: Pointer Types

This page describes non-function pointer feature.

## Prerequisites

This page assumes the reader knows:

- Basics of the C language
- Undefined behavior (UB) in C

----

## `Std.Ptr` Module

`Std.Ptr` is a special module that provides several primitives for pointers.

This page assumes `open Std.Ptr` is declared.

## Pointer Types

There are several types for pointers.

| milone-lang       | C                 | Permission    |
|:------------------|:------------------|:--------------|
| `InPtr<T>`        | `T const *`       | Read-only     |
| `OutPtr<T>`       | `T *`             | Write-only    |
| `nativeptr<T>`    | `T *`             | Read-write    |
| `VoidInPtr`       | `void const *`    | -             |
| `voidptr`         | `void *`          | -             |

*Note*: `nativeptr` and `voidptr` exist in F# but others don't.

First three types (`InPtr`, `OutPtr`, `nativeptr`) are generic. They carry type of pointee.
The difference is permission of read/write operations.

The other two types (`VoidInPtr`, `voidptr`) are *opaque* pointers.
Type of pointee isn't statically known.
Read/write operations don't directly work on them.
Cast to a generic pointer type to use.

`OutPtr` is same as `nativeptr` in the view of C language.
The difference is that `OutPtr` isn't readable.
Intentional usage is an uninitialized buffer (result of allocation function) and an output parameter.

## Obtaining Pointer

### Pointer of Variable

Unary `&&` operator (called "ptr-of" operator) makes a pointer to a variable.
It's invalidated when the variable goes out of scope.

```fsharp
    let x = 42
    let p: InPtr<int> = &&x
```

- Writing to the content is undefined behavior.
- Not compatible with F#, where `&&x` is `nativeptr<T>`.

### Allocated Pointer

```fsharp
    open Std.Region

    Region.alloc : uint -> OutPtr<'T>
```

`Region.alloc` function allocates a number of items of a type on the current region and returns a pointer to the start of memory block.

- Allocated memory is zeroed.
- The returned pointer is guaranteed to be valid. This function aborts the program if allocation failed.
- The returned pointer is invalidated when to leave of the current region.

See also [region](./x_region.md), and "Memory Management" in idea.md for "regions".

### Null Pointer

```fsharp
    Ptr.nullPtr : 'P
    // when 'P is a pointer type
```

`Ptr.nullPtr` is the null value of some pointer type.

### Address to Pointer Conversion

```fsharp
    Ptr.invalid : address:unativeint -> 'P
    // when 'P is a pointer type
```

`Ptr.invalid` function converts an address-sized integer to a fake pointer that is always valid.

The generated pointer is something to carry an integer as pointer type.
It may not be used to memory access but can be converted back to an integer later.

## Pointer Transformation

### Pointer Cast

```fsharp
    Ptr.cast : 'P -> 'Q
    // when both 'P and 'Q are pointer types
    //      but 'P <> 'Q

    Ptr.asIn : (OutPtr<'T> -> InPtr<'T>)
             & (nativeptr<'T> -> InPtr<'T>)
             & (voidptr -> VoidInPtr)

    Ptr.asNative : (InPtr<'T> -> nativeptr<'T>)
                 & (OutPtr<'T> -> nativeptr<'T>)
                 & (VoidInPtr -> voidptr)
```

*Note*: `f : F & G` means the function type is overloaded to F and G.

`Ptr.cast` casts a pointer to another pointer type.

`Ptr.asIn` casts a pointer to `InPtr` or `VoidInPtr` depending on the argument type.
This function doesn't change pointee type.

`Ptr.asNative` casts a pointer to `nativeptr` or `voidptr` depending on the argument type.
This function doesn't change pointee type.
Be careful to use this function since it's an unchecked downcast.

### Selection

```fsharp
    Ptr.select (accessPath:'P) -> 'Q
    // when 'P is a pointer type and 'Q is the derived pointer type
```

`Ptr.select` is a special primitive to derive an interior pointer from a pointer.
It can compute a pointer to i'th item.

```fsharp
    Ptr.select p.[i] // &p[i] in C
```

This primitive will extend to support other types in future.
For example, `Ptr.select p.Field` will derive a pointer to field from a pointer to record.

## Use of Pointer

### Read via Pointer

```fsharp
    Ptr.read : accessPath:'P -> 'T
    // when 'P is either InPtr<'T> or nativeptr<'T>

    Ptr.read p      // *p in C
    Ptr.read p.[i]  // p[i] in C
```

`Ptr.read` primitive reads a value from a location where the specified pointer points.

Reading from an invalid pointer or reading as incorrect type is undefined behavior.

### Write via Pointer

```fsharp
    Ptr.write : accessPath:'P -> value:'T -> unit
    // when 'P is either OutPtr<'T> or nativeptr<'T>

    // *p = value; in C
    Ptr.write p value

    // p[i] = value; in C
    Ptr.write p.[i] value
```

`Ptr.write` primitive writes a value to a location where the specified pointer points.

### Cast to Address

```fsharp
    unativeint : ('P -> unativeint) & ...
    // when 'P is a pointer type
```

`unativeint` primitive can cast any pointer to its address.

The address is considered exposed. This cast is lossy and impure.

## Others

- Pointer types support equality `(=)`
- `Own<P>` (when `P` is a pointer type) can be cast by `Ptr.cast`

## Recommended Articles

The "Pointers Are Complicated" article series is good to learn about semantics of pointers.

- [Pointers Are Complicated, or: What's in a Byte?](https://www.ralfj.de/blog/2018/07/24/pointers-and-bytes.html)
- [Pointers Are Complicated II, or: We need better language specs](https://www.ralfj.de/blog/2020/12/14/provenance.html)
- [Pointers Are Complicated III, or: Pointer-integer casts exposed](https://www.ralfj.de/blog/2022/04/11/provenance-exposed.html)

## Recommended Practice: Abstraction

Pointer types are inherently unsafe and very hard to use correctly.

Avoid using pointer types in application-wide source files.
Instead, make a module that manipulates pointers that provides only safe API to use.
Such module is called safe-wrapper or abstraction.

Also, [owned types](x_own_type.md) help such design.

----

## Appendix

### Difference of `obj` and `VoidInPtr`

Both `obj` and `VoidInPtr` are compiled to `void const *` in C.
However, `obj` isn't a pointer type.

The `box` function doesn't always make a pointer to its argument but just cast it to pointer type when the value type fits in a pointer.
For example, `Ptr.read (Ptr.cast (box 42un): InPtr<unativeint>)` attempts to read a value at the address `42`, which is definitely an error.
