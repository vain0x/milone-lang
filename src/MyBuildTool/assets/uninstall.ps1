#!/bin/pwsh
# Uninstall milone command from your home directory.

Remove-Item -Force "$HOME/bin/milone" -ErrorAction SilentlyContinue
Remove-Item -Recurse -Force "$HOME/.milone" -ErrorAction SilentlyContinue
echo 'Uninstalled successfully!'
