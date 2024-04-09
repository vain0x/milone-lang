# Roadmap

*Roadmap is subject to change.*

## Perspective

### Define the Goal

- **Current Status**: Self-hosting with the C backend. F#-ish part is done.
- **Ideal Goal**: Self-hosting with *assembler*, multi-platform (Linux and Windows) support, and documentation on implementation.

### Focus on the Concept

Keep focused on the concept of the project. It's:

- making a *self-hosting* compiler,
- in a language that looks like a *subset* of F#,
- as a pipeline of *immutable* data transformation.

### Done It

The project should achieve some point that can be called as completion.

----

## Lack

I tried to make example apps such as HTTP server and GUI tool in the language and couldn't because something is lacked.

### Lack of Practical IO Expressions

There's practically no "official" way perform IO operations.

Strictly speaking according to the current specification, `printfn` is UB because it's a `unit` value so the compiler may eliminate it as an optimization.
Owned types are the official way. However, it seems to take some time to design the language around it to make things practical, e.g. support loops, error handlings, concurrency etc.

### Lack of *Stable* FFI

Unstable features (`__nativeCode` etc.) feels okay. I just can't use them in example apps.

### Lack of Debugging, Logging

Debugging is cumbersome. `printfn` can print only numbers and strings. Dumping an object to observe the internal state requires some work such as hand-writing *toString* operators.

----

## Changes to the Language

**Allow sequential IO expressions**. Computations are sequential like C and F#. This change reduces the difficulty of language design and reduces features for owned type mechanism etc.
This change should solve the *Lack of Practical IO Expressions* issue.
This also unlocks designing *stable FFI*.

**Support overriding ToString methods** or similar.
Method-like syntax are currently unsupported.
`ToString` and something is definitely necessary.
This change should mitigate the debugging issue.

**Support context API** for custom resources and error handling.
Extend the current "dynamic region" mechanism.
Provide the way to attach some resource to the context so that the downstream of the call stack can retrieve it with the same key.
This should mitigate the logging issue and partially error handlings.

Error handlers can be registered in the context to be invoked so that libraries can raise various errors without writing a lot of error handling in polymorphic way.
This should mitigate the debugging

## What to Do Next

- Implement non-C backend for x64 architecture on Linux, and hopefully on Windows
- Implement standard libraries and some practical examples
