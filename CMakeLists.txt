cmake_minimum_required(VERSION 3.8)
project(nada)
set(CMAKE_CXX_STANDARD 17)

set(LIBNADA_INCLUDE_DIRS ${CMAKE_CURRENT_LIST_DIR}/include)
set(LIBNADA_INCLUDE_DIRS ${LIBNADA_INCLUDE_DIRS} PARENT_SCOPE)
file(GLOB_RECURSE CPP_FILES src/*.cpp)

# libnada
add_library(nada STATIC ${CPP_FILES})
target_include_directories(nada PRIVATE ${LIBNADA_INCLUDE_DIRS})

# libnada - tests
add_executable(nada_test test/tests.cpp)
#target_compile_definitions(nada_test PRIVATE UNITTEST=1)
target_include_directories(nada_test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/include)
target_include_directories(nada_test PRIVATE ${CMAKE_CURRENT_LIST_DIR}/test/doctest)
target_link_libraries(nada_test PRIVATE nada pthread tbb gcov)
target_compile_options(nada_test PRIVATE -coverage)
