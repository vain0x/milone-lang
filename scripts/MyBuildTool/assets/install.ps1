#!/bin/pwsh
# Install milone command to your home directory.

# This script is placed at the root of package.

$ErrorActionPreference = 'Stop'

$HOME = $env:USERPROFILE
$VERSION = $(get-content '.milone/version').Trim()

# Ensure directories exist and non-directory doesn't resident.
new-item -type directory -force "$HOME/bin"
new-item -type directory -force "$HOME/.milone"

# Uninstall.
remove-item -force "$HOME/bin/milone"
remove-item -recurse -force "$HOME/.milone"

# Install.
copy-item -recurse 'bin' -destination "$HOME/bin"
copy-item -recurse '.milone' -destination "$HOME/.milone"

# Information about PATH.
$underPath = $true
try {
    milone --version | out-null
} catch ($ex) {
    $underPath = $false
}
if (!$underPath) {
    echo "It's recommended to add $HOME/bin to \$PATH."
}

# Finish.
echo "milone-lang v$VERSION is installed successfully!"
