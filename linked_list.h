//
// Created by Денис Фазалов on 24.06.2024.
//

/// Todo
// 1. Вынести цикл в функцию
// for (int i = 0; i < index - 1; i++) {
//     current = current->next;
// }
//
// 2. Для Get, GetSublist, Remove, InsertAt сделать приблежиние слева и справа, чтобы проходить полсписка, а не весь список


#ifndef LAB_2_LINKED_LIST_H
#define LAB_2_LINKED_LIST_H

#include <stdexcept>
#include <type_traits>


// LinkedList class
template<class T>
class LinkedList {
private:
    struct DataElement {
        T value;
        DataElement *next;
        DataElement *prev;

        DataElement(T val, DataElement *n = nullptr, DataElement *p = nullptr);
    };

    int list_size;
    DataElement *list_beg_ptr;
    DataElement *list_end_ptr;

public:
    // Default constructor
    LinkedList():  list_beg_ptr(nullptr), list_end_ptr(nullptr), list_size(0)  {}

    // Constructor with items
    LinkedList(int size, const T *items);

    // Copy constructor
    LinkedList(const LinkedList<T> &other);

    // Destructor to clean up the list
    ~LinkedList();

    // Getting the value of the first element
    T GetFirst() const;

    // Getting the value of the last element
    T GetLast() const;

    // Getting the value of the element by index
    T Get(int index) const;

    // Get the sublist from start_index to end_index (inclusive)
    LinkedList<T> *GetSubList(int start_index, int end_index) const;

    // Get the length of the linked list
    int GetSize() const;

    // Append an item to the end of the list
    void Append(T item);

    // Prepend an item to the beginning of the list
    void Prepend(T item);

    // Insert an item at the given index
    void Remove(int index);

    // Insert an item at the given index
    void InsertAt(int index, T item);

    // Concatenating two lists (correct way)
    LinkedList<T> *Concat(const LinkedList<T> *list) const;
};

// LinkedList class implementation
template<class T>
// DataElement constructor
LinkedList<T>::DataElement::DataElement(T val, DataElement *n, DataElement *p)
        : value(val), next(n), prev(p) {}

template<class T>
// Constructor with size and items array
LinkedList<T>::LinkedList(int size, const T *items) : list_beg_ptr(nullptr), list_end_ptr(nullptr), list_size(0) {
    if (size < 0) {
        throw std::invalid_argument("Size must be non-negative"); // Check if size is non-negative
    }
    // Append items to the list
    for (int i = 0; i < size; i++) {
        Append(items[i]);
    }
}

template<class T>
// Copy constructor
LinkedList<T>::LinkedList(const LinkedList<T> &other)
        : list_beg_ptr(nullptr), list_end_ptr(nullptr), list_size(0) {
    // Copy elements from input list
    DataElement *current = other.list_beg_ptr;
    while (current != nullptr) {
        Append(current->value);
        current = current->next;
    }
}

template<class T>
// Destructor
LinkedList<T>::~LinkedList() {
    DataElement *current = list_beg_ptr;
    while (current != nullptr) {
        DataElement *next = current->next;
        delete current; // Delete elements
        current = next;
    }
}

template<class T>
// Get first element
T LinkedList<T>::GetFirst() const {
    if (list_beg_ptr == nullptr) {
        throw std::out_of_range("List is empty"); // Check if list is empty
    }
    return list_beg_ptr->value;
}

template<class T>
// Get last element
T LinkedList<T>::GetLast() const {
    if (list_end_ptr == nullptr) {
        throw std::out_of_range("List is empty"); // Check if list is empty
    }
    return list_end_ptr->value;
}

template<class T>
// Get element at index
T LinkedList<T>::Get(int index) const {
    if (index < 0 || index >= list_size) {
        throw std::out_of_range("Index out of range"); // Check index validity
    }
    DataElement *current = list_beg_ptr;
    for (int i = 0; i < index; i++) {
        current = current->next; // Traverse to index
    }
    return current->value;
}


template<class T>
// Get sublist from start_index to end_index
LinkedList<T> *LinkedList<T>::GetSubList(int start_index, int end_index) const {
    if (start_index < 0 || end_index >= list_size || start_index > end_index) {
        throw std::out_of_range("Index error"); // Check indices validity
    }

    LinkedList<T> *sublist = new LinkedList<T>();
    DataElement *current = list_beg_ptr;
    for (int i = 0; i < start_index; i++) {
        current = current->next; // Traverse to start index
    }

    for (int i = start_index; i <= end_index; i++) {
        sublist->Append(current->value); // Append to sublist
        current = current->next;
    }

    return sublist;
}


template<class T>
// Get list length
int LinkedList<T>::GetSize() const {
    return list_size;
}

template<class T>
// Append item to the list
void LinkedList<T>::Append(T item) {
    DataElement *newElement = new DataElement(item);
    if (list_end_ptr) {
        list_end_ptr->next = newElement;
        newElement->prev = list_end_ptr;
        list_end_ptr = newElement;
    } else {
        list_beg_ptr = list_end_ptr = newElement;
    }
    list_size++;
}

template<class T>
// Prepend item to the list
void LinkedList<T>::Prepend(T item) {
    DataElement *newElement = new DataElement(item);
    if (list_beg_ptr) {
        list_beg_ptr->prev = newElement;
        newElement->next = list_beg_ptr;
        list_beg_ptr = newElement;
    } else {
        list_beg_ptr = list_end_ptr = newElement;
    }
    list_size++;
}
template<class T>
void LinkedList<T>::Remove(int index) {
    if (index < 0 || index >= list_size) { // Corrected condition to ensure index is within valid range
        throw std::out_of_range("Index out of range");
    }

    // Special case for removing the list_beg_ptr
    if (index == 0) {
        DataElement *to_delete = list_beg_ptr;
        list_beg_ptr = list_beg_ptr->next;  // Move list_beg_ptr pointer to next element
        delete to_delete;    // Free the memory of the original list_beg_ptr
        if (list_size == 1) {  // If it was the only element
            list_end_ptr = nullptr; // Update list_end_ptr as well
        }
    } else {
        DataElement *current = list_beg_ptr;
        // Traverse the list to find the node just before the one to remove

        for (int i = 0; i < index - 1; i++) {
            current = current->next;
        }

        // current now points to the element before the one to be removed
        DataElement *to_delete = current->next;
        current->next = to_delete->next;  // Bypass the node to be removed

        // If removing the last element, update the list_end_ptr pointer
        if (to_delete == list_end_ptr) {
            list_end_ptr = current;
        }

        delete to_delete;  // Free the memory of the node to be removed
    }

    list_size--;  // Decrement the size of the list
}
template<class T>
// Insert item at index

void LinkedList<T>::InsertAt(int index, T item) {
    if (index < 0 || index > list_size) {
        throw std::out_of_range("Index error"); // Check index validity
    }

    if (index == 0) {
        Prepend(item); // Prepend if index is 0
    } else if (index == list_size) {
        Append(item); // Append if index is at the end
    } else {
        DataElement *current = list_beg_ptr;
        for (int i = 0; i < index; i++) {
            current = current->next; // Traverse to index
        }

        DataElement *newElement = new DataElement(item, current, current->prev);
        current->prev->next = newElement;
        current->prev = newElement;
            list_size++;
    }
}

template<class T>
// Concatenate with another list
LinkedList<T>* LinkedList<T>::Concat(const LinkedList<T>* list) const {
    LinkedList* result = new LinkedList(*this); // Copy current list
    DataElement* current = list->list_beg_ptr;
    while (current) {
        result->Append(current->value); // Append elements from input list
        current = current->next;
    }
    return result;
}


#endif //LAB_2_LINKED_LIST_H
