//
// Created by Grisha on 09.03.2021.
//

#include "myDynamicArray.h"

template<class T>
myDynamicArray<T>::myDynamicArray(T *items, int count) {
    if (count < 0) {len = 0; return;}             //создание нового пустого массива и копирование в него данных из исходного
    resize(count);
    memcpy(arr, items, len * elSize);
}

template<class T>
myDynamicArray<T>::myDynamicArray(int size) {   //создание нового пустого массива размера size
    if (size < 0) {len = 0; return;}
    resize(size);
}


template<class T>
myDynamicArray<T>::myDynamicArray(T item) {     //создание нового массива из одного элемента item
    resize(1);
    arr[0] = item;
}

template<class T>
myDynamicArray<T>::myDynamicArray(const myDynamicArray<T> &dynamicArray) { //создание нового массива и копирование элементов из такого же класса
    len = dynamicArray.len;
    arr = new T(len);
    memcpy(arr, dynamicArray.arr, len * elSize);
}

template<class T>
myDynamicArray<T>::~myDynamicArray() {      //удаление массива
    delete arr;
}

template<class T>
int myDynamicArray<T>::length() {           //вывод длины массива
    return len;
}

template<class T>
T myDynamicArray<T>::get(int index) {
    if (len == 0) throw IndexOutOfRange();  //обработка исключений

    return arr[index];
}

template<class T>
T &myDynamicArray<T>::operator[](int index) {
    return get(index);
}

template<class T>
void myDynamicArray<T>::set(T item, int index) {
    if (index < 0 || index >= len) throw IndexOutOfRange(); //обработка исключений

    arr[index] = item;
}

template<class T>
void myDynamicArray<T>::resize(int newSize) {
    if (newSize < 0) throw IndexOutOfRange(); //обработка исключений
    if (len == newSize) return;               //длина не изменилась
    if (newSize == 0) {                       //нулевая длина, удаление массива
        delete arr;
        len = 0;
        size = 0;
        arr = nullptr;
        return;
    }
    if (newSize > size) {                     //создание нового массива с выделением памяти и заполнение данных
        if (size == 0) size = 1;
        for (size; size < newSize; size *= 2);
        T *arrNew = new T(size);
        memcpy(arrNew, arr, newSize < len ? newSize : len);
        if (arr != nullptr) delete arr;
        arr = arrNew;
    }
    else if (newSize < size / 3) {            //создание нового массива с освобождением памяти и заполнение данных
        for (size; size / 3 > newSize; size /= 2);
        T *arrNew = new T(size);
        memcpy(arrNew, arr, newSize < len ? newSize : len);
        if (arr != nullptr) delete arr;
        arr = arrNew;
    }
    len = newSize;
}

template<class T>
std::string myDynamicArray<T>::getStr() {
    if (len == 0) return std::string("Пустой массив!");

    std::string res = std::string("Динамический массив: {");  //создание новой строки
    for (int i = 0; i < len; i++) {
        res += std::to_string(arr[i]);                        //преобразование типа данных элемента массива (в стринг)
        if (i != len - 1)
            res += ", ";
    }
    res += std::string("}");
    return res;
}

template<class T>
myDynamicArray<T> myDynamicArray<T>::set_(T item, int index) {
    auto dynamicArray = myDynamicArray<T>(this);
    dynamicArray.set(item, index);
    return dynamicArray;
}

template<class T>
myDynamicArray<T> myDynamicArray<T>::resize_(int newSize) {
    auto dynamicArray = myDynamicArray<T>(this);
    dynamicArray.resize(newSize);
    return dynamicArray;
}

