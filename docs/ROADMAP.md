# Roadmap

## M0 - Standalone repository
- [x] History of `molto/modules/moltest` split into this repo (molto's copy is a superset of pickup's)
- [x] `Project.toml`: a static library built and tested with molto
- [x] Self-test suite runs under `molto test`
- [x] Docs scaffold, ADR 0001 (standalone package), ADR 0002 (plugin model)

## M1 - Ready to publish (spec 001)
- [x] Test macro renamed to `DESCRIBE` / `SKIP_TEST`, old names kept as aliases (spec 002, ADR 0003)
- [ ] Setup/teardown hooks: BEFORE_ALL/AFTER_ALL per file, BEFORE_EACH/AFTER_EACH per test (spec 003, ADR 0004)
- [ ] Sources formatted with the molto preset; `molto fmt --check` clean
- [ ] `molto lint` warnings triaged (fixed or configured off with a reason)
- [ ] Self-tests for failure reporting: run a fixture suite in a child process, check output and exit status
- [ ] CI on Linux, macOS and Windows running `molto test`
- [ ] Release 0.1.0 published to the molto registry

## M2 - Adoption in molto and pickup
- [ ] molto and pickup replace `modules/moltest` with `molto add moltest --dev`
- [ ] Their bootstrap Makefiles still build the suite (see ARCHITECTURE, open question)

## M3 - In-process plugin API v1 (ADR 0002)
- [ ] Several reporters at once (`moltest_add_reporter`), the current single one kept as a shim
- [ ] Versioned reporter struct (`api_version`) and failure details in the test-end event
- [ ] `docs/Plugins.md` for plugin authors, plus a reference plugin (`moltest-junit`)

## M4 - Out-of-process events (ADR 0002)
- [ ] Built-in JSON Lines reporter (`--report=jsonl[:path]`) with a documented, versioned schema
- [ ] Example external consumer

## Non-goals
- Being required by molto or any molto project.
- Mocking frameworks, benchmarks or fuzzing inside moltest itself (plugins may do this).
- Runtime dependencies.

## Backlog
- `moltest-coverage` plugin (gcov/llvm-cov summary per test file)
- Parametrized tests
- C++ ergonomics (`EXPECT_EQ` on `std::string`, exceptions)
