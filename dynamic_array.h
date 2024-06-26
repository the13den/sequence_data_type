#ifndef LAB_2_DYNAMIC_ARRAY_H
#define LAB_2_DYNAMIC_ARRAY_H

#include <stdexcept>
#include <type_traits>

/// Todo
// 1. Добавить буфер массиву, чтобы базовые операции не вызывали перекопирование

// DynamicArray class
template<class T>
class DynamicArray {
private:
    int array_size;
    T* array_items;

public:
    // Constructor for blank array
    DynamicArray(int size, T fill_value = T());

    // Constructor for array with elements
    DynamicArray(int size, const T* items);

    // Copy constructor
    DynamicArray(const DynamicArray<T>& other);

    // Destructor
    ~DynamicArray();

    // Method to get item by index
    T Get(int index) const;

    // Method to get size of dynamic array
    int GetSize() const;

    // Method to set element at index
    void Set(int index, T value);

    // Method to resize array
    void Resize(int new_size, T fill_value = T());
};

// DynamicArray class implementation

template<class T>
DynamicArray<T>::DynamicArray(int size, T fill_value) : array_size(size), array_items(new T[size]) {
    if (size < 0) {
        throw std::invalid_argument("Size must be non-negative"); // Check if size is non-negative
    }
    // Initialize array elements
    for (int i = 0; i < size; i++) {
        array_items[i] = fill_value;  // Initialize pointers to nullptr
    }
}

template<class T>
DynamicArray<T>::DynamicArray(int size, const T* items) : array_size(size) {
    if (size < 0) {
        throw std::invalid_argument("Size must be non-negative"); // Check if size is non-negative
    }
    array_items = new T[size];
    // Copy items to the dynamic array
    for (int i = 0; i < size; i++) {
        array_items[i] = items[i];
    }
}

template<class T>
DynamicArray<T>::DynamicArray(const DynamicArray<T>& other)
        : array_size(other.array_size), array_items(new T[other.array_size]) {
    // Copy elements from input array
    for (int i = 0; i < array_size; i++) {
        array_items[i] = other.array_items[i];
    }
}

template<class T>
DynamicArray<T>::~DynamicArray() {
    delete[] array_items;  // Free allocated memory
}

template<class T>
T DynamicArray<T>::Get(int index) const {
    if ((index > array_size - 1) || (index < 0)) {
        throw std::out_of_range("Index out of range"); // Check index validity
    }
    return array_items[index];
}

template<class T>
int DynamicArray<T>::GetSize() const {
    return array_size;
}

template<class T>
void DynamicArray<T>::Set(int index, T value) {
    if ((index > array_size - 1) || (index < 0)) {
        throw std::out_of_range("Index out of range"); // Check index validity
    }
    array_items[index] = value;
}

template<class T>
void DynamicArray<T>::Resize(int new_size, T fill_value) {
    if (new_size < 0) {
        throw std::out_of_range("Index out of range"); // Check index validity
    }
    T* new_array_items = new T[new_size];
    for (int i = 0; i < new_size; i++) {
        if (i < array_size) {
            new_array_items[i] = array_items[i]; // Copy old elements
        } else {
            // Initialize new elements
            new_array_items[i] = fill_value;
        }
    }
    delete[] array_items; // Free old array
    array_items = new_array_items; // Assign new array
    array_size = new_size; // Update size
}

#endif //LAB_2_DYNAMIC_ARRAY_H
