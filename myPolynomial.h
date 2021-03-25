//
// Created by Grisha on 24.03.2021.
//

#ifndef LAB2_MYPOLYNOMIAL_H
#define LAB2_MYPOLYNOMIAL_H

#include <iostream>
#include "myArraySequence.h"
#include "myListSequence.h"

template<class T>
class myPolynomial {
private:
    mySequence<T> elements;
public:
    myPolynomial(mySequence<T> sequence) : elements(sequence) {};

    myPolynomial(myLinkedList<T> linkedList) : elements(myListSequence<T>(linkedList)) {};

    myPolynomial(myArraySequence<T> arraySequence) : elements(myArraySequence<T>(arraySequence)) {};

    myPolynomial(T item) : elements(myArraySequence<T>(item)) {};

    myPolynomial() : elements(myArraySequence<T>()) {};

    myPolynomial(myPolynomial<T> &polynomial) : elements(polynomial.elements) {};

    T &operator[](int index) {
        return elements[index];
    }

    void add(myPolynomial<T> polynomial) {
        for (int i = 0; i < polynomial.elements.length() && i < elements.length(); i++) {
            elements[i] += polynomial[i];
        }

        for (int i = elements.length(); i < polynomial.elements.length(); i++) {
            elements.append(polynomial[i]);
        }
    }

    myPolynomial<T> add_(myPolynomial<T> polynomial) {
        return myPolynomial<T>(this).add(polynomial);
    }

    myPolynomial<T> operator+(myPolynomial<T> polynomial1) {
        return myPolynomial<T>(this).add(polynomial1);
    }

    myPolynomial<T> operator+() {
        return myPolynomial<T>(this);
    }

    void sub(myPolynomial<T> polynomial) {
        for (int i = 0; i < polynomial.elements.length() && i < elements.length(); i++) {
            elements[i] = -polynomial[i];
        }

        for (int i = elements.length(); i < polynomial.elements.length(); i++) {
            elements.append(0 - polynomial[i]);
        }
    }

    myPolynomial<T> sub_(myPolynomial<T> polynomial) {
        return myPolynomial<T>(this).sub(polynomial);
    }

    myPolynomial<T> operator-(myPolynomial<T> polynomial1) {
        return myPolynomial<T>(this).sub(polynomial1);
    }

    myPolynomial<T> operator-() {
        return myPolynomial<T>(myArraySequence<T>()).sub(this);
    }

    void mult(myPolynomial<T> polynomial) {
        auto result = myPolynomial<T>();
        for (int i = 0; i < elements.length(); i++) {
            for (int j = 0; j < polynomial.elements.length(); j++) {
                T elem = elements[i] * polynomial.elements[j];
                int index = i + j;
                if (result.elements.length() < index) {
                    result.elements.append(elem);
                    continue;
                }
                result.elements[index] += elem;
            }
        }
        elements = result.elements;
    }

    myPolynomial<T> mult_(myPolynomial<T> polynomial) {
        return myPolynomial<T>(this).mult(polynomial);
    }

    myPolynomial<T> operator*(myPolynomial<T> polynomial) {
        return myPolynomial<T>(this).mult(polynomial);
    }

    void scalarMult(T item) {
        for (int i = 0; i < elements.length(); i++) {
            elements[i] *= item;
        }
    }

    myPolynomial<T> scalarMult_(T item) {
        return myPolynomial<T>(this).scalarMult(item);
    }

    myPolynomial<T> operator*(T item) {
        return myPolynomial<T>(this).scalarMult(item);
    }

    myPolynomial<T> pow_(int degree) {
        auto res = myPolynomial<T>(this);
        auto p = res;
        for (int i = 1; i < degree; i++) {
            res *= p;
        }
        return res;
    }

    T getValue(T item) {
        T res = elements[0];
        for (int i = 0; i < elements.length(); i++) {
            T val = item;
            for (int j = 1; j < i; j++) {
                val *= item;
            }
            res += val * elements[i];
        }

        return res;
    }

    T operator () (T item) {
        return myPolynomial<T>(this).getValue(item);
    }

    myPolynomial<T> getValue(myPolynomial<T> polynomial) {
        auto res = myPolynomial<T>(elements[0]);
        for (int i = 1; i < elements.length(); i++) {
            res += elements[i] * polynomial.pow_(i);
        }
        return res;
    }

    myPolynomial<T> operator () (myPolynomial<T> polynomial) {
        return myPolynomial<T>(this).getValue(polynomial);
    }
};


#endif //LAB2_MYPOLYNOMIAL_H
