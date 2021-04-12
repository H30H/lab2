//
// Created by Grisha on 16.03.2021.
//

#ifndef LAB2_MYSEQUENCE_H
#define LAB2_MYSEQUENCE_H
#include <iostream>

template<class T>
class mySequence {
public:
    class IndexOutOfRange{
    public:
        int length;
        int index;
        IndexOutOfRange(int length, int index): length(length), index(index) {};
        IndexOutOfRange(): length(-1), index(-1) {};
    };

    class Iterator {
    private:
        int itemIndex;
        mySequence<T> *sequence;
    public:
        explicit Iterator(mySequence<T> *Sequence): sequence(Sequence), itemIndex(0) {};
        explicit Iterator(mySequence<T> *Sequence, int index): sequence(Sequence), itemIndex(index) {};

        T &operator*() const {
            return sequence[0][itemIndex];
        }

        int operator == (const Iterator& iter) const {
            return sequence == iter.sequence && itemIndex == iter.itemIndex;
        }

        int operator != (const Iterator& iter) const {
            return !(*this == iter);
        }

        Iterator& operator++() {
            itemIndex++;
            return *this;
        }

        Iterator begin() {
            return Iterator(sequence);
        }

        Iterator end() {
            return Iterator(sequence, sequence->length());
        }

        void operator () (mySequence<T> *Sequence) {
            sequence = Sequence;
            itemIndex = 0;
        }
    };

    virtual T getFirst() = 0;
    virtual T getLast() = 0;
    virtual T get(int index) = 0;
    virtual void set(T item, int index) = 0;
    virtual T &operator [] (int index) = 0;

    virtual mySequence<T>* getSubSequence(
            int startIndex, int endIndex) = 0;

    virtual int length() = 0;

    virtual void append(T item) = 0;
    virtual void prepend(T item) = 0;
    virtual void insert(T item, int index) = 0;

    virtual mySequence<T>* concat(mySequence<T>* list) = 0;
};

#endif //LAB2_MYSEQUENCE_H
