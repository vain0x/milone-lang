# Binary Package

Binary packages are distributed in [GitHub Releases](https://github.com/vain0x/milone-lang/releases).
Package file extension is either `.tar.gz` or `.zip`.

## Usage

- Download and unarchive a package file
- Follow instruction written in `INSTALL.md`

----

## Package Structure

Package should consist of these files.

- `milone-X.Y.Z/` (root of package)
    - `.milone/`
    - `bin/`
    - `INSTALL.md` (this)
    - `install.sh`
    - `install.ps1`
    - `LICENSE`
    - `README.md`

## Generated Files by Installation

Installation script should place these files (and these files only):

- `$HOME/bin/`
    - `milone.exe` (or `milone`)
- `$HOME/.milone/`
    - `bin/`
        - `milone_dotnet/`
        - `milone_lsp/`
        - `ninja` (Linux only)
    - `src/`
        - `libmilonert/`
        - `MiloneCore/`
        - `Std/`
    - `version`

where `$HOME` is your home directory.
