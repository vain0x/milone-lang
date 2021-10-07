#!/bin/pwsh
# Install milone command to your home directory.

# This script is placed at the root of package.

$ErrorActionPreference = 'Stop'

$VERSION = $(Get-Content '.milone/version').Trim()

# Ensure directories exist and non-directory doesn't resident.
New-Item -Type Directory -Force "$HOME/bin"
New-Item -Type Directory -Force "$HOME/.milone"

# Uninstall.
Remove-Item -Force "$HOME/bin/milone.exe" -ErrorAction SilentlyContinue
Remove-Item -Recurse -Force "$HOME/.milone"

# Install.
Copy-Item -Force 'bin/milone.exe' -Destination "$HOME/bin/milone.exe"
Copy-Item -Recurse -Force '.milone' -Destination "$HOME/.milone"

# Information about PATH.
$underPath = $true
try {
    milone --version | Out-Null
} catch {
    $underPath = $false
}
if (!$underPath) {
    echo "It's recommended to add $HOME/bin to `$PATH."
}

# Finish.
echo "milone-lang v$VERSION is installed successfully!"
