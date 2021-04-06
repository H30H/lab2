//
// Created by Grisha on 16.03.2021.
//

#ifndef LAB2_MYARRAYSEQUENCE_H
#define LAB2_MYARRAYSEQUENCE_H

#include "mySequence.h"
#include "myDynamicArray.h"

template<class T>
class myArraySequence: mySequence<T> {
private:
    myDynamicArray<T> dynamicArray;
public:
    class IndexOutOfRange: myDynamicArray<T>::IndexOutOfRange{};

    friend std::ostream &operator << (std::ostream &cout, myArraySequence<T> &arraySequence) {
        cout << '{';
        for (int i = 0; i < arraySequence.length(); i++) {
            cout << arraySequence.dynamicArray[i];
            if (i != arraySequence.length() - 1) {
                cout << ", ";
            }
        }
        cout << '}';
        return cout;
    }

    friend std::string to_string(myArraySequence<T> arraySequence) {
        return std::to_string(arraySequence.dynamicArray);
    }

    myArraySequence(T* items, int count) {
        dynamicArray = myDynamicArray<T> (items, count);
    }

    myArraySequence() {
        int a = 0;
        dynamicArray = myDynamicArray<T>(a);
    }

    explicit myArraySequence(T item) {
        dynamicArray = myDynamicArray<T>(&item, 1);
    }

    myArraySequence(const myArraySequence<T> &array) {
        dynamicArray = array.dynamicArray;
    }

    explicit myArraySequence(const myDynamicArray<T> &array) {
        dynamicArray = array;
    }

    T getFirst() {
        return dynamicArray[0];
    }

    T getLast() {
        return dynamicArray[dynamicArray.length() - 1];
    }

    T get(int index) {
        return dynamicArray.get(index);
    }

    void set(T item, int index) {
        dynamicArray.set(item, index);
    }

    T &operator [] (int index) {
        return dynamicArray[index];
    }

    T *begin() const {
        return dynamicArray.begin();
    }

    T *end() const {
        return dynamicArray.end();
    }

    myArraySequence<T> &operator = (myArraySequence<T> arraySequence) {
        dynamicArray = arraySequence.dynamicArray;
        return *this;
    }

    int operator == (myArraySequence<T> arraySequence) {
        return dynamicArray == arraySequence.dynamicArray;
    }

    myArraySequence<T> *getSubSequence(int startIndex, int endIndex) {
        int delta = startIndex < endIndex ? 1 : -1;
        dynamicArray.get(startIndex);
        dynamicArray.get(endIndex);

        auto newArray = new myArraySequence<T>;
        for (int i = startIndex, j = 0; i != endIndex; i += delta, j++) {
            newArray->append(dynamicArray[i]);
        }

        return newArray;
    }

    int length() {
        return dynamicArray.length();
    }

    void append(T item) {
        dynamicArray.resize(dynamicArray.length() + 1);
        dynamicArray[length() - 1] = item;
    }

    void append(T *item) {
        dynamicArray.resize(dynamicArray.length() + 1);
        dynamicArray[length() - 1] = item;
    }

    myArraySequence<T> append_(const T &item) {
        auto arraySequence = myArraySequence<T>(this);
        arraySequence.append(item);
        return arraySequence;
    }

    void prepend(T item) {
        dynamicArray.resize(dynamicArray.length() + 1);
        for (int i = dynamicArray.length() - 1; i >= 0; i--) {
            dynamicArray[i+1] = dynamicArray[i];
        }
        dynamicArray[0] = item;
    }

    void remove() {
        dynamicArray.resize(0);
    }

    myArraySequence<T> prepend_(T item) {
        auto arraySequence = myArraySequence<T>(this);
        arraySequence.prepend(item);
        return arraySequence;
    }

    void insert(T item, int index) {
        dynamicArray[index];
        dynamicArray.resize(dynamicArray.length() + 1);
        for (int i = dynamicArray.length() - 1; i >= index; i--) {
            dynamicArray[i+1] = dynamicArray[i];
        }
        dynamicArray[index] = item;
    }

    myArraySequence<T> insert_(T item, int index) {
        auto arraySequence = myArraySequence<T>(this);
        arraySequence.insert(item, index);
        return arraySequence;
    }

    myArraySequence<T> *concat(mySequence<T>* list) {
        auto *newArray = new myArraySequence<T>();
        newArray->dynamicArray = dynamicArray;
        for (int i = this->length(), j = 0; i < newArray->length(); i++, j++) {
            newArray->append(list->get(i));
        }
        return newArray;
    }

    myArraySequence<myArraySequence<T>> split(T item) {
        myArraySequence<myArraySequence<T>> res;
        myArraySequence<T> element;
        for (auto &i : dynamicArray) {
            if (i == item) {
                res.append(element);
                element.remove();
                continue;
            }
            element.append(i);
        }
        res.append(element);

        return res;
        /* */
    }
};



#endif //LAB2_MYARRAYSEQUENCE_H
