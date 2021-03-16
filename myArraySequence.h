//
// Created by Grisha on 16.03.2021.
//

#ifndef LAB2_MYARRAYSEQUENCE_H
#define LAB2_MYARRAYSEQUENCE_H

#include "mySequence.cpp"
#include "myDynamicArray.cpp"
template<class T>
class myArraySequence: mySequence<T>{
private:
    myDynamicArray<T> dynamicArray;
public:
    class IndexOtOfRange{};

    myArraySequence(T* items, int count) {
        dynamicArray = myDynamicArray<T> (items, count);
    }

    myArraySequence() {
        dynamicArray = myDynamicArray<T>(0);
    }

    myArraySequence(const myDynamicArray<T> &array) {
        dynamicArray = array;
    }

    T getFirst() {

        return dynamicArray[0];
    }

    T getLast() {
        return dynamicArray[dynamicArray.length() - 1];
    }

    T get(int index) {
        return dynamicArray[index];
    }

    T operator [] (int index) {
        return dynamicArray.get(index);
    }

    mySequence<T> *getSubSequence(int startIndex, int endIndex) {
        int delta = startIndex < endIndex ? 1 : -1;
        dynamicArray.get(startIndex);
        dynamicArray.get(endIndex);

        auto *newArray = (myArraySequence<T>*) malloc(sizeof(myArraySequence<T>));
        *newArray = myArraySequence();
        for (int i = startIndex, j = 0; i != endIndex; i += delta, j++) {
            newArray->append(dynamicArray.get(i));
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

    void prepend(T item) {
        dynamicArray.resize(dynamicArray.length() + 1);
        for (int i = dynamicArray.length() - 1; i >= 0; i--) {
            dynamicArray.set(i+1, dynamicArray[i]);
        }
        dynamicArray.set(0, item);
    }

    void insert(T item, int index) {
        dynamicArray[index];
        dynamicArray.resize(dynamicArray.length() + 1);
        for (int i = dynamicArray.length() - 1; i >= index; i--) {
            dynamicArray.set(i+1, dynamicArray[i]);
        }
        dynamicArray[index] = item;
    }

    mySequence<T>* concat(mySequence<T>* list) {
        auto *newArray = (myArraySequence<T>*) malloc(sizeof(myArraySequence<T>));
        *newArray = myArraySequence();
        for (int i = this->length(), j = 0; i < newArray->length(); i++, j++) {
            newArray->append(list[j]);
        }
        return newArray;
    }

    string toStr() {
        return dynamicArray.getStr();
    }
};


#endif //LAB2_MYARRAYSEQUENCE_H
