#include "fixture_runner.h"

/* Fixture "fail_run": every test passes and a plugin fails the run anyway,
   the way a coverage floor does. */

static void gate(const moltest_summary *summary, void *ctx) {
    (void)summary, (void)ctx;
    moltest_fail_run("coverage 50.0% is under fail_under = 80.0");
}

static const moltest_reporter gatekeeper = {
    .api_version = MOLTEST_REPORTER_API,
    .name = "gatekeeper",
    .on_run_end = gate,
};

__attribute__((constructor)) static void register_gatekeeper(void) {
    if (fixture_active("fail_run"))
        moltest_add_reporter(&gatekeeper);
}

DESCRIBE(fail_run_passes_on_its_own) {
    if (!fixture_active("fail_run"))
        SKIP("fixture");
    EXPECT_TRUE(true);
}
