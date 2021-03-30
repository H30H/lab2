
#include "myDynamicArray.cpp"
#include "myLinkedList.cpp"
#include "mySequence.cpp"
#include "myArraySequence.cpp"
/**/
#include "myLinkedList.h"
#include "myDynamicArray.h"

#include <iostream>
#include <complex>
#include <vector>
#include <stdlib.h>

using namespace std;

class Test {
public:
    int array[10] = {0};

    class IndexOutOfRange{};

    class IndexOutOfRange2{};

    ~Test() {
        cout << "Delete" << endl;
    }

    void ttest() {
        throw IndexOutOfRange();
    }
    void ttest2() {
        throw IndexOutOfRange2();
    }
    int get(int index) {
        return array[index];
    }

    void set(int item, int index) {
        array[index] = item;
    }

    void print(int index) {
        cout << array[index] << endl;
    }

    int &operator [] (int index) {
        return array[index];
    }
};

int main() {
    int arr[]{1, 2, 3, 4, 5, 3, 1, 2, 3, 4, 5, 3};
    int arr2[]{4, 5};

    myArraySequence<int> arraySequence(arr, 12);
    myArraySequence<int> arraySequence2(arr2, 2);

    auto res = arraySequence.split(3);

    cout << res << " " << arraySequence << endl;

    auto res2 = res.split(arraySequence2);

    cout << res2 << endl;
}
