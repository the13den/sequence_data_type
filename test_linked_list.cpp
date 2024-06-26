#include "linked_list.h"
#include <cassert>
#include <iostream>
#include <string>

template<typename T>
void test_linked_list_blank_constructor() {
    LinkedList<T> list1;
    assert(list1.GetSize() == 0);
}

template<typename T>
void test_linked_list_constructor_with_elements(T *items, int size) {
    LinkedList<T> list2(size, items);
    assert(list2.GetSize() == size);
    for (int i = 0; i < size; i++) {
        assert(list2.Get(i) == items[i]);
    }
}

template<typename T>
void test_linked_list_constructor_with_elements_negative_length(T *items) {
    try {
        LinkedList<T> list(-5, items);
        assert(false);  // Should not reach here
    } catch (const std::invalid_argument &) {
        assert(true);  // Exception expected
    }
}

template<typename T>
void test_linked_list_constructor_with_elements_empty_items() {
    T items[] = {};
    LinkedList<T> list2(0, items);
    assert(list2.GetSize() == 0);
    try {
        list2.Get(0);
        assert(false);  // Should not reach here
    } catch (std::out_of_range &) {
        assert(true);  // Exception expected
    }
}

template<typename T>
void test_linked_list_copy_constructor(T *items, int size) {
    LinkedList<T> list2(size, items);
    LinkedList<T> list3(list2);
    assert(list3.GetSize() == size);
    for (int i = 0; i < size; i++) {
        assert(list3.Get(i) == items[i]);
    }
}

template<typename T>
void test_linked_list_copy_constructor_empty_source_list() {
    LinkedList<T> list2;
    LinkedList<T> list3(list2);
    assert(list3.GetSize() == 0);
    try {
        list2.Get(0);
        assert(false);  // Should not reach here
    } catch (std::out_of_range &) {
        assert(true);  // Exception expected
    }
}

template<typename T>
void test_linked_list_destructor() {
    LinkedList<T> *list = new LinkedList<T>();
    delete list; // Should not throw any exceptions or cause any errors
}

template<typename T>
void test_linked_list_copy_method(T *items, int size) {
    LinkedList<T> list(size, items);
    LinkedList<T> copy = list;
    assert(copy.GetSize() == list.GetSize());
    for (int i = 0; i < size; i++) {
        assert(copy.Get(i) == list.Get(i));
    }
}

template<typename T>
void test_linked_list_copy_method_empty_source_list() {
    LinkedList<T> list;
    LinkedList<T> copy = list;
    assert(copy.GetSize() == list.GetSize());
    for (int i = 0; i < list.GetSize(); i++) {
        assert(copy.Get(i) == list.Get(i));
    }

    try {
        list.Get(0);
        assert(false);  // Should not reach here
    } catch (std::out_of_range &) {
        assert(true);  // Exception expected
    }
}

template<typename T>
void test_linked_list_get_first_method(T *items, int size) {
    LinkedList<T> list(size, items);
    assert(list.GetFirst() == items[0]);
}

template<typename T>
void test_linked_list_get_first_method_empty_list() {
    LinkedList<T> list;
    try {
        list.GetFirst();
        assert(false);  // Should not reach here
    } catch (std::out_of_range &) {
        assert(true);  // Exception expected
    }
}

template<typename T>
void test_linked_list_get_last_method(T *items, int size) {
    LinkedList<T> list(size, items);
    assert(list.GetLast() == items[size - 1]);
}

template<typename T>
void test_linked_list_get_last_method_empty_list() {
    LinkedList<T> list;
    try {
        list.GetLast();
        assert(false);  // Should not reach here
    } catch (std::out_of_range &) {
        assert(true);  // Exception expected
    }
}

template<typename T>
void test_linked_list_get_length_method(T *items, int size) {
    LinkedList<T> list(size, items);
    assert(list.GetSize() == size);
}

template<typename T>
void test_linked_list_append_method() {
    LinkedList<T> list;
    T value = T();
    list.Append(value);
    assert(list.GetLast() == value);
    assert(list.GetSize() == 1);
}

template<typename T>
void test_linked_list_prepend_method() {
    LinkedList<T> list;
    T value = T();
    list.Prepend(value);
    assert(list.GetFirst() == value);
    assert(list.GetSize() == 1);
}

template<typename T>
void test_linked_list_get_method(T *items, int size) {
    LinkedList<T> list(size, items);
    for (int i = 0; i < size; i++) {
        assert(list.Get(i) == items[i]);
    }
    try {
        list.Get(size + 1);
        assert(false);  // Should not reach here
    } catch (std::out_of_range &) {
        assert(true);  // Exception expected
    }
}


template<typename T>
void test_linked_list_insert_at_method() {
    LinkedList<T> list;
    T value1 = T();
    T value2 = T();

    list.Append(value1);
    list.InsertAt(1, value2);

    assert(list.Get(0) == value1);
    assert(list.Get(1) == value2);
}

template<typename T>
void test_linked_list_insert_at_method_too_large_index() {
    LinkedList<T> list;
    T value = T();
    try {
        list.InsertAt(1, value);
        assert(false);  // Should not reach here
    } catch (const std::out_of_range &) {
        assert(true);  // Exception expected
    }
}

template<typename T>
void test_linked_list_insert_at_method_negative_index() {
    LinkedList<T> list;
    T value = T();
    try {
        list.InsertAt(-1, value);
        assert(false);  // Should not reach here
    } catch (const std::out_of_range &) {
        assert(true);  // Exception expected
    }
}

template<typename T>
void test_linked_list_concat_method(T *items1, int size1, T *items2, int size2) {
    LinkedList<T> list1(size1, items1);
    LinkedList<T> list2(size2, items2);
    LinkedList<T> *result = list1.Concat(&list2);

    assert(result->GetSize() == size1 + size2);
    for (int i = 0; i < size1; i++) {
        assert(result->Get(i) == items1[i]);
    }
    for (int i = 0; i < size2; i++) {
        assert(result->Get(size1 + i) == items2[i]);
    }
    delete result;
}

template<typename T>
void test_linked_list_concat_method_first_empty(T *items, int size) {
    LinkedList<T> list1;
    LinkedList<T> list2(size, items);
    LinkedList<T> *result = list1.Concat(&list2);

    assert(result->GetSize() == size);
    for (int i = 0; i < size; i++) {
        assert(result->Get(i) == items[i]);
    }
    delete result;
}

template<typename T>
void test_linked_list_concat_method_second_empty(T *items, int size) {
    LinkedList<T> list1(size, items);
    LinkedList<T> list2;
    LinkedList<T> *result = list1.Concat(&list2);

    assert(result->GetSize() == size);
    for (int i = 0; i < size; i++) {
        assert(result->Get(i) == items[i]);
    }
    delete result;
}

template<typename T>
void test_linked_list_concat_method_both_empty() {
    LinkedList<T> list1;
    LinkedList<T> list2;
    LinkedList<T> *result = list1.Concat(&list2);

    assert(result->GetSize() == 0);
    delete result;
}

template<typename T>
void single_type_full_coverage_test(T*items,int size) {
    T blank_items[0];
    test_linked_list_blank_constructor<T>();
    test_linked_list_constructor_with_elements(items, size);
    test_linked_list_constructor_with_elements_empty_items<T>();
    test_linked_list_constructor_with_elements_negative_length(items);
    test_linked_list_copy_constructor(items, size);
    test_linked_list_copy_constructor_empty_source_list<T>();
    test_linked_list_destructor<T>();
    test_linked_list_copy_method(items, size);
    test_linked_list_get_first_method(items, size);
    test_linked_list_get_last_method(items, size);
    test_linked_list_get_length_method(items, size);
    test_linked_list_append_method<T>();
    test_linked_list_prepend_method<T>();
    test_linked_list_get_method(items, size);
    test_linked_list_insert_at_method<T>();
    test_linked_list_insert_at_method_too_large_index<T>();
    test_linked_list_insert_at_method_negative_index<T>();
    test_linked_list_concat_method(items, size, items, size);
    test_linked_list_concat_method(blank_items, 0, items, size);
    test_linked_list_concat_method(items, size, blank_items, 0);
    test_linked_list_concat_method_both_empty<T>();
    test_linked_list_get_first_method_empty_list<T>();
    test_linked_list_get_last_method_empty_list<T>();
}

void run_linked_list_tests() {
    // Integer test
    int int_items[] = {1, 2, 3, 4, 5};
    single_type_full_coverage_test(int_items,5);

    // Char test
    char char_items[] = {'a', 'b', 'c', 'd', 'e'};
    single_type_full_coverage_test(char_items,5);
    // String test
    std::string string_items[] = {"one", "two", "three", "four", "five"};
    single_type_full_coverage_test(string_items,5);
    // Bool test
    bool bool_items[] = {true, false, true, false, true};
    single_type_full_coverage_test(bool_items,5);

    // Long test
    long long_items[] = {100000, 200000, 300000, 400000, 500000};
    single_type_full_coverage_test(long_items,5);

    // Pointer type test
    int *ptr1 = new int(10);
    int *ptr2 = new int(20);
    int *ptr_items[] = {ptr1, ptr2};
    single_type_full_coverage_test(ptr_items,2);
    delete ptr1;
    delete ptr2;

    // Array type test
    int arr1[] = {1, 2, 3};
    int arr2[] = {4, 5, 6};
    int *arr_items[] = {arr1, arr2};
    single_type_full_coverage_test(arr_items,2);
}

int main() {
    run_linked_list_tests();
    std::cout << "All LinkedList tests passed!" << std::endl;
    return 0;
}
