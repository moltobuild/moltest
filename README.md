# moltest

[![CI](https://github.com/moltobuild/moltest/actions/workflows/ci.yml/badge.svg?branch=master)](https://github.com/moltobuild/moltest/actions/workflows/ci.yml)

A small unit-testing framework for C, in the spirit of pytest.

```c
#include <moltest.h>

DESCRIBE(str_list_push_appends) {
    str_list list;
    str_list_init(&list);
    EXPECT_TRUE(str_list_push(&list, "a"));
    EXPECT_EQ(1, str_list_count(&list));
    str_list_free(&list);
}
```

Tests register themselves, so there is no list to keep in sync.

moltest is the official tester of the [Molto](https://github.com/moltobuild/molto)
ecosystem, and an optional one: nothing in molto requires it, and moltest
works in any C/C++ project.

## Installing

With molto, as a development dependency (compiled into your tests only).
Until moltest is on the registry, take it from git:

```sh
molto add git+https://github.com/moltobuild/moltest#v0.3.0 -d   # a release (recommended)
molto add moltest -d --path ../moltest                          # a local checkout
```

`molto add git+<url>` names the package after the repository and writes the
reference into `Project.toml`. Pin a release tag: a branch lets whatever lands
on it next into your build without a diff.

```toml
[dev-deps]
moltest = { git = "https://github.com/moltobuild/moltest", tag = "v0.3.0" }
```

A library created with `molto new` already has this line, pinned to moltest's
newest release when the project is created (molto 0.53.0 or later), and a
first test.

```toml
[test]
mode = "single"   # your tests and moltest link into one executable
```

Without molto: compile `src/moltest.c` and `src/moltest_main.c` into your test
binary with `-I<moltest>/include` (C23, `-std=c2x`); `moltest_main.c` provides
`main()`.

## Assertions

`EXPECT_*` records a failure and lets the test continue; `ASSERT_*` also stops
the test.

| Assertion | Checks |
|---|---|
| `EXPECT_TRUE` / `EXPECT_FALSE` | a condition |
| `EXPECT_EQ` / `EXPECT_NE` (alias `EXPECT_EQUALS`) | integers, or strings when the actual value is a `char *` |
| `EXPECT_STREQ` / `EXPECT_STRNE` | strings, explicitly |
| `EXPECT_PTR_EQ` / `EXPECT_PTR_NE` | pointer identity |
| `EXPECT_NULL` / `EXPECT_NOT_NULL` | pointers |
| `EXPECT_LT` / `LE` / `GT` / `GE` | ordering |

Outcome control: `SKIP("reason")`, `WARN("message")`, `FAIL("message")`, and
`SKIP_TEST(name, "reason")` to skip a test without running it.

`MOLTEST` and `MOLTEST_SKIP`, the names before 0.2.0, still work as deprecated
aliases of `DESCRIBE` and `SKIP_TEST` ([ADR 0003](docs/adr/0003-describe-macro.md)).

## Setup and teardown

Four hooks per test file, each at most once, used like a test body:

```c
static char dir[MOLTEST_PATH];

BEFORE_ALL()  { /* once, before the first test of this file that runs */ }
BEFORE_EACH() { ASSERT_TRUE(moltest_temp_dir("parser", dir, sizeof dir)); }
AFTER_EACH()  { remove_tree(dir); }   /* always, even after a failed ASSERT */
AFTER_ALL()   { /* once, after the last test of this file that runs */ }

DESCRIBE(parser_reads_an_empty_file) { /* uses dir */ }
```

- `AFTER_EACH` runs however the test ended: passed, failed, stopped by
  `ASSERT_*`, or skipped with `SKIP()`.
- Tests skipped with `SKIP_TEST` or filtered out by `-k` run no hooks.
- A failing `BEFORE_EACH` fails its test without running it; a failing
  `BEFORE_ALL` fails every test of the file. The `AFTER_*` hooks still run.
- A failing `AFTER_EACH` fails its test; a failing `AFTER_ALL` fails the last
  test that ran. The report names the hook.
- Share state through `static` variables in the test file.

See [ADR 0004](docs/adr/0004-setup-teardown-hooks.md).

## Output

Results are grouped per file with a progress percentage; `.` passed, `F` failed,
`s` skipped, `W` passed with warnings. Failures print the expectation, the
expected and actual values, the location and anything the test printed (output
is captured and only shown when a test fails). Colour is used when writing to a
terminal, honouring `NO_COLOR`.

## Options

| Option | Meaning |
|---|---|
| `-k <substring>` | only run tests whose file or name matches |
| `-v` | one line per test |
| `-s` | do not capture what the tests print |
| `--list` | list the registered tests |
| `--color=auto\|always\|never` | colour output |

The exit status is 0 when nothing failed, 1 otherwise.

### Running one folder

`-k` matches a substring of the test's name *or* of its file path, and the path
is the one the compiler saw (`__FILE__`). A suite laid out in folders, like
`tests/services/` next to `src/services/`, can therefore run one folder:

```sh
molto test -- -k tests/services/
molto test -p coverage -- -k tests/services/
```

Keep the trailing `/`, or `tests/util` also matches `tests/utility/`.

With [moltest-coverage](https://github.com/moltobuild/moltest-coverage), the
`fail_under` floor in `moltest-coverage.toml` is measured over all of `src/`. A
run limited to one folder will almost always land below it and fail, but the
report still shows what that folder covers.

## Writing a plugin

A plugin is a package that registers a reporter when it is linked: adding it
to `[dev-deps]` is the whole setup for its users. Up to 8 reporters run
together, called in the order they registered.

```c
#include <moltest.h>

static void on_run_end(const moltest_summary *summary, void *ctx) {
    (void)ctx;
    printf("my_plugin: %zu tests\n", summary->tests);
    if (summary->tests == 0)
        moltest_fail_run("my_plugin: nothing was tested");
}

static const moltest_reporter my_plugin = {
    .api_version = MOLTEST_REPORTER_API, /* required: checked when the run starts */
    .name = "my_plugin",
    .on_run_end = on_run_end,
};

__attribute__((constructor)) static void register_my_plugin(void) {
    moltest_add_reporter(&my_plugin);
}
```

| Callback | When |
|---|---|
| `on_run_start(files, tests)` | before the first test |
| `on_file_start(file)` / `on_file_end(file, done, total)` | around each file |
| `on_test_start(file, name)` | before each test's `BEFORE_EACH` (not for `SKIP_TEST`) |
| `on_test_end(file, name, status, seconds)` | after each test, `AFTER_EACH` included |
| `on_run_end(summary)` | after the summary is printed |

`moltest_fail_run(reason)` makes the run exit 1 even when every test passed,
and prints the reason last: for plugins that gate a run, such as a coverage
floor. A reporter built for another `MOLTEST_REPORTER_API` is refused before
any test runs. `moltest_set_reporter()` still works, as `moltest_add_reporter()`.

Community plugins are separate packages named `moltest-<name>`, such as
[moltest-coverage](https://github.com/moltobuild/moltest-coverage); see
[ADR 0002](docs/adr/0002-plugin-model.md).

## Developing moltest

moltest is built with molto: `molto build`, `molto test`. Start at
[`docs/PLAN.md`](docs/PLAN.md).

## License

Apache-2.0; see [LICENSE](LICENSE) and [NOTICE](NOTICE).

## Manifest packages (RFC-0024)

This checkout requires a Molto build with RFC-0024 support. Project.toml is
the only consumer description; run `molto package` before tagging a release.
Older release tags still use recipes and require older Molto consumers.
CI temporarily builds the immutable Molto revision in `MOLTO_SOURCE_REF`.
