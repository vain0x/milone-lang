# Projects

Project is a set of source files.

## Guide-level Explanation

### Project in File System

A project is mapped to a directory.
Project name (say, `Foo`) must match the directory name (`Foo/`).

Project directory contains module files (`.milone` or `.fs`).

If there exists a module whose name is same as the project name excluding its extension (say `Foo.milone`),
that module is **entry module**.
Entry module enables the project to be compiled as an executable, and therefore it must define `main` function.

- Foo/ : project directory
    - Foo.milone : entry module file
    - Bar.milone : module file

Project directory is not recursive. Subdirectories are not member of the project.

### External Project References

Projects can refer to other projects in the same directory.

- Foo/
    - A.milone
- Bar/
    - Bar.milone : can use `open Foo.A` to import from `../Foo/A.milone`

## Advanced Topics

### Comparison to F#

F# uses `.fsproj` file to specify the project:

- list of modules (in the order),
- external project references,
- external NuGet package reference,
- and other MsBuild settings.
