# Binary Package

Binary packages are distributed in [GitHub Releases](https://github.com/vain0x/milone-lang/releases).
Package file extension is either `.tar.gz` or `.zip`.

## Usage

- Download and unarchive a package
- Follow the instruction written in `INSTALL.md`

----

## Package Structure

Package should consist of these files.

- `milone-X.Y.Z/`
    - `bin/`
    - `share/`
    - `INSTALL.md`
    - `install.ps1`
    - `install.sh`
    - `LICENSE`
    - `README.md`
    - `uninstall.ps1`
    - `uninstall.sh`

## Install Scripts

This section describes the behavior of install scripts.

## Prerequisites

The install script requires:

- On Windows: *nothing*
- On Linux: curl, unzip

### Files Written

The install script copies some files and directories to the user's home directory (`$HOME`).
Only these files are created:

- `$HOME/.local/bin/`
    - `milone` (on Linux only)
    - `milone.exe` (on Windows only)
- `$HOME/.local/share/milone/`
    - `bin/`
        - `milone_dotnet/`
        - `milone_lsp/`
        - `ninja` (on Linux only)
    - `src/`
        - `libmilonert/`
        - `MiloneCore/`
        - `Std/`
    - `version`

### Network Access

- On Windows: *nothing*
- On Linux: `ninja` binary is downloaded from GitHub

### Configuration

The install script can be configured with environment variables.

- `$MILONE_CMD`:
    - Specify the location of the executable.
    - `$MILONE_CMD` replaces `$HOME/.local/bin/milone`.
- `$MILONE_HOME`:
    - Specify the location of the system root directory.
    - `$MILONE_HOME` replaces `$HOME/.local/share/milone`.

## Uninstall Scripts

The uninstall script deletes all files created by the install script.

Configuration is the same as install scripts.

----

### Appendix: XDG Base Directory

Directory structure is inspired with [XDG Base Directory](https://specifications.freedesktop.org/basedir-spec/basedir-spec-latest.html).
