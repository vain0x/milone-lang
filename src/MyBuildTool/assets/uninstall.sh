#!/bin/sh
# Uninstall milone command from your home directory.

set -eu

rm "$HOME/bin/milone"
rm -rf "$HOME/.milone"
echo 'Uninstalled successfully!'
