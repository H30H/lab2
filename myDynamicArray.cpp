//
// Created by Grisha on 09.03.2021.
//

#include "myDynamicArray.h"

template<class T>
myDynamicArray<T>::myDynamicArray(T *items, int count): len(count){
    if (len < 0) {len = 0; return;}
    arr = (T*) malloc(len * elSize);
    memcpy(arr, items, len * elSize);
}

template<class T>
myDynamicArray<T>::myDynamicArray(int size) {
    if (size < 0) {len = 0; return;}
    len = size;
    arr = (T*) calloc(size, elSize);
}

template<class T>
myDynamicArray<T>::myDynamicArray(const myDynamicArray<T> &dynamicArray) {
    len = dynamicArray.len;
    arr = (T*) malloc(len * elSize);
    memcpy(arr, dynamicArray.arr, len * elSize);
}

template<class T>
myDynamicArray<T>::~myDynamicArray() {
    free(arr);
}

template<class T>
int myDynamicArray<T>::length() {
    return len;
}

template<class T>
T myDynamicArray<T>::get(int index) {
    if (len == 0) throw IndexOutOfRange();  //обработка исключений

    return arr[index];
}

template<class T>
T myDynamicArray<T>::operator[](int index) {
    return get(index);
}

template<class T>
void myDynamicArray<T>::set(int index, T value) {
    if (index < 0 || index >= len) throw IndexOutOfRange(); //обработка исключений

    arr[index] = value;
}

template<class T>
void myDynamicArray<T>::resize(int newSize) {
    if (newSize < 0) throw IndexOutOfRange(); //обработка исключений
    if (len == newSize) return;               //длина не изменилась
    if (newSize == 0) {
        free(arr);
        len = 0;
        arr = NULL;
        return;
    }
    T *arrNew = (T*) calloc(newSize, elSize);
    memcpy(arrNew, arr, newSize < len ? newSize : len);
    len = newSize;
    free(arr);
    arr = arrNew;
}

template<class T>
std::string myDynamicArray<T>::getStr() {
    if (len == 0) return std::string("Пустой массив!");

    std::string res = std::string();
    for (int i = 0; i < len; i++) {
        res += std::to_string(arr[i]);
        if (i != len - 1)
            res += ' ';
    }
    return res;
}
