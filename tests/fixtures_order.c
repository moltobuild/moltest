#include "fixture_runner.h"

/* Fixture "order": hooks and bodies print markers, so the parent can count
   what ran. Every way a test can end is here once. */

#define ACTIVE fixture_active("order")

BEFORE_ALL() {
    if (ACTIVE)
        printf("[before_all]\n");
}

AFTER_ALL() {
    if (ACTIVE)
        printf("[after_all]\n");
}

BEFORE_EACH() {
    if (ACTIVE)
        printf("[before_each]\n");
}

AFTER_EACH() {
    if (ACTIVE)
        printf("[after_each]\n");
}

DESCRIBE(order_passes) {
    if (!ACTIVE)
        SKIP("fixture");
    printf("[body]\n");
}

DESCRIBE(order_fails) {
    if (!ACTIVE)
        SKIP("fixture");
    printf("[body]\n");
    EXPECT_TRUE(false);
}

DESCRIBE(order_stops_at_an_assert) {
    if (!ACTIVE)
        SKIP("fixture");
    printf("[body]\n");
    ASSERT_TRUE(false);
    printf("[after_the_assert]\n");
}

DESCRIBE(order_skips_from_inside) {
    if (!ACTIVE)
        SKIP("fixture");
    printf("[body]\n");
    SKIP("from inside");
}

SKIP_TEST(order_registered_skip, "never runs") {
    printf("[registered_skip_body]\n");
}
