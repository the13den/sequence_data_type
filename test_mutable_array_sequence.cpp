#include "mutable_array_sequence.h"
#include <cassert>
#include <iostream>
#include <string>

template<typename T>
void test_mutable_array_sequence_blank_constructor() {
    MutableArraySequence<T> array1;
    assert(array1.GetSize() == 0);
}

template<typename T>
void test_mutable_array_sequence_constructor_with_elements(T *items, int size) {
    MutableArraySequence<T> array2(size, items);
    assert(array2.GetSize() == size);
    for (int i = 0; i < size; i++) {
        assert(array2.Get(i) == items[i]);
    }
}

template<typename T>
void test_mutable_array_sequence_constructor_with_elements_negative_length(T *items) {
    try {
        MutableArraySequence<T> array(-5, items);
        assert(false);  // Should not reach here
    } catch (const std::invalid_argument &) {
        assert(true);  // Exception expected
    }
}

template<typename T>
void  test_mutable_array_sequence_constructor_with_elements_empty_items() {
    T items[] = {};
    MutableArraySequence<T> array2(0, items);
    assert(array2.GetSize() == 0);
    try {
        array2.Get(0);
        assert(false);  // Should not reach here
    } catch (std::out_of_range &) {
        assert(true);  // Exception expected
    }
}

template<typename T>
void test_mutable_array_sequence_copy_constructor(T *items, int size) {
    MutableArraySequence<T> array2(size, items);
    MutableArraySequence<T> array3(array2);
    assert(array3.GetSize() == size);
    for (int i = 0; i < size; i++) {
        assert(array3.Get(i) == items[i]);
    }
}

template<typename T>
void test_mutable_array_sequence_copy_constructor_empty_source_array() {
    MutableArraySequence<T> array2;
    MutableArraySequence<T> array3(array2);
    assert(array3.GetSize() == 0);
    try {
        array2.Get(0);
        assert(false);  // Should not reach here
    } catch (std::out_of_range &) {
        assert(true);  // Exception expected
    }
}

template<typename T>
void test_mutable_array_sequence_get_first_method(T *items, int size) {
    MutableArraySequence<T> array(size, items);
    assert(array.GetFirst() == items[0]);
}

template<typename T>
void test_mutable_array_sequence_get_first_method_empty_array() {
    MutableArraySequence<T> array;
    try {
        array.GetFirst();
        assert(false);  // Should not reach here
    } catch (std::out_of_range &) {
        assert(true);  // Exception expected
    }
}

template<typename T>
void test_mutable_array_sequence_get_last_method(T *items, int size) {
    MutableArraySequence<T> array(size, items);
    assert(array.GetLast() == items[size - 1]);
}

template<typename T>
void test_mutable_array_sequence_get_last_method_empty_array() {
    MutableArraySequence<T> array;
    try {
        array.GetLast();
        assert(false);  // Should not reach here
    } catch (std::out_of_range &) {
        assert(true);  // Exception expected
    }
}

template<typename T>
void test_mutable_array_sequence_get_length_method(T *items, int size) {
    MutableArraySequence<T> array(size, items);
    assert(array.GetSize() == size);
}

template<typename T>
void test_mutable_array_sequence_append_method() {
    MutableArraySequence<T> array;
    T value = T();
    array.Append(value);
    assert(array.GetLast() == value);
    assert(array.GetSize() == 1);
}

template<typename T>
void test_mutable_array_sequence_prepend_method() {
    MutableArraySequence<T> array;
    T value = T();
    array.Prepend(value);
    assert(array.GetFirst() == value);
    assert(array.GetSize() == 1);
}

template<typename T>
void test_mutable_array_sequence_get_method(T *items, int size) {
    MutableArraySequence<T> array(size, items);
    for (int i = 0; i < size; i++) {
        assert(array.Get(i) == items[i]);
    }
    try {
        array.Get(size + 1);
        assert(false);  // Should not reach here
    } catch (std::out_of_range &) {
        assert(true);  // Exception expected
    }
}

template<typename T>
void test_mutable_array_sequence_get_subsequence_method(T *items, int size) {
    MutableArraySequence<T> array(size, items);
    int start_index = 1;
    int end_index = 3;

    array.GetSubsequence(start_index, end_index);

    // Check the size of the subsequence
    assert(array.GetSize() == (end_index - start_index + 1));

    // Check the elements of the subsequence
    for (int i = 0; i <= end_index - start_index; i++) {
        assert(array.Get(i) == items[start_index + i]);
    }
}

template<typename T>
void test_mutable_array_sequence_get_subsequence_method_start_out_of_range(T *items, int size) {
    MutableArraySequence<T> array(size, items);
    try {
        array.GetSubsequence(-1, size - 1);
        assert(false);  // Should not reach here
    } catch (const std::out_of_range &) {
        assert(true);  // Exception expected
    }
}

template<typename T>
void test_mutable_array_sequence_get_subsequence_method_end_out_of_range(T *items, int size) {
    MutableArraySequence<T> array(size, items);
    try {
        array.GetSubsequence(0, size + 1);
        assert(false);  // Should not reach here
    } catch (const std::out_of_range &) {
        assert(true);  // Exception expected
    }
}

template<typename T>
void test_mutable_array_sequence_insert_at_method() {
    MutableArraySequence<T> array;
    T value1 = T();
    T value2 = T();

    array.Append(value1);
    array.InsertAt(1, value2);

    assert(array.Get(0) == value1);
    assert(array.Get(1) == value2);
}

template<typename T>
void test_mutable_array_sequence_insert_at_method_too_large_index() {
    MutableArraySequence<T> array;
    T value = T();
    try {
        array.InsertAt(1, value);
        assert(false);  // Should not reach here
    } catch (const std::out_of_range &) {
        assert(true);  // Exception expected
    }
}

template<typename T>
void test_mutable_array_sequence_insert_at_method_negative_index() {
    MutableArraySequence<T> array;
    T value = T();
    try {
        array.InsertAt(-1, value);
        assert(false);  // Should not reach here
    } catch (const std::out_of_range &) {
        assert(true);  // Exception expected
    }
}

template<typename T>
void test_mutable_array_sequence_concat_method(T *items1, int size1, T *items2, int size2) {
    MutableArraySequence<T> array1(size1, items1);
    MutableArraySequence<T> array2(size2, items2);
    array1.Concat(&array2);

    assert(array1.GetSize() == size1 + size2);
    for (int i = 0; i < size1; i++) {
        assert(array1.Get(i) == items1[i]);
    }
    for (int i = 0; i < size2; i++) {
        assert(array1.Get(size1 + i) == items2[i]);
    }
}

template<typename T>
void test_mutable_array_sequence_concat_method_both_empty() {
    MutableArraySequence<T> array1;
    MutableArraySequence<T> array2;
    array1.Concat(&array2);

    assert(array1.GetSize() == 0);
}

template<typename T>
void single_type_full_coverage_test(T* items, int size) {
    T blank_items[0];
    test_mutable_array_sequence_blank_constructor<T>();
    test_mutable_array_sequence_constructor_with_elements(items, size);
    test_mutable_array_sequence_constructor_with_elements_empty_items<T>();
    test_mutable_array_sequence_constructor_with_elements_negative_length(items);
    test_mutable_array_sequence_copy_constructor(items, size);
    test_mutable_array_sequence_copy_constructor_empty_source_array<T>();
    test_mutable_array_sequence_get_first_method(items, size);
    test_mutable_array_sequence_get_last_method(items, size);
    test_mutable_array_sequence_get_length_method(items, size);
    test_mutable_array_sequence_append_method<T>();
    test_mutable_array_sequence_prepend_method<T>();
    test_mutable_array_sequence_get_method(items, size);

    // Test will work correctly only if size of array passed here more that 5
    test_mutable_array_sequence_get_subsequence_method(items, size);

    test_mutable_array_sequence_get_subsequence_method_start_out_of_range(items, size);
    test_mutable_array_sequence_get_subsequence_method_end_out_of_range(items, size);

    test_mutable_array_sequence_insert_at_method<T>();
    test_mutable_array_sequence_insert_at_method_too_large_index<T>();
    test_mutable_array_sequence_insert_at_method_negative_index<T>();
    test_mutable_array_sequence_concat_method(items, size, items, size);
    test_mutable_array_sequence_concat_method(blank_items, 0, items, size);
    test_mutable_array_sequence_concat_method(items, size, blank_items, 0);
    test_mutable_array_sequence_concat_method_both_empty<T>();
    test_mutable_array_sequence_get_first_method_empty_array<T>();
    test_mutable_array_sequence_get_last_method_empty_array<T>();
}

void run_mutable_array_sequence_tests() {
    // Integer test
    int int_items[] = {1, 2, 3, 4, 5};
    single_type_full_coverage_test(int_items, 5);

    // Char test
    char char_items[] = {'a', 'b', 'c', 'd', 'e'};
    single_type_full_coverage_test(char_items, 5);

    // String test
    std::string string_items[] = {"one", "two", "three", "four", "five"};
    single_type_full_coverage_test(string_items, 5);

    // Bool test
    bool bool_items[] = {true, false, true, false, true};
    single_type_full_coverage_test(bool_items, 5);

    // Long test
    long long_items[] = {100000, 200000, 300000, 400000, 500000};
    single_type_full_coverage_test(long_items, 5);

    // Pointer type test
    int *ptr1 = new int(10);
    int *ptr2 = new int(20);
    int *ptr3 = new int(30);
    int *ptr4 = new int(40);
    int *ptr5 = new int(50);
    int *ptr_items[] = {ptr1, ptr2, ptr3, ptr4,ptr5};
    single_type_full_coverage_test(ptr_items, 5);
    delete ptr1;
    delete ptr2;
    delete ptr3;
    delete ptr4;
    delete ptr5;

    // Array type test
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};
    int arr3[] = {7, 8, 9};
    int arr4[] = {10, 11, 12};
    int arr5[] = {13, 14, 15};
    int *arr_items[] = {arr1, arr2,arr3,arr4,arr5};
    single_type_full_coverage_test(arr_items, 5);
}

int main() {
    run_mutable_array_sequence_tests();
    std::cout << "All MutableMutableArraySequence tests passed!" << std::endl;
    return 0;
}

