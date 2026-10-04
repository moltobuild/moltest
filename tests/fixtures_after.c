#include "fixture_runner.h"

/* Fixture "after": every test passes, and the teardowns fail. */

#define ACTIVE fixture_active("after")

AFTER_EACH() {
    if (ACTIVE)
        FAIL("teardown broke");
}

AFTER_ALL() {
    if (ACTIVE)
        FAIL("file teardown broke");
}

DESCRIBE(after_hooks_fail_this_passing_test) {
    if (!ACTIVE)
        SKIP("fixture");
    EXPECT_TRUE(true);
}
