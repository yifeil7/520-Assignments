// complex.c
#include "complex.h"
#include <math.h>

struct Complex add(struct Complex a, struct Complex b) {
    struct Complex result;
    result.real = a.real + b.real;
    result.im = a.im + b.im;
    return result;
}

struct Complex negate(struct Complex a) {
    struct Complex result;
    result.real = -a.real;
    result.im = -a.im;
    return result;
}

struct Complex multiply(struct Complex a, struct Complex b) {
    struct Complex result;
    result.real = a.real * b.real - a.im * b.im;
    result.im = a.real * b.im + a.im * b.real;
    return result;
}

double magnitude(struct Complex a) {
    return sqrt(a.real * a.real + a.im * a.im);
}

