# milone-lang support for VSCode

WIP

## Install

Not available yet.

## Features

- [ ] Syntax highlighting
- [ ] Hover on symbols for tooltip
- [ ] Documentation symbol highlighting
- [ ] Find and jump to definitions and references
- [ ] Rename
- [ ] Completion

----

## Development

### Dev: Prerequisites

- Visual Studio Code
- Node.js (>= 12)
- Git (on Window, in order to run shell scripts)

### Dev: Build Scripts

- `install`: Build the extension from source and install it to local VSCode.
    - Make sure to bump up the version number before installation. (It sometimes works incorrectly when you installed that of different edition with yet the same version number installed before, for some reason.)
- `uninstall`: Uninstall the extension from local VSCode.

## See also

- F# syntax definition built-in to VSCode: [vscode/fsharp.tmLanguage.json](https://github.com/microsoft/vscode/blob/d5e12a12ddcdbffa565ea36aec17d94df7c9f3d9/extensions/fsharp/syntaxes/fsharp.tmLanguage.json)
- Monokai color theme for VSCode: [vscode/monokai-color-theme.json at f74e473238aca7b79c08be761d99a0232838ca4c · microsoft/vscode](https://github.com/microsoft/vscode/blob/f74e473238aca7b79c08be761d99a0232838ca4c/extensions/theme-monokai/themes/monokai-color-theme.json)
- Official LSP website: [Overview](https://microsoft.github.io//language-server-protocol/overviews/lsp/overview/)
    - Unofficial Japanese translation: [tennashi/lsp_spec_ja\: LSP 仕様の日本語訳](https://github.com/tennashi/lsp_spec_ja)
- Article series: [LSP学習記 #1](https://qiita.com/vain0x/items/d050fe7c8b342ed2004e)
