#pragma

#include <doctest.h>

#include <nada/fs.hpp>

class Test_fs { TEST_CASE_CLASS("Test_fs") {

    SUBCASE("filesystem") {
        SUBCASE("txt") {
            const auto& all_files = nada::fs::all_files("test", "txt");
            REQUIRE_EQ(all_files.size(), 2);
        }
        SUBCASE("all files") {
            const auto& all_files = nada::fs::all_files("test");
            REQUIRE_EQ(all_files.size(), 5);
        }
        SUBCASE("cfg") {
            const auto& all_files = nada::fs::all_files("test", "cfg");
            REQUIRE_EQ(all_files.size(), 1);
            REQUIRE_EQ(all_files.at(0), "test/test_file_4.cfg");
        }
        SUBCASE("exe") {
            const auto& all_files = nada::fs::all_files("test", "exe");
            REQUIRE_EQ(all_files.size(), 0);
        }
        SUBCASE("subsubfolder") {
            auto all_files = nada::fs::all_files_recursive("test", "xml"); 
            REQUIRE_EQ(all_files.size(), 2);
            std::sort(all_files.begin(), all_files.end());
            REQUIRE_EQ(all_files.at(0), "test/subfolder/test_file_6.xml");
            REQUIRE_EQ(all_files.at(1), "test/test_file_5.xml");
        }
    }

    SUBCASE("exists") {
        REQUIRE(nada::fs::exists_file("test/test_file_4.cfg"));
        REQUIRE_FALSE(nada::fs::exists_file("test/xxxxx.yyy"));
        REQUIRE_FALSE(nada::fs::exists_file("test")); // is folder, not file
    }

}};
