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

## Workflow
See `docs/PLAN.md` for the current focus; every feature starts with a spec in `docs/specs/`.
