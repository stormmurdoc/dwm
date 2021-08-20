#!/usr/bin/env sh
#
# -e: stops the script on errors
# -u: stops the script on unset variables
# -o pipefail : fail the whole pipeline if
#               a command fail

set -euo pipefail

./getdwmkeys.sh ../config.h markdown

