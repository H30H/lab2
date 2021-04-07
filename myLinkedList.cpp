//
// Created by Grisha on 09.03.2021.
//

#include "myLinkedList.h"

template<class T>
void myLinkedList<T>::append(T item) {  //добавление элемента в конец списка
    auto *el = new element;             //создание элемента с входными данными
    el->data = item;
    el->next = nullptr;
    std::cout << "data: " << el->data << ", " << len << std::endl;
    len++;
    if (head == nullptr) {              //проверка на пустоту списка
        head = el;
        ending = el;
        lastGet = el;
        lastInd = 0;
        return;
    }
    ending->next = el;                     //добавление элемента в конец
    ending = el;
}

template<class T>
myLinkedList<T> myLinkedList<T>::append_(T item) {
    return myLinkedList<T>(*this);//.append(item);
}

template<class T>
void myLinkedList<T>::prepend(T item) { //добавление в начало
    auto *el = new element;             //создание нового элемента и заполнение
    el->data = item;
    el->next = head;
    len++;
    if (head == nullptr) {
        head = el;
        ending = el;
        lastGet = el;
        lastInd = 0;
        return;
    }
    head = el;
    lastInd++;
}

template<class T>
myLinkedList<T> myLinkedList<T>::prepend_(T item) {
    return myLinkedList<T>(*this).prepend(item);
}

template<class T>
void myLinkedList<T>::insert(T item, int index) {
    if (index < 0 || index >= len) throw IndexOutOfRange(len, index);

    element *el = head;
    for (int i = 1; i < index - 1; i++, el = el->next);

    element *elNew = new element*;
    elNew->next = el->next;
    elNew->data = item;
    el->next = elNew;
    if (index < lastInd) lastInd++;
}

template<class T>
myLinkedList<T> myLinkedList<T>::insert_(T item, int index) {
    return myLinkedList<T>(*this).insert(item, index);
}

template<class T>
void myLinkedList<T>::set(T item, int index) {
    (*this)[index] = item;
}

template<class T>
myLinkedList<T> myLinkedList<T>::set_(T item, int index) {
    return myLinkedList<T>(*this).set(item, index);
}

template<class T>
myLinkedList<T>::myLinkedList(T *items, int count) {
    if (count < 0) throw IndexOutOfRange(0, count);
    for (int i = 0; i < count; i++) {
        append(items[i]);
    }
}

template<class T>
myLinkedList<T>::myLinkedList(myLinkedList<T> const &linkedList) {
    len = linkedList.len;
    element *el = linkedList.head;
    while (el != nullptr) {
        append(el->data);
        el = el->next;
    }
}


template<class T>
myLinkedList<T>::myLinkedList(T item) {
    append(item);
}

template<class T>
T myLinkedList<T>::getFirst() {
    if (head == nullptr) throw IndexOutOfRange(len, 0); //обработка ошибки

    return head->data;
}

template<class T>
T myLinkedList<T>::getLast() {
    if (ending == nullptr) throw IndexOutOfRange(len, len - 1); //обработка ошибки

    return ending->data;
}

template<class T>
myLinkedList<T> myLinkedList<T>::getSubList(int startIndex, int endIndex) {
    if (startIndex < 0 || startIndex >= len) throw IndexOutOfRange(len, startIndex);
    if (endIndex < 0 || endIndex >= len) throw IndexOutOfRange(len, endIndex);

    myLinkedList<T> newLinkedList = myLinkedList<T>();
    for (int i = startIndex; i < endIndex; i++) {
        newLinkedList.append(get(i));
    }

    return newLinkedList;
}

template<class T>
int myLinkedList<T>::length() {
    return len;
}

template<class T>
myLinkedList<T>::myLinkedList() {
    len = 0;
    head = nullptr;
    ending = nullptr;
}

template<class T>
T myLinkedList<T>::pop() {
    return pop(len - 1);
}

template<class T>
T myLinkedList<T>::pop(int index) {
    if (index < 0 || index >= len) throw IndexOutOfRange(len, index); //обработка ошибки

    element *el = head;
    element *pref = nullptr;

    T data;

    for (int i = 0; i < index; i++, pref = el, el = el->next);

    data = el->data;

    if (pref == nullptr) {
        head = el->next;
    }
    else {
        pref->next = el->next;
    }
    delete el;
    len--;
    return data;
}

template<class T>
myLinkedList<T> myLinkedList<T>::pop_() {
    auto linkedList = myLinkedList<T>(*this);
    linkedList.pop();
    return linkedList;
}

template<class T>
myLinkedList<T> myLinkedList<T>::pop_(int index) {
    auto linkedList = myLinkedList<T>(*this);
    linkedList.pop(index);
    return linkedList;
}

template<class T>
myLinkedList<T>::~myLinkedList() {
    Element *next = head;
    while (next != nullptr) {
        head = next;
        next = head->next;
        delete head;
    }
}

template<class T>
T &myLinkedList<T>::operator[](int index) {
    if (index < 0 || index >= len) throw IndexOutOfRange(len, index); //обработка ошибки

    if (lastInd < index) {
        for (lastInd; lastInd < index; lastInd++, lastGet = lastGet->next);
        return lastGet->data;
    }

    element *el = head;

    T data;

    for (int i = 0; i < index; i++, el = el->next);
    lastInd = index;
    lastGet = el;
    return el->data;
}

template<class T>
T myLinkedList<T>::get(int index) {
    return (*this)[index];
}



