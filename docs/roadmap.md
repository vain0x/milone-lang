# Roadmap

*Roadmap is subject to change.*

## Perspective

### Define the Goal

- **Current Status**: Self-hosting with the C backend.
- **Ideal Goal**: Self-hosting, multi-platform (Linux and Windows) support, and documentation on implementation.

### Focus on the Concept

Keep focused on the concept of the project. It's:

- making a *self-hosting* compiler,
- in a language that looks like a *subset* of F#,
- as a pipeline of *immutable* data transformation.

### Done It

The project should achieve some point that can be called as completion.

----

## Significant Problems

I tried to make example apps such as HTTP server and GUI tool in the language and couldn't because something is lacked.

### Lack of Practical IO Expressions

There's practically no "valid" way perform IO operations.

Currently, strictly speaking, just calling `printfn` is UB because it's a `unit` value; the compiler may eliminate it as an optimization.
Owned types are the valid way. However, it doesn't compose well with other parts of the language. It seems to take a lot of time to redesign the language around it to make things practical.

### Lack of *Stable* FFI

Unstable features (`__nativeCode` etc.) work. I just can't use them in example apps.

### Lack of Debugging, Logging

Debugging is cumbersome. `printfn` can print only numbers and strings. Dumping an object to observe the internal state requires some work such as hand-writing *toString* operators.

## Acceptable Problems

These things aren't perfect but no need to immediately fix.

- Memory management
    - `loopInRegion` is acceptable
- Project structures
    - There's no way to make some modules private in libraries
- No testing/benchmark mechanism (inconvenient)
- Runtime efficiency
    - List processing isn't time/memory efficient at all, however, not too slow.

----

## Changes to the Language

**Sequential evaluation order**. Computations run in the order of syntax like C and F#. This change reduces the difficulty of language design and reduces features for owned type mechanism etc.
This also solves the *Lack of Practical IO Expressions* issue and unlocks designing *stable FFI*.

**Support overriding ToString methods** or similar.
Method-like syntax are currently unsupported.
`ToString` and something is definitely necessary.
This change should mitigate the debugging issue.

**Support context API** for custom resources and error handling.
Extend the current "dynamic region" mechanism.
Provide the way to attach some resource to the context so that the downstream of the call stack can retrieve it from the context.
This should mitigate the logging issue and partially error handling.

Error handlers can be registered in the context to be invoked so that libraries can raise various errors without writing a lot of error handling in polymorphic way.
