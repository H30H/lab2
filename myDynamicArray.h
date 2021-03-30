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
    T *arr;
    int len;
    int size;
    const size_t elSize = sizeof(T);
public:
    class IndexOutOfRange{};

    //std::string getStr();

    friend std::string to_string(myDynamicArray<T> &dynamicArray) {
        std::string res = "{";

        for (int i = 0; i < dynamicArray.len; i++) {
            res += std::to_string(dynamicArray[i]);
            if (i < dynamicArray.len - 1) {
                res += ", ";
            }
        }
        res += "}";
        return res;
    }

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

    myDynamicArray(T *items, int count);

    explicit myDynamicArray(int size);

    myDynamicArray();

    myDynamicArray(myDynamicArray<T> const &dynamicArray);

    ~myDynamicArray();

    int length();

    T get(int index);

    int getSize() {
        return size;
    }

    T &operator [] (int index);

    myDynamicArray<T> &operator = (myDynamicArray<T> dynamicArray) {
        resize(dynamicArray.len);
        for (int i = 0; i < len; i++) {
            arr[i] = dynamicArray.arr[i];
        }
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

    void set(T item, int index);                        //изменяет массив

    myDynamicArray<T> set_(T item, int index);          //создаёт новый массив

    void resize(int newSize);                           //изменяет массив

    myDynamicArray<T> resize_(int newSize);             //создаёт новый массив

    myDynamicArray<myDynamicArray<T>> split(T item) {
        myDynamicArray<int> indexes;

        for (int i = 0; i < len; i++) {
            if (arr[i] == item) {
                indexes.resize(indexes.length() + 1);
                indexes[indexes.length() - 1] = i;
            }
        }
        indexes.resize(indexes.length() + 1);
        indexes[indexes.length() - 1] = len;

        myDynamicArray<myDynamicArray<T>> res(indexes.length());
        for(int i = 0; i < indexes.length(); res[i] = myDynamicArray<T>(), i++);

        int index = 0;
        myDynamicArray<T> element;
        element.resize(indexes[index]);

        for (int i = 0, j = 0; i < len; i++, j++) {
            if (i == indexes[index]) {
                res[index] = element;
                element.resize(indexes[index + 1] - indexes[index] - 1);
                index++;
                j = -1;
                continue;
            }
            element[j] = arr[i];
        }
        return res;
    }
};




#endif //LAB2_MYDYNAMICARRAY_H