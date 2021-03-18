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

    friend std::ostream &operator << (std::ostream &cout, myLinkedList<T> linkedList) {
        cout << linkedList.getStr();
        return cout;
    }

    friend std::string to_string(myLinkedList<T> linkedList) {
        return linkedList.getStr();
    }

    void append(T item);                        //изменяет список

    myLinkedList<T> append_(T item);            //создаёт новый список

    void prepend(T item);                       //изменяет список

    myLinkedList<T> prepend_(T item);           //создаёт новый список

    void insert(T item, int index);             //изменяет список

    myLinkedList<T> insert_(T item, int index); //создаёт новый список

    void set(T item, int index);                //изменяет список

    myLinkedList<T> set_(T item, int index);    //создаёт новый список

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

    T pop();                                    //изменяет список

    T pop(int index);                           //изменяет список

    myLinkedList<T> pop_();                     //создаёт новый список

    myLinkedList<T> pop_(int index);            //создаёт новый список

    std::string getStr();
};

#endif //LAB2_MYLINKEDLIST_H