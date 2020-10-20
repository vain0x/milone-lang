# Notes

### FFI

FFI is absolutely necessary to use milone-lang in somewhat practical purpose.

Open design spaces:

- syntax to declare native functions (statically linked, dynamically linked)
- C-compatible data types (void, int8_t, pointers, etc)
- design of safe wrappers (APIs to indirectly use "unsafe" features without risk of problems)

Links:

- [External Functions - F# | Microsoft Docs](https://docs.microsoft.com/en-us/dotnet/fsharp/language-reference/functions/external-functions)
- [fsharp/nativeptr.fs · dotnet/fsharp](https://github.com/dotnet/fsharp/blob/ec5bad3a391357e03ff2286a264f0e4faf7d840d/src/fsharp/FSharp.Core/nativeptr.fs)

### Memory management

*In short: No GC. Will support dynamic region-based memory management by deep cloning.*

Unlike F#, milone-lang doesn't support GC.
Compiler is short-running application, so it doesn't need to free anything.

Memory management is necessary for some of long-running programs such as web servers.

As an experiment, milone-lang now supports `inRegion` primitive that takes a "region", a function (`() -> int`).
`inRegion` calls the region and returns the result, and then, *all memory allocated while running the region are freed*.

Deallocation by `inRegion` is safe and sound since *milone-lang doesn't support mutation of objects*,
so that no objects outside of the region point to these memory getting freed.

Using `inRegion`, at least in theory, I can now write long-running programs in milone-lang like this:

```fs
let work () =
    // Do something here, say, read and write to files.
    // Any memory allocated in this function
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

- Making "back" references via C FFI (once supported) is not a problem since using C FFI incorrectly causes some memory errors in other "safe" languages too.
- By deeply cloning objects that need allocation, outside of region eventually runs into out of memory.
    - free copies manually? (`let x = inRegion f in doSomething x; free x`)
    - prevent copies from escaping and free them at the end of scope? (`let x: inref<T> = inRegion f in doSomething x`)
