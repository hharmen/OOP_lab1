cmake_minimum_required(VERSION 3.16)
project(MAI_OOP_Lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_library(array_ops src/array_ops.cpp src/array_ops.h)

add_executable(main_app src/main.cpp)
target_link_libraries(main_app PRIVATE array_ops)

find_package(GTest REQUIRED)

add_executable(run_tests tests/test_variant.cpp)
target_link_libraries(run_tests PRIVATE array_ops GTest::gtest GTest::gtest_main)

target_include_directories(run_tests PRIVATE src)

include(CTest)
enable_testing()
add_test(NAME Variant3Tests COMMAND run_tests)
