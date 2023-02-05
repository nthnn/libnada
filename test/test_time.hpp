#pragma once

#include <doctest.h>
#include <nada/time.hpp>

class Test_time { TEST_CASE_CLASS("Test_time") {

    SUBCASE("millis + sleep") {
        const auto m1 = nada::time::millis();
        nada::time::sleep(1000);
        const auto m2 = nada::time::millis();
        REQUIRE(m1 < m2);
        const auto diff = m2 - m1;
        REQUIRE(diff < 1100); // 10% tolerance
    }

}};
