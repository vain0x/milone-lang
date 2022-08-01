# Dynamic Regions

This page explains *dynamic regions*.

NOTICE: *Region API is still incomplete for practical use.*

Dynamic region is a way to manage resources by the milone-lang runtime.
Especially, the allocator that is owned by the current region is used to allocate objects such as strings, lists, and closures.

The key point is resources that are owned by a dynamic region can't escape from it nor is transferred from.
These resources are disposed only by the dynamic region.

## `Std.Region`

`Std.Region` is a special module that provides a few of primitives.

```fsharp
open Std.Region
```

### `Region.run`

```fsharp
    Region.run: action:(unit -> int) -> int
```

The `Region.run` primitive runs a function in new dynamic region.

```fsharp
    let code =
        Region.run (fun () ->
            // do something to allocate things
            0
        )
```

### `Region.alloc`

```fsharp
    Region.alloc: count:int -> OutPtr<'T>
```

The `Region.alloc` function allocates a block of memory in the current region.

### `Region.defer`

```fsharp
    Region.defer: disposer:(unit -> unit) -> unit
```

The `Region.defer` primitive registers a function to dispose a resource when to leave from the current region.

## Remark: "Dynamic" not Lexical

"Region" in the milone-lang is different than "region" in the context of *region inference*.
Region is a kind of static, lexical thing there.
