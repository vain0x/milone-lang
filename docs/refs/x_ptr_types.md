# Extension: Pointer Types

This page describes non-function pointer feature.

- *NOTICE(lang-ext)*: This feature is "language extension", i.e. not compatible with F#. Identifiers that start with `__` are for extensions.

## Prerequisites

It's assumed that the reader know about:

- Basics of the C language
- Undefined behavior (UB) in C

----

## `Std.Ptr` Module

`Std.Ptr` is a special module that provides several primitives for pointers.

This page omits `Std.` prefix, assuming it's declared with `module Ptr = Std.Ptr`.

## Pointer Types

There are several types for pointers.

| milone-lang       | C                 | Permission    |
|:------------------|:------------------|:--------------|
| `__inptr<T>`      | `T const *`       | Read-only     |
| `__outptr<T>`     | `T *`             | Write-only    |
| `nativeptr<T>`    | `T *`             | Read-write    |
| `__voidinptr`     | `void const *`    | -             |
| `voidptr`         | `void *`          | -             |

*Note*: `nativeptr` and `voidptr` exist in F# but others don't.

First three types (`__inptr`, `__outptr`, `nativeptr`) are generic. They carry type of pointee.
The difference is permission of read/write operations.

The other two types (`__voidinptr`, `voidptr`) are *opaque* pointers.
Type of pointee isn't statically known.
Read/write operations don't directly work on them.
Cast to a generic pointer type to use.

`__outptr` is same as `nativeptr` in the view of C language.
The difference is that `__outptr` isn't readable.
Intentional usage is an uninitialized buffer (result of allocation function) and an output parameter.

### Notation of Types

Some of pointer primitives are treated specially in type check.

- `{ptr}` represents all pointer types.
- `{ptr<T>}` represents all generic pointer types.

## Obtaining Pointer

### Pointer of Variable

Unary `&&` operator (called "ptr-of" operator) makes a pointer to a variable.
It's invalidated when the variable goes out of scope.

```fsharp
    let x = 42
    let p: __inptr<int> = &&x
```

- Writing to the content is undefined behavior.
- Not compatible with F#, where `&&x` is `nativeptr<T>`.

### Allocated Pointer

```fsharp
    Ptr.regionAlloc : uint -> __outptr<'T>
```

`Ptr.regionAlloc` function allocates a number of items of a type on the current region and returns a pointer to the start of memory block.

- Allocated memory is zeroed.
- The returned pointer is guaranteed to be valid. This function aborts the program if allocation failed.
- The returned pointer is invalidated when to leave of the current region.

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

`Ptr.invalid` makes a pointer that points to the specified address.

There are two kind of potential usage:

- To make an non-null dangling pointer intentionally.
- To make a pointer that is valid if it has some previously exposed provenance.

## Pointer Transformation

### Pointer Cast

```fsharp
    Ptr.cast : 'P -> 'Q
    // when both 'P and 'Q are pointer types
    //      but 'P <> 'Q

    Ptr.asIn : (__outptr<'T> -> __inptr<'T>)
             & (nativeptr<'T> -> __inptr<'T>)
             & (voidptr -> __voidinptr)

    Ptr.asNative : (__inptr<'T> -> nativeptr<'T>)
                 & (__outptr<'T> -> nativeptr<'T>)
                 & (__voidinptr -> voidptr)
```

*Note*: `f : F & G` means the function type is overloaded to F and G.

`Ptr.cast` casts a pointer to another pointer type.

`Ptr.asIn` casts a pointer to `__inptr` or `__voidinptr` depending on the argument type.
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
    // when 'P is either __inptr<'T> or nativeptr<'T>

    Ptr.read p      // *p in C
    Ptr.read p.[i]  // p[i] in C
```

`Ptr.read` primitive reads a value from a location where the specified pointer points.

Reading from an invalid pointer or reading as incorrect type is undefined behavior.

### Write via Pointer

```fsharp
    Ptr.write : accessPath:'P -> value:'T -> unit
    // when 'P is either __outptr<'T> or nativeptr<'T>

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
- `__linear<P>` (when `P` is a pointer type) can be cast by `Ptr.cast`

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

Also, linear types help such design.

----

## Appendix

### Legacy Misuse of `obj` Types

The codebase might still contain incorrect use of `obj` due to the change of its semantics.

In previous version of the milone-lang, `obj` was one of pointer types that was equivalent to `void const *` in C.
`obj` was used instead of current `__voidinptr`.

However, there was a problem that `box` function did't always make a pointer to its argument but just cast it to pointer type when the value type was pointer-sized.
For example, `Ptr.read (Ptr.cast (box 42un): __inptr<unativeint>)` attempted to read a value from an address `42`, which was definitely error.

That is, existing `box` function made use of `obj` type more unsafe.
I decided to add a separate type `__voidinptr` for pointer.
