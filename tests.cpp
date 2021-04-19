//
// Created by Grisha on 16.04.2021.
//

#include "tests.h"

#define maxSizeDA 100000
#define maxSizeAS 1000
#define maxSizeLL 2000
#define maxSizeLS 2000

void printDone(int count, int done, int print) {
    if (print)
        if (done == count)
            std::cout << "\tТест пройден (\"" << count << "\" итераций).\n\n";
        else
            std::cout << "\tТест не пройден (провалено \"" << count - done << "\", пройдено \"" << done << "\" тестов).\n\n";
    else if (done != count)
        throw testFault(done, count - done);

}

int getLen(int max) {
    int len;
    do {
        len = rand()%max;
    } while (len == 0);
    return len;
}

int getIndex(int max){
    if (max == 0) return 0;
    return rand()%max;
}

void dynamicArrTest(int count, int print) {
    srand(count);
    if (print)
        std::cout << "Тестирование динамического массива:\n";
    dynamicArrTestResize(count, print);
    dynamicArrTestGetItem(count, print);
    dynamicArrTestReverse(count, print);
    dynamicArrTestFind(count, print);
}

void dynamicArrTestResize(int count, int print) {
    int done = 0;
    if (print)
        std::cout <<"\tТест изменения размера массива:\n";

    for (int i = 0; i < count; i++) {
        myDynamicArray<int> array;
        int len = getLen(maxSizeDA);
        array.resize(len);
        if (array.length() == len) {
            done++;
        }
    }

    printDone(count, done, print);
}

void dynamicArrTestGetItem(int count, int print) {
    int done = 0;
    int actions = 10;
    if (print)
        std::cout << "\tТест чтение элементов массива:\n";

    for (int i = 0; i < count; i+=actions) {
        myDynamicArray<int> array;
        int len = getLen(maxSizeDA);
        array.resize(len);
        for (int j = 0; j < actions; j++) {
            if (i + j >= count) break;
            int index = getIndex(maxSizeDA);
            try {
                array[index];
                if (index < len)
                    done++;
            }
            catch (myDynamicArray<int>::IndexOutOfRange err) {
                if (index >= len)
                    done++;
            }
        }
    }

    printDone(count, done, print);
}

void dynamicArrTestReverse(int count, int print) {
    int done = 0;
    int maxElement = 100000;
    if (print) std::cout << "\tТест разворота массива:\n";
    for (int i = 0; i < count; i++) {
        myDynamicArray<int> array;
        int len = getLen(maxSizeDA);
        array.resize(len);
        for (int j = 0; j < len; j++) {
            array[j] = rand();
        }
        auto arrayNew = array;
        arrayNew.reverse();
        int ok = 1;
        for (int j = 0; j < len; j++) {
            if (array[j] != arrayNew[len - 1 - j]) {
                ok = 0;
                break;
            }
        }
        done += ok;
    }

    printDone(count, done, print);
}

void dynamicArrTestFind(int count, int print) {
    int done = 0;
    if (print)
        std::cout << "\tТест поиска элементов в массива:\n";
    for (int i = 0; i < count; i++) {
        myDynamicArray<int> array;
        int len = getLen(maxSizeDA);
        array.resize(len);
        for (int j = 0; j < len; j++) {
            array[j] = j;
        }
        int index = getIndex(len);
        if (index == array.find(index))
            done++;
    }

    printDone(count, done, print);
}


void myArraySequenceTest(int count, int print) {
    srand(count);
    if (print)
        std::cout << "Тестирование последовательности массива:\n";
    myArraySequenceTestResize(count, print);
    myArraySequenceTestGetItem(count, print);
    myArraySequenceTestReverse(count, print);
    myArraySequenceTestFind(count, print);
}

void myArraySequenceTestResize(int count, int print) {
    int done = 0;
    if (print)
        std::cout << "\tТестирование изменения размера последовательности:\n";
    for (int j = 0; j < count; j++) {
        myArraySequence<int> sequence;
        int len = getLen(maxSizeAS / 3);
        for (int i = 0; i < len; i++) {
            sequence.append(i);
        }
        if (sequence.length() != len)
            continue;

        for (int i = 0; i < len; i++) {
            sequence.prepend(i);
        }

        if (sequence.length() != len*2)
            continue;

        for (int i = 0; i < len; i++) {
            sequence.insert(i, getIndex(sequence.length()));
        }

        if (sequence.length() != len*3)
            continue;

        for (int i = 0; i < len*3; i++) {
            sequence.pop();
        }

        if (sequence.length() != 0)
            continue;

        done++;
    }

    printDone(count, done, print);
}

void myArraySequenceTestGetItem(int count, int print) {
    int done = 0;
    int actions = 100;
    if (print)
        std::cout << "\tТестирование чтения элеметов последовательности\n";
    for (int i = 0; i < count; i+=actions) {
        myArraySequence<int> sequence;
        int len = getLen(maxSizeAS);
        for (int j = 0; j < len; j++) {
            sequence.append(j);
        }
        for (int j = 0; j < actions; j++) {
            if (i + j >= count) break;
            int index = getIndex(maxSizeAS);
            try {
                if (sequence[index] == index)
                    done++;
            }
            catch (myArraySequence<int>::IndexOutOfRange err) {
                if (index >= len)
                    done++;
            }
        }
    }

    printDone(count, done, print);
}

void myArraySequenceTestReverse(int count, int print) {
    int done = 0;
    if (print)
        std::cout << "\tТестирование разворота последовательности:\n";
    for (int i = 0; i < count; i++) {
        myArraySequence<int> sequence;
        int len = getLen(maxSizeAS);
        for (int j = 0; j < len; j++) {
            sequence.append(j);
        }
        auto sequenceRev = sequence;
        sequenceRev.reverse();
        int res = 1;
        for (int j = 0; j < len; j++) {
            if (sequence[j] != sequenceRev[len - j - 1]) {
                res = 0;
                break;
            }
        }
        done += res;
    }

    printDone(count, done, print);
}

void myArraySequenceTestFind(int count, int print) {
    int done = 0;
    int actions = 10;
    if (print)
        std::cout << "\tТестирование поиска элементов в последовательности:\n";
    for (int i = 0; i < count; i+=actions) {
        myArraySequence<int> sequence;
        int len = getLen(maxSizeAS);
        for (int j = 0; j < len; j++) {
            sequence.append(j);
        }
        for (int j = 0; j < actions; j++) {
            if (i + j >= count) break;
            int index = getIndex(len);
            if (sequence.find(index) == index)
                done++;
        }
    }

    printDone(count, done, print);
}

void myLinkedListTest(int count, int print) {
    srand(count);
    if (print)
        std::cout << "Тестирование связного списка:\n";
    myLinkedListTestResize(count, print);
    myLinkedListTestGetItem(count, print);
    myLinkedListTestReverse(count, print);
    myLinkedListTestFind(count, print);
}

void myLinkedListTestResize(int count, int print) {
    int done = 0;
    if (print)
        std::cout << "\tТестирование изменения размера списка:\n";
    for (int i = 0; i < count; i++) {
        myLinkedList<int> linkedList;
        int len = getLen(maxSizeLL / 3);
        for (int j = 0; j < len; j++) {
            linkedList.append(j);
        }
        if (linkedList.length() != len)
            continue;

        for (int j = 0; j < len; j++) {
            linkedList.prepend(j);
        }
        if (linkedList.length() != len * 2)
            continue;

        for (int j = 0; j < len; j++) {
            linkedList.insert(j, getIndex(linkedList.length()));
        }
        if (linkedList.length() != len * 3)
            continue;

        for (int j = 0; j < len * 3; j++) {
            linkedList.pop();
        }
        if (linkedList.length() != 0)
            continue;

        done++;
    }

    printDone(count, done, print);
}

void myLinkedListTestGetItem(int count, int print) {
    int done = 0;
    int actions = 10;
    if (print)
        std::cout << "\tТестирование чтения элементов списка:\n";
    for (int i = 0; i < count; i++) {
        myLinkedList<int> linkedList;
        int len = getLen(maxSizeLL);
        for (int j = 0; j < len; j++) {
            linkedList.append(j);
        }
        int Done = 0;
        for (int j = 0; j < actions; j++) {
            //if (j + i >= count) break;
            int index = getIndex(len);
            if (linkedList[index] == index)
                Done++;
        }
        done += Done == actions;
    }

    printDone(count, done, print);
}

void myLinkedListTestReverse(int count, int print) {
    int done = 0;
    if (print)
        std::cout << "\tТестирование разворота списка:\n";
    for (int i = 0; i < count; i++) {
        myLinkedList<int> linkedList;
        int len = getLen(maxSizeLL);
        for (int j = 0; j < len; j++) {
            linkedList.append(j);
        }
        myLinkedList<int> reverse = linkedList;
        reverse.reverse();
        int same = 1;
        for (int j = 0, k = len - 1; j < len; j++, k--) {
            if (linkedList[k] != reverse[j]) {
                same = 0;
                break;
            }
        }
        done += same;
    }

    printDone(count, done, print);
}

void myLinkedListTestFind(int count, int print) {
    int done = 0;
    int actions = 10;
    if (print)
        std::cout << "\tТестирование поиска элементов в списке\n";
    for (int i = 0; i < count; i++) {
        myLinkedList<int> linkedList;
        int len = getLen(maxSizeLL);
        for (int j = 0; j < len; j++) {
            linkedList.append(j);
        }

        int Done = 0;
        for (int j = 0; j < actions; j++) {
            int index = getIndex(len);
            int k = linkedList.find(index);
            if (k == index)
                Done++;
        }
        done += Done == actions;
    }

    printDone(count, done, print);
}

void myListSequenceTest(int count, int print) {
    if (print)
        std::cout << "Тестирование последовательности связного списка\n";
    myListSequenceTestResize(count, print);
    myListSequenceTestGetItem(count, print);
    myListSequenceTestReverse(count, print);
    myListSequenceTestFind(count, print);
}

void myListSequenceTestResize(int count, int print) {
    int done = 0;
    if (print)
        std::cout << "\tТестирование изменения размера последовательности:\n";
    for (int i = 0; i < count; i++) {
        myListSequence<int> listSequence;
        int len = getLen(maxSizeLS/3);
        for (int j = 0; j < len; j++) {
            listSequence.append(j);
        }
        if (listSequence.length() != len) continue;

        for (int j = 0; j < len; j++) {
            listSequence.prepend(j);
        }
        if (listSequence.length() != len * 2) continue;

        for (int j = 0; j < len; j++) {
            listSequence.insert(j, getIndex(listSequence.length()));
        }
        if (listSequence.length() != len * 3) continue;

        done++;
    }

    printDone(count, done, print);
}

void myListSequenceTestGetItem(int count, int print) {
    int done = 0;
    int actions = 10;
    if (print)
        std::cout << "\nТестирование чтения элементов последовательности:\n";
    for (int i = 0; i < count; i+=actions) {
        myListSequence<int> listSequence;
        int len = getLen(maxSizeLS);
        for (int j = 0; j < len; j++) {
            listSequence.append(j);
        }
        for (int j = 0; j < actions; j++) {
            int index = getIndex(len);
            if (listSequence[index] == index)
                done++;
        }
    }

    printDone(count, done, print);
}

void myListSequenceTestReverse(int count, int print) {
    int done = 0;
    if (print)
        std::cout << "\tТестирование разворота последовательности:\n";
    for (int i = 0; i < count; i++) {
        myListSequence<int> listSequence;
        int len = getLen(maxSizeLS);
        for (int j = 0; j < len; j++) {
            listSequence.append(j);
        }
        auto res = listSequence;
        res.reverse();
        int Done = 1;
        for (int j = 0, k = len - 1; j < len; j++, k--) {
            if (res[j] != listSequence[k]) {
                Done = 0;
                break;
            }
        }
        done += Done;
    }

    printDone(count, done, print);
}

void myListSequenceTestFind(int count, int print) {
    int done = 0;
    int actions = 10;
    if (print)
        std::cout << "\tТестирование поиска элементов в последовательности:\n";
    for (int i = 0; i < count; i++) {
        myListSequence<int> listSequence;
        int len = getLen(maxSizeLS);
        for (int j = 0; j < len; j++) {
            listSequence.append(j);
        }

        int Done = 0;
        for (int j = 0; j < actions; j++) {
            int index = getIndex(len);
            if (listSequence.find(index) == index)
                Done++;
        }
        done += Done == actions;
    }

    printDone(count, done, print);
}


void myPolynomialTest(int count, int print) {
    if (print)
        std::cout << "Тестирование многочленов:\n";
    myPolynomialTestSum(count, print);
    myPolynomialTestSub(count, print);
    myPolynomialTestMult(count, print);
    myPolynomialTestScalar(count, print);
    myPolynomialTestPow(count, print);
}

void myPolynomialTestSum(int count, int print) {}
void myPolynomialTestSub(int count, int print) {}
void myPolynomialTestMult(int count, int print) {}
void myPolynomialTestScalar(int count, int print) {}
void myPolynomialTestPow(int count, int print) {}