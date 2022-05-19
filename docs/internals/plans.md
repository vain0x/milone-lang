# Plans

(Not fully designed yet.)

## FFI

Foreign function interface (FFI) is necessary to implement practical programs.

To determine:

- Syntax to declare native functions
- C-compatible data types (~~void, int8_t, pointers,~~ enum, struct, union etc.)

## Memory Management

*In short: No GC. use dynamic region-based memory management and ownership.*

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

Memory that can't be put on a region are considered general resource and are manged using ownership.

## Resource Management

General resource is manged using ownership.
