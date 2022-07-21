#!/bin/sh
# Install milone command to your home directory.

# This script is placed at the root of package.

set -eu

NINJA_URL='https://github.com/ninja-build/ninja/releases/download/v1.11.0/ninja-linux.zip'
VERSION=$(cat .milone/version)

# Download ninja.
curl -sL "$NINJA_URL" -o 'ninja.zip'
unzip 'ninja.zip'
rm 'ninja.zip'

# Ensure directories exist and non-directory doesn't resident.
mkdir -p "$HOME/bin"
mkdir -p "$HOME/.milone"

# Uninstall.
rm -f "$HOME/bin/milone"
rm -rf "$HOME/.milone"

# Install.
cp 'bin/milone' "$HOME/bin/milone"
cp -R '.milone' "$HOME/.milone"
mv 'ninja' "$HOME/.milone/bin/ninja"

# Information about PATH.
if ! milone --version >/dev/null
then
    echo "It's recommended to add $HOME/bin to \$PATH."
fi

# Finish.
echo "milone-lang v$VERSION is installed successfully!"
