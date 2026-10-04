#include "fixture_runner.h"

/* What the runner does, seen from outside: each test runs one fixture file in
   a child process and reads its output and exit status (spec 003, spec 001). */

#define OUTPUT_SIZE (16 * 1024)

static char output[OUTPUT_SIZE];

DESCRIBE(after_each_runs_however_the_test_ends) {
    const int status = fixture_run("order", NULL, output, sizeof output);
    ASSERT_EQ(1, status); /* order_fails and order_stops_at_an_assert failed */

    EXPECT_EQ(1, fixture_count(output, "[before_all]"));
    EXPECT_EQ(1, fixture_count(output, "[after_all]"));
    /* Four tests run: passed, failed, stopped by ASSERT, skipped from inside. */
    EXPECT_EQ(4, fixture_count(output, "[body]"));
    EXPECT_EQ(4, fixture_count(output, "[before_each]"));
    EXPECT_EQ(4, fixture_count(output, "[after_each]"));
    EXPECT_EQ(0, fixture_count(output, "[after_the_assert]"));
}

DESCRIBE(filtered_tests_run_no_hooks) {
    /* The registered skip never runs, hooks included. */
    int status = fixture_run("order", NULL, output, sizeof output);
    ASSERT_EQ(1, status);
    EXPECT_EQ(0, fixture_count(output, "[registered_skip_body]"));

    /* One test selected by -k: one BEFORE_EACH, and the file hooks once. */
    status = fixture_run("order", "order_passes", output, sizeof output);
    ASSERT_EQ(0, status);
    EXPECT_EQ(1, fixture_count(output, "[before_each]"));
    EXPECT_EQ(1, fixture_count(output, "[after_each]"));
    EXPECT_EQ(1, fixture_count(output, "[before_all]"));

    /* Nothing selected from the file: none of its hooks. */
    status = fixture_run("order", "no_test_is_called_this", output, sizeof output);
    ASSERT_EQ(0, status);
    EXPECT_EQ(0, fixture_count(output, "[before_all]"));
    EXPECT_EQ(0, fixture_count(output, "[before_each]"));
}

DESCRIBE(failing_before_each_fails_the_test) {
    const int status = fixture_run("before_each", NULL, output, sizeof output);
    ASSERT_EQ(1, status);
    EXPECT_EQ(0, fixture_count(output, "[body]"));
    EXPECT_EQ(1, fixture_count(output, "[after_each]"));
    EXPECT_EQ(1, fixture_count(output, "FAILED"));
    EXPECT_EQ(1, fixture_count(output, "in BEFORE_EACH"));
}

DESCRIBE(failing_before_all_fails_the_file) {
    const int status = fixture_run("before_all", NULL, output, sizeof output);
    ASSERT_EQ(1, status);
    EXPECT_EQ(0, fixture_count(output, "[body]"));
    EXPECT_EQ(0, fixture_count(output, "[before_each]"));
    EXPECT_EQ(1, fixture_count(output, "[after_all]"));
    EXPECT_EQ(2, fixture_count(output, "FAILED"));
    EXPECT_EQ(1, fixture_count(output, "in BEFORE_ALL"));
    EXPECT_EQ(1, fixture_count(output, "not run: BEFORE_ALL failed"));
}

DESCRIBE(failing_after_hooks_fail_a_test) {
    const int status = fixture_run("after", NULL, output, sizeof output);
    ASSERT_EQ(1, status);
    EXPECT_EQ(1, fixture_count(output, "FAILED"));
    EXPECT_EQ(1, fixture_count(output, "in AFTER_EACH"));
    EXPECT_EQ(1, fixture_count(output, "in AFTER_ALL"));
    EXPECT_EQ(1, fixture_count(output, "file teardown broke"));
}

DESCRIBE(failing_check_exits_one_and_reports_its_values) {
    const int status = fixture_run("failing_check", NULL, output, sizeof output);
    ASSERT_EQ(1, status);
    EXPECT_EQ(1, fixture_count(output, "Expected: 1"));
    EXPECT_EQ(1, fixture_count(output, "Actual: 2"));
    /* The location names the line of the check, not just the file. */
    EXPECT_EQ(1, fixture_count(output, "fixtures_failing_check.c:9\n"));
}
