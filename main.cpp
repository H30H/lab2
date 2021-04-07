
#include "myDynamicArray.cpp"
#include "myLinkedList.cpp"
#include "mySequence.cpp"
#include "myArraySequence.cpp"
#include "myPolynomial.h"
/**/
#include "myLinkedList.h"
#include "myDynamicArray.h"

#include <iostream>
#include <complex>
#include <vector>

using namespace std;

template<class T>
class Test {
private:
    T *arr = nullptr;
    int len = 0;
public:
    Test(): arr(nullptr), len(0) {};

    Test(T *array, int length) {
        len = length;
        arr = new T[len];

        memcpy(arr, array, len*sizeof(T));
    }

    Test(const Test<T> &test) {
        len = test.len;
        arr = new T[len];
        memcpy(arr, test.arr, len*sizeof(T));
    }

    ~Test() {
        delete[] arr;
    }

    Test<T> operator + (Test<T>& test) {
        Test<T> res;
        res.arr = new T[len + test.len];
        res.len = len + test.len;
        memcpy(res.arr, arr, len * sizeof(T));
        memcpy(res.arr + len, test.arr, test.len * sizeof(T));
        cout << "res" << " " << res << endl;
        return res;
    }

    friend ostream &operator << (ostream& cout, Test<T> test) {
        cout << '{';
        for (int i = 0; i < test.len; i++) {
            cout << test.arr[i];
            if (i < test.len - 1) {
                cout << ", ";
            }
        }
        return cout << "}";
    }
};

void swap(int *x1, int *x2) {
    int t = *x1;
    *x1 = *x2;
    *x2 = t;
}

void swap2(int &x1, int &x2) {
    int t = x1;
    x1 = x2;
    x2 = t;
}

int myFunc(int val1, int val2) {
    return val1*5 + val2;
}

int main() {
    /*
    int arr1[] = {1, 2, 3, 4, 5};
    int arr2[] = {1, 2, 3, 4, 5};

    Test<int> k1(arr1, 5);
    Test<int> k2(arr2, 5);

    cout << k1 << endl;
    cout << k2 << endl;

    cout << k1 + k2 << endl;

    /*
    swap(arr+1, arr+2);

    cout << arr[1] << " " << arr[2] << endl;

    swap2(arr[1], arr[2]);

    cout << arr[1] << " " << arr[2] << endl;

    myDynamicArray<int> k1(arr, 5);

    k1[3] = 7;
     */

    myDynamicArray<int> k1(20);
    for (int i = 0; i < 20; i++) {
        k1[i] = i % 10;
    }

    myDynamicArray<myDynamicArray<int>*> k2;
    k2.resize(1);
    k2[0] = &k1;

    cout << k1 << endl;
    cout << &k1 << endl;
    cout << k2 << endl;
    cout << k1.split(5) << endl;

    /*
    myLinkedList<int> list;
    cout << list << endl;
    for(int i = 0; i < 10; i++) {
        cout << i << endl;
        list.append(i);
    }

    cout << list << endl;
    cout << list[0] << ' ' << list[1] << endl;
    cout << list.get(0) << ' ' << list.get(1) << endl;
    /*
    for (auto &i: myLinkedList<int>::Iterator(list)) {
        cout << i << " ";
    } /**/
}
