# Projects

Project is a set of source files.

## Guide-level explanation

### Project in file system

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

### Project manifest file

Project directory may contain a project manifest file. Its name equals to project name followed by `.milone_project`.

Its syntax is subset of milone-lang.
Top-level is a record expression.
Specify the current version number of the project and project references as below.

```fsharp
{
    Version = "0.1.0"
    Options = [
        // Reference to another project,
        // which is at ../MyLib (relative to this manifest file).
        Ref "../MyLib"
    ]
}
```

External references enable the project to refer that.

```fsharp
// Foo.milone
module Foo.Program

open MyLib.X // denotes to ../MyLib/X.milone
```

- Foo/
    - Foo.milone
- MyLib/
    - X.milone

## Advanced topics

TODO: specify format of manifest file
