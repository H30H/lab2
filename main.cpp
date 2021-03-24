
#include "myDynamicArray.cpp"
#include "myLinkedList.cpp"
#include "mySequence.cpp"
#include "myArraySequence.cpp"
/**/
#include "myLinkedList.h"

#include <iostream>
#include <complex>
#include <vector>

using namespace std;

class Test {
public:
    int array[10] = {0};

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
    Test test;

    test.set(10, 5);
    test.print(5);

    test[5] = 15;
    test.print(5);

    cout << test[5] << endl;

    return 0;
}
