#!/bin/sh
# Install milone command to your home directory.

# This script is placed at the root of package.

set -eu

VERSION=$(cat .milone/version)

# Ensure directories exist and non-directory doesn't resident.
mkdir -p "$HOME/bin"
mkdir -p "$HOME/.milone"

# Uninstall.
rm "$HOME/bin/milone"
rm -rf "$HOME/.milone"

# Install.
cp -R 'bin' "$HOME/bin"
cp -R '.milone' "$HOME/.milone"

# Information about PATH.
if ! milone --version >/dev/null
then
    echo "It's recommended to add $HOME/bin to \$PATH."
fi

# Finish.
echo "milone-lang v$VERSION is installed successfully!"
