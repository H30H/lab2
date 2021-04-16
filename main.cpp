
#include "myDynamicArray.cpp"
#include "myLinkedList.cpp"
#include "mySequence.cpp"
#include "myArraySequence.cpp"
#include "myPolynomial.h"
/**/
#include "myLinkedList.h"
#include "myDynamicArray.h"

#include <iostream>
#include "menu.h"
#include "tests.h"

using namespace std;
int sum(int k1, int k2) {
    return k1 + k2;
}

int sum1(myArraySequence<int> arr) {
    return arr.reduce(sum);
}

int main() {
    //mainMenu();

    int arr1[] = {1, 2, 3, 4};
    int arr2[] = {5, 6, 7, 8, 9, 10};

    myArraySequence<int> Arr1(arr1, 4);
    myArraySequence<int> Arr2(arr2, 6);

    //dynamicArrTest(10000, 1);
    myArraySequenceTest(10000, 1);
    /*
    auto Arr3 = Arr1.zip(&Arr2);
    cout << Arr1 << endl << Arr2 << endl << Arr3 << endl;
//    auto arr4 = Arr3->unzip(Arr3);
//    cout << arr4 << endl;
    auto summ {
        [](myDynamicArray<int> array) {
            return array.reduce(sum);
        }
    };
    auto arr5 = Arr3->map(sum1);
    cout << arr5 << endl;
    cin >> k;*/
    /*
    myPolynomial<int> pol1(Arr1);
    myPolynomial<int> pol2(Arr2);

    cout << pol1 << endl << pol2 << endl;
    cout << pol1 + pol2 << endl;
    cout << pol1 - pol2 << endl;
    cout << pol1 * pol2 << endl;
    cout << pol1 * 5 << endl;
    //auto *g =
    cout << *pol1.changeDegree_(2) << " pol\n";
    cout << pol1 << " pol\n";
    cout << *pol1.changeDegree_(-2) << " pol\n";
    cout << pol1 << " pol\n";
    cout << *pol1.changeDegree_(-2) << " pol\n";
    /**/
    return 0;
}
