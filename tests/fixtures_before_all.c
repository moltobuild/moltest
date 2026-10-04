#include "fixture_runner.h"

/* Fixture "before_all": the file's setup fails, so no test of it runs, and
   its teardown runs anyway. */

#define ACTIVE fixture_active("before_all")

BEFORE_ALL() {
    if (ACTIVE)
        FAIL("file setup broke");
}

AFTER_ALL() {
    if (ACTIVE)
        printf("[after_all]\n");
}

BEFORE_EACH() {
    if (ACTIVE)
        printf("[before_each]\n");
}

DESCRIBE(before_all_guards_this_body) {
    if (!ACTIVE)
        SKIP("fixture");
    printf("[body]\n");
}

DESCRIBE(before_all_guards_this_body_too) {
    if (!ACTIVE)
        SKIP("fixture");
    printf("[body]\n");
}
