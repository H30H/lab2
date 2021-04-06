
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


    myDynamicArray<int> k7;
    myDynamicArray<float> k8;
    myDynamicArray<myDynamicArray<myDynamicArray<char>>> k9;

    vector<int> v1, v2;

    myArraySequence<int> k1;
    myArraySequence<int> k2;
    v1.resize(10); v2.resize(10);
    for (int i = 0; i < 6; i++) {
        k1.append(i);
        k2.append(i*2);
        v1[i] = i;
        v2[i] = 2*i;
    }

    myPolynomial<int> pol1(k1);
    myPolynomial<int> pol2(k2);
    cout << pol1 << " " << k1 << endl;
    cout << pol2 << " " << k2 << endl << endl;
    cout << pol1 + pol2 << endl;

    cout << endl << pol1.map(pol2.get, myFunc) << endl;
}
