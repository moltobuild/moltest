#include "fixture_runner.h"

/* Fixture "before_each": the setup fails, so the body must not run, and the
   teardown must run anyway. */

#define ACTIVE fixture_active("before_each")

BEFORE_EACH() {
    if (ACTIVE)
        FAIL("setup broke");
}

AFTER_EACH() {
    if (ACTIVE)
        printf("[after_each]\n");
}

DESCRIBE(before_each_guards_this_body) {
    if (!ACTIVE)
        SKIP("fixture");
    printf("[body]\n");
}
