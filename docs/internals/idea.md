# Idea

This page describes some "idea."

Idea is:

- not proven to be good
- not fully considered
- not fully determined
- not decided to implement.

## FFI

Foreign function interface (FFI) is necessary to implement practical programs.
But how?

It seems to be enough if the language works with the C language (that is, C FFI).

It seems the language needs:

- Declaration for external native functions
    - Multiple argument types and single return type
- Way to dynamically load from shared object (so) or dynamic link library (dll)
    - dlopen, LoadLibrary
- Type to represent native function pointers
    - Multiple argument types and single return type
    - Attribute for calling convention
- C-compatible types:
    - C-style enum and C-style struct for code-level interop
    - C-style union for code-level and runtime interop

## Memory Management

Unlike F#, milone-lang doesn't support GC.
Compiler is short-running application, so it doesn't need to free anything.

Memory management is necessary for long-running programs.

### Dynamic Region

As an experiment, milone-lang now supports `Region.run` function that takes a "region", a function (`() -> int`).
`Region.run` calls the region and returns the result, and then, *all memory allocated while running the region are freed*.

Deallocation by `Region.run` is safe and sound since *milone-lang doesn't support mutation of objects*,
so that no objects outside of the region point to these memory getting freed.

Using `Region.run`, at least in theory, I can now write long-running programs in milone-lang like this:

```fs
let work () =
    // Do something here, say, read and write to files.
    // Any memory allocated in this function
    // are freed after the end of calling (`Region.run` does).
    0

let main _ =
    // Note creating a function object allocates: do this outside of loop.
    let workFn = work

    let rec go () =
        let code = Region.run workFn
        if code <> 0 then code else go ()
    go ()
```

I want to support `Region.run` returning any object other than int, especially one including references.
This should be done by deeply cloning the result value of the region: the copy is allocated outside of the region.

- Making "back" references via C FFI (once supported) is not a problem since using C FFI incorrectly causes some memory errors in other "safe" languages too.
- By deeply cloning objects that need allocation, outside of region eventually runs into out of memory.
    - free copies manually? (`let x = Region.run f in doSomething x; free x`)
    - prevent copies from escaping and free them at the end of scope? (`let x: inref<T> = Region.run f in doSomething x`)

### Ownership

Memory that can't be put in a dynamic region are categorized to general resource and are manged using ownership.

----

## Memory Management Alternatives

- no: Just adding garbage collector (GC)
    - There are already good languages with GC
    - Memory isn't the only resource to be managed correctly
    - "Optional GC" isn't a way to go too. Memory management affects how to write code
- no: Manual resource management (like C)
    - C is dominant and Zig and Hare seem growing well
- no: Lifetime and ownership (like Rust)
    - Use Rust
- no: Use generic resource management mechanism
    - Memory is allocated frequently to justify specialization

## Resource Management

Resource management is an important topic for a language since it's non-local issue.

## Problems

### Ownership and Verbosity

- Passing owned objects back and forth is too verbose

Potential solutions:

- (Not to do)
- Passing Mutable Reference Downward

### Ownership and Type Bloat

- Owned types tend to have a non-owned counterpart
    - E.g. Vector and Block
    - That bloats functions

Potential solution:

- (Not to do)
- Making a mechanism for single type to be used as owned type and non-owned type

## Solutions

### Passing Mutable Reference Downward

- Passing a mutable reference is explicit enough
- Considering to provide a way to make unique mutable reference to a resource
- Mutable reference must be unique and it's scope must be statically known
    - Mutable reference is a kind of owned types

Sketch:

```fsharp
    let xs: Vector<'T> = Vector.alloc 0
    let b: VectorBorrow<'T> = Vec.borrow v
    // xs loses ownership here
    useVector b
    let xs: Vector<'T> = Vec.unborrow b
    // b loses ownership here
```

- Issues:
    - Bloat of "borrow" types
    - Verbose
