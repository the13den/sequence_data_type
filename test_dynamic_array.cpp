#include "dynamic_array.h"
#include "random_element_generator.h"
#include <cassert>
#include <string>
#include <iostream>

/// New test functions

template<typename T>
void test_dynamic_array_constructor_blank_with_fill_value(T value) {
    DynamicArray<T> arr1(5, value);
    assert(arr1.GetSize() == 5);
    for (int i = 0; i < 5; i++) {
        assert(arr1.Get(i) == value);
    }
}


template<typename T>
void test_dynamic_array_constructor_blank_without_fill_value_other_type() {
    DynamicArray<T> arr1(5);
    assert(arr1.GetSize() == 5);
    for (int i = 0; i < 5; i++) {
        assert(arr1.Get(i) == T());
    }
}

template<typename T>
void test_dynamic_array_with_elements(T *items) {
    DynamicArray<T> arr2(5, items);
    assert(arr2.GetSize() == 5);
    for (int i = 0; i < 5; i++) {
        assert(arr2.Get(i) == items[i]);
    }
}

template<typename T>
void test_dynamic_array_copy_constructor_with_elements(T *items) {
    DynamicArray<T> arr2(5, items);
    DynamicArray<T> arr3(arr2);
    assert(arr3.GetSize() == 5);
    for (int i = 0; i < 5; i++) {
        assert(arr3.Get(i) == items[i]);
    }
}

template<typename T>
void test_dynamic_array_copy_constructor_without_elements(T *items) {
    DynamicArray<T> arr2(0);
    DynamicArray<T> arr3(arr2);
    assert(arr3.GetSize() == 0);
}

template<typename T>
void test_dynamic_array_destructor() {
    DynamicArray<T> *arr = new DynamicArray<T>(5);
    delete arr; // Should not throw any exceptions or cause any errors
}

template<typename T>
void test_dynamic_array_get_method_without_exception(T *items) {
    DynamicArray<T> arr(5, items);
    for (int i = 0; i < 5; i++) {
        assert(arr.Get(i) == items[i]);
    }
}

template<typename T>
void test_dynamic_array_get_method_with_exception_big_index(T *items) {
    DynamicArray<T> arr(5, items);
    try {
        arr.Get(10);
        assert(false);  // Should not reach here
    } catch (std::out_of_range &) {
        assert(true);  // Exception expected
    }
}

template<typename T>
void test_dynamic_array_get_method_with_exception_small_index(T *items) {
    DynamicArray<T> arr(5, items);
    try {
        arr.Get(-1);
        assert(false);  // Should not reach here
    } catch (std::out_of_range &) {
        assert(true);  // Exception expected
    }
}

template<typename T>
void test_dynamic_array_set_method_arithmetic() {
    if constexpr (std::is_arithmetic<T>::value) {
        DynamicArray<T> arr(5);
        arr.Set(0, static_cast<T>(10));
        assert(arr.Get(0) == static_cast<T>(10));
    }
}

template<typename T>
void test_dynamic_array_set_method_string() {
    if constexpr (std::is_same<T, std::string>::value) {
        DynamicArray<T> arr(5);
        arr.Set(0, "test");
        assert(arr.Get(0) == "test");
    }
}

template<typename T>
void test_dynamic_array_set_method_pointer() {
    if constexpr (std::is_pointer<T>::value) {
        using PointedType = typename std::remove_pointer<T>::type;
        DynamicArray<T> arr(5);
        if constexpr (std::is_polymorphic<PointedType>::value) {
            arr.Set(0, dynamic_cast<T>(new PointedType()));
            assert(arr.Get(0) != nullptr);
        } else {
            arr.Set(0, static_cast<T>(new PointedType()));
            assert(arr.Get(0) != nullptr);
        }
    }
}

template<typename T>
void test_dynamic_array_set_method_default() {
    DynamicArray<T> arr(5);
    T value = T();
    arr.Set(0, value);
    assert(arr.Get(0) == value);
}

template<typename T>
void test_dynamic_array_set_method_with_exception() {
    DynamicArray<T> arr(5);
    try {
        arr.Set(10, T());
        assert(false);  // Should not reach here
    } catch (const std::out_of_range &) {
        assert(true);  // Exception expected
    }
}

// Test resizing for numeric types
template<typename T>
void test_dynamic_array_resize_numeric() {
    if constexpr (std::is_arithmetic<T>::value) {
        DynamicArray<T> arr(5, static_cast<T>(10));
        for (int i = 0; i < 5; i++) {
            assert(arr.Get(i) == static_cast<T>(10));
        }

        arr.Resize(7);
        assert(arr.GetSize() == 7);
        for (int i = 0; i < 5; i++) {
            assert(arr.Get(i) == static_cast<T>(10));
        }
        for (int i = 5; i < 7; i++) {
            assert(arr.Get(i) == T());
        }

        arr.Resize(3);
        assert(arr.GetSize() == 3);
        for (int i = 0; i < 3; i++) {
            assert(arr.Get(i) == static_cast<T>(10));
        }
    }
}

// Test resizing for pointer types
template<typename T>
void test_dynamic_array_resize_pointer() {
    if constexpr (std::is_pointer<T>::value) {
        using PointedType = typename std::remove_pointer<T>::type;
        DynamicArray<T> arr(5, new PointedType());

        for (int i = 0; i < 5; i++) {
            assert(arr.Get(i) != nullptr);
        }

        arr.Resize(7);
        assert(arr.GetSize() == 7);
        for (int i = 0; i < 5; i++) {
            assert(arr.Get(i) != nullptr);
        }
        for (int i = 5; i < 7; i++) {
            assert(arr.Get(i) == T());
        }

        arr.Resize(3);
        assert(arr.GetSize() == 3);
        for (int i = 0; i < 3; i++) {
            assert(arr.Get(i) != nullptr);
        }
    }
}

// Test resizing for default types
template<typename T>
void test_dynamic_array_resize_default() {
    DynamicArray<T> arr(5, T());

    for (int i = 0; i < 5; i++) {
        assert(arr.Get(i) == T());
    }

    arr.Resize(7);
    assert(arr.GetSize() == 7);
    for (int i = 0; i < 5; i++) {
        assert(arr.Get(i) == T());
    }
    for (int i = 5; i < 7; i++) {
        assert(arr.Get(i) == T());
    }

    arr.Resize(3);
    assert(arr.GetSize() == 3);
    for (int i = 0; i < 3; i++) {
        assert(arr.Get(i) == T());
    }
}

// Test resizing for default types
template<typename T>
void test_dynamic_array_resize_overflow_test() {
    DynamicArray<T> arr(5, T());

    try {
        arr.Resize(-1);
        assert(false);  // Should not reach here
    } catch (const std::out_of_range &) {
        assert(true);  // Exception expected
    }
}

template<typename T>
void single_type_full_coverage_test(T* items, int size) {
    test_dynamic_array_constructor_blank_with_fill_value<T>(items[0]);
    test_dynamic_array_constructor_blank_without_fill_value_other_type<T>();
    test_dynamic_array_with_elements(items);
    test_dynamic_array_copy_constructor_with_elements(items);
    test_dynamic_array_copy_constructor_without_elements(items);
    test_dynamic_array_destructor<T>();
    test_dynamic_array_get_method_without_exception(items);
    test_dynamic_array_get_method_with_exception_big_index(items);
    test_dynamic_array_get_method_with_exception_small_index(items);
    test_dynamic_array_set_method_arithmetic<T>();
    test_dynamic_array_set_method_string<T>();
    test_dynamic_array_set_method_pointer<T>();
    test_dynamic_array_set_method_default<T>();
    test_dynamic_array_set_method_with_exception<T>();
    test_dynamic_array_resize_numeric<T>();
    test_dynamic_array_resize_pointer<T>();
    test_dynamic_array_resize_default<T>();
    test_dynamic_array_resize_overflow_test<T>();
}

void run_dynamic_array_tests() {
    // Integer test
    int int_items[] = {1, 2, 3, 4, 5};
    single_type_full_coverage_test(int_items, 5);

    // Double test
    double double_items[] = {1.1, 2.2, 3.3, 4.4, 5.5};
    single_type_full_coverage_test(double_items, 5);

    // Char test
    char char_items[] = {'a', 'b', 'c', 'd', 'e'};
    single_type_full_coverage_test(char_items, 5);

    // String test
    std::string string_items[] = {"one", "two", "three", "four", "five"};
    single_type_full_coverage_test(string_items, 5);

    // Float test
    float float_items[] = {1.1f, 2.2f, 3.3f, 4.4f, 5.5f};
    single_type_full_coverage_test(float_items, 5);

    // Bool test
    bool bool_items[] = {true, false, true, false, true};
    single_type_full_coverage_test(bool_items, 5);

    // Long test
    long long_items[] = {100000, 200000, 300000, 400000, 500000};
    single_type_full_coverage_test(long_items, 5);

    // Pointer type test
    int* ptr1 = new int(10);
    int* ptr2 = new int(20);
    int* ptr_items[] = {ptr1, ptr2};
    single_type_full_coverage_test(ptr_items, 2);
    delete ptr1;
    delete ptr2;

    // Array type test
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};
    int* arr_items[] = {arr1, arr2};
    single_type_full_coverage_test(arr_items, 2);
}

int main() {
    run_dynamic_array_tests();
    std::cout << "All DynamicArray tests passed!" << std::endl;
    return 0;
}
