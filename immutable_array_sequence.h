#ifndef LAB_2_IMMUTABLE_ARRAY_SEQUENCE_H
#define LAB_2_IMMUTABLE_ARRAY_SEQUENCE_H

#include "dynamic_array.h"
#include "array_sequence.h"
#include <stdexcept>
#include <type_traits>

// ImmutableArraySequence class
template<class T>
class ImmutableArraySequence : public ArraySequence<T> {
private:
    DynamicArray<T> dynamic_array; // Internal dynamic array to store elements

public:
    // Default constructor
    ImmutableArraySequence();

    // Constructor with size and items array
    ImmutableArraySequence(int size, const T *items);

    // Constructor with DynamicArray
    ImmutableArraySequence(const DynamicArray<T> &array);

    // Copy constructor
    ImmutableArraySequence(const ImmutableArraySequence<T>& other);

    // Destructor
    ~ImmutableArraySequence() = default;

    // Get the first element of the sequence
    T GetFirst() const override;

    // Get the last element of the sequence
    T GetLast() const override;

    // Get the element at the specified index
    T Get(int index) const override;

    // Get a subsequence from start_index to end_index
    ImmutableArraySequence<T> *GetSubsequence(int start_index, int end_index)  override;

    // Get the length of the sequence
    int GetSize() const override;

    // Append an element to the end of the sequence
    ImmutableArraySequence<T> *Append(T item) ;

    // Prepend an element to the beginning of the sequence
    ImmutableArraySequence<T> *Prepend(T item) ;

    // Remove an element at the specified index
    ImmutableArraySequence<T> *Remove(int index) ;

    // Insert an element at the specified index
    ImmutableArraySequence<T> *InsertAt(int index, T item) ;

    // Concatenate two ArraySequences
    ImmutableArraySequence<T> *Concat( Sequence<T> *list)  override;
};

// ImmutableArraySequence class implementation

template<class T>
// Default constructor
ImmutableArraySequence<T>::ImmutableArraySequence() : dynamic_array(0) {}

template<class T>
// Constructor with size and items array
ImmutableArraySequence<T>::ImmutableArraySequence(int size, const T *items) : dynamic_array(size, items) {}

template<class T>
// Constructor with dynamic array
ImmutableArraySequence<T>::ImmutableArraySequence(const DynamicArray<T> &array) : dynamic_array(array) {}

template<class T>
// Copy constructor
ImmutableArraySequence<T>::ImmutableArraySequence(const ImmutableArraySequence<T>& other) : dynamic_array(other.dynamic_array) {}

template<class T>
// Get first element
T ImmutableArraySequence<T>::GetFirst() const {
    if (dynamic_array.GetSize() == 0) {
        throw std::out_of_range("Sequence is empty");
    }
    return dynamic_array.Get(0);
}

template<class T>
// Get last element
T ImmutableArraySequence<T>::GetLast() const {
    if (dynamic_array.GetSize() == 0) {
        throw std::out_of_range("Sequence is empty");
    }
    return dynamic_array.Get(dynamic_array.GetSize() - 1);
}

template<class T>
// Get element at index
T ImmutableArraySequence<T>::Get(int index) const {
    return dynamic_array.Get(index);
}

// Get subsequence from start_index to end_index
template<class T>
ImmutableArraySequence<T>* ImmutableArraySequence<T>::GetSubsequence(int start_index, int end_index)  {
    if (start_index < 0 || end_index >= dynamic_array.GetSize() || start_index > end_index) {
        throw std::out_of_range("Index out of range");
    }

    int subsequence_len = end_index - start_index + 1;
    DynamicArray<T> new_array(subsequence_len);

    for (int i = 0; i < subsequence_len; i++) {
        new_array.Set(i, dynamic_array.Get(start_index + i));
    }

    return new ImmutableArraySequence(new_array);
}

template<class T>
// Get sequence length
int ImmutableArraySequence<T>::GetSize() const {
    return dynamic_array.GetSize();
}

// Append item to the sequence
template<class T>
ImmutableArraySequence<T> *ImmutableArraySequence<T>::Append(T item)  {
    DynamicArray<T> new_array(dynamic_array.GetSize() + 1);

    for (int i = 0; i < dynamic_array.GetSize(); ++i) {
        new_array.Set(i, dynamic_array.Get(i));
    }

    new_array.Set(dynamic_array.GetSize(), item);

    return new ImmutableArraySequence(new_array);
}

// Prepend item to the sequence
template<class T>
ImmutableArraySequence<T> *ImmutableArraySequence<T>::Prepend(T item) {
    DynamicArray<T> new_array(dynamic_array.GetSize() + 1);

    new_array.Set(0, item);

    for (int i = 0; i < dynamic_array.GetSize(); ++i) {
        new_array.Set(i + 1, dynamic_array.Get(i));
    }

    return new ImmutableArraySequence(new_array);
}

// Remove item at index
template<class T>
ImmutableArraySequence<T> *ImmutableArraySequence<T>::Remove(int index)  {
    if (index < 0 || index >= dynamic_array.GetSize()) {
        throw std::out_of_range("Index out of range");
    }

    DynamicArray<T> new_array(dynamic_array.GetSize() - 1);

    for (int i = 0, j = 0; i < dynamic_array.GetSize(); ++i) {
        if (i != index) {
            new_array.Set(j++, dynamic_array.Get(i));
        }
    }

    return new ImmutableArraySequence(new_array);
}

// Insert item at index
template<class T>
ImmutableArraySequence<T> *ImmutableArraySequence<T>::InsertAt(int index, T item)  {
    if (index < 0 || index > dynamic_array.GetSize()) {
        throw std::out_of_range("Index out of range");
    }

    DynamicArray<T> new_array(dynamic_array.GetSize() + 1);

    for (int i = 0, j = 0; i < dynamic_array.GetSize(); ++i, ++j) {
        if (j == index) {
            new_array.Set(j++, item);
        }
        new_array.Set(j, dynamic_array.Get(i));
    }

    if (index == dynamic_array.GetSize()) {
        new_array.Set(index, item);
    }

    return new ImmutableArraySequence(new_array);
}

// Concatenate with another sequence
template<class T>
ImmutableArraySequence<T> *ImmutableArraySequence<T>::Concat( Sequence<T> *list)  {
    DynamicArray<T> new_array(dynamic_array.GetSize() + list->GetSize());

    for (int i = 0; i < dynamic_array.GetSize(); ++i) {
        new_array.Set(i, dynamic_array.Get(i));
    }

    for (int i = 0; i < list->GetSize(); ++i) {
        new_array.Set(dynamic_array.GetSize() + i, list->Get(i));
    }

    return new ImmutableArraySequence(new_array);
}

#endif //LAB_2_IMMUTABLE_ARRAY_SEQUENCE_H
