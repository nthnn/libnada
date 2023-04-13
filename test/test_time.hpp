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

    SUBCASE("fps clock") {
        // 120 frames @ 60fps should take 2s
        nada::time::Clock c;
        for (unsigned i = 0; i < 120; ++i) nada::time::fps(60);
        REQUIRE_EQ(std::round(c.s()), doctest::Approx(2.0f)); 
        
        // clock should be @ almost 0ms after reset
        c.reset();
        REQUIRE_LT(c.ms(), 50); 
    }

}};
