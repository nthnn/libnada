#define DOCTEST_CONFIG_IMPLEMENT
//#define DOCTEST_CONFIG_SUPER_FAST_ASSERTS
#include <doctest.h>

#include "test_ini.hpp"
#include "test_log.hpp"
#include "test_misc.hpp"
#include "test_time.hpp"
#include "test_random.hpp"
#include "test_str.hpp"
#include "test_fs.hpp"

int main(int argc, char** argv) {
    doctest::Context context;
    context.setOption("order-by", "name");
    context.applyCommandLine(argc, argv);
    const auto res = context.run();
    context.shouldExit();
    return res;
}
