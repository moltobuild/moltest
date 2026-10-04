#include <moltest.h>

/* moltest's own suite, run by moltest. A failing check here fails the run, so
   these cover the passing paths; the reporting of failures is covered by
   running a suite in a child process (see docs/ROADMAP.md, M1). */

DESCRIBE(int_equality_passes) {
    EXPECT_EQ(3, 1 + 2);
    EXPECT_NE(3, 4);
}

DESCRIBE(string_equality_compares_contents) {
    char built[] = {'a', 'b', '\0'};
    EXPECT_STREQ("ab", built);
    EXPECT_STRNE("ba", built);
}

DESCRIBE(pointer_checks) {
    int value = 0;
    int *pointer = &value;
    EXPECT_NOT_NULL(pointer);
    EXPECT_PTR_EQ(&value, pointer);
    EXPECT_NULL(NULL);
}

DESCRIBE(ordering_checks) {
    EXPECT_LT(1, 2);
    EXPECT_LE(2, 2);
    EXPECT_GT(3, 2);
    EXPECT_GE(3, 3);
}

DESCRIBE(temp_dir_is_created) {
    char path[MOLTEST_PATH];
    ASSERT_TRUE(moltest_temp_dir("moltest_self", path, sizeof path));
    EXPECT_NE('\0', path[0]);
}

DESCRIBE(skip_marks_the_test_skipped) {
    SKIP("exercises the skip path");
}

SKIP_TEST(skip_test_does_not_run_the_body, "exercises SKIP_TEST") {
    FAIL("a skipped test must not run");
}
