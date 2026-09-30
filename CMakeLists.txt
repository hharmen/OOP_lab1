cmake_minimum_required(VERSION 3.16)
project(MAI_OOP_Lab1 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# 1. Библиотека чистых функций (в папке src)
add_library(array_ops src/array_ops.cpp src/array_ops.h)

# 2. Основная программа (в папке src)
add_executable(main_app src/main.cpp)
target_link_libraries(main_app PRIVATE array_ops)

# 3. Поиск Google Test, установленного в систему
find_package(GTest REQUIRED)

# Создаем исполняемый файл для тестов
add_executable(run_tests tests/test_variant.cpp)
target_link_libraries(run_tests PRIVATE array_ops GTest::gtest GTest::gtest_main)

# ОДНА НОВАЯ СТРОКА: Указываем путь к папке src, чтобы тесты видели array_ops.h
target_include_directories(run_tests PRIVATE src)

# Включаем тесты
include(CTest)
enable_testing()
add_test(NAME Variant3Tests COMMAND run_tests)
