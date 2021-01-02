# Function type

Function type is built-in type.

## Instant usage

```fsharp
    // Define a function. Polymorphic by default.
    let bind (f: _ -> _ option) (opt: _ option): _ option =
        match opt with
        | Some it -> f it
        | None -> None

    // Use anonymous function.
    let opt = bind (fun x -> x + 1) (Some 2)
    // opt is Some 3

    let opt = bind (fun x -> x + 1) None
    // opt is None
```

## Guide-level explanation

Functions are values. A function can be assigned to a variable, passed to other functions as parameter, and returned from a function.

See [let_expressions](let_expressions.md) to define named functions.

### Anonymous functions

`fun p1 p2 -> body` is a function as it looks like.

(Someone calls this kind of expressions *lambda*, but the term is problematic.)

## Advanced topics

### Currying and partial application

Functions are *curried* by default.

```fsharp
    let f x y = x + y

    // is basically same as...

    let f = fun x -> fun y -> x + y
```

Due to currying, functions can be partially applied.

```fsharp
    // The function has two parameters: x, y.
    let add x y = x + y

    // Only one parameter is applied to `add` function.
    // The result, `increment`, is a function to take the second parameter.
    let increment = add 1

    assert (increment 2 = 1 + 2)
```

### Arity error

Due to immaturity of compiler, use of function objects sometimes causes unusual compile error "arity mismatch".
This is not a problem of your code.

Arity mismatch can happen when a function would return another named function.

```fsharp
    // f returns a function that takes 2 parameters (when uncurried).
    let f (): _ -> _ -> _ =
        let g z = ...
        g
```

To workaround the issue, eta-expand the function as possible.

```fsharp
    let f (): _ -> _ -> _ =
        let g z = ...
        // instead of `g`:
        fun z w -> g z w
```

Test case about this: [tests/pendings/fun_arity_over](../../tests/pendings/fun_arity_over/fun_arity_over.fs).

### Derived forms

- `fun p1 p2 ... -> body` expands to `let f p1 p2 = body in f`.

## Runtime representation

(The runtime representation of functions is unlikely stabilized.)

Currently, function object is a pair of *environment* and function pointer.

Environment is an opaque pointer (`void const *`) to a struct.
The struct holds all values that the function object captures from outside of the function itself.
In other words, environment is an assignment to all *unbound* variables in the function body.

The environment doesn't appear in the function's type and which kind of struct it points to depends on the *value* of function objet rather than its type. This indirection is unavoidable.

Function pointer is a pointer to C function that to be called when the function object is called.
It takes an environment as first argument so that it can use the value of unbound variables.

```c
// int -> string
struct IntStringFun2 {
    void const *env;
    struct String (*fun)(void const *env, int);
};

// int -> float -> string (arity 2)
struct IntFloatStringFun2 {
    void const *env;
    struct String (*fun)(void const *env, int, float);
};
```

Caller of function object should pass the correct environment object to the function.
For example, function application `f x` is converted to `f.fun(f.env, x)`.
