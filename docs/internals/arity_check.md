# Arity Check

**Arity Check** is a pass to validate program so that usage of functions are safe to generate C code.

See also the section "Arity error" in documentation of function type.

## Arity

**Arity** is the number of parameters of function.

## Type of Function

Every function is 1-arity in milone-lang type system.
Function type `S -> T -> U` is just a nested function type, i.e. `S -> (T -> U)`, a function that takes `S` value and returns another function `T -> U`.

## Representation of Function

However, the runtime representation of milone-lang functions are not in such way.
Function that is declared with N parameters is compiled to an N-arity C function.

```fsharp
    let f p1 p2 p3 : U = ...
```

```c
    // Generated C code
    U f(T1 p1, T2 p2, T3 p3) { ... }
```

The reason why the compiler does so is for performance.
Creating a closure for each application would be unrealistically inefficient (not measured though.)

## Arity Mismatch Problem

Due to the mismatch, some expression is compiled to invalid C code unfortunately. For example from `fun_arity_over` test:

```fsharp
  let f: int -> int -> int =
    let add (x: int) : int -> int =
      fun (y: int) -> x + y

    add
```

Where:

- `add` is 1-arity function
- `f` is 2-arity function object

Naively generated code would be:

```c
// int -> int
struct IntFun1 {
    int(*fun)(void const *, int);
    void const *env;
};

// int -> int -> int
struct IntIntFun2 {
    int(*fun)(void const *, int, int);
    void const *env;
};

// fun y -> x + y
struct IntIntFun2 add_fun(void const *env, int y) {
    int x = *(int const *)env;
    return x + y;
}

// let add x = fun y -> x + y
struct IntFun1 add(int x) {
    return (struct IntFun1){.fun = add_fun, .env = &x};
}

// let f = add
struct IntIntFun2 f = (struct IntIntFun2){.fun = add};
//                                             ^ Error!
```

## How to Check

To avoid the problem, arity checker computes *ArityEx* for each expression.

### Helper Functions

*ArityEx* is a shape of function.

```
    a : ArityEx

    ArityEx :=
        1                   (Non-function value)
        | (a, ..., a) -> a  (N-arity function)
        | *                 (Hungry function)
```

Examples:

- `(1) -> 1` represents 1-arity function from non-function value to non-function value.
- `(1, 1) -> 1` represents 2-arity function
- `(1) -> (1) -> 1` represents 1-arity function that results in a 1-arity function
- `((1) -> 1) -> 1` represents a 1-arity function that takes an 1-arity function
- `*` is a special arity for variadic diverging function such as `failwithf`

Function τ computes *ArityEx* for a type.

```
    T_i : type
    U : non-function type

    τ : type -> ArityEx
    τ(U) = 1
    τ(T1 -> T2 -> ... -> TN -> U) =
        (τ(T1), ..., τ(TN)) -> 1
```

Function ε computes *ArityEx* for an expression.

```
    f : N-arity function of T1 -> ... -> TN -> U
    e : non-function expression

    ε : expression -> ArityEx
    ε(f) = (τ(T1), ..., τ(TN)) -> τ(U)
    ε(e) = τ(T)
```

### Check Rules

Arity judge: `Γ |= e :: a` indicates the expression has the ArityEx under the environment.

```
    Γ : environment
    e : expression
    a : ArityEx

    Γ |= e :: a
```

Unification of ArityEx is straight-forward (omit details.)
Hungry ArityEx (`*`) works like the bottom type in unification.

Arity check rules can be defined as analogue to type rules like this:

```
    e_i : expression


    Γ |= init :: ε(v),
    (v :: τ(v), Γ) |= next :: a
    ---- (LET-VAL)
    Γ |= (let v = init in next) :: a


    (pi :: τ(Pi), Γ) |= init :: ε(f),
    (f :: ε(f), Γ) |= next :: a
    ---- (LET-FUN)
    Γ |= (let f p1 p2 ... pN = init in next) :: a


    s : symbol,
    (s :: a) ∈ Γ
    ---- (SYMBOL)
    Γ |= s :: a


    Γ |= f :: (ε(e1), ε(e2), ..., ε(eN)) -> a
    ---- (APP)
    Γ |= (f e1 e2 ... eN) :: a


    Γ |= e1 :: 1, e2 :: a, e3 :: a
    ---- (IF)
    Γ |= (if e1 then e2 else e3) :: a


    and others...
```
