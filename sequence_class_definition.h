//
// Created by Денис Фазалов on 24.06.2024.
//

#ifndef LAB_2_SEQUENCE_CLASS_DEFINITION_H
#define LAB_2_SEQUENCE_CLASS_DEFINITION_H

// Sequence class
template<class T>
class Sequence {
public:
    virtual T GetFirst() const = 0;
    virtual T GetLast() const = 0;
    virtual T Get(int index) const = 0;
    virtual Sequence<T> *GetSubsequence(int start_index, int end_index) = 0;
    virtual int GetSize() const = 0;
    virtual Sequence *Append(T item) = 0;
    virtual Sequence *Prepend(T item) = 0;
    virtual Sequence *Remove(int index) = 0;
    virtual Sequence *InsertAt(int index, T item) = 0;
    virtual Sequence<T> *Concat(Sequence<T> *list) = 0;
};

#endif // LAB_2_SEQUENCE_CLASS_DEFINITION_H
