//
// Created by Grisha on 24.03.2021.
//

#ifndef LAB2_MYPOLYNOMIAL_H
#define LAB2_MYPOLYNOMIAL_H

#include <iostream>
#include "myArraySequence.h"
#include "myListSequence.h"

template<class T>
T addEl(T el1, T el2) {
    return el1 + el2;
}

template<class T>
T subEl(T el1, T el2) {
    return el1 - el2;
}

template<class T>
T multEl(T el1, T el2) {
    return el1 * el2;
}

template<class T>
class myPolynomial {
private:
    myArraySequence<T> elements;
public:
    friend std::ostream &operator << (std::ostream &cout, myPolynomial<T> polynomial) {
        for (int i = 0; i < polynomial.elements.length(); i++) {
            if (polynomial.elements[i] == 0) continue;
            cout << '(' << polynomial.elements[i] << ")*x^" << i << " + ";
        }
        return cout << "\b\b\b";
    }

    explicit myPolynomial(myArraySequence<T> &arraySequence) : elements(myArraySequence<T>(arraySequence)) {};

    explicit myPolynomial(T item) : elements(myArraySequence<T>(item)) {};

    myPolynomial() : elements(myArraySequence<T>()) {};

    myPolynomial(const myPolynomial<T> &polynomial) : elements(polynomial.elements) {};

    T get(int index) {
        return elements[index];
    }

    void checkLength() {
        int i;
        for (i = elements.length() - 1; i > 0 && elements[i] != 0; i--);
        i++;
        if (i != elements.length())
            elements.remove(i);
    }

    int length() {
        return elements.length();
    }

    T &operator[](int index) {
        return elements[index];
    }

    myPolynomial<T> add(myPolynomial<T> polynomial) {

        for (int i = 0; i < polynomial.elements.length() && i < elements.length(); i++) {
            elements[i] += polynomial[i];
        }

        for (int i = elements.length(); i < polynomial.elements.length(); i++) {
            elements.append(polynomial[i]);
        }
        return *this;
    }

    myPolynomial<T> operator+(myPolynomial<T> polynomial) {
        return (*this).add(polynomial);
    }

    myPolynomial<T> operator+() {
        return *this;
    }
    /**/
    myPolynomial<T> sub(myPolynomial<T> polynomial) {
        for (int i = 0; i < polynomial.elements.length() && i < elements.length(); i++) {
            elements[i] = -polynomial[i];
        }

        for (int i = elements.length(); i < polynomial.elements.length(); i++) {
            elements.append(0 - polynomial[i]);
        }
        return *this;
    }

    myPolynomial<T> operator-(myPolynomial<T> polynomial1) {
        return(*this).sub(polynomial1);
    }

    myPolynomial<T> operator-() {
        return myPolynomial<T>().sub(*this);
    }

    myPolynomial<T> mult(myPolynomial<T> polynomial) {
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
        return *this;
    }

    myPolynomial<T> operator*(myPolynomial<T> polynomial) {
        return myPolynomial<T>(*this).mult(polynomial);
    }

    myPolynomial<T> scalarMult(T item) {
        for (int i = 0; i < elements.length(); i++) {
            elements[i] *= item;
        }
        return *this;
    }

    myPolynomial<T> operator*(T item) {
        return myPolynomial<T>(*this).scalarMult(item);
    }

    myPolynomial<T> pow_(int degree) {
        auto res = myPolynomial<T>(*this);
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
        return myPolynomial<T>(*this).getValue(item);
    }

    myPolynomial<T> getValue(myPolynomial<T> polynomial) {
        auto res = myPolynomial<T>(elements[0]);
        for (int i = 1; i < elements.length(); i++) {
            res += elements[i] * polynomial.pow_(i);
        }
        return res;
    }

    myPolynomial<T> operator () (myPolynomial<T> polynomial) {
        return myPolynomial<T>(*this).getValue(polynomial);
    }

    myPolynomial<T> &operator = (const myPolynomial<T> &polynomial) {
        elements = polynomial.elements;
        return *this;
    }

    int operator == (myPolynomial<T> polynomial) {
        if (elements.length() != polynomial.length()) return 0;

        for (int i = 0; i < elements.length(); i++) {
            if (elements[i] != polynomial[i])
                return 0;
        }
        return 1;
    }

    int operator == (T value) {
        if (elements.length() == 1 && elements[0] == value) return 1;

        if (elements.length() == 0 && value == 0) return 1;

        return 0;
    }

    myPolynomial<T> map (T value, T (*func)(T value1, T value2)) {
        for (auto &i : elements) {
            i = func(i, value);
        }
        return *this;
    }

    myPolynomial<T> map(myPolynomial<T> polynomial, T (*func)(T value1, T value2)) {
        for (int i = 0; i < elements.length() && i < polynomial.elements.length(); i++) {
            elements[i] = func(elements[i], polynomial[i]);
        }

        return *this;
    }
};

#endif //LAB2_MYPOLYNOMIAL_H
