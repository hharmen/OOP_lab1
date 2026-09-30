#include <gtest/gtest.h>
#include <cstddef>
#include "array_ops.h"


TEST(ArrayBaseTests, CreateArray) {
    std::size_t size = 5;
    int* arr = array_create(size);
    ASSERT_NE(arr, nullptr); 
    
    for (std::size_t i = 0; i < size; ++i) {
        EXPECT_EQ(arr[i], 0);
    }
    
    array_delete(arr);
    EXPECT_EQ(arr, nullptr); }

TEST(ArrayBaseTests, ResizeArray) {
    std::size_t size = 3;
    int* arr = array_create(size);
    arr[0] = 10; arr[1] = 20; arr[2] = 30;

    std::size_t new_size = 5;
    arr = array_resize(arr, size, new_size);
    
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);
    EXPECT_EQ(arr[3], 0);
    
    array_delete(arr);
}

TEST(ArrayBaseTests, RemoveElement) {
    std::size_t size = 4;
    int* arr = array_create(size);
    arr[0] = 1; arr[1] = 2; arr[2] = 3; arr[3] = 4;

    arr = array_remove(arr, size, 1);
    
    ASSERT_EQ(size, 3);
    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 3);
    EXPECT_EQ(arr[2], 4);

    array_delete(arr);
}

TEST(ArrayInsertTests, InsertInside) {
    std::size_t size = 2;
    int* arr = array_create(size);
    arr[0] = 10; arr[1] = 30;

    arr = array_insert(arr, size, 1, 20);
    ASSERT_EQ(size, 3);
    EXPECT_EQ(arr[0], 10);
    EXPECT_EQ(arr[1], 20);
    EXPECT_EQ(arr[2], 30);

    arr = array_insert(arr, size, 0, 5);
    ASSERT_EQ(size, 4);
    EXPECT_EQ(arr[0], 5);
    EXPECT_EQ(arr[1], 10);

    array_delete(arr);
}

TEST(ArrayInsertTests, InsertBeyondBounds) {
    std::size_t size = 2;
    int* arr = array_create(size);
    arr[0] = 5; arr[1] = 6;

    arr = array_insert(arr, size, 4, 9);
    ASSERT_EQ(size, 5);
    EXPECT_EQ(arr[0], 5);
    EXPECT_EQ(arr[1], 6);
    EXPECT_EQ(arr[2], 0);
    EXPECT_EQ(arr[3], 0);
    EXPECT_EQ(arr[4], 9);

    array_delete(arr);
}

TEST(ArraySortTests, InsertionSort) {
    std::size_t size = 5;
    int* arr = array_create(size);
    arr[0] = 5; arr[1] = 2; arr[2] = 4; arr[3] = 1; arr[4] = 3;

    insert_sort(arr, size);

    EXPECT_EQ(arr[0], 1);
    EXPECT_EQ(arr[1], 2);
    EXPECT_EQ(arr[2], 3);
    EXPECT_EQ(arr[3], 4);
    EXPECT_EQ(arr[4], 5);

    array_delete(arr);
}

TEST(ArraySortTests, BinarySearch) {
    std::size_t size = 4;
    int* arr = array_create(size);
    arr[0] = 10; arr[1] = 20; arr[2] = 30; arr[3] = 40;

    std::size_t found_index = 0;
    
    bool found = array_binary_search(arr, size, 30, found_index);
    EXPECT_TRUE(found);
    EXPECT_EQ(found_index, 2);

    bool found_missing = array_binary_search(arr, size, 25, found_index);
    EXPECT_FALSE(found_missing);

    array_delete(arr);
}

TEST(ArrayRotateTests, RotateLeftNormal) {
    std::size_t size = 5;
    int* arr = array_create(size);
    arr[0] = 1; arr[1] = 2; arr[2] = 3; arr[3] = 4; arr[4] = 5;

    array_rotate_left(arr, size, 2);

    EXPECT_EQ(arr[0], 3);
    EXPECT_EQ(arr[1], 4);
    EXPECT_EQ(arr[2], 5);
    EXPECT_EQ(arr[3], 1);
    EXPECT_EQ(arr[4], 2);

    array_delete(arr);
}

TEST(ArrayRotateTests, RotateLeftLargeK) {
    std::size_t size = 3;
    int* arr = array_create(size);
    arr[0] = 7; arr[1] = 8; arr[2] = 9;

    array_rotate_left(arr, size, 3);
    EXPECT_EQ(arr[0], 7);
    EXPECT_EQ(arr[1], 8);
    EXPECT_EQ(arr[2], 9);

    array_rotate_left(arr, size, 4);
    EXPECT_EQ(arr[0], 8);
    EXPECT_EQ(arr[1], 9);
    EXPECT_EQ(arr[2], 7);

    array_delete(arr);
}

TEST(ArrayRotateTests, EmptyArrayResilience) {
    std::size_t size = 0;
    int* arr = nullptr;

    EXPECT_NO_THROW(insert_sort(arr, size));
    
    std::size_t index = 0;
    EXPECT_FALSE(array_binary_search(arr, size, 10, index));
    
    EXPECT_NO_THROW(array_rotate_left(arr, size, 5));
}
