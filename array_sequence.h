#ifndef LAB_2_ARRAY_SEQUENCE_H
#define LAB_2_ARRAY_SEQUENCE_H

#include "dynamic_array.h"
#include "sequence_class_definition.h"
#include <stdexcept>
#include <type_traits>

// ArraySequence class
template<class T>
class ArraySequence : public Sequence<T> {
private:
    DynamicArray<T> dynamic_array; // Internal dynamic array to store elements

public:
    // Default constructor
     ArraySequence();

    // Constructor with size and items array
     ArraySequence(int size, const T *items);

    // Constructor with DynamicArray
    ArraySequence(const DynamicArray<T> &array);

    // Copy constructor
     ArraySequence(const ArraySequence<T>& other);

    // Destructor
    virtual ~ArraySequence() = default;

    // Get the first element of the sequence
    virtual T GetFirst() const override;

    // Get the last element of the sequence
    virtual T GetLast() const override;

    // Get the element at the specified index
    virtual T Get(int index) const override;

    // Get a subsequence from start_index to end_index
    virtual ArraySequence<T> *GetSubsequence(int start_index, int end_index) override;

    // Get the length of the sequence
    virtual int GetSize() const override;

    // Append an element to the end of the sequence
    virtual ArraySequence<T> *Append(T item) override;

    // Prepend an element to the beginning of the sequence
    virtual ArraySequence<T> *Prepend(T item) override;

    // Remove an element at the specified index
    virtual ArraySequence<T> *Remove(int index) override;

    // Insert an element at the specified index
    virtual ArraySequence<T> *InsertAt(int index, T item) override;

    // Concatenate two ArraySequences
    virtual ArraySequence<T> *Concat( Sequence<T> *list) override;
};

// ArraySequence class implementation

template<class T>
// Default constructor
ArraySequence<T>::ArraySequence() : dynamic_array(0) {}

template<class T>
// Constructor with size and items array
ArraySequence<T>::ArraySequence(int size, const T *items) : dynamic_array(size, items) {}

template<class T>
// Constructor with dynamic array
ArraySequence<T>::ArraySequence(const DynamicArray<T> &array) : dynamic_array(array) {}

template<class T>
// Copy constructor
ArraySequence<T>::ArraySequence(const ArraySequence<T>& other) : dynamic_array(other.dynamic_array) {}

template<class T>
// Get first element
T ArraySequence<T>::GetFirst() const {
    if (dynamic_array.GetSize() == 0) {
        throw std::out_of_range("Sequence is empty");
    }
    return dynamic_array.Get(0);
}

template<class T>
// Get last element
T ArraySequence<T>::GetLast() const {
    if (dynamic_array.GetSize() == 0) {
        throw std::out_of_range("Sequence is empty");
    }
    return dynamic_array.Get(dynamic_array.GetSize() - 1);
}

template<class T>
// Get element at index
T ArraySequence<T>::Get(int index) const {
    return dynamic_array.Get(index);
}

// Get subsequence from start_index to end_index
template<class T>
ArraySequence<T>* ArraySequence<T>::GetSubsequence(int start_index, int end_index) {
    if (start_index < 0 || end_index >= dynamic_array.GetSize() || start_index > end_index) {
        throw std::out_of_range("Index out of range");
    }

    int subsequence_len = end_index - start_index + 1;
    T* sub_items = new T[subsequence_len];
    for (int i = 0; i < subsequence_len; i++) {
        sub_items[i] = dynamic_array.Get(start_index + i);
    }

    ArraySequence* subsequence = new ArraySequence(subsequence_len, sub_items);
    delete[] sub_items;
    return subsequence;
}

template<class T>
// Get sequence length
int ArraySequence<T>::GetSize() const {
    return dynamic_array.GetSize();
}

// Append item to the sequence
template<class T>
ArraySequence<T> *ArraySequence<T>::Append(T item) {
    dynamic_array.Resize(dynamic_array.GetSize() + 1); // Increase size
    dynamic_array.Set(dynamic_array.GetSize() - 1, item); // Set new item
    return this;
}

// Prepend item to the sequence
template<class T>
ArraySequence<T> *ArraySequence<T>::Prepend(T item) {
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
ArraySequence<T> *ArraySequence<T>::Remove(int index) {
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
ArraySequence<T> *ArraySequence<T>::InsertAt(int index, T item) {
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
ArraySequence<T> *ArraySequence<T>::Concat(Sequence<T> *list) {
    ArraySequence* result = new ArraySequence(dynamic_array);
    for (int i = 0; i < list->GetSize(); i++) {
        result->Append(list->Get(i));
    }
    return result;
}

#endif //LAB_2_ARRAY_SEQUENCE_H
