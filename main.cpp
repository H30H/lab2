
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
#include "menu.h"
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

int main() {/*
    myArraySequence<int> sequence1;
    for (int i = 0; i < 3; i++) {
        sequence1.append(i);
    }
    myPolynomial<int> polynomial1(sequence1);
    sequence1.append(11);
    sequence1.append(12);
    myPolynomial<int> polynomial2(sequence1);
    cout << polynomial1 << endl << polynomial2 << endl << endl;
    cout << polynomial1 + polynomial2 << endl << endl;
    cout << polynomial1 << endl << polynomial2 << endl << endl;
    cout << polynomial1 - polynomial2 << endl;

    cout << polynomial1 * polynomial2 << endl;
    cout << polynomial1 << endl << polynomial2 << endl << endl;
    cout << polynomial1(polynomial2) << endl;
    */
    mainMenu();
}
