# Validation

## Commands
| Check | Command |
|---|---|
| Build | `molto build` |
| Tests | `molto test` |
| Format | `molto fmt --check` |
| Lint | `molto lint` |
| Release build | `molto build --profile release` |

## Strategy
- moltest tests itself: `tests/` uses `MOLTEST()` and runs under `molto test`.
- Passing paths are checked in-process. Failure paths (a failing check, exit
  status, output format) need a fixture suite run in a child process (M1).
- Every acceptance criterion in a spec names the test that covers it.

## Definition of Done
- [ ] All acceptance criteria have passing tests
- [ ] Build, tests, format and lint pass
- [ ] SECURITY.md checklist reviewed
- [ ] Spec, ROADMAP and PLAN "Current focus" updated
- [ ] ARCHITECTURE / DEPENDENCIES / ADRs updated if affected
- [ ] PROGRESS entry added, commit done, graphs refreshed
