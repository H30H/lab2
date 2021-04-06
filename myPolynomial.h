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
    friend std::ostream;

    explicit myPolynomial(myArraySequence<T> &arraySequence) : elements(myArraySequence<T>(arraySequence)) {};

    explicit myPolynomial(T item) : elements(myArraySequence<T>(item)) {};

    myPolynomial() : elements(myArraySequence<T>()) {};

    myPolynomial(const myPolynomial<T> &polynomial) : elements(polynomial.elements) {};

    /*myPolynomial(myPolynomial<int> polynomial) {
        elements = polynomial.elements;
    }*/
    T get(int index) {
        return elements[index];
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

    myPolynomial<T> add_(myPolynomial<T> polynomial) {
        return myPolynomial<T>(*this).add(polynomial);
    }

    myPolynomial<T> operator+(myPolynomial<T> polynomial) {
        return myPolynomial<T>(*this).add(polynomial);
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

    myPolynomial<T> sub_(myPolynomial<T> polynomial) {
        return myPolynomial<T>(*this).sub(polynomial);
    }

    myPolynomial<T> operator-(myPolynomial<T> polynomial1) {
        return myPolynomial<T>(*this).sub(polynomial1);
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

    myPolynomial<T> mult_(myPolynomial<T> polynomial) {
        return myPolynomial<T>(*this).mult(polynomial);
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

    myPolynomial<T> scalarMult_(T item) {
        return myPolynomial<T>(*this).scalarMult(item);
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

    friend std::ostream &operator << (std::ostream &cout, myPolynomial<T> polynomial) {
        for (int i = 0; i < polynomial.elements.length(); i++) {
            if (polynomial.elements[i] == 0) continue;
            cout << '(' << polynomial.elements[i] << ")*x^" << i << " + ";
        }
       return cout << "\b\b\b";
    }

    myPolynomial<T> &operator = (const myPolynomial<T> &polynomial) {
        elements = polynomial.elements;
        return *this;
    }

    myPolynomial<T> map (T value, T (*func)(T value1, T value2)) {
        for (auto &i : elements) {
            i = func(i, value);
        }
        return *this;
    }

    myPolynomial<T> map(T (*funcEl)(int index), T (*func)(T value1, T value2)) {
        for (int i = 0; i < elements.length(); i++) {
            elements[i] = func(elements[i], funcEl(i));
        }

        return *this;
    }

    /*
    friend std::string to_string(myPolynomial<T> polynomial) {
        std::string res("");
        //for (auto i : )
    }/**/
};

/*
myPolynomial<int> operator + (myPolynomial<int> pol1, myPolynomial<int> pol2) {
    pol1.add(pol2);
    return pol2;
}

//template<> class myPolynomial<int>;
//template<> class myPolynomial<float>;
//template<> class myPolynomial<double>;
/*
template<int> std::ostream &operator << (std::ostream &cout, const myPolynomial<int> &polynomial) {
    return cout << polynomial;
};*/

#endif //LAB2_MYPOLYNOMIAL_H
