//
// Created by Денис Фазалов on 24.06.2024.
//

#ifndef LAB_2_IMMUTABLE_ARRAY_SEQUENCE_H
#define LAB_2_IMMUTABLE_ARRAY_SEQUENCE_H
#include "array_sequence.h"
// Immutable ArraySequence

template<class T>
class ImmutableArraySequence : public ArraySequence<T> {
public:
    // Inherit constructors from ArraySequence
    using ArraySequence<T>::ArraySequence;

    // Override modification methods to prevent changes
    ImmutableArraySequence *Append(T item) const override;
    ImmutableArraySequence *Remove(T item) const override;
    ImmutableArraySequence *Prepend(T item) const override;
    ImmutableArraySequence *InsertAt(int index, T item) const override;
};

// ImmutableArraySequence class implementation


template<class T>
// Append item to the sequence
ImmutableArraySequence<T>* ImmutableArraySequence<T>::Append(T item) const {
    ImmutableArraySequence<T>* copy = new ImmutableArraySequence<T>(*this);

    ArraySequence<T>* new_sequence = copy->ArraySequence<T>::Append(item);

    return static_cast<ImmutableArraySequence<T>*>(new_sequence);
}

template<class T>
// Prepend item to the sequence
ImmutableArraySequence<T>* ImmutableArraySequence<T>::Prepend(T item) const {
    ImmutableArraySequence<T>* copy = new ImmutableArraySequence<T>(*this);

    ArraySequence<T>* new_sequence = copy->ArraySequence<T>::Prepend(item);

    return static_cast<ImmutableArraySequence<T>*>(new_sequence);
}

template<class T>
// Prepend item to the sequence
ImmutableArraySequence<T>* ImmutableArraySequence<T>::Remove(T item) const {
    ImmutableArraySequence<T>* copy = new ImmutableArraySequence<T>(*this);

    ArraySequence<T>* new_sequence = copy->ArraySequence<T>::Remove(item);

    return static_cast<ImmutableArraySequence<T>*>(new_sequence);
}

template<class T>
// Insert item at index
ImmutableArraySequence<T>* ImmutableArraySequence<T>::InsertAt(int index, T item) const {
    ImmutableArraySequence<T>* copy = new ImmutableArraySequence<T>(*this);

    ArraySequence<T>* new_sequence = copy->ArraySequence<T>::InsertAt(index, item);

    return static_cast<ImmutableArraySequence<T>*>(new_sequence);
}




#endif //LAB_2_IMMUTABLE_ARRAY_SEQUENCE_H
