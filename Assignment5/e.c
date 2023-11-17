//e.c
#include "mathlib.h"

#include <stdio.h>
#define EPSILON 1e-14

static double terms;

double e(void) {
    double value = 0.0;
    double total = 0.0;
    double temp = 1;
    double sum = 1;
    double fact_val = 1;
    double previous_value = 0;
    for (double k = 0; absolute(sum - previous_value) > EPSILON; k++) {
        value = k;
        previous_value = sum;
        value = temp * fact_val;
        //previous times the next number
        temp = value;
        //have the temp hold the value of the variable
        fact_val += 1;
        total = 1 / value;
        //set the total to 1 divided by the value
        sum += total;
        //add the value to a sum variable
        terms += 1;
    }
    return sum;
}

int e_terms(void) {
    return terms;
    //return the terms static value
}
