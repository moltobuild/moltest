#include <moltest.h>

#include <string.h>

/* Several reporters at once, in registration order, and on_test_start before
   the test's BEFORE_EACH (spec 004 AC1, AC2, AC4). Each callback appends a
   letter; the test reads the sequence that led up to it. */

static char seen[16];

static void append(const char *letter) {
    if (strlen(seen) + strlen(letter) < sizeof seen)
        strcat(seen, letter);
}

static void first_starts(const char *file, const char *name, void *ctx) {
    (void)file, (void)name, (void)ctx;
    seen[0] = '\0'; /* every test starts its own sequence */
    append("A");
}

static void second_starts(const char *file, const char *name, void *ctx) {
    (void)file, (void)name, (void)ctx;
    append("B");
}

static void legacy_starts(const char *file, const char *name, void *ctx) {
    (void)file, (void)name, (void)ctx;
    append("C");
}

static const moltest_reporter first = {
    .api_version = MOLTEST_REPORTER_API,
    .name = "first",
    .on_test_start = first_starts,
};
static const moltest_reporter second = {
    .api_version = MOLTEST_REPORTER_API,
    .name = "second",
    .on_test_start = second_starts,
};
static const moltest_reporter legacy = {
    .api_version = MOLTEST_REPORTER_API,
    .name = "legacy",
    .on_test_start = legacy_starts,
};

/* One constructor, so the order is this file's to state. */
__attribute__((constructor)) static void register_reporters(void) {
    moltest_add_reporter(&first);
    moltest_add_reporter(&second);
    moltest_set_reporter(&legacy);
}

BEFORE_EACH() {
    append("E");
}

DESCRIBE(reporters_are_called_in_order) {
    EXPECT_STREQ("ABCE", seen);
}

DESCRIBE(set_reporter_still_registers) {
    EXPECT_NOT_NULL(strchr(seen, 'C'));
}

DESCRIBE(test_start_precedes_before_each) {
    EXPECT_EQ('E', seen[strlen(seen) - 1]);
}
