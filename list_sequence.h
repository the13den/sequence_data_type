//
// Created by Денис Фазалов on 24.06.2024.
//

#ifndef LAB_2_LIST_SEQUENCE_H
#define LAB_2_LIST_SEQUENCE_H

#include "linked_list.h"
#include "sequence_class_definition.h"
#include <iostream>
#include <stdexcept>
#include <type_traits>

// ListSequence class

template<class T>
class ListSequence : public Sequence<T> {
private:
    LinkedList<T> linked_list; // Internal linked list to store elements

public:
    // Default constructor
    ListSequence();

    // Constructor with size and items array
    ListSequence(int size, T *items);

    // Constructor with LinkedList
    ListSequence(const LinkedList<T> &list);

    // Destructor
    ~ListSequence() = default;

    // Get the first element of the sequence
    T GetFirst() const override;

    // Get the last element of the sequence
    T GetLast() const override;

    // Get the element at the specified index
    T Get(int index) const override;

    // Get a subsequence from start_index to end_index
    ListSequence<T> *GetSubsequence(int start_index, int end_index) const override;

    // Get the length of the sequence
    int GetSize() const override;

    // Append an element to the end of the sequence
    ListSequence<T> *Append(T item) override;

    // Prepend an element to the beginning of the sequence
    ListSequence<T> *Prepend(T item) override;

    // Remove an element at the specified index
    ListSequence<T> *Remove(int index) override;

    // Insert an element at the specified index
    ListSequence<T> *InsertAt(int index, T item) override;

    // Concatenate two sequences
    ListSequence<T> *Concat(const Sequence<T> *list) const override;
};


// ListSequence class implementation

template<class T>
// Default constructor
ListSequence<T>::ListSequence() : linked_list() {}

template<class T>
// Constructor with size and items array
ListSequence<T>::ListSequence(int size, T *items) : linked_list(size, items) {}

template<class T>
// Constructor with linked list
ListSequence<T>::ListSequence(const LinkedList<T> &list) : linked_list(list) {}

template<class T>
// Get first element
T ListSequence<T>::GetFirst() const {
    return linked_list.GetFirst();
}

template<class T>
// Get last element
T ListSequence<T>::GetLast() const {
    return linked_list.GetLast();
}

template<class T>
// Get element at index
T ListSequence<T>::Get(int index) const {
    return linked_list.Get(index);
}

template<class T>
// Get subsequence from start_index to end_index
ListSequence<T> *ListSequence<T>::GetSubsequence(int start_index, int end_index) const {
    LinkedList<T> *sublist = linked_list.GetSubList(start_index, end_index);
    return new ListSequence<T>(*sublist);
}

template<class T>
// Get sequence length
int ListSequence<T>::GetSize() const {
    return linked_list.GetSize();
}

template<class T>
// Append item to the sequence
ListSequence<T>* ListSequence<T>::Append(T item) {
    linked_list.Append(item);
    return this;
}

template<class T>
// Prepend item to the sequence
ListSequence<T>* ListSequence<T>::Prepend(T item) {
    linked_list.Prepend(item);
    return this;
}

template<class T>
// Remove item at index
ListSequence<T>* ListSequence<T>::Remove(int index) {
    linked_list.Remove(index);
    return this;
}

template<class T>
// Insert item at index
ListSequence<T>* ListSequence<T>::InsertAt(int index, T item) {
    linked_list.InsertAt(index, item);
    return this;
}

template<class T>
// Concatenate with another sequence
ListSequence<T> *ListSequence<T>::Concat(const Sequence<T> *list) const {
    const ListSequence<T> *new_list_seq = dynamic_cast<const ListSequence<T> *>(list);
    if (!new_list_seq) {
        throw std::invalid_argument("ListSequence error: The provided sequence is not a ListSequence");
    }
    LinkedList<T> *concatenated_list = linked_list.Concat(&(new_list_seq->linked_list));
    return new ListSequence<T>(*concatenated_list);
}

#endif // LAB_2_LIST_SEQUENCE_H
