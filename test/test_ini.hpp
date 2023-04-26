#pragma once

#include <doctest.h>
#include <nada/ini.hpp>

class Test_ini { TEST_CASE_CLASS("Test_ini") {

    SUBCASE("file good") {
        nada::Ini ini("test.ini");
        REQUIRE(ini.good() == true);
    }

    SUBCASE("file bad") {
        nada::Ini ini("non_existing_file.ini");
        REQUIRE(ini.good() == false);
    }

    SUBCASE("value_str") {
        nada::Ini ini("test.ini");
        REQUIRE(ini.get("value_str") == "test");
    }

    SUBCASE("value_float") {
        nada::Ini ini("test.ini");
        REQUIRE(ini.get_float<double>("value_float") == doctest::Approx(-1.0));
    }

    SUBCASE("value_int") {
        nada::Ini ini("test.ini");
        REQUIRE(ini.get_int<int>("value_int") == -1);
    }

    SUBCASE("value_vector") {
        nada::Ini ini("test.ini");
        const std::vector<std::string> v = ini.get_vector("value_vector");
        REQUIRE(v.size() == 4);
        REQUIRE(v.at(0) == "ich");
        REQUIRE(v.at(1) == "bin");
        REQUIRE(v.at(2) == "ein");
        REQUIRE(v.at(3) == "berliner");
    }

    SUBCASE("value_bool") {
        nada::Ini ini("test.ini");
        REQUIRE(ini.get_bool("value_bool_true") == true);
        REQUIRE(ini.get_bool("value_bool_false") == false);
        REQUIRE(ini.get_bool("value_bool_not_found") == false);
    }

}};
