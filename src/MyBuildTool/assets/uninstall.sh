#!/bin/sh
# Uninstall milone command from your home directory.

# **IMPORTANT**
# The script must be sync with documentation: binary_package.md, INSTALL.md

set -eu

DEFAULT_MILONE_CMD=${XDG_BIN_HOME:-$HOME/.local/bin}/milone
DEFAULT_MILONE_HOME=${XDG_DATA_HOME:-$HOME/.local/share}/milone

MILONE_CMD=${MILONE_CMD:-$DEFAULT_MILONE_CMD}
MILONE_HOME=${MILONE_HOME:-$DEFAULT_MILONE_HOME}

rm "$MILONE_CMD"
rm -rf "$MILONE_HOME"
echo 'Uninstalled successfully!'
