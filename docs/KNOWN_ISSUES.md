# Known issues

## KI-1 Inherited sources are not formatted with the molto preset — Status: Open
- Repro: `molto fmt --check`
- Expected: no changes. Actual: ~700 changed lines (e.g. `if (` vs `if(`, one-line functions).
- Cause: inside molto, `modules/` was never formatted. Planned in M1.
- CI: the `style` job reports it without failing the run until this closes.

## KI-2 `molto lint` reports 13 warnings — Status: Open
- Repro: `molto lint`
- Mostly `bugprone_unsafe_functions` (`rewind`) and multi-level pointer conversions in `src/moltest.c`. Triage in M1.

## KI-3 A C17 consumer cannot compile moltest.h, and glibc hides what moltest.c calls — Status: Resolved
- Repro: `molto new x` (std c17) + moltest as `[dev-deps]`, then `molto test` on Apple clang 15 or on Linux gcc.
- Expected: the consumer's suite builds. Actual: `[[nodiscard]]` is a syntax error before C23; on glibc `fileno`, `setenv`, `mkdtemp` are undeclared under a strict `-std` because recipe.toml defined no feature macro.
- Found by the CI `consumer` job (PR #3). Fixed by `MOLTEST_NODISCARD` in moltest.h and `_DEFAULT_SOURCE` in recipe.toml; the `consumer` job is the regression test.
