#pragma once

#include <doctest.h>
#include <nada/misc.hpp>
#include <functional>
#include <deque>
#include <list>

class Test_misc { TEST_CASE_CLASS("Test_misc") {

    SUBCASE("do_once") {
        unsigned count = 0;
        for (unsigned i = 0; i < 10; i++) {
            NADA_DO_ONCE { count++; }
        }
        REQUIRE(count == 1);
    }

    SUBCASE("nada_sum") {
        std::vector<unsigned> v = { 1, 1, 1, 1, 1, 1, 1, 1, 1, 1 };
        const auto sum = NADA_SUM(v, std::plus());
        REQUIRE(sum == 10);
    }

    SUBCASE("sort_ptr") {
        std::string s1 = "AAA", s2 = "BBB", s3 = "CCC";
        SUBCASE("vector") {
            std::vector<std::string*> v = { &s2, &s3, &s1 };
            nada::misc::sort_ptrs(v);
            REQUIRE(s1 == *v[0]);
            REQUIRE(s2 == *v[1]);
            REQUIRE(s3 == *v[2]);
        }
        SUBCASE("deque") {
            std::deque<std::string*> v = { &s2, &s3, &s1 };
            nada::misc::sort_ptrs(v);
            REQUIRE(s1 == *v[0]);
            REQUIRE(s2 == *v[1]);
            REQUIRE(s3 == *v[2]);
        }
        SUBCASE("list") {
            std::list<std::string*> v = { &s2, &s3, &s1 };
            nada::misc::sort_ptrs(v);
            auto it = v.begin();
            REQUIRE(s1 == **it); it++;
            REQUIRE(s2 == **it); it++;
            REQUIRE(s3 == **it);
        }
    }

    SUBCASE("get_color_from_ratio") { // currently not endian-portable
        WARN_EQ(0xFF40FF00, nada::misc::get_color_from_ratio(1.0f));
        WARN_EQ(0xFF407F80, nada::misc::get_color_from_ratio(0.5f));
        WARN_EQ(0xFF4000FF, nada::misc::get_color_from_ratio(0.0f));
    }

}};
