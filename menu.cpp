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

template<class T>
void printArr(myArraySequence<myPolynomial<T>*> *arr) {
    for (int i = 0; i < arr->length(); i++) {
        cout << i << ": " << *arr->get(i) << endl;
    }
    cout << endl;
}

void mainMenu() {
    myArraySequence<myPolynomial<int>*>          arrInt;
    myArraySequence<myPolynomial<float>*>        arrFloat;
    myArraySequence<myPolynomial<complex<int>>*> arrComplex;
    int item;
    while(true) {
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
            cout << "Ошибка! Нет такого пункта! Повторите попытку\n";
            continue;
        }

        if (item == 6)
            break;

        switch (item) {
            case 1: readPolynomial(&arrInt, &arrFloat, &arrComplex); break;
            case 2: operationWithPolynomial(&arrInt, &arrFloat, &arrComplex); break;
            case 3: printPolynomial(&arrInt, &arrFloat, &arrComplex); break;
            case 4: deletePolynomial(&arrInt, &arrFloat, &arrComplex); break;
            case 5: cout << "В разработке...\n"; break;
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

//1
void readPolynomial(myArraySequence<myPolynomial<int>*> *intArr,
                    myArraySequence<myPolynomial<float>*> *floatArr,
                    myArraySequence<myPolynomial<std::complex<int>>*> *complexArr){

    int count = 0;

    cout << "Введите степень многочлена или -1 для выхода\n: ";
    do {
        if (count < 0) {
            cout << "Многочлены отрицательной степени не поддерживаются!\n: ";
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

    cout << "Хотите ввести ещё один многочлен?\n"
            "\t0 - нет\n"
            "\t1 - да\n: ";

    item = getInt(0, 1);
    if (item) {
        readPolynomial(intArr, floatArr, complexArr);
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
    cout << "Введите переменную многочлена (по умолчанию х)\n: ";
    string symbol;
    cin >> symbol;
    cout << "Вы ввели: " << myPolynomial<T>(element).setSymbol(symbol)
         << "\nЗаписать этот многочлен? (1 - да, 0 - повторить попытку ввода, "
         << "другое число приведёт к выходу их функции)\n:";
    int item;
    cin >> item;

    switch (item) {
        default: break;
        case 0: readTypePolynomial<T>(arr, count); break;
        case 1:
            auto *res = new myPolynomial<T>;
            *res = myPolynomial<T>(element);
            res->setSymbol(symbol);
            arr->append(res);
            break;
    }
}

//2
void operationWithPolynomial(myArraySequence<myPolynomial<int>*> *intArr,
                             myArraySequence<myPolynomial<float>*> *floatArr,
                             myArraySequence<myPolynomial<std::complex<int>>*> *complexArr) {
    int type = getType();

    switch (type) {
        default: break;
        case 1: operationTypeWithPolynomial<int>(intArr); break;
        case 2: operationTypeWithPolynomial<float>(floatArr); break;
        case 3: operationTypeWithPolynomial<complex<int>>(complexArr); break;
    }
}

template<class T>
void operationTypeWithPolynomial(myArraySequence<myPolynomial<T>*> *arr) {
    if (arr->length() == 0 ) {
        cout << "Таких многочленов нет!\n";
        return;
    }
    int item;

    while(true) {
        auto len = arr->length();
        cout << "В памяти находится \"" << len << "\" многочленов, введите:\n"
                "\tчисло меньше нуля для выхода\n"
                "\tиндекс многочлена, для его выбора\n"
                "\tчисло, больше чем число элементов, для вывода всем многочленов\n: ";

        item = getInt();
        if (item < 0) break;

        if (item >= len) {
            printArr(arr);
            continue;
        }

        cout << "Вы выбрали: " << *arr->get(item) << endl;

        cout << "Какую операцию необходимо выполнить:\n"
                "\t0: выбрать другой многочлен\n"
                "\t1: сложить многочлены\n"
                "\t2: вычесть многочлены\n"
                "\t3: умножить многочлен на скаляр\n"
                "\t4: умножить многочлены\n"
                "\t5: вычислить значение для данного значения аргумента\n"
                "\t6: выполнить композицию\n: ";

        int item2 = getInt(0, 6);

        if (item2 == 0) continue;

        auto *polynomial1 = arr->get(item);
        myPolynomial<T> *polynomial2, *polynomial3;

        if (item2 == 3 || item2 == 5) {
            T elem;
            cout << "Введите скаляр\n: ";
            cin >> elem;
            if (item2 == 5) {
                cout << "Полученное значение: " << polynomial1->getValue(elem) << endl << endl;
                continue;
            }
            polynomial3 = new myPolynomial<T>;
            *polynomial3 = *polynomial1 * elem;
        }

        else {
            cout << "Введите:\n"
                    "\t-1: для выбора другого многочлена\n"
                    "\t индекс многочлена для выполнения данной операции\n: ";

            int item3 = getInt(-1, len - 1);
            if (item3 == -1) {
                continue;
            }

            polynomial2 = arr->get(item3);
            polynomial3 = new myPolynomial<T>;

            switch(item2) {
                default: break;
                case 1: *polynomial3 = *polynomial1 + *polynomial2; break;
                case 2: *polynomial3 = *polynomial1 - *polynomial2; break;
                case 4: *polynomial3 = *polynomial1 * *polynomial2; break;
                case 6: *polynomial3 = polynomial1->getValue(*polynomial2); break;
            }
        }

        cout << "Был получен: \"" << *polynomial3
             << "\". Запомнить его под индексом \"" << len << "\" ?:\n"
             << "0 - нет\n"
                "1 - да\n: ";

        item = getInt(0, 1);
        if (item == 1) {
            arr->append(polynomial3);
        }
        else {
            delete polynomial3;
        }
    }
}

//3
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
    cout << "В памяти находится \"" << arr->length() << "\" многочленов этого типа\n\n";
    int item;
    do {
        cout << "Введите:\n"
                "\tИндекс элемента для его вывода в консоль\n"
                "\tЧисло, больше чем количество многочленов для вывода всех многочленов "
                "этого типа\n"
                "\tЧисло меньше нуля для выхода из функции\n:";
        item = getInt();

        if (item < 0) break;

        if (item < arr->length()) {
            cout << item << ": " << *arr->get(item) << endl;
        }

        if (item >= arr->length())
            printArr(arr);

        cout << endl;
    } while (item >= 0);
}

//4
void deletePolynomial(myArraySequence<myPolynomial<int>*> *intArr,
                      myArraySequence<myPolynomial<float>*> *floatArr,
                      myArraySequence<myPolynomial<std::complex<int>>*> *complexArr) {

    auto item = getType();
    if (item == 0) return;

    switch (item) {
        case 1: deleteTypePolynomial(intArr); break;
        case 2: deleteTypePolynomial(floatArr); break;
        case 3: deleteTypePolynomial(complexArr); break;
        default: break;
    }
}

template<class T>
void deleteTypePolynomial(myArraySequence<myPolynomial<T>*> *arr) {
    if (arr->length() == 0) {
        cout << "Таких многочленов нет!\n";
        return;
    }
    int item;

    while(true) {
        int len = arr->length();
        if (len == 0) {
            cout << "Больше не осталось многочленов этого типа! Автоматический выход из функции\n";
            break;
        }
        cout << "В памяти находится \"" << len << "\" многочленов, введите:\n"
                "\tЧисло меньше нуля для выхода из функции\n"
                "\tИндекс элемента, для его выбора\n"
                "\tЧисло, больше длины массива, для вывода многочленов в консоль\n: ";

        item = getInt();

        if (item < 0) break;

        if (item >= arr->length()) {
            printArr(arr);
            continue;
        }

        cout << "Выберите операцию:"
                "\t-1: вернуться к выбору индекса\n"
                "\t 0: для удаления элемента\n"
                "\t 1: для перемещения элемента на другое место\n: ";
        int item2 = getInt(-1, 1);

        if (item2 == -1) continue;

        if (item2 == 0) {
            cout << "Вы действительно хотите удалить: " << *arr->get(item) << " ?\n"
                    "0 - нет\n"
                    "1 - да\n: ";
            item2 = getInt(0, 1);
            if (item2 == 1) {
                arr->pop(item);
            }
            continue;
        }

        cout << "Введите номер многочлена, с которым надо поменять \""
             << item << "\" многочлен\n: ";

        item2 = getInt(0, len - 1);
        if (item != item2) {
            myPolynomial<T> *polynomial = arr->get(item);
            arr->set(arr->get(item2), item);
            arr->set(polynomial, item2);
        }
    }
}




















#define funcTemplate(T) \
template void readTypePolynomial(myArraySequence<myPolynomial<T>*> *arr, int count); \
template void printTypePolynomial(myArraySequence<myPolynomial<T>*> *arr);           \
template void printArr(myArraySequence<myPolynomial<T>*> *arr);                      \
template void deleteTypePolynomial(myArraySequence<myPolynomial<T>*> *arr);          \
template void operationTypeWithPolynomial(myArraySequence<myPolynomial<T>*> *arr);

funcTemplate(int)

funcTemplate(float)

funcTemplate(complex<int>)

/*
template void readTypePolynomial<int>(myArraySequence<myPolynomial<int>*> *arr, int count);
template void readTypePolynomial<float>(myArraySequence<myPolynomial<float>*> *arr, int count);
template void readTypePolynomial<complex<int>>(myArraySequence<myPolynomial<complex<int>>*> *arr, int count);

template void printTypePolynomial<int>(myArraySequence<myPolynomial<int>*> *arr);
template void printTypePolynomial<float>(myArraySequence<myPolynomial<float>*> *arr);
template void printTypePolynomial<complex<int>>(myArraySequence<myPolynomial<complex<int>>*> *arr);

template void printArr<int>(myArraySequence<myPolynomial<int>*> *arr);
 */