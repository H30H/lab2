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
    T *arr;                           //массив элементов, с которыми работает пользователь
    int len;                          //длина массива (количество элементов, достуных пользователю)
    int size;                         //количество элементов, под которые выделена память
    int sizeOfBlock;                  //TODO количество элементов, на которое нужно увеличить массив в resize(int)
    const size_t elSize = sizeof(T);
public:
    class IndexOutOfRange{
    public:
        int length;
        int index;
        IndexOutOfRange(int length, int index): length(length), index(index) {};
        IndexOutOfRange(): length(-1), index(-1) {};
    };

    friend std::ostream &operator << (std::ostream &cout, myDynamicArray<T> &dynamicArray) {
        //cout << dynamicArray.length() << ' ';
        cout << '{';
        for (int i = 0; i < dynamicArray.length(); i++) {
            cout << dynamicArray[i];
            if (i < dynamicArray.length() - 1) {
                cout << ", ";
            }
        }
        return cout << '}';
    }

    friend std::ostream &operator << (std::ostream &cout, myDynamicArray<T> *dynamicArray) {
        return cout << dynamicArray[0];
        /*
        cout << '{';
        for (int i = 0; i < dynamicArray->length(); i++) {
            cout << dynamicArray[0][i];
            if (i != dynamicArray->length() - 1)
                cout << ", ";
        }
        return cout << '}';/**/
    }

    myDynamicArray(T *items, int count);

    explicit myDynamicArray(int size);

    myDynamicArray();

    myDynamicArray(myDynamicArray<T> const &dynamicArray);

    explicit myDynamicArray(myDynamicArray<T> *dynamicArray);

    ~myDynamicArray();

    int length();

    T get(int index);

    int getSize() {
        return size;
    }

    void reverse() {
        for (auto i = 0; i < len / 2; i++) {
            int index = len - 1 - i;
            T item = arr[i];
            arr[i] = arr[index];
            arr[index] = item;
        }
    }

    T &operator [] (int index);

    myDynamicArray<T> &operator = (myDynamicArray<T> dynamicArray) {
        resize(dynamicArray.len);
        for (int i = 0; i < len; i++) {
            arr[i] = dynamicArray.arr[i];
        }
        return *this;
    }

    myDynamicArray<T> &operator = (myDynamicArray<T> *dynamicArray) {
        arr = dynamicArray->arr;
        len = dynamicArray->len;
        size = dynamicArray->size;

        return *this;
    }

    myDynamicArray<T> &operator* () {
        return *this;
    }

    int operator == (myDynamicArray<T> dynamicArray) {
        if (len != dynamicArray.length()) return 0;

        for (int i = 0; i < len; i++) {
            if (arr[i] != dynamicArray.arr[i])
                return 0;
        }
        return 1;
    }

    T *begin() const;

    T *end() const;

    void set(T item, int index);

    void resize(int newSize);

    myDynamicArray<myDynamicArray<T>*> *split(T item) {
        myDynamicArray<int> indexes;

        for (int i = 0; i < len; i++) {
            if (arr[i] == item) {
                indexes.resize(indexes.length() + 1);
                indexes[indexes.length() - 1] = i;
            }
        }

        indexes.resize(indexes.length() + 1);
        indexes[indexes.length() - 1] = len;

        auto res = new myDynamicArray<myDynamicArray<T>*>;

        res->resize(indexes.length());

        int index = 0;
        auto *element = new myDynamicArray<T>;
        element->resize(indexes[index]);

        for (int i = 0, j = 0; i < len; i++, j++) {
            if (i == indexes[index]) {
                res[0][index] = element;
                element = new myDynamicArray<T>;
                index++;
                element->resize(indexes[index] - indexes[index - 1] - 1);
                j = -1;
                continue;
            }
            element[0][j] = arr[i];
        }
        res[0][index] = element;
        return res;
    }
    int k123 = 0;
};


#endif //LAB2_MYDYNAMICARRAY_H