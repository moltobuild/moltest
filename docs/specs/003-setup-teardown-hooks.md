# 003 Setup and teardown hooks — Status: Done
## Goal
`BEFORE_ALL`, `AFTER_ALL`, `BEFORE_EACH`, `AFTER_EACH` per test file, so
teardown runs even when an assertion ends a test early ([ADR 0004](../adr/0004-setup-teardown-hooks.md)).

## Acceptance criteria
- [x] AC1: BEFORE_EACH runs before every running test of its file, and only its file → test: `before_each_runs_once_per_test`
- [x] AC2: AFTER_EACH runs after a test that passed, failed, returned through `ASSERT_*`, or called `SKIP()` → test: `after_each_runs_however_the_test_ends` (child process)
- [x] AC3: BEFORE_ALL runs once before the file's first running test; AFTER_ALL once after its last → test: `all_hooks_run_once_per_file`
- [x] AC4: tests skipped by `SKIP_TEST` or filtered by `-k` run no hooks; a file with nothing to run runs no hooks → test: `filtered_tests_run_no_hooks` (child process), `a_registered_skip_runs_no_hooks`
- [x] AC5: a failing BEFORE_EACH fails its test without running the body; AFTER_EACH still runs → test: `failing_before_each_fails_the_test` (child process)
- [x] AC6: a failing BEFORE_ALL fails every test of the file without running them; AFTER_ALL still runs → test: `failing_before_all_fails_the_file` (child process)
- [x] AC7: a failing AFTER_EACH fails its test; a failing AFTER_ALL fails the file's last test and names the hook → test: `failing_after_hooks_fail_a_test` (child process)
- [x] AC8: exit status is 1 whenever a hook failed → covered by AC5–AC7
- [x] AC9: README documents the four hooks with an example → README "Setup and teardown"

## Design
- Macros define a `static` function and a constructor that registers it with
  `__FILE__`, like `DESCRIBE`. Registry: one entry per file, four slots.
- The per-file loop in `moltest_run` calls BEFORE_ALL lazily before the first
  selected, non-skipped test and AFTER_ALL after the loop if it ran.
- `run_one` gains: BEFORE_EACH → body (unless a hook failed) → AFTER_EACH, all
  inside the existing capture and environment save/restore.
- Child-process harness: fixture tests live in `tests/fixtures_*.c`, `SKIP()`
  unless `MOLTEST_FIXTURE` names them; the parent re-runs its own binary with
  `-k <file>` and that variable, and checks output and exit status.

## Security notes
No new input. The child-process harness passes only fixed arguments and one
environment variable to the test binary itself.

## Tasks
- [x] Hook registry and macros in moltest.h
- [x] Runner: per-file and per-test calls, failure attribution
- [x] Child-process harness, `tests/fixture_runner.h`, with `moltest_self_path()` (also unblocks spec 001 AC3)
- [x] Tests for AC1–AC8 (`tests/test_hooks.c`, `tests/test_runner_reports.c`)
- [x] README section, ARCHITECTURE data flow, ROADMAP

## Out of scope
Global (per-binary) hooks, hooks shared across files, parametrized tests.
