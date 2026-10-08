# Development

## Setup
Install molto (and pickup, which provides the compiler). Then:

```sh
molto build   # build/debug/libmoltest.a
molto test    # build and run moltest's own suite
```

There is no Makefile: moltest is built with molto only.

## Using a local checkout from another project
```sh
molto add moltest --dev --path ../moltest
```

## Conventions
- C23 (`-std=c2x`), `[[nodiscard]]` on calls whose result must be checked.
- Style and lint come from `format.json` and `linter.json` (molto preset).
- Public symbols start with `moltest_` or `MOLTEST_`; assertion macros are `EXPECT_*` / `ASSERT_*`.
- Commits: Conventional Commits; one commit per change.

## Releasing
1. One PR bumps the version in `Project.toml` and
   `MOLTEST_VERSION` (`src/moltest.c`); `.github/check-version.sh <version>`
   checks all three.
2. After it merges, tag the merge commit and push the tag:
   `git tag -a v0.3.0 -m "moltest 0.3.0" && git push origin v0.3.0`.
3. `.github/workflows/release.yml` checks the tag against the three, runs the
   CI on three platforms, and publishes the GitHub Release. Consumers pin it
   with `tag = "v0.3.0"`.

Running the Release workflow by hand rehearses all of it without publishing.

## Workflow
See `docs/PLAN.md` for the current focus; every feature starts with a spec in `docs/specs/`.
