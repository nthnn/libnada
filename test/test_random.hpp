#pragma once

#include <doctest.h>
#include <nada/random.hpp>

class Test_random { TEST_CASE_CLASS("Test_random") {

    SUBCASE("100%") {
        std::vector<bool> bools;
        for (unsigned i = 0; i<100; ++i) bools.push_back(nada::random::b(100));
        REQUIRE(std::find(bools.begin(), bools.end(), false) == bools.end());
    }

    SUBCASE("50%") {
        std::vector<bool> bools;
        for (unsigned i = 0; i<100; ++i) bools.push_back(nada::random::b(50));
        REQUIRE(std::find(bools.begin(), bools.end(), false) != bools.end());
        REQUIRE(std::find(bools.begin(), bools.end(), true) != bools.end());
    }

    SUBCASE("0%") {
        std::vector<bool> bools;
        for (unsigned i = 0; i<100; ++i) bools.push_back(nada::random::b(0));
        REQUIRE(std::find(bools.begin(), bools.end(), true) == bools.end());
    }

    SUBCASE("choice") {
        std::vector<int> ints = {1,2,3,4,5,6,7,8,9,10};
        for (unsigned i = 0; i<100; ++i) {
            auto& choice = nada::random::choice(ints);
            REQUIRE_GE(choice,  1);
            REQUIRE_LE(choice, 10);
        }
        for (unsigned i = 0; i<10; ++i) nada::random::choice_erase(ints);
        REQUIRE_EQ(ints.size(), 0);
    }

    SUBCASE("choice w/ string") {
        std::vector<std::string> v = {"first", "second", "third", "forth", "..."};
        std::string s = nada::random::choice(v);
        REQUIRE_GE(s.length(), 3);
    }

}};
