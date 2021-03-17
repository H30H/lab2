//
// Created by Grisha on 09.03.2021.
//

#include "myLinkedList.h"

template<class T>
void myLinkedList<T>::append(T item) {
    auto *el = new element;
    el->data = item;
    el->next = nullptr;
    len++;
    if (head == nullptr) {
        head = el;
        end = el;
        return;
    }
    end->next = el;
    end = el;
}

template<class T>
void myLinkedList<T>::prepend(T item) {
    auto *el = new element(item, head);
    //el->data = item;
    //el->next = head;
    len++;
    if (head == nullptr) {
        head = el;
        end = el;
        return;
    }
    head = el;
}

template<class T>
void myLinkedList<T>::insert(T item, int index) {
    element *el = head;
    for (int i = 1; i < index - 1; i++, el = el->next);

    element *elNew = new element*;
    elNew->next = el->next;
    elNew->data = item;
    el->next = elNew;
}

template<class T>
myLinkedList<T>::myLinkedList(T *items, int count) {
    for (int i = 0; i < count; i++) {
        append(items[i]);
    }
}

template<class T>
myLinkedList<T>::myLinkedList(const myLinkedList<T> &linkedList) {
    len = linkedList.len;
    element *el = linkedList.head;
    while (el != nullptr) {
        append(el->data);
        el = el->next;
    }
}

template<class T>
T myLinkedList<T>::getFirst() {
    if (head == nullptr) throw IndexOutOfRange(); //обработка ошибки

    return head->data;
}

template<class T>
T myLinkedList<T>::getLast() {
    if (end == nullptr) throw IndexOutOfRange(); //обработка ошибки

    return end->data;
}

template<class T>
T myLinkedList<T>::get(int index) {
    if (index < 0 || index >= len) throw IndexOutOfRange(); //обработка ошибки

    element *el = head;

    T data;

    for (int i = 1; i < index; i++, el = el->next);

    return el->data;
}

template<class T>
myLinkedList<T> myLinkedList<T>::getSubList(int startIndex, int endIndex) {
    myLinkedList<T> newLinkedList = myLinkedList<T>();
    element *el = head;
    for (int i = 1; i < startIndex; i++, el = el->next);

    for (int i = startIndex; i < endIndex; i++) {
        newLinkedList.append(el->data);
        el = el->next;
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
    end = nullptr;
}

template<class T>
T myLinkedList<T>::pop() {
    return pop(len - 1);
}

template<class T>
T myLinkedList<T>::pop(int index) {
    if (index < 0 || index >= len) throw IndexOutOfRange(); //обработка ошибки

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
myLinkedList<T>::~myLinkedList() {
    Element *next = head;
    while (next != nullptr) {
        head = next;
        next = head->next;
        delete head;
    }
}

template<class T>
T myLinkedList<T>::operator[](int index) {
    return get(index);
}

template<class T>
std::string myLinkedList<T>::getStr() {
    if (len == 0) return std::string("Пустой список!");
    auto str = std::string();
    str += std::string("Лист: {");
    element *el = head;
    while (el != nullptr) {
        str += std::to_string(el->data);
        el = el->next;
        if (el != nullptr) {
            str += std::string(", ");
        }
    }
    str += std::string("}");
    return str;
}
