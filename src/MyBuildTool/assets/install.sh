#!/bin/sh
# Install milone command to your home directory.

# **IMPORTANT**
# The script must be sync with documentation: binary_package.md, INSTALL.md

set -eu

NINJA_URL='https://github.com/ninja-build/ninja/releases/download/v1.11.0/ninja-linux.zip'

DEFAULT_MILONE_CMD=${XDG_BIN_HOME:-$HOME/.local/bin}/milone
DEFAULT_MILONE_HOME=${XDG_DATA_HOME:-$HOME/.local/share}/milone

MILONE_CMD=${MILONE_CMD:-$DEFAULT_MILONE_CMD}
MILONE_HOME=${MILONE_HOME:-$DEFAULT_MILONE_HOME}

MILONE_CMD_DIR=$(dirname "$MILONE_CMD")
VERSION=$(cat share/milone/version)

# Download ninja.
curl -sL "$NINJA_URL" -o 'ninja.zip'
unzip 'ninja.zip'
rm 'ninja.zip'

# Ensure directories exist and non-directory doesn't resident.
mkdir -p "$MILONE_CMD_DIR"
mkdir -p "$MILONE_HOME"

# Uninstall.
rm -f "$MILONE_CMD"
rm -rf "$MILONE_HOME"

# Install.
cp 'bin/milone' "$MILONE_CMD"
cp -R 'share/milone' "$MILONE_HOME"
mv 'ninja' "$MILONE_HOME/bin/ninja"

echo "milone-lang v$VERSION is installed successfully!"
