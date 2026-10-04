# Architecture

## Components
| Path | Role |
|---|---|
| `include/moltest.h` | Public API: `DESCRIBE()` / `SKIP_TEST()` registration (deprecated aliases `MOLTEST`, `MOLTEST_SKIP`), `EXPECT_*`/`ASSERT_*`, outcome control, reporter API, fixture helpers (temp dirs/files, fake programs, argv logs) |
| `src/moltest.c` | Registry, runner, output capture, default reporter, option parsing, fake-program support |
| `src/moltest_main.c` | Default `main()`: `return moltest_run(argc, argv);` |
| `tests/` | moltest's own suite, run by moltest. `fixtures_*.c` are suites the parent runs in a child process (`fixture_runner.h`) to see failures from outside |

## Data flow
1. Each `DESCRIBE(name)` registers itself through a constructor before `main()`.
2. `moltest_run()` parses options (`-k`, `-v`, `-s`, `--list`, `--color`), groups tests per file and runs them.
3. Per file, BEFORE_ALL runs before the first test that runs and AFTER_ALL
   after the last; per test, BEFORE_EACH, the body, then AFTER_EACH, all inside
   the test's output capture and environment restore ([ADR 0004](adr/0004-setup-teardown-hooks.md)).
4. Every outcome goes to the built-in reporter and to the extra reporter, if one is set (`moltest_set_reporter`).
5. Exit status: 0 when nothing failed, 1 otherwise.

## Packaging
A molto package with `artifact = "static"` ([ADR 0001](adr/0001-standalone-molto-package.md)).
`Project.toml` builds and tests moltest itself; `recipe.toml` (a source recipe,
molto RFC-0009) is what consumers compile. Consumers add it to `[dev-deps]`, so
its headers reach `tests/` only. Keep the two `version` keys equal.

## Invariants
- Zero runtime dependencies beyond the C standard library and the platform API.
- Builds on Linux, macOS and Windows (mingw) with C23 (`-std=c2x`).
- moltest never requires molto at runtime; molto never requires moltest.
- The reporter API is the plugin boundary ([ADR 0002](adr/0002-plugin-model.md)).

## Open question
molto and pickup build their first binary with a Makefile, which cannot run
`molto add`. M2 must decide how that bootstrap gets moltest's sources.
