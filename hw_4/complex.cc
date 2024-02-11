#include "complex.h"
#include <math.h>

Complex operator+(const Complex& a, const Complex& b) {
    return Complex(a.re + b.re, a.im + b.im);
}

Complex operator*(const Complex& a, const Complex& b) {
    return Complex(a.re * b.re - a.im * b.im, a.re * b.im + a.im * b.re);
}

bool operator==(const Complex& a, const Complex& b) {
    return a.re == b.re && a.im == b.im;
}
