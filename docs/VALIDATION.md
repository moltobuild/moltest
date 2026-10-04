# Validation

## Commands
| Check | Command |
|---|---|
| Build | `molto build` |
| Tests | `molto test` |
| Format | `molto fmt --check` |
| Lint | `molto lint` |
| Release build | `molto build --profile release` |

## CI
`.github/workflows/ci.yml` runs on every push to master and every PR, with the
molto release pinned in `MOLTO_VERSION` (installed and hash-checked by
`.github/install-molto.sh`):

| Job | Runs on | Checks |
|---|---|---|
| Test | Linux (gcc), macOS (clang), Windows (MSYS2 gcc) | `molto build`, `molto build --profile release`, `molto test` |
| Consumer | the same three | `molto new` + this checkout as `[dev-deps]` + its `molto test` (`.github/consumer.sh`), i.e. `recipe.toml` |
| Style | Linux, LLVM 19 | `molto fmt --check`, `molto lint`; **not a gate** until KI-1 and KI-2 close |

Bumping molto is a one-line change to `MOLTO_VERSION`, made in its own PR.

## Strategy
- moltest tests itself: `tests/` uses `DESCRIBE()` and runs under `molto test`.
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
