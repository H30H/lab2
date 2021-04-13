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

    element *head = nullptr;        //ссылка на начало списка
    element *ending = nullptr;      //ссылка на конец списка
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

        void operator () (myLinkedList<T> *linkedList) {
            list = linkedList;
            el = linkedList->head;
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

    friend std::ostream &operator << (std::ostream &cout, myLinkedList<T> *linkedList) {
        return cout << *linkedList;
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

    myLinkedList<T> operator * () {
        return *this;
    }

    myLinkedList<myLinkedList<T>*>* split(T item) {
        auto res = new myLinkedList<myLinkedList<T>*>;
        auto elem = new myLinkedList<T>;
        myLinkedList<T>::Iterator iter(this);
        for (auto &i : iter) {
            if (i == item) {
                res->append(elem);
                elem = new myLinkedList<T>;
                continue;
            }
            elem->append(i);
        }
        res->append(elem);
        return res;
    }

    int find(T item) {
        if (len == 0) throw IndexOutOfRange(0, 0);
        element *elem = head;
        int index = 0;
        while(elem != nullptr) {
            if (elem->data == item)
                return index;
            elem = elem->next;
            index++;
        }
        return -1;
    }

    int find(myLinkedList<T> linkedList) {
        if (linkedList.len == 0) throw IndexOutOfRange(0, 0);
        if (len == 0) throw IndexOutOfRange(0, 0);

        if (len < linkedList.len) return -1;

        element *elem = head;
        element *compare = linkedList.head;
        int index = 0;
        int count = 0;
        while (elem != nullptr) {
            if (count == linkedList.len)  //мы нашли подпоследовательность, которая начинается с элемента index
                return index;

            if (index + len > linkedList.len)  //у нас осталось для обхода меньше элементов, чем содержится в linkedList
                break;

            if (elem->data == compare->data) {
                count++;
                compare = compare->next;
            }
            else {
                index++;

                if (count != 0) {
                    compare = linkedList.head;
                    index += count;
                    count = 0;
                }
            }

            elem = elem->next;
        }

        return -1;
    }


};

#endif //LAB2_MYLINKEDLIST_H
