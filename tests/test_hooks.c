#include <moltest.h>

/* The hooks of this file, seen from the tests they wrap (spec 003 AC1, AC3).
   Registration order within a file is not promised, so each test checks
   relations between the counters rather than absolute positions. */

static int before_all_runs;
static int after_all_runs;
static int before_each_runs;
static int after_each_runs;
static int bodies;

BEFORE_ALL() {
    before_all_runs++;
}

AFTER_ALL() {
    after_all_runs++;
}

BEFORE_EACH() {
    before_each_runs++;
}

AFTER_EACH() {
    after_each_runs++;
}

/* Every body sees its own BEFORE_EACH and the AFTER_EACH of each earlier test. */
static void check_wrapping(void) {
    bodies++;
    EXPECT_EQ(bodies, before_each_runs);
    EXPECT_EQ(bodies - 1, after_each_runs);
}

DESCRIBE(before_each_runs_once_per_test) {
    check_wrapping();
}

DESCRIBE(all_hooks_run_once_per_file) {
    check_wrapping();
    EXPECT_EQ(1, before_all_runs);
    EXPECT_EQ(0, after_all_runs);
}

DESCRIBE(each_hooks_wrap_every_test) {
    check_wrapping();
}

SKIP_TEST(a_registered_skip_runs_no_hooks, "checked by the counters of the others") {
}
