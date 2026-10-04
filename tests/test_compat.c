#include <moltest.h>

/* The names before 0.2.0 still define tests (ADR 0003). If either alias broke,
   this file would stop compiling or its test would stop running. */

MOLTEST(the_old_name_still_defines_a_test) {
    EXPECT_TRUE(true);
}

MOLTEST_SKIP(the_old_skip_still_skips, "exercises the deprecated alias") {
    FAIL("a skipped test must not run");
}
