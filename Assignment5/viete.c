//viete.c
#include "mathlib.h"

#include <stdio.h>
#define EPSILON 1e-14

static double factors = 0;

double pi_viete(void) {
    double total = 1;
    double temp = 0;
    double div = 0;
    double previous_value = 0;
    for (factors = 1; absolute(total - previous_value) > EPSILON; factors++) {
        //new minus previous is less than epsilon, then stop
        previous_value = total;
        //set the new previous value
        temp = sqrt_newton(2 + temp);
        //setting the current to the sqrt of 2 plus the last
        div = temp / 2;
        //set the current over 2
        total *= div;
        //multiply it to the previous values
    }
    total = 2 / total;
    //divide 2 by the total to get pi
    factors = factors - 1;
    return total;
}

int pi_viete_factors(void) {
    return factors;
    //return the factor static value
}
