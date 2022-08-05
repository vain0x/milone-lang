#!/bin/pwsh
# Install milone command to your home directory.

# **IMPORTANT**
# The script must be sync with documentation: binary_package.md, INSTALL.md

$ErrorActionPreference = 'Stop'

$MILONE_CMD = $env:MILONE_CMD
if (!$MILONE_CMD) {
    $MILONE_CMD = "$env:USERPROFILE/.local/bin/milone.exe"
}

$MILONE_HOME = $env:MILONE_HOME
if (!$MILONE_HOME) {
    $MILONE_HOME = "$env:USERPROFILE/.local/share/milone"
}

$MILONE_CMD_DIR = [System.IO.Path]::GetDirectoryName($MILONE_CMD)

$VERSION = $(Get-Content 'share/milone/version').Trim()

# Ensure directories exist and non-directory doesn't resident.
New-Item -Type Directory -Force $MILONE_CMD_DIR | out-null
New-Item -Type Directory -Force $MILONE_HOME | out-null

# Uninstall.
Remove-Item -Force $MILONE_CMD -ErrorAction SilentlyContinue
Remove-Item -Recurse -Force $MILONE_HOME

# Install.
Copy-Item -Force 'bin/milone.exe' -Destination $MILONE_CMD
Copy-Item -Recurse -Force 'share/milone' -Destination $MILONE_HOME
Copy-Item 'uninstall.ps1' "$MILONE_HOME/uninstall.ps1"

# Information about PATH.
$underPath = $true
try {
    milone --version | Out-Null
} catch {
    $underPath = $false
}
if (!$underPath) {
    echo "It's recommended to add $MILONE_CMD_DIR to `$PATH."
}

# Finish.
echo "milone-lang v$VERSION is installed successfully!"
