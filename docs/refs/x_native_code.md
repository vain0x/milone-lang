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

See [x_ptr_types](x_ptr_types.md).

## Function pointer types

`FunPtr<T, U>` is a function pointer type. `T` represents the parameter list and `U` represents the result type.

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
    open Std.Ptr

    // void(*)(void)
    type ActionFun = FunPtr<unit, unit>

    // int(*)(int)
    type IntUnaryFun = FunPtr<int, int>

    // int(*)(int, int)
    type IntBinaryFun = FunPtr<int * int, int>
```

(Currently there is no way to specify calling convention.)

## Get pointer of function

`&&f` represents a function pointer of a function `f`, where `f` is a function defined by let-fun syntax.

Function must NOT capture any local variables.

```fsharp
    open Std.Ptr

    let f (x: int) : int = x + 1

    let fp: FunPtr<int, int> = &&f
```

## Call external native function

`__nativeFun ("name", args...)` is a special expression to call a native function with the specified name.

An extern declaration of the function is also generated.

```fsharp
    // void abort(void);
    // abort();
    __nativeFun "abort"

    // void *calloc(size_t, size_t);
    // void *p = calloc(4, sizeof(int));
    let p: voidptr = __nativeFun ("calloc", 4un, unativeint sizeof<int>)
    // ...
```

Called function must be linked statically.
Otherwise, link error will occur.
For example, if a program calls `sqrt` function then it needs to link `libm`.
(Just including `<math.h>` isn't enough.)
Use manifest file to specify linker options (TODO: write document of manifest file!).

Restriction: Variadic parameter functions (e.g. `printf`) can't be called with this syntax.

## Call native function from so/dll

(Not implemented yet. Use `dlopen` on Unix and link `libdl` (`-ldl` option). Use `LoadLibrary` on Windows.)

## Size of type

`sizeof<'T>` is the size of type T in bytes. Type is `int`. Equivalent to `sizeof(T)` in C.

## Embedded naive expressions

`__nativeExpr ("expression", arg1, arg2, ...)` is an expression to embed a C expression into generated code.
The string literal `"expression"` contains an arbitrary C expression.
Other arguments are bound to placeholders (see below).

```fsharp
    // int e = errno;
    // (Note `errno` is a global variable in C.)
    let e: int = __nativeExpr "errno"
```

`__nativeExpr` can be arbitrary type, i.e. `'A'`. Incorrect type would incur C compile error. Warning: Result type must NOT be `unit`; otherwise the expression might be erased during compilation.

`__nativeExpr` should be used when the expression is *pure*. Use `__nativeStmt` for side-effect.

### Placeholders

Placeholder `{i}` (`i >= 0`) in the template is each replaced with the i'th placeholder argument.

### Value placeholders

Placeholder argument is compiled to C normally and substitutes a placeholder in the template.

```fsharp
    // int z = x + y;
    let z: int = __nativeExpr("{0} + {1}", x, y)
```

### Type placeholders

`__type: T` is a special expression for placeholder argument.
It represents a type rather than value.

```fsharp
    // size_t n = sizeof(struct String);
    let n: unativeint = __nativeExpr ("sizeof({0})", (__type: string))
```

## Embedded native statements

`__nativeStmt ("statement", args...)` is an expression to embed a C statement into generated code.
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

`__nativeDecl ("declaration", args...)` is an expression to embed a C declaration into generated code.
The string literal `"declaration"` contains arbitrary C declaration.
Other arguments are bound to placeholders (same as `__nativeExpr`.)

Declarations are hoisted to top-level (even if `__nativeDecl` is used inside a function.)

```fsharp
    __nativeDecl "#include <errno.h>"
```

Value of `__nativeDecl (...)` is `()`.

Placeholder arguments are limited to expressions any of:

- Literals,
- Names,
- `&&f` (function pointer), or
- `(__type: 'T)`;

since arguments must be evaluated without using statements.

## Embedded native types

`__nativeType<T>` is a special type to embed a C type into generated code.
`T` is an identifier, which can be undefined.

```fsharp
    type F = __nativeType<FILE>

    // FILE *input = stdin;
    let input: nativeptr<F> = __nativeExpr "stdin"
```

----

## Recommended practice: Abstraction

See [Pointer Types / Recommended Practice: Abstraction](x_ptr_types.md#recommended-practice-abstraction)
