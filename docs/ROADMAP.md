# Roadmap

## M0 - Standalone repository
- [x] History of `molto/modules/moltest` split into this repo (molto's copy is a superset of pickup's)
- [x] `Project.toml`: a static library built and tested with molto
- [x] Self-test suite runs under `molto test`
- [x] Docs scaffold, ADR 0001 (standalone package), ADR 0002 (plugin model)

## M1 - Ready to publish (spec 001)
- [x] Test macro renamed to `DESCRIBE` / `SKIP_TEST`, old names kept as aliases (spec 002, ADR 0003)
- [x] Setup/teardown hooks: BEFORE_ALL/AFTER_ALL per file, BEFORE_EACH/AFTER_EACH per test (spec 003, ADR 0004)
- [ ] Sources formatted with the molto preset; `molto fmt --check` clean
- [ ] `molto lint` warnings triaged (fixed or configured off with a reason)
- [x] Self-tests for failure reporting: run a fixture suite in a child process, check output and exit status
- [x] CI on Linux, macOS and Windows running `molto test`, plus a consumer project (`.github/workflows/ci.yml`)
- [ ] Style job becomes a gate (after KI-1, KI-2)
- [ ] Release 0.1.0 published to the molto registry

## M2 - Adoption in molto and pickup
- [ ] molto and pickup replace `modules/moltest` with `molto add moltest --dev`
- [ ] Their bootstrap Makefiles still build the suite (see ARCHITECTURE, open question)

## M3 - In-process plugin API v1 (ADR 0002, spec 004) — needed by moltest-coverage
- [x] Several reporters at once (`moltest_add_reporter`), the current single one kept as a shim
- [x] Versioned reporter struct (`api_version`), `on_test_start`, and `moltest_fail_run()` for plugins that gate the run
- [ ] Failure details in the test-end event
- [x] README "Writing a plugin"
- [ ] First real plugin: moltest-coverage (its own repo)

## M4 - Out-of-process events (ADR 0002)
- [ ] Built-in JSON Lines reporter (`--report=jsonl[:path]`) with a documented, versioned schema
- [ ] Example external consumer

## Non-goals
- Being required by molto or any molto project.
- Mocking frameworks, benchmarks or fuzzing inside moltest itself (plugins may do this).
- Runtime dependencies.

## Backlog
- Parametrized tests
- C++ ergonomics (`EXPECT_EQ` on `std::string`, exceptions)
