# 0003 The test macro is DESCRIBE — Status: Accepted
Date: 2026-10-04

## Context
A test is defined with `MOLTEST(name)` and a skipped one with
`MOLTEST_SKIP(name, reason)`. The maintainer wants test definitions to read as
descriptions of behaviour: `DESCRIBE(parser_rejects_a_trailing_comma)`.
`molto new` already generates suites that use `MOLTEST`, and takes moltest
from the `master` branch, so removing the old name breaks every project it
created.

## Decision
- `DESCRIBE(name)` defines a test; `SKIP_TEST(name, reason)` defines one that
  is reported as skipped without running.
- `MOLTEST` and `MOLTEST_SKIP` stay as deprecated aliases, silently (no
  compile-time warning: suites of hundreds of tests would drown in it).
- `SKIP(reason)`, the statement that skips from inside a running test, keeps
  its name. `MOLTEST_FAKE` keeps its name: it defines a fake program, not a test.
- Released as 0.2.0, with `molto new` generating `DESCRIBE` afterwards.

## Alternatives considered
- Remove the old names: breaks every suite already written, for no gain.
- `SKIP(name, reason)` for the definition: collides with the `SKIP(reason)`
  statement; one would be file scope and the other a statement in a body.
- `TEST`/`IT`: conventional, but `TEST` collides with other frameworks' macros
  and the maintainer chose `DESCRIBE`. Note that in Jest/RSpec `describe`
  groups tests; here it defines one.

## Consequences
- Two spellings exist until the aliases are removed (not before 1.0.0, and only
  with an ADR that supersedes this one).
- `DESCRIBE` is an unprefixed name, like `EXPECT_*`; a project that defines its
  own `DESCRIBE` cannot include moltest.h unchanged.

## Update 2026-10-05
`molto new` no longer takes moltest from `master`: since molto 0.53.0
(moltobuild/molto#103) it pins the newest release tag when the project is
created, or offline the newest release that molto knows. A release of moltest
no longer reaches existing projects by itself. The aliases stay as decided
above: projects created before then still use `MOLTEST`.
