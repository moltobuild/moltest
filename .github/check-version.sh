#!/bin/sh
#
# Every place this package states its version, against the one asked for.
#
#   check-version.sh <version>      e.g. 0.3.0, or v0.3.0 (a tag)
#
# Project.toml describes both the package and its consumer interface, and
# MOLTEST_VERSION is what the runner prints. A release where they disagree has
# happened once already (the runner said 0.1.0 at 0.2.0); this makes it a red
# run instead of a published one.
set -eu

want=${1#v}
fail=0

check() {
    if [ "$2" = "$want" ]; then
        echo "ok   $1: $2"
    else
        echo "FAIL $1: $2, expected $want"
        fail=1
    fi
}

toml_version() {
    sed -n 's/^version *= *"\(.*\)".*/\1/p' "$1" | head -1
}

check Project.toml "$(toml_version Project.toml)"
check src/moltest.c "$(sed -n 's/^#define MOLTEST_VERSION "\(.*\)".*/\1/p' src/moltest.c)"

exit $fail
