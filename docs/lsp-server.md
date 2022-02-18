# LSP server

WIP: write document about MiloneLspServer

## Formatting

Currently LSP server's formatting feature just executes [fantomas-tool](https://github.com/fsprojects/fantomas).

### Fantomas

*Fantomas* is de facto standard formatting tool for F#.

To enable formatting feature, you need to install it locally (in workspace) or globally (in system).

- To install locally:
    - Read this article: [Tutorial: Install and use .NET local tools - .NET CLI | Microsoft Docs](https://docs.microsoft.com/en-us/dotnet/core/tools/local-tools-how-to-use)
    - Basically, `dotnet new tool-manifest && dotnet tool install fantomas-tool`
- To install globally:
    - Read this article: [Tutorial: Install and use a .NET global tool - .NET CLI | Microsoft Docs](https://docs.microsoft.com/en-us/dotnet/core/tools/global-tools-how-to-use)
    - Basically, `dotnet tool install -g fantomas-tool` and add `$HOME/.dotnet/tool` to PATH

### Versions of toolchain

Fantomas sometimes changes formatting algorithm.
You want to use the same version of fantomas with the one used by F# IDE for consistent formatting.

Check documentation and release notes, of toolchain like this:

- [fsharp/FsAutoComplete](https://github.com/fsharp/FsAutoComplete) (Core library)
- [ionide/ionide-vscode-fsharp](https://github.com/ionide/ionide-vscode-fsharp) (Front-end for VSCode)
