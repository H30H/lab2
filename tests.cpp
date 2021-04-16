//
// Created by Grisha on 16.04.2021.
//

#include "tests.h"
#include "cstdio"

#define maxSizeDA 100000
#define maxSizeAS 1000

class testFault{
public:
    int done;
    int fault;
    testFault(): done(0), fault(0) {}
    testFault(int done, int fault): done(done), fault(fault) {}
};

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
        std::cout << "\tТест обращения к элементам массива:\n";

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
        std::cout << "\tТест поиска элемента в массива:\n";
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