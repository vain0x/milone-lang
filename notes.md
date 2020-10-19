# Notes

### FFI

FFI is absolute necessary to use milone-lang in somewhat practical purpose.

### Memory management

*In short: No GC. Will support dynamic region-based memory management by deep cloning.*

Unlike F#, milone-lang doesn't support GC.
Compiler is short-running application, so it doesn't need to free anything.

Memory management is necessary for some of "long-running" applications such as web servers.

As an experiment, milone-lang now supports `inRegion` primitive.
It takes a function (`() -> int`), called "region", calls it and propagates to return the result.
After that, *all memory allocated while running the region are freed*.

Deallocation by `inRegion` is safe and sound *since milone-lang doesn't support mutation of objects*,
so no objects outside of the region can't point to these memory getting freed.

Using this `inRegion`, at least in theory, you can now write long-running programs in milone-lang like this:

```fs
let work () =
    // Do something here, say, read and write to files.
    // Any memory allocated in this anonymous function
    // are freed after the end of calling (`inRegion` does).
    0

let main _ =
    // Note creating a function object allocates: do this outside of loop.
    let workFn = work

    let rec go () =
        let code = inRegion workFn
        if code <> 0 then code else go ()
    go ()
```

I want to support `inRegion` returning any object other than int, especially one including references.
This should be done by deeply cloning the result value of the region: the copy is allocated outside of the region.

(Note that it's possible to make a "back" reference, a pointer from outside of the region to inside of that,
once milone-lang supports C-FFI (native functions and pointers).
I don't count this a problem, as it's easy to produce memory-specific errors using C-FFI also in other "safe" languages.)
