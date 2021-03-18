//
// Created by Grisha on 09.03.2021.
//

#ifndef LAB2_MYDYNAMICARRAY_H
#define LAB2_MYDYNAMICARRAY_H
#include "cstring"
#include <string>
#include <iostream>

template <class T>
class myDynamicArray {
private:
    T *arr = nullptr;
    int len = 0;
    int size = 0;
    const size_t elSize = sizeof(T);
public:
    class IndexOutOfRange{};

    friend std::ostream &operator << (std::ostream &cout, myDynamicArray<T> dynamicArray) {
        cout << dynamicArray.getStr();
        return cout;
    }

    friend std::string to_string(myDynamicArray<T> dynamicArray) {
        return dynamicArray.getStr();
    }

    myDynamicArray(T *items, int count);

    myDynamicArray(int size);

    myDynamicArray(myDynamicArray<T> const &dynamicArray);

    ~myDynamicArray();

    int length();

    T get(int index);

    T operator [] (int index);

    void set(int index, T value);                       //изменяет массив

    myDynamicArray<T> set_(int index, T value);         //создаёт новый массив

    void resize(int newSize);                           //изменяет массив

    myDynamicArray<T> resize_(int newSize);             //создаёт новый массив

    std::string getStr();
};




#endif //LAB2_MYDYNAMICARRAY_H