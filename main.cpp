#include <iostream>
#include <complex>
#include <vector>
#include "myDynamicArray.cpp"

using namespace std;

int main() {
    int count = 5;
    myDynamicArray<int> array = myDynamicArray<int>(count);
    for (int i = 0; i < count; i++) {
        int k = 0;
        cin >> k;
        array.set(i, k);
    }
    cout << array.getStr() << endl;
    int a[] = {1, 3, 5, 7, 9};
    cout << myDynamicArray<int>(a, sizeof(a) / sizeof(int)) << endl;
    cout << myDynamicArray<int>(array) << endl;
    cout << array << endl;
    cout << myDynamicArray<int>(-100) << endl;
    return 0;
}
