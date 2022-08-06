#!/bin/pwsh
# Uninstall milone command from your home directory.

# **IMPORTANT**
# The script must be sync with documentation: binary_package.md, INSTALL.md

$ErrorActionPreference = 'Stop'

$MILONE_CMD = $env:MILONE_CMD
if (!$MILONE_CMD) {
    $MILONE_CMD = "$env:USERPROFILE\.local\bin\milone.exe"
}

$MILONE_HOME = $env:MILONE_HOME
if (!$MILONE_HOME) {
    $MILONE_HOME = "$env:USERPROFILE\.local\share\milone"
}

$MILONE_CMD_DIR = [System.IO.Path]::GetDirectoryName($MILONE_CMD)

Remove-Item -Force $MILONE_CMD -ErrorAction SilentlyContinue
Remove-Item -Recurse -Force $MILONE_HOME
echo 'Uninstalled successfully!'
