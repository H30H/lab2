#include "myDynamicArray.cpp"
#include "myLinkedList.cpp"
#include "mySequence.cpp"
#include "myArraySequence.cpp"


#include <iostream>
#include <complex>
#include <vector>

using namespace std;

int main() {
    int count = 7;
    auto linkedList = myLinkedList<int>();
    for (int i = 0; i < count; i++) {
        int k;
        cin >> k;
        linkedList.append(k);
    }
    cout << linkedList << endl;
    cout << linkedList.getFirst() << " " << linkedList.getLast() << endl;
    cout << linkedList.length() << " " << linkedList.pop(2) << " " << linkedList.length() << endl;
    linkedList.prepend(3);
    cout << linkedList << endl;
    return 0;
}
