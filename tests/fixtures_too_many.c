#include "fixture_runner.h"

/* Fixture "too_many": more reporters than a run has room for. */

static const moltest_reporter quiet = {
    .api_version = MOLTEST_REPORTER_API,
    .name = "quiet",
};

__attribute__((constructor)) static void register_too_many(void) {
    if (!fixture_active("too_many"))
        return;
    for (int i = 0; i < MOLTEST_REPORTERS_MAX + 1; i++)
        moltest_add_reporter(&quiet);
}

DESCRIBE(too_many_guards_this_body) {
    if (!fixture_active("too_many"))
        SKIP("fixture");
    printf("[body]\n");
}
