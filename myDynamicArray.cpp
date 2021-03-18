//
// Created by Grisha on 09.03.2021.
//

#include "myDynamicArray.h"

template<class T>
myDynamicArray<T>::myDynamicArray(T *items, int count): len(count){
    if (len < 0) {len = 0; return;}             //создание нового пустого массива и копирование в него данных из исходного
    arr = new T(count);
    memcpy(arr, items, len * elSize);
}

template<class T>
myDynamicArray<T>::myDynamicArray(int size) {   //создание нового пустого массива размера size
    if (size < 0) {len = 0; return;}
    len = size;
    arr = new T(size);
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
    if (newSize == 0) {                       //нулевая длина, удаление массива
        delete arr;
        len = 0;
        arr = nullptr;
        return;
    }
    T *arrNew = new T(newSize);               //создание нового массива и заполнение данных
    memcpy(arrNew, arr, newSize < len ? newSize : len);
    len = newSize;
    delete arr;
    arr = arrNew;
}

template<class T>
std::string myDynamicArray<T>::getStr() {
    if (len == 0) return std::string("Пустой массив!");

    std::string res = std::string("Динамический массив: {");  //создание новой строки
    for (int i = 0; i < len; i++) {
        res += std::to_string(arr[i]);                        //преобразование типа данных (в стринг)
        if (i != len - 1)
            res += ", ";
    }
    res += std::string("}");
    return res;
}
