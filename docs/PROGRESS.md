# Progress

## 2026-10-03 — M0 standalone repository
- Done: split `molto/modules/moltest` history into this repo; Project.toml (static library); self-test suite; docs scaffold; ADRs 0001-0002
- Commit: see `git log`
- Tests: `molto test` 5 passed, 1 skipped; `molto fmt --check` fails on inherited sources; `molto lint` 0 errors, 13 warnings
- Next: M1, format the inherited sources with the molto preset

## 2026-10-03 — recipe.toml
- Done: source recipe so `[dev-deps] moltest = { path = ... }` works; checked with a scratch lib project
- Commit: see `git log`
- Tests: `molto test` passes here; consumer project builds and its moltest suite passes
- Next: publish 0.1.0 to the registry (it reports no package called 'moltest')

## 2026-10-04 — install from git
- Done: README documents `molto add git+https://github.com/moltobuild/moltest --dev`; molto (branch feat/new-lib-default) gained `git+<url>` and a library default for `molto new` that brings moltest
- Commit: see `git log`
- Tests: checked by hand: `molto add git+file://<this repo> --dev` then `molto test` in a new library
- Next: push this repo to github.com/moltobuild/moltest so the URL resolves

## 2026-10-04 — spec 002 DESCRIBE
- Done: `DESCRIBE` / `SKIP_TEST`, `MOLTEST` / `MOLTEST_SKIP` kept as aliases; ADR 0003; version 0.2.0
- Commit: see `git log`
- Tests: `molto test` 6 passed, 3 skipped (all skips intended)
- Next: molto's `molto new` template generates `DESCRIBE`; spec 003 hooks

## 2026-10-04 — spec 003 hooks
- Done: BEFORE_ALL / AFTER_ALL / BEFORE_EACH / AFTER_EACH per file; `moltest_self_path()`; child-process fixture harness (closes spec 001 AC3); ADR 0004 accepted; runtime version string 0.2.0
- Commit: see `git log`
- Tests: `molto test` 15 passed, 14 skipped (fixtures and intended skips); lint unchanged at 13 warnings (KI-2)
- Next: KI-1 formatting, KI-2 lint, CI workflows (M1)

## 2026-10-04 — CI on GitHub Actions
- Done: `.github/workflows/ci.yml` (test and consumer on Linux, macOS, Windows; style reported, not gated); `install-molto.sh` pins and hash-checks molto 0.46.0
- Commit: see `git log`
- Tests: install script, suite and consumer script checked locally on macOS with molto 0.46.0; the runners are checked by the first PR run
- Next: KI-1 and KI-2, then make the style job a gate

## 2026-10-04 — spec 004 drafted
- Done: plugin API v1 spec (several reporters, constructor registration, api_version, on_test_start, moltest_fail_run), driven by moltest-coverage's design
- Commit: see `git log`
- Tests: none (spec only)
- Next: implement spec 004

## 2026-10-04 — spec 004 plugin API v1
- Done: up to 8 reporters registered from constructors, api_version check, on_test_start, moltest_fail_run; README "Writing a plugin"; version 0.3.0
- Commit: see `git log`
- Tests: `molto test` 21 passed, 17 skipped (fixtures and intended skips); lint unchanged at 13 (KI-2)
- Next: moltest-coverage M2 (its spec 001)

## 2026-10-05 — M2 adoption done
- Done: molto (#92) and pickup (#26) take moltest v0.3.0 from molto's store; their Makefiles hand `make test` to molto; molto measures itself with moltest-coverage 0.1.1; releases are published by tag (v0.3.0)
- Commit: see `git log`
- Tests: molto and pickup CI green on Linux, macOS and Windows with moltest v0.3.0
- Next: KI-1 (formatting) and KI-2 (lint), then make the style job a gate
