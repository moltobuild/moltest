#include "fixture_runner.h"

/* Fixture "failing_check": one failed expectation, for the report and the
   exit status (spec 001 AC3). */

DESCRIBE(failing_check_reports_its_values) {
    if (!fixture_active("failing_check"))
        SKIP("fixture");
    EXPECT_EQ(1, 2);
}
