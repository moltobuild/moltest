# Known issues

## KI-1 Inherited sources are not formatted with the molto preset — Status: Open
- Repro: `molto fmt --check`
- Expected: no changes. Actual: ~700 changed lines (e.g. `if (` vs `if(`, one-line functions).
- Cause: inside molto, `modules/` was never formatted. Planned in M1.
- CI: the `style` job reports it without failing the run until this closes.

## KI-2 `molto lint` reports 13 warnings — Status: Open
- Repro: `molto lint`
- Mostly `bugprone_unsafe_functions` (`rewind`) and multi-level pointer conversions in `src/moltest.c`. Triage in M1.
