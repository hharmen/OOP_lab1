#include <iostream>
#include <cmath>
#include<algorithm>
#include <numeric>
#include "array_ops.h"

int* array_create(std::size_t size){
    if (size == 0){
        return nullptr;
    }
    int* arr = new int[size]();
    return arr;
}

void array_delete(int*& arr){
    delete[] arr;
    arr = nullptr;
}

int* array_resize(int* arr, std::size_t size, std::size_t new_size){
    int* new_arr = array_create(new_size);

    size_t mini = (size < new_size) ? size : new_size;
    for (size_t i = 0; i<mini; ++i){
        new_arr[i] = arr[i];
    }
    
    array_delete(arr);
    return new_arr;
}

int* array_insert(int* arr, std::size_t& size, std::size_t pos, int value){
    if (pos >= size){
        arr = array_resize(arr, size, pos+1);
        size = pos + 1;
        arr[pos] = value;
    }else{
        arr = array_resize(arr, size, size+1);
        size++;
        for (size_t i=size-1; i>pos; --i){
            arr[i] = arr[i-1];
        }
        arr[pos] = value;
    }
    return arr;
}

int* array_remove(int* arr, std::size_t& size, std::size_t pos){
    if (pos >= size){
        return arr;
    }
    int* new_arr = array_create(size-1);
    for (size_t i = 0; i < size; ++i){
        if (i < pos){
            new_arr[i] = arr[i];
        }else if (i > pos){
            new_arr[i-1] = arr[i];
        }
    }
    --size;
    array_delete(arr);
    return new_arr;
}

void array_print(const int* arr, std::size_t size){
    if (size == 0) {
        std::cout << std::endl;
        return;
    }

    std::cout << arr[0] << " ";

    for (size_t i = 1; i < size; ++i){
        std::cout << arr[i] << " ";
    }

    std::cout << std::endl;

}

bool array_binary_search(const int* arr, std::size_t size, int target, std::size_t&out_index){
    if (size == 0) return false;

    size_t l = 0, r = size-1;

    while (l <= r){
        size_t m = l + (r-l)/2;
        if (arr[m] == target){
            out_index = m;
            return true;
        }else if (arr[m] > target){
            if (m == 0){
                return false;
            }
            r = m-1;
        }else{
            l = m+1;
        }
    }
    return false;
}

void insert_sort(int* arr, size_t size){
    if (size <= 1) return;
    for (size_t i = 1; i < size; ++i){
        size_t index = i;
        while (index > 0 && arr[index] < arr[index-1]){
            std::swap(arr[index], arr[index-1]);
            index--;
        }
    }
}

void array_reverse_part(int* arr, size_t l, size_t r) {
    while (l < r) {
        std::swap(arr[l], arr[r]);
        l++;
        r--;
    }
}

void array_rotate_left(int* arr, size_t size, size_t k) {
    if (size <= 1) return;
    k = k % size;
    if (k == 0) return;

    array_reverse_part(arr, 0, k - 1);
    array_reverse_part(arr, k, size - 1);
    array_reverse_part(arr, 0, size - 1);
}








