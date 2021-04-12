//
// Created by Grisha on 12.04.2021.
//

#ifndef LAB2_MENU_H
#define LAB2_MENU_H

#include <complex>
#include "myPolynomial.h"
#include <iostream>

void mainMenu();
int getType();

void readPolynomial(myArraySequence<myPolynomial<int>*> *intArr,
                    myArraySequence<myPolynomial<float>*> *floatArr,
                    myArraySequence<myPolynomial<std::complex<int>>*> *complexArr);

template<class T>
void readTypePolynomial(myArraySequence<myPolynomial<T>*> *arr, int count);

void printPolynomial(myArraySequence<myPolynomial<int>*> *intArr,
                     myArraySequence<myPolynomial<float>*> *floatArr,
                     myArraySequence<myPolynomial<std::complex<int>>*> *complexArr);

template<class T>
void printTypePolynomial(myArraySequence<myPolynomial<T>*> *arr);



#endif //LAB2_MENU_H
