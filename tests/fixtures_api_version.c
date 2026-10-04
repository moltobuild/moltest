#include "fixture_runner.h"

/* Fixture "api_version": a plugin built for another reporter layout. */

static const moltest_reporter old_plugin = {
    .api_version = 0,
    .name = "old_plugin",
};

__attribute__((constructor)) static void register_old_plugin(void) {
    if (fixture_active("api_version"))
        moltest_add_reporter(&old_plugin);
}

DESCRIBE(api_version_guards_this_body) {
    if (!fixture_active("api_version"))
        SKIP("fixture");
    printf("[body]\n");
}
