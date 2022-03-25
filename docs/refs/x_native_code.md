# Extension: Native code

This page describes a particular set of features for native code interoperability.
These features are "language extensions", i.e. not compatible with F#.

**WARN: These features will be removed in future, especially before v1 release.**

### Prerequisites

It's assumed that you know about:

- Basics of the C language
- Undefined behavior (UB) in C
- Low-layer programming

### Naming convention

Keywords that start with `__` represent language extensions, which are unavailable in F#.

### Caution

The compiler can't ensure these features to work correctly.
If these features are used incorrectly at runtime, the program runs into *undefined behavior* (UB).
Such program does anything weird with no error.

----

## Native pointer types

| milone-lang       | C                 |
|:------------------|:------------------|
| `__constptr<T>`   | `const T *`       |
| `nativeptr<T>`    | `T *`             |
| `obj`             | `const void *`    |
| `voidptr`         | `void *`          |

## Get pointer of value

(Not implemented. Use `box` and cast it to pointer.)

## Pointer cast

`__nativeCast` function converts pointers and pointer-sized integers (`nativeint` / `unativeint`) each other.

```fsharp
    let p: nativeptr<int> = __nativeCast 0un
    let q: __constptr<int> = __nativeCast p
```

### Read via pointer

`__ptrRead p i` reads from a pointer `p` by offset `i` (that is, `p[i]`).
Pointer type must be `__constptr<T>`.

```fsharp
    //    p: __constptr<T>, i: int
    // => (__ptrRead p i): T

    __ptrRead p 0  //=> *p in C
    __ptrRead p i  //=> p[i] in C
```

### Write via pointer

`__ptrWrite p i` writes to a pointer `p` by offset `i` (that is `p[i]`).
Pointer type must be `nativeptr<T>`.

```fsharp
    //    p: nativeptr<T>, index: int, value: T
    // => (__ptrWrite p index value): unit

    __ptrWrite p 0 x  //=> *p = x; in C
    __ptrWrite p i x  //=> p[i] = x; in C
```

## Function pointer types

`__nativeFun<T, U>` is a function pointer type. `T` represents the parameter list and `U` represents the result type.

`T` is a tuple type or other:

| `T`               | parameter list    |
|:------------------|:------------------|
| `unit`            | `()`              |
| `T` (not tuple)   | `(T)`             |
| `T1 * T2`         | `(T1, T2)`        |
| `T1 * T2 * T3`    | `(T1, T2, T3)`    |

`U` is unit or other:

| `U`               | result type   |
|:------------------|:--------------|
| `unit`            | `void`        |
| `U` (not unit)    | `U`           |

```fsharp
    // void(*)(void)
    type ActionFun = __nativeFun<unit, unit>

    // int(*)(int)
    type IntUnaryFun = __nativeFun<int, int>

    // int(*)(int, int)
    type IntBinaryFun = __nativeFun<int * int, int>
```

(Currently there is no way to specify calling convention.)

## Get pointer of function

`__nativeFun f` represents a function pointer of a function `f`, where `f` is a function defined by let-fun syntax.

Function must NOT capture any local variables.

```fsharp
    let f (x: int) : int = x + 1

    let fp: __nativeFun<int, int> = __nativeFun f
```

## Call statically-linked native function

`__nativeFun ("name", args...)` is a special syntax to call a native function with the specified name.

An extern declaration of the function is also generated.

```fsharp
    // void abort(void);
    // abort();
    __nativeFun "abort"

    // void *calloc(size_t, size_t);
    // calloc(4, sizeof(int))
    let p: voidptr = __nativeFun ("calloc", unativeint 4, unativeint (__sizeOfVal 0))
    // ...
```

Called function must be linked statically.
Otherwise, link error will occur.
For example, if a program calls `sqrt` function then it needs to link `libm`.
(Just including `<math.h>` isn't enough.)
Use manifest file to specify linker options (TODO: write document of manifest file!).

Restriction: Variadic parameter functions (e.g. `printf`) can't be called with this syntax.

## Call dynamically-linked native function

(Not implemented yet. Use dlopen on Unix and link libdl. Use LoadLibrary on Windows.)

## Size of values

`__sizeOfVal (expr: T)` is the size of a value of a type T in bytes.
`expr` is not evaluated.

This is similar to `sizeof(expr)` in C.

```fsharp
    // If the type of `expr` is T, __sizeOfVal(expr) is compiled to sizeof(T).
    __sizeOfVal expr

    // expr is guaranteed to not evaluate.
    let nullptr: __constptr<int> = __nativeCast (unativeint 0)
    assert (__sizeOfVal (__ptrRead nullptr 0) = 4)
```

## Embedded naive expressions

`__nativeExpr ("expression", arg1, arg2, ...)` is an expression to embed a C expression into generated code.
The string literal `"expression"` contains an arbitrary C expression.
Other arguments are bound to placeholders (see below).

```fsharp
    // int e = errno;
    // (Note `errno` is a global variable in C.)
    let e: int = __nativeExpr "errno"
```

Placeholder `{i}` (`i >= 0`) in the template is each replaced with the i'th placeholder argument.
Warning: Currently there's no way to escape braces.

### Value placeholders

Placeholder argument is compiled to C normally and substitutes a placeholder in the template.

```fsharp
    // int z = x + y;
    let z: int = __nativeExpr("{0} + {1}", x, y)
```

### Type placeholders

`__type: T` is a special syntax for placeholder argument.
It represents a type rather than value.

```fsharp
    // size_t n = sizeof(struct String);
    let n: unativeint = __nativeExpr ("sizeof({0})", __type: string)
```

## Embedded native statements

`__nativeStmt ("statement", args...)` is a statement to embed a C statement into generated code.
The string literal `"statement"` contains arbitrary C statement.
Other arguments are bound to placeholders (same as `__nativeExpr`.)

```fsharp
    __nativeStmt "abort();"
```

```fsharp
    // printfn("%d", 42);
    __nativeStmt """printfn("%d\n", 42);"""
```

## Embedded native declarations

`__nativeDecl ("declaration", args...)` is a declaration to embed a C declaration into generated code.
The string literal `"declaration"` contains arbitrary C declaration.
Other arguments are bound to placeholders (same as `__nativeExpr`.)

Declarations are hoisted to top-level (even if `__nativeDecl` is used inside a function.)

```fsharp
    __nativeDecl "#include <errno.h>"
```

## Embedded native types

`__nativeType<T>` is a type to embed a C type into generated code.
`T` is an identifier, which can be undefined.

```fsharp
    type F = __nativeType<FILE>

    // FILE *stdin;
    let stdin: nativeptr<F> = __nativeExpr "stdin"
```

----

## Recommended practice: Safe wrapper

Function is *safe* if it can't cause undefined behavior (UB) for any arguments.

*Safe wrapper* is an API which exposes a set of *safe* functions and types.

Avoid using these features described in this page directly from application. Instead, make a module as a safe wrapper on top of them.

(TODO: explain more precisely, add examples)
