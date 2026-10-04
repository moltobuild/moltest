#!/bin/sh
#
# Make a library with `molto new`, point its moltest at the checkout given as
# $1, and run its suite. This is the path a user takes, through recipe.toml.
set -eu

moltest=$1
cd "$(mktemp -d)"
molto new consumer
cd consumer
# The template takes moltest from git; this replaces it with the checkout
# under test, in place.
molto add moltest --dev --path "$moltest"
grep -n moltest Project.toml
molto test
