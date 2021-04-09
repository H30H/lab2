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
    typedef struct Element {        //структура одного элемента связного списка
        T data;                     // * данные, хранящиеся в одном элементе
        struct Element *next;       // * ссылка на следующий элемент
    } element;

    int len = 0;                    //длина связного списка
    int lastInd = -1;               //индекс того элемента, к которому мы обращались в последный раз

    element *head = nullptr;        //ссылка на начало списка
    element *ending = nullptr;      //ссылка на конец списка
    element *lastGet = nullptr;     //ссылка на элемент с индексом lastInd
public:
    class IndexOutOfRange{
    public:
        int length;
        int index;
        IndexOutOfRange(int length, int index): length(length), index(index) {};
        IndexOutOfRange(): length(-1), index(-1) {};
    };

    class Iterator {               //класс итератора, для работы итератора со связным списком
    private:
        myLinkedList<T> *list;
        element *el;
    public:
        explicit Iterator(myLinkedList<T> *linkedList): list(linkedList), el(linkedList->head) {};
        explicit Iterator(myLinkedList<T> *linkedList, element *elem): list(linkedList), el(elem) {};

        T &operator*() const {
            return el->data;
        }

        int operator == (const Iterator& iter) const {
            return list == iter.list && el == iter.el;
        }

        int operator != (const Iterator& iter) const {
            return !(*this == iter);
        }

        Iterator& operator++() {
            if (el != nullptr)
                el = el->next;
            return *this;
        }

        Iterator begin() {
            return Iterator(list);
        }

        Iterator end() {
            return Iterator(list, nullptr);
        }
    };

    friend std::ostream &operator << (std::ostream &cout, myLinkedList<T> linkedList) {
        element *el = linkedList.head;
        cout << '{';
        while(el != nullptr) {
            cout << el->data;
            el = el->next;
            if (el != nullptr) {
                cout << ", ";
            }
        }
        return cout << '}';
    }

    void append(T item);

    void prepend(T item);

    void insert(T item, int index);

    void set(T item, int index);

    myLinkedList(T *items, int count);

    explicit myLinkedList(T item);

    myLinkedList();

    myLinkedList(myLinkedList<T> const &linkedList);

    ~myLinkedList();

    T getFirst();

    T getLast();

    T get(int index);

    T &operator [] (int index);

    myLinkedList<T> getSubList(int startIndex, int endIndex);

    int length();

    T pop();

    T pop(int index);
    /*
    myLinkedList<myLinkedList<T>*>* split(T item) {

    }
    /* */
};

#endif //LAB2_MYLINKEDLIST_H