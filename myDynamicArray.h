//
// Created by Grisha on 09.03.2021.
//

#ifndef LAB2_MYDYNAMICARRAY_H
#define LAB2_MYDYNAMICARRAY_H
#include "cstdlib"
#include "cstring"
#include <string>
#include <iostream>

template <class T>
class myDynamicArray {
private:
    T *arr = NULL;
    int len = 0;
    const size_t elSize = sizeof(T);
public:
    class IndexOutOfRange{};

    friend std::ostream& operator << (std::ostream& cout, myDynamicArray<T> dynamicArray);

    myDynamicArray(T *items, int count);

    myDynamicArray(int size);

    myDynamicArray(myDynamicArray<T> const &dynamicArray);

    ~myDynamicArray();

    int length();

    T get(int index);

    T operator [] (int index);

    void set(int index, T value);

    void resize(int newSize);

    string getStr();
};




#endif //LAB2_MYDYNAMICARRAY_H