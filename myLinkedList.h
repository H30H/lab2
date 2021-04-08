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

    /*
    class Iterator {
    private:
        element *el;
    public:
        explicit Iterator(myLinkedList<T> linkedList): el(linkedList.head) {};

        T *operator*() {
            return &(el->data);
        }

        void operator++(int) {
            el = el->next;
        }

        T *begin() {
            return &(head->data);
        }

        T *end() {
            return &(ending->data);
        }
    }; /**/

    friend std::ostream &operator << (std::ostream &cout, myLinkedList<T> linkedList) {
        element *el = linkedList.head;
        cout << '{';
        while(el != nullptr) {
            cout << el->data;
            el = el->next;
            if (el != nullptr) {
                cout << ' ';
            }
        }
        return cout << '}';
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

    T pop();                                    //изменяет список

    T pop(int index);                           //изменяет список

    myLinkedList<T> pop_();                     //создаёт новый список

    myLinkedList<T> pop_(int index);            //создаёт новый список
};

#endif //LAB2_MYLINKEDLIST_H