# 002 DESCRIBE and SKIP_TEST — Status: Done
## Goal
Rename the test-definition macros (ADR 0003) without breaking existing suites.

## Acceptance criteria
- [x] AC1: `DESCRIBE(name)` defines and runs a test → test: `tests/test_assertions.c` (every case)
- [x] AC2: `SKIP_TEST(name, reason)` reports the test skipped and never runs its body → test: `skip_test_does_not_run_the_body`
- [x] AC3: `MOLTEST` and `MOLTEST_SKIP` still work → tests: `the_old_name_still_defines_a_test`, `the_old_skip_still_skips`
- [x] AC4: README, ARCHITECTURE and VALIDATION use the new names

## Design
Two new macros; the old ones are one-line aliases. Version 0.2.0.

## Security notes
None: compile-time names only.

## Tasks
- [x] Header, self-tests, docs, ADR 0003, version 0.2.0
- [ ] molto: `molto new` generates `DESCRIBE` (after this is on master)

## Out of scope
Removing the aliases; hooks (spec 003).
