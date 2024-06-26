cmake_minimum_required(VERSION 3.27)
project(lab_2)

set(CMAKE_CXX_STANDARD 17)


add_executable(
        test_dynamic_array
        test_dynamic_array.cpp
        random_element_generator.h
        dynamic_array.h
)

add_executable(
        test_linked_list
        test_linked_list.cpp
        linked_list.h
)

add_executable(
        test_list_sequence
        test_list_sequence.cpp
        list_sequence.h
)


add_executable(
        test_mutable_array_sequence
        test_mutable_array_sequence.cpp
        mutable_array_sequence.h
)


add_executable(
        test_immutable_array_sequence
        test_immutable_array_sequence.cpp
        immutable_array_sequence.h
)

add_executable(
        test_array_sequence
        test_array_sequence.cpp
        array_sequence.h
)

add_executable(
        user_interface
        user_interface.cpp
        dynamic_array.h
        linked_list.h
        list_sequence.h
        array_sequence.h
)