//newton.c
#include "mathlib.h"

#include <stdio.h>
#define EPSILON 1e-14

static double iters;

double sqrt_newton(double x) {
    double div = 1;
    double mul = 1;
    double total;
    double guess = 0;
    while (x > 4) {
        //loop while x is greater than 4
        x /= 4;
        //x equals x divided by 4
        div *= 2;
        //div equals div times 2
        iters += 1;
    }
    while (absolute(mul - guess) > EPSILON) {
        guess = mul;
        //set the prev to old current value
        mul = (mul + x / mul) / 2;
        //set the mul to (mul*x/mul)/2
        iters += 1;
        total = div * mul;
        //set the total to div*mul
    }
    return total;
}

int sqrt_newton_iters(void) {
    return iters;
    //return the static iters value
}
