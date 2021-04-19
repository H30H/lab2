//
// Created by Grisha on 19.03.2021.
//

#ifndef LAB2_MYLISTSEQUENCE_H
#define LAB2_MYLISTSEQUENCE_H

#include "mySequence.h"
#include "myLinkedList.cpp"
#include <iostream>

template <class T>
class myListSequence: mySequence<T> {
private:
    myLinkedList<T> linkedList;
public:
    class IndexOutOfRange{
    public:
        int length;
        int index;
        IndexOutOfRange(int length, int index): length(length), index(index) {};
        IndexOutOfRange(): length(-1), index(-1) {};
    };

    friend std::ostream &operator << (std::ostream &cout, myListSequence<T> listSequence) {
        return cout << listSequence.linkedList;
    }

    friend std::ostream &operator << (std::ostream &cout, myListSequence<T> *listSequence) {
        return cout << *listSequence;
    }

    myListSequence() {
        linkedList = myLinkedList<T>();
    }

    myListSequence(T *items, int count) {
        linkedList = myLinkedList<T>(items, count);
    }

    explicit myListSequence(T item) {
        linkedList = myLinkedList<T>(item);
    }

    myListSequence(const myListSequence<T> &list) {
        linkedList = list.linkedList;
    }

    explicit myListSequence(const myLinkedList<T> &list) {
        linkedList = list;
    }

    T getFirst() {
        if (linkedList.length() == 0) throw IndexOutOfRange(0, 0);
        return linkedList.getFirst();
    }

    T getLast() {
        if (linkedList.length() == 0) throw IndexOutOfRange(0, -1);
        return linkedList.getLast();
    }

    T get(int index) {
        if (index < 0 || index >= linkedList.length()) throw (linkedList.length(), index);
        return linkedList.get(index);
    }

    void set(T item, int index) {
        if (index < 0 || index >= linkedList.length()) throw (linkedList.length(), index);
        linkedList.set(item, index);
    }

    T &operator [] (int index) {
        if (index < 0 || index >= linkedList.length()) throw (linkedList.length(), index);
        return linkedList[index];
    }

    myListSequence<T>& operator = (myListSequence<T> listSequence) {
        linkedList = listSequence.linkedList;
        return *this;
    }

    mySequence<T> *getSubSequence(int startIndex, int endIndex) {
        if (startIndex < 0 || startIndex >= linkedList.length()) throw (linkedList.length(), startIndex);
        if (endIndex < 0 || endIndex >= linkedList.length()) throw (linkedList.length(), endIndex);

        auto *res = new myListSequence<T>(linkedList.getSubList(startIndex, endIndex));
        return res;
    }

    int length() {
        return linkedList.length();
    }

    void append(T item) {
        linkedList.append(item);
    }

    void prepend(T item) {
        linkedList.prepend(item);
    }

    void insert(T item, int index) {
        if (index < 0 || index >= linkedList.length()) throw (linkedList.length(), index);

        linkedList.insert(item, index);
    }

    myListSequence<T> *concat(mySequence<T> *list) {
        for (int i = 0; i < list->length(); i++) {
            linkedList.append(list->get(i));
        }
        return this;
    }

    myListSequence<T> *concat_(mySequence<T> *list) {
        auto *listSequence = new myListSequence<T>(*this);
        for (int i = 0; i < list->length(); i++) {
            listSequence->append(list->get(i));
        }
        return listSequence;
    }

    void reverse() {
        linkedList.reverse();
    }

    int find(T item) {
        return linkedList.find(item);
    }

    int find(mySequence<T> *sequence) {
        myLinkedList<T> list;
        for (int i = 0; i < sequence->length(); i++) {
            list.append(sequence->get(i));
        }
        return linkedList.find(&list);
    }

    myListSequence<myListSequence<T>*>* split(T item) {
        auto res = new myListSequence<myListSequence<T>*>;

        auto *listRes = linkedList.split(item);

        for(auto &i : (*listRes)) {
            res->append(new myListSequence<T>(*i));
        }

        return res;
    }
    /*
    typename myLinkedList<T>::Iterator begin() const {
        return linkedList.begin();
    }

    typename myLinkedList<T>::Iterator end() const {
        return linkedList.end();
    }
    /**/
};


#endif //LAB2_MYLISTSEQUENCE_H
