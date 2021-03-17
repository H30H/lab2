//
// Created by Grisha on 09.03.2021.
//

#ifndef LAB2_MYLINKEDLIST_H
#define LAB2_MYLINKEDLIST_H

#include "cstdlib"
#include <iostream>

template<class T>
class myLinkedList {
private:
    typedef struct Element {
        T data;
        struct Element *next;
    } element;

    int len = 0;

    element *head = nullptr;
    element *end = nullptr;

public:
    class IndexOutOfRange{};

    void append(T item);

    void prepend(T item);

    void insert(T item, int index);

    myLinkedList(T *items, int count);

    myLinkedList();

    myLinkedList(myLinkedList<T> const &linkedList);

    ~myLinkedList();

    T getFirst();

    T getLast();

    T get(int index);

    T operator [] (int index);

    myLinkedList<T> getSubList(int startIndex, int endIndex);

    int length();

    T pop();

    T pop(int index);

    std::string getString();
};

#endif //LAB2_MYLINKEDLIST_H