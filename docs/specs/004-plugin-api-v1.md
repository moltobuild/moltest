# 004 Plugin API v1 — Status: Draft
## Goal
Let packages such as moltest-coverage plug into a run by being linked:
several reporters at once, registered from a constructor, versioned, and able
to fail the run ([ADR 0002](../adr/0002-plugin-model.md), M3).

## Acceptance criteria
- [ ] AC1: `moltest_add_reporter()` called from a constructor (before `main`) registers a reporter; up to `MOLTEST_REPORTERS_MAX` (8) coexist and are called in registration order → test: `reporters_are_called_in_order`
- [ ] AC2: `moltest_set_reporter()` keeps working, as `moltest_add_reporter()` → test: `set_reporter_still_registers`
- [ ] AC3: `moltest_reporter.api_version` must equal `MOLTEST_REPORTER_API` (1); a reporter with another version is refused at the start of the run with a message naming it, and the run exits 1 → test: `wrong_api_version_is_refused` (child process)
- [ ] AC4: a new `on_test_start(file, name, ctx)` callback runs before each test's hooks → test: `test_start_precedes_before_each`
- [ ] AC5: `moltest_fail_run(reason)`, called from `on_run_end`, makes the run exit 1 and prints the reason after the summary, even when every test passed → test: `a_reporter_can_fail_the_run` (child process)
- [ ] AC6: `on_run_end` runs after the summary is printed, for every reporter, before the exit status is decided → covered by AC5
- [ ] AC7: README documents writing a plugin, with a minimal example → README "Writing a plugin"

## Design
```c
#define MOLTEST_REPORTER_API 1
#define MOLTEST_REPORTERS_MAX 8

typedef struct {
    int api_version;                       /* MOLTEST_REPORTER_API */
    const char *name;                      /* for messages: "moltest_coverage" */
    void (*on_run_start)(size_t files, size_t tests, void *ctx);
    void (*on_file_start)(const char *file, void *ctx);
    void (*on_test_start)(const char *file, const char *name, void *ctx);
    void (*on_test_end)(const char *file, const char *name, moltest_status status,
                        double seconds, void *ctx);
    void (*on_file_end)(const char *file, size_t done, size_t total, void *ctx);
    void (*on_run_end)(const moltest_summary *summary, void *ctx);
    void *ctx;
} moltest_reporter;

void moltest_add_reporter(const moltest_reporter *reporter);
void moltest_fail_run(const char *reason);
```
Adding `api_version` and `name` first changes the struct's layout: a reporter
written with positional initializers for 0.2.0 stops compiling, which is
intended (designated initializers keep compiling, with `api_version` 0 refused
by AC3). Registration needs no allocation: a static array of pointers.

## Security notes
Reporters are linked code with full trust (SECURITY.md); the array is bounded
and a 9th registration is refused with a message, not written past the end.

## Tasks
- [ ] Header: struct, constants, two functions
- [ ] Runner: reporter array, callbacks, version check, fail_run reasons
- [ ] Tests AC1-AC6 (child-process harness from spec 003)
- [ ] README "Writing a plugin"; ADR 0002 consequences; version 0.3.0

## Out of scope
Failure details in `on_test_end` (later, with per-test contexts); the JSON
event stream (M4).
