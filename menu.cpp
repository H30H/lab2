//
// Created by Grisha on 12.04.2021.
//

#include "menu.h"
#include "myDynamicArray.cpp"

using namespace std;

int getInt() {
    int k;
    cin >> k;
    return k;
}

int getInt(int up) {
    int k;
    cin >> k;
    if (k > up) {
        cout << "Число вне диапозона. Повторите попытку\n";
        return getInt(up);
    }
    return k;
}

int getInt(int down, int up) {
    int k;
    cin >> k;
    if (k > up || k < down) {
        cout << "Число вне диапозона. Повторите попытку\n";
        return getInt(down, up);
    }
    return k;
}

void mainMenu() {
    myArraySequence<myPolynomial<int>*>          arrInt;
    myArraySequence<myPolynomial<float>*>        arrFloat;
    myArraySequence<myPolynomial<complex<int>>*> arrComplex;
    int item;
    while(1) {
        cout << "Программа имеет следующие возможности: \n"
             << "\t1: Ввести и запомнить многочлен\n"
             << "\t2: Выполнить операцию над многочленами\n"
             << "\t3: Вывести многочлен в консоль\n"
             << "\t4: Удалить или переместить многочлен в памяти\n"
             << "\t5: Запустить функцию тестирования многочленов\n"
             << "\t6: Закончить выполнение программы\n"
             << "Введите число: ";
        cin >> item;
        if (item < 1 || item > 6) {
            cout << "Ошибка! Нет такого пункта!\n";
            continue;
        }

        if (item == 6)
            break;

        switch (item) {
            case 1:
                readPolynomial(&arrInt, &arrFloat, &arrComplex);
                break;
            case 2: break;
            case 3:
                printPolynomial(&arrInt, &arrFloat, &arrComplex);
                break;
            case 4: break;
            case 5: break;
            default: break;
        }
    }

    for (auto &i : arrInt) {
        delete i;
    }

    for (auto &i : arrFloat) {
        delete i;
    }

    for (auto &i : arrComplex) {
        delete i;
    }
}

int getType() {
    cout << "Введите число для работы со следующим типом данных: \n"
         << "\t1: int\n"
         << "\t2: float\n"
         << "\t3: complex<int>\n"
         << "\t0: Выйти из функции\n"
         << ": ";
    int item;
    return getInt(0, 3);
}

void readPolynomial(myArraySequence<myPolynomial<int>*> *intArr,
                    myArraySequence<myPolynomial<float>*> *floatArr,
                    myArraySequence<myPolynomial<std::complex<int>>*> *complexArr){

    int count = 0;

    cout << "Введите степень многочлена или -1 для выхода\n:";
    do {
        if (count < 0) {
            cout << "Многочлены отрицательной степени не поддерживаются\n";
        }
        cin >> count;

        if (count == -1)
            return;
    } while(count < 0);

    auto item = getType();
    if (item == 0) return;

    switch (item) {
        case 1: readTypePolynomial<int>(intArr, count); break;
        case 2: readTypePolynomial<float>(floatArr, count); break;
        case 3: readTypePolynomial<complex<int>>(complexArr, count); break;
        default: break;
    }
}

template<class T>
void readTypePolynomial(myArraySequence<myPolynomial<T>*> *arr, int count) {
    cout << "Введите коэффициенты многочлена от старшей степени к младшей\n:";
    myArraySequence<T> element;
    for (int i = 0; i <= count; i++) {
        T item;
        cin >> item;
        element.append(item);
    }
    element.reverse();
    cout << "Введите переменную многочлена (по умолчанию х): ";
    string symbol;
    cin >> symbol;
    cout << "Вы ввели: " << myPolynomial<T>(element).setSymbol(symbol)
         << "\nЗаписать этот многочлен? (1 - да, 0 - повторить попытку ввода, "
         << "другое число приведёт к выходу их функции)";
    int item;
    cin >> item;

    switch (item) {
        default: break;
        case 0: readTypePolynomial<T>(arr, count); break;
        case 1:
            auto *res = new myPolynomial<T>;
            *res = myPolynomial<T>(element);
            arr->append(res);
            break;
    }
}


void printPolynomial(myArraySequence<myPolynomial<int>*> *intArr,
                     myArraySequence<myPolynomial<float>*> *floatArr,
                     myArraySequence<myPolynomial<std::complex<int>>*> *complexArr) {
    int type = getType();

    switch (type) {
        default: break;
        case 1:
            printTypePolynomial<int>(intArr);
            break;
        case 2:
            printTypePolynomial<float>(floatArr);
            break;
        case 3:
            printTypePolynomial<complex<int>>(complexArr);
            break;
    }
}


template<class T>
void printTypePolynomial(myArraySequence<myPolynomial<T>*> *arr) {
    cout << "Всего " << arr->length() << "многочленов этого типа\n\n";
    int item;
    do {
        cout << "Введите:"
                "\tИндекс элемента для его вывода в консоль\n"
                "\tЧисло, больше чем количество многочленов для вывода всех многочленов "
                "того типа\n"
                "\tЧисло меньше нуля для выхода из функции\n:";
        item = getInt();

        if (item < 0) break;

        if (item < arr->length()) {
            cout << item << ": " << *arr->get(item) << endl;
        }

        if (item >= arr->length())
            for (int i = 0; i < arr->length(); i++) {
                cout << i << ": " << *arr->get(i) << endl;
            }

        cout << endl;
    } while (item >= 0);
}






















template void readTypePolynomial<int>(myArraySequence<myPolynomial<int>*> *arr, int count);
template void readTypePolynomial<float>(myArraySequence<myPolynomial<float>*> *arr, int count);
template void readTypePolynomial<complex<int>>(myArraySequence<myPolynomial<complex<int>>*> *arr, int count);

template void printTypePolynomial<int>(myArraySequence<myPolynomial<int>*> *arr);
template void printTypePolynomial<float>(myArraySequence<myPolynomial<float>*> *arr);
template void printTypePolynomial<complex<int>>(myArraySequence<myPolynomial<complex<int>>*> *arr);