#ifndef LAB_2_MUTABLE_ARRAY_SEQUENCE_H
#define LAB_2_MUTABLE_ARRAY_SEQUENCE_H

#include "dynamic_array.h"
#include "sequence_class_definition.h"
#include <stdexcept>
#include <type_traits>

// MutableArraySequence class
template<class T>
class MutableArraySequence : public Sequence<T> {
private:
    DynamicArray<T> dynamic_array; // Internal dynamic array to store elements

public:
    // Default constructor
    MutableArraySequence();

    // Constructor with size and items array
    MutableArraySequence(int size, const T *items);

    // Constructor with DynamicArray
    MutableArraySequence(const DynamicArray<T> &array);

    // Copy constructor
    MutableArraySequence(const MutableArraySequence<T>& other);

    // Destructor
    ~MutableArraySequence() = default;

    // Get the first element of the sequence
    T GetFirst() const override;

    // Get the last element of the sequence
    T GetLast() const override;

    // Get the element at the specified index
    T Get(int index) const override;

    // Get a subsequence from start_index to end_index
    MutableArraySequence<T> *GetSubsequence(int start_index, int end_index) override;

    // Get the length of the sequence
    int GetSize() const override;

    // Append an element to the end of the sequence
    MutableArraySequence<T> *Append(T item) override;

    // Prepend an element to the beginning of the sequence
    MutableArraySequence<T> *Prepend(T item) override;

    // Remove an element at the specified index
    MutableArraySequence<T> *Remove(int index) override;

    // Insert an element at the specified index
    MutableArraySequence<T> *InsertAt(int index, T item) override;

    // Concatenate two MutableArraySequences
    MutableArraySequence<T> *Concat(const Sequence<T> *list) override;
};

// MutableArraySequence class implementation

template<class T>
// Default constructor
MutableArraySequence<T>::MutableArraySequence() : dynamic_array(0) {}

template<class T>
// Constructor with size and items array
MutableArraySequence<T>::MutableArraySequence(int size, const T *items) : dynamic_array(size, items) {}

template<class T>
// Constructor with dynamic array
MutableArraySequence<T>::MutableArraySequence(const DynamicArray<T> &array) : dynamic_array(array) {}

template<class T>
// Copy constructor
MutableArraySequence<T>::MutableArraySequence(const MutableArraySequence<T>& other) : dynamic_array(other.dynamic_array) {}

template<class T>
// Get first element
T MutableArraySequence<T>::GetFirst() const {
    if (dynamic_array.GetSize() == 0) {
        throw std::out_of_range("Sequence is empty");
    }
    return dynamic_array.Get(0);
}

template<class T>
// Get last element
T MutableArraySequence<T>::GetLast() const {
    if (dynamic_array.GetSize() == 0) {
        throw std::out_of_range("Sequence is empty");
    }
    return dynamic_array.Get(dynamic_array.GetSize() - 1);
}

template<class T>
// Get element at index
T MutableArraySequence<T>::Get(int index) const {
    return dynamic_array.Get(index);
}

// Get subsequence from start_index to end_index
template<class T>
MutableArraySequence<T>* MutableArraySequence<T>::GetSubsequence(int start_index, int end_index) {
    if (start_index < 0 || end_index >= dynamic_array.GetSize() || start_index > end_index) {
        throw std::out_of_range("Index out of range");
    }

    int subsequence_len = end_index - start_index + 1;
    DynamicArray<T> new_array(subsequence_len);

    for (int i = 0; i < subsequence_len; i++) {
        new_array.Set(i, dynamic_array.Get(start_index + i));
    }

    dynamic_array = new_array;
    return this;
}

template<class T>
// Get sequence length
int MutableArraySequence<T>::GetSize() const {
    return dynamic_array.GetSize();
}

// Append item to the sequence
template<class T>
MutableArraySequence<T> *MutableArraySequence<T>::Append(T item) {
    dynamic_array.Resize(dynamic_array.GetSize() + 1); // Increase size
    dynamic_array.Set(dynamic_array.GetSize() - 1, item); // Set new item
    return this;
}

// Prepend item to the sequence
template<class T>
MutableArraySequence<T> *MutableArraySequence<T>::Prepend(T item) {
    dynamic_array.Resize(dynamic_array.GetSize() + 1); // Increase size
    // Shift elements to the right
    for (int i = dynamic_array.GetSize() - 1; i > 0; --i) {
        dynamic_array.Set(i, dynamic_array.Get(i - 1));
    }
    dynamic_array.Set(0, item); // Set new item at the beginning
    return this;
}

// Remove item at index
template<class T>
MutableArraySequence<T> *MutableArraySequence<T>::Remove(int index) {
    if (index < 0 || index >= dynamic_array.GetSize()) {
        throw std::out_of_range("Index out of range"); // Check index validity
    }

    for (int i = index; i < dynamic_array.GetSize() - 1; i++) {
        dynamic_array.Set(i, dynamic_array.Get(i + 1));
    }
    dynamic_array.Resize(dynamic_array.GetSize() - 1);
    return this;
}

// Insert item at index
template<class T>
MutableArraySequence<T> *MutableArraySequence<T>::InsertAt(int index, T item) {
    if (index < 0 || index > dynamic_array.GetSize()) {
        throw std::out_of_range("Index out of range"); // Check index validity
    }
    dynamic_array.Resize(dynamic_array.GetSize() + 1);
    // Shift elements to the right from index
    for (int i = dynamic_array.GetSize() - 1; i > index; --i) {
        dynamic_array.Set(i, dynamic_array.Get(i - 1));
    }
    dynamic_array.Set(index, item); // Set new item at index
    return this;
}

// Concatenate with another sequence
template<class T>
MutableArraySequence<T> *MutableArraySequence<T>::Concat(const Sequence<T> *list) {
    int original_size = dynamic_array.GetSize();
    dynamic_array.Resize(original_size + list->GetSize());

    for (int i = 0; i < list->GetSize(); i++) {
        dynamic_array.Set(original_size + i, list->Get(i));
    }

    return this;
}

#endif //LAB_2_MUTABLE_ARRAY_SEQUENCE_H
