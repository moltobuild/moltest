# 001 Standalone package — Status: In progress
## Goal
moltest is its own molto package that any project can add with
`molto add moltest --dev`, with no tie to molto or pickup.

## Acceptance criteria
- [x] AC1: `molto build` produces `build/debug/libmoltest.a` → check: `molto build`
- [x] AC2: `molto test` runs moltest's own suite and passes → test: `tests/test_assertions.c`
- [x] AC3: a failing check makes the run exit 1 and prints expected/actual/location → test: `failing_check_exits_one_and_reports_its_values`
- [ ] AC4: `molto fmt --check` and `molto lint` report no errors → check: VALIDATION commands
- [ ] AC5 (checked by hand 2026-10-03, automate): a project outside this repo uses it via `molto add moltest --dev --path <moltest>` and its suite runs → test: `consumer_project_runs` (scripted fixture)
- [ ] AC6: CI runs AC1-AC4 on Linux, macOS and Windows

## Design
See [ARCHITECTURE](../ARCHITECTURE.md) and [ADR 0001](../adr/0001-standalone-molto-package.md).

## Security notes
No new input surfaces; the child-process fixture must use moltest's temp helpers.

## Tasks
- [x] Split history from molto
- [x] Project.toml, LICENSE, NOTICE, .gitignore
- [x] First self-tests
- [x] `recipe.toml` so molto can consume moltest as a dependency
- [ ] Format sources (KI-1), triage lint (KI-2)
- [x] Child-process fixture for failure paths (spec 003)
- [ ] Consumer-project test
- [ ] CI workflows

## Out of scope
Plugin API changes (M3), publishing (M1 closing step), migrating molto/pickup (M2).
