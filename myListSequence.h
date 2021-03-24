//
// Created by Grisha on 19.03.2021.
//

#ifndef LAB2_MYLISTSEQUENCE_H
#define LAB2_MYLISTSEQUENCE_H

#include "mySequence.h"
#include "myLinkedList.h"
#include <iostream>

template <class T>
class myListSequence: mySequence<T> {
private:
    myLinkedList<T> linkedList;
public:
    class IndexOutOfRange{};

    friend std::ostream &operator << (std::ostream &cout, myListSequence<T> listSequence) {
        cout << listSequence.linkedList;
        return cout;
    }

    friend std::string to_string(myListSequence<T> listSequence) {
        return listSequence.linkedList.getStr();
    }

    myListSequence() {
        linkedList = myLinkedList<T>();
    }

    myListSequence(T *items, int count) {
        linkedList = myLinkedList<T>(items, count);
    }

    myListSequence(T item) {
        linkedList = myLinkedList<T>(item);
    }

    myListSequence(const myListSequence<T> &list) {
        linkedList = list.linkedList;
    }

    myListSequence(const myLinkedList<T> &list) {
        linkedList = list;
    }

    T getFirst() {
        return linkedList.getFirst();
    }

    T getLast() {
        return linkedList.getLast();
    }

    T get(int index) {
        return linkedList.get(index);
    }

    void set(T item, int index) {
        linkedList.set(item, index);
    }

    T &operator [] (int index) {
        return linkedList.get(index);
    }

    mySequence<T> *getSubSequence(int startIndex, int endIndex) {
        return myListSequence<T>(linkedList.getSubList(startIndex, endIndex));
    }

    int length() {
        return linkedList.length();
    }

    void append(T item) {
        linkedList.append(item);
    }

    mySequence<T> append_(T item) {
        auto listSequence = myListSequence<T>(this);
        listSequence.linkedList.append(item);
        return listSequence;
    }

    void prepend(T item) {
        linkedList.prepend(item);
    }

    mySequence<T> prepend_(T item) {
        auto listSequence = myListSequence<T>(this);
        listSequence.linkedList.prepend(item);
        return listSequence;
    }

    void insert(T item, int index) {
        linkedList.insert(item, index);
    }

    mySequence<T> insert_(T item, int index) {
        auto listSequence = myListSequence<T>(this);
        listSequence.linkedList.insert(item, index);
        return listSequence;
    }

    mySequence<T> *concat(mySequence<T> *list) {
        myListSequence<T> listSequence = new myListSequence<T>(this);
        for (int i = 0; i < list->length(); i++) {
            listSequence.append(list[i]);
        }
        return listSequence;
    }

    std::string getStr() {
        return linkedList.getStr();
    }
};


#endif //LAB2_MYLISTSEQUENCE_H
