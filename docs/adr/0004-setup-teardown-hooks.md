# 0004 Setup and teardown hooks per file — Status: Proposed
Date: 2026-10-04

## Context
moltest has no setup/teardown. Suites write it by hand (`sandbox_open()` at the
top of a test, `sandbox_close()` at the bottom), and `ASSERT_*` returns from the
test, so a failing assertion skips the teardown: the temporary directory or the
environment it changed leaks into every later test. pytest (fixtures,
`setup_module`) and unittest (`setUp`, `setUpClass`) solve this in the runner.

## Decision
Four file-scope macros, at most one of each per test file:

```c
BEFORE_ALL()  { ... }   /* once, before the first test of this file that runs */
AFTER_ALL()   { ... }   /* once, after the last one, if BEFORE_ALL ran */
BEFORE_EACH() { ... }   /* before every test of this file that runs */
AFTER_EACH()  { ... }   /* after every such test, always */
```

- **Scope is the file**, the unit the runner already groups by (`on_file_start`
  / `on_file_end`). A hook in `test_parser.c` never runs for `test_lexer.c`.
- **AFTER_EACH runs however the test ended**: passed, failed, `ASSERT_*`
  returned, or `SKIP()` from inside. That is the reason for the feature.
- **Skipped or filtered tests** (`SKIP_TEST`, `-k`) run no hooks; a file with no
  test to run runs neither BEFORE_ALL nor AFTER_ALL.
- **Assertions work in hooks.** A failure in BEFORE_EACH fails that test without
  running its body (AFTER_EACH still runs). A failure in BEFORE_ALL fails every
  test of the file without running them (AFTER_ALL still runs). A failure in
  AFTER_EACH fails that test; in AFTER_ALL, the file's last test, with the hook
  named in the report.
- **State** is shared through `static` variables in the test file, the C idiom.
- **Environment**: restored after AFTER_EACH (it already is after each test);
  what BEFORE_ALL sets lasts until after AFTER_ALL.
- **Output** of a hook is captured and shown with the test it belongs to.
- A second hook of the same kind in one file is a compile error (redefinition).

## Alternatives considered
- **Fixture structs per test (Google Test `TEST_F`)**: typed state, but every
  test names its fixture and C has no constructors to run it.
- **pytest-style injected fixtures**: needs reflection C does not have; the
  macro machinery would cost more than it saves.
- **Global hooks for the whole binary**: useful, but a different scope; can be
  added later as `BEFORE_RUN`/`AFTER_RUN` without changing these.
- **`SETUP`/`TEARDOWN` names**: xUnit-style, but say nothing about how often;
  `*_EACH`/`*_ALL` do, and match Jest/Mocha, which `DESCRIBE` already echoes.

## Consequences
- Four new unprefixed public names (like `DESCRIBE`, `EXPECT_*`).
- Reporters (ADR 0002) see hook failures through the test they are charged to;
  no new callback is needed now.
- Tests of the failure paths need a fixture suite run in a child process (the
  harness for that is the same one spec 001 AC3 needs).
