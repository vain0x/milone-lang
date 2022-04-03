# AstBundle

This pass loads from source files and constructs an IR of entire program.

This pass also drives tokenizer, parser and NirGen for each file.

## Project Structure

See [docs/refs/projects](../refs/projects.md) for user-facing specification in details.

Key points are:

- Source directory is a project
- Source file is a module
- Source files (modules) can depend on others
    - Dependencies are written only by open/module syntax
- File path of source directory can be found by project name
- File path of source file can be computed by combination of project directory and module name

## Input

Input is an entry module. Host (caller) of the pass know filename to the entry module and its project directory.

Host is responsible to compute file paths and operate on file systems.
The pass uses references such as DocId, project names and module names.

## Output

Output is an NIR program for name resolution.

Source file maps to single NIR module.
NIR program is basically a list of modules.
These modules are layered and ordered by dependencies between modules.

Layer is a set of NIR modules.
Modules in single layer don't have dependency on others in the same layer.

Layers are ordered so that layers don't have dependency on higher layers.

For example:

```
    Modules and dependencies:
        Tokenize -> Syntax -> List
                    ^     \
                   /       -> Option
             Parse

    Layers:
        L1: List, Option
        L2: Syntax
        L3: Tokenize, Parse
```

In the above diagram:

- Tokenize module depends on Syntax module.
- Parse module depends on Syntax module.
- Syntax module depends on List and Option.

Layers represent the facts:

- L1 modules (List and Option) don't depend on each other
- L1 modules (List and Option) don't depend on higher modules (Syntax, Tokenize, Parse)
- L2 module (Syntax) can depend on L1 modules. But not on L3.
- L3 modules (Tokenize and Parse) depend on other modules except the other.

## What to Do

This pass does:

- load all source files that are transitively depended by the entry module
- process loaded files i.e. tokenize, parse and convert to an NIR module

These two processes are pipelined to get done concurrently.

Rules can be formulated like this:

- Initially, an entry module is *found*.
- Whenever a module is *found* at the first time, load source text from that file, tokenize, parse and convert to a NIR module.
    - By analyzing syntax tree (AST), collect module dependencies. These modules are *found*.

## Notes on Name

Current version of the pass doesn't *bundle* despite of its name. Actually, old version did. It did concat all contents of modules in topological order and the output was a long, single module at that time.
