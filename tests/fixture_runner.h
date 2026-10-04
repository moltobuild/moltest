#ifndef MOLTEST_FIXTURE_RUNNER_H
#define MOLTEST_FIXTURE_RUNNER_H

/*
 * Run this test binary again, in a child process, on one fixture file.
 *
 * Some behaviour can only be seen from outside the run: a failing hook, the
 * exit status, what the failure report prints. The fixture files hold suites
 * built to show it; they are part of this binary, so the parent runs itself
 * with `-k fixtures_<scenario>` and `MOLTEST_FIXTURE=<scenario>`, which is
 * what wakes them. In a normal run the variable is unset and every fixture
 * test skips itself.
 */

#include <moltest.h>

#include <stdio.h>
#include <string.h>

#ifndef _WIN32
#include <sys/wait.h>
#endif

#define FIXTURE_ENV "MOLTEST_FIXTURE"

/* Whether the fixture `scenario` is the one this run was started for. */
static inline bool fixture_active(const char *scenario) {
    const char *wanted = getenv(FIXTURE_ENV);
    return wanted != NULL && strcmp(wanted, scenario) == 0;
}

/* Run the fixture `scenario`, selecting tests with `filter` (the scenario's
   file when NULL). Its stdout and stderr land in `out`; the return value is
   its exit status, or -1 when it could not be started. */
static inline int fixture_run(const char *scenario, const char *filter, char *out, size_t size) {
    out[0] = '\0';
    const char *self = moltest_self_path();
    if (self == NULL || setenv(FIXTURE_ENV, scenario, 1) != 0)
        return -1;

    char selected[128];
    if (filter == NULL)
        snprintf(selected, sizeof selected, "fixtures_%s", scenario);
    else
        snprintf(selected, sizeof selected, "%s", filter);

    char command[1024];
#ifdef _WIN32
    /* cmd strips the outer pair of quotes, so the quoted program needs one more. */
    const int written = snprintf(command, sizeof command, "\"\"%s\" -k %s -v -s --color=never 2>&1\"",
                                 self, selected);
#else
    const int written = snprintf(command, sizeof command, "'%s' -k %s -v -s --color=never 2>&1",
                                 self, selected);
#endif
    if (written < 0 || (size_t)written >= sizeof command)
        return -1;

#ifdef _WIN32
    FILE *child = _popen(command, "r");
#else
    FILE *child = popen(command, "r");
#endif
    if (child == NULL)
        return -1;
    const size_t read = fread(out, 1, size - 1, child);
    out[read] = '\0';
#ifdef _WIN32
    return _pclose(child);
#else
    const int status = pclose(child);
    return WIFEXITED(status) ? WEXITSTATUS(status) : -1;
#endif
}

/* How many times `needle` occurs in `text`. */
static inline int fixture_count(const char *text, const char *needle) {
    int count = 0;
    for (const char *at = strstr(text, needle); at != NULL; at = strstr(at + 1, needle))
        count++;
    return count;
}

#endif /* MOLTEST_FIXTURE_RUNNER_H */
