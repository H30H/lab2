//
// Created by Grisha on 16.03.2021.
//

#ifndef LAB2_MYSEQUENCE_H
#define LAB2_MYSEQUENCE_H

template<class T>
class mySequence {
public:
    virtual T getFirst() = 0;
    virtual T getLast() = 0;
    virtual T get(int index) = 0;
    virtual T operator [] (int index) = 0;
    virtual mySequence<T>* getSubSequence(
            int startIndex, int endIndex) = 0;

    virtual int length() = 0;

    virtual void append(T item) = 0;
    virtual void prepend(T item) = 0;
    virtual void insert(T item, int index) = 0;

    virtual mySequence<T>* concat(mySequence<T>* list) = 0;
};

#endif //LAB2_MYSEQUENCE_H
